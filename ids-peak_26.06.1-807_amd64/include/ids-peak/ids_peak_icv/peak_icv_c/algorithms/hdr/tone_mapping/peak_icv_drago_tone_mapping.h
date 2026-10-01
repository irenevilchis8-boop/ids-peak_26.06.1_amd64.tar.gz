/*!
 * \file    peak_icv_drago_tone_mapping.h
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
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
struct peak_icv_tone_mapping_drago;

/*!
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
typedef struct peak_icv_tone_mapping_drago* peak_icv_tone_mapping_drago_handle;

/*!
 * Must be freed later using peak_icv_ToneMapping_Drago_Destroy().
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Drago_Create(peak_icv_tone_mapping_drago_handle* tone_mapping_handle);

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
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Drago_Destroy(peak_icv_tone_mapping_drago_handle tone_mapping_handle);

/*!
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Drago_GetOutputPixelFormat(peak_icv_tone_mapping_drago_handle tone_mapping_handle,
    peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);

/*!
 * This function compresses the dynamic range of the `input_hdr_image` using a logarithmic
 * curve adapted to human visual perception.
 * It is based on Adaptive Logarithmic Mapping For Displaying High Contrast Scenes Paper
 * from F. Drago, K. Myszkowski, T. Annen and N. Chiba from the year 2003.
 *
 * See paper: [External link](https://resources.mpi-inf.mpg.de/tmo/logmap/logmap.pdf)
 *
 * The `output_ldr_image` must be created by the caller
 * with dimensions matching the input image
 * and a compatible LDR pixel format
 * (which can be queried via \ref peak_icv_ToneMapping_Drago_GetOutputPixelFormat).
 * The existing contents of the `output_ldr_image` will be overwritten.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_MISMATCH
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \ingroup ids_peak_icv_c_tone_mapping
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_ToneMapping_Drago_Process(peak_icv_tone_mapping_drago_handle tone_mapping_handle,
    peak_icv_image_handle input_hdr_image, peak_icv_image_handle output_ldr_image);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
