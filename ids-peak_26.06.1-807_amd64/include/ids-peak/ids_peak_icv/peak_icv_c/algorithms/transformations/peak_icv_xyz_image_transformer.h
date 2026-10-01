/*!
 * \file    peak_icv_xyz_image_transformer.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-05-03
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/algorithms/calibration/peak_icv_camera_calibration.h>
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
 * \ingroup ids_peak_icv_c_transformation
 *
 * \brief Transforms an undistorted depth map with radial coordinates
 *        to a three-channel image with Cartesian coordinates.
 *
 * Transforms an image of pixel format `Coord3D_C32f` with radial coordinates
 * into a three-channel image,
 * where each channel encodes the Cartesian `x`, `y`, and `z` coordinates of a 3D point.
 *
 * The input image must represent an undistorted depth map,
 * where each pixel encodes the radial distance
 * from the camera origin to a 3D point
 * in a spherical coordinate system.
 *
 * Images with different binning factors than those used during calibration can also be transformed,
 * provided that the image's capture information contains valid binning data.
 * The binning factor of the input image
 * must be greater than or equal to
 * the binning factor used in the calibration images.
 *
 * If the images had binning applied to it
 * and the used binning factor is stored in the image capture information
 * the following needs to hold true:<br>
 * _binning factor image * image size =
 *  binning factor in intrinsic parameters * image size in intrinsic parameters_
 *
 * \param[out] xyz_image_handle          Handle to the output image that will store the transformed Cartesian coordinates.
 * \param[in]  intrinsic_parameters      Intrinsic parameters from the workspace calibration.
 * \param[in]  intrinsic_parameters_size Size of intrinsic parameters.
 * \param[in]  depth_map_handle          Handle to the input depth map image.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_MISMATCH                The image sizes of the depth map and the resulting XYZ image
 *                                                      must match the size specified in the intrinsic parameters.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          One or more provided handles are invalid.
 * \retval #PEAK_ICV_STATUS_NOT_SUPPORTED           The pixel format is not supported.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_Transform_DepthMap_To_XYZImage(peak_icv_image_handle xyz_image_handle,
    peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_image_handle depth_map_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
