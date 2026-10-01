/*!
 * \file    peak_common_rectangle.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-14
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_point.hpp>
#include <peak_common/types/geometry/peak_common_size.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common_c/types/peak_common_simple_types.h>

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
 * \brief A generic rectangle defined by a point and a size.
 *
 * Represents a rectangle composed of a position (top-left corner) and a size.
 * The position and size types are customizable via template parameters.
 *
 * \tparam PointType The type representing the positions' coordinates (e.g., int32_t, float).
 * \tparam SizeType The type representing the size's dimensions (e.g., uint32_t, float).
 *
 * \since ids_peak_common 1.0
 */
template <typename PointType, typename SizeType>
class RectangleT
{

public:
    static_assert(std::is_arithmetic<PointType>::value, "Template argument of Rect must be arithmetic.");

    /*!
     * \brief Default constructor for RectangleT.
     *
     * Constructs an empty rectangle with default-initialized point and size.
     *
     * \since ids_peak_common 1.0
     */
    constexpr RectangleT() = default;

    /*!
     * \brief Constructs a rectangle from a point and a size.
     *
     * \param point The top-left corner of the rectangle.
     * \param size The dimensions of the rectangle.
     *
     * \since ids_peak_common 1.0
     */
    constexpr RectangleT(const PointT<PointType>& point, const SizeT<SizeType>& size)
        : m_point(point)
        , m_size(size)
    {}

    /*!
     * \brief Constructs a rectangle from coordinates and dimensions.
     *
     * \param x The x-coordinate of the top-left corner.
     * \param y The y-coordinate of the top-left corner.
     * \param width The width of the rectangle.
     * \param height The height of the rectangle.
     *
     * \since ids_peak_common 1.0
     */
    constexpr RectangleT(PointType x, PointType y, SizeType width, SizeType height)
        : RectangleT({ x, y }, { width, height })
    {}

    /*!
     * \brief Returns the x-coordinate of the rectangle's top-left corner.
     *
     * \copydetails PointT::GetX()
     *
     */
    PEAK_COMMON_NO_DISCARD constexpr PointType GetX() const
    {
        return m_point.GetX();
    }

    /*!
     * \brief Returns the y-coordinate of the rectangle's top-left corner.
     *
     * \copydetails PointT::GetY()
     */
    PEAK_COMMON_NO_DISCARD constexpr PointType GetY() const
    {
        return m_point.GetY();
    }

    /*!
     * \brief Returns the width of the rectangle.
     *
     * \copydetails PointT::GetX()
     */
    PEAK_COMMON_NO_DISCARD constexpr SizeType GetWidth() const
    {
        return m_size.GetWidth();
    }

    /*!
     * \brief Returns the height of the rectangle.
     *
     * \copydetails Size::GetHeight()
     *
     */
    PEAK_COMMON_NO_DISCARD constexpr SizeType GetHeight() const
    {
        return m_size.GetHeight();
    }

    /*!
     * \brief Returns the size of the rectangle.
     */
    PEAK_COMMON_NO_DISCARD constexpr SizeT<SizeType> GetSize() const
    {
        return m_size;
    }

    /*!
     * \brief Returns the top-left corner of the rectangle as a [Point](\ref PointT).
     */
    PEAK_COMMON_NO_DISCARD constexpr PointT<PointType> GetPosition() const
    {
        return m_point;
    }

    /*!
     * \brief Equality operator
     *
     * Compares position and size for equality.
     *
     * \param rhs The RectangleT object to compare against.
     * \return true if both position and size are equal; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    template <typename RhsPointType, typename RhsSizeType>
    constexpr bool operator==(const RectangleT<RhsPointType, RhsSizeType>& rhs) const
    {
        return GetPosition() == rhs.GetPosition() && GetSize() == rhs.GetSize();
    }

    /*!
     * \brief Inequality operator.
     *
     * Returns true if the rectangles are not equal.
     *
     * \param rhs The RectangleT object to compare against.
     * \return true if either position or size is different; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    template <typename RhsPointType, typename RhsSizeType>
    constexpr bool operator!=(const RectangleT<RhsPointType, RhsSizeType>& rhs) const
    {
        return !(*this == rhs);
    }

    /*!
     * \brief Stream output operator for RectangleT.
     *
     * Outputs the rectangle in the format: { point: ..., size: ... }.
     *
     * \param os The output stream.
     * \param rectangle The rectangle to print.
     * \return Reference to the output stream.
     *
     * \since ids_peak_common 1.0
     */
    friend std::ostream& operator<<(std::ostream& os, RectangleT rectangle)
    {
        return os << "{ point: " << rectangle.m_point << ", size: " << rectangle.m_size << " }";
    }

    /*!
     * \brief Returns a string representation of the rectangle.
     *
     * The output format is: { point: ..., size: ... }.
     *
     * \return A string containing the rectangle's description.
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
    PointT<PointType> m_point;
    SizeT<SizeType> m_size;

    friend detail::BackendAccessor<RectangleT<PointType, SizeType>>;

    //! \private
    template <typename T = PointType, typename U = SizeType,
        typename std::enable_if<has_c_type_of<RectangleT<T, U>>::value, bool>::type = false>
    constexpr explicit operator peak::common::detail::c_type_of_t<RectangleT<T, U>>() const // NOLINT
    {
        return { this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight() };
    }
};

} // namespace detail

/*!
 * \ingroup ids_peak_common_types_geometry
 * \brief Rectangle with integer coordinates and unsigned dimensions.
 *
 * Provides a stable and public alias for a rectangle type using `int32_t` for position
 * and `uint32_t` for size.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::RectangleT<int32_t, uint32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using Rectangle = detail::RectangleT<int32_t, uint32_t>;

/*!
 * \ingroup ids_peak_common_types_geometry
 * \brief Rectangle with floating-point coordinates and dimensions.
 *
 * Provides a stable and public alias for a rectangle type using `float` for both position and size.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::RectangleT<float, float>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.0
 */
using RectangleF = detail::RectangleT<float, float>;

/*!
 * \ingroup ids_peak_common_types_geometry
 * \brief Rectangle with unsigned coordinates and unsigned dimensions.
 *
 * Provides a stable and public alias for a rectangle type using `uint32_t` for position
 * and `uint32_t` for size.
 *
 * This alias is intended for general use in user code.
 *
 * Direct usage of `detail::RectangleT<uint32_t, uint32_t>` is discouraged, as internal implementations may change.
 * Always use this public alias for forward compatibility.
 *
 * \since ids_peak_common 1.1
 */
using RectangleU = detail::RectangleT<uint32_t, uint32_t>;

} // namespace common 
} // namespace peak
