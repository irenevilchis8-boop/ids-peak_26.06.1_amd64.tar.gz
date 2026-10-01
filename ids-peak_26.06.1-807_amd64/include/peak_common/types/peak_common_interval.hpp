/*!
 * \file    peak_common_interval.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-14
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_backend_accessor.hpp>
#include <peak_common/detail/peak_common_math.hpp>
#include <peak_common/detail/peak_common_type_traits.hpp>
#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common_c/types/peak_common_simple_types.h>

#include <type_traits>
#include <sstream>

namespace peak
{
namespace common
{

namespace detail
{

/*!
 * \ingroup ids_peak_common_types ids_peak_common_detail
 * \brief Represents a continuous numeric interval with inclusive lower and upper bounds.
 *
 * The interval is defined by two values: a minimum and a maximum. These values
 * must satisfy the condition: `minimum <= maximum`.
 *
 * \tparam T Must be an arithmetic type (integer or floating point).
 *
 * \since ids_peak_common 1.0
 */
template <typename T>
class IntervalT
{

public:
    static_assert(std::is_arithmetic<T>::value, "Template argument of Interval must be arithmetic.");

    using type = T;

    /*!
     * \brief Constructs an interval with the given lower and upper bounds.
     *
     * \param minimum The lower boundary (inclusive).
     * \param maximum The upper boundary (inclusive).
     *
     * \throws InvalidParameterException     If the minimum is greater than the maximum.
     *
     * \since ids_peak_common 1.0
     */
    constexpr IntervalT(T minimum, T maximum)
        : m_minimum(minimum)
        , m_maximum(maximum)
    {
        if (minimum > maximum)
        {
            throw peak::common::InvalidParameterException("The maximum value has to be greater than or equal to the minimum value!");
        }
    }

    /*!
     * \brief Returns the lower boundary of the interval.
     * \return The minimum value of the interval (inclusive).
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr T GetMinimum() const
    {
        return m_minimum;
    }

    /*!
     * \brief Returns the upper boundary of the interval.
     * \return The maximum value of the interval (inclusive).
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr T GetMaximum() const
    {
        return m_maximum;
    }

    /*!
     * \brief Compares two intervals for equality (integral types).
     *
     * Checks whether the minimum and maximum values of both intervals are exactly the same.
     *
     * \param rhs The interval to compare against.
     * \return `true` if both intervals have the same minimum and maximum values; otherwise, `false`.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if_t<std::is_integral<H>::value, int> = 0
        /// @endcond
        >
    constexpr bool operator==(const IntervalT<H>& rhs) const
    {
        return GetMinimum() == rhs.GetMinimum() && GetMaximum() == rhs.GetMaximum();
    }

    /*!
     * \brief Compares two intervals for approximate equality (floating-point types).
     *
     * Determines whether two intervals are approximately equal by comparing their minimum and maximum
     * values using a tolerance defined in ULPs (Units in the Last Place).
     *
     * \param rhs The interval to compare against.
     * \return `true` if both intervals have approximately equal minimum and maximum values; otherwise, `false`.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if_t<std::is_floating_point<H>::value, int> = 0
        /// @endcond
        >
    constexpr bool operator==(const IntervalT<H>& rhs) const
    {
        // Unit in the last place
        constexpr uint32_t ulp = 4;

        using common_type = std::common_type_t<H, T>;

        return detail::AreAlmostEqual<common_type>(static_cast<common_type>(GetMinimum()), static_cast<common_type>(rhs.GetMinimum()), ulp)
            && detail::AreAlmostEqual<common_type>(static_cast<common_type>(GetMaximum()), static_cast<common_type>(rhs.GetMaximum()), ulp);
    }

    /*!
     * \brief Inequality comparison operator.
     * \param rhs The interval to compare with.
     * \return True if the intervals differ in either minimum or maximum value.
     *
     * \since ids_peak_common 1.0
     */
    constexpr bool operator!=(const IntervalT& rhs) const
    {
        return !(rhs == *this);
    }

    /*!
     * \brief Outputs the interval as a human-readable string to a stream.
     * \param os The output stream.
     * \param interval The interval to print.
     * \return Reference to the stream.
     *
     * \since ids_peak_common 1.0
     */
    friend std::ostream& operator<<(std::ostream& os, IntervalT interval)
    {
        return os << "{ minimum: " << interval.m_minimum << ", maximum: " << interval.m_maximum << " }";
    }

    /*!
     * \brief Returns a string representation of the interval.
     * \return A formatted string showing the minimum and maximum values.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD std::string ToString() const
    {
        std::ostringstream ss;
        ss << *this;
        return ss.str();
    }

private:
    T m_minimum;
    T m_maximum;

    friend detail::BackendAccessor<IntervalT<T>>;

    template <typename U = T, typename std::enable_if<has_c_type_of<IntervalT<U>>::value, bool>::type = false>
    explicit IntervalT(c_type_of_t<IntervalT<U>> interval)
        : IntervalT<U>(interval.minimum, interval.maximum)
    {}

    template <typename U = T, typename std::enable_if<has_c_type_of<IntervalT<U>>::value, bool>::type = false>
    constexpr explicit operator detail::c_type_of_t<IntervalT<U>>() const
    {
        return { this->GetMinimum(), this->GetMaximum() };
    }
};

} // namespace detail

/*!
 * \ingroup ids_peak_common_types
 * \brief Interval with unsigned 32-bit integer boundaries.
 *
 * Provides a stable and public alias for a numerical range where both the minimum and maximum values
 * are represented as `uint32_t`, suitable for positive-only ranges.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::IntervalT<uint32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using IntervalU = detail::IntervalT<uint32_t>;

/*!
 * \ingroup ids_peak_common_types
 * \brief Interval with signed 32-bit integer boundaries.
 *
 * Provides a stable and public alias for a numerical range using `int32_t` as the underlying type,
 * suitable for representing ranges that include both negative and positive values.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::IntervalT<int32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using Interval = detail::IntervalT<int32_t>;

/*!
 * \ingroup ids_peak_common_types
 * \brief Interval with floating-point boundaries.
 *
 * Provides a stable and public alias for a numerical range using `float`, supporting decimal precision
 * and continuous ranges.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::IntervalT<float>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using IntervalF = detail::IntervalT<float>;

} // namespace common 
} // namespace peak
