/*!
 * \file    main.c
 * \author  IDS Imaging Development Systems GmbH
 *
 * \version 1.0.0
 *
 * Copyright (C) 2024, IDS Imaging Development Systems GmbH.
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

peak_message_queue_handle hMessageQueue;

// Handling messages.
void startMessageLoop();
void stopMessageLoop();
FUNC_RET CALL_CONV messageLoopProc(void* context);

// Creates, enables the disconnected and reconnected messages and starts the queue.
void initializeMessageHandling();
// Destroys the message_queue.
void deInitializeMessageHandling();

THREAD_HANDLE hMessageThread;
THREAD_HANDLE startThread(FUNC_RET(CALL_CONV* callback)(void*));
void stopThread(THREAD_HANDLE threadHandle);

// Checks the status code end exits if error occurs.
void checkSuccess(peak_status status, const char* message);

int main(int argc, char* argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    if (argc != 2)
    {
        printf("Too many arguments or missing guf file argument!\n");
        return -1;
    }

    peak_status status = peak_Library_Init();
    checkSuccess(status, "peak_Library_Init");

    // NOTE: We need to update the camera list, as it is used by
    //       `peak_FirmwareUpdate_CompatibleCameraList_Get`
    status = peak_CameraList_Update(NULL);
    checkSuccess(status, "peak_CameraList_Update");

    const char* gufPath = argv[1];
    size_t size = 0;
    status = peak_FirmwareUpdate_CompatibleCameraList_Get(gufPath, NULL, &size);
    checkSuccess(status, "peak_FirmwareUpdate_CompatibleCameraList_Get");

    if (size == 0)
    {
        printf("No updatable devices found.\n");
        return 0;
    }

    printf("Found %zu cameras that can be updated using the GUF file at: %s\n", size, gufPath);

    peak_camera_descriptor* compatibleCameras = malloc(size * sizeof(peak_camera_descriptor));
    status = peak_FirmwareUpdate_CompatibleCameraList_Get(gufPath, compatibleCameras, &size);
    checkSuccess(status, "peak_FirmwareUpdate_CompatibleCameraList_Get");

    printf("The following cameras will be updated:\n");
    for (int i = 0; i < size; ++i)
    {
        const peak_camera_descriptor* compatibleCamera = &compatibleCameras[i];
        printf("\tModel %s Serial %s\n", compatibleCamera->modelName, compatibleCamera->serialNumber);
    }

    printf("Continue? y/n: ");
    char answer = (char)getchar();
    if (answer != 'y')
    {
        printf("Update aborted!\n");
        return 0;
    }

    initializeMessageHandling();
    startMessageLoop();

    for (int i = 0; i < size; ++i)
    {
        const peak_camera_descriptor* compatibleCamera = &compatibleCameras[i];
        printf("Updating camera: Model %s Serial %s\n", compatibleCamera->modelName, compatibleCamera->serialNumber);
        status = peak_FirmwareUpdate_Execute(compatibleCamera->cameraID, gufPath);
        checkSuccess(status, "peak_FirmwareUpdate_Execute");
    }

    stopMessageLoop();
    deInitializeMessageHandling();

    free(compatibleCameras);

    status = peak_Library_Exit();
    checkSuccess(status, "peak_Library_Exit");

    return 0;
}

void checkSuccess(peak_status status, const char* message)
{
    if (status != PEAK_STATUS_SUCCESS)
    {
        size_t lastErrorMessageSize = 2048;
        char lastErrorMessage[2048] = { 0 };
        peak_status lastStatus;
        peak_Library_GetLastError(&lastStatus, lastErrorMessage, &lastErrorMessageSize);
        fprintf(stderr, "%s failed with: %d\n", message, status);
        fprintf(stderr, "LastErrorCode: %d\n", lastStatus);
        fprintf(stderr, "LastErrorMessage: %s\n", lastErrorMessage);

        (void)peak_Library_Exit();
        exit(status);
    }
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

    status = peak_MessageQueue_EnableMessage(hMessageQueue, NULL, PEAK_MESSAGE_TYPE_FIRMWARE_UPDATE);
    checkSuccess(
        status, "peak_MessageQueue_EnableMessage with type PEAK_MESSAGE_TYPE_FIRMWARE_UPDATE");

    status = peak_MessageQueue_Start(hMessageQueue);
    checkSuccess(status, "peak_MessageQueue_Start");
}

const char* firmwareUpdateStepToString(peak_firmware_update_step step)
{
    switch (step)
    {
    case PEAK_FIRMWARE_UPDATE_STEP_TOTAL:
        return "Total";
    case PEAK_FIRMWARE_UPDATE_STEP_CHECKPRECONDITIONS:
        return "Check preconditions";
    case PEAK_FIRMWARE_UPDATE_STEP_ACQUIREUPDATEDATA:
        return "Acquire update data";
    case PEAK_FIRMWARE_UPDATE_STEP_WRITEFEATURE:
        return "Write feature";
    case PEAK_FIRMWARE_UPDATE_STEP_EXECUTEFEATURE:
        return "Execute feature";
    case PEAK_FIRMWARE_UPDATE_STEP_ASSERTFEATURE:
        return "Assert feature";
    case PEAK_FIRMWARE_UPDATE_STEP_UPLOADFILE:
        return "Upload file";
    case PEAK_FIRMWARE_UPDATE_STEP_RESETDEVICE:
        return "Reset device";
    default:
        return "Unknown";
    }
}

FUNC_RET CALL_CONV messageLoopProc(void* context)
{
    (void)context;

    while (true)
    {
        peak_message_handle hMessage;
        peak_status status = peak_MessageQueue_WaitForMessage(
            hMessageQueue, PEAK_INFINITE, &hMessage);
        if (status == PEAK_STATUS_ABORTED)
        {
            printf("Exiting message queue thread...\n");
            break;
        }

        if(status != PEAK_STATUS_SUCCESS)
        {
            continue;
        }

        peak_message_type messageType;
        status = peak_Message_Type_Get(hMessage, &messageType);
        checkSuccess(status, "peak_Message_Type_Get");

        if (messageType != PEAK_MESSAGE_TYPE_FIRMWARE_UPDATE)
        {
            continue;
        }

        peak_message_data_firmware_update data;
        status = peak_Message_Data_FirmwareUpdate_Get(hMessage, &data);
        checkSuccess(status, "peak_Message_Data_FirmwareUpdate_Get");

        if (data.step != PEAK_FIRMWARE_UPDATE_STEP_TOTAL
                && data.stepStatus == PEAK_FIRMWARE_UPDATE_STATUS_FINSIHED)
        {
            continue;
        }

        if (data.stepStatus == PEAK_FIRMWARE_UPDATE_STATUS_PROGRESS)
        {
            printf("\r  Progress: %.2f%%", data.stepProgressPercentage);
            if (data.stepProgressPercentage == 100)
            {
                printf("\n");
            }
        }
        else
        {
            printf("FirmwareUpdate(ID: %" PRIu64 ", Serial: %s, Step: %s) %s\n", data.cameraId,
                data.serialNumber, firmwareUpdateStepToString(data.step), data.description);
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
