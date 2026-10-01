/*!
 * \file    peak_icv_tone_curve_correction_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/pipeline/detail/peak_icv_pipeline_utils.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_tone_curve_correction.h>

namespace peak
{
namespace pipeline
{
namespace features
{
class GammaFeature;
class DigitalBlackFeature;
} // namespace features

namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Tone curve correction is an image pipeline module
 *        that applies digital black correction
 *        and inverse gamma transformation to an image.
 *
 * \see \ref features::DigitalBlackFeature and \ref features::GammaFeature
 *
 * \since ids_peak_icv 1.0
 */
class ToneCurveCorrectionModule : public modules::IModule
{
public:
    /*!
     * \brief Creates an instance of class ToneCurveCorrectionModule with default values for
     *        \ref defaults_feature_gamma "gamma" and
     *        \ref defaults_feature_digitalblack "black".
     *
     * \since ids_peak_icv 1.0
     */
    ToneCurveCorrectionModule();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~ToneCurveCorrectionModule() override;

    /*!
     * \brief Copy constructor for class ToneCurveCorrectionModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    ToneCurveCorrectionModule(const ToneCurveCorrectionModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ToneCurveCorrectionModule(ToneCurveCorrectionModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class ToneCurveCorrectionModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    ToneCurveCorrectionModule& operator=(const ToneCurveCorrectionModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ToneCurveCorrectionModule& operator=(ToneCurveCorrectionModule&& other) noexcept;

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
     *         \ref defaults_feature_gamma "gamma" and
     *         \ref defaults_feature_digitalblack "black".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the gamma correction exponent.
     *
     * This value determines the degree of inverse gamma correction applied during processing,
     * where output values are computed as pow(input, 1/gamma).
     * Higher gamma values lighten the image, while values closer to zero darken it.
     *
     * \note The gamma exponent must be within the valid range returned by \ref GetGammaRange().
     *
     * \param gamma The gamma exponent.
     *
     * \since ids_peak_icv 1.0
     */
    void SetGamma(float gamma);

    /*!
     * \brief Gets the current gamma correction exponent.
     *
     * \return The gamma exponent currently set.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetGamma() const;

    /*!
     * \brief Returns the valid range for the gamma correction exponent.
     *
     * \return An IntervalF containing the minimum and maximum allowed gamma values.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetGammaRange() const;

    /*!
     * \brief Sets the digital black used for digital black correction.
     *
     * This value is subtracted from the input image channel values before gamma correction. It typically represents sensor black offset.
     *
     * \note The digital black must be within the valid range returned by \ref GetDigitalBlackRange().
     *
     * \param digitalBlack The digital black value in normalized units.
     *
     * \since ids_peak_icv 1.0
     */
    void SetDigitalBlack(float digitalBlack);

    /*!
     * \brief Gets the current digital black used for correction.
     *
     * \return The digital black value currently set.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetDigitalBlack() const;

    /*!
     * \brief Returns the valid range for the digital black correction value.
     *
     * \return An IntervalF containing the minimum and maximum allowed digital black values.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetDigitalBlackRange() const;

    /*!
     * \brief Processes the input image and returns a tone curve corrected output image.
     *
     * \note Supported pixel formats: Mono8, Mono10, Mono12, Mono16, RGB8, RGB10, RGB12, BGR8, BGR10, BGR12, RGBa8, RGBa10, RGBa12,
     *                                BGRa8, BGRa10, BGRa12.
     *       Images with other formats are passed through unmodified.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed.
     *
     * \returns A new image with tone curve correction applied.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Processes the input image and returns a tone curve corrected output image.
     *
     * \note Supported pixel formats: Mono8, Mono10, Mono12, Mono16, RGB8, RGB10, RGB12, BGR8, BGR10, BGR12,
     *                                RGBa8, RGBa10, RGBa12, BGRa8, BGRa10, BGRa12.
     *       Images with other formats are passed through unmodified.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed.
     *
     * \returns A new image with tone curve correction applied.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

private:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    friend class features::GammaFeature;
    friend class features::DigitalBlackFeature;
#endif

    PEAK_COMMON_NO_DISCARD float FetchGamma() const;
    void ApplyGamma(float value) const;
    PEAK_COMMON_NO_DISCARD float FetchDigitalBlack() const;
    void ApplyDigitalBlack(float value) const;
    void SetGammaEnabled(bool enabled);
    void SetDigitalBlackEnabled(bool enabled);
    PEAK_COMMON_NO_DISCARD bool IsGammaEnabled() const;
    PEAK_COMMON_NO_DISCARD bool IsDigitalBlackEnabled() const;

    static constexpr int moduleVersion{ 1 };
    static constexpr auto gammaKey{ "Gamma" };
    static constexpr auto digitalBlackKey{ "DigitalBlack" };

    static constexpr auto gammaDefault = 1.0F;
    static constexpr auto digitalBlackDefault = 0.0F;

    peak_icv_tone_curve_correction_handle m_handle{};
    bool m_gammaEnabled{ true };
    bool m_digitalBlackEnabled{ true };

    float m_gamma{ gammaDefault };
    float m_digitalBlack{ digitalBlackDefault };
};

inline ToneCurveCorrectionModule::ToneCurveCorrectionModule()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_Create(&m_handle);
    });
}

inline ToneCurveCorrectionModule::~ToneCurveCorrectionModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_Destroy(m_handle);
    }
}

inline ToneCurveCorrectionModule::ToneCurveCorrectionModule(ToneCurveCorrectionModule&& other) noexcept
{
    m_handle = std::exchange(other.m_handle, nullptr);
    m_gammaEnabled = other.m_gammaEnabled;
    m_gamma = other.m_gamma;
    m_digitalBlackEnabled = other.m_digitalBlackEnabled;
    m_digitalBlack = other.m_digitalBlack;
}

inline ToneCurveCorrectionModule& ToneCurveCorrectionModule::operator=(ToneCurveCorrectionModule&& other) noexcept
{
    if (this != &other)
    {
        if (m_handle != nullptr)
        {
            peak::icv::detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_Destroy(m_handle);
            });
        }

        m_handle = std::exchange(other.m_handle, nullptr);
        m_gammaEnabled = other.m_gammaEnabled;
        m_gamma = other.m_gamma;
        m_digitalBlackEnabled = other.m_digitalBlackEnabled;
        m_digitalBlack = other.m_digitalBlack;
    }

    return *this;
}

inline void ToneCurveCorrectionModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetInt("Version", moduleVersion);

    const auto gammaArchive = archive.CreateArchive();
    const auto digitalBlackArchive = archive.CreateArchive();

    gammaArchive->SetBool("Enabled", m_gammaEnabled);
    digitalBlackArchive->SetBool("Enabled", m_digitalBlackEnabled);

    gammaArchive->SetDouble("Value", m_gamma);
    digitalBlackArchive->SetDouble("Value", m_digitalBlack);

    archive.SetArchive(gammaKey, gammaArchive);
    archive.SetArchive(digitalBlackKey, digitalBlackArchive);
}

inline void ToneCurveCorrectionModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");

    detail::ValidateVersion(version, GetType());

    const auto gammaArchive = archive.GetArchive(gammaKey);
    const auto digitalBlackArchive = archive.GetArchive(digitalBlackKey);

    m_gammaEnabled = gammaArchive->GetBool("Enabled");
    m_digitalBlackEnabled = digitalBlackArchive->GetBool("Enabled");

    m_gamma = static_cast<float>(gammaArchive->GetDouble("Value"));
    m_digitalBlack = static_cast<float>(digitalBlackArchive->GetDouble("Value"));

    ApplyGamma(m_gammaEnabled ? m_gamma : gammaDefault);
    ApplyDigitalBlack(m_digitalBlackEnabled ? m_digitalBlack : digitalBlackDefault);
}

inline void ToneCurveCorrectionModule::SetEnabled(bool enabled)
{
    SetGammaEnabled(enabled);
    SetDigitalBlackEnabled(enabled);
}

inline bool ToneCurveCorrectionModule::IsEnabled() const
{
    return m_gammaEnabled || m_digitalBlackEnabled;
}

inline const char* ToneCurveCorrectionModule::GetType() const
{
    return "ToneCurveCorrection";
}

inline void ToneCurveCorrectionModule::ResetToDefault()
{
    ApplyGamma(gammaDefault);
    m_gamma = gammaDefault;
    ApplyDigitalBlack(digitalBlackDefault);
    m_digitalBlack = digitalBlackDefault;
}

inline float ToneCurveCorrectionModule::GetGamma() const
{
    if (!m_gammaEnabled)
    {
        return m_gamma;
    }

    return FetchGamma();
}

inline peak::common::IntervalF ToneCurveCorrectionModule::GetGammaRange() const
{
    peak_common_interval_f cRange{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange(m_handle, &cRange);
    });

    return peak::common::detail::BackendAccessor<peak::common::IntervalF>::CreateInstance(cRange);
}

inline peak::common::IntervalF ToneCurveCorrectionModule::GetDigitalBlackRange() const
{
    peak_common_interval_f cRange{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange(m_handle, &cRange);
    });

    return peak::common::detail::BackendAccessor<peak::common::IntervalF>::CreateInstance(cRange);
}

inline void ToneCurveCorrectionModule::SetGamma(const float gamma)
{
    m_gamma = gamma;

    if (m_gammaEnabled)
    {
        ApplyGamma(gamma);
    }
}

inline float ToneCurveCorrectionModule::GetDigitalBlack() const
{
    if (!m_digitalBlackEnabled)
    {
        return m_digitalBlack;
    }
    return FetchDigitalBlack();
}

inline void ToneCurveCorrectionModule::SetDigitalBlack(const float digitalBlack)
{
    m_digitalBlack = digitalBlack;

    if (m_digitalBlackEnabled)
    {
        ApplyDigitalBlack(digitalBlack);
    }
}

inline peak::icv::Image ToneCurveCorrectionModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any ToneCurveCorrectionModule::Process(const peak::common::Any& input) const
{
    auto needsProcessing = [&] {
        bool value{};
        peak::icv::detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing(m_handle, &value);
        });
        return value;
    };

    if (!IsEnabled() || !needsProcessing())
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();

    const auto pixelFormat = inputImage.GetPixelFormat();
    const auto info = peak::common::PixelFormatInfo(pixelFormat);
    const auto isSupportedMonoImage = pixelFormat == peak::common::PixelFormat::Mono8
        || pixelFormat == peak::common::PixelFormat::Mono10 || pixelFormat == peak::common::PixelFormat::Mono12
        || pixelFormat == peak::common::PixelFormat::Mono16;
    const auto isColorImage = info.HasChannel(peak::common::Channel::Red) && info.HasChannel(peak::common::Channel::Green)
        && info.HasChannel(peak::common::Channel::Blue);
    const auto isSupportedColorImage = isColorImage && pixelFormat != peak::common::PixelFormat::RGB10p32
        && pixelFormat != peak::common::PixelFormat::BGR10p32;
    if (!isSupportedMonoImage && !isSupportedColorImage)
    {
        return input;
    }

    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(inputImage);

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace(m_handle, inputImageHandle);
    });

    return peak::common::Any{ inputImage };
}

inline float ToneCurveCorrectionModule::FetchGamma() const
{
    float value{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_GetGamma(m_handle, &value);
    });
    return value;
}

inline void ToneCurveCorrectionModule::ApplyGamma(float value) const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_SetGamma(m_handle, value);
    });
}

inline float ToneCurveCorrectionModule::FetchDigitalBlack() const
{
    float value{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack(m_handle, &value);
    });
    return value;
}

inline void ToneCurveCorrectionModule::ApplyDigitalBlack(float value) const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack(m_handle, value);
    });
}

inline void ToneCurveCorrectionModule::SetGammaEnabled(bool enabled)
{
    m_gammaEnabled = enabled;

    ApplyGamma(enabled ? m_gamma : gammaDefault);
}

inline void ToneCurveCorrectionModule::SetDigitalBlackEnabled(bool enabled)
{
    m_digitalBlackEnabled = enabled;

    ApplyDigitalBlack(enabled ? m_digitalBlack : digitalBlackDefault);
}

inline bool ToneCurveCorrectionModule::IsGammaEnabled() const
{
    return m_gammaEnabled;
}

inline bool ToneCurveCorrectionModule::IsDigitalBlackEnabled() const
{
    return m_digitalBlackEnabled;
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
