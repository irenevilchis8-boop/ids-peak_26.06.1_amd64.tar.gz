/*!
 * \file    peak_icv_gamma_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/pipeline/detail/peak_icv_tone_curve_correction_module.hpp>
#include <peak_icv/pipeline/features/peak_icv_ifeature.hpp>

namespace peak
{
namespace pipeline
{
class DefaultPipeline;

namespace features
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_features
 *
 * \brief Gamma applies an inverse gamma transformation to an image.
 *
 * This module adjusts the image luminance by applying an inverse gamma correction.
 * This prepares the image for a linear domain or further processing.
 *
 * The correction is applied independently to each channel in the image. For RGB images, it is applied
 * to each color channel (R, G, B), and for monochrome images, it is applied to the single intensity channel.
 *
 * The correction is performed using the following formula:
 * \code
 * color_value_out = pow(color_value_in, 1.0 / gamma);
 * \endcode
 *
 * where:
 * - \c color_value_in is the input channel value,
 * - \c gamma is the gamma exponent,
 * - \c color_value_out is the resulting output value.
 *
 * \warning Gamma values close to zero may result in very dark images, while very high values
 *          may cause loss of detail in dark areas. Use values within the range returned by GetRange().
 *
 * \defaults{defaults_feature_gamma|
 *   - gamma = 1.0
 * }
 *
 * \see \ref features::DigitalBlackFeature, \ref features::GainFeature, \ref features::SharpeningFeature
 *
 * \since ids_peak_icv 1.0
 */
class GammaFeature : public IFeature
{
public:
    /*!
     * \brief Creates a GammaFeature for an existing tone curve correction module.
     *
     * \param module Reference to the underlying \ref detail::ToneCurveCorrectionModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit GammaFeature(detail::ToneCurveCorrectionModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the gamma value to the \ref defaults_feature_gamma "default".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the gamma correction exponent.
     *
     * This value determines the degree of inverse gamma correction applied during processing,
     * where output values are computed as pow(input, 1/gamma).
     * Higher gamma values lighten the image, while values closer to zero darken it.
     *
     * \param gamma A floating-point value representing the gamma exponent.
     *              Valid values are within the range returned by \ref GetRange.
     *
     * \throws OutOfRangeException  If \p gamma is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetValue(float gamma);

    /*!
     * \brief Gets the current gamma correction exponent.
     *
     * \return The gamma exponent currently set.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetValue() const;

    /*!
     * \brief Retrieves the valid range for the gamma correction exponent.
     *
     * The returned interval specifies the minimum and maximum values that can be passed to \ref SetValue.
     *
     * \return An IntervalF representing the valid gamma range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetRange() const;

private:
    detail::ToneCurveCorrectionModule& m_module;
};

inline GammaFeature::GammaFeature(detail::ToneCurveCorrectionModule& module)
    : m_module(module)
{}

inline void GammaFeature::SetEnabled(bool enabled)
{
    m_module.SetGammaEnabled(enabled);
}

inline bool GammaFeature::IsEnabled() const
{
    return m_module.IsGammaEnabled();
}

inline void GammaFeature::ResetToDefault()
{
    SetValue(1.0F);
}

inline void GammaFeature::SetValue(float gamma)
{
    m_module.SetGamma(gamma);
}

inline float GammaFeature::GetValue() const
{
    return m_module.GetGamma();
}

inline peak::common::IntervalF GammaFeature::GetRange() const
{
    return m_module.GetGammaRange();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
