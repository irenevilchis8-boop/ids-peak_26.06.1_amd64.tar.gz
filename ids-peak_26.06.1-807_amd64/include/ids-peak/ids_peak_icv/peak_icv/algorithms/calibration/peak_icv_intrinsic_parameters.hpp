/*!
 * \file    peak_icv_intrinsic_parameters.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-08-21
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_point.hpp>
#include <peak_common/types/geometry/peak_common_size.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_distortion_coefficients.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_intrinsic_parameters.h>
#include <cstring>

namespace peak
{
namespace icv
{


/*!
 * \class IntrinsicParameters
 * \ingroup ids_peak_icv_cpp_calibration
 * \brief The intrinsic parameters contain the necessary information to use the camera calibration.
 *
 * This class contains only the intrinsic parameters and the mean reprojection error of the camera calibration. These parameters are
 * essential for image operations like point cloud generation, image undistortion, and other calibration-dependent operations.
 *
 * \since ids_peak_icv 1.1
 */
class IntrinsicParameters
{
public:
    /*!
     * \brief Provides the image size
     *
     * \return Returns the image size.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::Size GetImageSize() const;

    /*!
     * \brief Provides the principle point
     *
     * \return Returns the principle point.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::PointF GetPrinciplePoint() const;

    /*!
     * \brief Provides the distortion coefficients
     *
     * \return Returns the distortion coefficients.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD DistortionCoefficients GetDistortionCoefficients() const;

    /*!
     * \brief Provides the focal length pixel size ratio
     *
     * \return Returns the focal length pixel size ratio.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::PointF GetFocalLengthPixelSizeRatio() const;

private:
    friend peak::common::detail::BackendAccessor<IntrinsicParameters>;

    explicit IntrinsicParameters(const peak_icv_intrinsic_parameters& intrinsicParameters);
    explicit operator peak_icv_intrinsic_parameters() const;

    peak_icv_intrinsic_parameters m_intrinsicParameters{};
};

inline IntrinsicParameters::IntrinsicParameters(const peak_icv_intrinsic_parameters& intrinsicParameters)
    : m_intrinsicParameters{ intrinsicParameters }
{}

inline IntrinsicParameters::operator peak_icv_intrinsic_parameters() const
{
    return m_intrinsicParameters;
}

inline peak::common::Size IntrinsicParameters::GetImageSize() const
{
    return { m_intrinsicParameters.image_size.width, m_intrinsicParameters.image_size.height };
}

inline peak::common::PointF IntrinsicParameters::GetPrinciplePoint() const
{
    return peak::common::PointF{ m_intrinsicParameters.principle_point.x, m_intrinsicParameters.principle_point.y };
}

inline DistortionCoefficients IntrinsicParameters::GetDistortionCoefficients() const
{
    std::array<double, 14> coefficients{};
    memcpy(coefficients.data(), &m_intrinsicParameters.distortion_coefficients, sizeof(m_intrinsicParameters.distortion_coefficients));

    RadialDistortion radial{};
    auto end = coefficients.begin() + radial.size(); // NOLINT(readability-qualified-auto)
    std::copy(coefficients.begin(), end, radial.begin());

    TangentialDistortion tangential{};
    auto begin = end; // NOLINT(readability-qualified-auto)
    end += tangential.size();
    std::copy(begin, end, tangential.begin());

    PrismDistortion prism{};
    begin = end;
    end += prism.size();
    std::copy(begin, end, prism.begin());

    TiltDistortion tilt{};
    begin = end;
    end += tilt.size();
    std::copy(begin, end, tilt.begin());

    return { radial, tangential, prism, tilt };
}

inline peak::common::PointF IntrinsicParameters::GetFocalLengthPixelSizeRatio() const
{
    return { m_intrinsicParameters.focal_length_pixel_size_ratio.x, m_intrinsicParameters.focal_length_pixel_size_ratio.y };
}


} /* namespace icv */
} /* namespace peak */
