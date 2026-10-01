/*!
 * \file    peak_icv_painter.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/painting/peak_icv_color.h>
#include <peak_icv_c/types/peak_icv_region.h>

#ifdef __cplusplus

#    include <peak_icv_c/types/peak_icv_image.h>
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Draws the \p input_region onto the \p image. Only region points inside of the image are painted. Region points
 * outside of the image are ignored. In case of an empty region, the image is not modified and the function returns
 * #PEAK_ICV_STATUS_SUCCESS.
 *
 * \param[in,out] image          This is the input image as well as the output image, where the region is drawn.
 * \param[in]     input_region   Handle of the region, that should be drawn.
 * \param[in]     drawing_options Parameters for visualization.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The image must have a size of atleast 1 by 1 pixel.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image or \p input_region must be created first.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            The \p drawing_options opacity is out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Draw(
    peak_icv_image_handle image, peak_icv_region_handle input_region, peak_icv_drawing_options drawing_options);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
