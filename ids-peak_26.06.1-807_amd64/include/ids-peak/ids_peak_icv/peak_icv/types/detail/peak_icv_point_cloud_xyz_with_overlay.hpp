/*!
 * \file    peak_icv_point_cloud_xyz_with_overlay.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-04-23
 * \since   1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/types/detail/peak_icv_point_cloud.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyz.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyzrgb.hpp>
#include <peak_icv/types/peak_icv_xyz_image.hpp>
#include <peak_icv/utils/peak_icv_type_traits.hpp>
#include <peak_icv_c/types/peak_icv_point_cloud.h>
#include <algorithm>
#include <vector>

namespace peak
{
namespace icv
{

namespace detail
{
/*!
 * \ingroup ids_peak_icv_cpp_point_cloud
 *
 * \brief Represents a point cloud
 *        consisting of points with x, y, z coordinates
 *        and red, green and blue values.
 *
 * \since ids_peak_icv 1.4
 */

template <typename PointCloudType, typename InnerPointType>
class PointCloudXYZOverlay : public PointCloud<PointCloudType, InnerPointType>
{
public:
    using PointCloud<PointCloudType, InnerPointType>::PointCloud;

    /*!
     * \brief Constructs a point cloud from the specified XYZ image and intensity image.
     *
     * \note The region of the intensity image is disregarded.
     *
     * \param xyzImage       Image containing x, y, and z coordinates per pixel.
     * \param overlayImage   Image containing intensity or rgb values per pixel.
     *
     * \throws NotSupportedException The image format is not supported.
     * \throws MismatchException     The specified `xyzImage` and `overlayImage` do not have the same dimensions.
     *
     * \since ids_peak_icv 1.4
     */
    PointCloudXYZOverlay(const XYZImage& xyzImage, const Image& overlayImage);

    /*!
     * \brief Constructs a point cloud from the specified undistorted depth map and intensity image.
     *
     * The intrinsic parameters must be embedded in the image.
     *
     * The depth values must represent distances
     * measured in a spherical coordinate system centered at the camera origin.
     * Each pixel must encode the radial distance to a 3D point.
     *
     * Use the `Undistortion` class to convert a distorted depth map into an `UndistortedImage`.
     *
     * \note The region of the intensity image is disregarded.
     *
     * \param undistortedDepthMap Image containing distance values per pixel,
     *                            along with intrinsic camera parameters.
     * \param overlayImage        Image containing intensity or rgb values per pixel.
     *
     * \throws NotSupportedException The image format is not supported.
     * \throws MismatchException     The specified `undistortedDepthMap` and `overlayImage` do not have the same dimensions.
     *
     * \since ids_peak_icv 1.4
     */
    PointCloudXYZOverlay(const UndistortedImage& undistortedDepthMap, const Image& overlayImage);

    /*!
     * \brief Constructs a point cloud by loading it from the specified file.
     *
     * The file format is determined
     * by the specified file extension of the file name.
     *
     * Supported file formats (with required file extensions):
     * - PLY (.ply) – Polygon File Format
     *
     * \param filePath        Path to the point cloud file, encoded in UTF-8.
     * \param pixelFormatName Specifies the pixel format of the intensity values.
     *
     * \throws IOException           The specified `filePath` is invalid or lacks read permissions,
     *                               or the file is in an unsupported format or contains invalid data.
     * \throws NotSupportedException The pixel format is not supported.
     *
     * \since ids_peak_icv 1.4
     */
    explicit PointCloudXYZOverlay(const std::string& filePath, peak::common::PixelFormat pixelFormatName);

    /*!
     * \brief Constructs a point cloud from the specified list of points.
     *
     * \param points          Vector of 3D points with intensity.
     * \param pixelFormatName Specifies the pixel format of the intensity values.
     *
     * \throws NotSupportedException The pixel format is not supported.
     *
     * \since ids_peak_icv 1.4
     */
    explicit PointCloudXYZOverlay(const std::vector<InnerPointType>& points, peak::common::PixelFormat pixelFormatName);

protected:
    PointCloudXYZOverlay() = default;

private:
    friend peak::common::detail::BackendAccessor<PointCloudXYZOverlay>;
#ifndef DOXYGEN_SHOULD_SKIP_THIS // skip this as doxygen cannot handle friended base
    friend PointCloud<PointCloudXYZOverlay, InnerPointType>;
#endif                           /* DOXYGEN_SHOULD_SKIP_THIS */

    static peak_icv_point_cloud_handle CreatePointCloudHandle(const XYZImage& xyzImage, const Image& overlayImage);
    static peak_icv_point_type PointTypeFromPixelFormat(peak::common::PixelFormat pixelFormatName);
    static peak_icv_point_cloud_handle LoadFromFile(const std::string& filePath, peak::common::PixelFormat pixelFormatName);
    static peak_icv_point_cloud_handle CreateFromPoints(
        const std::vector<InnerPointType>& points, peak::common::PixelFormat pixelFormatName);
};

template <typename PointCloudType, typename InnerPointType>
inline PointCloudXYZOverlay<PointCloudType, InnerPointType>::PointCloudXYZOverlay(const XYZImage& xyzImage, const Image& overlayImage)
    : PointCloud<PointCloudType, InnerPointType>{ CreatePointCloudHandle(xyzImage, overlayImage) }
{}

template <typename PointCloudType, typename InnerPointType>
inline PointCloudXYZOverlay<PointCloudType, InnerPointType>::PointCloudXYZOverlay(
    const UndistortedImage& undistortedDepthMap, const Image& overlayImage)
    : PointCloudXYZOverlay(XYZImage(undistortedDepthMap), overlayImage)
{}

template <typename PointCloudType, typename InnerPointType>
inline PointCloudXYZOverlay<PointCloudType, InnerPointType>::PointCloudXYZOverlay(
    const std::string& filePath, peak::common::PixelFormat pixelFormatName)
    : PointCloud<PointCloudType, InnerPointType>{ LoadFromFile(filePath, pixelFormatName) }
{}

template <typename PointCloudType, typename InnerPointType>
inline PointCloudXYZOverlay<PointCloudType, InnerPointType>::PointCloudXYZOverlay(
    const std::vector<InnerPointType>& points, peak::common::PixelFormat pixelFormatName)
    : PointCloud<PointCloudType, InnerPointType>{ CreateFromPoints(points, pixelFormatName) }
{}

template <typename PointCloudType, typename InnerPointType>
inline peak_icv_point_cloud_handle PointCloudXYZOverlay<PointCloudType, InnerPointType>::CreatePointCloudHandle(
    const XYZImage& xyzImage, const Image& overlayImage)
{
    auto* const xyzImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(xyzImage);
    auto* const overlayImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(overlayImage);

    peak_icv_point_cloud_handle handle{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage(&handle, xyzImageHandle, overlayImageHandle);
    });
    return handle;
}

template <typename PointCloudType, typename InnerPointType>
inline peak_icv_point_type PointCloudXYZOverlay<PointCloudType, InnerPointType>::PointTypeFromPixelFormat(
    peak::common::PixelFormat pixelFormatName)
{
    switch (pixelFormatName)
    {
    case peak::common::PixelFormat::Mono8:
        return PEAK_ICV_POINT_TYPE_XYZ_I8;
    case peak::common::PixelFormat::Mono10:
        return PEAK_ICV_POINT_TYPE_XYZ_I10;
    case peak::common::PixelFormat::Mono12:
        return PEAK_ICV_POINT_TYPE_XYZ_I12;
    case peak::common::PixelFormat::RGB8:
        return PEAK_ICV_POINT_TYPE_XYZ_RGB8;
    default:
        throw peak::icv::NotSupportedException("The given pixel format is not supported!");
    }
}

template <typename PointCloudType, typename InnerPointType>
inline peak_icv_point_cloud_handle PointCloudXYZOverlay<PointCloudType, InnerPointType>::LoadFromFile(
    const std::string& filePath, peak::common::PixelFormat pixelFormatName)
{
    peak_icv_point_cloud_handle handle{};


    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_CreateFromFile(
            &handle, PointTypeFromPixelFormat(pixelFormatName), filePath.c_str());
    });
    return handle;
}

template <typename PointCloudType, typename InnerPointType>
inline peak_icv_point_cloud_handle PointCloudXYZOverlay<PointCloudType, InnerPointType>::CreateFromPoints(
    const std::vector<InnerPointType>& points, peak::common::PixelFormat pixelFormatName)
{
    std::vector<peak::common::detail::c_type_of_t<InnerPointType>> pointsC{};
    pointsC.reserve(points.size());

    std::transform(points.begin(), points.end(), std::back_inserter(pointsC),
        [](const InnerPointType& point) -> peak::common::detail::c_type_of_t<InnerPointType> {
            return point;
        });

    peak_icv_point_cloud_handle pointCloudHandle{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_CreateFromPoints(
            &pointCloudHandle, pointsC.data(), pointsC.size(), PointTypeFromPixelFormat(pixelFormatName));
    });
    return pointCloudHandle;
}
} // namespace detail

} /* namespace icv */
} /* namespace peak */
