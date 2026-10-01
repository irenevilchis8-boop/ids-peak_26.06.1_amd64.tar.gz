/*!
 * \file    peak_icv_hotpixel_correction_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/pipeline/detail/peak_icv_hotpixel_correction_module.hpp>
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
 * \brief HotpixelCorrection detects and corrects hot pixels in camera images.
 *
 * The HotpixelCorrection class is responsible for identifying and correcting defective pixels that consistently
 * report higher-than-expected intensity values.
 *
 * It allows fine-tuning of the detection sensitivity and management of a hot pixel
 * correction list, which is applied during image processing through the Process() method.
 *
 * \since ids_peak_icv 1.0
 */
class HotpixelCorrectionFeature : public IFeature
{
public:
    using HotpixelList = std::vector<peak::common::Point>;

    /*!
     * \brief Creates a HotpixelCorrectionFeature for an existing hotpixel correction module.
     *
     * \param module Reference to the underlying \ref detail::HotpixelCorrectionModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit HotpixelCorrectionFeature(detail::HotpixelCorrectionModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Clears the hot pixel list.
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the list of known hot pixels.
     *
     * \param hotpixels A vector of hot pixel positions to use.
     *
     * \since ids_peak_icv 1.0
     */
    void SetList(const HotpixelList& hotpixels);

    /*!
     * \brief Retrieves the current list of known hot pixels.
     *
     * \return A vector containing the positions of all configured hot pixels.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD HotpixelList GetList() const;

    /*!
     * \brief Retrieves the valid range for the detection sensitivity.
     *
     * The returned interval specifies the minimum and maximum sensitivity values that can be passed to the \ref Detect function.
     *
     * \return An IntervalU representing the valid sensitivity range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalU GetSensitivityRange() const;

    /*!
     * \brief Performs immediate hot pixel detection on the given image.
     *
     * This method analyzes the provided image and detects hot pixels based on the
     * sensitivity setting. The results are stored internally and can be accessed using GetList().
     *
     * \param image                 The input image to analyze for hot pixel detection.
     * \param sensitivity           Sensitivity for hot pixel detection. A higher sensitivity
     *                              may result in detecting more hot pixels, including possible
     *                              false positives.
     * \param gainFactor            Gain factor applied to the image. Used to account for
     *                              increased noise levels when detecting hot pixels.
     *
     * \note Calling this function will overwrite any existing hot pixel list previously set via SetList().
     *
     * \since ids_peak_icv 1.0
     */
    void Detect(const peak::icv::Image& image, uint32_t sensitivity = 3, float gainFactor = 1.0F);

private:
    detail::HotpixelCorrectionModule& m_module;
};

inline HotpixelCorrectionFeature::HotpixelCorrectionFeature(detail::HotpixelCorrectionModule& module)
    : m_module(module)
{}

inline void HotpixelCorrectionFeature::SetEnabled(bool enabled)
{
    m_module.SetEnabled(enabled);
}

inline bool HotpixelCorrectionFeature::IsEnabled() const
{
    return m_module.IsEnabled();
}

inline void HotpixelCorrectionFeature::ResetToDefault()
{
    m_module.ResetToDefault();
}

inline void HotpixelCorrectionFeature::SetList(const HotpixelList& hotpixels)
{
    m_module.SetList(hotpixels);
}

inline HotpixelCorrectionFeature::HotpixelList HotpixelCorrectionFeature::GetList() const
{
    return m_module.GetList();
}

inline peak::common::IntervalU HotpixelCorrectionFeature::GetSensitivityRange() const
{
    return m_module.GetSensitivityRange();
}

inline void HotpixelCorrectionFeature::Detect(const peak::icv::Image& image, uint32_t sensitivity, float gainFactor)
{
    m_module.Detect(image, sensitivity, gainFactor);
}

} // namespace features
} // namespace pipeline 
} // namespace peak
