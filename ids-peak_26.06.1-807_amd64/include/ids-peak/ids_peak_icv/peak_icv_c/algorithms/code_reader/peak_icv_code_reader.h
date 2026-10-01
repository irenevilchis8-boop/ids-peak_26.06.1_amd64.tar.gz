/*!
 * \file    peak_icv_code_reader.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-12-22
 * \since   1.2
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

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

struct peak_icv_code_reader_result;

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Code Reader result representation
 *        holding the information about a code that was found upon detection including the decoded data.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
using peak_icv_code_reader_result_handle = peak_icv_code_reader_result*;

struct peak_icv_code_reader;

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Code Reader representation
 *        central unit needed for code detection and decoding.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
using peak_icv_code_reader_handle = peak_icv_code_reader*;

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Code Reader types
 *        Optional, but can be set to limit the code types that can be found,
 *        as well queried from a code detection result.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
enum peak_icv_code_type
{
    /*!
     * \brief A Data Matrix code is a two-dimensional code, that may store numeric data or characters.
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    DataMatrix = 0x01
};

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Creates a Code Reader result handle.
 *
 * \param[out] result Code Reader result handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p result has already been created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_Create(peak_icv_code_reader_result_handle* result);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Creates an array of empty code reader results.
 *
 * \param[out] result Array of result handles.
 * \param[in]  count  Number of results to create.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The given pointer \p result is an invalid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            A result handle of \p result has already been created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_Array_Create(peak_icv_code_reader_result_handle* result, size_t count);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Destroys a code reader result handle.
 *
 * \destroyHandle{code reader result}
 *
 * \param[in] result Code Reader result handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p result must be created first by \ref peak_icv_BarcodeReaderResult_Create
 *                                                      or peak_icv_BarcodeReaderResult_Array_Create.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_Destroy(peak_icv_code_reader_result_handle result);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 * \brief Retrieves the size in bytes of the decoded text from a barcode reader result
 *
 * \param[in]  result             The handle to the barcode reader result, from that the text will be queried.
 * \param[out] text_size_in_bytes Pointer to a size_t that will be set to the size in bytes of the decoded text.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p result must be created first by \ref peak_icv_BarcodeReaderResult_Create
 *                                                      or peak_icv_BarcodeReaderResult_Array_Create.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p text_size_in_bytes is a null pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes(
    peak_icv_code_reader_result_handle result, size_t* text_size_in_bytes);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 * \brief Retrieves the decoded text from a barcode reader result
 *
 * \param[in]  result             The handle to the barcode reader result, from that the text will be queried.
 * \param[out] text               The decoded text.
 * \param[out] text_size_in_bytes Size in bytes of the decoded data.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p result must be created first by \ref peak_icv_BarcodeReaderResult_Create
 *                                                      or peak_icv_BarcodeReaderResult_Array_Create.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p text_size_in_bytes is a null pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The \p text_size_in_bytes is too small for the data that would be provided in
 *                                                       \p text. Query the size with \ref
 *                                                      peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_GetText(
    peak_icv_code_reader_result_handle result, char* text, size_t text_size_in_bytes);
/*!
 * \ingroup ids_peak_icv_c_code_reader
 * \brief Retrieves the decoded text from a barcode reader result
 *
 * \param[in]  result    The handle to the barcode reader result, from that the text will be queried.
 * \param[out] code_type The type of the code that was found and decoded.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p result must be created first by \ref peak_icv_BarcodeReaderResult_Create
 *                                                      or peak_icv_BarcodeReaderResult_Array_Create.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p code_type is a null pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_GetType(
    peak_icv_code_reader_result_handle result, peak_icv_code_type* code_type);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Creates a Code Reader handle.
 *
 * Allocates and initializes a new Code Reader instance. The handle is required
 * to configure code types and to run detection/decoding on input images.
 *
 * \param[out] handle Code Reader handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE The \p handle has already been created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReader_Create(peak_icv_code_reader_handle* handle);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Destroys a code reader handle.
 *
 * \destroyHandle{code Reader}
 *
 * \param[in] handle Code Reader handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE The \p handle must be created first by
 *         \ref peak_icv_BarcodeReader_Create.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReader_Destroy(peak_icv_code_reader_handle handle);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Retrieves the number of configured code types.
 *
 * When no explicit code types are set via \ref peak_icv_BarcodeReader_SetCodeTypes,
 * the implementation-defined default set is active.
 *
 * \param[in]  handle Code Reader handle.
 * \param[out] count  The number of code types that can be retrieved with
 *                    \ref peak_icv_BarcodeReader_GetCodeTypes.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE The \p handle must be created first by
 *         \ref peak_icv_BarcodeReader_Create.
 * \return #PEAK_ICV_STATUS_NULL_POINTER The parameter \p count is a null pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReader_GetCodeTypesGetCount(peak_icv_code_reader_handle handle, size_t* count);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Retrieves the configured code types.
 *
 * Copies up to \p count entries into \p barcode_types. Use
 * \ref peak_icv_BarcodeReader_GetCodeTypesGetCount to query the required size.
 *
 * \param[in]  handle         Code Reader handle.
 * \param[out] barcode_types  Destination array for the configured code types.
 * \param[in]  count          Capacity of \p barcode_types in number of entries.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE The \p handle must be created first by
 *         \ref peak_icv_BarcodeReader_Create.
 * \return #PEAK_ICV_STATUS_NULL_POINTER The parameter \p barcode_types is a null pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE The \p count is too small to hold all
 *         configured code types. Query the required count with
 *         \ref peak_icv_BarcodeReader_GetCodeTypesGetCount.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReader_GetCodeTypes(
    peak_icv_code_reader_handle handle, peak_icv_code_type* barcode_types, size_t count);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Sets the allowed code types for detection and decoding.
 *
 * Restricts the Code Reader to the provided list of \ref peak_icv_barcode_type values.
 *
 * \param[in] handle         Code Reader handle.
 * \param[in] barcode_types  Array with the code types to enable
 * \param[in] count          Number of entries in \p barcode_types.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE The \p handle must be created first by
 *         \ref peak_icv_BarcodeReader_Create.
 * \return #PEAK_ICV_STATUS_NULL_POINTER The parameter \p barcode_types is a null pointer
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReader_SetCodeTypes(
    peak_icv_code_reader_handle handle, peak_icv_code_type* barcode_types, size_t count);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Detects and decodes codes in an input image.
 *
 * Attempts to find codes of the configured types in \p input_image and decodes their payload.
 * The function writes up to \p result_count results into the array \p result.
 *
 * Typical usage:
 *  1) Call \ref peak_icv_BarcodeReaderResult_Array_Create to allocate \p result with a capacity.
 *  2) Call this function.
 *  3) Inspect results via \ref peak_icv_BarcodeReaderResult_GetText and
 *     \ref peak_icv_BarcodeReaderResult_GetType.
 *
 * \param[in]  handle       Code Reader handle.
 * \param[in]  input_image  Input image handle to search for codes.
 * \param[out] result       Array of result handles to receive detection/decoding outcomes.
 * \param[in]  result_count Number of elements available in \p result.
 * \param[out] found_count  The number of codes that were found
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE The \p handle and/or \p input_image must be valid.
 * \return #PEAK_ICV_STATUS_NULL_POINTER Any of \p result or \p found_count is a null pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE The \p result_count is too small, while more codes were found.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReader_DetectAndDecode(peak_icv_code_reader_handle handle, peak_icv_image_handle input_image,
    peak_icv_code_reader_result_handle* result, size_t result_count, size_t* found_count);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Sets the maximum number of codes to detect per call.
 *
 * Limits how many codes the detector will return for a single invocation of
 * \ref peak_icv_BarcodeReader_DetectAndDecode. This can be used to cap runtime
 * and memory usage in scenarios with many codes present.
 *
 * \param[in] handle    Code Reader handle.
 * \param[in] max_count Maximum number of codes to detect and return
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE The \p handle must be created first by
 *         \ref peak_icv_BarcodeReader_Create.
 * \return #PEAK_ICV_STATUS_MISMATCH The \p max_count exceeds internal limits.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect(peak_icv_code_reader_handle handle, size_t max_count);

/*!
 * \ingroup ids_peak_icv_c_code_reader
 *
 * \brief Retrieves the maximum number of codes to detect per call.
 *
 * Returns the current limit configured via
 * \ref peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect.
 *
 * \param[in]  handle    Code Reader handle.
 * \param[out] max_count The currently configured maximum number of codes to detect per call.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE The \p handle must be created first by
 *         \ref peak_icv_BarcodeReader_Create.
 * \return #PEAK_ICV_STATUS_NULL_POINTER The parameter \p max_count is a null pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
PEAK_ICV_API_STATUS peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect(peak_icv_code_reader_handle handle, size_t* max_count);


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
