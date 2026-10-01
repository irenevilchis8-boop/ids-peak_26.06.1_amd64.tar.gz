/*!
 * \file    peak_icv_coordinate_system.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_point.hpp>
#include <peak_common/types/geometry/peak_common_vector.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/utils/peak_icv_printable.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_view.h>
#include <limits>
#include <utility>
#include <vector>

namespace peak
{
namespace icv
{


/*!
 * \brief
 * \ingroup ids_peak_icv_cpp_geometry
 *
 * Represents the coordinate system of a calibration view projected into the image plane.
 * The coordinate system is represented by its origin and three vectors, each corresponding to one of the three coordinate axes (X, Y and
 * Z). These vectors describe the directions of the respective axes projected from 3D into 2D space. Their lengths are determined by twice
 * the distance between neighboring markers on the calibration plate.
 *
 * \since ids_peak_icv 1.1
 */

class CoordinateSystem : public detail::IPrintable<CoordinateSystem>
{
public:
    /*!
     * \brief CoordinateSystem constructor
     *
     * \since ids_peak_icv 1.1
     */
    CoordinateSystem() = default;

    /*!
     * \brief CoordinateSystem constructor from origin, xAxis, yAxis and zAxis
     *
     * \param origin location of the coordinate system origin
     * \param xAxis vector that describes the x-axis of the coordinate system
     * \param yAxis vector that describes the y-axis of the coordinate system
     * \param zAxis vector that describes the z-axis of the coordinate system
     *
     * \since ids_peak_icv 1.1
     */
    CoordinateSystem(
        peak::common::PointF origin, peak::common::VectorF xAxis, peak::common::VectorF yAxis, peak::common::VectorF zAxis)
        : m_origin(origin)
        , m_xAxis(xAxis)
        , m_yAxis(yAxis)
        , m_zAxis(zAxis)
    {}

    /*!
     * \brief Returns the location of the coordinate system origin
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::PointF GetOrigin() const
    {
        return m_origin;
    }

    /*!
     * \brief Returns the vector that describes the x-axis of the coordinate system. Its length is determined by twice
     * the distance between neighboring markers on the calibration plate.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::VectorF GetXAxis() const
    {
        return m_xAxis;
    }

    /*!
     * \brief Returns the vector that describes the y-axis of the coordinate system. Its length is determined by twice
     * the distance between neighboring markers on the calibration plate.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::VectorF GetYAxis() const
    {
        return m_yAxis;
    }

    /*!
     * \brief Returns the vector that describes the z-axis of the coordinate system. Its length is determined by twice
     * the distance between neighboring markers on the calibration plate.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::VectorF GetZAxis() const
    {
        return m_zAxis;
    }

    bool operator==(const CoordinateSystem& rhs) const
    {
        return m_origin == rhs.GetOrigin() && m_xAxis == rhs.GetXAxis() && m_yAxis == rhs.GetYAxis() && m_zAxis == rhs.GetZAxis();
    }

protected:
    void Print(detail::CommaSeperatedStream& stream) const override
    {
        stream << m_origin << m_xAxis << m_yAxis << m_zAxis;
    }

private:
    friend peak::common::detail::BackendAccessor<CoordinateSystem>;

    explicit CoordinateSystem(const peak_icv_coordinate_system& coordinateSystem);

    peak::common::PointF m_origin{ 0, 0 };
    peak::common::VectorF m_xAxis{ 1, 0 };
    peak::common::VectorF m_yAxis{ 0, 1 };
    peak::common::VectorF m_zAxis{ 0, 0 };
};

inline CoordinateSystem::CoordinateSystem(const peak_icv_coordinate_system& coordinateSystem)
    : m_origin(peak::common::detail::BackendAccessor<peak::common::PointF>::CreateInstance(coordinateSystem.origin))
    , m_xAxis(peak::common::detail::BackendAccessor<peak::common::VectorF>::CreateInstance(coordinateSystem.x_axis))
    , m_yAxis(peak::common::detail::BackendAccessor<peak::common::VectorF>::CreateInstance(coordinateSystem.y_axis))
    , m_zAxis(peak::common::detail::BackendAccessor<peak::common::VectorF>::CreateInstance(coordinateSystem.z_axis))
{}

} /* namespace icv */
} /* namespace peak */
