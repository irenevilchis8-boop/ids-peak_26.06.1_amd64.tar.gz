/*!
 * \file    peak_icv_calibration_parameters.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-28
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/algorithms/calibration/peak_icv_extrinsic_parameters.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_intrinsic_parameters.h>
#include <peak_icv_c/backend/peak_icv_defines.h>

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

typedef struct peak_icv_calibration_parameters_save_options
{
    uint8_t reserved[64];
} peak_icv_calibration_parameters_save_options;

/*!
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Represents the calibration parameters of a camera,
 *        including its intrinsic parameters (e.g., focal length, principal point)
 *        and extrinsic parameters (e.g., position and orientation relative to the world coordinate system).
 */
typedef struct peak_icv_calibration_parameters
{
    peak_icv_intrinsic_parameters intrinsic_parameters;
    peak_icv_extrinsic_parameters extrinsic_parameters;
} peak_icv_calibration_parameters;

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Creates and initializes calibration parameters from a JSON file.
 *
 * Allows calibration parameters to be loaded from a file,
 * avoiding the need for recalibration
 * and enabling consistent application of intrinsic and extrinsic camera parameters across sessions.
 *
 * The file may contain either calibration parameters or a full calibration result.
 * From a full calibration result, only the calibration parameters are extracted as follows:
 * - **Intrinsic parameters**:
 *   Always extracted from the calibration result.
 * - **Extrinsic parameters**:
 *   If the calibration result contains a single calibration view,
 *   the extrinsic parameters from that view are used;
 *   if multiple calibration views are present (e.g., from a camera calibration),
 *   the extrinsic parameters are set to the identity matrix.
 *
 * \param[out] calibration_parameters      Pointer to the structure where the loaded calibration parameters will be stored.
 * \param[in]  calibration_parameters_size Size of the calibration parameters structure.
 * \param[in]  file_path                   Path to the file from which the calibration parameters will be loaded.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 The operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p file_path or \p calibration_parameters is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     \p calibration_parameters_size is too small.
 * \return #PEAK_ICV_STATUS_IO_ERROR                If the given file_path does not exist,
 *                                                      or the permissions are not sufficient to read it.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_CreateFromFile(
    peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size, const char* file_path);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Saves calibration parameters to a file for later use.
 *
 * This function saves the given calibration parameters to a specified file.
 * This is useful for persisting calibration data across sessions,
 * allowing the parameters to be reloaded when needed.
 *
 * \param[in] calibration_parameters      Calibration parameters to be saved.
 * \param[in] calibration_parameters_size Size of the calibration parameters structure.
 * \param[in] file_path                   Path to the file where the calibration parameters will be saved.
 * \param[in] save_options                Reserved for future use; currently not utilized.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 The operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p file_path is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     \p calibration_parameters_size is too small.
 * \return #PEAK_ICV_STATUS_IO_ERROR                If the given file_path does not exist,
 *                                                      or the permissions are not sufficient to read it.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_SaveToFile(peak_icv_calibration_parameters calibration_parameters,
    size_t calibration_parameters_size, const char* file_path, peak_icv_calibration_parameters_save_options save_options);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 *
 * \brief Converts calibration parameters into a binary format for storage on a camera.
 *
 * This function takes calibration parameters
 * and generates a binary object
 * that includes additional metadata
 * to ensure the integrity and authenticity of the saved data.
 *
 * \param[in]  calibration_parameters             Calibration parameters to be transformed to binary format.
 * \param[in]  calibration_parameters_size        Size (in bytes) of the calibration parameters structure.
 * \param[out] calibration_parameters_binary      Pointer to the buffer where the binary calibration parameters will be stored.
 * \param[in]  calibration_parameters_binary_size Size (in bytes) of the binary calibration parameters buffer.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 The operation completed successfully.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library has not been initialized.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            \p calibration_parameters_binary is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     \p calibration_parameters_size or \p calibration_parameters_binary_size
 *                                                      is too small.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_ToBinary(peak_icv_calibration_parameters calibration_parameters,
    size_t calibration_parameters_size, uint8_t* calibration_parameters_binary, size_t calibration_parameters_binary_size);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 * \brief Retrieves the size in bytes of the binary calibration parameters
 *
 * \param[in]  calibration_parameters_size  The size of the calibration parameters.
 * \param[out] binary_size                  Pointer to a size_t that will be set to the size in bytes of the binary calibration parameters.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The parameter \p binary_size is a null pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The calibration parameter size or the binary size is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes(size_t calibration_parameters_size, size_t* binary_size);

/*!
 * \ingroup ids_peak_icv_c_calibration_result
 * \brief Constructs calibration parameters from binary data that have been read from the camera memory.
 *
 * The function validates the binary header, checks all buffer sizes, and verifies the
 * integrity of the binary payload (marker and checksum). If the binary block is larger
 * than required, the operation is still permitted as long as the header and the payload
 * are valid.
 *
 * \param[in]  binary_data                  Pointer to the binary calibration data.
 * \param[in]  binary_data_size             Size in bytes of \p binary_data.
 * \param[out] calibration_parameters       Pointer to a structure that receives the
 *                                          reconstructed calibration parameters.
 * \param[in]  calibration_parameters_size  Size in bytes of the \p calibration_parameters
 *                                          structure.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS
 *         Operation was successful.
 *
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 *         The library has not been initialized.
 *
 * \return #PEAK_ICV_STATUS_NULL_POINTER
 *         One or more required pointers are null
 *         (e.g., \p binary_data or \p calibration_parameters).
 *
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE
 *         The provided sizes are invalid. This includes:
 *         - \p binary_data_size smaller than the binary header
 *         - \p binary_data_size smaller than the required payload size
 *         - \p calibration_parameters_size too small to hold the target structure
 *
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED
 *         The binary header version is unknown or not supported.
 *
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE
 *         The binary header type does not match the calibration parameters entity type.
 *
 * \return #PEAK_ICV_STATUS_CORRUPTED
 *         The binary block is corrupted, including:
 *         - Header marker mismatch
 *         - CRC/checksum mismatch
 *
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR
 *         An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_CreateFromBinary(const uint8_t* binary_data, size_t binary_data_size,
    peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
