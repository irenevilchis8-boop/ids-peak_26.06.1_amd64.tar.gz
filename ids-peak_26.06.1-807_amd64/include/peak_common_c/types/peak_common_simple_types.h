/*!
 * \file    peak_common_simple_types.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-28
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
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
 * \ingroup ids_peak_common_c_types
 * \brief Represents an integer interval with inclusive minimum and maximum bounds.
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_interval
{
    /*! \brief Lower bound of the interval. */
    int32_t minimum;

    /*! \brief Upper bound of the interval. */
    int32_t maximum;
} peak_common_interval;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents an unsigned integer interval with inclusive minimum and maximum bounds.
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_interval_u
{
    /*! \brief Lower bound of the interval. */
    uint32_t minimum;

    /*! \brief Upper bound of the interval. */
    uint32_t maximum;
} peak_common_interval_u;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a floating-point interval with inclusive minimum and maximum bounds.
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_interval_f
{
    /*! \brief Lower bound of the interval. */
    float minimum;

    /*! \brief Upper bound of the interval. */
    float maximum;
} peak_common_interval_f;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents an integer range with inclusive minimum and maximum bounds and an increment step.
 * \since ids_peak_common 1.3
 */
typedef struct peak_common_range
{
    /*! \brief Lower bound of the range. */
    int32_t minimum;

    /*! \brief Upper bound of the range. */
    int32_t maximum;

    /*! \brief Step size or increment of the range. */
    int32_t increment;
} peak_common_range;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents an unsigned integer range with inclusive minimum and maximum bounds and an increment step.
 * \since ids_peak_common 1.3
 */
typedef struct peak_common_range_u
{
    /*! \brief Lower bound of the range. */
    uint32_t minimum;

    /*! \brief Upper bound of the range. */
    uint32_t maximum;

    /*! \brief Step size or increment of the range. */
    uint32_t increment;
} peak_common_range_u;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a floating-point range with inclusive minimum and maximum bounds and an increment step.
 * \since ids_peak_common 1.3
 */
typedef struct peak_common_range_f
{
    /*! \brief Lower bound of the range. */
    float minimum;

    /*! \brief Upper bound of the range. */
    float maximum;

    /*! \brief Step size or increment of the range. */
    float increment;
} peak_common_range_f;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a 2D size with unsigned integer dimensions.
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_size
{
    /*! \brief Width component of the size. */
    uint32_t width;

    /*! \brief Height component of the size. */
    uint32_t height;
} peak_common_size;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a 2D size with floating-point dimensions.
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_size_f
{
    /*! \brief Width component of the size. */
    float width;

    /*! \brief Height component of the size. */
    float height;
} peak_common_size_f;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a 2D point with signed integer coordinates.
 *
 * This point can be located in any quadrant, including negative X and Y coordinates.
 *
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_point
{
    /*! \brief X-coordinate of the point. */
    int32_t x;

    /*! \brief Y-coordinate of the point. */
    int32_t y;
} peak_common_point;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a 2D point with unsigned integer coordinates.
 *
 * This point is constrained to the positive quadrant.
 *
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_point_u
{
    /*! \brief X-coordinate of the point. */
    uint32_t x;

    /*! \brief Y-coordinate of the point. */
    uint32_t y;
} peak_common_point_u;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a 2D point with floating-point coordinates.
 *
 * This point can represent any position in the 2D plane, including negative values.
 *
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_point_f
{
    /*! \brief X-coordinate of the point. */
    float x;

    /*! \brief Y-coordinate of the point. */
    float y;
} peak_common_point_f;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a 2D vector using floating-point precision.
 * \since ids_peak_common 1.0
 */
typedef peak_common_point_f peak_common_vector;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a rectangle defined by a position and unsigned integer size.
 *
 * The position (x, y) defines the top-left corner of the rectangle.
 *
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_rectangle
{
    /*! \brief X-coordinate of the rectangle's origin. */
    int32_t x;

    /*! \brief Y-coordinate of the rectangle's origin. */
    int32_t y;

    /*! \brief Width of the rectangle. */
    uint32_t width;

    /*! \brief Height of the rectangle. */
    uint32_t height;
} peak_common_rectangle;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a rectangle defined by an unsigned integer position and unsigned integer size.
 *
 * The position (x, y) defines the top-left corner of the rectangle.
 *
 * \since ids_peak_common 1.1
 */
typedef struct peak_common_rectangle_u
{
    /*! \brief X-coordinate of the rectangle's origin. */
    uint32_t x;

    /*! \brief Y-coordinate of the rectangle's origin. */
    uint32_t y;

    /*! \brief Width of the rectangle. */
    uint32_t width;

    /*! \brief Height of the rectangle. */
    uint32_t height;
} peak_common_rectangle_u;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a rectangle defined by a floating-point position and size.
 *
 * The position (x, y) defines the top-left corner of the rectangle with sub-pixel precision.
 *
 * \since ids_peak_common 1.0
 */
typedef struct peak_common_rectangle_f
{
    /*! \brief X-coordinate of the rectangle's origin. */
    float x;

    /*! \brief Y-coordinate of the rectangle's origin. */
    float y;

    /*! \brief Width of the rectangle. */
    float width;

    /*! \brief Height of the rectangle. */
    float height;
} peak_common_rectangle_f;

/*!
 * \ingroup ids_peak_common_c_types
 * \brief Represents a version number.
 *
 * This structure encodes a version in the form:
 * **major.minor.subminor.patch**
 */
typedef struct peak_common_version
{
    uint32_t major;    /*!< Major version component. */
    uint32_t minor;    /*!< Minor version component. */
    uint32_t subminor; /*!< Subminor version component. */
    uint32_t patch;    /*!< Patch or build number. */
} peak_common_version;


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
