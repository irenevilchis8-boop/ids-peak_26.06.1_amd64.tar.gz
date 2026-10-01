/*!
 * \file    peak_icv_image_converter.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>

#ifdef __cplusplus
#    include <cstdint>
extern "C" {
#else
#    include <stdbool.h>
#    include <stddef.h>
#    include <stdint.h>
#endif


/*!
 * \defgroup ids_peak_icv_c_preprocessing_image_converter ImageConverter
 * \ingroup ids_peak_icv_c_preprocessing
 *
 * \brief ImageConverter is responsible for converting images between different pixel formats
 *
 * The ImageConverter module provides efficient pixel format conversion capabilities for image processing workflows.
 * It supports conversion between various pixel formats including RGB, BGR, YUV, grayscale, and other common formats
 * used in computer vision and image processing applications.
 *
 * Key features:
 * - High-performance pixel format conversions using optimized algorithms
 * - Support for multiple input and output pixel formats
 * - Internal buffer management for improved performance
 * - Memory-efficient processing with reusable buffer pools
 *
 * The module is designed to handle various conversion scenarios such as:
 * - Debayering
 * - Color space transformations (RGB ↔ YUV, etc.)
 * - Channel reordering (RGB ↔ BGR)
 * - Bit depth conversions (8-bit ↔ 16-bit)
 *
 * \note This module uses internal buffer pools to minimize memory allocations during conversions.
 * Use \ref peak_icv_Preprocessing_ImageConverter_ReleaseBuffers to free unused buffers when needed.
 * \since ids_peak_icv 1.0
 */
struct peak_icv_image_converter;
typedef struct peak_icv_image_converter* peak_icv_image_converter_handle;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_image_converter
 * \brief Creates a image converter object.
 *
 * Initializes a new image converter instance with default settings and empty buffer pools.
 * The converter is ready to use immediately after creation.
 *
 * \param[out] image_converter_handle           Handle for the image converter object.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ImageConverter_Create(peak_icv_image_converter_handle* image_converter_handle);


/*!
 * \ingroup ids_peak_icv_c_preprocessing_image_converter
 *
 * \brief Destroys an image converter handle.
 *
 * \destroyHandle{image converter}
 *
 * \param[in] image_converter_handle                     Image converter handle to destroy.
 *                                                       Must be a valid handle created by
 *                                                       \ref peak_icv_Preprocessing_ImageConverter_Create.
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p image_converter_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ImageConverter_Destroy(peak_icv_image_converter_handle image_converter_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_image_converter
 * \brief Converts an image from one pixel format to another.
 *
 * This method takes the provided input image and converts it to the specified pixel format.
 * A new image handle is created for the converted output image. The original input image
 * remains unchanged.
 *
 * The conversion process automatically handles:
 * - Color space transformations
 * - Channel reordering
 * - Bit depth adjustments
 * - Memory layout optimizations
 *
 * \param[in]  converter_handle                    Handle to the image converter object
 * \param[in]  input_handle                        The handle to the image to be converted.
 * \param[in]  pixel_format                        The target pixel format for the conversion.
 * \param[out] output_handle                       Handle to the newly created converted image.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                    Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED    The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE             One or more handles (\p input_handle, \p converter_handle) were not created.
 * \return #PEAK_ICV_STATUS_NOT_SUPPORTED              Conversion to the specified \p pixel_format is not supported.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR             An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ImageConverter_Convert(peak_icv_image_converter_handle converter_handle,
    peak_icv_image_handle input_handle, enum peak_common_pixel_format pixel_format, peak_icv_image_handle* output_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_image_converter
 * \brief Frees unused internal buffers.
 *
 * A image converter uses pre-allocated internal buffers to accelerate conversions.
 * When the image size or pixel format changes, new buffers are allocated, which may cause
 * the internal buffer pool to grow over time. This function releases unused buffers
 * and compacts the buffer pool to reduce memory usage.
 *
 * \note Avoid calling this function too frequently (e.g., after every resize or format change),
 * as it introduces overhead and may degrade performance by forcing buffer reallocation.
 * A good practice is to call it after processing batches of images or during natural
 * breaks in processing workflows.
 *
 * \param[in] converter_handle  Handle to the image converter object
 *                              Must be a valid converter instance.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p converter_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_ImageConverter_ReleaseBuffers(peak_icv_image_converter_handle converter_handle);

#ifdef __cplusplus
} // extern "C"

#endif // __cplusplus
