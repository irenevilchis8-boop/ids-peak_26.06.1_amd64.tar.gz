/*!
 * \file    additional_functions.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-10-31
 * \since   2.14.0
 *
 * \brief   This file provides functions to control the sequence mode.
 *          They are implemented over the ComfortC GFA functions.
 *
 * \version 1.0.0
 *
 * Copyright (C) 2024 - 2026, IDS Imaging Development Systems GmbH.
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

#include "additional_functions.h"


peak_status CheckStatusAndDisableGfaWriteAccess(peak_camera_handle hCam, peak_status status)
{
    peak_status statusGfa = peak_GFA_EnableWriteAccess(hCam, PEAK_FALSE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }
    else
    {
        return statusGfa;
    }
}

peak_status Trigger_SoftwareBurst_Configure(peak_camera_handle hCam, uint32_t burstSize)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "TriggerSelector", "ExposureStart");
    if (PEAK_STATUS_SUCCESS != status)
    {
        return CheckStatusAndDisableGfaWriteAccess(hCam, status);
    }

    status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "TriggerSource", "Counter0Active");
    if (PEAK_STATUS_SUCCESS != status)
    {
        return CheckStatusAndDisableGfaWriteAccess(hCam, status);
    }

    status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "TriggerActivation", "LevelHigh");
    if (PEAK_STATUS_SUCCESS != status)
    {
        return CheckStatusAndDisableGfaWriteAccess(hCam, status);
    }

    status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "TriggerMode", "On");
    if (PEAK_STATUS_SUCCESS != status)
    {
        return CheckStatusAndDisableGfaWriteAccess(hCam, status);
    }

    status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "CounterSelector", "Counter0");
    if (PEAK_STATUS_SUCCESS != status)
    {
        return CheckStatusAndDisableGfaWriteAccess(hCam, status);
    }

    status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "CounterEventSource", "ExposureStart");
    if (PEAK_STATUS_SUCCESS != status)
    {
        return CheckStatusAndDisableGfaWriteAccess(hCam, status);
    }

    status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "CounterEventActivation", "RisingEdge");
    if (PEAK_STATUS_SUCCESS != status)
    {
        return CheckStatusAndDisableGfaWriteAccess(hCam, status);
    }

    status = peak_GFA_Integer_Set(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "CounterDuration", burstSize);
    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}

peak_status Trigger_SoftwareBurst_Execute(peak_camera_handle hCam)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    status = peak_GFA_Command_Execute(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "CounterReset");
    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}

peak_bool Sequencer_IsSupported(peak_camera_handle hCam)
{
    if (PEAK_STATUS_SUCCESS == peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE))
    {
        if (PEAK_ACCESS_READWRITE == peak_GFA_Feature_GetAccessStatus(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerConfigurationMode"))
        {
            if (PEAK_STATUS_SUCCESS == peak_GFA_EnableWriteAccess(hCam, PEAK_FALSE))
            {
                return PEAK_TRUE;
            }
        }
    }

    return PEAK_FALSE;
}

peak_status Sequencer_EnableConfiguration(peak_camera_handle hCam, peak_bool enable)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    if (enable == PEAK_TRUE)
    {
        status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerConfigurationMode", "On");
    }
    else
    {
        status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerConfigurationMode", "Off");
    }

    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}

peak_status Sequencer_Enable(peak_camera_handle hCam, peak_bool enable)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    if (PEAK_ACCESS_READWRITE != peak_GFA_Feature_GetAccessStatus(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerMode"))
    {
        return CheckStatusAndDisableGfaWriteAccess(hCam, PEAK_STATUS_ACCESS_DENIED);
    }

    if (enable == PEAK_TRUE)
    {
        status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerMode", "On");
    }
    else
    {
        status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerMode", "Off");
    }

    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}

peak_status SequencerSet_Select(peak_camera_handle hCam, uint32_t sequencerSet)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    status = peak_GFA_Integer_Set(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerSetSelector", (int64_t)sequencerSet);
    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}

peak_status SequencerSet_SetNext(peak_camera_handle hCam, uint32_t nextSet)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    status = peak_GFA_Integer_Set(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerSetNext", (int64_t)nextSet);
    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}

peak_status SequencerSet_SetTriggerSource(peak_camera_handle hCam, sequencer_trigger_source source)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    if (source == SEQUENCER_TRIGGERSOURCE_EXPOSURE_START)
    {
        status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerTriggerSource", "ExposureStart");
    }
    else
    {
        status = peak_GFA_Enumeration_SetBySymbolicValue(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerTriggerSource", "Off");
    }

    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}

peak_status SequencerSet_SaveSettings(peak_camera_handle hCam)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    status = peak_GFA_Command_Execute(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerSetSave");
    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}

peak_status SequencerSet_LoadSettings(peak_camera_handle hCam)
{
    peak_status status = peak_GFA_EnableWriteAccess(hCam, PEAK_TRUE);
    if (PEAK_STATUS_SUCCESS != status)
    {
        return status;
    }

    status = peak_GFA_Command_Execute(hCam, PEAK_GFA_MODULE_REMOTE_DEVICE, "SequencerSetLoad");
    return CheckStatusAndDisableGfaWriteAccess(hCam, status);
}
