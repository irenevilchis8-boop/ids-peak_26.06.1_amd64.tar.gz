/*!
 * \file    peak_icv_camera_calibration.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_plate.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_camera_calibration.h>
#include <algorithm>
#include <utility>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Camera calibration representation
 *        holding the logic to compute intrinsic and extrinsic parameters.
 *
 * This class represents the camera calibration process.
 * It requires a CalibrationPlate instance
 * that provides the world coordinates of the reference points
 * on the physical calibration plate.
 * These points are needed to calculate the camera parameters.
 *
 * The main operation is the `CameraCalibration::Process()` method,
 * which calculates intrinsic and extrinsic parameters from input images.
 *
 * \since ids_peak_icv 1.1
 */
class CameraCalibration
{
public:
    /*!
     * \brief Constructs a CameraCalibration with the given calibration plate.
     *
     * \param[in] calibrationPlate Holds the world coordinates of the reference points.
     *
     * \since ids_peak_icv 1.1
     */
    explicit CameraCalibration(CalibrationPlate calibrationPlate);

    /*!
     * \brief Calculates intrinsic and extrinsic parameters.
     *
     * Processes several images
     * showing the calibration plate in different poses
     * to accurately calculate camera calibration parameters.
     *
     * The calibration process involves
     * detecting the reference points in the images
     * and matching them to their known world coordinates
     * provided by the calibration plate.
     * Using these correspondences, the method estimates the camera’s
     * intrinsic parameters (such as focal length and distortion)
     * and extrinsic parameters (position and orientation).
     *
     * \note This operation disregards any specified image regions.
     *       It processes the entire image.
     *
     * \param[in] images A vector of images of a calibration plate in different poses.
     *
     * \return The calibration results, including intrinsic and extrinsic parameters.
     *
     * \throws NotSupportedException   If the pattern of the calibration plate is not supported
     *                                 or the image has an unsupported format.
     * \throws MismatchException       If the images do not all have the same size.
     * \throws TargetNotFoundException If the marker points were not found on the specified image.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD CalibrationResult Process(const std::vector<Image>& images) const;

private:
    CalibrationPlate m_calibrationPlate;
};

inline CameraCalibration::CameraCalibration(CalibrationPlate calibrationPlate)
    : m_calibrationPlate{ std::move(calibrationPlate) }
{}

inline CalibrationResult CameraCalibration::Process(const std::vector<Image>& images) const
{
    if (images.size() == 0)
    {
        throw NotPossibleException("Number of input images has to be greater than 0.");
    }

    auto result = peak::common::detail::BackendAccessor<CalibrationResult>::CreateInstance();

    std::vector<peak_icv_image_handle> imageHandles;
    imageHandles.reserve(images.size());
    std::transform(images.begin(), images.end(), std::back_inserter(imageHandles), [](const auto& image) {
        return peak::common::detail::BackendAccessor<Image>::BackendHandle(image);
    });
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Process(
            peak::common::detail::BackendAccessor<CalibrationPlate>::BackendHandle(m_calibrationPlate), imageHandles.data(),
            imageHandles.size(), peak::common::detail::BackendAccessor<CalibrationResult>::BackendHandleAddress(result));
    });

    return result;
}

} /* namespace icv */
} /* namespace peak */
