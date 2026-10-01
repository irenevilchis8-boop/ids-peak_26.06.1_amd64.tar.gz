/*!
 * \file    peak_icv_metadata.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-05-22
 * \since   1.4
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
#    include <stdbool.h>
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
struct peak_icv_metadata;

/*!
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
typedef struct peak_icv_metadata* peak_icv_metadata_handle;

/*!
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
enum peak_icv_metadata_value_type
{
    PEAK_ICV_METADATA_VALUE_TYPE_BOOL,
    PEAK_ICV_METADATA_VALUE_TYPE_BOOL_ARRAY,
    PEAK_ICV_METADATA_VALUE_TYPE_INT,
    PEAK_ICV_METADATA_VALUE_TYPE_INT_ARRAY,
    PEAK_ICV_METADATA_VALUE_TYPE_DOUBLE,
    PEAK_ICV_METADATA_VALUE_TYPE_DOUBLE_ARRAY,
    PEAK_ICV_METADATA_VALUE_TYPE_STRING,
    PEAK_ICV_METADATA_VALUE_TYPE_STRING_ARRAY,
    PEAK_ICV_METADATA_VALUE_TYPE_UINT = 10,
    PEAK_ICV_METADATA_VALUE_TYPE_UINT_ARRAY = 11
};

/*!
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata

 */
typedef int32_t peak_icv_metadata_value_type_t;

/*!
 * \param[out] handle
 *     Must be uninitialized.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_Create(peak_icv_metadata_handle* handle);

/*!
 * \brief
 *     Destroys a metadata handle.
 *
 * \destroyHandle{metadata}
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_Destroy(peak_icv_metadata_handle handle);

/*!
 * \param[in] key
 *      Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetInt(peak_icv_metadata_handle handle, const char* key, int64_t* value);


/*!
 * \param[in] key
 *      Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetInt(peak_icv_metadata_handle handle, const char* key, int64_t value);

/*!
 * \param[in] key
 *     Name of the key (must be an existing non-empty string).
 * \param[in] count
 *     Number of elements in the \p values array
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_CORRUPTED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetIntArray(peak_icv_metadata_handle handle, const char* key, int64_t* values, size_t count);

/*!
 * \param[in] key
 *     Name of the key (must be a non-empty string).
 * \param[in] count
 *     The number of elements in the \p values array.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetIntArray(
    peak_icv_metadata_handle handle, const char* key, const int64_t* values, size_t count);

/*!
 * \param[in] key
 *      Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetUInt(peak_icv_metadata_handle handle, const char* key, uint64_t* value);

/*!
 * \param[in] key
 *      Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetUInt(peak_icv_metadata_handle handle, const char* key, uint64_t value);

/*!
 * \param[in] key
 *     Name of the key (must be an existing non-empty string).
 * \param[in] count
 *     Number of elements in the \p values array
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_CORRUPTED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetUIntArray(
    peak_icv_metadata_handle handle, const char* key, uint64_t* values, size_t count);

/*!
 * \param[in] key
 *     Name of the key (must be a non-empty string).
 * \param[in] count
 *     The number of elements in the \p values array.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetUIntArray(
    peak_icv_metadata_handle handle, const char* key, const uint64_t* values, size_t count);


/*!
 * \param[in] key
 *      Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetDouble(peak_icv_metadata_handle handle, const char* key, double* value);


/*!
 * \param[in] key
 *      Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetDouble(peak_icv_metadata_handle handle, const char* key, double value);

/*!
 * \param[in] key
 *     Name of the key (must be an existing non-empty string).
 * \param[in] count
 *     Number of elements in the \p values array
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_CORRUPTED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetDoubleArray(
    peak_icv_metadata_handle handle, const char* key, double* values, size_t count);

/*!
 * \param[in] key
 *     Name of the key (must be a non-empty string).
 * \param[in] count
 *     The number of elements in the \p values array.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetDoubleArray(
    peak_icv_metadata_handle handle, const char* key, const double* values, size_t count);

/*!
 * \param[in] key
 *      Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetBool(peak_icv_metadata_handle handle, const char* key, bool* value);


/*!
 * \param[in] key
 *      Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetBool(peak_icv_metadata_handle handle, const char* key, bool value);

/*!
 * \param[in] key
 *     Name of the key (must be an existing non-empty string).
 * \param[in] count
 *     Number of elements in the \p values array
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_CORRUPTED
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetBoolArray(peak_icv_metadata_handle handle, const char* key, bool* values, size_t count);

/*!
 * \param[in] key
 *     Name of the key (must be a non-empty string).
 * \param[in] count
 *     The number of elements in the \p values array.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetBoolArray(
    peak_icv_metadata_handle handle, const char* key, const bool* values, size_t count);

/*!
 * \param[in] key
 *     Name of the key (must be an existing non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetString_GetSizeInBytes(peak_icv_metadata_handle handle, const char* key, size_t* size);

/*!
 * \param[in] key
 *      Name of the key (must be an existing non-empty string).
 * \param[out] buffer
 *     Preallocated buffer with the size returned by \ref peak_icv_Metadata_GetString_GetSizeInBytes.
 * \param[in] size
 *     Size in bytes of the preallocated buffer.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetString(peak_icv_metadata_handle handle, const char* key, char* buffer, size_t size);

/*!
 * \param[in] key
 *     Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetString(peak_icv_metadata_handle handle, const char* key, const char* buffer);

/*!
 * \param[in] key
 *     Name of the key (must be an existing non-empty string).
 * \param[in] index
 *     The index of the array element.
 *     The number of elements in the array can be received using \ref peak_icv_Metadata_GetArray_GetCount.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_OUT_OF_RANGE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes(
    peak_icv_metadata_handle handle, const char* key, size_t index, size_t* size);

/*!
 *
 * \param[in] key
 *     Name of the key (must be an existing non-empty string).
 * \param[in] index
 *     The index of the array element.
 *     The number of elements in the array can be received using \ref peak_icv_Metadata_GetArray_GetCount.
 * \param[out] buffer
 *     Preallocated buffer with the size returned by \ref peak_icv_Metadata_GetString_GetSizeInBytes.
 * \param[in] size
 *     Size in bytes of the preallocated buffer.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_OUT_OF_RANGE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetStringArrayElement(
    peak_icv_metadata_handle handle, const char* key, size_t index, char* buffer, size_t size);

/*!
 * \param[in] key
 *     Name of the key (must be a non-empty string).
 * \param[out] buffers
 *     Preallocated array of buffers.
 * \param[in] count
 *     The number of elements in the \p buffers array.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_SetStringArray(
    peak_icv_metadata_handle handle, const char* key, const char* const* buffers, size_t count);

/*!
 * \param[in] key
 *     Name of the key (must be a non-empty string).
 * \param[out] count
 *     Pointer to a variable that receives the number of elements in the array.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetArray_GetCount(peak_icv_metadata_handle handle, const char* key, size_t* count);

/*!
 * \param[in] key
 *     Name of the key (must be a non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_HasKey(peak_icv_metadata_handle handle, const char* key, bool* has_key);

/*!
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetEntryCount(peak_icv_metadata_handle handle, size_t* count);

/*!
 * \param[in] index
 *     The index of the array element.
 *     The number of elements in the array can be received using \ref peak_icv_Metadata_GetArray_GetCount.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_OUT_OF_RANGE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetKey_GetSizeInBytes(peak_icv_metadata_handle handle, size_t index, size_t* size);

/*!
 * \param[in] index
 *     The index of the array element.
 *     The number of elements in the array can be received using \ref peak_icv_Metadata_GetArray_GetCount.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_OUT_OF_RANGE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetKey(peak_icv_metadata_handle handle, size_t index, char* buffer, size_t size);

/*!
 * \param[in] key
 *     Name of the key (must be an existing non-empty string).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_metadata
 */
PEAK_ICV_API_STATUS peak_icv_Metadata_GetValueType(
    peak_icv_metadata_handle handle, const char* key, peak_icv_metadata_value_type_t* type);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
