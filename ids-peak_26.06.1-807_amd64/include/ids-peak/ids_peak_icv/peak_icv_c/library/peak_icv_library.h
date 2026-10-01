/*!
 * \file    peak_icv_library.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
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
 * \ingroup ids_peak_icv_c_library
 *
 * \brief Initialize the IDS peak ICV library
 *
 * This function must be called prior to any other function call,
 * otherwise no IDS peak ICV function is operable.
 *
 * The function may be called multiple times from a single client process,
 * but note that for each call there has to be a corresponding call to #peak_icv_Exit
 * when closing the library.
 *
 * \note Calling any other function before #peak_icv_Init
 *       will result in an #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                    Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_DYNAMIC_DEPENDENCY_MISSING A dynamic dependency is missing. Query the last error with
 *                                                         \ref peak_icv_GetLastErrorMessage for more information.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR             An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Init(void);

/*!
 * \ingroup ids_peak_icv_c_library
 *
 * \brief Deinitializes the IDS peak ICV library
 *
 * This function should be called when no function of the library is needed anymore.
 * It releases all allocated memory
 * and destroys all handles along with their associated resources.
 *
 * Calls to #peak_icv_Init and #peak_icv_Exit are reference counted,
 * so you have to call #peak_icv_Exit as many times as you have called #peak_icv_Init.
 *
 * After the library has been deinitialized,
 * its functions (except for #peak_icv_Init) will not be operable
 * until #peak_icv_Init is called again.
 *
 * \note Calling any other function (except #peak_icv_Init) after calling #peak_icv_Exit
 *       will result in an #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Exit(void);

/*!
 * \ingroup ids_peak_icv_c_library
 *
 * \brief Provides the version of the library
 *        separated into major, minor, subminor and patch,
 *        in decreasing order of significance.
 *
 * Each component represents a different level of change or compatibility.
 *
 * You are allowed to pass NULL for parts you are not interested in.
 *
 * \note This function can be used even if the library is not initialized.
 *
 * \param[out] major_version    Major Version. NULL if not required.
 * \param[out] minor_version    Minor Version. NULL if not required.
 * \param[out] subminor_version Subminor Version. NULL if not required.
 * \param[out] patch_version    Patch Version. NULL if not required.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS Operation was successful; no error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_GetVersion(
    uint32_t* major_version, uint32_t* minor_version, uint32_t* subminor_version, uint32_t* patch_version);

/*!
 * \ingroup ids_peak_icv_c_library
 *
 * \brief Queries the size for the string in #peak_icv_GetLastErrorMessage.
 *
 * \param[out] last_error_message_size resulting size for the string in #peak_icv_GetLastErrorMessage.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS        Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_NULL_POINTER   The \p lastErrorMessageSize is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_GetLastErrorMessage_GetCount(size_t* last_error_message_size);

/*!
 * \ingroup ids_peak_icv_c_library
 *
 * \brief Queries the last error in the current thread.
 *
 * Returns a human-readable text description of the last error
 * that occurred in the local thread context.
 * The library maintains thread-local error information,
 * meaning each thread stores its own last error independently.
 *
 * If a library function fails and returns an error status,
 * this function can be used to retrieve a textual description
 * providing details about the error.
 *
 * Note that the last error persists until it is overwritten.
 * If an error occurs and subsequent function calls succeed,
 * this function will still return the original error,
 * ignoring the successful calls.
 *
 * If no error has occurred in the current thread
 * since the library was initialized,
 * the function returns #PEAK_ICV_STATUS_SUCCESS,
 * and \p lastErrorMessage will contain an empty string.
 *
 * If #peak_icv_GetLastErrorMessage itself encounters an error,
 * it will return the appropriate error code,
 * but will not overwrite the stored last error.
 * This ensures that future calls can still retrieve the original error.
 *
 * For more information and a guide on how to use the function
 * see \ref principle_last_error_handling.
 *
 * \note This function can be used even if the library is not initialized.
 *       This is useful in the case that \ref peak_icv_Init fails.
 *
 * \param[out] last_error_message      Pointer to a user allocated C string buffer to receive the last error text.
 * \param[in]  last_error_message_size Size of the provided \p lastErrorMessage in bytes.
 *                                     See #peak_icv_GetLastErrorMessage_GetCount
 *
 * \return #PEAK_ICV_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE the value of \p lastErrorMessageSize is too small to receive the expected amount of data.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR      An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_GetLastErrorMessage(char* last_error_message, size_t last_error_message_size);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
