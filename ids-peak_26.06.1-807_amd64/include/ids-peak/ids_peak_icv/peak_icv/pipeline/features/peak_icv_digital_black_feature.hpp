/*!
 * \file    peak_icv_digital_black_feature.hpp
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
namespace features
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_features
 *
 * \brief Digital black applies digital black correction to an image.
 *
 * This feature adjusts the image luminance by first subtracting a digital black and then normalizing the result.
 * This compensates for sensor digital black offsets.
 *
 * The correction is applied independently to each channel in the image. For RGB images, it is applied
 * to each color channel (R, G, B), and for monochrome images, it is applied to the single intensity channel.
 *
 * The correction is performed using the following formula:
 * \code
 * color_value_out = clamp((color_value_in - black) / (1.0 - black), 0.0, 1.0);
 * \endcode
 *
 * where:
 * - \c color_value_in is the input channel value,
 * - \c black is the digital black to be subtracted (in normalized units),
 * - \c color_value_out is the resulting output value.
 *
 * All input and output values are in the normalized range [0.0, 1.0].
 *
 * \defaults{defaults_feature_digitalblack|
 *   - black = 0.0
 * }
 *
 * \see \ref features::GammaFeature, \ref features::GainFeature
 *
 * \since ids_peak_icv 1.0
 */
class DigitalBlackFeature : public IFeature
{
public:
    /*!
     * \brief Creates a DigitalBlackFeature for an existing tone curve correction module.
     *
     * \param module Reference to the underlying \ref detail::ToneCurveCorrectionModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit DigitalBlackFeature(detail::ToneCurveCorrectionModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the digital black value to its \ref defaults_feature_digitalblack "default".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the digital black correction value.
     *
     * This value is subtracted from the input image channel values before normalizing it. It typically represents sensor black offset.
     *
     * \param digitalBlack A floating-point value representing the digital black value in normalized units.
     *                     Valid values are within the range returned by \ref GetRange.
     *
     * \throws OutOfRangeException  If \p digitalBlack is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetValue(float digitalBlack);

    /*!
     * \brief Gets the current digital black correction value.
     *
     * \return The digital black value currently set.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetValue() const;

    /*!
     * \brief Retrieves the valid range for the digital black value.
     *
     * The returned interval specifies the minimum and maximum values that can be passed to \ref SetValue.
     *
     * \return An IntervalF representing the valid digital black range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetRange() const;

private:
    detail::ToneCurveCorrectionModule& m_module;
};

inline DigitalBlackFeature::DigitalBlackFeature(detail::ToneCurveCorrectionModule& module)
    : m_module(module)
{}

inline void DigitalBlackFeature::SetEnabled(bool enabled)
{
    m_module.SetDigitalBlackEnabled(enabled);
}

inline bool DigitalBlackFeature::IsEnabled() const
{
    return m_module.IsDigitalBlackEnabled();
}

inline void DigitalBlackFeature::ResetToDefault()
{
    SetValue(0.0F);
}

inline void DigitalBlackFeature::SetValue(float digitalBlack)
{
    m_module.SetDigitalBlack(digitalBlack);
}

inline float DigitalBlackFeature::GetValue() const
{
    return m_module.GetDigitalBlack();
}

inline peak::common::IntervalF DigitalBlackFeature::GetRange() const
{
    return m_module.GetDigitalBlackRange();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
