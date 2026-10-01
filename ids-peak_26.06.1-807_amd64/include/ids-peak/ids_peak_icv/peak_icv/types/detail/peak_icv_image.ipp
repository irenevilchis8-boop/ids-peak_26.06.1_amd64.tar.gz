/*!
 * \file    peak_icv_image.ipp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-03-19
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_metadata.hpp>
#include <peak_icv/types/peak_icv_region.hpp>
#include <peak_icv/utils/peak_icv_metadata_adapter.hpp>
#include <peak_icv/utils/peak_icv_metadata_handle_guard.hpp>
#include <peak_icv_c/types/peak_icv_buffer.h>
#include <algorithm>
#include <cstring>
#include <utility>

#ifdef WITH_peak_ipl
#    include <peak_ipl/types/peak_ipl_pixel_format.hpp>
#endif

namespace peak
{
namespace icv
{
inline peak_icv_image_handle Image::CreateFromFile(const std::string& path)
{
    peak_icv_image_handle handle{};
    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_CreateFromFile(&handle, path.c_str());
    });
    return handle;
}

inline peak_icv_image_handle Image::CreateFromFile(const std::string& path, peak::common::PixelFormat name)
{
    peak_icv_image_handle handle{};
    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_CreateFromFileWithPixelFormat(
            &handle, path.c_str(), peak::common::detail::CppPixelFormatToCPixelFormat(name));
    });
    return handle;
}

inline peak_icv_image_info Image::CreateFromHandle(peak_icv_image_handle handle)
{
    peak_icv_image_info imageInfo{};
    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_GetInfo(handle, &imageInfo, sizeof(imageInfo));
    });

    return imageInfo;
}

inline peak_icv_image_handle Image::CreateFromSize(
    peak::common::PixelFormat pixelFormat, const peak::common::Size& size, bool zeroInitialize)
{
    peak_icv_image_handle handle{};
    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_CreateWithZeroInit(&handle,
            peak::common::detail::CppPixelFormatToCPixelFormat(pixelFormat), { size.GetWidth(), size.GetHeight() }, zeroInitialize);
    });
    return handle;
}

inline peak_icv_image_handle Image::CreateFromBuffer(
    peak::common::PixelFormat pixelFormat, const peak::common::Size& size, const uint8_t* buffer, size_t bufferSize)
{
    peak_icv_image_handle handle{};
    detail::ExecuteAndMapReturnCodes([&]() {
        peak_icv_image_info info{ peak::common::detail::CppPixelFormatToCPixelFormat(pixelFormat),
            { size.GetWidth(), size.GetHeight() }, bufferSize, const_cast<uint8_t*>(buffer) };
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_CreateFromImageInfo(&handle, info, sizeof(info));
    });
    return handle;
}

inline peak_icv_image_handle Image::CreateFromImageView(const peak::common::IImageView& imageView)
{
    const auto imageViewSize = imageView.GetSize();
    const auto lineStartOffset = imageView.GetLineStartOffset();

    const size_t validBytesPerLine = peak::common::PixelFormatInfo(imageView.GetPixelFormat())
                                         .GetSizeInBytes({ imageViewSize.GetWidth(), 1 });

    if (lineStartOffset == 0 && validBytesPerLine == imageView.GetBytesPerLine())
    {
        return CreateFromBuffer(imageView.GetPixelFormat(), imageViewSize, imageView.GetData(), imageView.GetSizeInBytes());
    }

    Image imageWithoutBlackColumns(imageView.GetPixelFormat(), imageViewSize, false);
    auto imageHandleWithoutBlackColumns = peak::common::detail::BackendAccessor<Image>::BackendHandle(imageWithoutBlackColumns);

    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Buffer_CutBytes(imageView.GetData(), lineStartOffset, imageView.GetBytesPerLine(),
            validBytesPerLine, imageViewSize.GetHeight(), imageHandleWithoutBlackColumns);
    });
    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_IncreaseUseCount(imageHandleWithoutBlackColumns);
    });
    return imageHandleWithoutBlackColumns;
}

inline Image::Image(peak_icv_image_handle handle, peak_icv_image_info info)
    : m_imageHandle{ handle }
    , m_size{ info.size.width, info.size.height }
    , m_buffer{ info.buffer }
    , m_pixelFormatInfo{ peak::common::detail::CPixelFormatToCppPixelFormat(info.pixelFormat) }
{}

#ifdef WITH_peak_ipl
inline Image::Image(const peak::ipl::Image& image)
    : Image(CreateFromBuffer(peak::common::detail::CPixelFormatToCppPixelFormat(
                                 static_cast<peak_common_pixel_format>(image.PixelFormat().PixelFormatName())), // NOLINT
          peak::common::Size{ static_cast<uint32_t>(image.Width()), static_cast<uint32_t>(image.Height()) }, image.Data(),
          image.ByteCount()))
{
    if (image.Timestamp() != 0)
    {
        peak::common::Metadata metadata;
        metadata.SetValueByKey<peak::common::MetadataKey::DeviceTimestamp>(image.Timestamp());
        SetMetadata(metadata);
    }

    m_image = image;
}
#endif

inline Image::Image(const peak::common::IImageView& imageView)
    : Image(CreateFromImageView(imageView))
{
    const auto metadata = imageView.GetMetadata();
    SetMetadata(*metadata);
}

inline Image::Image(const std::string& path)
    : Image{ CreateFromFile(path) }
{}

inline Image::Image(const std::string& path, peak::common::PixelFormat name)
    : Image{ CreateFromFile(path, name) }
{}

inline Image::Image(peak::common::PixelFormat pixelFormat, uint8_t* buffer, size_t bufferSize, const peak::common::Size& imageSize)
    : Image{ CreateFromBuffer(pixelFormat, imageSize, buffer, bufferSize),
        { peak::common::detail::CppPixelFormatToCPixelFormat(pixelFormat), { imageSize.GetWidth(), imageSize.GetHeight() }, bufferSize,
            buffer } }
{}

inline Image::Image(peak::common::PixelFormat pixelFormat, const peak::common::Size& imageSize)
    : Image{ pixelFormat, imageSize, true }
{}

inline Image::Image(peak::common::PixelFormat pixelFormat, const peak::common::Size& imageSize, bool zeroInitialize)
    : Image{ CreateFromSize(pixelFormat, imageSize, zeroInitialize) }
{}

inline Image::Image(peak_icv_image_handle imageHandle)
    : Image{ imageHandle, CreateFromHandle(imageHandle) }
{}

inline Image::Image(const Image& other)
    : Image{ other.m_imageHandle, CreateFromHandle(other.m_imageHandle) }
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_IncreaseUseCount(other.m_imageHandle);
    });
#ifdef WITH_peak_ipl
    m_image = other.m_image;
#endif
}

inline Image::Image(Image&& other) noexcept
    : Image{ other.m_imageHandle, CreateFromHandle(other.m_imageHandle) }
{
#ifdef WITH_peak_ipl
    m_image = std::move(other.m_image);
#endif
    other.m_imageHandle = nullptr;
}

inline Image& Image::operator=(const Image& other)
{
    if (this->m_imageHandle != other.m_imageHandle)
    {
        if (m_imageHandle)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Destroy(m_imageHandle);
            });
        }

        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_IncreaseUseCount(other.m_imageHandle);
        });
        m_imageHandle = other.m_imageHandle;
        m_size = other.m_size;
        m_pixelFormatInfo = other.m_pixelFormatInfo;
        m_buffer = other.m_buffer;
#ifdef WITH_peak_ipl
        m_image = other.m_image;
#endif
    }

    return *this;
}

inline Image& Image::operator=(Image&& other) noexcept
{
    if (this->m_imageHandle != other.m_imageHandle)
    {
        if (m_imageHandle)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Destroy(m_imageHandle);
            });
        }

        m_imageHandle = std::exchange(other.m_imageHandle, nullptr);
        m_size = other.m_size;
        m_pixelFormatInfo = other.m_pixelFormatInfo;
        m_buffer = std::exchange(other.m_buffer, nullptr);
#ifdef WITH_peak_ipl
        m_image = std::move(other.m_image);
#endif
    }

    return *this;
}

inline Image::~Image()
{
    if (m_imageHandle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Destroy(m_imageHandle);
    }
}

inline bool Image::operator==(const Image& rhs) const
{
    if (rhs.GetSizeInBytes() != this->GetSizeInBytes())
    {
        return false;
    }
    if (rhs.GetSize() != this->GetSize())
    {
        return false;
    }
    if (rhs.GetPixelFormat() != this->GetPixelFormat())
    {
        return false;
    }
    if (rhs.GetRegion() != this->GetRegion())
    {
        return false;
    }
    bool isSame{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Compare(
            m_imageHandle, peak::common::detail::BackendAccessor<Image>::BackendHandle(rhs), &isSame);
    });
    return isSame;
}

inline Image Image::Copy() const
{
    peak_icv_image_handle handle{};

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_CreateFromExistingImage(&handle, m_imageHandle);
    });

    return Image{ handle };
}

inline peak::common::Size Image::GetSize() const
{
    return m_size;
}

inline uint8_t* Image::GetData() const
{
    return m_buffer;
}

inline size_t Image::GetSizeInBytes() const
{
    return m_pixelFormatInfo.GetSizeInBytes(m_size);
}

inline size_t Image::GetBytesPerLine() const
{
    return GetSizeInBytes() / m_size.GetHeight();
}

inline detail::handle_of_t<Image> Image::GetHandle() const
{
    return m_imageHandle;
}

inline peak::common::PixelFormat Image::GetPixelFormat() const
{
    return m_pixelFormatInfo.GetPixelFormat();
}

#ifdef WITH_peak_ipl
inline peak::ipl::Image Image::GetIPLImage() const
{
    if (!m_image.Empty())
    {
        return m_image;
    }

    constexpr std::array<peak::ipl::PixelFormatName, 59> possibleValues{ peak::ipl::PixelFormatName::BayerGR8,
        peak::ipl::PixelFormatName::BayerGR10, peak::ipl::PixelFormatName::BayerGR12, peak::ipl::PixelFormatName::BayerRG8,
        peak::ipl::PixelFormatName::BayerRG10, peak::ipl::PixelFormatName::BayerRG12, peak::ipl::PixelFormatName::BayerGB8,
        peak::ipl::PixelFormatName::BayerGB10, peak::ipl::PixelFormatName::BayerGB12, peak::ipl::PixelFormatName::BayerBG8,
        peak::ipl::PixelFormatName::BayerBG10, peak::ipl::PixelFormatName::BayerBG12, peak::ipl::PixelFormatName::Mono8,
        peak::ipl::PixelFormatName::Mono10, peak::ipl::PixelFormatName::Mono12, peak::ipl::PixelFormatName::Mono16,
        peak::ipl::PixelFormatName::Confidence8, peak::ipl::PixelFormatName::Confidence16,
        peak::ipl::PixelFormatName::Coord3D_C8, peak::ipl::PixelFormatName::Coord3D_C16,
        peak::ipl::PixelFormatName::Coord3D_C32f, peak::ipl::PixelFormatName::Coord3D_ABC32f,
        peak::ipl::PixelFormatName::YUV420_8_YY_UV_SemiplanarIDS, peak::ipl::PixelFormatName::YUV420_8_YY_VU_SemiplanarIDS,
        peak::ipl::PixelFormatName::YUV422_8_UYVY, peak::ipl::PixelFormatName::RGB8, peak::ipl::PixelFormatName::RGB10,
        peak::ipl::PixelFormatName::RGB12, peak::ipl::PixelFormatName::BGR8, peak::ipl::PixelFormatName::BGR10,
        peak::ipl::PixelFormatName::BGR12, peak::ipl::PixelFormatName::RGBa8, peak::ipl::PixelFormatName::RGBa10,
        peak::ipl::PixelFormatName::RGBa12, peak::ipl::PixelFormatName::BGRa8, peak::ipl::PixelFormatName::BGRa10,
        peak::ipl::PixelFormatName::BGRa12, peak::ipl::PixelFormatName::BayerBG10p, peak::ipl::PixelFormatName::BayerBG12p,
        peak::ipl::PixelFormatName::BayerGB10p, peak::ipl::PixelFormatName::BayerGB12p, peak::ipl::PixelFormatName::BayerGR10p,
        peak::ipl::PixelFormatName::BayerGR12p, peak::ipl::PixelFormatName::BayerRG10p, peak::ipl::PixelFormatName::BayerRG12p,
        peak::ipl::PixelFormatName::Mono10p, peak::ipl::PixelFormatName::Mono12p, peak::ipl::PixelFormatName::RGB10p32,
        peak::ipl::PixelFormatName::BGR10p32, peak::ipl::PixelFormatName::BayerRG10g40IDS,
        peak::ipl::PixelFormatName::BayerGB10g40IDS, peak::ipl::PixelFormatName::BayerGR10g40IDS,
        peak::ipl::PixelFormatName::BayerBG10g40IDS, peak::ipl::PixelFormatName::BayerRG12g24IDS,
        peak::ipl::PixelFormatName::BayerGB12g24IDS, peak::ipl::PixelFormatName::BayerGR12g24IDS,
        peak::ipl::PixelFormatName::BayerBG12g24IDS, peak::ipl::PixelFormatName::Mono10g40IDS,
        peak::ipl::PixelFormatName::Mono12g24IDS };

    const auto currentPixelFormat = m_pixelFormatInfo.GetPixelFormat();
    const auto foundIt = std::find_if(possibleValues.begin(), possibleValues.end(), [&](const peak::ipl::PixelFormatName& name) {
        return static_cast<std::underlying_type<peak::ipl::PixelFormatName>::type>(name)
            == static_cast<std::underlying_type<peak::ipl::PixelFormatName>::type>(currentPixelFormat);
    });
    if (foundIt == possibleValues.end())
    {
        throw NotSupportedException("The pixelformat " + m_pixelFormatInfo.GetName()
            + " has no equivalent in the ids_peak_ipl. As a result, it cannot be converted to an ids_peak_ipl Image!");
    }

    const auto metadata = GetMetadata();
    const auto timestamp = metadata.HasEntryByKey<peak::common::MetadataKey::DeviceTimestamp>() ?
        GetMetadata().GetValueByKey<peak::common::MetadataKey::DeviceTimestamp>() :
        0;

    m_image = peak::ipl::Image{ static_cast<peak::ipl::PixelFormatName>(currentPixelFormat), m_buffer,
        m_pixelFormatInfo.GetSizeInBytes(m_size), m_size.GetWidth(), m_size.GetHeight(), timestamp };

    return m_image;
}
#endif

inline Region Image::GetRegion() const
{
    Region region;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_GetRegion(
            m_imageHandle, peak::common::detail::BackendAccessor<Region>::BackendHandleAddress(region));
    });
    return region;
}

inline void Image::SetRegion(const Region& region) const
{
    const peak_icv_region_handle regionHandle = peak::common::detail::BackendAccessor<Region>::BackendHandle(region);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_SetRegion(m_imageHandle, regionHandle);
    });
}

inline void Image::ResetRegion() const
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_ResetRegion(m_imageHandle);
    });
}

inline Image Image::ConvertPixelFormat(peak::common::PixelFormat pixelFormat) const
{
    Image outputImage(pixelFormat, GetSize(), false);
    ConvertPixelFormat(outputImage);
    return outputImage;
}

inline void Image::ConvertPixelFormat(Image& destinationImage) const
{
    const auto imageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(destinationImage);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_ConvertPixelFormat(
            m_imageHandle, peak::common::detail::CppPixelFormatToCPixelFormat(destinationImage.GetPixelFormat()), imageHandle);
    });
}

inline Image Image::ConvertPixelFormatWithFactor(peak::common::PixelFormat pixelFormat, const double factor) const
{
    Image outputImage(pixelFormat, GetSize(), false);
    const auto imageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(outputImage);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_ConvertPixelFormatWithFactor(
            m_imageHandle, peak::common::detail::CppPixelFormatToCPixelFormat(pixelFormat), factor, imageHandle);
    });
    return outputImage;
}

inline void Image::SetMetadata(const peak::common::Metadata& metadata)
{
    const auto& metadataGuard = detail::MetadataAdapter::createMetadataHandleGuardFromMetadata(metadata);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_SetMetadata(m_imageHandle, metadataGuard.GetHandle());
    });
}

inline peak::common::Metadata Image::GetMetadata() const
{
    detail::MetadataHandleGuard metadataGuard;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_GetMetadata(m_imageHandle, metadataGuard.GetHandleAddress());
    });

    detail::MetadataAdapter metadataAdapter;
    const auto metadata = metadataAdapter.createMetaDataFromHandle(metadataGuard.GetHandle());

    return metadata;
}

inline Image Image::Subtract(const Image& subtrahend) const
{
    Image difference{ GetPixelFormat(), GetSize() };

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Subtract(GetHandle(), subtrahend.GetHandle(), difference.GetHandle());
    });


    return difference;
}

inline Image Image::operator-(const Image& subtrahend) const
{
    return Subtract(subtrahend);
}

inline Image Image::Crop(const peak::common::Rectangle& rect) const
{
    Image croppedImage{ GetPixelFormat(), { rect.GetWidth(), rect.GetHeight() } };

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Crop(GetHandle(), croppedImage.GetHandle(),
            peak::common::detail::BackendAccessor<peak::common::Rectangle>::CreateCType(rect));
    });
    return croppedImage;
}

inline Image Image::Scale(const peak::common::Size& targetImageSize, const Interpolation& interpolation) const
{
    Image scaledImage{ GetPixelFormat(), targetImageSize };
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Scale(
            GetHandle(), scaledImage.GetHandle(), static_cast<peak_icv_interpolation>(interpolation));
    });
    return scaledImage;
}

inline std::vector<Image> Image::Deinterleave() const
{
    size_t numOutputImages{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Deinterleave_GetOutputImageCount(
            peak::common::detail::CppPixelFormatToCPixelFormat(GetPixelFormat()), &numOutputImages);
    });
    peak_common_pixel_format outputPixelFormat;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Deinterleave_GetOutputPixelFormat(
            peak::common::detail::CppPixelFormatToCPixelFormat(GetPixelFormat()), &outputPixelFormat);
    });
    peak_common_size outputSize{};
    detail::ExecuteAndMapReturnCodes([&] {
        const auto size = GetSize();
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Deinterleave_GetOutputImageSize(
            peak::common::detail::CppPixelFormatToCPixelFormat(GetPixelFormat()), { size.GetWidth(), size.GetHeight() }, &outputSize);
    });

    std::vector<Image> deinterleavedImages;
    deinterleavedImages.reserve(numOutputImages);
    std::vector<peak_icv_image_handle> deinterleavedImageHandles;
    deinterleavedImages.reserve(numOutputImages);
    for (size_t i = 0; i < numOutputImages; ++i)
    {
        Image tmpImage{ peak::common::detail::CPixelFormatToCppPixelFormat(outputPixelFormat),
            { outputSize.width, outputSize.height } };
        deinterleavedImageHandles.emplace_back(peak::common::detail::BackendAccessor<Image>::BackendHandle(tmpImage));
        deinterleavedImages.emplace_back(std::move(tmpImage));
    }

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_Deinterleave(
            GetHandle(), deinterleavedImageHandles.data(), deinterleavedImages.size());
    });

    return deinterleavedImages;
}

#ifdef WITH_peak_ipl
inline Image::operator peak::ipl::Image() const
{
    return GetIPLImage();
}
#endif
} /* namespace icv */
} /* namespace peak */
