/*!
 * \file    peak_icv_xyz_image.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-05-08
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>
#include <peak_icv/types/peak_icv_undistorted_image.hpp>
#include <peak_icv/types/peak_icv_xyz_image.hpp>
#include <peak_icv_c/algorithms/transformations/peak_icv_xyz_image_transformer.h>
#include <utility>

namespace peak
{
namespace icv
{

/*!
 * \brief
 *     Represents a three-channel image
 *     encoding cartesian coordinates (x, y, z) of a 3D point.
 *
 * This image is derived from an undistorted depth map
 * that contains embedded intrinsic parameters and uses radial coordinates.
 *
 * In contrast to radial coordinates,
 * which measure the direct distance from the optical center to the object,
 * cartesian coordinates project these measurements onto a uniform plane.
 *
 * For example:
 * If the camera faces a flat wall,
 * only the cartesian coordinates will form a flat plane,
 * whereas radial values will increase towards the image edges.
 *
 * \ingroup ids_peak_icv_cpp_types
 * \since ids_peak_icv 1.1
 */
class XYZImage final : public Image
{
public:
    /*!
     * \brief
     *     Constructs a cartesian coordinate image
     *     from an undistorted depth map.
     *
     * To convert a distorted depth map into the required format,
     * use the `Undistortion` class beforehand.
     *
     * \supportedPixelformats{XYZImageTransformer}
     *
     * \param undistortedDepthMap
     *     An image encoding radial distances to 3D points
     *     that contains embedded intrinsic camera parameters.
     *
     * \since ids_peak_icv 1.1
     */
    explicit XYZImage(const UndistortedImage& undistortedDepthMap);

    /*!
     * \brief
     *     Transforms the camera-centric coordinates into workspace coordinates.
     *
     * This applies the inverse of the provided extrinsic matrix
     * to map the 3D points
     * from the camera's perspective
     * into the physical workspace.
     *
     * \param extrinsicParameters The extrinsic parameters defining the workspace.
     *
     * \since ids_peak_icv 1.1
     */
    XYZImage TransformToWorkspace(const ExtrinsicParameters& extrinsicParameters) const;

private:
    friend peak::common::detail::BackendAccessor<XYZImage>;

    using Image::Image;
};

inline XYZImage::XYZImage(const UndistortedImage& undistortedDepthMap)
    : Image{ peak::common::PixelFormat::Coord3D_ABC32f, undistortedDepthMap.GetSize() }
{
    auto* const depthMapHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(undistortedDepthMap);

    auto* const xyzImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(*this);

    const auto cType = peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(
        undistortedDepthMap.GetIntrinsicParameters());
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Transform_DepthMap_To_XYZImage(
            xyzImageHandle, cType, sizeof(peak_icv_intrinsic_parameters), depthMapHandle);
    });
}

inline XYZImage XYZImage::TransformToWorkspace(const ExtrinsicParameters& extrinsicParameters) const
{
    const auto extrinsicParametersC = peak::common::detail::BackendAccessor<ExtrinsicParameters>::CreateCType(extrinsicParameters);

    XYZImage outputImage{ this->GetPixelFormat(), this->GetSize() };
    auto* outputHandle = peak::common::detail::BackendAccessor<XYZImage>::BackendHandle(outputImage);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Image_TransformToWorkspace(
            this->GetHandle(), extrinsicParametersC, sizeof(peak_icv_extrinsic_parameters), outputHandle);
    });

    return outputImage;
}

} /* namespace icv */
} /* namespace peak */
