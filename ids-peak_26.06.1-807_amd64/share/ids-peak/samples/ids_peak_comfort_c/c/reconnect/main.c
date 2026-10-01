/*!
 * \file    main.c
 * \author  IDS Imaging Development Systems GmbH
 *
 * \version 1.0.0
 *
 * Copyright (C) 2023 - 2024, IDS Imaging Development Systems GmbH.
 *
 * The information in this document is subject to change without notice
 * and should not be construed as a commitment by IDS Imaging Development Systems GmbH.
 * IDS Imaging Development Systems GmbH does not assume any responsibility for any errors
 * that may appear in this document.
 *
 * This document, or source code, is provided solely as an example of how to utilize
 * IDS Imaging Development Systems GmbH software libraries in a sample application.
 * IDS Imaging Development Systems GmbH does not assume any responsibility
 * for the use or reliability of any portion of this document.
 *
 * General permission to copy or modify is hereby granted.
 */
#define VERSION "1.0.0"

#include <ids_peak_comfort_c/ids_peak_comfort_c.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#if _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <process.h>
#    include <windows.h>
#    define FUNC_RET unsigned int
#    define CALL_CONV __stdcall
typedef HANDLE THREAD_HANDLE;
#else
#    include <pthread.h>
#    define FUNC_RET void*
#    define CALL_CONV
typedef pthread_t THREAD_HANDLE;
#endif

peak_camera_handle hCam;
peak_message_queue_handle hMessageQueue;

// Checks the status code end exits if error occurs.
void checkSuccess(peak_status status, const char* message);

// Returns the camera descriptor from device in use.
peak_camera_descriptor getCameraDescriptor();

// Opens the first available camera.
void initializeCamera();
// Closes the camera.
void deInitializeCamera();

// Enables the reconnect for the appropriate interface based on the camera type.
void enableReconnect();

// Handling acquisition.
void startAcquisitionLoop();
void stopAcquisitionLoop();
FUNC_RET CALL_CONV acquisitionLoopProc(void* context);

// Handling messages.
void startMessageLoop();
void stopMessageLoop();
FUNC_RET CALL_CONV messageLoopProc(void* context);

// Creates, enables the disconnected and reconnected messages and starts the queue.
void initializeMessageHandling();
// Destroys the message_queue.
void deInitializeMessageHandling();

// Thread veriables and helper functions.
THREAD_HANDLE hMessageThread;
THREAD_HANDLE hAcquisitionThread;
THREAD_HANDLE startThread(FUNC_RET(CALL_CONV* callback)(void*));
void stopThread(THREAD_HANDLE threadHandle);

int main(int argc, char* argv[])
{
    peak_status status = peak_Library_Init();
    checkSuccess(status, "peak_Library_Init");

    initializeCamera();
    enableReconnect();

    initializeMessageHandling();
    startMessageLoop();

    fprintf(stdout,
        "Now you can disconnect or reboot the device to trigger a reconnect!\n"
        "Press ENTER to quit.\n");

    startAcquisitionLoop();

    getchar();

    stopAcquisitionLoop();
    stopMessageLoop();

    deInitializeMessageHandling();
    deInitializeCamera();

    status = peak_Library_Exit();
    checkSuccess(status, "peak_Library_Exit");

    return 0;
}

void checkSuccess(peak_status status, const char* message)
{
    if (status != PEAK_STATUS_SUCCESS)
    {
        size_t lastErrorMessageSize = 2048;
        char lastErrorMessage[2048] = {0};
        peak_status lastStatus;
        peak_Library_GetLastError(&lastStatus, lastErrorMessage, &lastErrorMessageSize);
        fprintf(stderr, "%s failed with: %d\n", message, status);
        fprintf(stderr, "LastErrorCode: %d\n", lastStatus);
        fprintf(stderr, "LastErrorMessage: %s\n", lastErrorMessage);
        exit(status);
    }
}

peak_camera_descriptor getCameraDescriptor()
{
    peak_camera_id cameraID = peak_Camera_ID_FromHandle(hCam);

    peak_camera_descriptor cameraDescriptor;
    peak_status status = peak_Camera_GetDescriptor(cameraID, &cameraDescriptor);
    checkSuccess(status, "peak_Camera_GetDescriptor");

    return cameraDescriptor;
}

void initializeCamera()
{
    size_t cameraCount = 0;
    peak_status status = peak_CameraList_Update(&cameraCount);
    checkSuccess(status, "peak_CameraList_Update");

    if (cameraCount == 0)
    {
        fprintf(stdout, "No cameras found!\n");
        exit(0);
    }

    status = peak_Camera_OpenFirstAvailable(&hCam);
    checkSuccess(status, "peak_Camera_Open");

    peak_camera_descriptor cameraDescriptor = getCameraDescriptor();
    fprintf(stdout, "Device(%" PRIu64 ")  opened: %s\n", cameraDescriptor.cameraID, cameraDescriptor.modelName);
}

void deInitializeCamera()
{
    peak_status status = peak_Camera_Close(hCam);
    checkSuccess(status, "peak_Camera_Close");
}

void enableReconnect()
{
    peak_camera_descriptor cameraDescriptor = getCameraDescriptor();
    peak_status status = PEAK_STATUS_SUCCESS;

    peak_interface_technology technology = cameraDescriptor.interfaceTechnology;

    if (peak_Library_InterfaceTechnology_IsSupported(technology))
    {
        peak_access_status  access = peak_Reconnect_GetAccessStatus(technology);
        if (PEAK_IS_WRITEABLE(access))
        {
            status = peak_Reconnect_Enable(technology, PEAK_TRUE);
            checkSuccess(status, "peak_Reconnect_Enable");
        }
        else if (PEAK_IS_READABLE(access))
        {
            if (!peak_Reconnect_IsEnabled(technology))
            {
                status = PEAK_STATUS_ERROR;
                fprintf(stdout, "Reconnect is not enabled and not accessible to change!\n");
                exit(status);
            }
        }
        else
        {
            status = PEAK_STATUS_ACCESS_DENIED;
            fprintf(stdout, "Reconnect not supported!\n");
            exit(status);
        }
    }
    else
    {
        status = PEAK_STATUS_ERROR;
        fprintf(stdout, "InterfaceTechnology is not supported!\n");
        exit(status);
    }
}

void startAcquisitionLoop()
{
    peak_status status = peak_Acquisition_Start(hCam, PEAK_INFINITE);
    checkSuccess(status, "peak_Acquisition_Start");

    hAcquisitionThread = startThread(acquisitionLoopProc);
}

FUNC_RET CALL_CONV acquisitionLoopProc(void* context)
{
    (void)context;

    while (true)
    {
        peak_frame_handle hFrame;
        peak_status status = peak_Acquisition_WaitForFrame(hCam, PEAK_INFINITE, &hFrame);
        if (status == PEAK_STATUS_SUCCESS)
        {
            peak_frame_info frameInfo;
            status = peak_Frame_GetInfo(hFrame, &frameInfo);
            checkSuccess(status, "peak_Frame_GetInfo");

            fprintf(stdout, "Image with ID: %" PRIu64 "\n", frameInfo.frameID);

            status = peak_Frame_Release(hCam, hFrame);
            checkSuccess(status, "peak_Frame_Release");
        }
        else if (status == PEAK_STATUS_ABORTED || status == PEAK_STATUS_ACCESS_DENIED)
        {
            fprintf(stdout, "Stopping acquisition loop\n");
            break;
        }
        else
        {
            fprintf(stdout, "Unexpected error: %d\n", status);
            exit(status);
        }
    }

    return 0;
}

void stopAcquisitionLoop()
{
    peak_status status = peak_Acquisition_Stop(hCam);
    checkSuccess(status, "peak_Acquisition_Stop");

    stopThread(hAcquisitionThread);
}

void startMessageLoop()
{
    hMessageThread = startThread(messageLoopProc);
}

void stopMessageLoop()
{
    peak_status status = peak_MessageQueue_Stop(hMessageQueue);
    checkSuccess(status, "peak_MessageQueue_Stop");

    stopThread(hMessageThread);
}

void initializeMessageHandling()
{
    peak_status status = peak_MessageQueue_Create(&hMessageQueue);
    checkSuccess(status, "peak_MessageQueue_Create");

    status = peak_MessageQueue_EnableMessage(hMessageQueue, NULL, PEAK_MESSAGE_TYPE_DEVICE_RECONNECTED);
    checkSuccess(
        status, "peak_MessageQueue_EnableMessage with type PEAK_MESSAGE_TYPE_DEVICE_RECONNECTED");

    status = peak_MessageQueue_EnableMessage(hMessageQueue, NULL, PEAK_MESSAGE_TYPE_DEVICE_DISCONNECTED);
    checkSuccess(
        status, "peak_MessageQueue_EnableMessage with type PEAK_MESSAGE_TYPE_DEVICE_DISCONNECTED");

    status = peak_MessageQueue_Start(hMessageQueue);
    checkSuccess(status, "peak_MessageQueue_Start");
}

FUNC_RET CALL_CONV messageLoopProc(void* context)
{
    (void)context;

    while (true)
    {
        peak_message_handle hMessage;
        peak_status status = peak_MessageQueue_WaitForMessage(
            hMessageQueue, PEAK_INFINITE, &hMessage);
        if (status == PEAK_STATUS_SUCCESS)
        {
            peak_message_type messageType;
            status = peak_Message_Type_Get(hMessage, &messageType);
            checkSuccess(status, "peak_Message_Type_Get");

            if (messageType == PEAK_MESSAGE_TYPE_DEVICE_DISCONNECTED)
            {
                peak_message_data_device_disconnected disconnectedData;
                status = peak_Message_Data_DeviceDisconnected_Get(hMessage, &disconnectedData);
                checkSuccess(status, "peak_Message_Data_DeviceDisconnected_Get");

                fprintf(stdout, "Device(%" PRIu64 ") disconnected: %s\n", disconnectedData.cameraDescriptor.cameraID,
                    disconnectedData.cameraDescriptor.modelName);
            }
            else if (messageType == PEAK_MESSAGE_TYPE_DEVICE_RECONNECTED)
            {
                peak_message_data_device_reconnected reconnectedData;
                status = peak_Message_Data_DeviceReconnected_Get(hMessage, &reconnectedData);
                checkSuccess(status, "peak_Message_Data_DeviceReconnected_Get");

                fprintf(stdout,
                    "Device(%" PRIu64 ") reconnected: %s\n"
                    "  isReconnectSuccessful:   %u\n"
                    "  isAcquisitionRunning:    %u\n"
                    "  isConfigurationRestored: %u\n",
                    reconnectedData.cameraDescriptor.cameraID, reconnectedData.cameraDescriptor.modelName,
                    reconnectedData.reconnectInformation.isReconnectSuccessful,
                    reconnectedData.reconnectInformation.isAcquisitionRunning,
                    reconnectedData.reconnectInformation.isConfigurationRestored);
            }
        }
        else if (status == PEAK_STATUS_ABORTED)
        {
            fprintf(stdout, "Stopping message queue loop!\n");
            break;
        }
    }

    return 0;
}

void deInitializeMessageHandling()
{
    peak_status status = peak_MessageQueue_Destroy(hMessageQueue);
    checkSuccess(status, "peak_MessageQueue_Destroy");

    hMessageQueue = NULL;
}

THREAD_HANDLE startThread(FUNC_RET(CALL_CONV* callback)(void*))
{
    THREAD_HANDLE threadHandle;
#if defined _WIN32
    threadHandle = (HANDLE)_beginthreadex(NULL, 0, callback, NULL, 0, NULL);
    if (!threadHandle)
    {
        fprintf(stderr, "_beginthreadex: Error!\n");
        exit(-1);
    }
#else
    int result;
    if ((result = pthread_create(&threadHandle, NULL, callback, NULL)) != 0)
    {
        fprintf(stderr, "pthread_create: Error: %d\n", result);
        exit(result);
    }
#endif
    return threadHandle;
}

void stopThread(THREAD_HANDLE threadHandle)
{
#if defined _WIN32
    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);
#else
    pthread_join(threadHandle, NULL);
#endif
}
