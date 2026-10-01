/*!
 * \file    peak_icv_threshold.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/types/peak_common_simple_types.h>
#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>
#include <peak_icv_c/types/peak_icv_region.h>


#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

typedef void* peak_icv_variant_interval;
typedef const void* c_peak_icv_variant_interval;

/*!
 * \ingroup ids_peak_icv_c_threshold
 * \brief Applies a fixed threshold on a given single-channel image and returns a region with selected pixels
 * whose gray values are in the range minimum <= gray value <= maximum.
 *
 * Can be applied on images with pixelFormat Mono8, Mono10, Mono12 or Coord3D_C32f.
 *
 * \param[in]  input_image      Image handle.
 * \param[in]  interval         Interval with lower and upper threshold value. The Interval can be of type peak_common_interval or peak_common_interval_f.
 * \param[in]  size_of_interval The size of the interval type.
 * \param[out] output_region    Region handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_image and \p output_region must be created first.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The \p size_of_interval does not match the size of peak_common_interval,
 *                                                      nor peak_common_interval_f.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p interval is an invalid pointer.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            The \p interval is out of bounds for the pixel format.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p input_image is too big for processing.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Threshold_Process(peak_icv_image_handle input_image, c_peak_icv_variant_interval interval,
    size_t size_of_interval, peak_icv_region_handle* output_region);

/*!
 * \ingroup ids_peak_icv_c_threshold
 * \brief Queries the minimum and maximum value of a given image and provides it as an interval.
 *
 * \param[in]  image            This is the image for which the range is calculated.
 * \param[out] interval         The maximum possible range of the given image. The Interval can be of type peak_common_interval or peak_common_interval_f.
 * \param[in]  size_of_interval The size of the interval type.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p interval is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The \p size_of_interval does not match the size of peak_common_interval,
 *                                                      nor peak_common_interval_f.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Threshold_GetRange(
    peak_icv_image_handle image, peak_icv_variant_interval interval, size_t size_of_interval);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
