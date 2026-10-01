/*!
 * \file    peak_icv_color_matrix_transformation_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_iautofeature_module.hpp>
#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_common/types/peak_common_range.hpp>
#include <peak_icv/pipeline/detail/peak_icv_pipeline_utils.hpp>
#include <peak_icv/pipeline/types/peak_icv_chromatic_adaption_algorithm.hpp>
#include <peak_icv/pipeline/types/peak_icv_color_correction_matrix.hpp>
#include <peak_icv/pipeline/types/peak_icv_color_space.hpp>
#include <peak_icv/types/peak_icv_image.hpp>

namespace peak
{
namespace pipeline
{
namespace features
{
class ChromaticAdaptionFeature;
class SaturationFeature;
class ColorCorrectionFeature;
} // namespace features

namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Color matrix transformation is an image pipeline module that applies a \ref ColorCorrectionMatrix to an image.
 *
 * Provides the features \ref features::ColorCorrectionFeature, \ref features::SaturationFeature and \ref features::ChromaticAdaptionFeature
 *
 * Default configuration:
 *   - Color correction matrix = 3x3 identity matrix
 *   - Saturation = 1.0
 *
 * \since ids_peak_icv 1.0
 */
class ColorMatrixTransformationModule : public modules::IModule
{
public:
    /*!
     * \brief Creates an instance of class ColorMatrixTransformationModule with the default
     *        \ref defaults_feature_colorcorrection "color correction matrix",
     *        \ref defaults_feature_saturation "saturation value" and \ref defaults_feature_chromaticadaption "chromatic adaption value".
     *
     * \since ids_peak_icv 1.0
     */
    ColorMatrixTransformationModule();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~ColorMatrixTransformationModule() override;

    /*!
     * \brief Copy constructor for class ColorMatrixTransformation is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    ColorMatrixTransformationModule(const ColorMatrixTransformationModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ColorMatrixTransformationModule(ColorMatrixTransformationModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class ColorMatrixTransformation is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    ColorMatrixTransformationModule& operator=(const ColorMatrixTransformationModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ColorMatrixTransformationModule& operator=(ColorMatrixTransformationModule&& other) noexcept;

    /*!
     * \brief Serializes the object's internal state into the provided archive.
     *
     * This function populates the given \p archive with all parameters required to  fully represent the current state of the object.
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
     * \throws NotSupportedException If the 'Version' entry indicates an unsupported version.
     *
     * \note This function requires that the archive contains all expected fields as produced by a corresponding Serialize() call.
     *
     * \since ids_peak_icv 1.0
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override;

    /*!
     * \brief Enables or disables the module.
     * When disabled, \ref Process returns the input image unchanged.
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
     * When disabled, \ref Process returns the input image unchanged.
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
     * \brief Resets the \ref ColorCorrectionMatrix to the \ref defaults_feature_colorcorrection "default",
     * the chromatic adaption color space and algorithm to the \ref defaults_feature_chromaticadaption "default"
     * and the saturation value to the \ref defaults_feature_saturation "default".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the \ref ColorCorrectionMatrix.
     *
     * \param matrix The \ref ColorCorrectionMatrix.
     *
     * \since ids_peak_icv 1.0
     */
    void SetMatrix(const ColorCorrectionMatrix& matrix);

    /*!
     * \brief Gets the current \ref ColorCorrectionMatrix.
     *
     * \returns The current \ref ColorCorrectionMatrix.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD ColorCorrectionMatrix GetMatrix() const;

    /*!
     * \brief Sets the saturation value.
     *
     * \param saturation The saturation value.
     *
     * \throws OutOfRangeException  If \p saturation is outside the valid range (see \ref GetSaturationRange).
     *
     * \since ids_peak_icv 1.0
     */
    void SetSaturation(float saturation);

    /*!
     * \brief Gets the current saturation value.
     *
     * \returns The current saturation value.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetSaturation() const;

    /*!
     * \brief Gets the valid range for saturation.
     *
     * \returns The valid saturation range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetSaturationRange() const;

    /*!
     * \brief Processes the input image and returns a color corrected and/or saturated output image.
     *
     * \note Supported pixel formats: RGB8, RGB10, RGB12, BGR8, BGR10, BGR12, RGBa8, RGBa10, RGBa12, BGRa8, BGRa10, BGRa12.
     *       Images with other formats are passed through unmodified.
     *
     * Images with other formats are passed through unmodified.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed.
     *
     * \returns The input image after in-place color correction and/or saturation has been applied.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Processes the input image and returns a color corrected and/or saturated output image.
     *
     * \note Supported pixel formats: RGB8, RGB10, RGB12, BGR8, BGR10, BGR12, RGBa8, RGBa10, RGBa12, BGRa8, BGRa10, BGRa12.
     *       Images with other formats are passed through unmodified.
     *
     * Images with other formats are passed through unmodified.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed.
     *
     * \returns The input image after in-place color correction and/or saturation has been applied.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

    /*!
     * \brief Sets the auto feature module that should take the color correction matrix into account for automatic white balancing.
     *
     * \since ids_peak_icv 1.0
     */
    void SetAutoFeatureModule(const std::shared_ptr<modules::IAutoFeature>& module);

    /*!
     * \brief Returns the final effective matrix calculated by concatenating all enabled transformations
     * (e.g., Chromatic Adaptation, Color Correction, and Saturation).
     *
     * \returns The combined effective \ref ColorCorrectionMatrix.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD ColorCorrectionMatrix GetEffectiveMatrix() const;

    /*!
     * \brief Sets the algorithm used to calculate the chromatic adaptation transformation.
     *
     * \param algorithm The \ref ChromaticAdaptionAlgorithm to apply.
     *
     * \since ids_peak_icv 1.3
     */
    void SetChromaticAdaptionAlgorithm(ChromaticAdaptionAlgorithm algorithm);

    /*!
     * \brief Returns the current algorithm used for chromatic adaptation.
     *
     * \returns The active \ref ChromaticAdaptionAlgorithm.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD ChromaticAdaptionAlgorithm GetChromaticAdaptionAlgorithm() const;

    /*!
     * \brief Sets the target color space for the chromatic adaptation transformation.
     *
     * \param colorSpace The target \ref ColorSpace.
     *
     * \since ids_peak_icv 1.3
     */
    void SetTargetColorSpace(ColorSpace colorSpace);

    /*!
     * \brief Returns the target color space used for chromatic adaptation.
     *
     * \returns The current target \ref ColorSpace.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD ColorSpace GetTargetColorSpace() const;

    /*!
     * \brief Sets the source color temperature in Kelvin to be used for chromatic adaptation.
     *
     * \param temperature The color temperature value in Kelvin.
     *
     * \since ids_peak_icv 1.3
     */
    void SetColorTemperature(uint32_t temperature);

    /*!
     * \brief Returns the currently configured source color temperature in Kelvin.
     *
     * \returns The color temperature value in Kelvin.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetColorTemperature() const;

    /*!
     * \brief Returns the valid range of values for color temperature.
     *
     * \returns A \ref peak::common::RangeU denoting the min and max allowed temperature values.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU GetColorTemperatureRange() const;

    /*!
     * \brief Resets the color temperature to its default, uninitialized state.
     *
     * \since ids_peak_icv 1.3
     */
    void ResetColorTemperature() const;

    /*!
     * \brief Checks if a specific color temperature has been explicitly set.
     *
     * \returns True if a color temperature is configured, false otherwise.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD bool HasColorTemperature() const;

    /*!
     * \brief Enables or disables the chromatic adaptation feature.
     *
     * \param enabled True to enable chromatic adaptation, false to disable it.
     *
     * \since ids_peak_icv 1.3
     */
    void SetChromaticAdaptionEnabled(bool enabled);

    /*!
     * \brief Checks if the chromatic adaptation feature is enabled.
     *
     * \returns True if chromatic adaptation is currently active, false otherwise.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD bool IsChromaticAdaptionEnabled() const;

    /*!
     * \brief Enables or disables the saturation adjustment feature.
     *
     * \param enabled True to enable saturation adjustment, false to disable it.
     *
     * \since ids_peak_icv 1.3
     */
    void SetSaturationEnabled(bool enabled);

    /*!
     * \brief Checks if the saturation adjustment feature is enabled.
     *
     * \returns True if saturation adjustment is currently active, false otherwise.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD bool IsSaturationEnabled() const;

    /*!
     * \brief Enables or disables the static color correction matrix feature.
     *
     * \param enabled True to enable color correction, false to disable it.
     *
     * \since ids_peak_icv 1.3
     */
    void SetColorCorrectionEnabled(bool enabled);

    /*!
     * \brief Checks if the static color correction matrix feature is enabled.
     *
     * \returns True if color correction is currently active, false otherwise.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD bool IsColorCorrectionEnabled() const;

    /*!
     * \brief Resets all chromatic adaptation settings (temperature, algorithm, color space) to their default values.
     *
     * \since ids_peak_icv 1.3
     */
    void ResetChromaticAdaption();

private:
    void UpdateMatrixInAutoFeatureModule() const;

    static constexpr auto saturationKey = "Saturation";
    static constexpr auto matrixKey = "ColorCorrection";
    static constexpr auto chromaticAdaptionKey = "ChromaticAdaption";

    peak_icv_color_matrix_transformation_handle m_handle{};

    std::shared_ptr<modules::IAutoFeature> m_autoFeatureModule;
};

inline ColorMatrixTransformationModule::ColorMatrixTransformationModule()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_Create(&m_handle);
    });
}

inline ColorMatrixTransformationModule::~ColorMatrixTransformationModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_Destroy(m_handle);
    }
}

inline ColorMatrixTransformationModule::ColorMatrixTransformationModule(ColorMatrixTransformationModule&& other) noexcept
{
    m_handle = std::exchange(other.m_handle, nullptr);
}

inline ColorMatrixTransformationModule& ColorMatrixTransformationModule::operator=(ColorMatrixTransformationModule&& other) noexcept
{
    if (this != &other)
    {
        if (m_handle != nullptr)
        {
            peak::icv::detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_Destroy(m_handle);
            });
        }

        m_handle = std::exchange(other.m_handle, nullptr);
    }

    return *this;
}

inline void ColorMatrixTransformationModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetInt("Version", 2);

    const auto saturationArchive = archive.CreateArchive();
    saturationArchive->SetBool("Enabled", IsSaturationEnabled());
    saturationArchive->SetDouble("Value", GetSaturation());
    archive.SetArchive(saturationKey, saturationArchive);

    const auto matrixArchive = archive.CreateArchive();
    matrixArchive->SetBool("Enabled", IsColorCorrectionEnabled());

    const auto colorCorrectionMatrix = GetMatrix();
    colorCorrectionMatrix.Serialize(*matrixArchive);
    archive.SetArchive(matrixKey, matrixArchive);

    const auto chromaticAdaption = archive.CreateArchive();
    chromaticAdaption->SetBool("Enabled", IsChromaticAdaptionEnabled());
    chromaticAdaption->SetString("Algorithm", ToString(GetChromaticAdaptionAlgorithm()));
    chromaticAdaption->SetString("TargetColorSpace", ToString(GetTargetColorSpace()));
    if (HasColorTemperature())
    {
        chromaticAdaption->SetInt("ColorTemperature", GetColorTemperature());
    }
    archive.SetArchive(chromaticAdaptionKey, chromaticAdaption);
}

inline void ColorMatrixTransformationModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");

    detail::ValidateVersion(version, GetType());

    const auto saturationArchive = archive.GetArchive(saturationKey);
    const auto matrixArchive = archive.GetArchive(matrixKey);

    SetSaturationEnabled(saturationArchive->GetBool("Enabled"));
    SetColorCorrectionEnabled(matrixArchive->GetBool("Enabled"));

    ColorCorrectionMatrix matrix{ "Matrix", ColorCorrectionMatrix::Identity() };
    matrix.Deserialize(*matrixArchive);
    SetMatrix(matrix);

    SetSaturation(static_cast<float>(saturationArchive->GetDouble("Value")));

    if (version >= 2)
    {
        const auto chromaticAdaptionArchive = archive.GetArchive(chromaticAdaptionKey);
        if (chromaticAdaptionArchive->HasKey("ColorTemperature"))
        {
            SetColorTemperature(static_cast<uint32_t>(chromaticAdaptionArchive->GetInt("ColorTemperature")));
        }
        else
        {
            ResetColorTemperature();
        }
        SetTargetColorSpace(ToColorSpace(chromaticAdaptionArchive->GetString("TargetColorSpace")));
        SetChromaticAdaptionAlgorithm(ToChromaticAdaptionAlgorithm(chromaticAdaptionArchive->GetString("Algorithm")));
        SetChromaticAdaptionEnabled(chromaticAdaptionArchive->GetBool("Enabled"));
    }
    else
    {
        ResetChromaticAdaption();
    }
}

inline void ColorMatrixTransformationModule::SetEnabled(bool enabled)
{
    SetColorCorrectionEnabled(enabled);
    SetSaturationEnabled(enabled);
    SetChromaticAdaptionEnabled(enabled);

    UpdateMatrixInAutoFeatureModule();
}

inline bool ColorMatrixTransformationModule::IsEnabled() const
{
    return IsColorCorrectionEnabled() || IsSaturationEnabled() || IsChromaticAdaptionEnabled();
}

inline const char* ColorMatrixTransformationModule::GetType() const
{
    return "ColorMatrixTransformation";
}

inline void ColorMatrixTransformationModule::ResetToDefault()
{
    SetMatrix(ColorCorrectionMatrix::Identity());
    SetSaturation(1.0F);

    ResetChromaticAdaption();

    UpdateMatrixInAutoFeatureModule();
}

inline ColorCorrectionMatrix ColorMatrixTransformationModule::GetMatrix() const
{
    ColorCorrectionMatrix colorCorrectionMatrix{ "Matrix", ColorCorrectionMatrix::Identity() };
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix(
            m_handle, reinterpret_cast<peak_icv_color_correction_matrix*>(&colorCorrectionMatrix.At(0, 0)));
    });

    return colorCorrectionMatrix;
}

inline void ColorMatrixTransformationModule::SetMatrix(const ColorCorrectionMatrix& matrix)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix(
            m_handle, *reinterpret_cast<const peak_icv_color_correction_matrix*>(&matrix.At(0, 0)));
    });

    if (IsColorCorrectionEnabled())
    {
        UpdateMatrixInAutoFeatureModule();
    }
}

inline void ColorMatrixTransformationModule::SetSaturation(float saturation)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation(m_handle, saturation);
    });
    if (IsSaturationEnabled())
    {
        UpdateMatrixInAutoFeatureModule();
    }
}

PEAK_COMMON_NO_DISCARD inline float ColorMatrixTransformationModule::GetSaturation() const
{
    float saturation;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation(m_handle, &saturation);
    });
    return saturation;
}

PEAK_COMMON_NO_DISCARD inline peak::common::IntervalF ColorMatrixTransformationModule::GetSaturationRange() const
{
    peak_common_interval_f intervalF;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange(m_handle, &intervalF);
    });

    return { intervalF.minimum, intervalF.maximum };
}

inline peak::icv::Image ColorMatrixTransformationModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any ColorMatrixTransformationModule::Process(const peak::common::Any& input) const
{
    auto needsProcessing = [&] {
        bool value{};
        peak::icv::detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing(m_handle, &value);
        });
        return value;
    };

    if (!IsEnabled() || !needsProcessing())
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();

    const auto pixelFormat = inputImage.GetPixelFormat();
    const peak::common::PixelFormatInfo info(pixelFormat);
    const auto isColorImage = info.HasChannel(peak::common::Channel::Red) && info.HasChannel(peak::common::Channel::Green)
        && info.HasChannel(peak::common::Channel::Blue);
    if (!isColorImage || info.IsPacked())
    {
        return input;
    }

    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(inputImage);

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace(m_handle, inputImageHandle);
    });

    return peak::common::Any{ inputImage };
}

inline void ColorMatrixTransformationModule::UpdateMatrixInAutoFeatureModule() const
{
    if (m_autoFeatureModule != nullptr)
    {
        std::array<float, 9> data{};

        const auto matrix = GetEffectiveMatrix();
        std::copy(matrix.cbegin(), matrix.cend(), data.begin());

        m_autoFeatureModule->SetColorCorrectionMatrix(data);
    }
}

inline void ColorMatrixTransformationModule::SetAutoFeatureModule(const std::shared_ptr<modules::IAutoFeature>& module)
{
    m_autoFeatureModule = module;
    UpdateMatrixInAutoFeatureModule();
}

inline ColorCorrectionMatrix ColorMatrixTransformationModule::GetEffectiveMatrix() const
{
    ColorCorrectionMatrix matrix{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix(
            m_handle, reinterpret_cast<peak_icv_color_correction_matrix*>(&matrix.At(0, 0)));
    });
    return matrix;
}

inline void ColorMatrixTransformationModule::SetSaturationEnabled(bool enabled)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled(m_handle, enabled);
    });
    UpdateMatrixInAutoFeatureModule();
}

inline void ColorMatrixTransformationModule::SetColorCorrectionEnabled(bool enabled)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled(m_handle, enabled);
    });
    UpdateMatrixInAutoFeatureModule();
}

inline bool ColorMatrixTransformationModule::IsSaturationEnabled() const
{
    bool enabled;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled(m_handle, &enabled);
    });
    return enabled;
}

inline bool ColorMatrixTransformationModule::IsColorCorrectionEnabled() const
{
    bool enabled;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled(m_handle, &enabled);
    });
    return enabled;
}

inline ChromaticAdaptionAlgorithm ColorMatrixTransformationModule::GetChromaticAdaptionAlgorithm() const
{
    peak_icv_chromatic_adaption_algorithm algorithm;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm(m_handle, &algorithm);
    });
    return static_cast<ChromaticAdaptionAlgorithm>(algorithm);
}

inline ColorSpace ColorMatrixTransformationModule::GetTargetColorSpace() const
{
    peak_icv_color_space colorSpace;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace(
            m_handle, &colorSpace);
    });
    return static_cast<ColorSpace>(colorSpace);
}

inline void ColorMatrixTransformationModule::SetChromaticAdaptionAlgorithm(ChromaticAdaptionAlgorithm algorithm)
{
    const auto cAlgorithm = static_cast<peak_icv_chromatic_adaption_algorithm>(algorithm);
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm(m_handle, cAlgorithm);
    });
    UpdateMatrixInAutoFeatureModule();
}

inline void ColorMatrixTransformationModule::SetTargetColorSpace(ColorSpace colorSpace)
{
    const auto cColorSpace = static_cast<peak_icv_color_space>(colorSpace);
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace(
            m_handle, cColorSpace);
    });
    UpdateMatrixInAutoFeatureModule();
}

inline peak::common::RangeU ColorMatrixTransformationModule::GetColorTemperatureRange() const
{
    peak_common_range_u cRange{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange(
            m_handle, &cRange);
    });

    return peak::common::detail::BackendAccessor<peak::common::RangeU>::CreateInstance(
        peak::common::detail::c_type_of_t<peak::common::RangeU>{ cRange });
}

inline void ColorMatrixTransformationModule::SetColorTemperature(const uint32_t temperature)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature(
            m_handle, temperature);
    });
    UpdateMatrixInAutoFeatureModule();
}

inline bool ColorMatrixTransformationModule::HasColorTemperature() const
{
    bool value;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature(
            m_handle, &value);
    });
    return value;
}

inline uint32_t ColorMatrixTransformationModule::GetColorTemperature() const
{
    uint32_t temperature{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature(
            m_handle, &temperature);
    });
    return temperature;
}

inline void ColorMatrixTransformationModule::ResetColorTemperature() const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature(m_handle);
    });
    UpdateMatrixInAutoFeatureModule();
}

inline void ColorMatrixTransformationModule::SetChromaticAdaptionEnabled(const bool enabled)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled(m_handle, enabled);
    });
    UpdateMatrixInAutoFeatureModule();
}

inline bool ColorMatrixTransformationModule::IsChromaticAdaptionEnabled() const
{
    bool enabled;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled(m_handle, &enabled);
    });
    return enabled;
}

inline void ColorMatrixTransformationModule::ResetChromaticAdaption()
{
    ResetColorTemperature();
    SetChromaticAdaptionAlgorithm(ChromaticAdaptionAlgorithm::Bradford);
    SetTargetColorSpace(ColorSpace::SRGB_D65);
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
