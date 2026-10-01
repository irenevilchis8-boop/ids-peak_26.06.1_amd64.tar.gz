/*!
 * \file    peak_icv_reprojection_error.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-09-04
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_vector.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_intrinsic_parameters.hpp>
#include <peak_icv/utils/peak_icv_printable.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_view.h>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Represents the reprojection error for a marker point in the image.
 *
 * Holds the reprojection error for a specific calibration plate marker,
 * including its
 * position in the image,
 * the direction of the error,
 * and its magnitude in pixels.
 * This quantifies the deviation of the reprojected marker from its observed image location.
 *
 * Such information helps evaluate the calibration accuracy at that specific point.
 *
 * \since ids_peak_icv 1.1
 */
class ReprojectionError : public detail::IPrintable<ReprojectionError>
{
public:
    /*!
     * \since ids_peak_icv 1.1
     */
    ~ReprojectionError() override = default;

    /*!
     * \since ids_peak_icv 1.1
     */
    ReprojectionError(const ReprojectionError& other) = default;

    /*!
     * \since ids_peak_icv 1.1
     */
    ReprojectionError(ReprojectionError&& other) noexcept = default;

    /*!
     * \since ids_peak_icv 1.1
     */
    ReprojectionError& operator=(const ReprojectionError& other) = default;

    /*!
     * \since ids_peak_icv 1.1
     */
    ReprojectionError& operator=(ReprojectionError&& other) noexcept = default;

    /*!
     * \return The detected position of the calibration marker in image coordinates.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::PointF GetPosition() const;

    /*!
     * \return The direction of the reprojection error.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::common::VectorF GetDirection() const;

    /*!
     * \return The magnitude of the reprojection error, measured in pixels.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD double GetLength() const;

protected:
    void Print(detail::CommaSeperatedStream& stream) const override;

private:
    friend class CalibrationView;
    friend class peak::common::detail::BackendAccessor<ReprojectionError>;

    ReprojectionError(const peak_icv_reprojection_error& reprojectionError); // NOLINT

    peak_icv_reprojection_error m_reprojectionError{};
};

inline ReprojectionError::ReprojectionError(const peak_icv_reprojection_error& reprojectionError)
    : m_reprojectionError{ reprojectionError }
{}

inline peak::common::PointF ReprojectionError::GetPosition() const
{
    return peak::common::detail::BackendAccessor<peak::common::PointF>::CreateInstance(m_reprojectionError.position);
}

inline peak::common::VectorF ReprojectionError::GetDirection() const
{
    return peak::common::detail::BackendAccessor<peak::common::PointF>::CreateInstance(m_reprojectionError.direction);
}

inline double ReprojectionError::GetLength() const
{
    return m_reprojectionError.length;
}

inline void ReprojectionError::Print(detail::CommaSeperatedStream& stream) const
{
    stream << GetPosition() << GetDirection() << GetLength();
}

} /* namespace icv */
} /* namespace peak */
