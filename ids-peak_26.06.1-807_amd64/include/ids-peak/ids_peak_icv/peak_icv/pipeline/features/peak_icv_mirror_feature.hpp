/*!
 * \file    peak_icv_mirror_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/pipeline/detail/peak_icv_transformation_module.hpp>
#include <peak_icv/pipeline/features/peak_icv_ifeature.hpp>
#include <peak_icv/pipeline/types/peak_icv_rotation.hpp>

namespace peak
{
namespace pipeline
{
namespace features
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_features
 *
 * \brief Mirror provides functionality to flip the image left-right or up-down.
 *
 * \note  When processing images with a Bayer pattern, the result may have a different pixel format, though the bit depth remains unchanged.
 *        Ensure your application can handle potential pixel format changes after mirroring.
 *
 * \defaults{defaults_feature_mirror|
 *   - no mirroring
 * }
 *
 * \since ids_peak_icv 1.0
 */
class MirrorFeature : public IFeature
{
public:
    /*!
     * \brief Creates a MirrorFeature for an existing transformation module.
     *
     * \param module Reference to the underlying \ref detail::TransformationModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit MirrorFeature(detail::TransformationModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the mirroring to the \ref defaults_feature_mirror "default value".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets whether the image should be mirrored left-right.
     *
     * \param enabled If true, the image will be mirrored along the vertical axis.
     *
     * \since ids_peak_icv 1.0
     */
    void SetLeftRightEnabled(bool enabled);

    /*!
     * \brief Sets whether the image should be mirrored up-down.
     *
     * \param enabled If true, the image will be mirrored along the horizontal axis.
     *
     * \since ids_peak_icv 1.0
     */
    void SetUpDownEnabled(bool enabled);

    /*!
     * \brief Gets the current left-right mirroring setting.
     *
     * \return True if left-right mirroring is enabled so that left and right will be flipped.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD bool IsLeftRightEnabled() const;

    /*!
     * \brief Gets the current up-down mirroring setting.
     *
     * \return True if up-down mirroring is enabled so that up and down will be flipped.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD bool IsUpDownEnabled() const;

private:
    detail::TransformationModule& m_module;
};

inline MirrorFeature::MirrorFeature(detail::TransformationModule& module)
    : m_module(module)
{}

inline void MirrorFeature::SetEnabled(bool enabled)
{
    m_module.SetMirrorEnabled(enabled);
}

inline bool MirrorFeature::IsEnabled() const
{
    return m_module.IsMirrorEnabled();
}

inline void MirrorFeature::ResetToDefault()
{
    m_module.SetMirrorLeftRightEnabled(false);
    m_module.SetMirrorUpDownEnabled(false);
}

inline void MirrorFeature::SetLeftRightEnabled(bool enabled)
{
    m_module.SetMirrorLeftRightEnabled(enabled);
}

inline void MirrorFeature::SetUpDownEnabled(bool enabled)
{
    m_module.SetMirrorUpDownEnabled(enabled);
}

inline bool MirrorFeature::IsLeftRightEnabled() const
{
    return m_module.IsMirrorLeftRightEnabled();
}

inline bool MirrorFeature::IsUpDownEnabled() const
{
    return m_module.IsMirrorUpDownEnabled();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
