/*!
 * \file    peak_icv_calibration_view.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-08-30
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/types/peak_common_simple_types.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_extrinsic_parameters.h>
#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_polygon.h>

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

struct peak_icv_calibration_view;

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Holds the reprojection error for a marker point in the image.
 *
 * This quantifies the deviation of the reprojected marker from its observed image location.
 *
 * Such information helps evaluate the calibration accuracy at that specific point.
 */
typedef struct peak_icv_reprojection_error
{
    peak_common_point_f position; /*!< The detected position of the calibration marker in image coordinates. */
    peak_common_vector direction; /*!< The reprojection error vector. */
    double length;                  /*!< The magnitude (length) of the reprojection error, measured in pixels. */
    uint8_t reserved[40];           /*!< Reserved for future use. */
} peak_icv_reprojection_error;

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Represents a 3D coordinate system projected into 2D.
 *
 * It consists of an origin
 * and three vectors representing the X, Y, and Z axes.
 * These vectors describe the axes directions
 * projected from 3D to 2D.
 */
typedef struct peak_icv_coordinate_system
{
    peak_common_point_f origin; /*!< The origin position. */
    peak_common_point_f x_axis; /*!< The x axis vector. */
    peak_common_point_f y_axis; /*!< The y axis vector. */
    peak_common_point_f z_axis; /*!< The z axis vector. */
} peak_icv_coordinate_system;

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Represents a single observation of a calibration plate in an image.
 *
 * A calibration view encapsulates the data and results
 * derived from a single image
 * in which a calibration plate has been successfully detected.
 * This includes the estimated camera pose (extrinsic parameters),
 * the reprojection errors,
 * the convex hull of detected markers,
 * and the 2D projection of the plate's 3D coordinate system into the image plane.
 *
 * \since ids_peak_icv 1.0
 */
typedef struct peak_icv_calibration_view* peak_icv_calibration_view_handle;


/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Creates a calibration view handle, which can be filled using `peak_icv_Calibration_Result_GetCalibrationViews()`.
 *
 * \param[out] calibration_view_handle Calibration view handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p calibration_view_handle has already been created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_Create(peak_icv_calibration_view_handle* calibration_view_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Creates multiple calibration view handles, which can be filled using `peak_icv_Calibration_Result_GetCalibrationViews()`.
 *
 * \param[out] calibration_view_handles Array of calibration view handles.
 * \param[in]  num_calibration_views    Number of calibration views to create.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            At least one calibration view handle of \p calibration_view_handles has already been created
 *                                                      or \p num_calibration_views is zero.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_Array_Create(
    peak_icv_calibration_view_handle* calibration_view_handles, size_t num_calibration_views);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Increases the use count of the specified calibration view handle.
 *
 * In order to decrease it,
 * you need to call `peak_icv_Calibration_View_Destroy()`.
 *
 * If you copy the calibration view, you should call this method,
 * because otherwise, when one handle will be destroyed, the other will be invalid.
 *
 * \param[in] calibration_view_handle Calibration view handle (which was copied).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_IncreaseUseCount(peak_icv_calibration_view_handle calibration_view_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Destroys a calibration view handle.
 *
 * \destroyHandle{calibration view}
 *
 * \param[in] calibration_view_handle Calibration view handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_view_handle must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_Destroy(peak_icv_calibration_view_handle calibration_view_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Destroys an array of calibration views.
 *
 * \param[in] calibration_view_handles Array of calibration view handles.
 * \param[in] num_calibration_views    Number of calibration views to destroy.
 *
 * \note
 *   This function does not return early on an unexpected error
 *   and tries to destroy further elements in the array,
 *   even if one instance cannot be destroyed.
 *   In addition, this function does not set a last error
 *   (retrieved by \ref peak_icv_GetLastErrorMessage)
 *   in case an element destruction fails.
 *   The reason for this behavior is, that
 *   once the destruction of the first valid handle is started, it cannot be undone.
 *   Hence, the user wants to free as much memory as possible.
 *   When an error occurs, the first error that occurred will be returned after completing the operation.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          All calibration view handles of \p calibration_view_handles must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_Array_Destroy(
    peak_icv_calibration_view_handle* calibration_view_handles, size_t num_calibration_views);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Provides the reprojection errors for every marker in the view.
 *
 * The reprojection errors are the distances (in pixels)
 * between the detected marker points in the calibration image
 * and the corresponding projected world points,
 * computed using the estimated camera parameters.
 *
 * The function `peak_icv_Calibration_View_GetReprojectionErrors_GetCount()`
 * has to be called first to determine the number of reprojection errors.
 *
 * \param[in]  calibration_view_handle Calibration view handle.
 * \param[out] reprojection_errors     Array of reprojection errors.
 * \param[in]  num_reprojection_errors Number of reprojection errors.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_view_handle must be created first.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The buffer size is to small for the amount to existing reprojection errors.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p reprojection_errors is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetReprojectionErrors(peak_icv_calibration_view_handle calibration_view_handle,
    peak_icv_reprojection_error* reprojection_errors, size_t num_reprojection_errors);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Provides the mean reprojection error of a calibration view.
 *
 * The mean reprojection error is the root mean square of the distances (in pixels)
 * between the marker points detected in the calibration image
 * and the projected world points,
 * computed using the estimated camera parameters.
 *
 * \param[in]  calibration_view_handle Calibration view handle.
 * \param[out] mean_reprojection_error Mean reprojection error of the calibration view.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_view_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p mean_reprojection_error is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetMeanReprojectionError(
    peak_icv_calibration_view_handle calibration_view_handle, double* mean_reprojection_error);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Provides the maximum reprojection error of a calibration view.
 *
 * The returned value is the maximum distance (in pixels)
 * between marker points detected in the calibration image
 * and the corresponding projected world points,
 * computed using the estimated camera parameters.
 *
 * \param[in]  calibration_view_handle    Calibration view handle.
 * \param[out] maximum_reprojection_error Maximum reprojection error of the calibration view.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_view_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p maximum_reprojection_error is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetMaximumReprojectionError(
    peak_icv_calibration_view_handle calibration_view_handle, double* maximum_reprojection_error);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Provides the number of reprojection errors of a calibration view.
 *
 * \param[in]  calibration_view_handle Calibration view handle.
 * \param[out] num_reprojection_errors Number of reprojection errors.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_view_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_reprojection_errors is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetReprojectionErrors_GetCount(
    peak_icv_calibration_view_handle calibration_view_handle, size_t* num_reprojection_errors);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Provides the extrinsic parameters of a calibration view.
 *
 * The extrinsic parameters define the 3D transformation
 * from the calibration plate's coordinate system
 * into the camera's coordinate system.
 * This includes both rotation and translation.
 *
 * \param[in]  calibration_view_handle   Calibration view handle.
 * \param[out] extrinsic_parameters      Extrinsic parameters.
 * \param[in]  extrinsic_parameters_size Extrinsic parameters size.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_view_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p extrinsic_parameters is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The \p extrinsic_parameters_size is to small.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetExtrinsicParameters(peak_icv_calibration_view_handle calibration_view_handle,
    peak_icv_extrinsic_parameters* extrinsic_parameters, size_t extrinsic_parameters_size);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Provides the convex hull of the found calibration plate in the view.
 *
 * The convex hull is the smallest convex polygon
 * that encloses all detected marker points
 * from the calibration plate in the image.
 *
 * \param[in]  calibration_view_handle Calibration view handle.
 * \param[out] polygon_handle          The convex hull of the calibration plate, represented as a polygon.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_view_handle or polygon_handle must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetConvexHull(
    peak_icv_calibration_view_handle calibration_view_handle, peak_icv_polygon_handle* polygon_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_view
 *
 * \brief Provides the calibration plate coordinate system projected into the image.
 *
 * The coordinate system is projected using the estimated camera parameters.
 * It consists of an origin
 * and three vectors representing the X, Y, and Z axes.
 * These vectors describe the axes directions
 * projected from 3D to 2D.
 * Their lengths are twice the distance
 * between neighboring markers on the calibration plate.
 *
 * \param[in]  calibration_view_handle Calibration view handle.
 * \param[out] coordinate_system       The projected coordinate system of the calibration plate.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_view_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p coordinate_system is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetCoordinateSystem(
    peak_icv_calibration_view_handle calibration_view_handle, peak_icv_coordinate_system* coordinate_system);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
