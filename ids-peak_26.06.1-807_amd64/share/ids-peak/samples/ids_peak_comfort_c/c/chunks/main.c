/*!
 * \file    main.c
 * \author  IDS Imaging Development Systems GmbH
 *
 * \version 1.0.0
 *
 * Copyright (C) 2025, IDS Imaging Development Systems GmbH.
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
#include <stdio.h>
#include <stdlib.h>


// Checks the status code end exits if an error occurs.
void checkSuccess(peak_status status, const char* message);
void autoUpdate(peak_camera_handle hCam);
void manualUpdate(peak_camera_handle hCam);

int main(int argc, char** argv)
{
    peak_camera_handle hCam = PEAK_INVALID_HANDLE;

    peak_status status = peak_Library_Init();
    checkSuccess(status, "peak_Library_Init");

    status = peak_CameraList_Update(NULL);
    checkSuccess(status, "peak_CameraList_Update");

    status = peak_Camera_OpenFirstAvailable(&hCam);
    checkSuccess(status, "peak_Camera_OpenFirstAvailable");

    peak_camera_descriptor cameraDescriptor = { 0 };
    status = peak_Camera_GetDescriptor(peak_Camera_ID_FromHandle(hCam), &cameraDescriptor);
    checkSuccess(status, "peak_Camera_GetDescriptor");

    printf("Using camera %s [%s]\n", cameraDescriptor.modelName, cameraDescriptor.serialNumber);

    // Check if the chunks feature is supported
    peak_access_status accessStatus = peak_Chunks_GetAccessStatus(hCam);
    if (!PEAK_IS_WRITEABLE(accessStatus))
    {
        printf("The camera does not support chunks. Exiting...\n");
        status = peak_Library_Exit();
        checkSuccess(status, "peak_Library_Exit");
        return 0;
    }

    // Enable the chunks
    status = peak_Chunks_Enable(hCam, PEAK_TRUE);
    checkSuccess(status, "peak_Chunks_Enable");

    // Check if timestamp chunk is supported
    accessStatus = peak_Chunks_Type_GetAccessStatus(hCam, PEAK_CHUNKS_TYPE_TIMESTAMP);
    if (!PEAK_IS_WRITEABLE(accessStatus))
    {
        printf("The camera does not support the timestamp chunk. Exiting...\n");
        status = peak_Library_Exit();
        checkSuccess(status, "peak_Library_Exit");
        return 0;
    }

    // Enable the timestamp chunk
    status = peak_Chunks_Type_Enable(hCam, PEAK_CHUNKS_TYPE_TIMESTAMP, PEAK_TRUE);
    checkSuccess(status, "peak_Chunks_Type_Enable");

    printf("Which chunks update mode should be used: (a) auto or (m) manual? ");
    int mode = getchar();

    if (mode == 'm')
    {
        printf("Using manual chunks update mode.\n");
        manualUpdate(hCam);
    }
    else if (mode == 'a')
    {
        printf("Using auto chunks update mode.\n");
        autoUpdate(hCam);
    }
    else
    {
        printf("Unrecognized mode %c! Assuming auto update mode.\n", mode);
        autoUpdate(hCam);
    }

    status = peak_Camera_Close(hCam);
    checkSuccess(status, "peak_Camera_Close");

    status = peak_Library_Exit();
    checkSuccess(status, "peak_Library_Exit");

    return 0;
}

void autoUpdate(peak_camera_handle hCam)
{
    // Start the acquisition normally
    peak_status status = peak_Acquisition_Start(hCam, PEAK_INFINITE);
    checkSuccess(status, "peak_Acquisition_Start");

    // Get 10 frames
    for (int i = 0; i < 10; i++)
    {
        peak_frame_handle hFrame = PEAK_INVALID_HANDLE;
        peak_chunks_timestamp timestampChunk = { 0 };

        // Wait for the frame. Before returning, the chunks will be updated.
        if (PEAK_ERROR(peak_Acquisition_WaitForFrame(hCam, 1000, &hFrame)))
        {
            printf("Could not get frame %d\n", i);
            continue;
        }

        // Get the timestamp chunk and print it
        if (PEAK_SUCCESS(peak_Chunks_Timestamp_Get(hCam, &timestampChunk)))
        {
            printf("Timestamp for frame %d: %"PRIi64"\n", i, timestampChunk.timestamp);
        }
        else
        {
            printf("Could not get timestamp chunk data for frame %d", i);
        }

        status = peak_Frame_Release(hCam, hFrame);
        checkSuccess(status, "peak_Frame_Release");
    }

    status = peak_Acquisition_Stop(hCam);
    checkSuccess(status, "peak_Acquisition_Stop");
}

void manualUpdate(peak_camera_handle hCam)
{
    peak_status status = peak_Chunks_AutoUpdate_Enable(hCam, PEAK_FALSE);
    checkSuccess(status, "peak_Chunks_AutoUpdate_Enable");

    // Create a list for the 4 buffers.
    // Note: As the program exits abnormally in case of an error, the free call is omitted.
    const int numImages = 4;
    peak_frame_handle* listHFrames = (peak_frame_handle*)malloc(sizeof(peak_frame_handle) * numImages);
    if (listHFrames == NULL)
    {
        printf("Could not allocate memory for the frame list!\n");
        exit(-1);
    }

    // Start the acquisition normally
    status = peak_Acquisition_Start(hCam, PEAK_INFINITE);
    checkSuccess(status, "peak_Acquisition_Start");

    int imageCounter = 0;
    for (int i = 0; i < 10 && imageCounter < numImages; i++)
    {
        peak_frame_handle hFrame = PEAK_INVALID_HANDLE;

        // Wait for the frame. No update of the chunks will occur.
        if (PEAK_ERROR(peak_Acquisition_WaitForFrame(hCam, 1000, &hFrame)))
        {
            printf("Could not get frame %d\n", i);
            continue;
        }

        printf("Acquired frame %d\n", imageCounter);

        // Save the buffer in the list
        listHFrames[imageCounter++] = hFrame;
    }

    // Get 10 frames
    for (int i = 0; i < imageCounter; i++)
    {
        peak_chunks_timestamp timestampChunk = { 0 };

        // Update the chunks for frame i now.
        if (PEAK_ERROR(peak_Chunks_Update(hCam, listHFrames[i])))
        {
            printf("Failed to update chunks for frame %d\n", i);
            continue;
        }

        // Get the timestamp chunk and print it
        if (PEAK_SUCCESS(peak_Chunks_Timestamp_Get(hCam, &timestampChunk)))
        {
            printf("Timestamp for frame %d: %"PRIi64"\n", i, timestampChunk.timestamp);
        }
        else
        {
            printf("Could not get timestamp chunk data for frame %d", i);
        }

        status = peak_Frame_Release(hCam, listHFrames[i]);
        checkSuccess(status, "peak_Frame_Release");
    }

    free(listHFrames);

    status = peak_Acquisition_Stop(hCam);
    checkSuccess(status, "peak_Acquisition_Stop");
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

