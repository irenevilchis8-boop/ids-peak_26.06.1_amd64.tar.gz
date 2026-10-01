/*!
 * \file    peak_common_math.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <type_traits>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <limits>

namespace peak
{
namespace common
{
namespace detail
{

/*!
 * \ingroup ids_peak_common_detail
 * \brief Compares two floating-point values for approximate equality using a ULP-based tolerance.
 *
 * Determines whether two floating-point numbers are approximately equal by considering
 * the difference between them relative to their magnitude and the machine epsilon.
 * The comparison uses a configurable tolerance based on *Units in the Last Place (ULP)*.
 *
 * \param lhs The first floating-point value to compare.
 * \param rhs The second floating-point value to compare.
 * \param ulp The tolerance multiplier in ULP units; larger values allow for greater difference.
 * \return True if the two values are approximately equal within the specified ULP tolerance; false otherwise.
 *
 * This function is useful for mitigating issues with precision loss in floating-point arithmetic,
 * especially when exact equality comparisons are not reliable.
 *
 * \since ids_peak_common 1.0
 */
template <typename H
    /// @cond HIDE_FROM_DOXYGEN
    ,
    typename std::enable_if_t<std::is_floating_point<H>::value, int> = 0
    /// @endcond
    >
constexpr bool AreAlmostEqual(H lhs, H rhs, uint32_t ulp)
{
    return std::abs(lhs - rhs) <= std::numeric_limits<H>::epsilon() * (std::max)(std::abs(lhs), std::abs(rhs)) * static_cast<H>(ulp);
}

} // namespace detail
} // namespace common 
} // namespace peak
