/*!
 * \file    peak_icv_workspace_calibration.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-08
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_plate.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_result.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_view.h>
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
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Calculates the camera's extrinsic parameters
 *        from a single image of a calibration plate.
 *
 * The method estimates
 * the camera's position and orientation
 * relative to the workspace coordinate system
 * and calculates the mean reprojection error
 * as a measure of calibration quality.
 *
 * \note Processes the entire image, ignoring any specified image region.
 *
 * \param[in]     calibration_plate         Calibration plate handle
 *                                          which needs to be filled using `peak_icv_Calibration_Plate_CreateFromFile()`.
 * \param[in]     intrinsic_parameters      Intrinsic parameters for undistortion.
 * \param[in]     intrinsic_parameters_size size of intrinsic parameters for undistortion.
 * \param[in]     image                     An image of a single calibration plate.
 * \param[in,out] calibration_result        Calibration result handle
 *                                          which needs to be created using `peak_icv_Calibration_Result_Create()`.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_plate, \p image, and \p calibration_result must
 *                                                      be valid.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The pattern of the \p calibration_plate is not supported
 *                                                      or the image is too big for processing.
 * \return #PEAK_ICV_STATUS_MISMATCH                The size defined in the intrinsic parameters does not match the image size.
 * \return #PEAK_ICV_STATUS_TARGET_NOT_FOUND        The calibration plate markers were not found in image.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_WorkspaceCalibration_Process(peak_icv_calibration_plate_handle calibration_plate,
    peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_image_handle image,
    peak_icv_calibration_result_handle* calibration_result);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
