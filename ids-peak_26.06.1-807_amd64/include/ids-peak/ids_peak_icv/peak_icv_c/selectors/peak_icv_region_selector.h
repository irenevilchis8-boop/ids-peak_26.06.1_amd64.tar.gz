/*!
 * \file    peak_icv_region_selector.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_region.h>

#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Counts regions where the area is within the specified range.
 *
 * Selects regions from the input set
 * where the area
 * satisfies the following condition:
 *
 * area.minimum <= area(region) <= area.maximum.
 *
 * This function only returns the count.
 * To retrieve the actual regions,
 * call `peak_icv_Region_SelectByArea()` with the same parameters.
 *
 * \param[in]  input_regions      Array of region handles.
 * \param[in]  num_input_regions  Number of input regions.
 * \param[in]  area               A structure representing an inclusive interval
 *                                with `uint32_t` lower and upper bounds.
 * \param[out] num_output_regions Number of output regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p input_regions must be created before calling this function.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_output_regions is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            \p num_input_regions must be greater than 0,
 *                                                      and \p area.minimum must be less than or equal to \p area.maximum.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_SelectByArea_GetCount(
    peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_u area, size_t* num_output_regions);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Selects regions from a set of input regions by their area.
 *
 * Only regions satisfying the following condition are selected:
 *
 * area.minimum <= area(region) <= area.maximum.
 *
 * The function `peak_icv_Region_SelectByArea_GetCount()`
 * must be called first to determine the number of output regions.
 *
 * \warning The \p output_regions must not be created first.
 *          Please instantiate the \p output_regions
 *          with #PEAK_ICV_INVALID_HANDLE within a valid container.
 *
 * \param[in]  input_regions      Array of region handles.
 * \param[in]  num_input_regions  Number of input regions.
 * \param[in]  area               A structure representing an inclusive interval
 *                                with `uint32_t` lower and upper bounds.
 * \param[out] output_regions     Array of output regions.
 * \param[in]  num_output_regions Number of output regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p input_regions and \p output_regions must be created before calling this function.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_output_regions is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            \p num_input_regions and \p num_output_regions must be greater than 0,
 *                                                      and the \p output_regions must be properly initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_SelectByArea(peak_icv_region_handle* input_regions, size_t num_input_regions,
    peak_common_interval_u area, peak_icv_region_handle* output_regions, size_t num_output_regions);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Counts regions where the center of gravity’s X-coordinate is within the specified range.
 *
 * Selects regions from the input set
 * where the X-coordinate of the center of gravity
 * satisfies the following condition:
 *
 * x.minimum <= x(center of gravity) <= x.maximum.
 *
 * This function only returns the count.
 * To retrieve the actual regions,
 * call `peak_icv_Region_SelectByCenterOfGravityX()` with the same parameters.
 *
 * \param[in]  input_regions      Array of region handles.
 * \param[in]  num_input_regions  Number of input regions.
 * \param[in]  x                  A structure representing an inclusive interval
 *                                with `float` lower and upper bounds.
 * \param[out] num_output_regions Number of output regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p input_regions must be created before calling this function.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_output_regions is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            \p num_input_regions must be greater than 0,
 *                                                      and x.minimum must be less than or equal to x.maximum.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityX_GetCount(
    peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f x, size_t* num_output_regions);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Selects regions from a set of input regions by their center of gravity X-coordinate.
 *
 * Only regions satisfying the following condition are selected:
 *
 * x.minimum <= x(center of gravity) <= x.maximum.
 *
 * The function `peak_icv_Region_SelectByCenterOfGravityX_GetCount()`
 * must be called first to determine the number of output regions.
 *
 * \warning The \p output_regions must not be created first.
 *          Please instantiate the \p output_regions
 *          with #PEAK_ICV_INVALID_HANDLE within a valid container.
 *
 * \param[in]  input_regions      Array of region handles.
 * \param[in]  num_input_regions  Number of input regions.
 * \param[in]  x                  A structure representing an inclusive interval
 *                                with `float` lower and upper bounds.
 * \param[out] output_regions     Array of output regions.
 * \param[in]  num_output_regions Number of output regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p input_regions and \p output_regions must be created before calling this function.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_output_regions is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            \p num_input_regions and \p num_output_regions must be greater than 0,
 *                                                      and the \p output_regions must be properly initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityX(peak_icv_region_handle* input_regions, size_t num_input_regions,
    peak_common_interval_f x, peak_icv_region_handle* output_regions, size_t num_output_regions);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Counts the regions where the center of gravity’s Y-coordinate is within the specified range.
 *
 * Selects regions from the input set
 * where the Y-coordinate of the center of gravity
 * satisfies the following condition:
 *
 * y.minimum <= y(center of gravity) <= y.maximum.
 *
 * This function only returns the count.
 * To retrieve the actual regions,
 * call `peak_icv_Region_SelectByCenterOfGravityY()` with the same parameters.
 *
 * \param[in]  input_regions      Array of region handles.
 * \param[in]  num_input_regions  Number of input regions.
 * \param[in]  y                  A structure representing an inclusive interval
 *                                with `float` lower and upper bounds.
 * \param[out] num_output_regions Number of output regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p input_regions must be created before calling this function.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_output_regions is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            \p num_input_regions must be greater than 0,
 *                                                      and y.minimum must be less than or equal to y.maximum.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityY_GetCount(
    peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f y, size_t* num_output_regions);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Selects regions from a set of input regions by their center of gravity Y-coordinate.
 *
 * Only regions satisfying the following condition are selected:
 *
 * y.minimum <= y(center of gravity) <= y.maximum.
 *
 * The function `peak_icv_Region_SelectByCenterOfGravityY_GetCount()`
 * must be called first to determine the number of output regions.
 *
 * \warning The \p output_regions must not be created first.
 *          Please instantiate the \p output_regions
 *          with #PEAK_ICV_INVALID_HANDLE within a valid container.
 *
 * \param[in]  input_regions      Array of region handles.
 * \param[in]  num_input_regions  Number of input regions.
 * \param[in]  y                  A structure representing an inclusive interval
 *                                with `float` lower and upper bounds.
 * \param[out] output_regions     Array of output regions.
 * \param[in]  num_output_regions Number of output regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p input_regions and \p output_regions must be created before calling this function.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_output_regions is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            \p num_input_regions and \p num_output_regions must be greater than 0,
 *                                                      and the \p output_regions must be properly initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityY(peak_icv_region_handle* input_regions, size_t num_input_regions,
    peak_common_interval_f y, peak_icv_region_handle* output_regions, size_t num_output_regions);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Counts regions where the center of gravity lies inside the specified rectangle.
 *
 * Selects regions from the input set
 * where the center of gravity
 * satisfies the following condition:
 *
 * rect.x <= x(region) <= rect.x + rect.width
 *
 * rect.y <= y(region) <= rect.y + rect.height.
 *
 * This function only returns the count.
 * To retrieve the actual regions, call `peak_icv_Region_SelectByCenterOfGravityRect()`
 * with the same parameters.
 *
 * \note Width and height can be set to zero.
 *       In this case, only the point (x, y) is considered.
 *
 * \param[in]  input_regions      Array of region handles.
 * \param[in]  num_input_regions  Number of input regions.
 * \param[in]  rect               A rectangle defined by its position (x, y) and size (width, height)
 *                                — all of type `float`.
 * \param[out] num_output_regions Number of output regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p input_regions must be created before calling this function.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_output_regions is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            \p num_input_regions must be greater than 0.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityRect_GetCount(
    peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_rectangle_f rect, size_t* num_output_regions);

/*!
 * \ingroup ids_peak_icv_c_region
 *
 * \brief Selects the regions whose center of gravity lies within the specified rectangle.
 *
 * Only regions satisfying the following condition are selected:
 *
 * rect.x <= x(region) <= rect.x + rect.width
 *
 * rect.y <= y(region) <= rect.y + rect.height.
 *
 * The function `peak_icv_Region_SelectByCenterOfGravityRect_GetCount()`
 * must be called first to determine the number of output regions.
 *
 * \note Width and height can be set to zero.
 *       In this case, only the point (x, y) is considered.
 *
 * \warning The \p output_regions must not be created first.
 *          Please instantiate the \p output_regions
 *          with #PEAK_ICV_INVALID_HANDLE within a valid container.
 *
 * \param[in]  input_regions      Array of region handles.
 * \param[in]  num_input_regions  Number of input regions.
 * \param[in]  rect               A rectangle defined by its position (x, y) and size (width, height)
 *                                — all of type `float`.
 * \param[out] output_regions     Array of output regions.
 * \param[in]  num_output_regions Number of output regions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p input_regions and \p output_regions must be created before calling this function.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p num_output_regions is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            \p num_input_regions and \p num_output_regions must be greater than 0,
 *                                                      and the \p output_regions must be properly initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityRect(peak_icv_region_handle* input_regions, size_t num_input_regions,
    peak_common_rectangle_f rect, peak_icv_region_handle* output_regions, size_t num_output_regions);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
