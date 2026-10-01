/*!
 * \file    peak_icv_decimation_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/pipeline/detail/peak_icv_downsampling_module.hpp>
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
 * \brief Decimation is used to decrease the image size.
 *
 * This method reduces resolution by selecting (i.e., skipping) pixels at regular intervals
 * along, columns (x), rows (y) or both.
 * It is computationally efficient but may introduce aliasing.
 *
 * \note Processes the entire image, ignoring any specified image region.
 * As with binning, the alpha channel of the input image (if present) is also ignored during decimation.
 * It is always set to the maximum possible pixel value.
 *
 * \warning Decimation permanently reduces image resolution. The original resolution cannot be recovered
 *          after decimation is applied.
 *
 * \defaults{defaults_feature_decimation|
 *   - x = 1
 *   - y = 1
 *   - peak::pipeline::detail::DownsamplingMode::Decimation
 * }
 *
 * \see \ref features::BinningFeature
 *
 * \since ids_peak_icv 1.0
 */
class DecimationFeature : public IFeature
{
public:
    /*!
     * \brief Creates a DecimationFeature for an existing downsampling module.
     *
     * \param module Reference to the underlying \ref detail::DownsamplingModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit DecimationFeature(detail::DownsamplingModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets all settings to the \ref defaults_feature_decimation "default values".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the number of columns used for decimation.
     *
     * \param x The number of columns used for decimation.
     *          The decimation algorithm uses one column, skips the next \p x - 1 columns, and repeats this process.
     *          Valid values are within the range returned by \ref GetRange.
     *
     * \throws OutOfRangeException  If \p x is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetX(uint32_t x);

    /*!
     * \brief Sets the number of rows used for decimation.
     *
     * \param y The number of rows used for decimation.
     *          The decimation algorithm uses one row, skips the next \p y - 1 rows, and repeats this process.
     *          Valid values are within the range returned by \ref GetRange.
     *
     * \throws OutOfRangeException  If \p y is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetY(uint32_t y);

    /*!
     * \brief Gets the current number of columns used for decimation.
     *
     * \returns The current number of columns used for decimation.
     *          The decimation algorithm uses one column, skips the next \p x - 1 columns, and repeats this process.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetX() const;

    /*!
     * \brief Gets the current number of rows used for decimation.
     *
     * \returns The current number of rows used for decimation.
     *          The decimation algorithm uses one row, skips the next \p y - 1 rows, and repeats this process.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetY() const;

    /*!
     * \brief Gets the valid range for the decimation factors x and y.
     *
     * The returned interval specifies the minimum and maximum values that can be passed to \ref SetX or \ref SetY.
     *
     * \returns An IntervalU representing the valid decimation factor range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalU GetRange() const;

private:
    detail::DownsamplingModule& m_module;
};

inline DecimationFeature::DecimationFeature(detail::DownsamplingModule& module)
    : m_module(module)
{}

inline void DecimationFeature::SetEnabled(bool enabled)
{
    m_module.SetEnabled(enabled);
}

inline bool DecimationFeature::IsEnabled() const
{
    return m_module.IsEnabled();
}

inline void DecimationFeature::ResetToDefault()
{
    m_module.ResetToDefault();
}

inline void DecimationFeature::SetX(uint32_t x)
{
    try
    {
        m_module.SetX(x);
    }
    catch (const peak::icv::OutOfRangeException&)
    {
        const auto range = m_module.GetRange();
        throw peak::icv::OutOfRangeException("The specified decimation factor " + std::to_string(x)
            + " is incorrect; the expected value must be between " + std::to_string(range.GetMinimum()) + " and "
            + std::to_string(range.GetMaximum()) + ".");
    }
}

inline void DecimationFeature::SetY(uint32_t y)
{
    try
    {
        m_module.SetY(y);
    }
    catch (const peak::icv::OutOfRangeException&)
    {
        const auto range = m_module.GetRange();
        throw peak::icv::OutOfRangeException("The specified decimation factor " + std::to_string(y)
            + " is incorrect; the expected value must be between " + std::to_string(range.GetMinimum()) + " and "
            + std::to_string(range.GetMaximum()) + ".");
    }
}

inline uint32_t DecimationFeature::GetX() const
{
    return m_module.GetX();
}

inline uint32_t DecimationFeature::GetY() const
{
    return m_module.GetY();
}

inline peak::common::IntervalU DecimationFeature::GetRange() const
{
    return m_module.GetRange();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
