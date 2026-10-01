/*!
 * \file    peak_icv_point_xyz.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-01-18
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_point.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv/utils/peak_icv_printable.hpp>
#include <peak_icv/utils/peak_icv_type_traits.hpp>
#include <peak_icv_c/types/peak_icv_simple_types.h>
#include <array>
#include <limits>
#include <set>
#include <sstream>
#include <vector>

namespace peak
{
namespace icv
{

/*!
 * \brief A point consists of x, y and z coordinate.
 *
 * \ingroup ids_peak_icv_cpp_geometry
 *
 * \since ids_peak_icv 1.1
 */
class PointXYZ
    : public peak::common::detail::PointXd<float, 3>
    , public detail::IPrintable<PointXYZ>
{
public:
    constexpr PointXYZ() = default;

    /*!
     * \brief Point constructor from x, y and z
     *
     * \param x x coordinate
     * \param y y coordinate
     * \param z z coordinate
     *
     * \since ids_peak_icv 1.1
     */
    constexpr PointXYZ(float x, float y, float z)
        : PointXd<float, 3>({ x, y, z })
    {}

    /*!
     * \brief Returns the z coordinate
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD float GetZ() const
    {
        return PointXd<float, 3>::GetCoordinates().at(2);
    }

    operator peak_icv_point_xyz() const // NOLINT
    {
        return { GetX(), GetY(), GetZ(), {} };
    }

protected:
    void Print(detail::CommaSeperatedStream& stream) const override
    {
        stream << GetX() << GetY() << GetZ();
    }

private:
    friend peak::common::detail::BackendAccessor<PointXYZ>;

    constexpr PointXYZ(peak_icv_point_xyz point) // NOLINT
        : PointXYZ(point.x, point.y, point.z)
    {}
};


} /* namespace icv */
} /* namespace peak */
