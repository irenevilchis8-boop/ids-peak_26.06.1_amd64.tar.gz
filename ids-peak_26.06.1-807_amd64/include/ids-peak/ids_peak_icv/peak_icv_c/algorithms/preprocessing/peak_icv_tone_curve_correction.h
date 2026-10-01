/*!
 * \file    peak_icv_tone_curve_correction.h
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
 * \defgroup ids_peak_icv_c_preprocessing_tone_curve_correction Tone Curve Correction
 * \ingroup ids_peak_icv_c_preprocessing
 *
 * \brief Tone curve correction applies digital black correction and inverse gamma transformation to an image.
 *
 * Tone curve correction adjusts the image luminance by first subtracting a digital black, normalizing the result,
 * and then applying an inverse gamma correction. This compensates for sensor digital black offsets and prepares
 * the image for a linear domain or further processing.
 *
 * The correction is applied independently to each channel in the image. For RGB images, it is applied
 * to each color channel (R, G, B), and for monochrome images, it is applied to the single intensity channel.
 *
 * The correction is performed using the following formula:
 * \code
 * color_value_norm = clamp((color_value_in - black) / (1.0 - black), 0.0, 1.0);
 * color_value_out = pow(color_value_norm, 1.0 / gamma);
 * \endcode
 *
 * where:
 * - \c color_value_in is the input channel value,
 * - \c black is the digital black to be subtracted (in normalized units),
 * - \c gamma is the gamma exponent,
 * - \c color_value_out is the resulting output value.
 *
 * All input and output values are in the normalized range [0.0, 1.0].
 *
 * \since ids_peak_icv 1.0
 */
struct peak_icv_tone_curve_correction;
typedef struct peak_icv_tone_curve_correction* peak_icv_tone_curve_correction_handle;


/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Creates a tone curve correction object.
 *
 * \param[out] tone_curve_correction_handle  Handle for the tone curve correction object.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_Create(
    peak_icv_tone_curve_correction_handle* tone_curve_correction_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Destroys a tone curve correction handle.
 *
 * \destroyHandle{tone curve correction}
 *
 * \param[in] tone_curve_correction_handle  Tone curve correction handle to destroy.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p tone_curve_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_Destroy(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Returns the valid range for setting gamma values.
 *
 * Provides the minimum and maximum values that are accepted by the \ref peak_icv_Preprocessing_ToneCurveCorrection_SetGamma function.
 *
 * \param[in]  tone_curve_correction_handle   Handle to the tone curve correction.
 * \param[out] range                          The interval containing the minimum and maximum valid gamma values.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p tone_curve_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p range is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_common_interval_f* range);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Returns the valid range for setting digital black values.
 *
 * Provides the minimum and maximum values that are accepted by the \ref peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack
 * function.
 *
 * \param[in]  tone_curve_correction_handle   Handle to the tone curve correction.
 * \param[out] range                          The interval containing the minimum and maximum valid digital black values.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p tone_curve_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p range is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_common_interval_f* range);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Returns the current gamma into \p value.
 *
 * \param[in]  tone_curve_correction_handle   Handle to the tone curve correction.
 * \param[out] value                          The current gamma value.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p tone_curve_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p value is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_GetGamma(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float* value);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Returns the current digital black into \p value.
 *
 * \param[in]  tone_curve_correction_handle   Handle to the tone curve correction.
 * \param[out] value                          The current digital black value.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p tone_curve_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p value is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float* value);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Sets the current gamma to \p value.
 *
 * \note The provided \p value must be within the valid range.
 *       You can get the valid range using the \ref peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange function.
 *
 * \param[in]  tone_curve_correction_handle             Handle to the tone curve correction.
 * \param[in]  value                                    The value to set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p tone_curve_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE             The \p value is out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_SetGamma(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float value);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Sets the current digital black to \p value.
 *
 * \note The provided \p value must be within the valid range.
 *       You can get the valid range using the \ref peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange function.
 *
 * \param[in]  tone_curve_correction_handle   Handle to the tone curve correction.
 * \param[in]  value                          The value to set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p tone_curve_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE             The \p value is out of range.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float value);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Checks if tone curve correction needs to be applied.
 *
 * \param[in]  tone_curve_correction_handle   Handle to the tone curve correction.
 * \param[out] needs_processing               True if processing is needed, otherwise false.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p tone_curve_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p needs_processing is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle, bool* needs_processing);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_tone_curve_correction
 *
 * \brief Applies gamma and digital black on the provided \p input_image_handle in-place.
 *
 * \note This operation disregards any specified image regions. It processes the entire image.
 *
 * \param[in]  tone_curve_correction_handle  Handle to the tone curve correction.
 * \param[in]  input_image_handle            The handle to the image to be processed.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           One or more handles (\p input_image_handle, \p tone_curve_correction_handle) were not created.
 * \return #PEAK_ICV_STATUS_MISMATCH                 The output image size or pixel format does not match.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace(
    peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_icv_image_handle input_image_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
