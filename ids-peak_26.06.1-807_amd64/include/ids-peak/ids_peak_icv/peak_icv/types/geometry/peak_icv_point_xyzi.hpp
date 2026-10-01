/*!
 * \file    peak_icv_point_xyzi.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-01-18
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
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
 * \brief A point consists of x, y, z coordinates and intensity metadata.
 *
 * \ingroup ids_peak_icv_cpp_geometry
 *
 * \since ids_peak_icv 1.1
 */
class PointXYZI
    : public PointXYZ
    , public detail::IPrintable<PointXYZI>
{
public:
    constexpr PointXYZI() = default;

    /*!
     * \brief Point constructor from x, y and z and intensity
     * \param x x coordinate
     * \param y y coordinate
     * \param z z coordinate
     * \param intensity intensity metadata
     *
     * \since ids_peak_icv 1.1
     */
    constexpr PointXYZI(float x, float y, float z, uint16_t intensity)
        : PointXYZ{ x, y, z }
        , m_intensity{ intensity }
    {}

    /*!
     * \brief Returns the intensity metadata
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD constexpr uint16_t GetIntensity() const
    {
        return m_intensity;
    }

    /*!
     * PointXYZI equality operator
     *
     * \since ids_peak_icv 1.1
     */
    constexpr bool operator==(const PointXYZI& rhs) const
    {
        return PointXYZ::operator==(rhs) && m_intensity == rhs.m_intensity;
    }

    operator peak_icv_point_xyzi() const // NOLINT
    {
        return { GetX(), GetY(), GetZ(), m_intensity };
    }

protected:
    void Print(detail::CommaSeperatedStream& stream) const override
    {
        stream << GetX() << GetY() << GetZ() << GetIntensity();
    }

private:
    friend peak::common::detail::BackendAccessor<PointXYZI>;

    constexpr PointXYZI(peak_icv_point_xyzi point) // NOLINT
        : PointXYZI(point.x, point.y, point.z, point.intensity)
    {}

    uint16_t m_intensity{};
};
} /* namespace icv */
} /* namespace peak */
