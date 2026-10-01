/*!
 * \file    peak_common_size.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-12
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

#include <cassert>
#include <cstdint>
#include <sstream>

namespace peak
{
namespace common
{

namespace detail
{
/*!
 * \ingroup ids_peak_common_types_geometry ids_peak_common_detail
 * \brief Represents a two-dimensional size with non-negative width and height.
 *
 * A `SizeT` stores the width and height of an object or area. Both dimensions must be greater than or equal to zero.
 *
 * \tparam T Arithmetic type used for width and height.
 *
 * \since ids_peak_common 1.0
 */
template <typename T>
class SizeT
{

public:
    static_assert(std::is_arithmetic<T>::value, "Template argument of Size must be arithmetic.");

    /*!
     * \brief Default constructor for SizeT.
     *
     * Initializes a size with default values for width and height.
     *
     * \since ids_peak_common 1.0
     */
    constexpr SizeT() = default;

    /*!
     * \brief Constructs a SizeT object from integral width and height.
     *
     * Initializes the size with the specified width and height values.
     *
     * \param width  Width of the size.
     * \param height Height of the size.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H = T
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if_t<std::is_integral<H>::value, int> = 0
        /// @endcond
        >
    constexpr SizeT(T width, T height)
        : m_width{ width }
        , m_height{ height }
    {
        static_assert(std::is_unsigned<T>::value, "Parameter width and/or height has to be greater or equal to zero.");
    }

    /*!
     * \brief Constructs a SizeT object from floating-point width and height.
     *
     * Initializes the size with the specified width and height values.
     * Throws an exception if either value is negative.
     *
     * \param width  Width of the size.
     * \param height Height of the size.
     *
     * \throws InvalidParameterException     If width or height is less than zero.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H = T
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if_t<std::is_floating_point<H>::value, int> = 0
        /// @endcond
        >
    constexpr SizeT(T width, T height)
        : m_width{ width }
        , m_height{ height }
    {
        if (width < 0)
        {
            throw peak::common::InvalidParameterException("Parameter width has to be greater or equal to zero.");
        }
        if (height < 0)
        {
            throw peak::common::InvalidParameterException("Parameter height has to be greater or equal to zero.");
        }
    }

    /*!
     * \brief Returns the width.
     *
     * \return The width value.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr T GetWidth() const
    {
        return m_width;
    }

    /*!
     * \brief Returns the height.
     *
     * \return The height value.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr T GetHeight() const
    {
        return m_height;
    }

    /*!
     * \brief Returns a transposed size with width and height swapped.
     *
     * \return A new SizeT object with width and height swapped.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr SizeT<T> Transposed() const
    {
        return { m_height, m_width };
    }

    /*!
     * \brief Equality operator for integral types.
     *
     * Compares width and height for exact equality.
     *
     * \param rhs The SizeT object to compare against.
     * \return true if both width and height are equal; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if_t<std::is_integral<H>::value, int> = 0
        /// @endcond
        >
    constexpr bool operator==(const SizeT<H>& rhs) const
    {
        return GetHeight() == rhs.GetHeight() && GetWidth() == rhs.GetWidth();
    }

    /*!
     * \brief Equality operator for floating point types.
     *
     * Compares width and height using a tolerance based on ULP (Units in Last Place).
     *
     * \param rhs The SizeT object to compare against.
     * \return true if both width and height are approximately equal within tolerance; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if_t<std::is_floating_point<H>::value, int> = 0
        /// @endcond
        >
    constexpr bool operator==(const SizeT<H>& rhs) const
    {
        // Unit in the last place
        constexpr uint32_t ulp = 4;

        using common_type = std::common_type_t<H, T>;

        return detail::AreAlmostEqual<common_type>(static_cast<common_type>(GetWidth()), static_cast<common_type>(rhs.GetWidth()), ulp)
            && detail::AreAlmostEqual<common_type>(static_cast<common_type>(GetHeight()), static_cast<common_type>(rhs.GetHeight()), ulp);
    }

    /*!
     * \brief Inequality operator.
     *
     * Returns true if the sizes are not equal.
     *
     * \param rhs The SizeT object to compare against.
     * \return true if sizes are different; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H>
    constexpr bool operator!=(const SizeT<H>& rhs) const
    {
        return !(*this == rhs);
    }

    /*!
     * \brief Stream operator to output SizeT in a readable format.
     *
     * Outputs width and height in the form: { width: ..., height: ... }
     *
     * \param os Output stream
     * \param size SizeT instance to output
     * \return Reference to the output stream
     *
     * \since ids_peak_common 1.0
     */
    friend std::ostream& operator<<(std::ostream& os, SizeT size)
    {
        return os << "{ width: " << size.GetWidth() << ", height: " << size.GetHeight() << " }";
    }

    /*!
     * \brief Convert the SizeT instance to a string representation.
     *
     * Outputs width and height in the form: { width: ..., height: ... }
     *
     * \return String representation of the size
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
    T m_width{};
    T m_height{};

    friend detail::BackendAccessor<SizeT<T>>;

    template <typename U = T, typename std::enable_if<has_c_type_of<SizeT<U>>::value, bool>::type = false>
    constexpr explicit operator detail::c_type_of_t<SizeT<T>>() const // NOLINT
    {
        return { this->GetWidth(), this->GetHeight() };
    }
};

} // namespace detail

/*!
 * \ingroup ids_peak_common_types_geometry
 * \brief Size with unsigned 32-bit integer dimensions.
 *
 * Provides a stable and public alias for a size type where width and height are represented
 * as `uint32_t`.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::SizeT<uint32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using Size = detail::SizeT<uint32_t>;

/*!
 * \ingroup ids_peak_common_types_geometry
 * \brief Size with floating-point dimensions.
 *
 * Provides a stable and public alias for a size type where width and height are represented
 * as `float`, suitable for precise or fractional dimensions.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::SizeT<float>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using SizeF = detail::SizeT<float>;

} // namespace common 
} // namespace peak
