/*!
 * \file    peak_icv_linear_tone_mapping.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-05-22
 * \since   ids_peak_icv 1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/types/peak_common_simple_types.h>
#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \warning This function is still in development and not released.
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
struct peak_icv_tone_mapping_linear;

/*!
 * \warning This function is still in development and not released.
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
typedef struct peak_icv_tone_mapping_linear* peak_icv_tone_mapping_linear_handle;

/*!
 * Must be freed later using peak_icv_ToneMapping_Linear_Destroy().
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \warning This function is still in development and not released.
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_Create(peak_icv_tone_mapping_linear_handle* tone_mapping_handle);

/*!
 * \brief Destroys a tone mapping handle.
 *
 * \destroyHandle{tone mapping}
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \warning This function is still in development and not released.
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_Destroy(peak_icv_tone_mapping_linear_handle tone_mapping_handle);

/*!
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \warning This function is still in development and not released.
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_GetOutputPixelFormat(peak_icv_tone_mapping_linear_handle tone_mapping_handle,
    peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);

/*!
 * Maps a specific exposure window of an HDR image linearly to an LDR image.
 *
 * The exposure window is defined by the `centerExposureValue` (in EV) and the total
 * dynamic range specified by `numberOfStops`. Pixels with an exposure falling within
 * the window `[centerExposureValue - (numberOfStops / 2), centerExposureValue + (numberOfStops / 2)]`
 * are mapped linearly to the full LDR range. Values outside this window are clipped.
 *
 * The `ldrImage` must be created by the caller with dimensions matching the `hdrImage`
 * and a compatible LDR pixel format (which can be queried via
 * \ref peak_icv_ToneMapping_Linear_GetOutputPixelFormat).
 * The existing contents of the `ldrImage` will be overwritten.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_MISMATCH
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \warning This function is still in development and not released.
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_Process(peak_icv_tone_mapping_linear_handle tone_mapping_handle,
    peak_icv_image_handle hdr_image, float center_exposure_value, float number_of_stops, peak_icv_image_handle ldr_image);

/*!
 * Computes the absolute minimum and maximum exposure values (EV) of an HDR image.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_MISMATCH
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \warning This function is still in development and not released.
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_GetExposureValueRange(
    peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_icv_image_handle hdr_image, peak_common_interval_f* range);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
