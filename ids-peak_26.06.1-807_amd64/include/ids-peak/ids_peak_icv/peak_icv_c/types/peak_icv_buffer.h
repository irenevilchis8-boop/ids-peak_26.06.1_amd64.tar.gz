/*!
 * \file    peak_icv_buffer.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-03-04
 * \since   1.3
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>

#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>

extern "C" {
#else
#    include <stdbool.h>
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \ingroup ids_peak_icv_c_buffer
 *
 * \brief Cuts black columns from the input \p data and writes the resulting pixel data into an \p output_image_handle.
 *
 * The function copies the parts of the buffer that contain actual image data to the target image. Non-image regions at the buffer are
 * ignored.
 *
 * \param data                  Pointer to the buffer data to cut the image data from.
 * \param line_start_offset     The offset in bytes from the beginning of a buffer line to the start of the image data.
 * \param bytes_per_line        Number of bytes per line including invalid image data.
 * \param valid_bytes_per_line  The size, in bytes, of the actual image data per line.
 * \param number_of_lines       The resulting image height.
 * \param output_image_handle   Image filled with pixel date from buffer. The output image has to be allocated with the correct size and pixel format (can be queried from an image view).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE          The \p output_image_handle must be created first.
 * \return #PEAK_ICV_STATUS_NOT_POSSIBLE            The \p line_start_offset and \p valid_bytes_per_line exceeds the \p bytes_per_line.
 * \return #PEAK_ICV_STATUS_MISMATCH                The \p number_of_lines exceeds the output image height or valid_bytes_per_line exceeds the output image width.
 *
 * \since ids_peak_icv 1.3
 */
PEAK_ICV_API_STATUS peak_icv_Buffer_CutBytes(const uint8_t* data, size_t line_start_offset, size_t bytes_per_line,
    size_t valid_bytes_per_line, size_t number_of_lines, peak_icv_image_handle output_image_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
