/*!
 * \file    peak_icv_calibration_plate.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-08-30
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

struct peak_icv_calibration_plate;

/*!
 * \ingroup ids_peak_icv_c_calibration_plate
 *
 * \brief Calibration plate representation
 *        holding the world coordinates of the reference points on a calibration plate.
 *
 * These coordinates are essential for accurate camera calibration.
 *
 * \see Guide \ref guide_calibration for more information about the calibration process.
 *
 * \since ids_peak_icv 1.0
 */
typedef struct peak_icv_calibration_plate* peak_icv_calibration_plate_handle;

/*!
 * \ingroup ids_peak_icv_c_calibration_plate
 *
 * \brief Creates a calibration plate handle.
 *
 * \param[out] calibration_plate_handle Calibration plate handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p calibration_plate_handle has already been created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Plate_Create(peak_icv_calibration_plate_handle* calibration_plate_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_plate
 *
 * \brief Creates and initializes a calibration plate handle
 *        by loading world coordinates from a description file.
 *
 * The description file contains the world coordinates of the reference points
 * on a specific calibration plate.
 *
 * Ensure that the description file corresponds to the physical calibration plate
 * used in the setup.
 *
 * \param[in,out] calibration_plate_handle Calibration plate handle.
 * \param[in]     file_path                An existing file path to a calibration plate JSON file.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_plate_handle must be created first by \ref peak_icv_Calibration_Plate_Create.
 * \return #PEAK_ICV_STATUS_IO_ERROR                Indicates that the file could not be read due to an I/O error, such as missing permissions or non-existent file.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p file_path is a null pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Plate_CreateFromFile(
    peak_icv_calibration_plate_handle* calibration_plate_handle, const char* file_path);

/*!
 * \ingroup ids_peak_icv_c_calibration_plate
 *
 * \brief Increases the use count of the specified calibration plate handle.
 *
 * In order to decrease it,
 * you need to call \ref peak_icv_Calibration_Plate_Destroy.
 *
 * If you copy the calibration plate, you should call this method,
 * because otherwise, when one handle will be destroyed, the other will be invalid.
 *
 * \param[in] calibration_plate_handle Calibration plate handle (which was copied).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Plate_IncreaseUseCount(peak_icv_calibration_plate_handle calibration_plate_handle);

/*!
 * \ingroup ids_peak_icv_c_calibration_plate
 *
 * \brief Destroys a calibration plate handle.
 *
 * \destroyHandle{calibration plate}
 *
 * \param[in] calibration_plate_handle Calibration plate handle.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p calibration_plate_handle must be created first by \ref peak_icv_Calibration_Plate_Create.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Plate_Destroy(peak_icv_calibration_plate_handle calibration_plate_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
