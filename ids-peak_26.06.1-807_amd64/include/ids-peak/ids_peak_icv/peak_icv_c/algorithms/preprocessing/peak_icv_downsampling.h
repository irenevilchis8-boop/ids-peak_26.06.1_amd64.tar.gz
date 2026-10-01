/*!
 * \file    peak_icv_downsampling.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup ids_peak_icv_c_preprocessing_downsampling Downsampling
 * \ingroup ids_peak_icv_c_preprocessing
 *
 * Downsampling is used to decrease the image size. There are two methods to downsample the image:
 *
 * - _Binning_ is a technique to reduce image resolution by typically _summarizing_ or _averaging_ a certain
 *   number of pixels in rows, columns, or both columns and rows.
 * - _Decimation_ is a technique to reduce image resolution by skipping a certain number of pixels in rows, columns,
 *   or both columns and rows.
 *
 * \since ids_peak_icv 1.0
 */
struct peak_icv_downsampling;
typedef struct peak_icv_downsampling* peak_icv_downsampling_handle;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Downsampling mode for image preprocessing.
 *
 * The following downsample modes are supported:
 *
 * \since ids_peak_icv 1.0
 */
typedef enum peak_icv_downsampling_mode
{
    //! The averaged pixel values are computed during downsampling.
    PEAK_ICV_BINNING_AVERAGE = 0,

    //! The pixel values are summed during downsampling.
    PEAK_ICV_BINNING_SUM = 1,

    //! Only one pixel is used. Other pixels are skipped.
    PEAK_ICV_DECIMATION = 2
} peak_icv_downsampling_mode;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Creates a downsampling object from factors and mode.
 *
 * The factors given in \p factor specify the number of pixels to be aggregated in the row and column directions.
 *
 * The \p mode must be one of the values defined in the \ref peak_icv_downsampling_mode enumeration.
 *
 * \param[out] downsampling_handle  Handle for the downsampling object.
 * \param[in]  factor               Factors for downsampling.
 * \param[in]  mode                 Downsampling mode.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE             One or both factors are out of range.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED            The given downsampling mode is not supported.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_Create(
    peak_icv_downsampling_handle* downsampling_handle, peak_icv_downsampling_factor factor, peak_icv_downsampling_mode mode);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Destroys a downsampling handle.
 *
 * \destroyHandle{downsampling)
 *
 * \param[in] downsampling_handle Downsampling handle to destroy.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The downsampling_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_Destroy(peak_icv_downsampling_handle downsampling_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Set factors.
 *
 * The factors given in \p factor specify the number of pixels to be aggregated in the row and column directions.
 *
 * \param[out] downsampling_handle  Handle for the downsampling object.
 * \param[in]  factor               Factors for downsampling.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE             Factors are out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_SetFactor(
    peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_factor factor);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Get factors.
 *
 * The factors given in \p factor specify the number of pixels to be aggregated in the row and column directions.
 *
 * \param[in] downsampling_handle  Handle for the downsampling object.
 * \param[out] factor              Factors for downsampling.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_GetFactor(
    peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_factor* factor);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Returns the valid range for downsampling factors.
 *
 * Provides the minimum and maximum values that are accepted by the downsampling functions.
 *
 * \param[in] downsampling_handle  Handle for the downsampling object.
 * \param[out] range               Valid range for downsampling factors.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_GetRange(
    peak_icv_downsampling_handle downsampling_handle, peak_common_interval_u* range);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Set mode.
 *
 * \param[in] downsampling_handle  Handle for the downsampling object.
 * \param[in] mode                 Downsampling mode.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED            The given downsampling mode is not supported.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_SetMode(
    peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_mode mode);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Get mode.
 *
 * \param[in] downsampling_handle  Handle for the downsampling object.
 * \param[out] mode                Downsampling mode.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_GetMode(
    peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_mode* mode);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Returns the size of the output image after downsampling.
 *
 * \param[in]  downsampling_handle  Handle to the downsampling.
 * \param[in]  input_image_handle   The handle to the image to be processed.
 * \param[out] output_image_size    The handle to the image that is downsampled.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           One or more handles (input_image, downsampling_handle, output_image_size) were not created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_GetOutputImageSize(
    peak_icv_downsampling_handle downsampling_handle, peak_icv_image_handle input_image_handle, peak_common_size* output_image_size);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Checks if downsampling needs to be applied.
 *
 * \param[in]  downsampling_handle  Handle to the downsampling.
 * \param[out] needs_processing     True if processing is needed, otherwise false.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p downsampling_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p needs_processing is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_NeedsProcessing(
    peak_icv_downsampling_handle downsampling_handle, bool* needs_processing);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_downsampling
 *
 * \brief Applies the downsampling on the provided \p input_image_handle
 * and stores the downsampled result in the \p output_image_handle.
 *
 * Ensure that the output image has the correct dimensions.
 * Use \ref peak_icv_Preprocessing_Downsampling_GetOutputImageSize to retrieve the size of the processed image.
 *
 * \note This operation disregards any specified image regions. It processes the entire image.
 *
 * \param[in]  downsampling_handle  Handle to the downsampling.
 * \param[in]  input_image_handle   The handle to the image to be processed.
 * \param[out] output_image_handle  The handle to the image that contains the downsampled result.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           One or more handles (input_image, downsampling_handle) were not created.
 * \return #PEAK_ICV_STATUS_MISMATCH                 The output_image size does not match. See
 *                                                       \ref peak_icv_Preprocessing_Downsampling_GetOutputImageSize.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_Process(peak_icv_downsampling_handle downsampling_handle,
    peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle);


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
