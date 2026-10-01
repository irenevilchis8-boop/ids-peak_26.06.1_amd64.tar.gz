/*!
 * \file    peak_icv_calibration_result.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_parameters.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_view.h>
#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif


struct peak_icv_calibration_result;

typedef struct peak_icv_calibration_result_save_options
{
    uint8_t reserved[64];
} peak_icv_calibration_result_save_options;

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Represents the results of a camera calibration.
 *
 * This handle refers to a calibration result containing
 * intrinsic and extrinsic parameters,
 * the mean reprojection error,
 * and a collection of calibration views,
 * each representing marker positions
 * and corresponding reprojection errors in the image.
 *
 * \since ids_peak_icv 1.0
 */
typedef struct peak_icv_calibration_result* peak_icv_calibration_result_handle;


/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Creates a calibration result handle, which can be filled using \ref peak_icv_Calibration_Process.
 *
 * \param[out] calibration_result_handle Calibration result handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p calibration_result_handle has already been created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_Create(peak_icv_calibration_result_handle* calibration_result_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Saves a calibration result to a JSON file for later use.
 *
 * This function serializes the given calibration result and writes it to the specified file
 * in JSON format. The file can later be loaded to restore the calibration result.
 *
 * \param[in] calibration_result_handle Calibration result handle.
 * \param[in] file_path                 An existing file path to save calibration result.
 * \param[in] save_options              Not used.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_result_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p file_path is a null pointer.
 * \return #PEAK_ICV_STATUS_IO_ERROR                Indicates that the file could not be written due to an I/O error,
 *                                                      such as missing permissions or path not existing.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_SaveToFile(peak_icv_calibration_result_handle calibration_result_handle,
    const char* file_path, peak_icv_calibration_result_save_options save_options);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Loads a calibration result from a JSON file.
 *
 * This function parses the specified JSON file and initializes a calibration result handle
 * with the data it contains. The file must be in the format produced by the corresponding
 * save function.
 *
 * \param[in,out] calibration_result_handle Calibration result handle.
 * \param[in]     file_path                 An existing file path to load calibration result.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_result_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p file_path is a null pointer.
 * \return #PEAK_ICV_STATUS_IO_ERROR                Indicates that the file could not be read due to an I/O error, such as missing permissions or non-existent file.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_CreateFromFile(
    peak_icv_calibration_result_handle* calibration_result_handle, const char* file_path);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Destroys a calibration result handle.
 *
 * \destroyHandle{calibration result}
 *
 * \param[in] calibration_result_handle Calibration result handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_result_handle must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_Destroy(peak_icv_calibration_result_handle calibration_result_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Increases the use count of the specified calibration result handle.
 *
 * In order to decrease it,
 * you need to call \ref peak_icv_Calibration_Result_Destroy.
 *
 * If you copy the calibration result, you should call this method,
 * because otherwise, when one handle will be destroyed, the other will be invalid.
 *
 * \param[in] calibration_result_handle Calibration result handle (which was copied).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_IncreaseUseCount(peak_icv_calibration_result_handle calibration_result_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Gets the mean reprojection error from a calibration result.
 *
 * This function retrieves the mean reprojection error,
 * which represents the root mean square distance between
 * detected marker points in the image and the projected world points,
 * measured in pixels.
 *
 * \param[in]  calibration_result_handle Calibration result handle.
 * \param[out] mean_reprojection_error   Mean reprojection error value.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_result_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p mean_reprojection_error is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_GetMeanReprojectionError(
    peak_icv_calibration_result_handle calibration_result_handle, double* mean_reprojection_error);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Gets the number of calibration views of a calibration result.
 *
 * \param[in]  calibration_result_handle    Calibration result handle.
 * \param[out] calibration_view_count       Number of calibration views.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_result_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p calibration_view_count is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_GetCalibrationViews_GetCount(
    peak_icv_calibration_result_handle calibration_result_handle, size_t* calibration_view_count);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Gets the calibration views from a calibration result.
 *
 * This function retrieves the calibration views stored in the result.
 * Each view contains marker positions and reprojection errors
 * for one input image used during calibration.
 *
 * The number of available views must first be obtained using
 * `peak_icv_Calibration_Result_GetCalibrationViews_GetCount()`.
 *
 * The order of the returned views corresponds to the order of images
 * provided to \ref peak_icv_Calibration_Process.
 *
 * \param[in]  calibration_result_handle Calibration result handle.
 * \param[out] calibration_views         Array of calibration views of the calibration result.
 * \param[in]  calibration_views_count   Number of calibration views of the calibration result.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_result_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p calibration_views is an invalid pointer.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            The \p calibration_views_count is too small.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_GetCalibrationViews(peak_icv_calibration_result_handle calibration_result_handle,
    peak_icv_calibration_view_handle* calibration_views, size_t calibration_views_count);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Extracts the calibration parameters from a calibration result.
 *
 * This function extracts the calibration parameters required for image operations
 * such as point cloud generation, image undistortion, and other calibration-dependent tasks.
 * The extracted parameters include intrinsic parameters and,
 * depending on the number of calibration views, extrinsic parameters.
 *
 * - Intrinsic parameters are always extracted from the calibration result.
 * - If the calibration result contains exactly one calibration view,
 *   the extrinsic parameters are taken from that view.
 * - If multiple calibration views are present (e.g., from a full camera calibration),
 *   the extrinsic parameters are set to the identity matrix.
 *
 * To use extrinsic parameters from a specific calibration view rather than the identity matrix,
 * retrieve the desired view using `peak_icv_Calibration_Result_GetCalibrationViews()`
 * and incorporate its parameters accordingly.
 *
 * The extracted calibration parameters can be stored in the persistent memory of the camera, allowing
 * them to be loaded later via the IDS peak genericAPI API. Alternatively, they can be saved to a file using
 * `peak_icv_CalibrationParameters_SaveToFile()`.
 *
 * \param[in]  calibration_result_handle  Handle to the calibration result.
 * \param[out] calibration_parameters     Pointer to the structure that will be populated with the calibration parameters.
 * \param[in] calibration_parameters_size The size of the calibration parameters.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 The operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_result_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p calibration_parameters is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Result_ToParameters(peak_icv_calibration_result_handle calibration_result_handle,
    peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
