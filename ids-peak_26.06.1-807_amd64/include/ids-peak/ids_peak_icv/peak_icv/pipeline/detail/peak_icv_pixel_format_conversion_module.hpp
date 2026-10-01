/*!
 * \file    peak_icv_pixel_format_conversion_module.hpp
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
 * \brief Pixel format conversion module that transforms images to a specified output pixel format.
 *
 * The pixel format conversion module allows explicit control over the output pixel format.
 *
 * \defaults{defaults_module_pixelformat_conversion_cpp|
 *   - peak::common::PixelFormat::RGB8
 * }
 *
 * \since ids_peak_icv 1.0
 */
class PixelFormatConversionModule : public modules::IModule
{
public:
    /*!
     * \brief Creates an instance of class PixelFormatConversionModule
     *        with \ref defaults_module_pixelformat_conversion_cpp "default output pixelformat".
     *
     * \since ids_peak_icv 1.0
     */
    PixelFormatConversionModule();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~PixelFormatConversionModule() override;

    /*!
     * \brief Copy constructor for class PixelFormatConversionModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    PixelFormatConversionModule(const PixelFormatConversionModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    PixelFormatConversionModule(PixelFormatConversionModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class PixelFormatConversionModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    PixelFormatConversionModule& operator=(const PixelFormatConversionModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    PixelFormatConversionModule& operator=(PixelFormatConversionModule&& other) noexcept;

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
     * \brief Resets the output pixel format to its \ref defaults_module_pixelformat_conversion_cpp "default value".
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the desired output pixel format.
     *
     * \param format The desired output pixel format.
     *
     * \since ids_peak_icv 1.0
     */
    virtual void SetOutputPixelFormat(peak::common::PixelFormat format);

    /*!
     * \brief Gets the currently set output pixel format.
     *
     * \return The current output pixel format.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual peak::common::PixelFormat GetOutputPixelFormat() const;

    /*!
     * \brief Converts the input image to the configured output pixel format.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to convert.
     *
     * \return The converted image in the specified pixel format.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Converts the input image to the configured output pixel format.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to convert.
     *
     * \return The converted image in the specified pixel format.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

    /*!
     * \brief Frees unused internal buffers.
     *
     * This module uses pre-allocated internal buffers to accelerate pixel format conversions.
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
    static constexpr int moduleVersion{ 1 };
    static constexpr auto outputPixelFormatKey{ "OutputPixelFormat" };

    peak::common::PixelFormat m_outputPixelFormat{ peak::common::PixelFormat::RGB8 };
    bool m_enabled{ true };
    peak_icv_image_converter_handle m_handle{};
};

inline PixelFormatConversionModule::PixelFormatConversionModule()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Create(&m_handle);
    });
}

inline PixelFormatConversionModule::~PixelFormatConversionModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Destroy(m_handle);
    }
}

inline PixelFormatConversionModule::PixelFormatConversionModule(PixelFormatConversionModule&& other) noexcept
{
    m_outputPixelFormat = other.m_outputPixelFormat;
    m_enabled = other.m_enabled;
    std::swap(m_handle, other.m_handle);
}

inline PixelFormatConversionModule& PixelFormatConversionModule::operator=(PixelFormatConversionModule&& other) noexcept
{
    if (this != &other)
    {
        m_outputPixelFormat = other.m_outputPixelFormat;
        m_enabled = other.m_enabled;
        std::swap(m_handle, other.m_handle);
    }

    return *this;
}

inline void PixelFormatConversionModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetBool("Enabled", IsEnabled());
    archive.SetInt("Version", moduleVersion);

    archive.SetString(outputPixelFormatKey, peak::common::PixelFormatInfo(m_outputPixelFormat).GetName());
}

inline void PixelFormatConversionModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");
    detail::ValidateVersion(version, GetType());

    SetEnabled(archive.GetBool("Enabled"));
    m_outputPixelFormat = peak::common::PixelFormatInfo(archive.GetString(outputPixelFormatKey)).GetPixelFormat();
}

inline void PixelFormatConversionModule::SetOutputPixelFormat(peak::common::PixelFormat format)
{
    m_outputPixelFormat = format;
}

inline peak::common::PixelFormat PixelFormatConversionModule::GetOutputPixelFormat() const
{
    return m_outputPixelFormat;
}

inline void PixelFormatConversionModule::ResetToDefault()
{
    m_outputPixelFormat = peak::common::PixelFormat::RGB8;
}

inline void PixelFormatConversionModule::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

inline bool PixelFormatConversionModule::IsEnabled() const
{
    return m_enabled;
}

inline const char* PixelFormatConversionModule::GetType() const
{
    return "PixelFormatConversion";
}

inline peak::icv::Image PixelFormatConversionModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any PixelFormatConversionModule::Process(const peak::common::Any& input) const
{
    if (!IsEnabled())
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();

    const auto inputFormat = inputImage.GetPixelFormat();

    if (inputFormat == m_outputPixelFormat)
    {
        return input;
    }

    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(inputImage);
    peak_icv_image_handle outputHandle = nullptr;

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_Convert(
            m_handle, inputImageHandle, peak::common::detail::CppPixelFormatToCPixelFormat(m_outputPixelFormat), &outputHandle);
    });

    return peak::common::Any(peak::common::detail::BackendAccessor<peak::icv::Image>::CreateInstance(outputHandle));
}

inline void PixelFormatConversionModule::ReleaseBuffers() const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_ImageConverter_ReleaseBuffers(m_handle);
    });
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
