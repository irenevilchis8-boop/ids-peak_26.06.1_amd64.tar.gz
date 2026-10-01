/*!
 * \file    peak_icv_binning_feature.hpp
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
#include <peak_icv/pipeline/types/peak_icv_binning_mode.hpp>

namespace peak
{
namespace pipeline
{
namespace features
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_features
 *
 * \brief Binning is used to decrease the image size.
 *
 * This method reduces resolution by summarizing or averaging groups of pixels
 * in the horizontal (x) and/or vertical (y) directions.
 * It helps preserve image quality by minimizing aliasing artifacts.
 *
 * \note Processes the entire image, ignoring any specified image region.
 * The alpha channel of the input image (if present) is also ignored.
 * This is because the alpha channel can have different interpretations — such as transparency, segmentation labels, or masks — each of
 * which would require different handling during binning.
 * Consequently, the alpha channel of the output image is always set to the maximum possible pixel value.
 *
 * \warning Binning permanently reduces image resolution. The original resolution cannot be recovered
 *          after binning is applied.
 *
 * \defaults{defaults_feature_binning|
 *   - x = 1
 *   - y = 1
 *   - peak::pipeline::detail::DownsamplingMode::BinningAverage
 * }
 *
 * \see \ref features::DecimationFeature, \ref BinningMode
 *
 * \since ids_peak_icv 1.0
 */
class BinningFeature : public IFeature
{
public:
    /*!
     * \brief Creates a BinningFeature for an existing downsampling module.
     *
     * \param module Reference to the underlying \ref detail::DownsamplingModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit BinningFeature(detail::DownsamplingModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets all settings to the \ref defaults_feature_binning "default values".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the number of columns used for binning.
     *
     * \param x An integer value representing the number of columns summarized/averaged during binning.
     *          Valid values are within the range returned by \ref GetRange.
     *
     * \throws OutOfRangeException  If \p x is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetX(uint32_t x);

    /*!
     * \brief Sets the number of rows used for binning.
     *
     * \param y An integer value representing the number of rows summarized/averaged during binning.
     *          Valid values are within the range returned by \ref GetRange.
     *
     * \throws OutOfRangeException  If \p y is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetY(uint32_t y);

    /*!
     * \brief Gets the current number of columns used for binning.
     *
     * \returns The current number of columns summarized/averaged during binning.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetX() const;

    /*!
     * \brief Gets the current number of rows used for binning.
     *
     * \returns The current number of rows summarized/averaged during binning.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetY() const;

    /*!
     * \brief Gets the valid range for the binning factors x and y.
     *
     * The returned interval specifies the minimum and maximum values that can be passed to \ref SetX or \ref SetY.
     *
     * \returns An IntervalU representing the valid binning factor range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalU GetRange() const;

    /*!
     * \brief Sets the \ref BinningMode.
     *
     * \param mode The \ref BinningMode to set.
     *
     * \throws NotSupportedException  If the \p mode is an unsupported \ref BinningMode.
     *
     * \since ids_peak_icv 1.0
     */
    void SetMode(const BinningMode& mode);

    /*!
     * \brief Gets the current \ref BinningMode.
     *
     * \returns The current \ref BinningMode.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD BinningMode GetMode() const;

private:
    detail::DownsamplingModule& m_module;
};

inline BinningFeature::BinningFeature(detail::DownsamplingModule& module)
    : m_module(module)
{}

inline void BinningFeature::SetEnabled(bool enabled)
{
    m_module.SetEnabled(enabled);
}

inline bool BinningFeature::IsEnabled() const
{
    return m_module.IsEnabled();
}

inline void BinningFeature::ResetToDefault()
{
    m_module.ResetToDefault();
}

inline void BinningFeature::SetX(uint32_t x)
{
    try
    {
        m_module.SetX(x);
    }
    catch (const peak::icv::OutOfRangeException&)
    {
        const auto range = m_module.GetRange();
        throw peak::icv::OutOfRangeException("The specified binning factor " + std::to_string(x)
            + " is incorrect; the expected value must be between " + std::to_string(range.GetMinimum()) + " and "
            + std::to_string(range.GetMaximum()) + ".");
    }
}

inline void BinningFeature::SetY(uint32_t y)
{
    try
    {
        m_module.SetY(y);
    }
    catch (const peak::icv::OutOfRangeException&)
    {
        const auto range = m_module.GetRange();
        throw peak::icv::OutOfRangeException("The specified binning factor " + std::to_string(y)
            + " is incorrect; the expected value must be between " + std::to_string(range.GetMinimum()) + " and "
            + std::to_string(range.GetMaximum()) + ".");
    }
}

inline uint32_t BinningFeature::GetX() const
{
    return m_module.GetX();
}

inline uint32_t BinningFeature::GetY() const
{
    return m_module.GetY();
}

inline peak::common::IntervalU BinningFeature::GetRange() const
{
    return m_module.GetRange();
}

inline void BinningFeature::SetMode(const BinningMode& mode)
{
    if (mode != BinningMode::Sum && mode != BinningMode::Average)
    {
        throw peak::icv::NotSupportedException("The binning mode is not supported");
    }
    try
    {
        m_module.SetMode(static_cast<detail::DownsamplingMode>(mode));
    }
    catch (const peak::icv::NotSupportedException&)
    {
        throw peak::icv::NotSupportedException("The binning mode is not supported");
    }
}

inline BinningMode BinningFeature::GetMode() const
{
    return static_cast<BinningMode>(m_module.GetMode());
}

} // namespace features
} // namespace pipeline 
} // namespace peak
