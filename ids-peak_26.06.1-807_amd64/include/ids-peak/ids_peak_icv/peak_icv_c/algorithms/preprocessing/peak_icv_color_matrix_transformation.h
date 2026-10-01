/*!
 * \file    peak_icv_color_matrix_transformation.h
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
 * \defgroup ids_peak_icv_c_preprocessing_color_matrix_transformation Color Matrix Transformation
 * \ingroup ids_peak_icv_c_preprocessing
 *
 * \brief Color Matrix Transformation applies a \ref peak_icv_color_correction_matrix to an image and adjusts it's saturation.
 *
 * Color correction is typically used to convert colors from a camera sensor’s native RGB space to a standard color space,
 * or to perform color balancing and correction.
 *
 * When performing color correction, a 3x3 \ref peak_icv_color_correction_matrix is applied to the color values of the image.
 *
 * The \ref peak_icv_color_correction_matrix is represented as a 3×3 float array:
 *
 * |        |        |        |
 * |--------|--------|--------|
 * | m_00   | m_01   | m_02   |
 * | m_10   | m_11   | m_12   |
 * | m_20   | m_21   | m_22   |
 *
 * Each element `m_ij` defines how much of the input channel `j` contributes to the output channel `i`.
 * For example, `m_01` is the contribution of the green input to the red output.
 *
 * The matrix is applied as follows:
 * \code
 * red_value_out = m_00 * red_value_in + m_01 * green_value_in + m_02 * blue_value_in;
 * green_value_out = m_10 * red_value_in + m_11 * green_value_in + m_12 * blue_value_in;
 * blue_value_out = m_20 * red_value_in + m_21 * green_value_in + m_22 * blue_value_in;
 * \endcode
 *
 * where \c red_value_in, \c green_value_in, and \c blue_value_in are the input red, green, and blue channel values, respectively,
 * and \c red_value_out, \c green_value_out, and \c blue_value_out are the corresponding corrected output values.
 * All RGB values are normalized to the range [0.0, 1.0].
 *
 * \since ids_peak_icv 1.0
 */
struct peak_icv_color_matrix_transformation;
typedef struct peak_icv_color_matrix_transformation* peak_icv_color_matrix_transformation_handle;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Color correction matrix.
 *
 * A color correction matrix is a 3×3 transformation matrix used to adjust RGB color values.
 * It is typically used to convert colors from a camera sensor’s native RGB space to a standard color space,
 * or to perform color balancing and correction.
 *
 * The color correction matrix is represented as a 3×3 float array:
 *
 * |        |        |        |
 * |--------|--------|--------|
 * | m_00   | m_01   | m_02   |
 * | m_10   | m_11   | m_12   |
 * | m_20   | m_21   | m_22   |
 *
 * \see \ref ids_peak_icv_c_preprocessing_color_matrix_transformation for more information.
 *
 * \since ids_peak_icv 1.0
 */
typedef union
{
    /*! \brief The matrix elements in struct format. */
    struct
    {
        /*! \brief Element 00 */
        float m_00;

        /*! \brief Element 01 */
        float m_01;

        /*! \brief Element 02 */
        float m_02;

        /*! \brief Element 10 */
        float m_10;

        /*! \brief Element 11 */
        float m_11;

        /*! \brief Element 12 */
        float m_12;

        /*! \brief Element 20 */
        float m_20;

        /*! \brief Element 21 */
        float m_21;

        /*! \brief Element 22 */
        float m_22;

    } elements;

    /*! \brief The matrix elements in 2-dimensional array format. */
    float data_2d[3][3];

    /*! \brief The matrix elements in 1-dimensional array format. */
    float data_1d[9];

} peak_icv_color_correction_matrix;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Enumeration that defines the available color spaces.
 *
 * A color space is a specific implementation of a color model, mapping colors to a defined range of values.
 * For example, sRGB is a standardized color space based on the RGB color model, but it also defines color primaries,
 * the white point, and gamma to ensure consistent color representation across various platforms and devices.
 */
typedef enum peak_icv_color_space
{
    //! sRGB (standard RGB): standard illuminant D50 (5000 K), gamma 2.2.
    PEAK_ICV_COLOR_SPACE_SRGB_D50 = 1,

    //! sRGB (standard RGB): standard illuminant D65 (6500 K), gamma 2.2.
    PEAK_ICV_COLOR_SPACE_SRGB_D65 = 2,

    //! CIE-RGB: standard illuminant E (equal energy distribution), gamma 2.2.
    PEAK_ICV_COLOR_SPACE_CIE_RGB_E = 3,

    //! ECI-RGB: standard illuminant D50 (5000 K), gamma 1.8.
    PEAK_ICV_COLOR_SPACE_ECI_RGB_D50 = 4,

    //! Adobe RGB: standard illuminant D65 (6500 K), gamma 2.2.
    PEAK_ICV_COLOR_SPACE_ADOBE_RGB_D65 = 5

} peak_icv_color_space;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Enumeration that defines the available chromatic adaption algorithms.
 */
typedef enum peak_icv_chromatic_adaption_algorithm
{
    PEAK_ICV_CHROMATIC_ADAPTION_ALGORITHM_LEGACY = 1,
    PEAK_ICV_CHROMATIC_ADAPTION_ALGORITHM_BRADFORD = 2
} peak_icv_chromatic_adaption_algorithm;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Creates a color matrix transformation object.
 *
 * \param[out] color_matrix_transformation_handle  Handle for the color matrix transformation object.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_Create(
    peak_icv_color_matrix_transformation_handle* color_matrix_transformation_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Destroys a color matrix transformation handle.
 *
 * \destroyHandle{color matrix transformation}
 *
 * \param[in] color_matrix_transformation_handle  Color matrix transformation handle to destroy.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_Destroy(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Checks if the color matrix transformation needs to be applied.
 *
 * \param[in]  color_matrix_transformation_handle  Handle to the color matrix transformation.
 * \param[out] needs_processing                    True if processing is needed, otherwise false.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p needs_processing is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* needs_processing);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Applies the color matrix transformation on the provided \p input_image_handle in-place.
 *
 * \note This operation disregards any specified image regions. It processes the entire image.
 *
 * \param[in]  color_matrix_transformation_handle  Handle to the color matrix transformation.
 * \param[in]  input_image_handle                  The handle to the image to be processed.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           One or more handles (\p input_image_handle, \p color_matrix_transformation_handle) were not created.
 * \return #PEAK_ICV_STATUS_MISMATCH                 The output image size or pixel format does not match.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_image_handle input_image_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Sets the \ref peak_icv_color_correction_matrix to \p color_correction_matrix.
 *
 * \param[in]  color_matrix_transformation_handle  Handle to the color matrix transformation.
 * \param[in]  color_correction_matrix             The color correction matrix to set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle,
    peak_icv_color_correction_matrix color_correction_matrix);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Returns the \ref peak_icv_color_correction_matrix into \p color_correction_matrix.
 *
 * \param[in]  color_matrix_transformation_handle  Handle to the color matrix transformation.
 * \param[out] color_correction_matrix             The color correction matrix.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p color_correction_matrix is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle,
    peak_icv_color_correction_matrix* color_correction_matrix);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Sets the saturation to the value in \p saturation.
 *
 * \param[in] color_matrix_transformation_handle  Handle to the color matrix transformation.
 * \param[in] saturation                          The saturation value to set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_OUT_OF_RANGE             \p saturation is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, float saturation);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Returns the saturation value into \p saturation.
 *
 * \param[in]  color_matrix_transformation_handle  Handle to the color matrix transformation.
 * \param[out] saturation                          Pointer to the variable to store the saturation value to.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p color_correction_matrix is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, float* saturation);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Returns the valid range for setting saturation values.
 *
 * Provides the minimum and maximum values
 * that are accepted by the \ref peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation function.
 *
 * \param[in]  color_matrix_transformation_handle  Handle to the Color Corrector.
 * \param[out] range                               The interval containing the minimum and maximum valid saturation values.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p range is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_common_interval_f* range);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Returns the effective \ref peak_icv_color_correction_matrix into \p color_correction_matrix.
 *
 * This is the matrix used internally to combine saturation and color correction.
 *
 * \param[in]  color_matrix_transformation_handle  Handle to the color matrix transformation.
 * \param[out] color_correction_matrix             The effective color correction matrix.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p color_correction_matrix is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle,
    peak_icv_color_correction_matrix* color_correction_matrix);


/*!
 * \brief Get the current chromatic adaption target color space for the color matrix transformation instance.
 *
 * \param[in]  color_matrix_transformation_handle        Handle to the color matrix transformation.
 * \param[out] color_space                               The color space for chromatic adaption.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p color_space is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_space* color_space);


/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Sets the chromatic adaption target color space for the color matrix transformation instance to \p color_space.
 *
 * \param[in] color_matrix_transformation_handle    Handle to the color matrix transformation.
 * \param[in] color_space                           The color space for chromatic adaption to be set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_space color_space);
/*!
 * \brief Get the current chromatic adaption target algorithm for the color matrix transformation instance.
 *
 * \param[in]  color_matrix_transformation_handle        Handle to the color matrix transformation.
 * \param[out] algorithm                                 The algorithm for chromatic adaption.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p algorithm is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_chromatic_adaption_algorithm* algorithm);


/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Sets the chromatic adaption target algorithm for the color matrix transformation instance to \p algorithm.
 *
 * \param[in] color_matrix_transformation_handle    Handle to the color matrix transformation.
 * \param[in] algorithm                             The algorithm for chromatic adaption to be set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_chromatic_adaption_algorithm algorithm);


/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Sets the chromatic adaption temperature for the color matrix transformation instance to \p temperature.
 *
 * \param[in] color_matrix_transformation_handle        Handle to the color matrix transformation.
 * \param[in] color_temperature                         The temperature in Kelvin for chromatic adaption to be set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, uint32_t color_temperature);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Gets the chromatic adaption temperature for the color matrix transformation instance.
 *
 * \param[in]  color_matrix_transformation_handle       Handle to the color matrix transformation.
 * \param[out] color_temperature                        The temperature in Kelvin.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p color_temperature is not a valid pointer.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE             The color temperature has no default value. Use \p peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature to set it first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, uint32_t* color_temperature);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Resets the chromatic adaption temperature for the color matrix transformation instance.
 *
 * \param[in]  color_matrix_transformation_handle       Handle to the color matrix transformation.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Gets the possible chromatic adaption temperature range for the color matrix transformation instance
 *
 * \param[in]  color_matrix_transformation_handle   Handle to the color matrix transformation.
 * \param[out] range                                Contains the minimum, maximum and increment values in kelvin.
 * \param[out] maximum_temperature                  The maximum temperature in kelvin.
 * \param[out] increment_temperature                The temperature increment in kelvin.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p range is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_common_range_u* range);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Checks if the color matrix transformation currently has a color temperature set for chromatic adaption.
 *
 * \param[in]  color_matrix_transformation_handle   Handle to the color matrix transformation.
 * \param[out] has_color_temperature                True if a color temperature is set, otherwise false.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p has_color_temperature is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* has_color_temperature);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Enables or disables chromatic adaption.
 *
 * \param[in]  color_matrix_transformation_handle   Handle to the color matrix transformation.
 * \param[in]  enabled                              True to enable chromatic adaption, false to disable.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Checks if chromatic adaption is currently enabled.
 *
 * \param[in]  color_matrix_transformation_handle   Handle to the color matrix transformation.
 * \param[out] enabled                              True if chromatic adaption is enabled, otherwise false.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p enabled is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Enables or disables saturation adjustment.
 *
 * \param[in]  color_matrix_transformation_handle   Handle to the color matrix transformation.
 * \param[in]  enabled                              True to enable saturation adjustment, false to disable.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Checks if saturation adjustment is currently enabled.
 *
 * \param[in]  color_matrix_transformation_handle   Handle to the color matrix transformation.
 * \param[out] enabled                              True if saturation adjustment is enabled, otherwise false.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p enabled is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Enables or disables color correction.
 *
 * \param[in]  color_matrix_transformation_handle   Handle to the color matrix transformation.
 * \param[in]  enabled                              True to enable color correction, false to disable.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_color_matrix_transformation
 *
 * \brief Checks if color correction is currently enabled.
 *
 * \param[in]  color_matrix_transformation_handle   Handle to the color matrix transformation.
 * \param[out] enabled                              True if color correction is enabled, otherwise false.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p color_matrix_transformation_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             \p enabled is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled(
    peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);

#ifdef __cplusplus
} // extern "C"

#endif // __cplusplus
