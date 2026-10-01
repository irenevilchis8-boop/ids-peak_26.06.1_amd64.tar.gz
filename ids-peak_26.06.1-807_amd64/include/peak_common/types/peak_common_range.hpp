/*!
 * \file    peak_common_range.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-14
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common/types/peak_common_interval.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

#include <type_traits>

namespace peak
{
namespace common
{

namespace detail
{

/*!
 * \ingroup ids_peak_common_types ids_peak_common_detail
 * \brief Represents a numeric range with defined boundaries and a fixed increment.
 *
 * A RangeT models a continuous sequence of values starting from a minimum value,
 * ending at a maximum value, and progressing in steps defined by an increment.
 * It supports arithmetic types such as integers and floating-point numbers.
 *
 * This class ensures that the increment does not exceed the total span between
 * the minimum and maximum bounds. The range is inclusive of its boundary values.
 *
 * \tparam T The numeric type used for the range values. Must be an arithmetic type (e.g., int, float).
 *
 * \since ids_peak_common 1.0
 */
template <typename T>
class RangeT : public detail::IntervalT<T>
{

public:
    static_assert(std::is_arithmetic<T>::value, "Template argument of Interval must be arithmetic.");

    using type = T;

    /*!
     * \brief Constructs a range with specified minimum, maximum, and increment values.
     *
     * \param minimum The inclusive starting (lower) boundary of the range.
     * \param maximum The inclusive ending (upper) boundary of the range.
     * \param increment The step size or increment between values within the range.
     *
     * \throws InvalidParameterException If \p minimum is greater than \p maximum,
     *         or if \p increment exceeds the total range span.
     *
     * \since ids_peak_common 1.0
     */
    constexpr RangeT(T minimum, T maximum, T increment)
        : detail::IntervalT<T>(minimum, maximum)
        , m_increment{ increment }
    {
        if (increment > maximum - minimum)
        {
            throw peak::common::InvalidParameterException("The given increment is larger than the total range!");
        }
    }

    /*!
     * \brief Retrieves the increment value associated with this range.
     *
     * \return The increment step.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr T GetIncrement() const
    {
        return m_increment;
    }

    /*!
     * \brief Compares this range with another for equality.
     *
     * Two ranges are equal if their boundaries and increments are the same.
     *
     * \param rhs The other range to compare with.
     * \return True if the ranges are equal; otherwise, false.
     *
     * \since ids_peak_common 1.0
     */
    constexpr bool operator==(const RangeT& rhs) const
    {
        return detail::IntervalT<T>::operator==(rhs) && m_increment == rhs.m_increment;
    }

    /*!
     * \brief Compares this range with another for inequality.
     *
     * \param rhs The other range to compare with.
     * \return True if the ranges are not equal; otherwise, false.
     *
     * \since ids_peak_common 1.0
     */
    constexpr bool operator!=(const RangeT& rhs) const
    {
        return !(rhs == *this);
    }

    /*!
     * \brief Outputs the range as a human-readable string to a stream.
     * \param os The output stream.
     * \param range The range to print.
     * \return Reference to the stream.
     *
     * \since ids_peak_common 1.3
     */
    friend std::ostream& operator<<(std::ostream& os, RangeT range)
    {
        return os << "{ minimum: " << range.GetMinimum() << ", maximum: " << range.GetMaximum() << ", increment: " << range.GetIncrement()
                  << " }";
    }

    /*!
     * \brief Returns a string representation of the range.
     * \return A formatted string showing the minimum, maximum and increment values.
     *
     * \since ids_peak_common 1.3
     */
    PEAK_COMMON_NO_DISCARD std::string ToString() const
    {
        std::ostringstream ss;
        ss << *this;
        return ss.str();
    }

private:
    T m_increment;

    friend detail::BackendAccessor<RangeT<T>>;

    template <typename U = T, typename std::enable_if<has_c_type_of<RangeT<U>>::value, bool>::type = false>
    explicit RangeT(c_type_of_t<RangeT<U>> range)
        : RangeT<U>(range.minimum, range.maximum, range.increment)
    {}

    template <typename U = T, typename std::enable_if<has_c_type_of<RangeT<U>>::value, bool>::type = false>
    constexpr explicit operator detail::c_type_of_t<RangeT<U>>() const
    {
        return { this->GetMinimum(), this->GetMaximum(), this->GetIncrement() };
    }
};

} // namespace detail

/*!
 * \ingroup ids_peak_common_types
 * \brief Alias for a range of 32-bit unsigned integers.
 *
 * Represents a numerical range where both the minimum and maximum values are of type `uint32_t`.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::RangeT<uint32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using RangeU = detail::RangeT<uint32_t>;

/*!
 * \ingroup ids_peak_common_types
 * \brief Alias for a range of 32-bit signed integers.
 *
 * Represents a numerical range with `int32_t` as the underlying type, allowing for negative and positive values.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::RangeT<int32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using Range = detail::RangeT<int32_t>;

/*!
 * \ingroup ids_peak_common_types
 * \brief Alias for a range of 32-bit floating-point numbers.
 *
 * Represents a numerical range using `float`, supporting fractional and continuous ranges.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::RangeT<float>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using RangeF = detail::RangeT<float>;

/*!
 * \ingroup ids_peak_common_types
 * \brief Alias for a range of 8-bit unsigned integers.
 *
 * Represents a numerical range where both minimum and maximum values are `uint8_t`.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::RangeT<uint8_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using RangeU8 = detail::RangeT<uint8_t>;


} // namespace common 
} // namespace peak
