/*!
 * \file    peak_icv_median_filter.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-09-24
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
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
 * \brief
 *     Applies a median filter to `input_image`
 *     using the specified `kernel_size`
 *     and stores the result in `output_image`.
 *
 * \note
 *     The input and output images must be initialized
 *     with the same pixel format and size
 *     prior to using this function.
 *
 * The median filter is a non-linear, spatial filter
 * used to reduce impulsive noise in images.
 * It replaces each pixel
 * with the median value
 * of the pixels in its local neighborhood,
 * defined by the specified kernel size.
 * The kernel size corresponds to a square neighborhood
 * (size x size grid) around each pixel,
 * where the median is calculated.
 *
 * This process preserves edges better than linear smoothing filters
 * while effectively removing salt-and-pepper noise
 * and small image artifacts.
 * A larger kernel removes more noise
 * but also reduces image detail.
 *
 * \supportedPixelformats{MedianFilter}
 *
 * \note
 *     Processes the entire image,
 *     ignoring any specified image region.
 *
 * \param[in] input_image
 *     The image to be filtered.
 * \param[in] kernel_size
 *     The size of the kernel
 *     must be an odd number
 *     greater than 1
 *     and smaller than the image dimensions.
 * \param[out] output_image
 *     The image to store the filtered result.
 *     Must be initialized with the same pixel format
 *     and size as `input_image`.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 *     The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE
 *     `input_image` or `output_image` is invalid
 *     or uninitialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE
 *     `kernel_size` is not an odd number.
 * \return #PEAK_ICV_STATUS_MISMATCH
 *     Input and output images differ in size.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE
 *     `kernel_size` exceeds image dimensions.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR
 *     An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 *
 * \ingroup ids_peak_icv_c_filter
 */
PEAK_ICV_API_STATUS peak_icv_Filter_Image_Median(
    peak_icv_image_handle input_image, size_t kernel_size, peak_icv_image_handle output_image);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
