/*!
 * \file    peak_icv_binary_validator.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-11-28
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/binary/peak_icv_binary_header.h>

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \ingroup ids_peak_icv_c_binary
 * \brief Validates a binary data structure received from a camera.
 *
 * This function checks the integrity of a binary data structure received from a camera, such as binary calibration parameters
 * (\p peak_icv_calibration_parameters_binary). All supported binary structures have the suffix "_binary".
 *
 * The validation process includes verifying the marker and the CRC32 checksum in the binary header to ensure
 * the data's authenticity and integrity.
 *
 * \param[in]  binary          Pointer to the binary data structure received from the camera.
 * \param[in]  binary_size     Size (in bytes) of the binary data structure.
 * \param[out] is_valid        Pointer to a boolean that will be set to \c true if the binary is valid, or \c false otherwise.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS             The binary was successfully validated.
 * \return #PEAK_ICV_STATUS_NULL_POINTER        The \p binary or \p is_valid pointer is invalid
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE The given \p binary_size is smaller the binary header.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR      An unexpected internal error occurred during validation.
 *
 * \note Ensure that \p binary and \p is_valid point to valid memory. The binary data must be properly formatted and
 *       include a valid header with a marker and CRC32 checksum for successful validation.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_ValidateBinary(const uint8_t* binary, size_t binary_size, bool* is_valid);


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
