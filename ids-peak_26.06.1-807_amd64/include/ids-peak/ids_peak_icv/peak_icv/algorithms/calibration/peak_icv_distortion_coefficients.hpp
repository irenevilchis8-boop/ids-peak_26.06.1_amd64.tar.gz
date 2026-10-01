/*!
 * \file    peak_icv_distortion_coefficients.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-27
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_backend_accessor.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_intrinsic_parameters.h>
#include <algorithm>
#include <array>
#include <vector>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Radial distortion coefficients.
 *
 * Describes a polynomial distortion model
 * based on the radial distance from the image center.
 *
 * The array contains six coefficients:
 * `k1, k2, k3, k4, k5, k6`.
 */
using RadialDistortion = std::array<double, 6>;

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Tangential distortion coefficients.
 *
 * Describes tangential distortion
 * caused by lens decentering,
 * where the lens is not perfectly aligned with the optical axis.
 *
 * The array contains two coefficients:
 * `p1, p2`.
 */
using TangentialDistortion = std::array<double, 2>;

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Prism distortion coefficients.
 *
 * Describes asymmetrical distortions
 * introduced by elements such as prisms.
 *
 * The array contains four coefficients:
 * `s1, s2, s3, s4`.
 */
using PrismDistortion = std::array<double, 4>;

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Tilt distortion coefficients.
 *
 * Describes distortion from lens tilt
 * relative to the image plane.
 *
 * The array contains two coefficients:
 * `τx, τy`.
 */
using TiltDistortion = std::array<double, 2>;

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Holds lens distortion coefficients.
 *
 * Contains coefficients
 * used to model and correct optical distortions
 * introduced by real-world lenses.
 * These coefficients are typically estimated during camera calibration
 * and are used for image undistortion or improving projection accuracy.
 *
 * The distortion model includes:
 *
 * - \ref RadialDistortion "RadialDistortion":
 *   Radial distortion causes straight lines to appear curved,
 *   especially near the image edges.
 *   The effect increases with distance from the optical center.
 *
 * - \ref TangentialDistortion "TangentialDistortion":
 *   Tangential distortion results from lens decentering,
 *   where the lens is not perfectly aligned with the optical axis.
 *   This causes image points to be displaced perpendicular to the radial direction.
 *
 * - \ref PrismDistortion "PrismDistortion":
 *   Prism distortion introduces asymmetrical warping
 *   due to optical elements such as prisms or tilted glass plates.
 *   This distortion leads to non-uniform displacement
 *   that cannot be captured by purely radial models.
 *
 * - \ref TiltDistortion "TiltDistortion":
 *   Tilt distortion occurs when the lens
 *   is tilted relative to the image plane,
 *   introducing a global projective distortion
 *   that skews the overall image geometry.
 *
 * \since ids_peak_icv 1.1
 */
class DistortionCoefficients
{
public:
    /*!
     * \brief Creates distortion coefficients from radial and tangential distortion coefficients.
     *
     * \since ids_peak_icv 1.1
     */
    DistortionCoefficients(const RadialDistortion& radialDistortion, const TangentialDistortion& tangentialDistortion);

    /*!
     * \brief Creates distortion coefficients from radial, tangential and prism distortion coefficients.
     *
     * \since ids_peak_icv 1.1
     */
    DistortionCoefficients(
        const RadialDistortion& radialDistortion, const TangentialDistortion& tangentialDistortion, const PrismDistortion& prismDistortion);

    /*!
     * \brief Creates distortion coefficients from radial, tangential, prism and tilt distortion coefficients.
     *
     * \since ids_peak_icv 1.1
     */
    DistortionCoefficients(const RadialDistortion& radialDistortion, const TangentialDistortion& tangentialDistortion,
        const PrismDistortion& prismDistortion, const TiltDistortion& tiltDistortion);

    /*!
     * \return The radial distortion.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD RadialDistortion GetRadialDistortion() const;

    /*!
     * \return The tangential distortion.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD TangentialDistortion GetTangentialDistortion() const;

    /*!
     * \return The prism distortion.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD PrismDistortion GetPrismDistortion() const;

    /*!
     * \return The tilt distortion.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD TiltDistortion GetTiltDistortion() const;

    bool operator==(const DistortionCoefficients& rhs) const;

private:
    friend peak::common::detail::BackendAccessor<DistortionCoefficients>;

    explicit DistortionCoefficients(const peak_icv_distortion_coefficients& distortionConditions);

    RadialDistortion m_radialDistortion{};
    TangentialDistortion m_tangentialDistortion{};
    PrismDistortion m_prismDistortion{};
    TiltDistortion m_tiltDistortion{};
};

inline DistortionCoefficients::DistortionCoefficients(
    const RadialDistortion& radialDistortion, const TangentialDistortion& tangentialDistortion)
    : DistortionCoefficients(radialDistortion, tangentialDistortion, {})
{}

inline DistortionCoefficients::DistortionCoefficients(
    const RadialDistortion& radialDistortion, const TangentialDistortion& tangentialDistortion, const PrismDistortion& prismDistortion)
    : DistortionCoefficients(radialDistortion, tangentialDistortion, prismDistortion, {})
{}

inline DistortionCoefficients::DistortionCoefficients(const RadialDistortion& radialDistortion,
    const TangentialDistortion& tangentialDistortion, const PrismDistortion& prismDistortion, const TiltDistortion& tiltDistortion)
    : m_radialDistortion{ radialDistortion }
    , m_tangentialDistortion{ tangentialDistortion }
    , m_prismDistortion{ prismDistortion }
    , m_tiltDistortion{ tiltDistortion }
{}

inline DistortionCoefficients::DistortionCoefficients(const peak_icv_distortion_coefficients& distortionConditions)
{
    std::copy_n(distortionConditions.radial_distortion.coefficients, m_radialDistortion.size(), m_radialDistortion.data());
    std::copy_n(distortionConditions.tangential_distortion.coefficients, m_tangentialDistortion.size(), m_tangentialDistortion.data());
    std::copy_n(distortionConditions.prism_distortion.coefficients, m_prismDistortion.size(), m_prismDistortion.data());
    std::copy_n(distortionConditions.tilt_distortion.coefficients, m_tiltDistortion.size(), m_tiltDistortion.data());
}

inline RadialDistortion DistortionCoefficients::GetRadialDistortion() const
{
    return m_radialDistortion;
}

inline TangentialDistortion DistortionCoefficients::GetTangentialDistortion() const
{
    return m_tangentialDistortion;
}

inline PrismDistortion DistortionCoefficients::GetPrismDistortion() const
{
    return m_prismDistortion;
}

inline TiltDistortion DistortionCoefficients::GetTiltDistortion() const
{
    return m_tiltDistortion;
}

inline bool DistortionCoefficients::operator==(const DistortionCoefficients& rhs) const
{
    return m_radialDistortion == rhs.m_radialDistortion && m_tangentialDistortion == rhs.m_tangentialDistortion
        && m_prismDistortion == rhs.m_prismDistortion && m_tiltDistortion == rhs.m_tiltDistortion;
}

} /* namespace icv */
} /* namespace peak */
