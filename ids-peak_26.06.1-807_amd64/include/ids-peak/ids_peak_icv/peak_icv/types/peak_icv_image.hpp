/*!
 * \file    peak_icv_image.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-05-20
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once


#include <peak_common/types/geometry/peak_common_rectangle.hpp>
#include <peak_common/types/geometry/peak_common_size.hpp>
#include <peak_common/types/peak_common_pixel_format.hpp>
#include <peak_icv/algorithms/transformations/peak_icv_interpolation.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <memory>

#ifdef WITH_peak_ipl
#    include <peak_ipl/types/peak_ipl_image.hpp>
#endif

#include <peak_common/types/peak_common_iimageview.hpp>

struct peak_icv_image_info;
struct peak_icv_image;
using peak_icv_image_handle = peak_icv_image*;

namespace peak
{
namespace icv
{

class ImageWriter;

/*!
 * \ingroup ids_peak_icv_cpp_types
 *
 * \brief For detailed information about the use of ids_peak_icv Image refer to the \ref concept_type_image "Image Guide"
 *
 * \since ids_peak_icv 1.0
 */
class Image : private detail::IBackendAccessible<Image>
{
public:
#ifdef WITH_peak_ipl
    /*!
     * \brief Constructs an Image from an existing peak image.
     *
     * \note The image memory is not copied. Please do not delete the peak::ipl::Image while still using this image.
     *
     * \param image existing peak image
     *
     * \since ids_peak_icv 1.0
     */
    Image(const peak::ipl::Image& image); // NOLINT
#endif

    /**
     * \brief Constructs an Image from an IImageView Instance.
     *
     * This can be a buffer or a possibility to convert other libraries Images into this Image type.
     *
     * \param imageView Abstract Image source
     *
     * \since ids_peak_icv 1.0
     */
    explicit Image(const peak::common::IImageView& imageView);

    /*!
     * \brief Constructs an Image from a file path.
     *
     * The following image formats are supported:
     *
     * - Bitmap (BMP)
     * - Joint Photographic Experts Group (JPEG)
     * - Portable Network Graphics (PNG)
     * - Raw Binary Format (RAW)
     *
     * ### Supported image and pixel formats
     *
     * #### BMP:
     * \supportedPixelformats{ImageLoad_BMP}
     * #### JPEG:
     * \supportedPixelformats{ImageLoad_JPEG}
     * #### PNG:
     * \supportedPixelformats{ImageLoad_PNG}
     * #### RAW:
     * \supportedPixelformats{ImageLoad_RAW}
     *
     * See the \ref concept_type_pixel_format for a detailed description of the pixel formats.
     *
     * \param path The file path to the image.
     *
     * \since ids_peak_icv 1.0
     */
    explicit Image(const std::string& path);

    /*!
     * \brief
     *   Constructs an Image from a file path with a specified pixel format.
     *
     * This constructor loads an image from the given file path
     * and forces the use of the specified pixel format.
     * The function attempts to interpret the file using the provided format.
     * If interpretation fails, an exception is thrown.
     * Explicit conversion between image formats must be handled manually by the user.
     *
     * The following image formats are supported:
     *
     * - Bitmap (BMP)
     * - Joint Photographic Experts Group (JPEG)
     * - Portable Network Graphics (PNG)
     * - \htmlonly Tag Image File Format (TIFF)\endhtmlonly
     * - Raw Binary Format (RAW)
     * - High Dynamic Range Format (HDR)
     *
     * ### Supported image and pixel formats
     *
     * #### BMP:
     * \supportedPixelformats{ImageLoad_BMP}
     * #### JPEG:
     * \supportedPixelformats{ImageLoad_JPEG}
     * #### PNG:
     * \supportedPixelformats{ImageLoad_PNG}
     * #### TIFF:
     * \supportedPixelformats{ImageLoad_TIFF}
     * #### RAW:
     * Only the following formats are supported
     * and must match the format used when saving:
     * \supportedPixelformats{ImageLoad_RAW_WithPixelFormat}
     * #### HDR:
     * \supportedPixelformats{ImageLoad_HDR}
     *
     *
     * See the \ref concept_type_pixel_format for a detailed description of the pixel formats.
     */
    explicit Image(const std::string& path, peak::common::PixelFormat name);

    /*!
     * \brief Constructs an Image from a buffer.
     *
     * \param pixelFormat The pixel format of the image.
     * \param buffer The buffer containing image data.
     * \param bufferSize The size of the buffer.
     * \param imageSize The size of the image in pixels.
     *
     * \since ids_peak_icv 1.0
     */
    Image(peak::common::PixelFormat pixelFormat, uint8_t* buffer, size_t bufferSize, const peak::common::Size& imageSize);

    /*!
     * \brief Constructs an Image with a given size and pixel format.
     *
     * \param pixelFormat The pixel format of the image.
     * \param imageSize The size of the image in pixels.
     *
     * \since ids_peak_icv 1.0
     */
    Image(peak::common::PixelFormat pixelFormat, const peak::common::Size& imageSize);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    Image(const Image& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    Image(Image&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    Image& operator=(const Image& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    Image& operator=(Image&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~Image() override;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    bool operator==(const Image& rhs) const;

    /*!
     * \return A deep copy of the image, including its region and metadata.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD Image Copy() const;

    /*!
     * \brief Provides the size of the image in pixels.
     *
     * \return The size of the image in pixels.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Size GetSize() const;

    /*!
     * \brief Provides a pointer to the image data buffer.
     *
     * \return A pointer to the image data buffer.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint8_t* GetData() const;

    /*!
     * \brief Provides the size of the image data in bytes.
     *
     * \return The size of the image data in bytes.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetSizeInBytes() const;

    /*!
     * \brief Computes the number of bytes required to store one line of pixel data (no padding).
     *
     * This returns the exact number of bytes used for one scanline of pixel data based on the image's
     * width, number of channels, and bits per pixel.
     *
     * \return Number of bytes per line of pixel data.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetBytesPerLine() const;


    /*!
     * \brief Provides the pixel format of the image.
     *
     * \return The pixel format of the image.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::PixelFormat GetPixelFormat() const;

    /*!
     * \brief Provides the region of the image.
     *
     * \return The region of the image.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Region GetRegion() const;

    /*!
     * \brief Updates the region on the image.
     *
     * Sets a region of interest (ROI) for the specified image handle,
     * which defines a sub-area of the image where operations or analyses are focused.
     * Any points in the region that fall outside the bounds of the image are automatically discarded (clipped).
     *
     * \param region Region to update
     *
     * \since ids_peak_icv 1.1
     */
    void SetRegion(const Region& region) const;

    /*!
     * \brief Resets the region on the image to the complete image.
     *
     * \since ids_peak_icv 1.1
     */
    void ResetRegion() const;

    /*!
     * \brief Provides a pointer to the data at the specified coordinates.
     *
     * \tparam DataType The type of the data to retrieve.
     * \param x The x-coordinate.
     * \param y The y-coordinate.
     * \return A pointer to the data at the specified coordinates.
     *
     * \since ids_peak_icv 1.0
     */
    template <typename DataType>
    PEAK_COMMON_NO_DISCARD DataType* At(size_t x, size_t y) const
    {
        return reinterpret_cast<DataType*>(m_buffer + (x + y * m_size.GetWidth()) * m_pixelFormatInfo.GetAllocatedBitsPerPixel() / 8);
    }

    /*!
     * \brief
     *   Converts the image to a different pixel format.
     *
     * If the input image has the same pixel format as the specified pixel format parameter,
     * the image will be copied.
     *
     * **Restrictions**:
     * - Conversion to Bayer formats is only supported from a bayer format with the same pattern,
     *   e.g. from BayerRG10p to BayerRG10 or BayerRG8.
     * - Conversion to packed formats is not supported.
     * - Conversions from RGB or BGR formats to RGBa or BGRa formats is not supported.
     * - RGBa and BGRa formats support only conversions into different bit depths of the same channel layout
     *   or to Mono formats.
     * - Confidence and Coord3D formats can only be converted to other bit depths of the same format type.
     *
     * \note
     *   For a full list of supported conversions see \ref concept_supported_pixel_format_conversion.
     *
     * \param pixelFormat The target pixel format.
     *
     * \return A new Image with the target pixel format.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD Image ConvertPixelFormat(peak::common::PixelFormat pixelFormat) const;

    /*!
     * \brief
     *    Converts the image to the pixel format specified in the previously created destination image.
     *
     * Use this function if you already have a previously created image
     * and want to avoid unnecessary memory allocations or copies.
     *
     * If the input image has the same pixel format as the target pixel format,
     * the image will be copied.
     *
     * **Restrictions**:
     * - Conversion to Bayer formats is only supported from a bayer format with the same pattern,
     *   e.g. from BayerRG10p to BayerRG10 or BayerRG8.
     * - Conversion to packed formats is not supported.
     * - Conversions from RGB or BGR formats to RGBa or BGRa formats is not supported.
     * - RGBa and BGRa formats support only conversions into different bit depths of the same channel layout
     *   or to Mono formats.
     * - Confidence and Coord3D formats can only be converted to other bit depths of the same format type.
     *
     * \note For a full list of supported conversions see \ref concept_supported_pixel_format_conversion.
     *
     * \param destinationImage
     *    The size of the source image must match the size of the destination image.
     *
     * \throws MismatchException The source size does not match the destination image size.
     * \throws NotSupportedException The conversion of the source pixel format into the destination pixel format is currently not supported.
     *
     * \since ids_peak_icv 1.4
     */
    void ConvertPixelFormat(Image& destinationImage) const;

    /*!
     * \brief Converts an image into another pixel format with a factor multiplied to every pixel.
     *
     * If the input image has the same pixel format as the specified pixel format parameter, the image will be copied.
     *
     * Supported conversions:
     * From PixelFormat::Coord3D_C8 or PixelFormat::Coord3D_C16 to PixelFormat::Coord3D_C32f
     *
     * \param pixelFormat The target pixel format.
     * \param factor The multiplication factor
     * \return A new Image with the target pixel format.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image ConvertPixelFormatWithFactor(
        peak::common::PixelFormat pixelFormat, const double factor) const;

    /*!
     * \brief Splits an image with an interleaved pixel format into individual images.
     *
     * The function separates e.g. multiple exposures embedded in the combined HDR raw image
     * and provides them as independent images,
     * each with the correctly associated exposure information.
     *
     * \supportedPixelformats{ImageDeinterleave}
     *
     * \return A vector where each element represents one of the interleaved images.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD std::vector<Image> Deinterleave() const;

    /*!
     * \brief Updates the Metadata of an image which is used to store and manage capture information.
     *
     * \param metadata Metadata to be updated
     *
     * \since ids_peak_icv 1.1
     */
    void SetMetadata(const peak::common::Metadata& metadata);

    /*!
     * \brief Returns the Metadata of an image which contains information about the image capture information.
     *
     * \return The Metadata of the image
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::Metadata GetMetadata() const;

    /*!
     * \brief Subtracts the specified \p subtrahend image pixelwise from the current image and returns the resulting image.
     *
     * This function performs a pixelwise subtraction of the given \p subtrahend image from the current image.
     * The resulting image is returned as a new `Image` object.
     * The operation requires that both images have the same pixel format and dimensions.
     *
     * \param subtrahend The image to subtract from the current image.
     *
     * \supportedPixelformats{ImageMathematics}
     *
     * \return The resulting image after pixelwise subtraction.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Image Subtract(const Image& subtrahend) const;

    /*!
     * \brief Subtracts the specified \p subtrahend image pixelwise from the current image and returns the resulting image.
     *
     * This function performs a pixelwise subtraction of the given \p subtrahend image from the current image.
     * The resulting image is returned as a new `Image` object.
     * The operation requires that both images have the same pixel format and dimensions.
     *
     * \param subtrahend The image to subtract from the current image.
     *
     * \supportedPixelformats{ImageMathematics}
     *
     * \return The resulting image after pixelwise subtraction.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Image operator-(const Image& subtrahend) const;

    /*!
     * \brief Crops the image to the given rectangle.
     *
     * \return The cropped image.
     *
     * \throws OutOfRangeException The given rectangle is (partly) outside the image.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD Image Crop(const peak::common::Rectangle& rect) const;

    /*!
     * \brief Returns an image scaled to the given image size.
     *
     * Internally the scale factors are computed as follows:
     * - Horizontal scale factor (X-axis) = Image width / Size width
     * - Vertical scale factor (Y-axis) =  Image height / Size height
     *
     * These factors determine how the input image is resized to match the desired output dimensions.
     *
     * \param targetImageSize     The image size to which the original image is scaled.
     * \param interpolation The interpolation method used to scale the image.
     *
     * \return The scaled image.
     *
     * \throws NotPossibleException The given targetImageSize is empty (i.e. width × height == 0).
     * \throws NotSupportedException The interpolation method is not supported.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD Image Scale(
        const peak::common::Size& targetImageSize, const Interpolation& interpolation = Interpolation::NearestNeighbor) const;

#ifdef WITH_peak_ipl
    /*!
     * \brief Implicit conversion to peak_ipl image
     *
     * \return A new instance of an peak_ipl image
     *
     * \since ids_peak_icv 1.0
     */
    operator peak::ipl::Image() const; // NOLINT
#endif

protected:
    /*!
     * \brief Provides the handle of the image.
     *
     * \return The handle of the image.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<Image> GetHandle() const override;

private:
    friend peak::common::detail::BackendAccessor<Image>;
    friend ImageWriter;

    explicit Image(peak_icv_image_handle imageHandle);
    Image(peak_icv_image_handle handle, peak_icv_image_info info);
    Image(peak::common::PixelFormat pixelFormat, const peak::common::Size& imageSize, bool zeroInitialize);

    static peak_icv_image_handle CreateFromFile(const std::string& path);
    static peak_icv_image_handle CreateFromFile(const std::string& path, peak::common::PixelFormat name);
    static peak_icv_image_info CreateFromHandle(peak_icv_image_handle handle);
    static peak_icv_image_handle CreateFromSize(
        peak::common::PixelFormat pixelFormat, const peak::common::Size& size, bool zeroInitialize);
    static peak_icv_image_handle CreateFromBuffer(
        peak::common::PixelFormat pixelFormat, const peak::common::Size& size, const uint8_t* buffer, size_t bufferSize);
    static peak_icv_image_handle CreateFromImageView(const peak::common::IImageView& imageView);

#ifdef WITH_peak_ipl
    PEAK_COMMON_NO_DISCARD peak::ipl::Image GetIPLImage() const;
#endif

    peak_icv_image_handle m_imageHandle{};
    peak::common::Size m_size;
    uint8_t* m_buffer;
    peak::common::PixelFormatInfo m_pixelFormatInfo;

#ifdef WITH_peak_ipl
    mutable peak::ipl::Image m_image;
#endif
};
} /* namespace icv */
} /* namespace peak */

#include <peak_icv/types/detail/peak_icv_image.ipp>
