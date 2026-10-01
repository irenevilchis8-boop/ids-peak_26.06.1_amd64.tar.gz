/*!
 * \file    peak_icv_saturation_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_interval.hpp>
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
 * \brief Adjusts the saturation of an image by modifying a 3x3 \ref ColorCorrectionMatrix.
 *
 * This feature modifies the image's color saturation by scaling the chrominance components
 * of the color correction matrix. A higher saturation makes colors more vivid, while a lower
 * value results in more muted tones.
 *
 * \defaults{defaults_feature_saturation|
 *   - saturation = 1.0
 * }
 *
 * \see \ref features::ColorCorrectionFeature, \ref ColorCorrectionMatrix
 *
 * \since ids_peak_icv 1.0
 */
class SaturationFeature : public IFeature
{
public:
    /*!
     * \brief Creates a SaturationFeature using an existing color matrix transformation module.
     *
     * \param module Reference to the underlying \ref detail::ColorMatrixTransformationModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit SaturationFeature(detail::ColorMatrixTransformationModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the saturation value to its \ref defaults_feature_saturation "default".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the saturation value.
     *
     * \param saturation A floating-point value representing the saturation value.
     *                   A value of 1.0 means no change, values greater than 1.0 increase saturation,
     *                   and values less than 1.0 decrease saturation.
     *                   Valid values are within the range returned by \ref GetRange.
     *
     * \warning Extreme saturation values may cause color clipping or unnatural color appearance.
     *          Values significantly above 2.0 or below 0.0 should be used with caution.
     *
     * \throws OutOfRangeException If \p saturation is outside the valid range.
     *
     * \see \ref features::ColorCorrectionFeature, GetRange()
     * \since ids_peak_icv 1.0
     */
    void SetValue(float saturation);

    /*!
     * \brief Gets the current saturation value.
     *
     * \return The current saturation value.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetValue() const;

    /*!
     * \brief Gets the valid range for the saturation value.
     *
     * The returned interval specifies the minimum and maximum values that can be passed to \ref SetValue.
     *
     * \return An IntervalF representing the valid saturation range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetRange() const;

private:
    detail::ColorMatrixTransformationModule& m_module;
};

inline SaturationFeature::SaturationFeature(detail::ColorMatrixTransformationModule& module)
    : m_module(module)
{}

inline void SaturationFeature::SetEnabled(bool enabled)
{
    m_module.SetSaturationEnabled(enabled);
}

inline bool SaturationFeature::IsEnabled() const
{
    return m_module.IsSaturationEnabled();
}

inline void SaturationFeature::ResetToDefault()
{
    SetValue(1.0F);
}

inline void SaturationFeature::SetValue(float saturation)
{
    m_module.SetSaturation(saturation);
}

inline float SaturationFeature::GetValue() const
{
    return m_module.GetSaturation();
}

inline peak::common::IntervalF SaturationFeature::GetRange() const
{
    return m_module.GetSaturationRange();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
