/*!
 * \file    peak_icv_point_xyzrgb.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-04-20
 * \since   1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_rectangle.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/types/geometry/peak_icv_point_xyz.hpp>
#include <peak_icv/utils/peak_icv_printable.hpp>
#include <vector>

namespace peak
{
namespace icv
{

/*!
 * \brief A point consists of x, y, z coordinates and color metadata.
 *
 * \ingroup ids_peak_icv_cpp_geometry
 *
 * \since ids_peak_icv 1.4
 */
class PointXYZRGB

    : public PointXYZ
    , public detail::IPrintable<PointXYZRGB>
{
public:
    constexpr PointXYZRGB() = default;

    /*!
     * \brief Point constructor from x, y and z and color (R, G and B) metadata
     * \param x x coordinate
     * \param y y coordinate
     * \param z z coordinate
     * \param red overlay metadata
     * \param green overlay metadata
     * \param blue overlay metadata
     *
     * \since ids_peak_icv 1.4
     */
    constexpr PointXYZRGB(float x, float y, float z, uint16_t red, uint16_t green, uint16_t blue)
        : PointXYZ{ x, y, z }
        , m_red{ red }
        , m_green{ green }
        , m_blue{ blue }
    {}

    /*!
     * \brief Returns the red metadata
     *
     * \since ids_peak_icv 1.4
     */
    PEAK_COMMON_NO_DISCARD constexpr uint16_t GetRed() const
    {
        return m_red;
    }

    /*!
     * \brief Returns the green metadata
     *
     * \since ids_peak_icv 1.4
     */
    PEAK_COMMON_NO_DISCARD constexpr uint16_t GetGreen() const
    {
        return m_green;
    }

    /*!
     * \brief Returns the blue metadata
     *
     * \since ids_peak_icv 1.4
     */
    PEAK_COMMON_NO_DISCARD constexpr uint16_t GetBlue() const
    {
        return m_blue;
    }

    /*!
     * PointXYZRGB
     * equality operator
     *
     * \since ids_peak_icv 1.4
     */
    constexpr bool operator==(const PointXYZRGB& rhs) const
    {
        return PointXYZ::operator==(rhs) && m_red == rhs.m_red && m_green == rhs.m_green && m_blue == rhs.m_blue;
    }

    operator peak_icv_point_xyzrgb() const // NOLINT
    {
        return { GetX(), GetY(), GetZ(), {}, m_red, m_green, m_blue };
    }

protected:
    void Print(detail::CommaSeperatedStream& stream) const override
    {
        stream << GetX() << GetY() << GetZ() << GetRed() << GetGreen() << GetBlue();
    }

private:
    friend peak::common::detail::BackendAccessor<PointXYZRGB>;

    constexpr PointXYZRGB(peak_icv_point_xyzrgb point) // NOLINT
        : PointXYZRGB(point.x, point.y, point.z, point.red, point.green, point.blue)
    {}

    uint16_t m_red{};
    uint16_t m_green{};
    uint16_t m_blue{};
};
} /* namespace icv */
} /* namespace peak */
