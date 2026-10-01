/*!
 * \file    peak_icv_undistortion.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
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
 * \defgroup ids_peak_icv_c_transformations_undistortion Undistortion
 * \ingroup ids_peak_icv_c_transformations
 *
 * Provides geometric correction
 * to remove lens distortion using intrinsic calibration parameters.
 * These parameters can be obtained using `peak_icv_Calibration_Process()`.
 *
 * Images with different binning factors than those used during calibration can also be undistorted,
 * provided that the image's capture information contains valid binning data.
 * The binning factor of the image to be undistorted must be greater than or equal to
 * the binning factor used in the calibration images.
 *
 * If the images had binning applied to it
 * and the used binning factor is stored in the image capture information
 * the following needs to hold true:<br>
 * _binning factor image * image size =
 *  binning factor in intrinsic parameters * image size in intrinsic parameters_
 *
 * If the capture information differs from that used during calibration,
 * internal parameters may be reinitialized.
 * This may cause the first undistortion call to be slower.
 * To avoid this, use `peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation()`
 * to construct the undistortion object with matching capture information.
 *
 * ### Limitations
 * - In-place undistortion is not supported.
 * - Maximum supported image size is 32767 × 32767 pixels.
 */

struct peak_icv_undistortion;
typedef struct peak_icv_undistortion* peak_icv_undistortion_handle;

/*!
 * \brief
 *     Applies undistortion to the input image.
 *
 * Removes lens distortion from the input image
 * using a configured undistortion object,
 * and writes the corrected image to the output image.
 *
 * The image region is also undistorted.
 *
 * The geometry of the output image corresponds to the new intrinsic parameters
 * returned by the undistortion object's creation function
 * (see `peak_icv_Transform_Undistortion_Create()`
 * and `peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation()`).
 *
 * \note
 *   - The input and output images must have the same size and pixel format.
 *   - Processes the entire image, ignoring any specified image region.
 *   - In-place undistortion is not supported;
 *     the input and output handles must be different.
 *   - In the rare case that the Metadata ROI is set
 *     such that the principal point of the calibration parameters lies outside the ROI,
 *     invalid data may appear at the image border.
 *     The image region is therefore restricted to points within the valid area.
 *
 * \supportedPixelformats{Undistortion}
 *
 * \param[in]  undistortion_handle
 *     Handle to the undistortion object.
 * \param[in]  input_image
 *     Image to be undistorted.
 * \param[out] output_image
 *     Undistorted image with the same pixel format and size as the input image
 *     and updated intrinsic parameters.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 *     The input image binning factor is too small
 *     for the undistortion configuration.
 * \retval #PEAK_ICV_STATUS_MISMATCH
 *     The input image size or capture information
 *     does not match the undistortion configuration.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.0
 * \ingroup ids_peak_icv_c_transformations_undistortion
 */
PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_Process(
    peak_icv_undistortion_handle undistortion_handle, peak_icv_image_handle input_image, peak_icv_image_handle output_image);

/*!
 * \brief
 *     Creates an undistortion object using intrinsic parameters.
 *
 * Initializes an undistortion object with the specified intrinsic parameters,
 * typically obtained via `peak_icv_Calibration_Process()`.
 * The function also computes new intrinsic parameters for the undistorted image.
 *
 * \param[out] undistortion_handle
 *     The created undistortion object handle.
 * \param[in]  intrinsic_parameters
 *     Intrinsic calibration parameters to configure the undistortion.
 * \param[in]  intrinsic_parameters
 *     Size of intrinsic calibration parameters.
 * \param[out] new_intrinsic_parameters
 *     Intrinsic parameters corresponding to the undistorted image.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.1
 * \ingroup ids_peak_icv_c_transformations_undistortion
 */
PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_Create(peak_icv_undistortion_handle* undistortion_handle,
    peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size,
    peak_icv_intrinsic_parameters* new_intrinsic_parameters);

/* \cond DEPRECATED */
/*!
 * \brief
 *     Creates an undistortion object using intrinsic parameters and image capture information.
 *
 * Initializes an undistortion object with the specified intrinsic parameters
 * and detailed image capture information (binning factors).
 * This allows the undistortion process to correctly handle images whose capture metadata
 * matches the provided information, avoiding runtime reinitialization overhead.
 * The function also computes new intrinsic parameters for the undistorted image.
 *
 * \remark
 *     Use this function to avoid runtime reinitialization
 *     when the capture information differs from that used during calibration.
 *
 * \attention
 *     When using this function,
 *     the images to be undistorted must have capture information
 *     that exactly matches the data provided during creation.
 *
 * \param[out] undistortion_handle
 *     The created undistortion object handle.
 * \param[in]  intrinsic_parameters
 *     Intrinsic calibration parameters to configure the undistortion.
 * \param[in]  intrinsic_parameters_size
 *     Size of intrinsic calibration parameters.
 * \param[in]  image_capture_information
 *     Metadata related to the capture process, e.g. used binning factor.
 * \param[in]  capture_information_size
 *     Size of the image capture information.
 * \param[out] new_intrinsic_parameters
 *     Intrinsic parameters corresponding to the undistorted image.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.1
 * \ingroup ids_peak_icv_c_transformations_undistortion
 */
PEAK_ICV_API_STATUS_DEPRECATED("peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation has beeen replaced by "
                                   "peak_icv_Transform_Undistortion_CreateWithImageMetadata.")
    peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation(peak_icv_undistortion_handle* undistortion_handle,
        peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size,
        peak_icv_capture_information image_capture_information, size_t capture_information_size,
        peak_icv_intrinsic_parameters* new_intrinsic_parameters);
/* \endcond */

/*!
 * \brief
 *      Creates an undistortion object configured
 *      with specific image metadata.
 *
 * Initializes an undistortion object
 * using intrinsic parameters and capture metadata (ROI and binning factors).
 * Use this function when the images to be undistorted
 * have different ROI or binning
 * than the images originally used to determine the geometric camera calibration.
 * This avoids the performance overhead of runtime reinitialization.
 *
 * \note
 *      Metadata:
 *      This function uses ROI (Keys: ROIX, ROIY, ROIWidth, ROIHeight)
 *      and binning factor (Keys: BinningFactorX BinningFactorY)
 *      of the metadata.
 *      Restrictions:
 *      - **ROI**:
 *           - Must include at least `ROIWidth` and `ROIHeight` (`ROIX` and `ROIY` default to 0).
 *           - The specified ROI must not exceed the original image size defined in the intrinsic parameters.
 *      - **Binning**:
 *           - `BinningFactorX` and `BinningFactorY` must be >= 1 and result in valid image dimensions (width and height > 0).
 *
 * \attention
 *      Images subsequently passed to the undistortion process
 *      must exactly match the metadata
 *      provided during this creation step.
 *
 * \see
 *      peak_icv_Transform_Undistortion_Create
 *      (Use this function
 *      if the image metadata is identical
 *      to the original images
 *      used for the geometric camera calibration).
 *
 * \param[out] new_intrinsic_parameters
 *      Updated \ref intrinsic_parameters.
 *      The provided metadata determines the new image size,
 *      and the camera matrix is optimized
 *      to prevent undefined pixels in the final output.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_OUT_OF_RANGE
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_transformations_undistortion
 */
PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_CreateWithImageMetadata(peak_icv_undistortion_handle* undistortion_handle,
    peak_icv_metadata_handle metadata_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size,
    peak_icv_intrinsic_parameters* new_intrinsic_parameters);

/*!
 * \brief
 *     Increases the use count of the specified undistortion handle.
 *
 * In order to decrease it,
 * you need to call `peak_icv_Transform_Undistortion_Destroy()`.
 *
 * If you copy the undistortion handle, call this method;
 * otherwise, deleting one handle invalidates the other.
 *
 * \param[in] undistortion_handle
 *     Undistortion handle to increase use count.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.0
 * \ingroup ids_peak_icv_c_transformations_undistortion
 */
PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_IncreaseUseCount(peak_icv_undistortion_handle undistortion_handle);

/*!
 * \brief
 *     Destroys an undistortion handle.
 *
 * \destroyHandle{undistortion}
 *
 * \param[in] undistortion_handle
 *     Handle to the undistortion object.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.0
 * \ingroup ids_peak_icv_c_transformations_undistortion
 */
PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_Destroy(peak_icv_undistortion_handle undistortion_handle);

/*!
 * \brief
 *     Sets the \ref peak_icv_interpolation "interpolation method" for the undistortion process.
 *
 * \param[in] undistortion_handle
 *     Handle to the undistortion object.
 * \param[in] interpolation
 *     \ref peak_icv_interpolation "Interpolation method" to use.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.0
 * \ingroup ids_peak_icv_c_transformations_undistortion
 */
PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_SetInterpolation(
    peak_icv_undistortion_handle undistortion_handle, enum peak_icv_interpolation interpolation);

/*!
 * \brief
 *     Retrieves the current interpolation method used by the undistortion.
 *
 * \param[in]  undistortion_handle
 *     Handle to the undistortion object.
 * \param[out] interpolation
 *     Pointer to store the current \ref peak_icv_interpolation "interpolation method".
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.0
 * \ingroup ids_peak_icv_c_transformations_undistortion
 */
PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_GetInterpolation(
    peak_icv_undistortion_handle undistortion_handle, enum peak_icv_interpolation* interpolation);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
