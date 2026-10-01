/*!
 * \file    peak_icv_gain.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup ids_peak_icv_c_preprocessing_gain Gain
 * \ingroup ids_peak_icv_c_preprocessing
 *
 * Gain is used to adjust pixel intensities either uniformly across all color channels using the master gain,
 * or individually per channel using the red, green, and blue gains.
 * With master gain, image brightness can be increased.
 * With color gains, the white balance can be adjusted.
 *
 * For color images, gain is applied as follows:
 * \code
 * red_value_out = red_value_in * red_gain * master_gain
 * green_value_out = green_value_in * green_gain * master_gain
 * blue_value_out = blue_value_in * blue_gain * master_gain
 * \endcode
 *
 * where \c red_value_in, \c green_value_in, and \c blue_value_in are the input red, green, and blue channel values, respectively,
 * and \c red_value_out, \c green_value_out, and \c blue_value_out are the corresponding output values.
 * All RGB values are normalized to the range [0.0, 1.0].
 *
 * For mono images, the color gains are ignored and applied as follows:
 * \code
 * gray_value_out = gray_value_in * master_gain
 * \endcode
 *
 * where \c gray_value_in is the input and \c gray_value_out the output value, normalized to the range [0.0, 1.0].
 *
 * \since ids_peak_icv 1.0
 */
struct peak_icv_gain;
typedef struct peak_icv_gain* peak_icv_gain_handle;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_gain
 *
 * \brief Gain type.
 *
 * The following gain types are supported:
 *
 * \since ids_peak_icv 1.0
 */
typedef enum peak_icv_gain_type
{
    //! The gain is applied to all color channels uniformly.
    PEAK_ICV_GAIN_TYPE_MASTER = 0,
    //! The gain is applied to the red channel.
    PEAK_ICV_GAIN_TYPE_RED = 1,
    //! The gain is applied to the green channel.
    PEAK_ICV_GAIN_TYPE_GREEN = 2,
    //! The gain is applied to the blue channel.
    PEAK_ICV_GAIN_TYPE_BLUE = 3
} peak_icv_gain_type;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_gain
 *
 * \brief Creates a gain object.
 *
 * \param[out] gain_handle  Handle for the gain object.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_Create(peak_icv_gain_handle* gain_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_gain
 *
 * \brief Destroys a gain handle.
 *
 * \destroyHandle{gain}
 *
 * \param[in] gain_handle  Gain handle to destroy.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p gain_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_Destroy(peak_icv_gain_handle gain_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_gain
 *
 * \brief Applies the gain on the provided \p input_image_handle in-place.
 *
 * \note This operation disregards any specified image regions. It processes the entire image.
 *
 * \param[in]  gain_handle         Handle to the gain.
 * \param[in]  input_image_handle  The handle to the image to be processed.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           One or more handles (\p input_image_handle, \p gain_handle) were not created.
 * \return #PEAK_ICV_STATUS_MISMATCH                 The output image size or pixel format does not match.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_ProcessInplace(
    peak_icv_gain_handle gain_handle, peak_icv_image_handle input_image_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_gain
 *
 * \brief Checks if gain needs to be applied.
 *
 * \param[in]  gain_handle       Handle to the gain.
 * \param[out] needs_processing  True if processing is needed, otherwise false.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p gain_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p needs_processing is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_NeedsProcessing(peak_icv_gain_handle gain_handle, bool* needs_processing);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_gain
 *
 * \brief Sets the gain of \p type to \p value.
 *
 * \note The provided \p value must be within the valid range.
 *       You can get the valid range using the \ref peak_icv_Preprocessing_Gain_GetRange function.
 *
 * \param[in]  gain_handle  Handle to the gain.
 * \param[in]  type         The gain type.
 * \param[in]  value        The value to set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p gain_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The gain \p type is not valid.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE             \p value is out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_SetValue(peak_icv_gain_handle gain_handle, peak_icv_gain_type type, float value);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_gain
 *
 * \brief Returns the gain of \p type into \p value.
 *
 * \param[in]  gain_handle  Handle to the gain.
 * \param[in]  type         The gain type.
 * \param[out] value        The returned value.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p gain_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The gain \p type is not valid or \p value is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_GetValue(peak_icv_gain_handle gain_handle, peak_icv_gain_type type, float* value);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_gain
 *
 * \brief Returns the valid range for setting gain values.
 *
 * Provides the minimum and maximum values that are accepted by the \ref peak_icv_Preprocessing_Gain_SetValue function.
 *
 * \param[in]  gain_handle  Handle to the gain.
 * \param[out] range        The interval containing the minimum and maximum valid gain values.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p gain_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p range is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_GetRange(peak_icv_gain_handle gain_handle, peak_common_interval_f* range);


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
