/*!
 * \file    peak_icv_camera_calibration.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_plate.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_result.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_view.h>
#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

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
 * \brief Calculates intrinsic and extrinsic parameters.
 *
 * Processes several images
 * showing the calibration plate in different poses
 * to accurately calculate camera calibration parameters.
 *
 * The calibration process involves
 * detecting the reference points in the images
 * and matching them to their known world coordinates
 * provided by the calibration plate.
 * Using these correspondences, the method estimates the camera’s
 * intrinsic parameters (such as focal length and distortion)
 * and extrinsic parameters (position and orientation).
 *
 * \note This operation disregards any specified image regions.
 *       It processes the entire image.
 *
 * \param[in]     input_calibration_plate   Calibration plate handle which needs to be filled using
 *                                          `peak_icv_Calibration_Plate_CreateFromFile()`.
 * \param[in]     input_images              An array of images of a calibration plate in different poses.
 * \param[in]     num_input_images          Number of \p input_images.
 * \param[in,out] output_calibration_result Calibration result handle which needs to be created using
 *                                          `peak_icv_Calibration_Result_Create()`.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_calibration_plate, input_images,
 *                                                      and \p output_calibration_result must be valid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p num_input_images must be greater than 0.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The pattern of the \p input_calibration_plate is not supported
 *                                                      or the image is too big for processing.
 * \return #PEAK_ICV_STATUS_MISMATCH                The size of all images has to be equal.
 * \return #PEAK_ICV_STATUS_TARGET_NOT_FOUND        Printed markers on the given images must be detectable.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Process(peak_icv_calibration_plate_handle input_calibration_plate,
    peak_icv_image_handle* input_images, size_t num_input_images, peak_icv_calibration_result_handle* output_calibration_result);


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
