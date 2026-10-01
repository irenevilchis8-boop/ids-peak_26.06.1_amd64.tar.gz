/*!
 * \file    peak_icv_image_filter_sharpening.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

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
 * \ingroup ids_peak_icv_c_filter
 * \brief The sharpening function applies a kernel-based sharpening filter to an \p input_image.
 *
 * It enhances edges and fine structures by emphasizing high-frequency components in the image.
 *
 * The strength of the effect is controlled by the \p sharpness_level, where `0` results in no change.
 *
 * \note Increasing the sharpness level can also amplify image noise, especially at higher values.
 *       You can get the valid range using the \ref peak_icv_ImageFilter_Sharpening_GetRange function.
 *
 * \note The input and output images must be initialized with the same pixel format and size prior to using this function.
 *
 * \note This operation disregards any specified image regions. It processes the entire image.
 *
 * \param[in]  input_image      The image to which the sharpness filter will be applied.
 * \param[in]  sharpness_level  The level for sharpening the image.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p input_image must be valid and initialized.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE             The \p sharpness_level must be within the valid range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_ImageFilter_Sharpening_ProcessInPlace(peak_icv_image_handle input_image, uint32_t sharpness_level);

/*!
 * \ingroup ids_peak_icv_c_filter
 * \brief Returns the valid range of sharpness levels.
 *
 * Provides the minimum and maximum values that are accepted by the \ref peak_icv_ImageFilter_Sharpening_ProcessInPlace function.
 *
 * \param[out] range   An interval containing the minimum and maximum allowed sharpness level values.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p range is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_ImageFilter_Sharpening_GetRange(peak_common_interval_u* range);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
