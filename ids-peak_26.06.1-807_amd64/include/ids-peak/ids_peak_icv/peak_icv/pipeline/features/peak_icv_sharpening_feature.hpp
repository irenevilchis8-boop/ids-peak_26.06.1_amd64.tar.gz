/*!
 * \file    peak_icv_sharpening_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/pipeline/detail/peak_icv_sharpening_module.hpp>
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
 * \brief Sharpening applies a sharpening filter to enhance image detail.
 *
 * It enhances edges and fine structures by emphasizing high-frequency components in the image.
 *
 * The strength of the effect is controlled by the sharpness level, where `0` results in no change.
 *
 * \warning Increasing the sharpness level can also amplify image noise, especially at higher values.
 *          Excessive sharpening may introduce artifacts such as halos around edges.
 *
 * \defaults{defaults_feature_sharpening|
 *   - level = 0
 * }
 *
 * \see \ref features::GammaFeature
 *
 * \since ids_peak_icv 1.0
 */
class SharpeningFeature : public IFeature
{
public:
    /*!
     * \brief Initialize the SharpeningFeature to manage the specified sharpening module.
     *
     * \param module Reference to the underlying \ref detail::SharpeningModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit SharpeningFeature(detail::SharpeningModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the sharpness level to the \ref defaults_feature_sharpening "default value".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the sharpness level.
     *
     * \param level The acceptable range of values can be obtained from the range property.
     *              A value of 0 means no sharpening, higher values increase the effect.
     *              Valid values are within the range returned by \ref GetRange.
     *
     * \warning Higher sharpness levels may increase noise in the output image and introduce
     *          artifacts such as halos around edges. Use moderate values for best results.
     *
     * \throws OutOfRangeException  If \p level is outside the valid range.
     *
     * \see GetRange()
     * \since ids_peak_icv 1.0
     */
    void SetLevel(uint32_t level);

    /*!
     * \brief Gets the current sharpness level.
     *
     * \return The sharpness level currently set.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetLevel() const;

    /*!
     * \brief Retrieves the valid range for the sharpness level.
     *
     * The returned interval specifies the minimum and maximum values that can be passed to \ref SetLevel.
     *
     * \return An IntervalU representing the valid sharpness level range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalU GetRange() const;

private:
    detail::SharpeningModule& m_module;
};

inline SharpeningFeature::SharpeningFeature(detail::SharpeningModule& module)
    : m_module(module)
{}

inline void SharpeningFeature::SetEnabled(bool enabled)
{
    m_module.SetEnabled(enabled);
}

inline bool SharpeningFeature::IsEnabled() const
{
    return m_module.IsEnabled();
}

inline void SharpeningFeature::ResetToDefault()
{
    m_module.ResetToDefault();
}

inline void SharpeningFeature::SetLevel(uint32_t level)
{
    m_module.SetLevel(level);
}

inline uint32_t SharpeningFeature::GetLevel() const
{
    return m_module.GetLevel();
}

inline peak::common::IntervalU SharpeningFeature::GetRange() const
{
    return m_module.GetLevelRange();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
