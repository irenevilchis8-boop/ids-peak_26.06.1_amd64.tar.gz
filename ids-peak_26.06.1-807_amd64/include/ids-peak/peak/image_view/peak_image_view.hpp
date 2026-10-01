/*!
 * \file    peak_image_view.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-30
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_size.hpp>
#include <peak_common/types/peak_common_any.hpp>
#include <peak_common/types/peak_common_iimageview.hpp>
#include <peak_common/types/peak_common_pixel_format.hpp>

#include <memory>

/*!
 *
 */
namespace peak
{
namespace core
{
class Buffer;
class BufferPart;

namespace detail
{
struct ExtractedPayload
{
    peak::common::Size size;
    peak::common::PixelFormat pixelFormat{};
    void* dataPtr{};
    size_t dataSize{};
    size_t bytesPerLine{};
    size_t lineStartOffset{};
};
} // namespace detail

/*!
 * \brief Controls how metadata is extracted when constructing an ImageView.
 *
 * This enum defines the level of metadata extraction performed when an
 * ImageView is created from a Buffer.
 *
 * \since 1.15
 */
enum class MetadataExtractionMode
{
    /*!
     * Extract only essential metadata (e.g. time stamps or frame ID).
     * This mode is faster and suitable for performance-critical scenarios.
     */
    Minimal = 1,

    /*!
     * Extract extended metadata.
     *
     * Performs metadata extraction also from chunk data, including e.g.
     * exposure time or gain. This may result in additional processing
     * overhead.
     */
    Extended = 2,
};


/*!
 *\ingroup ids_peak_acquisition
 * \brief Implementation of the #peak::common::IImageView interface for viewing image pixel data from arbitrary sources.
 *
 * This interface defines a standard way to access image properties and raw
 * pixel data, enabling interoperability with different image processing
 * libraries or backends.
 *
 * \note This object does not own the image memory. Lifetime management must be
 * handled externally.
 *
 * \since 1.12
 */
class ImageView : public peak::common::IImageView
{
public:
    /*!
     * \brief Construct an ImageView from a Buffer.
     *
     * Metadata is extracted using \ref MetadataExtractionMode::Minimal.
     *
     * \param buffer Shared pointer to the source Buffer containing image data.
     *
     * \note The Buffer must remain valid and must not be queued for the lifetime of the ImageView.
     *
     * \since 1.12
     */
    explicit ImageView(const std::shared_ptr<Buffer>& buffer);

    /*!
     * \brief Construct an ImageView from a Buffer and controls how metadata
     * is extracted via the specified [update mode](\ref MetadataExtractionMode).
     *
     * \param buffer  Shared pointer to the source Buffer containing image data.
     * \param mode    The metadata extraction mode controlling how much metadata is parsed.
     *                See \ref MetadataExtractionMode for details.
     *
     * \note The Buffer must remain valid and must not be queued for the lifetime of the ImageView.
     *
     * \since 1.15
     */
    ImageView(const std::shared_ptr<Buffer>& buffer, MetadataExtractionMode mode);

    /*!
     * \brief Construct an ImageView from a BufferPart.
     *
     * Metadata is extracted using \ref MetadataExtractionMode::Minimal.
     *
     * \param part Shared pointer to the source BufferPart containing image data.
     *
     * \note The Buffer must remain valid and must not be queued for the lifetime of the ImageView.
     *
     * \since 1.12
     */
    explicit ImageView(const std::shared_ptr<BufferPart>& part);

    /*!
     * \brief Construct an ImageView from a BufferPart and controls how metadata
     * is extracted via the specified [update mode](\ref MetadataExtractionMode).
     *
     * \param part  Shared pointer to the source BufferPart containing image data.
     * \param mode  The metadata extraction mode controlling how much metadata is parsed.
     *              See \ref MetadataExtractionMode for details.
     *
     * \note The parent Buffer must remain valid and must not be queued for the lifetime of the ImageView.
     *
     * \since 1.15
     */
    ImageView(const std::shared_ptr<BufferPart>& part, MetadataExtractionMode mode);

    /*!
     * \brief Returns a pointer to the start of the first line that contains valid image data (read-only).
     * \return Pointer to data.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD const uint8_t* GetData() const override;

    /*!
     * \brief  Returns a pointer to the start of the first line that contains valid image data (read-write).
     * \return Pointer to data.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD uint8_t* GetData() override;

    /*!
     * \brief Returns the byte offset to the first pixel of a line.
     * \return Line offset in Bytes.
     *
     * \since 1.14
     */
    PEAK_COMMON_NO_DISCARD std::size_t GetLineStartOffset() const override;

    /*!
     * \brief Returns the number of bytes in a single image row.
     * \return Bytes per line, including any padding.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD std::size_t GetSizeInBytes() const override;

    /*!
     * \brief PixelFormat of the contained image.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD peak::common::PixelFormat GetPixelFormat() const override;

    /*!
     * \brief Information object for the PixelFormat of the contained image.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD peak::common::PixelFormatInfo GetPixelFormatInfo() const override;

    /*!
     * \brief Get the dimensions of the image. I.e. Width, Height, etc.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD peak::common::Size GetSize() const override;

    /*!
     * \brief Width of the image in pixels.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetWidth() const override;

    /*!
     * \brief Height of the image in pixels.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetHeight() const override;

    /*!
     * \brief The amount of bits in one pixel.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD size_t GetBitsPerPixel() const override;

    /*!
     * \brief The amount of bytes per line.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD size_t GetBytesPerLine() const override;

    /*!
     * \brief The metadata object belonging to the image.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD std::shared_ptr<peak::common::Metadata> GetMetadata() override;

    /*!
     * \brief The metadata object belonging to the image.
     *
     * \since 1.12
     */
    PEAK_COMMON_NO_DISCARD std::shared_ptr<const peak::common::Metadata> GetMetadata() const override;

    /*!
     * \brief The parent buffer object, the image view was created from.
     *
     * If the image was created from a buffer part, the parent buffer is the same
     * as returned by #BufferPart::ParentBuffer.
     *
     * \return Parent buffer
     *
     * \throws InternalErrorException An internal error has occurred.
     *
     * \since 1.13
     */
    PEAK_COMMON_NO_DISCARD std::shared_ptr<peak::core::Buffer> GetParentBuffer() const;

private:
    explicit ImageView(const detail::ExtractedPayload& payload, std::shared_ptr<peak::common::Metadata> metadata);
    std::shared_ptr<peak::common::Metadata> m_metadata;
    std::weak_ptr<peak::core::Buffer> m_parentBuffer;
    const detail::ExtractedPayload m_payload;
};

} // namespace core
} // namespace peak
