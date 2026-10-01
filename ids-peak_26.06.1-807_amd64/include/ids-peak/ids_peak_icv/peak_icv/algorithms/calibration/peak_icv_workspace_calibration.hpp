/*!
 * \file    peak_icv_workspace_calibration.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-08
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_plate.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_intrinsic_parameters.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_workspace_calibration.h>
#include <utility>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Performs a workspace calibration to determine
 *        the position and orientation of a camera
 *        relative to a physical workspace.
 *
 * Workspace calibration determines
 * the extrinsic parameters of a camera,
 * which describe its position and orientation
 * with respect to the workspace coordinate system.
 *
 * A calibration plate is used
 * to calculate the transformation between
 * the camera coordinate system
 * and the workspace coordinate system.
 * This enables accurate mapping
 * of 2D image points to 3D coordinates in the workspace
 * for tasks such as measurement and localization.
 *
 * The calibration process uses a single image
 * of a calibration plate as input.
 *
 * \since ids_peak_icv 1.1
 */
class WorkspaceCalibration
{
public:
    /*!
     * \brief Constructs a WorkspaceCalibration using the given
     *        intrinsic parameters
     *        and the specified calibration plate.
     *
     * \param[in] intrinsicParameters Holds the intrinsic camera parameters,
     *                                e.g. estimated using `CameraCalibration::Process()`.
     * \param[in] calibrationPlate    Holds the world coordinates of the reference points.
     *
     * \since ids_peak_icv 1.1
     */
    WorkspaceCalibration(const IntrinsicParameters& intrinsicParameters, CalibrationPlate calibrationPlate);

    /*!
     * \brief Calculates the camera's extrinsic parameters
     *        from a single image of a calibration plate.
     *
     * The method estimates
     * the camera's position and orientation
     * relative to the workspace coordinate system
     * and calculates the mean reprojection error
     * as a measure of calibration quality.
     *
     * \note Processes the entire image, ignoring any specified image region.
     *
     * \param[in] image An image showing a single calibration plate.
     *
     * \return The calibration result,
     *         including the extrinsic parameters
     *         and the mean reprojection error.
     *
     * \throws NotSupportedException   If the calibration plate pattern
     *                                 or image format is unsupported.
     * \throws MismatchException       If the image size differs from that
     *                                 specified in the intrinsic parameters
     * \throws TargetNotFoundException If the calibration plate markers are not found in the image.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD CalibrationResult Process(const Image& image) const;

private:
    IntrinsicParameters m_intrinsicParameters;
    CalibrationPlate m_calibrationPlate;
};

inline WorkspaceCalibration::WorkspaceCalibration(const IntrinsicParameters& intrinsicParameters, CalibrationPlate calibrationPlate)
    : m_intrinsicParameters{ intrinsicParameters }
    , m_calibrationPlate{ std::move(calibrationPlate) }
{}

inline CalibrationResult WorkspaceCalibration::Process(const Image& image) const
{
    CalibrationResult calibrationResult = peak::common::detail::BackendAccessor<CalibrationResult>::CreateInstance();
    const auto intrinsicParametersC = peak::common::detail::BackendAccessor<IntrinsicParameters>::CreateCType(m_intrinsicParameters);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_WorkspaceCalibration_Process(
            peak::common::detail::BackendAccessor<CalibrationPlate>::BackendHandle(m_calibrationPlate), intrinsicParametersC,
            sizeof(peak_icv_intrinsic_parameters), peak::common::detail::BackendAccessor<Image>::BackendHandle(image),
            peak::common::detail::BackendAccessor<CalibrationResult>::BackendHandleAddress(calibrationResult));
    });
    return calibrationResult;
}

} /* namespace icv */
} /* namespace peak */
