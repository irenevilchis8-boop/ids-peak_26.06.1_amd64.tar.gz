/*!
 * \file    peak_icv_simple_types.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \ingroup ids_peak_icv_c_status
 * \brief peak_icv Status codes
 *
 * The majority of the peak_icv functions return a status code.
 */
/*!
 * \brief Status codes used throughout the library.
 */
typedef enum peak_icv_status
{
    /*! \brief Success */
    PEAK_ICV_STATUS_SUCCESS = 0,

    /*! \brief Library not initialized */
    PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED = 1,

    /*! \brief Dynamic dependency missing */
    PEAK_ICV_STATUS_DYNAMIC_DEPENDENCY_MISSING = 2,

    /*! \brief Input parameters are valid individually but invalid in combination */
    PEAK_ICV_STATUS_MISMATCH = 3,

    /*! \brief Not supported */
    PEAK_ICV_STATUS_NOT_SUPPORTED = 4,

    /*! \brief Operation is not possible due to API constraints */
    PEAK_ICV_STATUS_NOT_POSSIBLE = 5,

    /*! \brief Null pointer received where a valid one was expected */
    PEAK_ICV_STATUS_NULL_POINTER = 6,

    /*! \brief Invalid handle */
    PEAK_ICV_STATUS_INVALID_HANDLE = 7,

    /*! \brief Value is out of valid range */
    PEAK_ICV_STATUS_OUT_OF_RANGE = 8,

    /*! \brief Mathematical computation error (e.g., division by zero) */
    PEAK_ICV_STATUS_MATH_ERROR = 9,

    /*! \brief Target not found */
    PEAK_ICV_STATUS_TARGET_NOT_FOUND = 10,

    /*! \brief Corrupted file or data */
    PEAK_ICV_STATUS_CORRUPTED = 11,

    /*! \brief I/O error during file access */
    PEAK_ICV_STATUS_IO_ERROR = 12,

    /*! \brief Internal error within the library */
    PEAK_ICV_STATUS_INTERNAL_ERROR = 13,

    /*! \brief Provided buffer size is invalid */
    PEAK_ICV_STATUS_INVALID_BUFFER_SIZE = 14

} peak_icv_status;

/*!
 * \ingroup ids_peak_icv_c_types
 * \brief Homogeneous transformation matrix.
 *
 * The matrix is defined as a 4x4 float array, where the matrix follows the form: \n
 *       r_11 r_12 r_13 t_x \n
 *       r_21 r_22 r_23 t_y \n
 *       r_31 r_32 r_33 t_z \n
 *       0    0    0    1 \n
 * where \p r_ij represents rotation, and \p t_x, \p t_y, and \p t_z represent translation.
 */
typedef float peak_icv_transformation_matrix_3d[4][4];

/*!
 * \ingroup ids_peak_icv_c_types
 * \brief The peak_icv_drawing_options specify parameters for visualization.
 */
typedef struct peak_icv_drawing_options
{
    /*! \brief Color to draw */
    uint64_t color;

    /*! \brief Opacity to draw with */
    uint32_t opacity;

    /*! \brief Reserved */
    size_t reserved;
} peak_icv_drawing_options;

/*!
 * \ingroup ids_peak_icv_c_types
 * \brief The peak_icv_point_xyz describes a floating point coordinate in a three dimensional space. This point can also have negative coordinates.
 */
typedef struct peak_icv_point_xyz
{
    /*! \brief X */
    float x;

    /*! \brief Y */
    float y;

    /*! \brief Z */
    float z;

    /*! \brief reserved data. No use */
    float reserved[1];
} peak_icv_point_xyz;

/*!
 * \ingroup ids_peak_icv_c_types
 * \brief The peak_icv_point_xyz_intensity describes a floating point coordinate in a three dimensional space with an additional intensity. This point can also have negative coordinates.
 */
typedef struct peak_icv_point_xyzi
{
    /*! \brief X */
    float x;

    /*! \brief Y */
    float y;

    /*! \brief Z */
    float z;

    /*! \brief Intensity */
    uint16_t intensity;
} peak_icv_point_xyzi;

/*!
 * \ingroup ids_peak_icv_c_types
 * \brief The peak_icv_point_xyzrgb describes a floating point coordinate in a three dimensional space with an additional color information R, G and B. This point can also have negative coordinates.
 */
typedef struct peak_icv_point_xyzrgb
{
    /*! \brief X */
    float x;

    /*! \brief Y */
    float y;

    /*! \brief Z */
    float z;

    /*! \brief reserved data. No use */
    float reserved[1];

    /*! \brief Red */
    uint16_t red;

    /*! \brief Green */
    uint16_t green;

    /*! \brief Blue */
    uint16_t blue;
} peak_icv_point_xyzrgb;

/*!
 * \brief Reserved for future use
 */
typedef struct peak_icv_point_cloud_save_options
{
    /*! \brief Reserved */
    uint8_t reserved[64];
} peak_icv_point_cloud_save_options;

/*!
 * \ingroup ids_peak_icv_c_types
 * \brief The point type is used to define the point structure of a point cloud.
 */
typedef enum peak_icv_point_type
{
    /*! XYZ coordinates only. */
    PEAK_ICV_POINT_TYPE_XYZ = 0,

    /*! XYZ coordinates with 8-bit intensity. */
    PEAK_ICV_POINT_TYPE_XYZ_I8 = 1,

    /*! XYZ coordinates with 10-bit intensity. */
    PEAK_ICV_POINT_TYPE_XYZ_I10 = 2,

    /*! XYZ coordinates with 12-bit intensity. */
    PEAK_ICV_POINT_TYPE_XYZ_I12 = 3,

    /*! XY float coordinates. */
    PEAK_ICV_POINT_TYPE_XY = 4,

    /*! XYZ coordinates with 8-bit r g b. */
    PEAK_ICV_POINT_TYPE_XYZ_RGB8 = 5,
} peak_icv_point_type;

/*!
 * \ingroup ids_peak_icv_c_transformation
 *
 * \brief Enumeration of interpolation methods used in image transformations.
 *
 * These methods determine how pixel values are calculated
 * when performing geometric transformations on images,
 * such as undistortion and scaling.
 *
 * \since ids_peak_icv 1.0
 */
typedef enum peak_icv_interpolation
{
    /*!
     * Calculates the output pixel value
     * as a weighted average of the four closest input pixels.
     * Suitable for smoother results.
     */
    PEAK_ICV_INTERPOLATION_BILINEAR = 0,

    /*!
     * Uses the nearest input pixel value directly.
     * Faster but may introduce aliasing or blocky artifacts.
     */
    PEAK_ICV_INTERPOLATION_NEAREST_NEIGHBOR = 1
} peak_icv_interpolation;

/*!
 * \ingroup ids_peak_icv_c_types
 * \brief File format used in serialization.
 *
 * The enum holding the possible serialization file types.
 */
typedef enum peak_icv_serialization_type
{
    /*! \brief Serialization file format json */
    PEAK_ICV_SERIALIZATION_TYPE_JSON,
} peak_icv_serialization_type;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
