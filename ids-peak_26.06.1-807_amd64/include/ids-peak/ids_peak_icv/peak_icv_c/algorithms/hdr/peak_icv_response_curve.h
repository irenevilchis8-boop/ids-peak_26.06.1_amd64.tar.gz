/*!
 * \file    peak_icv_response_curve.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-04-14
 * \since   ids_peak_icv 1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>

#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
struct peak_icv_hdr_response_curve;

/*!
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
typedef struct peak_icv_hdr_response_curve* peak_icv_hdr_response_curve_handle;

/*!
 * The created handle has to be freed using peak_icv_HDR_ResponseCurve_Destroy().
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_Create(peak_icv_hdr_response_curve_handle* response_curve_handle);

/*!
 * Must be freed later using peak_icv_HDR_ResponseCurve_Destroy().
 *
 * \param[in] file_path
 *     Path to an existing response curve JSON file.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_IO_ERROR
 * \retval #PEAK_ICV_STATUS_CORRUPTED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_CreateFromFile(
    peak_icv_hdr_response_curve_handle* response_curve_handle, const char* file_path);

/*!
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_IncreaseUseCount(peak_icv_hdr_response_curve_handle response_curve_handle);

/*!
 * \brief Destroys a response curve handle.
 *
 * \destroyHandle{response curve}
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_Destroy(peak_icv_hdr_response_curve_handle response_curve_handle);

/*!
 * \param[in] file_path
 *     Destination file path for the response curve JSON file.
 *     The .json file extension is automatically added if not provided.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_IO_ERROR
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_SaveToFile(
    peak_icv_hdr_response_curve_handle response_curve_handle, const char* file_path);

/*!
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_Compare(peak_icv_hdr_response_curve_handle response_curve_handle_lhs,
    peak_icv_hdr_response_curve_handle response_curve_handle_rhs, bool* is_equal);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
