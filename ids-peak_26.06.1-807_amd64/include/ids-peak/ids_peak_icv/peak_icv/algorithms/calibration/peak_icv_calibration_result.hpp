/*!
 * \file    peak_icv_calibration_result.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-08-29
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_parameters.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_view.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_intrinsic_parameters.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv/utils/peak_icv_type_traits.hpp>
#include <peak_icv_c/algorithms/calibration/peak_icv_camera_calibration.h>

#include <tuple>

namespace peak
{
namespace icv
{
/*!
 * \ingroup ids_peak_icv_cpp_calibration
 *
 * \brief Holds the results of a camera calibration.
 *
 * The CalibrationResult class stores
 * the intrinsic and extrinsic parameters,
 * the mean reprojection error,
 * and a collection of calibration views,
 * each representing marker positions
 * and corresponding reprojection errors in the image.
 *
 * These results are typically produced by the `CameraCalibration::Process()` method.
 *
 * \since ids_peak_icv 1.1
 */
class CalibrationResult
    : private detail::IBackendAccessible<CalibrationResult>
    , private detail::IBackendExchangeable<CalibrationResult>
{
public:
    /*!
     * \brief Constructs a CalibrationResult instance by loading data from a JSON file.
     *
     * This constructor initializes the calibration result by parsing the given file,
     * which contains intrinsic parameters, the mean reprojection error, and the calibration views.
     *
     * \param[in] filePath An existing file path to a calibration result JSON file.
     *
     * \throws IOException        If the given \p filePath does not exist,
     *                            or the permissions are not sufficient to read it.
     * \throws CorruptedException If the file cannot be read.
     *
     * \since ids_peak_icv 1.1
     */
    explicit CalibrationResult(const std::string& filePath);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    ~CalibrationResult() override;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationResult(const CalibrationResult& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationResult(CalibrationResult&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationResult& operator=(const CalibrationResult& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    CalibrationResult& operator=(CalibrationResult&& other) noexcept;

    /*!
     * \brief Retrieves the mean reprojection error from the calibration result.
     *
     * The mean reprojection error is the root mean square
     * of distances between the marker points detected from the calibration images
     * and the projected world points,
     * measured in pixels.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD double GetMeanReprojectionError() const;

    /*!
     * \brief Returns a vector of `CalibrationView` objects.
     *
     * The order of the returned CalibrationViews corresponds exactly to the order of images
     * passed to `CameraCalibration::Process()`.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD std::vector<CalibrationView> GetViews() const;

    /*!
     * \brief Extracts the calibration parameters from a calibration result.
     *
     * This function extracts the calibration parameters required for image operations
     * such as point cloud generation, image undistortion, and other calibration-dependent tasks.
     * The extracted parameters include intrinsic parameters and,
     * depending on the number of calibration views, extrinsic parameters.
     *
     * - Intrinsic parameters are always extracted from the calibration result.
     * - If the calibration result contains exactly one calibration view,
     *   the extrinsic parameters are taken from that view.
     * - If multiple calibration views are present (e.g., from a full camera calibration),
     *   the extrinsic parameters are set to the identity matrix.
     *
     * To use extrinsic parameters from a specific calibration view rather than the identity matrix,
     * retrieve the desired view using `CalibrationResult::GetViews()`
     * and incorporate its parameters accordingly.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD CalibrationParameters GetCalibrationParameters() const;

    /*!
     * \brief Implicitly converts a CalibrationResult into calibration parameters.
     *
     * This operator calls `CalibrationResult::GetCalibrationParameters()` to extract the calibration parameters.
     *
     * \since ids_peak_icv 1.1
     */
    operator CalibrationParameters() const; // NOLINT

private:
    friend peak::common::detail::BackendAccessor<CalibrationResult>;

    CalibrationResult();
    explicit CalibrationResult(peak_icv_calibration_result_handle calibrationResultHandle);
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<CalibrationResult> GetHandle() const override;
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<CalibrationResult>* GetHandleAddress() override;

    peak_icv_calibration_result_handle m_calibrationResultHandle{};
};

inline CalibrationResult::CalibrationResult()
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_Create(&m_calibrationResultHandle);
    });
}

inline detail::handle_of_t<CalibrationResult> CalibrationResult::GetHandle() const
{
    return m_calibrationResultHandle;
}

inline detail::handle_of_t<CalibrationResult>* CalibrationResult::GetHandleAddress()
{
    return &m_calibrationResultHandle;
}

inline CalibrationResult::CalibrationResult(peak_icv_calibration_result_handle calibrationResultHandle)
    : m_calibrationResultHandle{ calibrationResultHandle }
{}

inline CalibrationResult::CalibrationResult(const CalibrationResult& other)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_IncreaseUseCount(other.m_calibrationResultHandle);
    });
    m_calibrationResultHandle = other.m_calibrationResultHandle;
}

inline CalibrationResult::CalibrationResult(CalibrationResult&& other) noexcept
{
    m_calibrationResultHandle = other.m_calibrationResultHandle;
    other.m_calibrationResultHandle = nullptr;
}

inline CalibrationResult& CalibrationResult::operator=(const CalibrationResult& other)
{
    if (m_calibrationResultHandle != other.m_calibrationResultHandle)
    {
        if (m_calibrationResultHandle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_Destroy(m_calibrationResultHandle);
            });
        }

        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_IncreaseUseCount(other.m_calibrationResultHandle);
        });
        m_calibrationResultHandle = other.m_calibrationResultHandle;
    }

    return *this;
}

inline CalibrationResult& CalibrationResult::operator=(CalibrationResult&& other) noexcept
{
    if (m_calibrationResultHandle != other.m_calibrationResultHandle)
    {
        if (m_calibrationResultHandle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_Destroy(m_calibrationResultHandle);
            });
        }

        m_calibrationResultHandle = other.m_calibrationResultHandle;
        other.m_calibrationResultHandle = nullptr;
    }

    return *this;
}

inline CalibrationResult::~CalibrationResult()
{
    if (m_calibrationResultHandle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_Destroy(m_calibrationResultHandle);
    }
}

inline CalibrationResult::CalibrationResult(const std::string& filePath)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_CreateFromFile(&m_calibrationResultHandle, filePath.c_str());
    });
}

inline double CalibrationResult::GetMeanReprojectionError() const
{
    double meanReprojectionError{};

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_GetMeanReprojectionError(
            m_calibrationResultHandle, &meanReprojectionError);
    });
    return meanReprojectionError;
}

inline std::vector<CalibrationView> CalibrationResult::GetViews() const
{
    size_t numViews{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_GetCalibrationViews_GetCount(m_calibrationResultHandle, &numViews);
    });

    if (numViews == 0)
    {
        return {};
    }

    std::vector<peak_icv_calibration_view_handle> viewHandles(numViews);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_Array_Create(viewHandles.data(), viewHandles.size());
    });

    try
    {
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_GetCalibrationViews(
                m_calibrationResultHandle, viewHandles.data(), viewHandles.size());
        });
        return peak::common::detail::BackendAccessor<CalibrationView>::CreateInstances(viewHandles);
    }
    catch (const std::exception&)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_View_Array_Destroy(viewHandles.data(), viewHandles.size());
        throw;
    }
}

inline CalibrationParameters CalibrationResult::GetCalibrationParameters() const
{
    peak_icv_calibration_parameters calibrationParameters{};

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Calibration_Result_ToParameters(
            m_calibrationResultHandle, &calibrationParameters, sizeof(peak_icv_calibration_parameters));
    });

    return CalibrationParameters{ calibrationParameters };
}

inline CalibrationResult::operator CalibrationParameters() const
{
    return GetCalibrationParameters();
}

} /* namespace icv */
} /* namespace peak */
