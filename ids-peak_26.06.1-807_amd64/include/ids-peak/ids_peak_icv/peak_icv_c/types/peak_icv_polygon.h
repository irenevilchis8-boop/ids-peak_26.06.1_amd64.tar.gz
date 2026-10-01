/*!
 * \file    peak_icv_polygon.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-01-23
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

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

struct peak_icv_polygon;
/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief peak_icv_polygon handle
 *
 * A polygon is a two-dimensional geometric shape that is made up of a finite number of straight line segments connected end-to-end to
 * form an open or closed figure. A polygon is represented by the points where the line segments meet.
 *
 * \since ids_peak_icv 1.0
 */
typedef struct peak_icv_polygon* peak_icv_polygon_handle;
/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief This is a generic type that can contain a pointer to different point types. Right now the only supported point type is peak_common_point_f.
 */
typedef void* peak_icv_point_type_variant;

/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief Creates an empty polygon
 *
 * \param[out] polygon_handle Polygon handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p polygon_handle has already been created.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The given handle \p polygon_handle is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_Create(peak_icv_polygon_handle* polygon_handle);

/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief Creates a polygon from a set of peak_common_point_f
 *
 * \param[out] polygon_handle     Polygon handle.
 * \param[in]  points             Array of peak_common_point_f.
 * \param[in]  num_points         Number of points in the array.
 * \param[in]  point_type         The point type of the given points.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The given handle \p polygon_handle is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p polygon_handle has already been created.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The \p point_type is not supported in polygon.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_CreateFromPoints(peak_icv_polygon_handle* polygon_handle, peak_icv_point_type_variant points,
    size_t num_points, enum peak_icv_point_type point_type);

/*!
 * \ingroup ids_peak_icv_c_polygon
 *
 * \brief Destroys a polygon handle.
 *
 * \destroyHandle{polygon}
 *
 * \param[in] polygon_handle Polygon handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p polygon_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_Destroy(peak_icv_polygon_handle polygon_handle);

/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief Increases the use count of the specified \p polygon_handle. In order to decrease it, you need to call
 * \ref peak_icv_Polygon_Destroy. If you copy the polygon, you should call this method, because otherwise, when one
 * handle will be destroyed, the other will be invalid.
 *
 * \param[in] polygon_handle Polygon handle (which was copied).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p polygon_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_IncreaseUseCount(peak_icv_polygon_handle polygon_handle);

/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief Provides the number of points of a polygon.
 *
 * \param[in]  polygon_handle Polygon handle.
 * \param[out] points_count     Number of points
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p polygon_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p points_count is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_GetPoints_GetCount(peak_icv_polygon_handle polygon_handle, size_t* points_count);

/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief Provides the \ref peak_icv_point_type of a polygon.
 *
 * \param[in]  polygon_handle Polygon handle.
 * \param[out] point_type     Type of point.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p polygon_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p point_type is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_GetPointType(peak_icv_polygon_handle polygon_handle, enum peak_icv_point_type* point_type);

/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief Checks if a polygon is closed. A closed polygon contains the same point as first and last point.
 *
 * \param[in]  polygon_handle Polygon handle.
 * \param[out] is_closed      True if closed, False if open.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                     Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR              An unexpected internal error occurred.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE              The \p polygon_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER                \p is_closed is an invalid pointer.
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_IsClosed(peak_icv_polygon_handle polygon_handle, bool* is_closed);

/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief Provides the size of a polygon in bytes. The size depends on the peak_icv_point_type of the given polygon.
 * Different peak_icv_point_type use different amounts of memory.
 *
 * \param[in]  polygon_handle    Point cloud handle.
 * \param[out] byte_size_points Size of point cloud points in bytes
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                     Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR              An unexpected internal error occurred.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE              The \p polygon_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER                \p byte_size_points is an invalid pointer.
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_GetPoints_GetSizeInBytes(peak_icv_polygon_handle polygon_handle, size_t* byte_size_points);

/*!
 * \ingroup ids_peak_icv_c_polygon
 * \brief Provides the points of a polygon.
 * To calculate the byte size use the function peak_icv_Polygon_GetPoints_GetSizeInBytes.
 *
 * The following example shows how points can be retrieved from a polygon:
 * \code
 * size_t size = 0;
 * peak_icv_Polygon_GetPoints_GetSizeInBytes(my_polygon, &size);
 * peak_common_point_f* points = (peak_common_point_f*) malloc(size);
 * peak_icv_Polygon_GetPoints(my_polygon, points, size);
 * \endcode
 *
 * \param[in]  polygon_handle           Polygon handle.
 * \param[out] points                   Array of points of the polygon.
 * \param[in]  byte_size_points    Size of point cloud points in bytes
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p polygon_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p points is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The Value of \p byte_size_coordinates has to be greater than zero
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The Number of points in the polygon exceeds provided number of points.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Polygon_GetPoints(
    peak_icv_polygon_handle polygon_handle, peak_icv_point_type_variant points, size_t byte_size_points);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
