/*!
 * \file    peak_common_point.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-28
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_backend_accessor.hpp>
#include <peak_common/detail/peak_common_math.hpp>
#include <peak_common/detail/peak_common_type_traits.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

#include <array>
#include <sstream>

namespace peak
{
namespace common
{

namespace detail
{
/*!
 * \ingroup ids_peak_common_types_geometry ids_peak_common_detail
 * \brief A point in space with configurable dimensionality and coordinate type.
 *
 * Represents a mathematical point consisting of at least two coordinates (e.g., x and y).
 * The number of dimensions and the data type of the coordinates are defined by the template parameters.
 *
 * \tparam T The coordinate data type. Must be an arithmetic type.
 * \tparam dimension The number of dimensions. Must be 2 or greater.
 *
 * \since ids_peak_common 1.0
 */
template <typename T, size_t dimension>
class PointXd
{
public:
    static_assert(dimension >= 2, "A Point must consist of at least two coordinates (x,y)!");
    static_assert(std::is_arithmetic<T>::value, "A point must be created from an arithmetic type!");

    /*!
     * \brief Default constructor for PointXd.
     *
     * Initializes the point with default-initialized coordinates.
     *
     * \since ids_peak_common 1.0
     */
    constexpr PointXd() = default;

    /*!
     * \brief Constructs a PointXd from an array of coordinates.
     *
     * \param coordinates An array containing the coordinates of the point.
     *
     * \since ids_peak_common 1.0
     */
    constexpr explicit PointXd(std::array<T, dimension> coordinates)
        : m_coordinates{ coordinates }
    {}

    /*!
     * \brief Returns the x-coordinate (first component).
     *
     * \return The value of the first coordinate.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr T GetX() const
    {
        return m_coordinates.at(0);
    }

    /*!
     * \brief Returns the y-coordinate (second component).
     *
     * \return The value of the second coordinate.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr T GetY() const
    {
        return m_coordinates.at(1);
    }

    /*!
     * \brief Equality operator for comparing integral coordinates.
     *
     * Returns true if all coordinates of this point are exactly equal to the corresponding
     * coordinates of the other point. This overload is used for integral coordinate types.
     *
     * \tparam H The type of the other point's coordinates.
     * \tparam d The dimensionality of the point.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H,
        size_t d
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if_t<std::is_integral<H>::value, int> = 0
        /// @endcond
        >
    constexpr bool operator==(const PointXd<H, d>& rhs) const
    {
        return std::equal(this->m_coordinates.begin(), this->m_coordinates.end(), rhs.GetCoordinates().begin());
    }

    /*!
     * \brief Inequality operator for comparing coordinates.
     *
     * Returns true if any coordinates of this point are not equal to the corresponding
     * coordinates of the other point.
     *
     * \tparam H The type of the other point's coordinates.
     * \tparam d The dimensionality of the point.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H, size_t d>
    constexpr bool operator!=(const PointXd<H, d>& rhs) const
    {
        return !(*this == rhs);
    }

    /*!
     * \brief Equality operator for comparing floating-point coordinates.
     *
     * Returns true if all coordinates of this point are approximately equal to the corresponding
     * coordinates of the other point. Comparison is performed using a tolerance based on units
     * in the last place (ULP), allowing for small floating-point inaccuracies.
     *
     * \tparam H The type of the other point's coordinates.
     * \tparam d The dimensionality of the point.
     *
     * \since ids_peak_common 1.0
     */
    template <typename H,
        size_t d
        /// @cond HIDE_FROM_DOXYGEN
        ,
        typename std::enable_if_t<std::is_floating_point<H>::value, int> = 0
        /// @endcond
        >
    constexpr bool operator==(const PointXd<H, d>& rhs) const
    {
        using common_type = std::common_type_t<T, H>;

        // Unit in the last place
        constexpr uint32_t ulp = 4;

        return std::equal(this->m_coordinates.begin(), this->m_coordinates.end(), rhs.GetCoordinates().begin(),
            [ulp](const auto& left, const auto& right) {
                return detail::AreAlmostEqual<common_type>(static_cast<common_type>(left), static_cast<common_type>(right), ulp);
            });
    }

    /*!
     * \brief Returns the coordinates of the point as an array.
     *
     * \return A copy of the internal coordinate array.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr std::array<T, dimension> GetCoordinates() const
    {
        return m_coordinates;
    }

private:
    std::array<T, dimension> m_coordinates{};
};

/*!
 * \ingroup ids_peak_common_types_geometry ids_peak_common_detail
 * \brief 2D point template type.
 *
 * Represents a two-dimensional point consisting of x and y coordinates.
 * This is a convenience alias for a PointXd with two dimensions.
 *
 * \tparam T The coordinate data type.
 *
 * \since ids_peak_common 1.0
 */
template <typename T>
class PointT : public PointXd<T, 2>
{

private:
    using PointType = PointT<T>;

public:
    static_assert(std::is_arithmetic<T>::value, "Template argument of Point must be arithmetic.");

    /*!
     * \brief Default constructor for PointT (2D point).
     *
     * Initializes the point with default-initialized coordinates (x and y).
     *
     * \since ids_peak_common 1.0
     */
    constexpr PointT() = default;

    /*!
     * \brief Point constructor from x and y coordinates
     * \param x x coordinate
     * \param y y coordinate
     *
     * \since ids_peak_common 1.0
     */
    constexpr PointT(T x, T y)
        : PointXd<T, 2>({ x, y })
    {}

    /*!
     * \brief Stream output operator for PointT.
     *
     * Outputs the point's coordinates in a readable format: { x: ..., y: ... }.
     *
     * \param os The output stream.
     * \param point The point to print.
     * \return A reference to the output stream.
     *
     * \since ids_peak_common 1.0
     */
    friend std::ostream& operator<<(std::ostream& os, PointT point)
    {
        return os << "{ x: " << point.GetX() << ", y: " << point.GetY() << " }";
    }

    /*!
     * \brief Returns a string representation of the point.
     *
     * Formats the point as: { x: ..., y: ... }.
     *
     * \return A string containing the formatted coordinates.
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
    friend detail::BackendAccessor<PointT<T>>;

    template <typename U = T, typename std::enable_if<has_c_type_of<PointT<U>>::value, bool>::type = false>
    constexpr explicit PointT(peak::common::detail::c_type_of_t<PointT<U>> point)
        : PointT(static_cast<T>(point.x), static_cast<T>(point.y))
    {}

    template <typename U = T, typename std::enable_if<has_c_type_of<PointT<U>>::value, bool>::type = false>
    constexpr explicit operator peak::common::detail::c_type_of_t<PointT<U>>() const
    {
        return { this->GetX(), this->GetY() };
    }

    friend detail::BackendAccessor<PointType>;
};

} // namespace detail

/*!
 * \ingroup ids_peak_common_types_geometry
 * \brief 2D point with 32-bit signed integer coordinates.
 *
 * Provides a stable and public alias for a 2D point type using signed 32-bit integers.
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::PointT<int32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using Point = detail::PointT<int32_t>;

/*!
 * \ingroup ids_peak_common_types_geometry
 * \brief 2D point with single-precision floating-point coordinates.
 *
 * Provides a stable and public alias for a 2D point type using single-precision floating-point values.
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::PointT<float>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using PointF = detail::PointT<float>;

/*!
 * \ingroup ids_peak_common_types_geometry
 * \brief 2D point with 32-bit unsigned integer coordinates.
 *
 * Public alias for a 2D point type based on 32-bit unsigned integers.
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::PointT<uint32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using PointU = detail::PointT<uint32_t>;

} // namespace common 
} // namespace peak
