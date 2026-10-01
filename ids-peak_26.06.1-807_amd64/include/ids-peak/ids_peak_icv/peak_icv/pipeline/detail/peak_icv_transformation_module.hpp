/*!
 * \file    peak_icv_transformation_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_icv/pipeline/detail/peak_icv_pipeline_utils.hpp>
#include <peak_icv/pipeline/types/peak_icv_rotation.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_image_transformation.h>

namespace peak
{
namespace pipeline
{

namespace features
{
class MirrorFeature;
class RotationFeature;
} // namespace features

namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Transformation is an image pipeline module that provides mirror and rotation functionality.
 *
 * \see \ref features::MirrorFeature and \ref features::RotationFeature
 */
class TransformationModule : public modules::IModule
{
public:
    /*!
     * \brief Creates a TransformationModule module with default values for
     *        \ref defaults_feature_mirror "mirror" and
     *        \ref defaults_feature_rotation "rotation".
     *
     * \since ids_peak_icv 1.0
     */
    TransformationModule() = default;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~TransformationModule() override = default;

    /*!
     * \brief Copy constructor for class TransformationModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    TransformationModule(const TransformationModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    TransformationModule(TransformationModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class TransformationModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    TransformationModule& operator=(const TransformationModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    TransformationModule& operator=(TransformationModule&& other) noexcept;

    /*!
     * \brief Serializes the object's internal state into the provided archive.
     *
     * This function populates the given \p archive with all parameters required to fully represent the current state of the object.
     * It ensures that the object can be reconstructed or transmitted accurately by saving all relevant data members
     * in a consistent and structured format.
     *
     * \param archive The target archive that will store the serialized parameters.
     *
     * \since ids_peak_icv 1.0
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override;

    /*!
     * \brief Restores the object's state from the provided archive.
     *
     * This function reads and applies all necessary parameters from the given \p archive to reconstruct the internal state of the object.
     * It ensures that the object is restored to a valid and consistent state.
     *
     * \param archive The source archive containing the serialized parameters.
     *
     * \throws CorruptedException If Archive is malformed, misses keys or the values are invalid
     * \throws NotSupportedException If the 'Version' entry indicates an unsupported version or if the rotation angle is not transformable
     * into peak::pipeline::Rotation.
     *
     * \note This function requires that the archive contains all expected fields as produced by a corresponding Serialize() call.
     *
     * \since ids_peak_icv 1.0
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override;

    /*!
     * \brief Enables or disables the module.
     *
     * \param enabled Set to \c true to enable, or \c false to disable.
     *
     * \since ids_peak_icv 1.0
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \brief Gets whether this module is currently enabled.
     *
     * \return \c true if enabled; otherwise \c false.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Returns the type of the module for serialization purposes.
     *
     * \returns A string representing the module's type.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD const char* GetType() const override;

    /*!
     * \brief Resets all settings to the default values for
     *        \ref defaults_feature_mirror "mirror" and
     *        \ref defaults_feature_rotation "rotation".
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
    void SetMirrorLeftRightEnabled(bool enabled);

    /*!
     * \brief Sets whether the image should be mirrored up-down.
     *
     * \param enabled If true, the image will be mirrored along the horizontal axis.
     *
     * \since ids_peak_icv 1.0
     */
    void SetMirrorUpDownEnabled(bool enabled);

    /*!
     * \brief Gets the current left-right mirroring setting.
     *
     * \return True if left-right mirroring is enabled so that left and right will be flipped.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD bool IsMirrorLeftRightEnabled() const;

    /*!
     * \brief Gets the current up-down mirroring setting.
     *
     * \return True if up-down mirroring is enabled so that up and down will be flipped.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD bool IsMirrorUpDownEnabled() const;

    /*!
     * \brief Sets the desired rotation angle.
     *
     * \param angle The rotation angle to apply (see Rotation enum).
     *
     * \since ids_peak_icv 1.0
     */
    void SetRotationAngle(Rotation angle);

    /*!
     * \brief Gets the current rotation angle.
     *
     * \return The currently configured rotation angle.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD Rotation GetRotationAngle() const;

    /*!
     * \brief Processes the input image and returns a mirrored and/or rotated copy based on current settings.
     *
     * \supportedPixelformats{ImageTransformation}
     *
     * \note  When processing images with a Bayer pattern, the result may have a different pixel format,
     *        though the bit depth remains unchanged.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed.
     *
     * \returns A new image object that is the transformed result of the input.
     *
     * \throws NotSupportedException  If \p image has any other than the supported pixel formats.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Processes the input image and returns a mirrored and/or rotated copy based on current settings.
     *
     * \supportedPixelformats{ImageTransformation}
     *
     * \note  When processing images with a Bayer pattern, the result may have a different pixel format,
     *        though the bit depth remains unchanged.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed.
     *
     * \returns A new image object that is the transformed result of the input.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     * \throws NotSupportedException  If \p image has any other than the supported pixel formats.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

private:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    friend class features::MirrorFeature;
    friend class features::RotationFeature;
#endif

    void SetMirrorEnabled(bool enabled);
    PEAK_COMMON_NO_DISCARD bool IsMirrorEnabled() const;

    void SetRotationEnabled(bool enabled);
    PEAK_COMMON_NO_DISCARD bool IsRotationEnabled() const;

    static constexpr int moduleVersion{ 1 };
    static constexpr auto mirrorKey{ "Mirror" };
    static constexpr auto rotationKey{ "Rotation" };
    static constexpr auto mirrorLeftRightKey{ "LeftRight" };
    static constexpr auto mirrorUpDownKey{ "UpDown" };
    static constexpr auto rotationAngleKey{ "Angle" };
    static constexpr Rotation defaultRotation{ Rotation::None };

    bool m_leftRight{ false };
    bool m_upDown{ false };
    Rotation m_angle{ defaultRotation };

    bool m_mirrorEnabled{ true };
    bool m_rotationEnabled{ true };
};

inline void TransformationModule::SetEnabled(bool enabled)
{
    m_mirrorEnabled = enabled;
    m_rotationEnabled = enabled;
}

inline bool TransformationModule::IsEnabled() const
{
    return m_mirrorEnabled || m_rotationEnabled;
}

inline const char* TransformationModule::GetType() const
{
    return "TransformationModule";
}

inline TransformationModule::TransformationModule(TransformationModule&& other) noexcept
{
    m_leftRight = other.m_leftRight;
    m_upDown = other.m_upDown;
    m_angle = other.m_angle;
    m_mirrorEnabled = other.m_mirrorEnabled;
    m_rotationEnabled = other.m_rotationEnabled;
}

inline TransformationModule& TransformationModule::operator=(TransformationModule&& other) noexcept
{
    if (this != &other)
    {
        m_leftRight = other.m_leftRight;
        m_upDown = other.m_upDown;
        m_angle = other.m_angle;
        m_mirrorEnabled = other.m_mirrorEnabled;
        m_rotationEnabled = other.m_rotationEnabled;
    }

    return *this;
}

inline void TransformationModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetInt("Version", moduleVersion);

    const auto mirrorArchive = archive.CreateArchive();
    const auto rotationArchive = archive.CreateArchive();

    mirrorArchive->SetBool("Enabled", m_mirrorEnabled);
    rotationArchive->SetBool("Enabled", m_rotationEnabled);

    mirrorArchive->SetBool(mirrorLeftRightKey, m_leftRight);
    mirrorArchive->SetBool(mirrorUpDownKey, m_upDown);

    rotationArchive->SetInt(rotationAngleKey, static_cast<int64_t>(m_angle));

    archive.SetArchive(mirrorKey, mirrorArchive);
    archive.SetArchive(rotationKey, rotationArchive);
}

inline void TransformationModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");
    detail::ValidateVersion(version, GetType());

    const auto mirrorArchive = archive.GetArchive(mirrorKey);
    const auto rotationArchive = archive.GetArchive(rotationKey);
    const auto rotation = rotationArchive->GetInt(rotationAngleKey);
    if (rotation != 0 && rotation != 90 && rotation != 180 && rotation != 270)
    {
        throw peak::icv::NotSupportedException("The given rotation angle " + std::to_string(rotation) + " is invalid!");
    }

    m_mirrorEnabled = mirrorArchive->GetBool("Enabled");
    m_rotationEnabled = rotationArchive->GetBool("Enabled");

    m_leftRight = mirrorArchive->GetBool(mirrorLeftRightKey);
    m_upDown = mirrorArchive->GetBool(mirrorUpDownKey);

    m_angle = static_cast<Rotation>(rotation);
}

inline void TransformationModule::ResetToDefault()
{
    m_leftRight = false;
    m_upDown = false;
    m_angle = defaultRotation;
}

inline void TransformationModule::SetMirrorLeftRightEnabled(bool enabled)
{
    m_leftRight = enabled;
}

inline void TransformationModule::SetMirrorUpDownEnabled(bool enabled)
{
    m_upDown = enabled;
}

inline bool TransformationModule::IsMirrorLeftRightEnabled() const
{
    return m_leftRight;
}

inline bool TransformationModule::IsMirrorUpDownEnabled() const
{
    return m_upDown;
}

inline void TransformationModule::SetRotationAngle(Rotation angle)
{
    if (static_cast<uint32_t>(angle) % 90 != 0 || static_cast<uint32_t>(angle) > 270)
    {
        throw peak::icv::NotSupportedException("The given rotation angle is not supported.");
    }
    m_angle = angle;
}

inline Rotation TransformationModule::GetRotationAngle() const
{
    return m_angle;
}

inline peak::icv::Image TransformationModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any TransformationModule::Process(const peak::common::Any& input) const
{
    const auto mirrorNeedsProcessing = m_mirrorEnabled && (m_leftRight || m_upDown);
    const auto rotationNeedsProcessing = m_rotationEnabled && (m_angle != Rotation::None);

    if (!mirrorNeedsProcessing && !rotationNeedsProcessing)
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();

    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(inputImage);

    const peak_icv_preprocessing_transformation_parameters parameters{ m_mirrorEnabled && m_leftRight, m_mirrorEnabled && m_upDown,
        m_rotationEnabled ? static_cast<peak_icv_preprocessing_transformation_rotation_angle>(m_angle) :
                            PEAK_ICV_PREPROCESSING_TRANSFORMATION_ROTATION_NONE };

    peak_common_pixel_format outputPixelFormat;

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Transformation_GetOutputPixelFormat(
            peak::common::detail::CppPixelFormatToCPixelFormat(inputImage.GetPixelFormat()), parameters, &outputPixelFormat);
    });

    const auto transpose = m_rotationEnabled && (m_angle == Rotation::Degree90Clockwise || m_angle == Rotation::Degree90Counterclockwise);
    const auto outputSize = transpose ? inputImage.GetSize().Transposed() : inputImage.GetSize();
    peak::icv::Image outputImage = peak::common::detail::BackendAccessor<peak::icv::Image>::CreateInstance(
        peak::common::detail::CPixelFormatToCppPixelFormat(outputPixelFormat), outputSize, false);
    auto* const outputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(outputImage);

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Transformation_Process(inputImageHandle, parameters, outputImageHandle);
    });

    return peak::common::Any(outputImage);
}

inline void TransformationModule::SetMirrorEnabled(bool enabled)
{
    m_mirrorEnabled = enabled;
}

inline bool TransformationModule::IsMirrorEnabled() const
{
    return m_mirrorEnabled;
}

inline void TransformationModule::SetRotationEnabled(bool enabled)
{
    m_rotationEnabled = enabled;
}

inline bool TransformationModule::IsRotationEnabled() const
{
    return m_rotationEnabled;
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
