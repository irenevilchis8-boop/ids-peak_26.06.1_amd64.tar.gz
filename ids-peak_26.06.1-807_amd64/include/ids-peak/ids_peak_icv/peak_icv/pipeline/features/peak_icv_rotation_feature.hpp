/*!
 * \file    peak_icv_rotation_feature.hpp
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
 * \brief Rotation provides fixed-angle rotation functionality.
 *
 * This feature rotates images in 90-degree increments, based on the rotation mode set via the \ref RotationFeature::SetAngle method.
 *
 * \warning When processing images with a Bayer pattern, the result may have a different pixel format, though the bit depth remains unchanged.
 *          Ensure your application can handle potential pixel format changes after rotation.
 *
 * \defaults{defaults_feature_rotation|
 *   - Rotation::None
 * }
 *
 * \see \ref Rotation, \ref features::MirrorFeature
 *
 * \since ids_peak_icv 1.0
 */
class RotationFeature : public IFeature
{
public:
    /*!
     * \brief Creates a RotationFeature for an existing transformation module.
     *
     * \param module Reference to the underlying \ref detail::TransformationModule.
     *
     * \since ids_peak_icv 1.0
     */
    explicit RotationFeature(detail::TransformationModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the rotation to the \ref defaults_feature_rotation "default value"
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the desired rotation angle.
     *
     * \param angle The rotation angle to apply (see Rotation enum).
     *
     * \since ids_peak_icv 1.0
     */
    void SetAngle(Rotation angle);

    /*!
     * \brief Gets the current rotation angle.
     *
     * \return The currently configured rotation angle.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD Rotation GetAngle() const;

private:
    detail::TransformationModule& m_module;
};

inline RotationFeature::RotationFeature(detail::TransformationModule& module)
    : m_module(module)
{}

inline void RotationFeature::SetEnabled(bool enabled)
{
    m_module.SetRotationEnabled(enabled);
}

inline bool RotationFeature::IsEnabled() const
{
    return m_module.IsRotationEnabled();
}

inline void RotationFeature::ResetToDefault()
{
    m_module.SetRotationAngle(detail::TransformationModule::defaultRotation);
}

inline void RotationFeature::SetAngle(Rotation angle)
{
    m_module.SetRotationAngle(angle);
}

inline Rotation RotationFeature::GetAngle() const
{
    return m_module.GetRotationAngle();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
