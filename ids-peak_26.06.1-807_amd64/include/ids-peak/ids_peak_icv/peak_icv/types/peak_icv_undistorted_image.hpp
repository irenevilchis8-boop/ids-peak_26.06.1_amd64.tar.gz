/*!
 * \file    peak_icv_undistorted_image.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-09-17
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/algorithms/calibration/peak_icv_intrinsic_parameters.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <utility>

namespace peak
{
namespace icv
{

/*!
 * \brief
 *     Represents an image that has undergone undistortion.
 *
 * The `UndistortedImage` class is derived from `Image` and
 * encapsulates the result of an undistortion process.
 * It includes updated intrinsic parameters computed during the undistortion.
 * These parameters are essential for further processing such as point cloud generation.
 *
 * \since ids_peak_icv 1.1
 * \ingroup ids_peak_icv_cpp_types
 */
class UndistortedImage final : public Image
{
public:
    /*!
     * \brief Constructs an `UndistortedImage` from the specified undistorted `image`
     *        and its corresponding `intrinsicParameters`.
     *
     * \param image               The undistorted image.
     * \param intrinsicParameters The intrinsic parameters associated with the undistorted image.
     *
     * \since ids_peak_icv 1.1
     */
    UndistortedImage(const Image& image, const IntrinsicParameters& intrinsicParameters);

    /*!
     * \return The intrinsic parameters associated with the undistorted image.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD IntrinsicParameters GetIntrinsicParameters() const;

private:
    friend peak::common::detail::BackendAccessor<UndistortedImage>;

    const IntrinsicParameters m_intrinsicParameters;
};

inline UndistortedImage::UndistortedImage(const Image& image, const IntrinsicParameters& intrinsicParameters)
    : Image{ image }
    , m_intrinsicParameters{ intrinsicParameters }
{}

inline IntrinsicParameters UndistortedImage::GetIntrinsicParameters() const
{
    return m_intrinsicParameters;
}

} /* namespace icv */
} /* namespace peak */
