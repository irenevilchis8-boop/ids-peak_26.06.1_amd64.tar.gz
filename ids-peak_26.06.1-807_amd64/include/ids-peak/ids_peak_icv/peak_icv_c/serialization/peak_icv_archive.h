/*!
 * \file    peak_icv_archive.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-19
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
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

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Structure representing a key-value store archive.
 */
struct peak_icv_archive;

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Handle for archive operations.
 */
typedef struct peak_icv_archive* peak_icv_archive_handle;

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Enumeration of archive value types.
 */
enum peak_icv_archive_value_type
{
    PEAK_ICV_ARCHIVE_VALUE_TYPE_BOOL,         /**< Boolean type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_BOOL_ARRAY,   /**< Boolean array type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_INT,          /**< Integer type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_INT_ARRAY,    /**< Integer array type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_DOUBLE,       /**< Double type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_DOUBLE_ARRAY, /**< Double array type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_STRING,       /**< String type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_STRING_ARRAY, /**< String array type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_ARCHIVE,      /**< Nested archive type */
    PEAK_ICV_ARCHIVE_VALUE_TYPE_ARCHIVE_ARRAY /**< Nested archive array type */
};

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Alias for the archive value type enumeration.
 */
typedef int32_t peak_icv_archive_value_type_t;

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Creates a new archive.
 *
 * \param[out] archive_handle A pointer to a peak_icv_archive_handle that will be initialized.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The given handle \p archive_handle already exists.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_Create(peak_icv_archive_handle* archive_handle);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Creates an archive from a string.
 *
 * \param[out] archive_handle Pointer to the archive handle created from the data.
 * \param[in]  data_type      The type of the given data.
 * \param[in]  data           The string data to be deserialized.

 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p deserializer_handle or \p archive_handle does not exist, it must be created
 first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data is invalid.
 * \return #PEAK_ICV_STATUS_CORRUPTED               The string with parameter \p data is not deserializable.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_CreateFromString(
    peak_icv_archive_handle* archive_handle, peak_icv_serialization_type data_type, const char* data);

/**
 * \ingroup ids_peak_icv_c_archive
 *
 * \brief Destroys an archive handle.
 *
 * \destroyHandle{archive}
 *
 * \param[in] archive_handle The archive handle to destroy.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_Destroy(peak_icv_archive_handle archive_handle);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Checks if a key exists in the archive.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key to check.
 * \param[out] has_key        Pointer to a uint8_t that will be set to true if the key exists, false otherwise.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            If \p key or \p has_key is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_HasKey(peak_icv_archive_handle archive_handle, const char* key, bool* has_key);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves the count of keys stored in the archive.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[out] count          Pointer to a size_t that will be set to the number of keys.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p count is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetKeys_GetCount(peak_icv_archive_handle archive_handle, size_t* count);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves the size in bytes of a key element at the specified index.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  index          The index of the key element.
 * \param[out] size           Pointer to a size_t that will be set to the size in bytes of the key.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p size is invalid.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            The parameter \p index is out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetKeysElement_GetSizeInBytes(
    peak_icv_archive_handle archive_handle, size_t index, size_t* size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves a key element from the archive at the specified index.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  index          The index of the key element.
 * \param[out] data           Buffer where the key will be copied.
 * \param[in]  size           The size of the buffer (number of elements).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            The parameter \p index is out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetKeysElement(peak_icv_archive_handle archive_handle, size_t index, char* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves the value type of given key in the archive.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key whose value type is sought.
 * \param[out] type           Pointer to a variable to store the value type.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p key or \p type is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetValueType(
    peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_value_type_t* type);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves the count of elements in an array stored at a given key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key of the array.
 * \param[out] count          Pointer to a size_t that will be set to the number of elements.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p key or \p count is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetArray_GetCount(peak_icv_archive_handle archive_handle, const char* key, size_t* count);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves an integer value stored at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key associated with the integer value.
 * \param[out] value         Pointer to an int64_t that will store the retrieved integer.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p key or \p value is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetInt(peak_icv_archive_handle archive_handle, const char* key, int64_t* value);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores an integer value in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the integer value.
 * \param[in] value          The integer value to set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The supplied \p key is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetInt(peak_icv_archive_handle archive_handle, const char* key, int64_t value);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves an array of integers stored at the specified key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key of the integer array.
 * \param[out] data           Buffer to store the integer array.
 * \param[in]  size           The size of the buffer (number of elements).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            If \p key, \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_CORRUPTED               If the specified \p key does not exist.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetIntArray(
    peak_icv_archive_handle archive_handle, const char* key, int64_t* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores an array of integers in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the integer array.
 * \param[in] data           The array of integers to store.
 * \param[in] size           The number of elements in the integer array.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetIntArray(
    peak_icv_archive_handle archive_handle, const char* key, const int64_t* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves a double value stored at the specified key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key associated with the double value.
 * \param[out] value          Pointer to a double that will store the retrieved value.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p value is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetDouble(peak_icv_archive_handle archive_handle, const char* key, double* value);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores a double value in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the double value.
 * \param[in] value          The double value to set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The supplied \p key is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetDouble(peak_icv_archive_handle archive_handle, const char* key, double value);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves an array of doubles stored at the specified key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key of the double array.
 * \param[out] data           Buffer to store the double array.
 * \param[in]  size           The size of the buffer (number of elements).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            If \p key, \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_CORRUPTED               If the specified \p key does not exist.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetDoubleArray(
    peak_icv_archive_handle archive_handle, const char* key, double* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores an array of doubles in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the double array.
 * \param[in] data           The array of doubles to store.
 * \param[in] size           The number of elements in the double array.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetDoubleArray(
    peak_icv_archive_handle archive_handle, const char* key, const double* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves a boolean value stored at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key associated with the boolean value.
 * \param[out] value         Pointer to an uint8_t that will store the retrieved boolean value.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p value is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetBool(peak_icv_archive_handle archive_handle, const char* key, bool* value);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores a boolean value in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the boolean value.
 * \param[in] value          The boolean value to set (non-zero for true, zero for false).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The supplied \p key is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetBool(peak_icv_archive_handle archive_handle, const char* key, bool value);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves an array of booleans stored at the specified key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key of the boolean array.
 * \param[out] data           Buffer to store the boolean array.
 * \param[in]  size           The size of the buffer (number of elements).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            If \p key, \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_CORRUPTED               If the specified \p key does not exist.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetBoolArray(peak_icv_archive_handle archive_handle, const char* key, bool* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores an array of booleans in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the boolean array.
 * \param[in] data           The array of booleans to store.
 * \param[in] size           The number of elements in the boolean array.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetBoolArray(
    peak_icv_archive_handle archive_handle, const char* key, const bool* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves the size in bytes of the string stored at the specified key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key associated with the string.
 * \param[out] size           Pointer to a size_t that will be set to the size in bytes needed to store the string.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetString_GetSizeInBytes(
    peak_icv_archive_handle archive_handle, const char* key, size_t* size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves a string from the archive.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key associated with the string.
 * \param[out] data           Buffer to store the retrieved string.
 * \param[in]  size           The size of the buffer (number of elements).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p value is invalid.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetString(peak_icv_archive_handle archive_handle, const char* key, char* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores a string in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the string.
 * \param[in] data           The string to store.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The supplied \p key or \p data is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetString(peak_icv_archive_handle archive_handle, const char* key, const char* data);

/**
 *\ingroup ids_peak_icv_c_archive
 * \brief Retrieves the size in bytes of an element in a string array stored at the specified key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key associated with the string array.
 * \param[in]  index          The index of the string element.
 * \param[out] size           Pointer to a size_t that will be set to the size in bytes of the string element.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p size is invalid,
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            The parameter \p index is out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetStringArrayElement_GetSizeInBytes(
    peak_icv_archive_handle archive_handle, const char* key, size_t index, size_t* size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves an element from a string array stored in the archive.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key of the string array.
 * \param[in]  index          The index of the string element in the array.
 * \param[out] data           Buffer to store the retrieved string element.
 * \param[in]  size           The size of the buffer (number of elements).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE            The parameter \p index is out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetStringArrayElement(
    peak_icv_archive_handle archive_handle, const char* key, size_t index, char* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores an array of strings in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the string array.
 * \param[in] data           Array of strings to store.
 * \param[in] size           The number of strings in the array.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetStringArray(
    peak_icv_archive_handle archive_handle, const char* key, const char* const* data, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves a nested archive stored at the specified key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key associated with the nested archive.
 * \param[out] sub_archive    Pointer to a variable to hold the retrieved nested archive handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p value is invalid.
 * \return #PEAK_ICV_STATUS_CORRUPTED               If \p key was not found.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetArchive(
    peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle* sub_archive);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores a nested archive in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the nested archive.
 * \param[in] sub_archive    The nested archive handle to store.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p value is invalid.
 * \return #PEAK_ICV_STATUS_CORRUPTED               If \p key was not found.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            If \p key is empty.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetArchive(
    peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle sub_archive);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves an array of nested archives stored at the specified key.
 *
 * \param[in]  archive_handle The archive handle.
 * \param[in]  key            The key associated with the nested archive array.
 * \param[out] sub_archives   Buffer to store the nested archive handles.
 * \param[in]  size           The size of the buffer (number of elements).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_GetArchiveArray(
    peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle* sub_archives, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Stores an array of nested archives in the archive at the specified key.
 *
 * \param[in] archive_handle The archive handle.
 * \param[in] key            The key for the nested archive array.
 * \param[in] sub_archives   Array of nested archive handles to store.
 * \param[in] size           The number of elements in the nested archive array.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p archive_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data or \p size is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_SetArchiveArray(
    peak_icv_archive_handle archive_handle, const char* key, const peak_icv_archive_handle* sub_archives, size_t size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves the size in bytes of the archive string produced by the serializer.
 *
 * \param[in]  archive_handle   The archive handle.
 * \param[in]  type             The format of the resulting string
 * \param[out] size             Pointer to store the size of the archive string.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The parameter \p handle is invalid.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p size is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_ToString_GetSizeInBytes(
    peak_icv_archive_handle archive_handle, peak_icv_serialization_type type, size_t* size);

/**
 * \ingroup ids_peak_icv_c_archive
 * \brief Retrieves the archive string produced by the serializer.
 *
 * \param[in]      archive_handle    The archive handle.
 * \param[in]      type              The format of the resulting string
 * \param[in]      data              Buffer to store the archive string.
 * \param[in, out] size              Pointer to store the size of the archive string.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The parameter \p handle is invalid.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p data is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Archive_ToString(
    peak_icv_archive_handle archive_handle, peak_icv_serialization_type type, char* data, size_t* size);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
