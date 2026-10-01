/*!
 * \file    peak_icv_gain_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_igain_module.hpp>
#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/pipeline/detail/peak_icv_pipeline_utils.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_gain.h>

namespace peak
{
namespace pipeline
{

namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Image pipeline module for applying gain to the image.
 *
 * \details \copydetails features::GainFeature
 */
class GainModule final : public modules::IGain
{
public:
    /*!
     * \brief Creates an instance of class GainModule with \ref defaults_feature_gain "default values".
     *
     * \since ids_peak_icv 1.0
     */
    GainModule();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~GainModule() override;

    /*!
     * \brief Copy constructor for class GainModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    GainModule(const GainModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    GainModule(GainModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class GainModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    GainModule& operator=(const GainModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    GainModule& operator=(GainModule&& other) noexcept;

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
     * \brief Returns the type of the module for serialization purposes.
     *
     * \returns A string representing the module's type.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD const char* GetType() const override;

    /*!
     * \brief Resets the gain values to their \ref defaults_feature_gain "defaults".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the master gain value.
     *
     * Sets the overall master gain. The valid range for the gain value can be
     * obtained using the \ref GetRange function.
     *
     * \param value The master gain value to set.
     *
     * \throws peak::icv::OutOfRangeException  If the gain \p value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetMaster(float value) override;

    /*!
     * \brief Returns the current master gain.
     *
     * \returns The current master gain.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetMaster() const override;

    /*!
     * \brief Sets the red gain value.
     *
     * Sets the color gain for the red channel. The valid range for the gain value can be
     * obtained using the \ref GetRange function.
     *
     * \param value The red gain value to set.
     *
     * \throws peak::icv::OutOfRangeException  If the gain \p value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetRed(float value) override;

    /*!
     * \brief Returns the current red gain.
     *
     * \returns The current red gain.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetRed() const override;

    /*!
     * \brief Sets the green gain value.
     *
     * Sets the color gain for the green channel. The valid range for the gain value can be
     * obtained using the \ref GetRange function.
     *
     * \param value The green gain value to set.
     *
     * \throws peak::icv::OutOfRangeException  If the gain \p value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetGreen(float value) override;

    /*!
     * \brief Returns the current green gain.
     *
     * \returns The current green gain.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetGreen() const override;

    /*!
     * \brief Sets the blue gain value.
     *
     * Sets the color gain for the blue channel. The valid range for the gain value can be
     * obtained using the \ref GetRange function.
     *
     * \param value The blue gain value to set.
     *
     * \throws peak::icv::OutOfRangeException  If the gain \p value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetBlue(float value) override;

    /*!
     * \brief Returns the current blue gain.
     *
     * \returns The current blue gain.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD float GetBlue() const override;

    /*!
     * \brief Returns the valid range for the master or color gains.
     *
     * Provides the minimum and maximum values that are accepted by the
     * \ref SetMaster, \ref SetRed, \ref SetGreen and the \ref SetBlue functions.
     *
     * \returns The interval containing the minimum and maximum valid gain values.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetRange() const;

    /*!
     * \brief Applies the gains to the input image in place and returns a reference to the modified image.
     *
     * The correction is performed based on the current configuration of the module. The operation modifies the
     * input image directly and does not create a copy.
     *
     * \note Supported pixel formats: BayerRG8, BayerRG10, BayerRG12, BayerGR8, BayerGR10, BayerGR12,
     *                                BayerBG8, BayerBG10, BayerBG12, BayerGB8, BayerGB10, BayerGB12, Mono8, Mono10, Mono12, Mono16.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed and corrected.
     *
     * \returns A reference to the input image after in-place gain correction.
     *
     * \throws NotSupportedException  If \p input image has any other than the supported pixel formats.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Applies the gains to the input image in place and returns a reference to the modified image.
     *
     * The correction is performed based on the current configuration of the module. The operation modifies the
     * input image directly and does not create a copy.
     *
     * \note Supported pixel formats: BayerRG8, BayerRG10, BayerRG12, BayerGR8, BayerGR10, BayerGR12,
     *                                BayerBG8, BayerBG10, BayerBG12, BayerGB8, BayerGB10, BayerGB12, Mono8, Mono10, Mono12, Mono16.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed and corrected.
     *
     * \returns A reference to the input image after in-place gain correction.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     * \throws NotSupportedException                  If \p input image has any other than the supported pixel formats.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

private:
    void Apply(peak_icv_gain_type type, float value) const;

    PEAK_COMMON_NO_DISCARD float Fetch(peak_icv_gain_type type) const;

    static constexpr int moduleVersion = 1;
    static constexpr auto masterGainKey = "MasterGain";
    static constexpr auto redGainKey = "RedGain";
    static constexpr auto greenGainKey = "GreenGain";
    static constexpr auto blueGainKey = "BlueGain";

    peak_icv_gain_handle m_handle{};
    bool m_enabled{ true };
};

inline GainModule::GainModule()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Gain_Create(&m_handle);
    });
}

inline GainModule::~GainModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Gain_Destroy(m_handle);
    }
}

inline GainModule::GainModule(GainModule&& other) noexcept
{
    m_handle = std::exchange(other.m_handle, nullptr);
    m_enabled = other.m_enabled;
}

inline GainModule& GainModule::operator=(GainModule&& other) noexcept
{
    if (this != &other)
    {
        if (m_handle != nullptr)
        {
            peak::icv::detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Gain_Destroy(m_handle);
            });
        }

        m_handle = std::exchange(other.m_handle, nullptr);
        m_enabled = other.m_enabled;
    }

    return *this;
}

inline void GainModule::SetEnabled(const bool enabled)
{
    m_enabled = enabled;
}

inline bool GainModule::IsEnabled() const
{
    return m_enabled;
}

inline void GainModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetInt("Version", moduleVersion);
    archive.SetBool("Enabled", IsEnabled());

    archive.SetDouble(masterGainKey, Fetch(PEAK_ICV_GAIN_TYPE_MASTER));
    archive.SetDouble(redGainKey, Fetch(PEAK_ICV_GAIN_TYPE_RED));
    archive.SetDouble(greenGainKey, Fetch(PEAK_ICV_GAIN_TYPE_GREEN));
    archive.SetDouble(blueGainKey, Fetch(PEAK_ICV_GAIN_TYPE_BLUE));
}

inline void GainModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");
    detail::ValidateVersion(version, GetType());

    SetEnabled(archive.GetBool("Enabled"));

    Apply(PEAK_ICV_GAIN_TYPE_MASTER, static_cast<float>(archive.GetDouble(masterGainKey)));

    Apply(PEAK_ICV_GAIN_TYPE_RED, static_cast<float>(archive.GetDouble(redGainKey)));
    Apply(PEAK_ICV_GAIN_TYPE_GREEN, static_cast<float>(archive.GetDouble(greenGainKey)));
    Apply(PEAK_ICV_GAIN_TYPE_BLUE, static_cast<float>(archive.GetDouble(blueGainKey)));
}

inline const char* GainModule::GetType() const
{
    return "Gain";
}

inline void GainModule::ResetToDefault()
{
    Apply(PEAK_ICV_GAIN_TYPE_MASTER, 1.0F);

    Apply(PEAK_ICV_GAIN_TYPE_RED, 1.0F);
    Apply(PEAK_ICV_GAIN_TYPE_GREEN, 1.0F);
    Apply(PEAK_ICV_GAIN_TYPE_BLUE, 1.0F);
}

inline void GainModule::SetMaster(const float value)
{
    Apply(PEAK_ICV_GAIN_TYPE_MASTER, value);
}

inline float GainModule::GetMaster() const
{
    return Fetch(PEAK_ICV_GAIN_TYPE_MASTER);
}

inline void GainModule::SetRed(const float value)
{
    Apply(PEAK_ICV_GAIN_TYPE_RED, value);
}

inline float GainModule::GetRed() const
{
    return Fetch(PEAK_ICV_GAIN_TYPE_RED);
}

inline void GainModule::SetGreen(const float value)
{
    Apply(PEAK_ICV_GAIN_TYPE_GREEN, value);
}

inline float GainModule::GetGreen() const
{
    return Fetch(PEAK_ICV_GAIN_TYPE_GREEN);
}

inline void GainModule::SetBlue(const float value)
{
    Apply(PEAK_ICV_GAIN_TYPE_BLUE, value);
}

inline float GainModule::GetBlue() const
{
    return Fetch(PEAK_ICV_GAIN_TYPE_BLUE);
}

inline peak::common::IntervalF GainModule::GetRange() const
{
    peak_common_interval_f cRange{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Gain_GetRange(m_handle, &cRange);
    });

    return { cRange.minimum, cRange.maximum };
}

inline peak::icv::Image GainModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any GainModule::Process(const peak::common::Any& input) const
{
    auto needsProcessing = [&] {
        bool value{};
        peak::icv::detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Gain_NeedsProcessing(m_handle, &value);
        });
        return value;
    };

    if (!IsEnabled() || !needsProcessing())
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(inputImage);

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Gain_ProcessInplace(m_handle, inputImageHandle);
    });

    return peak::common::Any{ inputImage };
}

inline void GainModule::Apply(peak_icv_gain_type type, const float value) const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Gain_SetValue(m_handle, type, value);
    });
}

inline float GainModule::Fetch(peak_icv_gain_type type) const
{
    float value{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Gain_GetValue(m_handle, type, &value);
    });
    return value;
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
