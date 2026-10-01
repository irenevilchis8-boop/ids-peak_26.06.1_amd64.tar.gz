/*!
 * \file    peak_icv_unpack_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_icv/pipeline/types/peak_icv_processing_policy.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_image_converter.h>

#include <utility>

namespace peak
{
namespace pipeline
{
namespace detail
{
/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Unpack is an image pipeline module that converts packed pixel formats into corresponding unpacked Bayer or mono formats.
 *
 * The unpack module is always enabled and cannot be disabled. It converts input images
 * with packed pixel formats into their corresponding unpacked Bayer or monochrome formats.
 * The output bit depth depends on the applied processing policy and the specified target bit depth.
 *
 * Default configuration:
 *     - Target bit depth: 8
 *     - Processing policy: ProcessingPolicy.Fast
 *
 * \since ids_peak_icv 1.0
 */
class UnpackModule : public modules::IModule
{
public:
    /*!
     * \brief Creates an instance of class UnpackModule.
     *
     * \since ids_peak_icv 1.0
     */
    UnpackModule();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~UnpackModule() override;

    /*!
     * \brief Copy constructor for class UnpackModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    UnpackModule(const UnpackModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    UnpackModule(UnpackModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class UnpackModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    UnpackModule& operator=(const UnpackModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    UnpackModule& operator=(UnpackModule&& other) noexcept;

    /*!
     * \brief This function has no effect on the Unpack module.
     *
     * \since ids_peak_icv 1.0
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override;

    /*!
     * \brief This function has no effect on the unpack module.
     *
     * \since ids_peak_icv 1.0
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override;

    /*!
     * \brief This property cannot be changed.
     *
     * The module remains enabled to guarantee correct operation of following modules.
     *
     * \since ids_peak_icv 1.0
     */
    void SetEnabled(bool enable) override;

    /*!
     * \brief Indicates whether the unpack module is enabled.
     *
     * This property always returns true.
     *
     * \return True.
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
     * \brief Resets all module settings
     *
     * Resets the target bit depth to 8 and the processing policy to ProcessingPolicy::Fast
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Set the target bit depth for image processing.
     *
     * The target bit depth acts as a reference when deciding how to
     * unpack packed pixel formats. The actual resulting bit depth
     * depends on the selected \ref ProcessingPolicy "ProcessingPolicy:"
     *
     * - \b Fast:      The output bit depth is the \e minimum of the input image bit depth
     *                 and the target bit depth.
     * - \b Balanced:  The output bit depth is the \e same as the input image bit depth
     *                 (the target value is ignored).
     * - \b Enhanced:  The output bit depth is the \e maximum of the input image bit depth
     *                 and the target bit depth.
     *
     * This allows you to downsample, preserve, or enhance bit depth depending
     * on your use case.
     *
     * \param bitDepth The desired target bit depth (e.g., 8, 10, 12).
     *
     * \since ids_peak_icv 1.0
     */
    void SetTargetBitDepth(size_t bitDepth);

    /*!
     * \brief Get the target bit depth used during image processing.
     *
     * This value specifies the bit depth the module will aim for when unpacking
     * packed pixel formats. The actual output bit depth depends on the
     * selected \ref ProcessingPolicy.
     *
     * \return The currently configured target bit depth.
     */
    size_t GetTargetBitDepth() const;

    /*!
     * \brief Set the processing policy
     *
     * Defines how the bit depth is handled during image processing — whether it is increased, decreased, or preserved.
     *
     * \param policy The desired processing policy.
     */
    void SetProcessingPolicy(ProcessingPolicy policy);

    /*!
     * \brief Get the currently configured processing policy.
     *
     * \return The active processing policy.
     */
    ProcessingPolicy GetProcessingPolicy() const;

    /*!
     * \brief Converts a packed pixel format image into an unpacked Bayer or monochrome format.
     *
     * This function unpacks the input image from a packed format to its corresponding
     * unpacked Bayer or monochrome format.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The packed input image to unpack.
     *
     * \return The unpacked output image with the downsampled bit depth.
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Converts a packed pixel format image into an unpacked Bayer or mono format.
     *
     * This function unpacks the input image from a packed format to its corresponding
     * unpacked Bayer or monochrome format.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The packed input image to unpack.
     *
     * \return The unpacked output image with the downsampled bit depth.
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
    PEAK_COMMON_NO_DISCARD static peak::common::PixelFormat GetOutputFormat(
        peak::common::PixelFormat inputFormat, size_t outputBitDepth);
    PEAK_COMMON_NO_DISCARD size_t GetOutputBitDepth(size_t inputBitDepth) const;

    PEAK_COMMON_NO_DISCARD static peak::common::PixelFormat BayerBGFormat(size_t bitDepth);
    PEAK_COMMON_NO_DISCARD static peak::common::PixelFormat BayerGBFormat(size_t bitDepth);
    PEAK_COMMON_NO_DISCARD static peak::common::PixelFormat BayerGRFormat(size_t bitDepth);
    PEAK_COMMON_NO_DISCARD static peak::common::PixelFormat BayerRGFormat(size_t bitDepth);
    PEAK_COMMON_NO_DISCARD static peak::common::PixelFormat MonoFormat(size_t bitDepth);

    peak_icv_image_converter_handle m_handle{};

    size_t m_targetBitDepth{ 8 };
    ProcessingPolicy m_policy{ ProcessingPolicy::Fast };
};

inline UnpackModule::UnpackModule()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Create(&m_handle);
    });
}

inline UnpackModule::~UnpackModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Destroy(m_handle);
    }
}

inline UnpackModule::UnpackModule(UnpackModule&& other) noexcept
{
    std::swap(m_handle, other.m_handle);
}

inline UnpackModule& UnpackModule::operator=(UnpackModule&& other) noexcept
{
    if (this != &other)
    {
        std::swap(m_handle, other.m_handle);
    }

    return *this;
}

inline void UnpackModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    std::ignore = archive;
}

inline void UnpackModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    std::ignore = archive;
}

inline void UnpackModule::SetEnabled(bool enable)
{
    std::ignore = enable;
}

inline bool UnpackModule::IsEnabled() const
{
    return true;
}

inline const char* UnpackModule::GetType() const
{
    return "Unpack";
}

inline peak::common::PixelFormat UnpackModule::GetOutputFormat(
    const peak::common::PixelFormat inputFormat, const size_t outputBitDepth)
{
    switch (inputFormat)
    {
    case peak::common::PixelFormat::BayerBG8:
    case peak::common::PixelFormat::BayerBG10:
    case peak::common::PixelFormat::BayerBG10p:
    case peak::common::PixelFormat::BayerBG10g40IDS:
    case peak::common::PixelFormat::BayerBG12:
    case peak::common::PixelFormat::BayerBG12p:
    case peak::common::PixelFormat::BayerBG12g24IDS:
        return BayerBGFormat(outputBitDepth);

    case peak::common::PixelFormat::BayerGB8:
    case peak::common::PixelFormat::BayerGB10:
    case peak::common::PixelFormat::BayerGB10p:
    case peak::common::PixelFormat::BayerGB10g40IDS:
    case peak::common::PixelFormat::BayerGB12:
    case peak::common::PixelFormat::BayerGB12p:
    case peak::common::PixelFormat::BayerGB12g24IDS:
        return BayerGBFormat(outputBitDepth);

    case peak::common::PixelFormat::BayerGR8:
    case peak::common::PixelFormat::BayerGR10:
    case peak::common::PixelFormat::BayerGR10p:
    case peak::common::PixelFormat::BayerGR10g40IDS:
    case peak::common::PixelFormat::BayerGR12:
    case peak::common::PixelFormat::BayerGR12p:
    case peak::common::PixelFormat::BayerGR12g24IDS:
        return BayerGRFormat(outputBitDepth);

    case peak::common::PixelFormat::BayerRG8:
    case peak::common::PixelFormat::BayerRG10:
    case peak::common::PixelFormat::BayerRG10p:
    case peak::common::PixelFormat::BayerRG10g40IDS:
    case peak::common::PixelFormat::BayerRG12:
    case peak::common::PixelFormat::BayerRG12p:
    case peak::common::PixelFormat::BayerRG12g24IDS:
        return BayerRGFormat(outputBitDepth);

    case peak::common::PixelFormat::Mono8:
    case peak::common::PixelFormat::Mono10:
    case peak::common::PixelFormat::Mono10p:
    case peak::common::PixelFormat::Mono10g40IDS:
    case peak::common::PixelFormat::Mono12:
    case peak::common::PixelFormat::Mono12p:
    case peak::common::PixelFormat::Mono12g24IDS:
        return MonoFormat(outputBitDepth);

    case peak::common::PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
    case peak::common::PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
    case peak::common::PixelFormat::YUV422_8_UYVY:
        return peak::common::PixelFormat::RGB8;

    default:
        return inputFormat;
    }
}

inline peak::common::PixelFormat UnpackModule::BayerBGFormat(const size_t bitDepth)
{
    if (bitDepth >= 12)
    {
        return peak::common::PixelFormat::BayerBG12;
    }
    if (bitDepth >= 10)
    {
        return peak::common::PixelFormat::BayerBG10;
    }
    return peak::common::PixelFormat::BayerBG8;
}

inline peak::common::PixelFormat UnpackModule::BayerGBFormat(const size_t bitDepth)
{
    if (bitDepth >= 12)
    {
        return peak::common::PixelFormat::BayerGB12;
    }
    if (bitDepth >= 10)
    {
        return peak::common::PixelFormat::BayerGB10;
    }
    return peak::common::PixelFormat::BayerGB8;
}

inline peak::common::PixelFormat UnpackModule::BayerGRFormat(const size_t bitDepth)
{
    if (bitDepth >= 12)
    {
        return peak::common::PixelFormat::BayerGR12;
    }
    if (bitDepth >= 10)
    {
        return peak::common::PixelFormat::BayerGR10;
    }
    return peak::common::PixelFormat::BayerGR8;
}

inline peak::common::PixelFormat UnpackModule::BayerRGFormat(const size_t bitDepth)
{
    if (bitDepth >= 12)
    {
        return peak::common::PixelFormat::BayerRG12;
    }
    if (bitDepth >= 10)
    {
        return peak::common::PixelFormat::BayerRG10;
    }
    return peak::common::PixelFormat::BayerRG8;
}

inline peak::common::PixelFormat UnpackModule::MonoFormat(const size_t bitDepth)
{
    if (bitDepth >= 12)
    {
        return peak::common::PixelFormat::Mono12;
    }
    if (bitDepth >= 10)
    {
        return peak::common::PixelFormat::Mono10;
    }
    return peak::common::PixelFormat::Mono8;
}

inline void UnpackModule::ResetToDefault()
{
    m_policy = ProcessingPolicy::Fast;
    m_targetBitDepth = 8;
}

inline void UnpackModule::SetTargetBitDepth(const size_t bitDepth)
{
    m_targetBitDepth = bitDepth;
}

inline size_t UnpackModule::GetTargetBitDepth() const
{
    return m_targetBitDepth;
}

inline void UnpackModule::SetProcessingPolicy(const ProcessingPolicy policy)
{
    m_policy = policy;
}

inline ProcessingPolicy UnpackModule::GetProcessingPolicy() const
{
    return m_policy;
}

inline peak::icv::Image UnpackModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline size_t UnpackModule::GetOutputBitDepth(const size_t inputBitDepth) const
{
    if (m_policy == ProcessingPolicy::Fast)
    {
        return (std::min)(inputBitDepth, m_targetBitDepth);
    }
    if (m_policy == ProcessingPolicy::Enhanced)
    {
        return (std::max)(inputBitDepth, m_targetBitDepth);
    }
    return inputBitDepth;
}

inline peak::common::Any UnpackModule::Process(const peak::common::Any& input) const
{
    const auto& inputImage = input.AnyCast<peak::icv::Image>();

    const auto inputFormat = inputImage.GetPixelFormat();
    const auto inputBitDepth = peak::common::PixelFormatInfo(inputFormat).GetStorageBitsPerChannel();
    const auto outputBitDepth = GetOutputBitDepth(inputBitDepth);
    const auto outputFormat = GetOutputFormat(inputFormat, outputBitDepth);

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

inline void UnpackModule::ReleaseBuffers() const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_ReleaseBuffers(m_handle);
    });
}
} // namespace detail
} // namespace pipeline 
} // namespace peak
