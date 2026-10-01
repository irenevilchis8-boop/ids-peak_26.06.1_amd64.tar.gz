/*!
 * \file    peak_icv_debayer_module.hpp
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
#include <peak_icv/pipeline/types/peak_icv_debayer_channel_layout.hpp>
#include <peak_icv/pipeline/types/peak_icv_processing_policy.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_image_converter.h>

#include <algorithm>
#include <sstream>
#include <string>

namespace peak
{
namespace pipeline
{
namespace detail
{
/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 * \brief Specifies the conditions under which the Debayer module performs color conversion.
 *
 * \since ids_peak_icv 1.0
 */
enum class DebayerConversionPolicy
{
    Bypass,      //!< Do not convert images.
    BayerOnly,   //!< Convert only Bayer-pattern images.
    BayerAndMono //!< Convert both Bayer-pattern and monochrome images.
};

PEAK_COMMON_NO_DISCARD inline std::string ToString(const DebayerConversionPolicy& policy)
{
    if (policy == DebayerConversionPolicy::BayerAndMono)
    {
        return "BayerAndMono";
    }
    if (policy == DebayerConversionPolicy::BayerOnly)
    {
        return "BayerOnly";
    }
    if (policy == DebayerConversionPolicy::Bypass)
    {
        return "Bypass";
    }
    const auto policyStr = std::to_string(static_cast<int>(policy));
    throw peak::icv::NotSupportedException("The given debayer conversion policy " + policyStr + " is unknown!");
}

PEAK_COMMON_NO_DISCARD inline DebayerConversionPolicy ToDebayerConversionPolicy(const std::string& policy)
{
    if (policy == "BayerAndMono")
    {
        return DebayerConversionPolicy::BayerAndMono;
    }
    if (policy == "BayerOnly")
    {
        return DebayerConversionPolicy::BayerOnly;
    }
    if (policy == "Bypass")
    {
        return DebayerConversionPolicy::Bypass;
    }
    throw peak::icv::NotSupportedException("The given debayer conversion policy " + policy + " is unknown!");
}

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Debayer is an image pipeline module that converts Bayer RAW images into standard color formats.
 *
 * It performs demosaicing on Bayer-pattern RAW images, converting them into full-color images
 * using configurable channel layouts such as RGB, BGR, RGBA, or BGRA. The bit depth of the output
 * is inferred from the input, depending on the selected processing policy.
 *
 * The module can also be configured to convert Bayer or monochrome images, while
 * passing through other image types unchanged.
 *
 * \defaults{defaults_module_debayer|
 *   - DebayerChannelLayout::RGB
 *   - DebayerConversionPolicy::BayerOnly
 *   - Target bit depth = 8
 *   - ProcessingPolicy::Fast
 * }
 *
 * \since ids_peak_icv 1.0
 */
class DebayerModule : public modules::IModule
{
public:
    /*!
     * \brief Creates an instance of class DebayerModule with \ref defaults_module_debayer "default settings".
     *
     * \since ids_peak_icv 1.0
     */
    DebayerModule();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~DebayerModule() override;

    /*!
     * \brief Copy constructor for class DebayerModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    DebayerModule(const DebayerModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    DebayerModule(DebayerModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class DebayerModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    DebayerModule& operator=(const DebayerModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    DebayerModule& operator=(DebayerModule&& other) noexcept;

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
     * \brief Resets all module settings to its \ref defaults_module_debayer "default settings".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Set the output channel layout for debayered images.
     *
     * This controls the order and number of color channels in the converted image.
     *
     * \param layout The channel layout to use (e.g., RGB, BGRA).
     *
     * \since ids_peak_icv 1.0
     */
    void SetChannelLayout(DebayerChannelLayout layout);

    /*!
     * \brief Gets the current channel layout setting.
     *
     * \return The currently configured channel layout.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD DebayerChannelLayout GetChannelLayout() const;

    /*!
     * \brief Set the debayer conversion policy.
     *
     * This policy determines which types of input images will be converted.
     * All other image types are passed through unchanged.
     *
     * \param policy The desired conversion policy.
     *
     * \since ids_peak_icv 1.0
     */
    void SetConversionPolicy(DebayerConversionPolicy policy);

    /*!
     * \brief Retrieves the current conversion policy.
     *
     * \return The currently configured DebayerConversionPolicy.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD DebayerConversionPolicy GetConversionPolicy() const;

    /*!
     * \brief Set the target bit depth for processed images.
     *
     * The effective output bit depth depends on the selected \ref ProcessingPolicy "ProcessingPolicy:"
     *
     *  - **Fast**: The minimum of input bit depth and target bit depth.
     *  - **Balanced**: Equal to input bit depth.
     *  - **Enhanced**: The maximum of input bit depth and target bit depth.
     *
     * \param bitDepth The desired target bit depth (e.g., 8, 10, 12).
     *
     * \since ids_peak_icv 1.0
     */
    void SetTargetBitDepth(size_t bitDepth)
    {
        m_targetBitDepth = bitDepth;
    }

    /*!
     * \brief Set the processing policy.
     *
     * The processing policy defines how the target bit depth interacts
     * with the input image bit depth.
     *
     * \param policy The desired \ref ProcessingPolicy.
     *
     * \since ids_peak_icv 1.0
     */
    void SetProcessingPolicy(ProcessingPolicy policy);

    /*!
     * \brief Converts a Bayer or mono image to a color image,
     *        or returns the input image unchanged.
     *
     * A demosaicing algorithm is applied according to the configured
     * conversion policy. The input image is returned unchanged if the module
     * is disabled, the policy indicates bypass, or the image format is not
     * eligible for conversion. Otherwise, the Bayer RAW image is converted
     * to the configured output format.
     *
     * \note This operation disregards any specified image regions and processes
     *       the entire image.
     *
     * \param input The input image (Bayer, mono, or already color).
     *
     * \return The processed color image or the unmodified input image.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Converts a Bayer or mono image to a color image,
     *        or returns the input image unchanged.
     *
     * A demosaicing algorithm is applied according to the configured
     * conversion policy. The input image is returned unchanged if the module
     * is disabled, the policy indicates bypass, or the image format is not
     * eligible for conversion. Otherwise, the Bayer RAW image is converted
     * to the configured output format.
     *
     * \note This operation disregards any specified image regions and processes
     *       the entire image.
     *
     * \param input The input image (Bayer, mono, or already color).
     *
     * \return The processed color image or the unmodified input image.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

    /*!
     * \brief Frees unused internal buffers.
     *
     * This module uses pre-allocated internal buffers to accelerate conversions.
     * When the image size or pixel format changes, new buffers are allocated, which may cause
     * the internal buffer pool to grow over time. This function can be used to release
     * unused buffers and reduce memory usage.
     *
     * \note Avoid calling this function too frequently (e.g., after every resize or format change),
     * as it introduces some overhead.
     *
     * \since ids_peak_icv 1.0
     */
    void ReleaseBuffers() const;

private:
    PEAK_COMMON_NO_DISCARD peak::common::PixelFormat GetOutputFormat(peak::common::PixelFormat inputFormat) const;
    PEAK_COMMON_NO_DISCARD size_t GetOutputBitDepth(size_t inputBitDepth) const;

    static void ValidateChannelLayout(DebayerChannelLayout layout);
    static void ValidateConversionPolicy(DebayerConversionPolicy policy);

    static constexpr int moduleVersion{ 1 };
    static constexpr auto conversionPolicyKey{ "ConversionPolicy" };
    static constexpr auto channelLayoutKey{ "ChannelLayout" };

    peak_icv_image_converter_handle m_handle{};
    DebayerChannelLayout m_channelLayout{ DebayerChannelLayout::RGB };
    DebayerConversionPolicy m_conversionPolicy{ DebayerConversionPolicy::BayerOnly };

    size_t m_targetBitDepth{ 8 };
    ProcessingPolicy m_processingPolicy{ ProcessingPolicy::Fast };

    bool m_enabled{ true };
};

inline DebayerModule::DebayerModule()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Create(&m_handle);
    });
}

inline DebayerModule::~DebayerModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Destroy(m_handle);
    }
}

inline DebayerModule::DebayerModule(DebayerModule&& other) noexcept
{
    m_channelLayout = other.m_channelLayout;
    m_conversionPolicy = other.m_conversionPolicy;
    m_enabled = other.m_enabled;

    std::swap(m_handle, other.m_handle);
}

inline DebayerModule& DebayerModule::operator=(DebayerModule&& other) noexcept
{
    if (this != &other)
    {
        m_channelLayout = other.m_channelLayout;
        m_conversionPolicy = other.m_conversionPolicy;
        m_enabled = other.m_enabled;
        std::swap(m_handle, other.m_handle);
    }

    return *this;
}

inline void DebayerModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetBool("Enabled", IsEnabled());
    archive.SetInt("Version", moduleVersion);

    archive.SetString(channelLayoutKey, ToString(m_channelLayout));
    archive.SetString(conversionPolicyKey, ToString(m_conversionPolicy));
}

inline void DebayerModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");
    detail::ValidateVersion(version, GetType());

    SetEnabled(archive.GetBool("Enabled"));
    m_channelLayout = ToDebayerChannelLayout(archive.GetString(channelLayoutKey));
    m_conversionPolicy = ToDebayerConversionPolicy(archive.GetString(conversionPolicyKey));
}

inline void DebayerModule::ResetToDefault()
{
    m_channelLayout = DebayerChannelLayout::RGB;
    m_conversionPolicy = DebayerConversionPolicy::BayerOnly;
}

inline void DebayerModule::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

inline bool DebayerModule::IsEnabled() const
{
    return m_enabled;
}

inline const char* DebayerModule::GetType() const
{
    return "Debayer";
}

inline void DebayerModule::SetChannelLayout(DebayerChannelLayout layout)
{
    ValidateChannelLayout(layout);
    m_channelLayout = layout;
}

inline DebayerChannelLayout DebayerModule::GetChannelLayout() const
{
    return m_channelLayout;
}

inline void DebayerModule::SetConversionPolicy(DebayerConversionPolicy policy)
{
    ValidateConversionPolicy(policy);
    m_conversionPolicy = policy;
}

inline DebayerConversionPolicy DebayerModule::GetConversionPolicy() const
{
    return m_conversionPolicy;
}

inline size_t DebayerModule::GetOutputBitDepth(const size_t inputBitDepth) const
{
    if (m_processingPolicy == ProcessingPolicy::Fast)
    {
        return (std::min)(inputBitDepth, m_targetBitDepth);
    }
    if (m_processingPolicy == ProcessingPolicy::Enhanced)
    {
        return (std::max)(inputBitDepth, m_targetBitDepth);
    }
    return inputBitDepth;
}

inline peak::common::PixelFormat DebayerModule::GetOutputFormat(peak::common::PixelFormat inputFormat) const
{
    if (m_conversionPolicy == DebayerConversionPolicy::Bypass)
    {
        return inputFormat;
    }

    const peak::common::PixelFormatInfo info(inputFormat);

    if (!info.IsSingleChannel())
    {
        return inputFormat;
    }

    const auto isBayer = info.HasChannel(peak::common::Channel::Bayer);
    const auto isMono = info.HasIntensityChannel();

    if (!isBayer && (!isMono || m_conversionPolicy != DebayerConversionPolicy::BayerAndMono))
    {
        return inputFormat;
    }

    const auto inputBitDepth = info.GetStorageBitsPerChannel();
    const auto outputBitDepth = GetOutputBitDepth(inputBitDepth);

    if (outputBitDepth <= 8)
    {
        switch (m_channelLayout)
        {
        case DebayerChannelLayout::RGB:
            return peak::common::PixelFormat::RGB8;
        case DebayerChannelLayout::BGR:
            return peak::common::PixelFormat::BGR8;
        case DebayerChannelLayout::RGBA:
            return peak::common::PixelFormat::RGBa8;
        case DebayerChannelLayout::BGRA:
            return peak::common::PixelFormat::BGRa8;
        }
    }
    if (outputBitDepth <= 10)
    {
        switch (m_channelLayout)
        {
        case DebayerChannelLayout::RGB:
            return peak::common::PixelFormat::RGB10;
        case DebayerChannelLayout::BGR:
            return peak::common::PixelFormat::BGR10;
        case DebayerChannelLayout::RGBA:
            return peak::common::PixelFormat::RGBa10;
        case DebayerChannelLayout::BGRA:
            return peak::common::PixelFormat::BGRa10;
        }
    }

    switch (m_channelLayout)
    {
    case DebayerChannelLayout::RGB:
        return peak::common::PixelFormat::RGB12;
    case DebayerChannelLayout::BGR:
        return peak::common::PixelFormat::BGR12;
    case DebayerChannelLayout::RGBA:
        return peak::common::PixelFormat::RGBa12;
    case DebayerChannelLayout::BGRA:
        return peak::common::PixelFormat::BGRa12;
    }

    std::ostringstream oss;
    oss << "0x" << std::uppercase << std::hex << static_cast<int>(inputFormat);
    throw peak::icv::NotSupportedException("The given input pixel format " + oss.str() + " is unknown!");
}

inline void DebayerModule::ValidateChannelLayout(DebayerChannelLayout layout)
{
    if (layout != DebayerChannelLayout::RGB && layout != DebayerChannelLayout::BGR && layout != DebayerChannelLayout::RGBA
        && layout != DebayerChannelLayout::BGRA)
    {
        throw peak::icv::NotSupportedException("The given channel layout " + ToString(layout) + " is invalid!");
    }
}

inline void DebayerModule::ValidateConversionPolicy(DebayerConversionPolicy policy)
{
    if (policy != DebayerConversionPolicy::BayerOnly && policy != DebayerConversionPolicy::BayerAndMono
        && policy != DebayerConversionPolicy::Bypass)
    {
        throw peak::icv::NotSupportedException("The given conversion policy " + ToString(policy) + " is invalid!");
    }
}

inline void DebayerModule::SetProcessingPolicy(ProcessingPolicy policy)
{
    m_processingPolicy = policy;
}

inline peak::icv::Image DebayerModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any DebayerModule::Process(const peak::common::Any& input) const
{
    if (!IsEnabled())
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();

    const auto inputFormat = inputImage.GetPixelFormat();
    const auto outputFormat = GetOutputFormat(inputFormat);

    if (inputFormat == outputFormat)
    {
        return input;
    }

    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(inputImage);
    peak_icv_image_handle outputHandle = nullptr;

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Convert(
            m_handle, inputImageHandle, peak::common::detail::CppPixelFormatToCPixelFormat(outputFormat), &outputHandle);
    });

    return peak::common::Any(peak::common::detail::BackendAccessor<peak::icv::Image>::CreateInstance(outputHandle));
}

inline void DebayerModule::ReleaseBuffers() const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_ReleaseBuffers(m_handle);
    });
}
} // namespace detail
} // namespace pipeline 
} // namespace peak
