/*!
 * \file    peak_icv_color_correction_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/pipeline/detail/peak_icv_color_matrix_transformation_module.hpp>
#include <peak_icv/pipeline/features/peak_icv_ifeature.hpp>

namespace peak
{
namespace pipeline
{
namespace features
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_features
 *
 * \brief Color correction applies a 3x3 \ref ColorCorrectionMatrix to the image.
 *
 * Color correction is typically used to convert colors from a camera sensor’s native RGB space to a standard color space,
 * or to perform color balancing and correction.
 *
 * When performing color correction, a 3x3 \ref ColorCorrectionMatrix is applied to the color values of the image.
 *
 * The \ref ColorCorrectionMatrix is represented as a 3×3 float array:
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
 * red_value_out   = m_00 * red_value_in + m_01 * green_value_in + m_02 * blue_value_in;
 * green_value_out = m_10 * red_value_in + m_11 * green_value_in + m_12 * blue_value_in;
 * blue_value_out  = m_20 * red_value_in + m_21 * green_value_in + m_22 * blue_value_in;
 * \endcode
 *
 * where \c red_value_in, \c green_value_in, and \c blue_value_in are the input red, green, and blue channel values, respectively,
 * and \c red_value_out, \c green_value_out, and \c blue_value_out are the corresponding corrected output values.
 * All RGB values are normalized to the range [0.0, 1.0].
 *
 * \warning Improper color correction matrices may result in color shifts, clipping, or unnatural colors.
 *
 * \defaults{defaults_feature_colorcorrection|
 *   - identity matrix
 * }
 *
 * \see \ref ColorCorrectionMatrix, \ref features::SaturationFeature, \ref features::ChromaticAdaptionFeature
 *
 * \since ids_peak_icv 1.0
 */
class ColorCorrectionFeature : public IFeature
{
public:
    /*!
     * \brief Creates a ColorCorrectionFeature for an existing color matrix transformation module.
     *
     * \param module Reference to the underlying \ref detail::ColorMatrixTransformationModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit ColorCorrectionFeature(detail::ColorMatrixTransformationModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the \ref ColorCorrectionMatrix to the \ref defaults_feature_colorcorrection "default".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the \ref ColorCorrectionMatrix
     *
     * \param matrix The \ref ColorCorrectionMatrix to set.
     *
     * \since ids_peak_icv 1.0
     */
    void SetMatrix(const ColorCorrectionMatrix& matrix);

    /*!
     * \brief Gets the current \ref ColorCorrectionMatrix.
     *
     * \returns The current \ref ColorCorrectionMatrix.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD ColorCorrectionMatrix GetMatrix() const;

private:
    detail::ColorMatrixTransformationModule& m_module;
};

inline ColorCorrectionFeature::ColorCorrectionFeature(detail::ColorMatrixTransformationModule& module)
    : m_module(module)
{}

inline void ColorCorrectionFeature::SetEnabled(bool enabled)
{
    m_module.SetColorCorrectionEnabled(enabled);
}

inline bool ColorCorrectionFeature::IsEnabled() const
{
    return m_module.IsColorCorrectionEnabled();
}

inline void ColorCorrectionFeature::ResetToDefault()
{
    SetMatrix(ColorCorrectionMatrix::Identity());
}

inline void ColorCorrectionFeature::SetMatrix(const ColorCorrectionMatrix& matrix)
{
    m_module.SetMatrix(matrix);
}

inline ColorCorrectionMatrix ColorCorrectionFeature::GetMatrix() const
{
    return m_module.GetMatrix();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
