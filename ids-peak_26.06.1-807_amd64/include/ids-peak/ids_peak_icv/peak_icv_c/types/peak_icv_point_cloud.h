/*!
 * \file    peak_icv_point_cloud.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-01-16
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

struct peak_icv_pointcloud;

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Generic pointer type representing either `peak_icv_point_xyz` or `peak_icv_point_xyzi`.
 *
 * \since ids_peak_icv 1.0
 */
typedef void* peak_icv_point_xyz_variant;

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Handle to a point cloud.
 *
 * \since ids_peak_icv 1.0
 */
typedef struct peak_icv_pointcloud* peak_icv_point_cloud_handle;

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Creates an empty point cloud.
 *
 * \param[out] point_cloud_handle Pointer to receive the created point cloud handle.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle is an invalid pointer.
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE            \p point_cloud_handle already exists.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_Create(peak_icv_point_cloud_handle* point_cloud_handle);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Creates a point cloud from the specified XYZ image.
 *
 * \details To create a XYZ image from a depth map see `peak_icv_Transform_DepthMap_To_XYZImage()`.
 *
 * \param[out] point_cloud_handle Pointer to receive the created point cloud handle.
 * \param[in]  xyz_image_handle   Image containing x, y, and z coordinates per pixel.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          One of the parameters is an invalid handle
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE            \p point_cloud_handle already exists.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromXYZImage(
    peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Creates a point cloud from the specified XYZ image and overlay image.
 *
 * To create a XYZ image from a depth map see \ref peak_icv_Transform_DepthMap_To_XYZImage
 *
 * \note The region of the overlay image is disregarded.
 *
 * \param[out] point_cloud_handle     Pointer to a variable that will store the handle to the created point cloud.
 * \param[in]  xyz_image_handle       Image containing x, y, and z coordinates per pixel.
 * \param[in]  overlay_image_handle   Image containing overlay (intensity or rgb) values per pixel.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          One of the parameters is an invalid handle
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE            \p point_cloud_handle already exists.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage(peak_icv_point_cloud_handle* point_cloud_handle,
    peak_icv_image_handle xyz_image_handle, peak_icv_image_handle overlay_image_handle);


/* \cond DEPRECATED */
/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Creates a point cloud from the specified XYZ image and intensity image.
 *
 * To create a XYZ image from a depth map see \ref peak_icv_Transform_DepthMap_To_XYZImage
 *
 * \note The region of the intensity image is disregarded.
 *
 * \param[out] point_cloud_handle     Pointer to a variable that will store the handle to the created point cloud.
 * \param[in]  xyz_image_handle       Image containing x, y, and z coordinates per pixel.
 * \param[in]  intensity_image_handle Image containing intensity values per pixel.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          One of the parameters is an invalid handle
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE            \p point_cloud_handle already exists.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS_DEPRECATED("peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage has beeen replaced by "
                                   "peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage.")
    peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage(peak_icv_point_cloud_handle* point_cloud_handle,
        peak_icv_image_handle xyz_image_handle, peak_icv_image_handle intensity_image_handle);
/* \endcond */

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Loads a point cloud from the specified file.
 *
 * The file format is determined by the file extension.
 *
 * Supported file formats (with required file extensions):
 * - PLY (.ply) – Polygon File Format
 *
 * \note The handle is implicitly created during loading;
 *       explicit allocation is not required.
 *
 * \param[out] point_cloud_handle Pointer to receive the created point cloud handle.
 * \param[in]  point_type         Point type of the data in the file.
 * \param[in]  file_path          Path to the point cloud file, encoded in UTF-8.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          One of the parameters is an invalid handle.
 * \retval #PEAK_ICV_STATUS_CORRUPTED               The file could not be read due to an invalid format of the file.
 * \retval #PEAK_ICV_STATUS_IO_ERROR                If the given file_path does not exist, or the permissions are not sufficient.
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE            \p point_cloud_handle already exists.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromFile(
    peak_icv_point_cloud_handle* point_cloud_handle, enum peak_icv_point_type point_type, const char* file_path);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Creates a point cloud from the specified list of points.
 *
 * \param[out] point_cloud_handle Pointer to receive the created point cloud handle.
 * \param[in]  points             Array of points.
 * \param[in]  num_points         Number of points in the array.
 * \param[in]  point_type         Type of the points in the array.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle is an invalid pointer.
 * \retval #PEAK_ICV_STATUS_NULL_POINTER            \p points is an invalid pointer.
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE            \p point_cloud_handle already exists.
 * \retval #PEAK_ICV_STATUS_NOT_SUPPORTED           The given \p point_type is not supported
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromPoints(peak_icv_point_cloud_handle* point_cloud_handle,
    peak_icv_point_xyz_variant points, size_t num_points, enum peak_icv_point_type point_type);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Increases the reference count of the point cloud handle.
 *
 * In order to decrease it,
 * you need to call `peak_icv_PointCloud_Destroy()`.
 *
 * If you copy the point cloud, call this method;
 * otherwise, deleting one handle invalidates the other.
 *
 * \param[in] point_cloud_handle Point Cloud handle (which was copied).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle does not exist.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_IncreaseUseCount(peak_icv_point_cloud_handle point_cloud_handle);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Destroys a point cloud handle.
 *
 * \destroyHandle{point cloud}
 *
 * \param[in] point_cloud_handle Point cloud handle to destroy.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle does not exist.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_Destroy(peak_icv_point_cloud_handle point_cloud_handle);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Retrieves the point type of a point cloud.
 *
 * \param[in]  point_cloud_handle Point cloud handle.
 * \param[out] point_type         Pointer to receive the point type.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle does not exist.
 * \retval #PEAK_ICV_STATUS_NULL_POINTER            \p point_type is an invalid pointer.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_GetType(
    peak_icv_point_cloud_handle point_cloud_handle, enum peak_icv_point_type* point_type);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 * \brief Provides the number of points of a point cloud.
 *
 * \param[in]  point_cloud_handle Point cloud handle.
 * \param[out] num_points         Pointer to receive the number of points.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle does not exist.
 * \retval #PEAK_ICV_STATUS_NULL_POINTER            \p num_points is an invalid pointer.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_GetPoints_GetCount(peak_icv_point_cloud_handle point_cloud_handle, size_t* num_points);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Retrieves the size in bytes of the points data in a point cloud.
 *
 * \param[in]  point_cloud_handle Point cloud handle.
 * \param[out] byte_size_points   Pointer to receive the size in bytes.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle does not exist.
 * \retval #PEAK_ICV_STATUS_NULL_POINTER            \p byte_size_points is an invalid pointer.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_GetPoints_GetSizeInBytes(
    peak_icv_point_cloud_handle point_cloud_handle, size_t* byte_size_points);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Retrieves the points of a point cloud.
 *
 * The points buffer must be allocated by the caller
 * with a size obtained from `peak_icv_PointCloud_GetPoints_GetSizeInBytes()`.
 *
 * The following example shows how points can be retrieved from a point cloud:
 * \snippet{trimleft} point_cloud.cpp point_cloud_get_points_c
 *
 * \param[in]  point_cloud_handle Point cloud handle.
 * \param[out] points             Buffer to receive points.
 * \param[in]  byte_size_points   Size of the buffer in bytes.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle does not exist.
 * \retval #PEAK_ICV_STATUS_NULL_POINTER            \p points is an invalid pointer.
 * \retval #PEAK_ICV_STATUS_OUT_OF_RANGE            \p byte_size_points is smaller than required.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_GetPoints(
    peak_icv_point_cloud_handle point_cloud_handle, peak_icv_point_xyz_variant points, size_t byte_size_points);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Saves the specified point cloud to a PLY file.
 *
 * The file format is determined
 * by the specified file extension of the file name.
 * Only binary PLY (.ply) is supported.
 *
 * If no extension is provided, `.ply` is appended automatically.
 *
 * \note If a point cloud does not contain any points it cannot be written to file.
 *
 * \param[in] point_cloud_handle The point cloud to save.
 * \param[in] file_path          The path of the file to write to, as a UTF-8 encoded string.
 * \param[in] save_options       Currently unused but reserved for future use,
 *                               allowing for potential expansion
 *                               or additional functionality
 *                               in subsequent iterations of the software.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          \p point_cloud_handle does not exist.
 * \retval #PEAK_ICV_STATUS_IO_ERROR                The \p `file_path` is invalid or lacks write permissions.
 * \retval #PEAK_ICV_STATUS_NOT_SUPPORTED           The point type is not supported or the point cloud is empty.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_SaveToFile(
    peak_icv_point_cloud_handle point_cloud_handle, const char* file_path, peak_icv_point_cloud_save_options save_options);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Transforms a point cloud using a 3D transformation matrix.
 *
 * Applies a 4x4 transformation matrix to the input point cloud.
 * The transformation may include translation, rotation, or scaling.
 *
 * \param[in]  input_point_cloud  Handle to the point cloud to transform.
 * \param[in]  matrix_3d          3D transformation matrix.
 * \param[out] output_point_cloud Handle to the output point cloud.
 *                                The handle has to be created before the function call.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_point_cloud or \p output_point_cloud handle is invalid or uninitialized.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_Transform(peak_icv_point_cloud_handle input_point_cloud,
    peak_icv_transformation_matrix_3d matrix_3d, peak_icv_point_cloud_handle* output_point_cloud);

/*!
 * \ingroup ids_peak_icv_c_pointcloud
 *
 * \brief Transforms a point cloud to the workspace coordinate system using the extrinsic parameters.
 *
 * Applies the inverse of the specified extrinsic parameters
 * to transform the point cloud from camera to workspace coordinates.
 *
 * \param[in]  input_point_cloud         Handle to the point cloud to transform.
 * \param[in]  extrinsic_parameters      Extrinsic parameters of the workspace calibration.
 * \param[in]  extrinsic_parameters_size Size of the extrinsic parameters..
 * \param[out] output_point_cloud        Handle to the output point cloud.
 *                                       The handle has to be created before the function call.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_point_cloud or \p output_point_cloud handle is invalid or uninitialized.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_PointCloud_TransformToWorkspace(peak_icv_point_cloud_handle input_point_cloud,
    peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size,
    peak_icv_point_cloud_handle* output_point_cloud);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
