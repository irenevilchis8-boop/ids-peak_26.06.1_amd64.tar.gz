/*!
 * \file    peak_icv_interpolation.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-10-22
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_transformations
 *
 * \brief Enumeration of interpolation methods used in image transformations.
 *
 * These methods determine how pixel values are calculated
 * when performing geometric transformations on images,
 * such as undistortion and scaling.
 *
 * \since ids_peak_icv 1.1
 */
enum class Interpolation
{
    /*!
     * Calculates the output pixel value
     * as a weighted average of the four closest input pixels.
     * Suitable for smoother results.
     */
    Bilinear = 0,

    /*!
     * Uses the nearest input pixel value directly.
     * Faster but may introduce aliasing or blocky artifacts.
     */
    NearestNeighbor = 1
};

} /* namespace icv */
} /* namespace peak */
