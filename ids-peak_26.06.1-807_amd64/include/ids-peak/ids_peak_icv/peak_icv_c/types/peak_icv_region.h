/*!
 * \file    peak_icv_region.h
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

#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stdbool.h>
#    include <stddef.h>
#    include <stdint.h>
#endif

struct peak_icv_region;

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief peak_icv_region handle
 *
 * A region consists of a set of points. A point is an integer coordinate in a 2D plane, that can also be negative.
 *
 * \see \ref concept_type_region
 *
 * \since ids_peak_icv 1.0
 */
typedef struct peak_icv_region* peak_icv_region_handle;

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Creates an empty region
 *
 * \param[out] region_handle Region handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The given handle \p region_handle already exists.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Create(peak_icv_region_handle* region_handle);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Creates a region from a set of points
 *
 * \param[out] region_handle Region handle.
 * \param[in]  points        Array of points.
 * \param[in]  num_points    Number of points in the array.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The given handle \p region_handle is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The given handle \p region_handle already exists.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p points is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_CreateFromPoints(
    peak_icv_region_handle* region_handle, peak_common_point* points, size_t num_points);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Creates a region from a rectangle
 *
 * \param[out] region_handle
 * \param[in]  rect
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The given handle \p region_handle is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The given handle \p region_handle already exists.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_CreateFromRectangle(peak_icv_region_handle* region_handle, peak_common_rectangle rect);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Increases the use count of the specified region_handle.
 *
 * In order to decrease it, you need to call \ref peak_icv_Region_Destroy.
 * If you copy the region, you should call this method,
 * because otherwise, when one handle will be destroyed, the other will be invalid.
 *
 * \param[in] region_handle Region handle (which was copied).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p region_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_IncreaseUseCount(peak_icv_region_handle region_handle);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Destroys a region handle.
 *
 * \destroyHandle{region}
 *
 * \param[in] region_handle Region handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p region_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Destroy(peak_icv_region_handle region_handle);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Creates an array of empty regions.
 *
 * \param[out] region_handles     Array of region handles.
 * \param[in]  num_region_handles Number of regions to create.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The given pointer \p region_handles is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            A region handle of \p region_handles has already been created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Array_Create(peak_icv_region_handle* region_handles, size_t num_region_handles);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Destroys an array of regions.
 *
 * \param[in] region_handles     Array of region handles.
 * \param[in] num_region_handles Number of regions to destroy.
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
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          All region handles of \p region_handles must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Array_Destroy(peak_icv_region_handle* region_handles, size_t num_region_handles);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Provides the number of connected components of a region.
 *
 * \param[in]  input_region         Region handle.
 * \param[out] output_regions_count Count of connected components.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p output_regions_count is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_GetConnectedComponents_GetCount(
    peak_icv_region_handle input_region, size_t* output_regions_count);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Provides the connected components of a region as a region array.
 *
 * The 8-neighborhood is used to determine the components.
 *
 * \see \ref concept_region_connected-components
 *
 * \param[in]  input_region         Region handle.
 * \param[out] output_regions       Region array handle.
 * \param[in]  region_handles_count Count of connected components.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region and all \p output_regions must be created first.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            If the number of connected components exceeds provided number of handles.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_GetConnectedComponents(
    peak_icv_region_handle input_region, peak_icv_region_handle* output_regions, size_t region_handles_count);


/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Provides the area of a region. The area is the number of pixels in the region.
 *
 * \param[in]  input_region Region handle.
 * \param[out] area         Area of the region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p area is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_GetArea(peak_icv_region_handle input_region, size_t* area);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Provides the center of gravity of a region as a floating point.
 *
 * \param[in]  input_region      Region handle.
 * \param[out] center_of_gravity Center of gravity of the region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p center_of_gravity is an invalid pointer.
 * \return #PEAK_ICV_STATUS_MATH_ERROR              The center of gravity could not be computed.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_GetCenterOfGravity(
    peak_icv_region_handle input_region, peak_common_point_f* center_of_gravity);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Provides the number of points/pixels of a region.
 *
 * \param[in]  input_region Region handle.
 * \param[out] points_count Number of points/pixels of the region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p points_count is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_GetPoints_GetCount(peak_icv_region_handle input_region, size_t* points_count);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Provides the points/pixels of a region.
 *
 * The function \p peak_icv_Region_GetPoints_GetCount has to be called first to determine the number of points/pixels.
 *
 * \param[in]  input_region Region handle.
 * \param[out] points       Array of points/pixels of the region.
 * \param[in]  num_points   Number of points/pixels of the region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p points is an invalid pointer.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            The \p num_points is too small.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_GetPoints(peak_icv_region_handle input_region, peak_common_point* points, size_t num_points);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Computes the difference between two regions.
 *
 * \param[in]  input_region_minuend     Region handle.
 * \param[in]  input_region_subtrahend  Region handle for region to be subtracted from input_region_minuend.
 * \param[out] output_region_difference Region handle for difference between the two regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region_minuend, input_region_subtrahend and output_region_difference must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Difference(peak_icv_region_handle input_region_minuend,
    peak_icv_region_handle input_region_subtrahend, peak_icv_region_handle* output_region_difference);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Computes the intersection of two regions.
 *
 * \param[in]  input_region_1             Region handle.
 * \param[in]  input_region_2             Region handle.
 * \param[out] output_region_intersection Region handle for the intersection of the two regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region_1, input_region_2 and output_region_intersection must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Intersection(
    peak_icv_region_handle input_region_1, peak_icv_region_handle input_region_2, peak_icv_region_handle* output_region_intersection);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Computes the union of two regions.
 *
 * \param[in]  input_region_1       Region handle.
 * \param[in]  input_region_2       Region handle.
 * \param[out] output_region_united Region handle for the union of the two regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region_1, \p input_region_2 and \p output_region_united must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Union(
    peak_icv_region_handle input_region_1, peak_icv_region_handle input_region_2, peak_icv_region_handle* output_region_united);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Computes the dilation of the input region with the given structuring element.
 *
 * The reference point of the structuring element is at (0, 0).
 *
 * \param[in]  input_region              Region handle.
 * \param[in]  input_structuring_element Region handle.
 * \param[out] output_region_dilation    Region handle for the dilated region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region, \p input_structuring_element and \p output_region_dilation must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Dilation(peak_icv_region_handle input_region,
    peak_icv_region_handle input_structuring_element, peak_icv_region_handle* output_region_dilation);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Computes the erosion of the input region with the given structuring element.
 *
 * The reference point of the structuring element is at (0, 0).
 *
 * \param[in]  input_region              Region handle.
 * \param[in]  input_structuring_element Region handle.
 * \param[out] output_region_erosion     Region handle for the eroded region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region, \p input_structuring_element and \p output_region_erosion must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Erosion(peak_icv_region_handle input_region, peak_icv_region_handle input_structuring_element,
    peak_icv_region_handle* output_region_erosion);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Compares the region in \p region_handle_lhs to the region in \p region_handle_rhs
 *        and stores the result in is_equal.
 *
 * \param[in]  region_handle_lhs Region to compare.
 * \param[in]  region_handle_rhs Region to compare.
 * \param[out] is_equal          Comparison Result.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p region_handle_lhs and \p region_handle_rhs must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p is_equal is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Compare(
    peak_icv_region_handle region_handle_lhs, peak_icv_region_handle region_handle_rhs, bool* is_equal);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Scales the region in \p input_region_handle from the \p input_size to the \p output_size
 *        using the \p interpolation method
 *        and stores the result in \p output_region_handle.
 *
 * The \p input_size typically refers to the dimensions of the original image
 * from which the region was derived (e.g. during segmentation).
 * This is the coordinate space in which the region was initially defined.
 *
 * The \p output_size represents the dimensions of the target image
 * where the region will be mapped or rendered after scaling or transformation.
 *
 * Ensure that any coordinate or size transformations account for the difference
 * between input and output dimensions to maintain spatial consistency.
 *
 * \param[in]  input_region_handle  Region to scale.
 * \param[in]  input_size           The size based on the original image.
 * \param[in]  output_size          The size of a corresponding image to which the original region is scaled.
 * \param[in]  interpolation        The interpolation method used to scale the image.
 * \param[out] output_region_handle The handle to the scaled region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_region_handle and \p output_region_handle must be created first.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The given \p input_size parameter is too small for the given \p input_region_handle or the given \p output_size is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_Scale(peak_icv_region_handle input_region_handle, peak_common_size input_size,
    peak_common_size output_size, peak_icv_interpolation interpolation, peak_icv_region_handle* output_region_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
