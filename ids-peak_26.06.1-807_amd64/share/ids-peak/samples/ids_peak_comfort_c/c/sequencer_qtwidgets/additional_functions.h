/*!
 * \file    additional_functions.h
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

#ifndef ADDITIONAL_FUNCTIONS_H
#define ADDITIONAL_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <ids_peak_comfort_c/ids_peak_comfort_c.h>

typedef enum
{
    SEQUENCER_TRIGGERSOURCE_OFF,
    SEQUENCER_TRIGGERSOURCE_EXPOSURE_START
} sequencer_trigger_source;

peak_status Trigger_SoftwareBurst_Configure(peak_camera_handle hCam, uint32_t burstSize);
peak_status Trigger_SoftwareBurst_Execute(peak_camera_handle hCam);

peak_bool Sequencer_IsSupported(peak_camera_handle hCam);
peak_status Sequencer_EnableConfiguration(peak_camera_handle hCam, peak_bool enable);
peak_status Sequencer_Enable(peak_camera_handle hCam, peak_bool enable);

peak_status SequencerSet_Select(peak_camera_handle hCam, uint32_t sequencerSet);
peak_status SequencerSet_SetNext(peak_camera_handle hCam, uint32_t nextSet);
peak_status SequencerSet_SetTriggerSource(peak_camera_handle hCam, sequencer_trigger_source source);
peak_status SequencerSet_SaveSettings(peak_camera_handle hCam);
peak_status SequencerSet_LoadSettings(peak_camera_handle hCam);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // ADDITIONAL_FUNCTIONS_H
