/*!
 * \file    peak_common_iimageview.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_size.hpp>
#include <peak_common/types/peak_common_pixel_format.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

#include <cstddef>
#include <cstdint>
#include <memory>

namespace peak
{
namespace common
{

class Metadata;

/*!
 * \ingroup ids_peak_common_types
 * \brief Interface for viewing image pixel data from arbitrary sources.
 *
 * This interface defines a standard way to access image properties and raw
 * pixel data, enabling interoperability with different image processing
 * libraries or backends.
 *
 * \note The interface does <b>not</b> own the image memory. Lifetime management must be
 * handled externally.
 *
 * \since ids_peak_common 1.0
 */
class IImageView
{
public:
    virtual ~IImageView() = default;

    /*!
     * \brief Returns a pointer to the start of the first line that contains valid image data (read-only).
     * \return Pointer to the raw pixel data.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual const uint8_t* GetData() const = 0;

    /*!
     * \brief Returns a pointer to the start of the first line that contains valid image data (read-write).
     * \return Pointer to the raw pixel data.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual uint8_t* GetData() = 0;

    /*!
     * \brief Returns the byte offset to the first pixel of a line.
     * \return Line offset in bytes.
     *
     * \since ids_peak_common 1.2
     */
    PEAK_COMMON_NO_DISCARD virtual std::size_t GetLineStartOffset() const = 0;

    /*!
     * \brief Returns the total size of the image data in bytes.
     * \return Number of bytes occupied by the image in the buffer.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual std::size_t GetSizeInBytes() const = 0;

    /*!
     * \brief Returns the pixel format used by the image.
     * \return The PixelFormat of the image stored in the buffer.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual peak::common::PixelFormat GetPixelFormat() const = 0;

    /*!
     * \brief Returns a helper object describing the pixel format in detail.
     *
     * The PixelFormatInfo class provides methods to inspect the layout, size,
     * channel count, channel order, and other attributes of the format returned
     * by GetPixelFormat().
     *
     * \return An instance of PixelFormatInfo for querying format details.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual peak::common::PixelFormatInfo GetPixelFormatInfo() const = 0;

    /*!
     * \brief Returns the overall size of the image (width × height).
     * \return Size object containing width and height in pixels.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual Size GetSize() const = 0;

    /*!
     * \brief Returns the width of the image in pixels.
     * \return Number of pixels per row.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual uint32_t GetWidth() const = 0;

    /*!
     * \brief Returns the height of the image in pixels.
     * \return Number of rows in the image.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual uint32_t GetHeight() const = 0;

    /*!
     * \brief Returns the number of bits that each pixel occupies.
     * \return Bits per pixel.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual size_t GetBitsPerPixel() const = 0;

    /*!
     * \brief Returns the number of bytes in a single image row.
     * \return Bytes per line, including any padding.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual size_t GetBytesPerLine() const = 0;

    /*!
     * \brief Returns the metadata object which can be used to retrieve or set metadata belonging to the image.
     * \return Pointer to the metadata object
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual std::shared_ptr<peak::common::Metadata> GetMetadata() = 0;

    /*!
     * \brief Returns the metadata object which can be used to retrieve metadata belonging to the image.
     * \return Pointer to the metadata object
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual std::shared_ptr<const peak::common::Metadata> GetMetadata() const = 0;
};

} // namespace common 
} // namespace peak
