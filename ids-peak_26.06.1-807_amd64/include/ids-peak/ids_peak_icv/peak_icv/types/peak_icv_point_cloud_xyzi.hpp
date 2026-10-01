/*!
 * \file    peak_icv_point_cloud_xyzi.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-03-19
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/detail/peak_icv_point_cloud_xyz_with_overlay.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyzi.hpp>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_point_cloud
 *
 * \brief Represents a point cloud
 *        consisting of points with x, y, z coordinates
 *        and an intensity value.
 *
 * \since ids_peak_icv 1.1
 */
class PointCloudXYZI : public detail::PointCloudXYZOverlay<PointCloudXYZI, PointXYZI>
{
public:
    using PointCloudXYZOverlay::PointCloudXYZOverlay;

private:
    friend peak::common::detail::BackendAccessor<PointCloudXYZI>;
};

} /* namespace icv */
} /* namespace peak */
