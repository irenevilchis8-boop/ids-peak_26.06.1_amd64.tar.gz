/*!
 * \file    peak_icv_mono_conversion_module.hpp
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
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_image_converter.h>

namespace peak
{
namespace pipeline
{
namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Mono conversion is an image pipeline module that converts images to a monochrome format.
 *
 * The mono conversion module performs a mono (grayscale) conversion on input images.
 * When enabled, it converts the input image to a mono format while preserving the input bit depth.
 * If disabled, the input image is passed through unchanged.
 *
 * \since ids_peak_icv 1.0
 */
class MonoConversionModule : public modules::IModule
{
public:
    /*!
     * \brief Creates an instance of class MonoConversion.
     *
     * \since ids_peak_icv 1.0
     */
    MonoConversionModule();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~MonoConversionModule() override;

    /*!
     * \brief Copy constructor for class MonoConversionModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    MonoConversionModule(const MonoConversionModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    MonoConversionModule(MonoConversionModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class MonoConversionModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    MonoConversionModule& operator=(const MonoConversionModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    MonoConversionModule& operator=(MonoConversionModule&& other) noexcept;

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
     * \brief Calling this method has no effect.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override
    {}

    /*!
     * \brief Converts the input image to the configured output pixel format.
     *
     * \note This operation disregards any specified image regions
     *       and processes the full image.
     *
     * \param input The input image to convert.
     *
     * \return Converted image in the configured pixel format.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Converts the input image to the configured output pixel format.
     *
     * \note This operation disregards any specified image regions
     *       and processes the full image.
     *
     * \param input The input image to convert.
     *
     * \return Converted image in the configured pixel format.
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
    PEAK_COMMON_NO_DISCARD static peak::common::PixelFormat GetOutputFormat(peak::common::PixelFormat inputFormat);

    constexpr static int moduleVersion{ 1 };

    bool m_enabled{ true };
    peak_icv_image_converter_handle m_handle{};
};

inline MonoConversionModule::MonoConversionModule()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Create(&m_handle);
    });
}

inline MonoConversionModule::~MonoConversionModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Destroy(m_handle);
    }
}

inline MonoConversionModule::MonoConversionModule(MonoConversionModule&& other) noexcept
{
    m_enabled = other.m_enabled;
    std::swap(m_handle, other.m_handle);
}

inline MonoConversionModule& MonoConversionModule::operator=(MonoConversionModule&& other) noexcept
{
    if (this != &other)
    {
        m_enabled = other.m_enabled;
        std::swap(m_handle, other.m_handle);
    }

    return *this;
}

inline void MonoConversionModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetBool("Enabled", IsEnabled());
    archive.SetInt("Version", moduleVersion);
}

inline void MonoConversionModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");
    detail::ValidateVersion(version, GetType());

    SetEnabled(archive.GetBool("Enabled"));
}

inline void MonoConversionModule::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

inline bool MonoConversionModule::IsEnabled() const
{
    return m_enabled;
}

inline const char* MonoConversionModule::GetType() const
{
    return "MonoConversion";
}

inline peak::common::PixelFormat MonoConversionModule::GetOutputFormat(peak::common::PixelFormat inputFormat)
{
    const peak::common::PixelFormatInfo info(inputFormat);

    if (info.IsSingleChannel() && info.HasIntensityChannel())
    {
        return inputFormat;
    }

    const auto bitDepth = info.GetStorageBitsPerChannel();

    if (bitDepth <= 8)
    {
        return peak::common::PixelFormat::Mono8;
    }
    if (bitDepth <= 10)
    {
        return peak::common::PixelFormat::Mono10;
    }
    if (bitDepth <= 12)
    {
        return peak::common::PixelFormat::Mono12;
    }
    return peak::common::PixelFormat::Mono16;
}

inline peak::icv::Image MonoConversionModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any MonoConversionModule::Process(const peak::common::Any& input) const
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

inline void MonoConversionModule::ReleaseBuffers() const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_ReleaseBuffers(m_handle);
    });
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
