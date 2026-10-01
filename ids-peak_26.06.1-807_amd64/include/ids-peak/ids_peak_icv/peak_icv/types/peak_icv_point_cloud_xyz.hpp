/*!
 * \file    peak_icv_point_cloud_xyz.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-03-19
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/types/detail/peak_icv_point_cloud.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyz.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyzi.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv/types/peak_icv_undistorted_image.hpp>
#include <peak_icv/types/peak_icv_xyz_image.hpp>
#include <peak_icv/utils/peak_icv_type_traits.hpp>
#include <peak_icv_c/types/peak_icv_point_cloud.h>
#include <algorithm>
#include <memory>
#include <vector>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_point_cloud
 *
 * \brief Represents a point cloud
 *        consisting of points with x, y, and z coordinates.
 *
 * \since ids_peak_icv 1.1
 */
class PointCloudXYZ : public detail::PointCloud<PointCloudXYZ, PointXYZ>
{
public:
    using detail::PointCloud<PointCloudXYZ, PointXYZ>::PointCloud;

    /*!
     * \brief Constructs a point cloud from the specified XYZ image.
     *
     * \param image Image containing x, y, and z coordinates per pixel.
     *
     * \throws NotSupportedException The image format is not supported.
     *
     * \since ids_peak_icv 1.1
     */
    explicit PointCloudXYZ(const XYZImage& image);

    /*!
     * \brief Constructs a point cloud from the specified undistorted depth map.
     *
     * The intrinsic parameters must be embedded in the image.
     *
     * The depth values must represent distances
     * measured in a spherical coordinate system centered at the camera origin.
     * Each pixel must encode the radial distance to a 3D point.
     *
     * Use the `Undistortion` class to convert a distorted depth map into an `UndistortedImage`.
     *
     * \param undistortedDepthMap Image containing distance values per pixel,
     *                            along with intrinsic camera parameters.
     *
     * \throws NotSupportedException The image format is not supported.
     *
     * \since ids_peak_icv 1.1
     */
    explicit PointCloudXYZ(const UndistortedImage& undistortedDepthMap);

    /*!
     * \brief Constructs a point cloud by loading it from the specified file.
     *
     * The file format is determined
     * by the specified file extension of the file name.
     *
     * Supported file formats (with required file extensions):
     * - PLY (.ply) – Polygon File Format
     *
     * \param filePath Path to the point cloud file, encoded in UTF-8.
     *
     * \throws IOException The specified `filePath` is invalid or lacks read permissions,
     *                     or the file is in an unsupported format or contains invalid data.
     *
     * \since ids_peak_icv 1.1
     */
    explicit PointCloudXYZ(const std::string& filePath);

    /*!
     * \brief Constructs a point cloud from the specified list of points.
     *
     * \param points Vector of 3D points.
     *
     * \since ids_peak_icv 1.1
     */
    explicit PointCloudXYZ(const std::vector<PointXYZ>& points);

protected:
    PointCloudXYZ() = default;

private:
#ifndef DOXYGEN_SHOULD_SKIP_THIS // skip this as doxygen cannot handle friended base
    friend detail::PointCloud<PointCloudXYZ, PointXYZ>;
#endif                           /* DOXYGEN_SHOULD_SKIP_THIS */

    friend peak::common::detail::BackendAccessor<PointCloudXYZ>;

    static peak_icv_point_cloud_handle CreatePointCloudHandle(const XYZImage& image);
    static peak_icv_point_cloud_handle LoadFromFile(const std::string& filePath);
    static peak_icv_point_cloud_handle CreateFromPoints(const std::vector<PointXYZ>& points);
};

inline PointCloudXYZ::PointCloudXYZ(const XYZImage& image)
    : PointCloud<PointCloudXYZ, PointXYZ>{ CreatePointCloudHandle(image) }
{}

inline PointCloudXYZ::PointCloudXYZ(const UndistortedImage& undistortedDepthMap)
    : PointCloudXYZ{ XYZImage{ undistortedDepthMap } }
{}

inline PointCloudXYZ::PointCloudXYZ(const std::string& filePath)
    : PointCloud<PointCloudXYZ, PointXYZ>{ LoadFromFile(filePath) }
{}

inline PointCloudXYZ::PointCloudXYZ(const std::vector<PointXYZ>& points)
    : PointCloud<PointCloudXYZ, PointXYZ>{ CreateFromPoints(points) }
{}

inline peak_icv_point_cloud_handle PointCloudXYZ::CreatePointCloudHandle(const XYZImage& image)
{
    auto* const imageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(image);

    peak_icv_point_cloud_handle pointCloudHandle{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_CreateFromXYZImage(&pointCloudHandle, imageHandle);
    });
    return pointCloudHandle;
}

inline peak_icv_point_cloud_handle PointCloudXYZ::LoadFromFile(const std::string& filePath)
{
    peak_icv_point_cloud_handle handle{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_CreateFromFile(&handle, PEAK_ICV_POINT_TYPE_XYZ, filePath.c_str());
    });
    return handle;
}

inline peak_icv_point_cloud_handle PointCloudXYZ::CreateFromPoints(const std::vector<PointXYZ>& points)
{
    std::vector<peak_icv_point_xyz> pointsC(points.size());

    std::transform(points.begin(), points.end(), pointsC.begin(), [](const PointXYZ& point) -> peak_icv_point_xyz {
        return { point.GetX(), point.GetY(), point.GetZ(), {} };
    });

    peak_icv_point_cloud_handle pointCloudHandle{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_CreateFromPoints(
            &pointCloudHandle, pointsC.data(), pointsC.size(), PEAK_ICV_POINT_TYPE_XYZ);
    });
    return pointCloudHandle;
}

} /* namespace icv */
} /* namespace peak */
