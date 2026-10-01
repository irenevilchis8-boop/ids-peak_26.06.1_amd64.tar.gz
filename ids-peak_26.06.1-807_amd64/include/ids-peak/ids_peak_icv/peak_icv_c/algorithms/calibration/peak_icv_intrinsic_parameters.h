/*!
 * \file    peak_icv_intrinsic_parameters.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-28
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif


/*!
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Prism distortion coefficients.
 *
 * Describes asymmetrical distortions
 * introduced by elements such as prisms.
 *
 * The array contains four coefficients:
 * `s1, s2, s3, s4`.
 */
typedef struct peak_icv_prism_distortion
{
    double coefficients[4]; //!< Array of four coefficients defining prism distortion.
} peak_icv_prism_distortion;

/*!
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Radial distortion coefficients.
 *
 * Describes a polynomial distortion model
 * based on the radial distance from the image center.
 *
 * The array contains six coefficients:
 * `k1, k2, k3, k4, k5, k6`.
 */
typedef struct peak_icv_radial_distortion
{
    double coefficients[6]; //!< Array of six coefficients defining radial distortion.
} peak_icv_radial_distortion;

/*!
 * \ingroup ids_peak_icv_c_calibration
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
typedef struct peak_icv_tangential_distortion
{
    double coefficients[2]; //!< Array of two coefficients defining tangential distortion.
} peak_icv_tangential_distortion;

/*!
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Tilt distortion coefficients.
 *
 * Describes distortion from lens tilt
 * relative to the image plane.
 *
 * The array contains two coefficients:
 * `τx, τy`.
 */
typedef struct peak_icv_tilt_distortion
{
    double coefficients[2]; //!< Array of two coefficients defining tilt distortion.
} peak_icv_tilt_distortion;

/*!
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Holds lens distortion coefficients.
 *
 * Contains coefficients
 * used to model and correct optical distortions
 * introduced by real-world lenses.
 * These coefficients are typically estimated during camera calibration
 * and are used for image undistortion or improving projection accuracy.
 */
typedef struct peak_icv_distortion_coefficients
{
    /*!
     * Radial distortion causes straight lines to appear curved,
     * especially near the image edges.
     * The effect increases with distance from the optical center.
     */
    peak_icv_radial_distortion radial_distortion;
    /*!
     * Tangential distortion results from lens decentering,
     * where the lens is not perfectly aligned with the optical axis.
     * This causes image points to be displaced perpendicular to the radial direction.
     */
    peak_icv_tangential_distortion tangential_distortion;
    /*!
     * Prism distortion introduces asymmetrical warping
     * due to optical elements such as prisms or tilted glass plates.
     * This distortion leads to non-uniform displacement
     * that cannot be captured by purely radial models.
     */
    peak_icv_prism_distortion prism_distortion;
    /*!
     * Tilt distortion occurs when the lens
     * is tilted relative to the image plane,
     * introducing a global projective distortion
     * that skews the overall image geometry.
     */
    peak_icv_tilt_distortion tilt_distortion;
} peak_icv_distortion_coefficients;

/*!
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Represents the intrinsic camera parameters
 *        that define the internal geometry and optical characteristics of the camera.
 */
typedef struct peak_icv_intrinsic_parameters
{
    peak_common_size image_size;                              //!< Resolution the intrinsic camera parameters were created with.
    peak_icv_binning_factor binning_factor;                   //!< Binning the intrinsic camera parameters were created with.
    peak_icv_distortion_coefficients distortion_coefficients; //!< Various distortion coefficients.
    peak_common_point_f focal_length_pixel_size_ratio;        //!< Ratio of focal length to pixel size.
    peak_common_point_f principle_point;                      //!< Principal point in the image sensor.
} peak_icv_intrinsic_parameters;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
