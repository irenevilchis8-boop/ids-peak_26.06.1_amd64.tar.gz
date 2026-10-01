/*!
 * \file    peak_image_view_impl.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-30
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include "peak_image_view.hpp"

#include <peak_common/types/peak_common_iimageview.hpp>
#include <peak_common/types/peak_common_metadata.hpp>

#include <peak/buffer/peak_buffer.hpp>
#include <peak/buffer/peak_buffer_part.hpp>
#include <peak/data_stream/peak_data_stream.hpp>
#include <peak/device/peak_device.hpp>
#include <peak/exception/peak_exception.hpp>
#include <peak/node_map/peak_node_map.hpp>

#include <memory>

namespace peak
{
namespace core
{

namespace detail
{
constexpr uint64_t usableRoiChunkId = 0x73020405;
constexpr uint64_t imageChunkId = 0x73688300;

struct UsableRoiChunkInfo
{
    uint16_t usableWidth{};
    uint16_t usableHeight{};
    uint16_t offsetX{};
    uint16_t offsetY{};
};

inline UsableRoiChunkInfo ExtractUsableRoiChunkInfo(const std::shared_ptr<peak::core::BufferChunk>& chunk)
{
    if (chunk->ID() != usableRoiChunkId)
    {
        throw core::InternalErrorException("Cannot extract usable roi chunk info from chunk with wrong ID!");
    }

    const auto* base = static_cast<uint16_t*>(chunk->BasePtr());
    return { base[0], base[1], base[2], base[3] };
}

inline std::shared_ptr<core::BufferChunk> FindBufferChunkById(
    const std::vector<std::shared_ptr<peak::core::BufferChunk>>& chunks, uint64_t chunkId)
{
    const auto it = std::find_if(
        chunks.cbegin(), chunks.cend(), [chunkId](const auto& chunk) { return chunk->ID() == chunkId; });
    if (it == chunks.cend())
    {
        return nullptr;
    }
    return *it;
}

inline ExtractedPayload UpdatePayloadInfoWithChunks(const peak::core::detail::ExtractedPayload& payload,
    const std::vector<std::shared_ptr<peak::core::BufferChunk>>& chunks)
{
    const auto imageChunk = FindBufferChunkById(chunks, imageChunkId);
    if (imageChunk == nullptr)
    {
        throw core::InternalErrorException("Buffer has no image chunk.");
    }

    const auto imageSizeWithPaddingWithoutChunks = imageChunk->Size();

    const auto usableRoiChunk = FindBufferChunkById(chunks, usableRoiChunkId);
    if (usableRoiChunk == nullptr)
    {
        return payload;
    }

    ExtractedPayload result{ payload };

    const auto chunkInfo = ExtractUsableRoiChunkInfo(usableRoiChunk);

    result.size = peak::common::Size{ chunkInfo.usableWidth, chunkInfo.usableHeight };

    auto buffer = imageChunk->ParentBuffer();
    if (result.bytesPerLine != imageSizeWithPaddingWithoutChunks / buffer->Height())
    {
        throw core::InternalErrorException("Unexpected pitch!");
    }

    const auto bytesToSkip = result.bytesPerLine * chunkInfo.offsetY;
    result.dataPtr = static_cast<void*>(static_cast<uint8_t*>(result.dataPtr) + bytesToSkip);

    const peak::common::PixelFormatInfo pixelFormatInfo(result.pixelFormat);
    result.lineStartOffset = pixelFormatInfo.GetSizeInBytes({ chunkInfo.offsetX, 1 });
    result.dataSize = pixelFormatInfo.GetSizeInBytes(
        { static_cast<uint32_t>(buffer->Width()), chunkInfo.usableHeight });
    if (result.dataSize > imageSizeWithPaddingWithoutChunks)
    {
        throw core::InternalErrorException("Chunk size is not large enough to fit the expected image size!");
    }

    return result;
}

inline ExtractedPayload ExtractPayloadTypeImage(const std::shared_ptr<peak::core::Buffer>& buffer)
{
    assert(buffer->PixelFormatNamespace() != core::PixelFormatNamespace::IIDC
        && buffer->PixelFormatNamespace() != core::PixelFormatNamespace::Custom);

    ExtractedPayload result{};

    result.size = { static_cast<uint32_t>(buffer->Width()), static_cast<uint32_t>(buffer->Height()) };
    result.pixelFormat = static_cast<peak::common::PixelFormat>(buffer->PixelFormat());
    result.dataPtr = static_cast<uint8_t*>(buffer->BasePtr()) + buffer->ImageOffset();

    const auto pixelFormatInfo = peak::common::PixelFormatInfo(result.pixelFormat);

    result.bytesPerLine = pixelFormatInfo.GetSizeInBytes({ static_cast<uint32_t>(buffer->Width()), 1 });
    result.lineStartOffset = 0;
    result.dataSize = pixelFormatInfo.GetSizeInBytes(
        { static_cast<uint32_t>(buffer->Width()), static_cast<uint32_t>(buffer->Height()) });

    const auto imageSizeWithPadding = buffer->Size() - buffer->ImageOffset();
    if (result.dataSize > imageSizeWithPadding)
    {
        throw core::InternalErrorException("Buffer is not large enough to fit the expected image size!");
    }

    if (buffer->HasChunks())
    {
        result = UpdatePayloadInfoWithChunks(result, buffer->Chunks());
    }

    return result;
}

inline ExtractedPayload ExtractPayloadTypeChunk(const std::shared_ptr<peak::core::Buffer>& buffer)
{
    const auto remoteNodeMap = buffer->ParentDataStream()->ParentDevice()->RemoteDevice()->NodeMaps().at(0);
    remoteNodeMap->UpdateChunkNodes(buffer);

    const auto chunkWidth = remoteNodeMap->TryFindNode<core::nodes::IntegerNode>("ChunkWidth");
    if (chunkWidth == nullptr || chunkWidth->AccessStatus() == core::nodes::NodeAccessStatus::NotAvailable)
    {
        throw core::InvalidCastException("Buffer has no ChunkWidth.");
    }

    const auto chunkHeight = remoteNodeMap->TryFindNode<core::nodes::IntegerNode>("ChunkHeight");
    if (chunkHeight == nullptr || chunkHeight->AccessStatus() == core::nodes::NodeAccessStatus::NotAvailable)
    {
        throw core::InvalidCastException("Buffer has no ChunkHeight.");
    }

    const peak::common::Size size(
        static_cast<uint32_t>(chunkWidth->Value()), static_cast<uint32_t>(chunkHeight->Value()));

    const auto chunkPixelFormat = remoteNodeMap->TryFindNode<core::nodes::EnumerationNode>("ChunkPixelFormat");
    if (chunkPixelFormat == nullptr || chunkPixelFormat->AccessStatus() == core::nodes::NodeAccessStatus::NotAvailable)
    {
        throw core::InvalidCastException("Buffer has no ChunkPixelFormat.");
    }

    const auto pixelFormat = static_cast<peak::common::PixelFormat>(
        chunkPixelFormat->CurrentEntry()->NumericValue());

    // assume first chunks is image data
    const auto imageChunk = FindBufferChunkById(buffer->Chunks(), imageChunkId);
    if (imageChunk == nullptr)
    {
        throw core::InternalErrorException("Buffer has no image chunk.");
    }

    const auto sizeInBytes = imageChunk->Size();

    const auto pixelFormatInfo = peak::common::PixelFormatInfo(pixelFormat);
    const auto expectedDataSize = pixelFormatInfo.GetSizeInBytes(size);
    if (sizeInBytes < expectedDataSize)
    {
        std::stringstream msg;
        msg << "The buffer's first chunk's size (" << imageChunk->Size() << ") is smaller than the expected data size ("
            << expectedDataSize << ").";
        throw core::InvalidCastException(msg.str());
    }

    return { size, pixelFormat, imageChunk->BasePtr(), sizeInBytes,
        pixelFormatInfo.GetSizeInBytes(peak::common::Size(size.GetWidth(), 1)), 0 };
}

inline ExtractedPayload ExtractPayloadFromBufferPart(const std::shared_ptr<peak::core::BufferPart>& part)
{
    if (part == nullptr)
    {
        throw core::InvalidArgumentException("The given part is a nullptr!");
    }

    const auto partType = part->Type();

    if (partType != BufferPartType::Image2D && partType != BufferPartType::ConfidenceMap
        && partType != BufferPartType::Image3D)
    {
        throw core::InvalidCastException("BufferPart has no image data.");
    }

    assert(part->FormatNamespace() != static_cast<uint64_t>(core::PixelFormatNamespace::IIDC)
        && part->FormatNamespace() != static_cast<uint64_t>(core::PixelFormatNamespace::Custom));

    const auto pixelFormat = static_cast<peak::common::PixelFormat>(part->Format());
    const auto bytesPerLine = peak::common::PixelFormatInfo(pixelFormat)
                                  .GetSizeInBytes({ static_cast<uint32_t>(part->Width()), 1 });
    return { peak::common::Size{ static_cast<uint32_t>(part->Width()), static_cast<uint32_t>(part->Height()) },
        pixelFormat, part->BasePtr(), part->Size(), bytesPerLine, 0 };
}

inline ExtractedPayload ExtractPayloadFromBuffer(const std::shared_ptr<peak::core::Buffer>& buffer)
{
    if (buffer == nullptr)
    {
        throw core::InvalidArgumentException("The given buffer is a nullptr!");
    }

    if (buffer->HasImage())
    {
        return ExtractPayloadTypeImage(buffer);
    }

    if (buffer->PayloadType() == core::BufferPayloadType::Chunk)
    {
        return ExtractPayloadTypeChunk(buffer);
    }

    throw core::InvalidCastException("Buffer has no image data and no chunks.");
}

inline std::shared_ptr<peak::common::Metadata> ExtractMetadataFromBuffer(
    const std::shared_ptr<peak::core::Buffer>& buffer, MetadataExtractionMode mode)
{
    if (buffer == nullptr)
    {
        throw core::InvalidArgumentException("The given buffer is a nullptr!");
    }

    auto metadata = std::make_shared<peak::common::Metadata>();

    // NOTE: BUFFER_INFO_FRAMEID is a mandatory GenTL feature. It MUST be implemented.
    metadata->SetValueByKey<peak::common::MetadataKey::DeviceFrameID>(buffer->FrameID());

    // NOTE: We need to try, as the timestamp might not be supported by the TL.
    try
    {
        metadata->SetValueByKey<peak::common::MetadataKey::DeviceTimestamp>(buffer->Timestamp_ns());
    }
    catch (const peak::core::Exception&)
    {}

    // NOTE: The system timestamp is optional and may not be supported by the TL or device.
    try
    {
        metadata->SetValueByKey<peak::common::MetadataKey::SystemTimestamp>(buffer->SystemTimestamp_ns());
    }
    catch (const peak::core::Exception&)
    {}

    if (mode == MetadataExtractionMode::Minimal)
    {
        return metadata;
    }

    // MetadataExtractionMode::Extended

    const auto remoteNodeMap = buffer->ParentDataStream()->ParentDevice()->RemoteDevice()->NodeMaps().at(0);
    const auto chunkExposureTimeNode = remoteNodeMap->TryFindNode<nodes::FloatNode>("ChunkExposureTime");
    const auto chunkGainSelectorNode = remoteNodeMap->TryFindNode<nodes::EnumerationNode>("ChunkGainSelector");
    const auto chunkGainNode = remoteNodeMap->TryFindNode<nodes::FloatNode>("ChunkGain");

    const auto lock = remoteNodeMap->Lock();
    remoteNodeMap->UpdateChunkNodes(buffer);

    if (chunkExposureTimeNode != nullptr && chunkExposureTimeNode->IsReadable())
    {
        metadata->SetValueByKey<peak::common::MetadataKey::DeviceExposureTime>(chunkExposureTimeNode->Value());
    }

    if (chunkGainSelectorNode != nullptr && chunkGainSelectorNode->AccessStatus() == nodes::NodeAccessStatus::ReadWrite
        && chunkGainNode != nullptr)
    {
        const auto availableEntries = chunkGainSelectorNode->AvailableEntries();

        bool found = false;
        auto readChunkGain = [&](const std::string& entryName) {
            const auto entry = chunkGainSelectorNode->TryFindEntry(entryName);
            if (entry == nullptr || !entry->IsAvailable())
            {
                return 1.0;
            }

            chunkGainSelectorNode->SetCurrentEntry(entry);
            if (!chunkGainNode->IsReadable())
            {
                return 1.0;
            }
            found = true;
            return chunkGainNode->Value();
        };

        const auto gainAll = readChunkGain("All");
        const auto gainAnalogAll = readChunkGain("AnalogAll");
        const auto gainDigitalAll = readChunkGain("DigitalAll");

        if (found)
        {
            metadata->SetValueByKey<peak::common::MetadataKey::DeviceGain>(
                gainAll * gainAnalogAll * gainDigitalAll);
        }
    }

    return metadata;
}

} // namespace detail

inline ImageView::ImageView(
    const detail::ExtractedPayload& payload, std::shared_ptr<peak::common::Metadata> metadata)
    : m_metadata{ std::move(metadata) }
    , m_payload{ payload }
{}

inline ImageView::ImageView(const std::shared_ptr<peak::core::Buffer>& buffer)
    : ImageView(detail::ExtractPayloadFromBuffer(buffer),
          detail::ExtractMetadataFromBuffer(buffer, MetadataExtractionMode::Minimal))
{
    m_parentBuffer = buffer;
}

inline ImageView::ImageView(const std::shared_ptr<Buffer>& buffer, MetadataExtractionMode mode)
    : ImageView(detail::ExtractPayloadFromBuffer(buffer), detail::ExtractMetadataFromBuffer(buffer, mode))
{
    m_parentBuffer = buffer;
}

inline ImageView::ImageView(const std::shared_ptr<core::BufferPart>& part)
    : ImageView(detail::ExtractPayloadFromBufferPart(part),
          detail::ExtractMetadataFromBuffer(part->ParentBuffer(), MetadataExtractionMode::Minimal))
{
    m_parentBuffer = part->ParentBuffer();
}

inline ImageView::ImageView(const std::shared_ptr<core::BufferPart>& part, MetadataExtractionMode mode)
    : ImageView(detail::ExtractPayloadFromBufferPart(part),
          detail::ExtractMetadataFromBuffer(part->ParentBuffer(), mode))
{
    m_parentBuffer = part->ParentBuffer();
}

inline const uint8_t* ImageView::GetData() const
{
    return static_cast<uint8_t*>(m_payload.dataPtr);
}

inline uint8_t* ImageView::GetData()
{
    return static_cast<uint8_t*>(m_payload.dataPtr);
}

inline std::size_t ImageView::GetLineStartOffset() const
{
    return m_payload.lineStartOffset;
}

inline std::size_t ImageView::GetSizeInBytes() const
{
    return m_payload.dataSize;
}

inline peak::common::PixelFormat ImageView::GetPixelFormat() const
{
    return m_payload.pixelFormat;
}

inline peak::common::PixelFormatInfo ImageView::GetPixelFormatInfo() const
{
    return peak::common::PixelFormatInfo(m_payload.pixelFormat);
}

inline peak::common::Size ImageView::GetSize() const
{
    return m_payload.size;
}

inline uint32_t ImageView::GetWidth() const
{
    return m_payload.size.GetWidth();
}

inline uint32_t ImageView::GetHeight() const
{
    return m_payload.size.GetHeight();
}

inline size_t ImageView::GetBitsPerPixel() const
{
    return peak::common::PixelFormatInfo(m_payload.pixelFormat).GetAllocatedBitsPerPixel();
}

inline size_t ImageView::GetBytesPerLine() const
{
    return m_payload.bytesPerLine;
}

inline std::shared_ptr<peak::common::Metadata> ImageView::GetMetadata()
{
    return m_metadata;
}

inline std::shared_ptr<const peak::common::Metadata> ImageView::GetMetadata() const
{
    return m_metadata;
}

inline std::shared_ptr<peak::core::Buffer> ImageView::GetParentBuffer() const
{
    return LockOrThrow(m_parentBuffer);
}

} // namespace core
} // namespace peak
