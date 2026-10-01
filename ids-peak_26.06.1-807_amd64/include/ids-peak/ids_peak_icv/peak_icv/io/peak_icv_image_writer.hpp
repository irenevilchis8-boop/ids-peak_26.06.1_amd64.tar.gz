/*!
 * \file    peak_icv_image_writer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-01-30
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/peak_icv_image.hpp>

#include <string>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_io
 *
 * \brief Provides functionality to write images to files
 *        in various supported formats.
 *
 * \since ids_peak_icv 1.0
 */
class ImageWriter
{
public:
    /*! \brief Saves the specified image to a file.
     *
     * The file format is determined
     * by the specified file extension of the file name.
     *
     * Supported image formats (with required file extensions):
     * - PNG (.png) – Portable Network Graphics
     * - BMP (.bmp) – Bitmap
     * - JPEG (.jpeg) – Joint Photographic Experts Group
     * - TIFF (.tiff) – \htmlonly Tag Image File Format\endhtmlonly
     * - RAW (.raw) – Raw Binary Format
     * - HDR (.hdr) – High Dynamic Range Format
     *
     * Compression settings:
     * - JPEG: 75% quality
     * - PNG: 100% quality
     *
     * ### Supported pixel formats per image format
     *
     * #### BMP:
     * \supportedPixelformats{ImageSave_BMP}
     *
     * #### JPEG:
     * \supportedPixelformats{ImageSave_JPEG}
     *
     * #### PNG:
     * \supportedPixelformats{ImageSave_PNG}
     *
     * \note When saving *BGR* formats to PNG, they are written as *RGB*.
     *
     * #### TIFF:
     * \supportedPixelformats{ImageSave_TIFF}
     *
     * \note When saving floating‑point images to TIFF:
     *    Not all image viewers support displaying TIFF files
     *    that store floating‑point pixel data.
     *    The saved TIFF file is intended primarily as a data container
     *    that allows this library to reliably write
     *    and later re‑read the data.
     *
     * #### RAW:
     * \supportedPixelformats{ImageSave_RAW}
     *
     * #### HDR:
     * \supportedPixelformats{ImageSave_HDR}
     *
     * See the \ref concept_type_pixel_format for a detailed description of the pixel formats.
     *
     * \param[in] filePath The path of the file to write to, as a UTF-8 encoded string.
     * \param[in] image    The image to save.
     *
     * \throws NotSupportedException The specified file extension or pixel format is not supported.
     * \throws IOException           The specified file path is invalid or lacks write permissions.
     *
     * \since ids_peak_icv 1.0
     */
    void Write(const std::string& filePath, const Image& image) const;
};

inline void ImageWriter::Write(const std::string& filePath, const Image& image) const
{
    detail::ExecuteAndMapReturnCodes([&]() {
        auto* handle = peak::common::detail::BackendAccessor<Image>::BackendHandle(image);
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_SaveToFile(handle, filePath.c_str());
    });
}

} /* namespace icv */
} /* namespace peak */
