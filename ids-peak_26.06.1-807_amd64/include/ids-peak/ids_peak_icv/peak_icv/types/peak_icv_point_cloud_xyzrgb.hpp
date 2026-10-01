/*!
 * \file    peak_icv_point_cloud_xyzrgb.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-04-20
 * \since   1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/detail/peak_icv_point_cloud_xyz_with_overlay.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyzrgb.hpp>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_point_cloud
 *
 * \brief Represents a point cloud
 *        consisting of points with x, y, z coordinates
 *        and RGB values.
 *
 * \since ids_peak_icv 1.4
 */
class PointCloudXYZRGB : public detail::PointCloudXYZOverlay<PointCloudXYZRGB, PointXYZRGB>
{
public:
    using PointCloudXYZOverlay::PointCloudXYZOverlay;

private:
    friend peak::common::detail::BackendAccessor<PointCloudXYZRGB>;
};

} /* namespace icv */
} /* namespace peak */
