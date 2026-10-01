/*!
 * \file    peak_icv_calibration_view.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-08-21
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_extrinsic_parameters.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_reprojection_error.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/types/geometry/peak_icv_coordinate_system.hpp>
#include <peak_icv/types/geometry/peak_icv_polygon.hpp>
#include <peak_icv/types/peak_icv_array_2d.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_view.h>

#include <tuple>

namespace peak
{
namespace icv
{
/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Represents a single observation of a calibration plate in an image.
 *
 * A CalibrationView encapsulates the data and results
 * derived from a single image
 * in which a calibration plate has been successfully detected.
 * This includes the estimated camera pose (extrinsic parameters),
 * the reprojection errors,
 * the convex hull of detected markers,
 * and the 2D projection of the plate's 3D coordinate system into the image plane.
 *
 * Each instance corresponds to one image (or view) used during the calibration process
 * and provides detailed insight into how well the model fits that observation.
 *
 * \since ids_peak_icv 1.1
 */
class CalibrationView
    : private detail::IBackendAccessible<CalibrationView>
    , private detail::IBackendExchangeable<CalibrationView>
{
public:
    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    ~CalibrationView() override;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationView(const CalibrationView& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationView(CalibrationView&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationView& operator=(const CalibrationView& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationView& operator=(CalibrationView&& other) noexcept;

    /*!
     * \brief Provides the reprojection errors for every marker in the view.
     *
     * The reprojection errors are the distances (in pixels)
     * between the detected marker points in the calibration image
     * and the corresponding projected world points,
     * computed using the estimated camera parameters.
     *
     * \return A vector containing all reprojection errors from the calibration view.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD std::vector<ReprojectionError> GetReprojectionErrors() const;

    /*!
     * \brief Provides the extrinsic parameters for the view.
     *
     * The extrinsic parameters define the 3D transformation
     * from the calibration plate's coordinate system
     * into the camera's coordinate system.
     * This includes both rotation and translation.
     *
     * \return The extrinsic parameters of the calibration view.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD ExtrinsicParameters GetExtrinsicParameters() const;

    /*!
     * \brief Provides the convex hull of the found calibration plate in the view.
     *
     * The convex hull is the smallest convex polygon
     * that encloses all detected marker points
     * from the calibration plate in the image.
     *
     * \return The convex hull of the calibration plate, represented as a polygon.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD PolygonF GetConvexHull() const;

    /*!
     * \brief Provides the calibration plate coordinate system projected into the image.
     *
     * The coordinate system is projected using the estimated camera parameters.
     * It consists of an origin
     * and three vectors representing the X, Y, and Z axes.
     * These vectors describe the axes directions
     * projected from 3D to 2D.
     * Their lengths are twice the distance
     * between neighboring markers on the calibration plate.
     *
     * \return The projected coordinate system of the calibration plate.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD CoordinateSystem GetCoordinateSystem() const;


private:
    friend peak::common::detail::BackendAccessor<CalibrationView>;

    CalibrationView();
    explicit CalibrationView(peak_icv_calibration_view_handle calibrationViewHandle);
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<CalibrationView> GetHandle() const override;
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<CalibrationView>* GetHandleAddress() override;

    peak_icv_calibration_view_handle m_calibrationViewHandle{};
};

inline CalibrationView::CalibrationView()
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_Create(&m_calibrationViewHandle);
    });
}

inline CalibrationView::CalibrationView(peak_icv_calibration_view_handle calibrationViewHandle)
    : m_calibrationViewHandle(calibrationViewHandle)
{}

inline CalibrationView::~CalibrationView()
{
    if (m_calibrationViewHandle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_Destroy(m_calibrationViewHandle);
    }
}

inline CalibrationView::CalibrationView(const CalibrationView& other)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_IncreaseUseCount(other.m_calibrationViewHandle);
    });
    m_calibrationViewHandle = other.m_calibrationViewHandle;
}

inline CalibrationView::CalibrationView(CalibrationView&& other) noexcept
    : m_calibrationViewHandle(other.m_calibrationViewHandle)
{
    other.m_calibrationViewHandle = nullptr;
}

inline CalibrationView& CalibrationView::operator=(const CalibrationView& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (m_calibrationViewHandle != nullptr)
    {
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_Destroy(m_calibrationViewHandle);
        });
    }

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_IncreaseUseCount(other.m_calibrationViewHandle);
    });
    m_calibrationViewHandle = other.m_calibrationViewHandle;
    return *this;
}

inline CalibrationView& CalibrationView::operator=(CalibrationView&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    if (m_calibrationViewHandle != nullptr)
    {
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_Destroy(m_calibrationViewHandle);
        });
    }

    m_calibrationViewHandle = other.m_calibrationViewHandle;
    other.m_calibrationViewHandle = nullptr;
    return *this;
}

inline detail::handle_of_t<CalibrationView> CalibrationView::GetHandle() const
{
    return m_calibrationViewHandle;
}

inline detail::handle_of_t<CalibrationView>* CalibrationView::GetHandleAddress()
{
    return &m_calibrationViewHandle;
}

inline std::vector<ReprojectionError> CalibrationView::GetReprojectionErrors() const
{
    size_t reprojectionErrorsCount{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_GetReprojectionErrors_GetCount(
            m_calibrationViewHandle, &reprojectionErrorsCount);
    });

    if (reprojectionErrorsCount == 0)
    {
        return {};
    }

    std::vector<peak_icv_reprojection_error> cReprojectionErrors(reprojectionErrorsCount);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_GetReprojectionErrors(
            m_calibrationViewHandle, cReprojectionErrors.data(), reprojectionErrorsCount);
    });

    std::vector<ReprojectionError> reprojectionErrors;
    reprojectionErrors.reserve(reprojectionErrorsCount);

    std::transform(cReprojectionErrors.begin(), cReprojectionErrors.end(), std::back_inserter(reprojectionErrors),
        [&](const auto& reprojectionError) -> ReprojectionError {
            return reprojectionError;
        });

    return reprojectionErrors;
}

inline ExtrinsicParameters CalibrationView::GetExtrinsicParameters() const
{
    peak_icv_extrinsic_parameters extrinsicParameters{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_GetExtrinsicParameters(
            m_calibrationViewHandle, &extrinsicParameters, sizeof(extrinsicParameters));
    });
    return peak::common::detail::BackendAccessor<ExtrinsicParameters>::CreateInstance(extrinsicParameters);
}

inline PolygonF CalibrationView::GetConvexHull() const
{
    PolygonF polygonF{};
    auto* polygonHandle = peak::common::detail::BackendAccessor<PolygonF>::BackendHandle(polygonF);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_GetConvexHull(m_calibrationViewHandle, &polygonHandle);
    });

    return peak::common::detail::BackendAccessor<PolygonF>::CreateInstance(polygonHandle);
}

inline CoordinateSystem CalibrationView::GetCoordinateSystem() const
{
    peak_icv_coordinate_system coordinateSystem{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_GetCoordinateSystem(m_calibrationViewHandle, &coordinateSystem);
    });

    return peak::common::detail::BackendAccessor<CoordinateSystem>::CreateInstance(coordinateSystem);
}

} /* namespace icv */
} /* namespace peak */
