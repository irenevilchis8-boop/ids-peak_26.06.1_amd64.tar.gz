/*!
 * \file    peak_icv_sharpening_module.hpp
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
#include <peak_icv_c/algorithms/filters/peak_icv_image_filter_sharpening.h>

namespace peak
{
namespace pipeline
{
namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Sharpening is an image pipeline module that applies a sharpening filter to enhance image detail.
 *
 * \details \copydetails features::SharpeningFeature
 */
class SharpeningModule : public modules::IModule
{
public:
    /*!
     * \brief Creates an instance of class SharpeningModule with \ref defaults_feature_sharpening "default values".
     *
     * \since ids_peak_icv 1.0
     */
    SharpeningModule() = default;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~SharpeningModule() override = default;

    /*!
     * \brief Copy constructor for class SharpeningModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    SharpeningModule(const SharpeningModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    SharpeningModule(SharpeningModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class SharpeningModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    SharpeningModule& operator=(const SharpeningModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    SharpeningModule& operator=(SharpeningModule&& other) noexcept;

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
     * \note Higher sharpness levels may increase noise in the output image.
     *
     * \note The sharpness level must be within the valid range returned by \ref GetLevelRange.
     *
     * \param level The sharpness level.
     *
     * \throws OutOfRangeException  If \p level is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetLevel(uint32_t level);

    /*!
     * \brief Retrieves the current sharpness level.
     *
     * \return The currently configured sharpness level.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetLevel() const;

    /*!
     * \brief Returns the valid range of sharpness levels.
     *
     * \return  An IntervalU containing the minimum and maximum allowed sharpness level values.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalU GetLevelRange() const;

    /*!
     * \brief Processes the input image and returns a sharpened output image.
     *
     * \note Supported pixel formats: Mono8, Mono10, Mono12, RGB8, RGB10, RGB12, BGR8, BGR10, BGR12, RGBa8, RGBa10, RGBa12,
     *                                BGRa8, BGRa10, BGRa12.
     *       Images with other formats are passed through unmodified.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed.
     *
     * \returns A new image with sharpening applied.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Processes the input image and returns a sharpened output image.
     *
     * \note Supported pixel formats: Mono8, Mono10, Mono12, RGB8, RGB10, RGB12, BGR8, BGR10, BGR12, RGBa8, RGBa10, RGBa12,
     *                                BGRa8, BGRa10, BGRa12.
     *       Images with other formats are passed through unmodified.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed.
     *
     * \returns A new image with sharpening applied.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

private:
    static constexpr int moduleVersion{ 1 };
    static constexpr auto levelKey{ "Level" };

    uint32_t m_level{ 0 };

    bool m_enabled{ true };
};

inline SharpeningModule::SharpeningModule(SharpeningModule&& other) noexcept
{
    m_enabled = other.m_enabled;
}

inline SharpeningModule& SharpeningModule::operator=(SharpeningModule&& other) noexcept
{
    if (this != &other)
    {
        m_enabled = other.m_enabled;
    }

    return *this;
}

inline void SharpeningModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetInt("Version", moduleVersion);
    archive.SetBool("Enabled", IsEnabled());

    archive.SetInt(levelKey, m_level);
}

inline void SharpeningModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");
    detail::ValidateVersion(version, GetType());

    SetEnabled(archive.GetBool("Enabled"));

    m_level = static_cast<uint32_t>(archive.GetInt(levelKey));
}

inline void SharpeningModule::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

inline bool SharpeningModule::IsEnabled() const
{
    return m_enabled;
}

inline const char* SharpeningModule::GetType() const
{
    return "Sharpening";
}

inline void SharpeningModule::ResetToDefault()
{
    m_level = 0;
}

inline void SharpeningModule::SetLevel(const uint32_t level)
{
    auto range = GetLevelRange();
    if (level < range.GetMinimum() || level > range.GetMaximum())
    {
        throw peak::icv::OutOfRangeException(std::string("The given level value " + std::to_string(level) + " is out of range!"));
    }
    m_level = level;
}

inline uint32_t SharpeningModule::GetLevel() const
{
    return m_level;
}

inline peak::common::IntervalU SharpeningModule::GetLevelRange() const
{
    peak_common_interval_u cRange{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ImageFilter_Sharpening_GetRange(&cRange);
    });

    return { cRange.minimum, cRange.maximum };
}

inline peak::icv::Image SharpeningModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any SharpeningModule::Process(const peak::common::Any& input) const
{
    if (!IsEnabled() || m_level == 0)
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();

    const auto pixelFormat = inputImage.GetPixelFormat();
    const peak::common::PixelFormatInfo info(pixelFormat);
    const auto isSupportedMonoImage = pixelFormat == peak::common::PixelFormat::Mono8
        || pixelFormat == peak::common::PixelFormat::Mono10 || pixelFormat == peak::common::PixelFormat::Mono12;
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
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ImageFilter_Sharpening_ProcessInPlace(inputImageHandle, m_level);
    });

    return peak::common::Any{ inputImage };
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
