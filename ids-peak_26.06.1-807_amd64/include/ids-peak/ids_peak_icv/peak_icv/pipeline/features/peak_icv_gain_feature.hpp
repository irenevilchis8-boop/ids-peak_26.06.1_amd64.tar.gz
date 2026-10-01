/*!
 * \file    peak_icv_gain_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/pipeline/detail/peak_icv_gain_module.hpp>
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
 * \brief The GainFeature applies gain to the image.
 *
 * Gain is used to adjust pixel intensities either uniformly across all color channels using the master gain,
 * or individually per channel using the red, green, and blue gains.
 * With master gain, image brightness can be increased.
 * With color gains, the white balance can be adjusted.
 *
 * For color images, gain is applied as follows:
 * \code
 * red_value_out   = red_value_in   * red_gain   * master_gain
 * green_value_out = green_value_in * green_gain * master_gain
 * blue_value_out  = blue_value_in  * blue_gain  * master_gain
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
 * \warning Excessive gain values may cause clipping and loss of image detail in bright areas.
 *
 * \defaults{defaults_feature_gain|
 * - red_gain = 1.0
 * - green_gain = 1.0
 * - blue_gain = 1.0
 * - master_gain = 1.0
 * }
 *
 * \see \ref features::DigitalBlackFeature, \ref features::GammaFeature
 *
 * \since ids_peak_icv 1.0
 */
class GainFeature : public IFeature
{
public:
    /*!
     * \brief Creates a GainFeature for an existing gain module.
     *
     * \param module Reference to the underlying \ref detail::GainModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit GainFeature(detail::GainModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the gain values to their \ref defaults_feature_gain "defaults".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the master gain value.
     *
     * Sets the overall master gain. The valid range for the gain value can be
     * obtained using the \ref GetRange function.
     *
     * \param value The master gain value to set.
     *
     * \throws peak::icv::OutOfRangeException  If the gain \p value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetMaster(float value);

    /*!
     * \brief Retrieves the current master gain.
     *
     * \returns The current master gain.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetMaster() const;

    /*!
     * \brief Sets the red gain value.
     *
     * Sets the color gain for the red channel. The valid range for the gain value can be
     * obtained using the \ref GetRange function.
     *
     * \param value The red gain value to set.
     *
     * \throws peak::icv::OutOfRangeException  If the gain \p value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetRed(float value);

    /*!
     * \brief Retrieves the current red gain.
     *
     * \returns The current red gain.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetRed() const;

    /*!
     * \brief Sets the green gain value.
     *
     * Sets the color gain for the green channel. The valid range for the gain value can be
     * obtained using the \ref GetRange function.
     *
     * \param value The green gain value to set.
     *
     * \throws peak::icv::OutOfRangeException  If the gain \p value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetGreen(float value);

    /*!
     * \brief Retrieves the current green gain.
     *
     * \returns The current green gain.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetGreen() const;

    /*!
     * \brief Sets the blue gain value.
     *
     * Sets the color gain for the blue channel. The valid range for the gain value can be
     * obtained using the \ref GetRange function.
     *
     * \param value The blue gain value to set.
     *
     * \throws peak::icv::OutOfRangeException  If the gain \p value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetBlue(float value);

    /*!
     * \brief Retrieves the current blue gain.
     *
     * \returns The current blue gain.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetBlue() const;

    /*!
     * \brief Retrieves the valid range for the master or color gains.
     *
     * The returned interval specifies the minimum and maximum values that can be passed to
     * \ref SetMaster, \ref SetRed, \ref SetGreen and \ref SetBlue.
     *
     * \returns An IntervalF representing the valid gain range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetRange() const;

private:
    detail::GainModule& m_module;
};

inline GainFeature::GainFeature(detail::GainModule& module)
    : m_module(module)
{}

inline void GainFeature::SetEnabled(bool enabled)
{
    m_module.SetEnabled(enabled);
}

inline bool GainFeature::IsEnabled() const
{
    return m_module.IsEnabled();
}

inline void GainFeature::ResetToDefault()
{
    m_module.ResetToDefault();
}

inline void GainFeature::SetMaster(float value)
{
    m_module.SetMaster(value);
}

inline float GainFeature::GetMaster() const
{
    return m_module.GetMaster();
}

inline void GainFeature::SetRed(float value)
{
    m_module.SetRed(value);
}

inline float GainFeature::GetRed() const
{
    return m_module.GetRed();
}

inline void GainFeature::SetGreen(float value)
{
    m_module.SetGreen(value);
}

inline float GainFeature::GetGreen() const
{
    return m_module.GetGreen();
}

inline void GainFeature::SetBlue(float value)
{
    m_module.SetBlue(value);
}

inline float GainFeature::GetBlue() const
{
    return m_module.GetBlue();
}

inline peak::common::IntervalF GainFeature::GetRange() const
{
    return m_module.GetRange();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
