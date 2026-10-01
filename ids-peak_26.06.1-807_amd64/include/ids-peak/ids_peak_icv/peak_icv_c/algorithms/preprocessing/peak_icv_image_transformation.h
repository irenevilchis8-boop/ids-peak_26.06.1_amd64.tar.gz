/*!
 * \file    peak_icv_image_transformation.h
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
 * \defgroup ids_peak_icv_c_preprocessing_transformation Image Transformation
 * \ingroup ids_peak_icv_c_preprocessing
 *
 * \brief Image transformation provides mirror and rotation functionality.
 *
 * \since ids_peak_icv 1.0
 */

/*!
 * \ingroup ids_peak_icv_c_preprocessing_transformation
 *
 * \brief Angle parameter for the rotation algorithm.
 *
 * The enum holding the possible rotation angles and the rotation direction.
 *
 * \since ids_peak_icv 1.0
 */
typedef enum peak_icv_preprocessing_transformation_rotation_angle
{
    /*! \brief Describes no rotation. */
    PEAK_ICV_PREPROCESSING_TRANSFORMATION_ROTATION_NONE = 0,

    /*! \brief Describes a 90-degree counterclockwise rotation. */
    PEAK_ICV_PREPROCESSING_TRANSFORMATION_ROTATION_90_DEGREE_COUNTERCLOCKWISE = 90,

    /*! \brief Describes a 180-degree rotation. */
    PEAK_ICV_PREPROCESSING_TRANSFORMATION_ROTATION_180_DEGREE = 180,

    /*! \brief Describes a 90-degree clockwise rotation. */
    PEAK_ICV_PREPROCESSING_TRANSFORMATION_ROTATION_90_DEGREE_CLOCKWISE = 270
} peak_icv_preprocessing_transformation_rotation_angle;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_transformation
 *
 * \brief Image transformation parameters define, how an image is transformed.
 *
 * \since ids_peak_icv 1.0
 */
struct peak_icv_preprocessing_transformation_parameters
{
    bool mirror_left_right;
    bool mirror_up_down;
    peak_icv_preprocessing_transformation_rotation_angle rotation_angle;
};

/*!
 * \ingroup ids_peak_icv_c_preprocessing_transformation
 *
 * \brief Returns the expected output pixel format after mirror and rotation transformation for the given the input format.
 *
 * \note A different output pixel format can be expected when using bayer formats.
 *
 * \param[in]  input_pixel_format   Input image pixel format.
 * \param[in]  parameters           Transformation parameters.
 * \param[out] output_pixel_format  Output image pixel format.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p output_pixel_format is an invalid pointer.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Transformation_GetOutputPixelFormat(peak_common_pixel_format input_pixel_format,
    peak_icv_preprocessing_transformation_parameters parameters, peak_common_pixel_format* output_pixel_format);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_transformation
 *
 * \brief Mirrors and rotates the given image according to the given transformation parameters.
 *
 * \param[in]  input_image_handle   Handle to the input image that is to be mirrored.
 * \param[in]  parameters           Transformation parameters.
 * \param[out] output_image_handle  Handle to the output image that stores the mirrored image. This handle must be created with the same size and pixel format first.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p input_image_handle or \p output_image_handle must be created first.
 * \return #PEAK_ICV_STATUS_MISMATCH                 The given images have different pixel formats or sizes.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_Transformation_Process(peak_icv_image_handle input_image_handle,
    peak_icv_preprocessing_transformation_parameters parameters, peak_icv_image_handle output_image_handle);

#ifdef __cplusplus
} // extern "C"

#endif // __cplusplus
