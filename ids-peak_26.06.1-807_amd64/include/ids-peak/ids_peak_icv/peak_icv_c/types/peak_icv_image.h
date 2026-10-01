/*!
 * \file    peak_icv_image.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-06-19
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/types/peak_common_pixel_format.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_extrinsic_parameters.h>
#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_metadata.h>
#include <peak_icv_c/types/peak_icv_region.h>

#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>

extern "C" {
#else
#    include <stdbool.h>
#    include <stddef.h>
#    include <stdint.h>
#endif

struct peak_icv_image;
typedef struct peak_icv_image* peak_icv_image_handle;

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief The peak_icv_image_info struct holds necessary information to create an image with \ref peak_icv_Image_CreateFromImageInfo.
 * In addition it can be used to query information about an existing image with \ref peak_icv_Image_GetInfo.
 */
typedef struct peak_icv_image_info
{
    /*! Image pixel format. */
    enum peak_common_pixel_format pixelFormat;
    /*! Image size in pixels. */
    peak_common_size size;
    /*! Size of image buffer. */
    size_t bufferSize;
    /*! Image buffer. */
    uint8_t* buffer;
} peak_icv_image_info;

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Binning factor in x and y direction.
 */
typedef peak_common_point_u peak_icv_binning_factor;

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Downsampling factor in x and y direction.
 */
typedef peak_common_point_u peak_icv_downsampling_factor;

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Region of interest of an image.
 */
typedef peak_common_rectangle_u peak_icv_region_of_interest;

/* \cond DEPRECATED */
/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Information about the image capturing (e.g. binning).
 */
typedef struct peak_icv_capture_information
{
    /*! Binning factor */
    peak_icv_binning_factor binning_factor;
    /*! The timestamp in nanoseconds
     *  The point in camera time at which the image was exposed. The timestamp starts at 0 at camera startup.
     */
    uint64_t relative_timestamp;
    /*! Region of interest */
    peak_icv_region_of_interest region_of_interest;
    /*! Exposure time */
    double exposure_time;
    /*! Part a of the exposure time sequence */
    double exposure_time_a;
    /*! Part b of the exposure time sequence */
    double exposure_time_b;
    /*! Part c of the exposure time sequence */
    double exposure_time_c;
    /*! Part d of the exposure time sequence */
    double exposure_time_d;
    /*! Gain */
    double gain;
    /*! Part a of the gain sequence */
    double gain_a;
    /*! Part b of the gain sequence */
    double gain_b;
    /*! Part c of the gain sequence */
    double gain_c;
    /*! Part dof the gain sequence */
    double gain_d;

    /*! \brief Reserved */
    uint8_t reserved[24];
} peak_icv_capture_information PEAK_COMMON_DEPRECATED_MSG("This struct has been replaced by metadata.");

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Creates an image with constant gray value 0.
 *
 * \param[out] image_handle Pointer to a variable that will store the handle to the created image.
 * \param[in]  pixelformat  Pixel format of the new image.
 * \param[in]  size         Size (width and height) of the new image in pixels.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p image_handle is an invalid handle.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The given handle \p image_handle already exists.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS_DEPRECATED("Use peak_icv_Image_CreateWithZeroInit instead.")
    peak_icv_Image_Create(peak_icv_image_handle* image_handle, enum peak_common_pixel_format pixelformat, peak_common_size size);
/* \endcond */

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Creates an image from a size.
 *
 * \param[out] image_handle Pointer to a variable that will store the handle to the created image.
 * \param[in]  pixelformat  Pixel format of the new image.
 * \param[in]  size         Size (width and height) of the new image in pixels.
 * \param[in]  zero_init    Whether to zero initialize the memory.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p image_handle is an invalid handle.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The given handle \p image_handle already exists.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.4
 */
PEAK_ICV_API_STATUS peak_icv_Image_CreateWithZeroInit(
    peak_icv_image_handle* image_handle, enum peak_common_pixel_format pixelformat, peak_common_size size, bool zero_init);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Creates an image based on the given image info.
 *
 * \param[out] image_handle    Pointer to a variable that will store the handle to the created image.
 * \param[in]  image_info      Contains the image information as pixel format, image size in pixels, buffer and buffer size.
 * \param[in]  image_info_size Size of the image_info struct. (Due to new versions the image_info_size can increase over time).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          \p image_handle is an invalid handle.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The given handle \p image_handle already exists.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     \p image_info_size or buffer_size in image_info is too small.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_CreateFromImageInfo(
    peak_icv_image_handle* image_handle, peak_icv_image_info image_info, size_t image_info_size);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Loads the image from a file.
 *
 * The file format is specified by the file ending (e.g.: ".png").
 *
 * The following image formats are supported:
 *
 * - Portable Network Graphics (PNG)
 * - Bitmap (BMP)
 * - Joint Photographic Experts Group (JPEG)
 * - Raw Binary Format (RAW)
 *
 * ### Supported image and pixel formats
 *
 * #### BMP (Bitmap)
 *
 *      Not all pixel formats can be read from a Bitmap file. Supported pixel formats are:
 *
 *      - Mono8
 *      - Mono10
 *      - Mono12
 *      - RGBa8
 *      - BGR8
 *      - BGRa8
 *
 * #### JPEG (Joint Photographic Experts Group)
 *
 *      Not all pixel formats can be read from a JPEG file. Supported pixel formats are:
 *
 *      - Mono8
 *      - RGB8
 *
 * #### PNG (Portable Network Graphics)
 *
 *      Not all pixel formats can be read from a PNG file. Supported pixel formats are:
 *
 *      - Mono8
 *      - Mono10
 *      - Mono12
 *      - RGB8
 *      - RGBa8
 *
 * #### RAW (Raw Binary Format)
 *
 *      Not all pixel formats can be read from a RAW file. Supported pixel formats are:
 *
 *      - Mono8
 *      - Mono10
 *      - Mono12
 *      - RGB8
 *      - RGBa8
 *      - BGR8
 *      - BGRa8
 *
 * \note The handle is implicitly created during loading, eliminating the need for explicit allocation.
 *
 * \param[in,out] image_handle      Image handle.
 * \param[in]     file_path         An existing file path to an image file.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_IO_ERROR                Indicates that the file could not be read due to an I/O error, such as missing
permissions or non-existent file.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           Reading of .tiff files for this pixelformat is not supported by this function,
please call peak_icv_Image_CreateFromFileWithPixelFormat.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_CreateFromFile(peak_icv_image_handle* image_handle, const char* file_path);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Loads the image from a file with forced pixel format.
 *
 * The pixel format to use is specified manually here. The function tries to interpret the file with the given format. If this isn't
 * possible, an exception is thrown.
 * Explicit conversion of image formats must be done manually.
 *
 * The following image formats are supported:
 *
 * - Portable Network Graphics (PNG)
 * - Bitmap (BMP)
 * - Joint Photographic Experts Group (JPEG)
 * - Tag Image File Format (TIFF)
 * - Raw Binary Format (RAW)
 *
 * ### Supported image and pixel formats
 *
 * #### BMP (Bitmap)
 *
 *      Not all pixel formats can be read from a Bitmap file. Supported pixel formats are:
 *
 *      - Mono8
 *      - Mono10
 *      - Mono12
 *      - RGBa8
 *      - BGR8
 *      - BGRa8
 *
 * #### JPEG (Joint Photographic Experts Group)
 *
 *      Not all pixel formats can be read from a JPEG file. Supported pixel formats are:
 *
 *      - Mono8
 *      - RGB8
 *
 * #### PNG (Portable Network Graphics)
 *
 *      Not all pixel formats can be read from a PNG file. Supported pixel formats are:
 *
 *      - Mono8
 *      - Mono10
 *      - Mono12
 *      - RGB8
 *      - RGBa8
 *
 * #### RAW (Raw Binary Format)
 *
 *      Not all pixel formats can be read from a RAW file. Supported pixel formats are:
 *
 *      - Mono8
 *      - Mono10
 *      - Mono12
 *      - RGB8
 *      - RGBa8
 *      - BGR8
 *      - BGRa8
 *
 * #### TIFF (Tag Image File Format)
 *
 *      Not all pixel formats can be read from a TIFF file. Supported pixel formats are:
 *
 *      - Mono8
 *      - RGB8
 *      - Coord3D_C32f
 *
 * #### HDR (High Dynamic Range Format)
 *
 *      Not all pixel formats can be read from an HDR file. Supported pixel formats are:
 *
 *      - Mono32f
 *      - RGB32f
 *
 * \note The handle is implicitly created during loading, eliminating the need for explicit allocation.
 *
 * \param[in,out] image_handle       Image handle.
 * \param[in]     file_path          An existing file path to an image file.
 * \param[in]     forced_pixelformat Pixel format the loaded image is forced to use.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_IO_ERROR                The \p file_path has to exist.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_CreateFromFileWithPixelFormat(
    peak_icv_image_handle* image_handle, const char* file_path, enum peak_common_pixel_format forced_pixelformat);

/*!
 * Creates a deep copy of the source_image_handle, including its region and metadata.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE            The given handle \p image_handle already exists.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_image
 */
PEAK_ICV_API_STATUS peak_icv_Image_CreateFromExistingImage(
    peak_icv_image_handle* image_handle, peak_icv_image_handle source_image_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Saves the specified image to a file.
 *
 * The file format is determined
 * by the specified file extension of the file name.
 *
 * Supported image formats (with required file extensions):
 * - PNG (.png) – Portable Network Graphics
 * - BMP (.bmp) – Bitmap
 * - JPEG (.jpeg) – Joint Photographic Experts Group
 * - TIFF (.tiff) – Tag Image File Format
 * - RAW (.raw) – Raw Binary Format
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
 *   Not all image viewers support displaying TIFF files
 *   that store floating‑point pixel data.
 *   The saved TIFF file is intended primarily as a data container
 *   that allows this library to reliably write
 *   and later re‑read the data.
 *
 * #### RAW:
 * \supportedPixelformats{ImageSave_RAW}
 *
 * #### HDR:
 * \supportedPixelformats{ImageSave_HDR}
 *
 * See the \ref concept_type_pixel_format for a detailed description of the pixel formats.
 *
 * \param[in] image_handle The image to save.
 * \param[in] file_path    The path of the file to write to, as a UTF-8 encoded string.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p `image_handle` must be created first.
 * \return #PEAK_ICV_STATUS_IO_ERROR                The \p `file_path` is invalid or lacks write permissions.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p `file_path` is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_SaveToFile(peak_icv_image_handle image_handle, const char* file_path);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Increases the use count of the specified image_handle. In order to decrease it, you need to call
 * \ref peak_icv_Image_Destroy. If you copy the image, you should call this method, because otherwise, when one
 * handle will be destroyed, the other will be invalid.
 *
 * \param[in] image_handle      Image handle (which was copied).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_IncreaseUseCount(peak_icv_image_handle image_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Destroys an image handle.
 *
 * \destroyHandle{image}
 *
 * \param[in] image_handle Image handle to destroy.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle does not exist, it must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_Destroy(peak_icv_image_handle image_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief
 *   Converts the specified image to a different pixel format.
 *
 * If the input image has the same pixel format as the specified pixel format parameter,
 * the image will be copied.
 *
 * For a full list of supported conversions see \ref concept_supported_pixel_format_conversion.
 *
 * \note
 *   The output image has to be created with the correct size and pixel format already,
 *   ideally with \ref  peak_icv_Image_Create.
 *   The image data in the output image will be overwritten.
 *
 * \param[in]  input_image_handle      Image handle which is converted.
 * \param[in]  destination_pixelformat Resulting pixel format.
 * \param[out] output_image_handle     Image handle of the new image.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The conversion into \p destination_pixelformat is not supported
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_image_handle and \p output_image_handle must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_ConvertPixelFormat(peak_icv_image_handle input_image_handle,
    enum peak_common_pixel_format destination_pixelformat, peak_icv_image_handle output_image_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Converts an image into another pixel format with a factor multiplied to every pixel.
 *
 * Supported conversions:
 * From peak_common_pixel_format::PEAK_COMMON_PIXEL_FORMAT_COORD3D_C8 or
 * peak_common_pixel_format::PEAK_COMMON_PIXEL_FORMAT_COORD3D_C16
 * to peak_common_pixel_format::PEAK_COMMON_PIXEL_FORMAT_COORD3D_C32F
 *
 * \note The output image has to be created with the correct size and pixel format already, ideally with \ref peak_icv_Image_Create.
 * The image data in the output image will be overwritten.
 *
 * \param[in]  input_image_handle      Image handle which is converted.
 * \param[in]  destination_pixelformat Resulting pixel format.
 * \param[in]  factor                  The multiplication factor
 * \param[out] output_image_handle     Image handle of the new image.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The conversion into \p destination_pixelformat is not supported
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_image_handle and \p output_image_handle must be created first.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            A factor of 0.0 was given.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since 1.1
 */
PEAK_ICV_API_STATUS peak_icv_Image_ConvertPixelFormatWithFactor(peak_icv_image_handle input_image_handle,
    enum peak_common_pixel_format destination_pixelformat, double factor, peak_icv_image_handle output_image_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Queries information about the already created \p image_handle.
 *
 * \param[in] image_handle    Image handle
 * \param[out] image_info     Information about \p image_handle
 * \param[in] image_info_size Size of the \p image_info
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p image_info is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The \p image_info_size is too small.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_GetInfo(
    peak_icv_image_handle image_handle, peak_icv_image_info* image_info, size_t image_info_size);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Retrieves the region associated with the specified image_handle.
 *
 * \param[in]  image_handle   Image handle for which to retrieve the region.
 * \param[out] region_handle  Pointer to a variable that will store the handle to the retrieved region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle must be created first or the \p region_handle is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_GetRegion(peak_icv_image_handle image_handle, peak_icv_region_handle* region_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Sets the region for the specified image_handle.
 *
 * This function sets a region of interest (ROI) for the specified image handle,
 * which defines a sub-area of the image where operations or analyses are focused.
 * Any points in the region that fall outside the bounds of the image are automatically
 * discarded (clipped).
 *
 * \param[in] image_handle    Image handle for which to set the region.
 * \param[in] region_handle   Handle to the region to set.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle or \p region_handle must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_SetRegion(peak_icv_image_handle image_handle, peak_icv_region_handle region_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Resets the region associated with the specified image_handle to the complete image.
 *
 * \param[in] image_handle   Image handle for which to reset the region.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle must be created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_ResetRegion(peak_icv_image_handle image_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Compares the image in \p image_handle_lhs to the image in \p image_handle_rhs and stores the result in is_equal.
 *
 * \param[in]  image_handle_lhs Image to compare.
 * \param[in]  image_handle_rhs Image to compare.
 * \param[out] is_equal         Comparison Result.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle_lhs or \p image_handle_rhs must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p is_equal is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_Compare(
    peak_icv_image_handle image_handle_lhs, peak_icv_image_handle image_handle_rhs, bool* is_equal);

/* \cond DEPRECATED */
PEAK_COMMON_BEGIN_DISABLE_DEPRECATED_WARNINGS
/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Retrieves the image capture information associated with the specified image_handle.
 *
 * \param[in]  image_handle             Image handle for which to retrieve the region.
 * \param[out] capture_information      Pointer to a variable that will store the image capture information.
 * \param[in]  capture_information_size Size of the image capture information.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p image_capture_information is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The \p capture_information buffer is to small.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS_DEPRECATED("This function has been replaced by peak_icv_Image_GetMetadata.")
    peak_icv_Image_GetCaptureInformation(
        peak_icv_image_handle image_handle, peak_icv_capture_information* capture_information, size_t capture_information_size);
PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS

PEAK_COMMON_BEGIN_DISABLE_DEPRECATED_WARNINGS
/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Sets the capture information associated with the specified image_handle.
 *
 * \param[in]  image_handle             Image handle for which to retrieve the region.
 * \param[out] capture_information      Image capture information to a variable that will store the image capture information.
 * \param[in]  capture_information_size Size of the image capture information.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle must be created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p image_capture_information is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The \p capture_information buffer is to small.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS_DEPRECATED("This function has been replaced by peak_icv_Image_SetMetadata.")
    peak_icv_Image_SetCaptureInformation(
        peak_icv_image_handle image_handle, peak_icv_capture_information capture_information, size_t capture_information_size);
PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS
/* \endcond */

/*!
 * \ingroup ids_peak_icv_c_image
 * \brief Subtracts the image in \p image_handle_subtrahend pixelwise from the image in \p image_handle_minuend and stores the result in image_handle_difference.
 *
 * \param[in]  image_handle_minuend    Image to subtract from.
 * \param[in]  image_handle_subtrahend Subtracted image.
 * \param[out] image_handle_difference Subtraction Result.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p image_handle_minuend or \p image_handle_subtrahend must be created first.
 * \return #PEAK_ICV_STATUS_MISMATCH                The given images have different pixel formats or sizes.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_Subtract(peak_icv_image_handle image_handle_minuend,
    peak_icv_image_handle image_handle_subtrahend, peak_icv_image_handle image_handle_difference);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Transforms a Cartesian coordinate image to workspace coordinates
 *        using the specified extrinsic parameters.
 *
 * Transforms an image of pixel format `Coord3D_ABC32f`
 * from the camera coordinate system
 * to the workspace coordinate system
 * using the inverse of the specified extrinsic parameters.
 *
 * \param[in]  input_image_handle        Handle to the input image to be transformed.
 * \param[in]  extrinsic_parameters      Extrinsic parameters from the workspace calibration.
 * \param[in]  extrinsic_parameters_size Size of the extrinsic parameters.
 * \param[out] output_image_handle       Handle to the output image that stores the transformed result.
 *                                       This handle must be created before the function is called.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_image_handle or \p output_image_handle must be created first.
 * \retval #PEAK_ICV_STATUS_NOT_SUPPORTED           The pixel format is not supported.
 * \retval #PEAK_ICV_STATUS_MISMATCH                The given images have different pixel formats.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.1
 */
PEAK_ICV_API_STATUS peak_icv_Image_TransformToWorkspace(peak_icv_image_handle input_image_handle,
    peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_image_handle output_image_handle);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Crops the given image to the rectangle and stores the result in the output image.
 *
 * \note The output image must have the size of the rectangle and the pixel format of the input image.
 *
 * \param input_image_handle  Handle to the input image that is to be cropped.
 * \param output_image_handle Handle to the output image that stores the cropped image. This handle must be created with the correct size and pixel format first.
 * \param rectangle           The rectangular region to which the image will be cropped.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_image_handle or \p output_image_handle must be created first.
 * \return #PEAK_ICV_STATUS_MISMATCH                The given images have different pixel formats or the size of the output image does not match.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_Crop(
    peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle, peak_common_rectangle rectangle);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Scales the image in \p input_image_handle to the \p output_size in pixels
 *        using the \p interpolation method
 *        and stores the result in \p output_image_handle.
 *
 * Internally the scale factors are computed as follows:
 * - Horizontal scale factor (X-axis) = Input image width / Output image width
 * - Vertical scale factor (Y-axis) = Input image height / Output image height
 *
 * These factors determine how the input image is resized to match the desired output dimensions.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_image_handle or \p output_image_handle must be created first.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The interpolation method is not supported.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Image_Scale(
    peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle, peak_icv_interpolation interpolation);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Deinterleaves images of a specialized HDR pixel format into individual images.
 *
 * The function separates the multiple exposures or gains embedded in the combined HDR raw \p input_image_handle
 * and provides them as independent \p output_image_handles,
 * each with the correctly associated exposure information.
 *
 * \param input_image_handle   Image to deinterleave into individual images.
 * \param output_image_handles Images deinterleaved from input image.
 *                             Call \ref peak_icv_Image_Deinterleave_GetOutputPixelFormat to get the correct output pixel format and call
 *                             \ref peak_icv_Image_Deinterleave_GetOutputImageSize for the correct output image size.
 * \param output_image_count   The number of handles in the array passed with output_image_handles.
 *                             Call \ref peak_icv_Image_Deinterleave_GetOutputImageCount to get the number of images one will get for the
 * input image.
 *
 * \supportedPixelformats{ImageDeinterleave}
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p input_image_handle or \p output_image_handles must be created first.
 * \return #PEAK_ICV_STATUS_MISMATCH                The \p output_image_handles must be object wise different or does not match the needed output pixel format.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The \p output_image_handles count must match the needed number of images stored in \p input_image_handle.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Image_Deinterleave(
    peak_icv_image_handle input_image_handle, peak_icv_image_handle* output_image_handles, size_t output_image_count);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Retrieves the \p output_pixel_format for deinterleaving an image with \ref peak_icv_Image_Deinterleave.
 *
 * \param input_pixel_format    Pixel format of the image to deinterleav with \ref peak_icv_Image_Deinterleave
 * \param output_pixel_format   Pixel format of the deinterleaved images.
 *
 * \supportedPixelformats{ImageDeinterleave}
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The \p input_pixel_format is not supported for deinterleaving channels.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p output_pixel_format is an invalid pointer.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Image_Deinterleave_GetOutputPixelFormat(
    peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Retrieves the number of images deinterleaved with \ref peak_icv_Image_Deinterleave.
 *
 * \param input_pixel_format    Pixel format of the image to deinterleave with \ref peak_icv_Image_Deinterleave
 * \param output_image_count    Number of images which are deinterleaved.
 *
 * \supportedPixelformats{ImageDeinterleave}
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The \p input_pixel_format is not supported for deinterleaving.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p output_image_count is an invalid pointer.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Image_Deinterleave_GetOutputImageCount(
    peak_common_pixel_format input_pixel_format, size_t* output_image_count);

/*!
 * \ingroup ids_peak_icv_c_image
 *
 * \brief Retrieves the size of the images deinterleaved by \ref peak_icv_Image_Deinterleave.
 *
 * \param input_pixel_format    Pixel format of the image to deinterleave with \ref peak_icv_Image_Deinterleave
 * \param input_image_size      Image size of the image to deinterleave with \ref peak_icv_Image_Deinterleave
 * \param output_image_size     Image size of images which are deinterleaved.
 *
 * \supportedPixelformats{ImageDeinterleave}
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED           The \p input_pixel_format is not supported for deinterleaving.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p output_image_size is an invalid pointer.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Image_Deinterleave_GetOutputImageSize(
    peak_common_pixel_format input_pixel_format, peak_common_size input_image_size, peak_common_size* output_image_size);

/*!
 * \details
 *      All pixel formats are supported.
 *
 * \param[out] metadata_handle
 *     Must be initialized prior to execution with \ref peak_icv_Metadata_Create.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_NULL_POINTER
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE

 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_image
 */
PEAK_ICV_API_STATUS peak_icv_Image_GetMetadata(peak_icv_image_handle image_handle, peak_icv_metadata_handle* metadata_handle);

/*!
 * \details
 *     All pixel formats are supported.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE

 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_image
 */
PEAK_ICV_API_STATUS peak_icv_Image_SetMetadata(peak_icv_image_handle image_handle, peak_icv_metadata_handle metadata_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
