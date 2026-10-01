/*!
 * \file    peak_icv_point_cloud.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-03-19
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyz.hpp>
#include <peak_icv/types/peak_icv_array_2d.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv/utils/peak_icv_type_traits.hpp>
#include <peak_icv_c/types/peak_icv_point_cloud.h>
#include <algorithm>
#include <cstring>
#include <memory>
#include <vector>

namespace peak
{
namespace icv
{
namespace detail
{

/*!
 * \defgroup ids_peak_icv_cpp_point_cloud Point cloud
 * \ingroup ids_peak_icv_cpp_types
 *
 * \brief A point cloud is a set of data points defined in a three-dimensional (3D) coordinate system.
 *
 * Each point is represented by its X, Y, and Z coordinates,
 * specifying its exact position in 3D space. Optionally it can contain intensity metadata.
 * Point clouds are often generated from depth maps,
 * such as those obtained from a time-of-flight camera.
 * They serve as a detailed digital representation of the shape and size of physical objects,
 * enabling precise measurements and analysis.
 */

/*!
 * \ingroup ids_peak_icv_cpp_point_cloud
 *
 * \brief Represents a generic point cloud interface for spatial data types.
 *
 * \tparam PointCloudType Type of the concrete point cloud implementation.
 * \tparam InnerPointType Type of the points in the point cloud.
 *
 * \since ids_peak_icv 1.1
 */
template <typename PointCloudType, typename InnerPointType>
class PointCloud
    : private detail::IBackendAccessible<PointCloud<PointCloudType, InnerPointType>>
    , private detail::IBackendExchangeable<PointCloud<PointCloudType, InnerPointType>>
{
    static_assert(
        std::is_base_of<PointXYZ, InnerPointType>::value, "The given PointType is invalid. Please use a class which derives from Point3d");

public:
    using PointType = InnerPointType;

    ~PointCloud() override;

    PointCloud(const PointCloud& other);

    PointCloud(PointCloud&& other) noexcept;

    PointCloud& operator=(const PointCloud& other);

    PointCloud& operator=(PointCloud&& other) noexcept;

    bool operator==(const PointCloud& rhs) const;

    bool operator!=(const PointCloud& rhs) const;

    /*!
     * \return Reference to the vector containing the points.
     */
    const std::vector<PointType>& GetPoints() const;

    /*!
     * \brief Applies the specified transformation matrix to the point cloud.
     *
     * \param matrix Transformation matrix to apply.
     *
     * \return Transformed point cloud.
     */
    PEAK_COMMON_NO_DISCARD PointCloudType Transform(const TransformationMatrix3D& matrix) const;

    /*!
     * \brief Transforms the point cloud to workspace coordinates
     *        using the specified extrinsic parameters.
     *
     * The transformation uses the inverse of the extrinsic matrix
     * to convert from camera to workspace coordinate system.
     *
     * \param extrinsicParameters Extrinsic parameters from the workspace calibration.
     *
     * \return Transformed point cloud.
     */
    PEAK_COMMON_NO_DISCARD PointCloudType TransformToWorkspace(const ExtrinsicParameters& extrinsicParameters) const;

    /*!
     * \return Iterator to the first point.
     */
    typename std::vector<PointType>::const_iterator cbegin() const;

    /*!
     * \return Iterator to the end of the points (the point after the last point).
     */
    typename std::vector<PointType>::const_iterator cend() const;

protected:
    PointCloud();
    explicit PointCloud(peak_icv_point_cloud_handle handle);

    PEAK_COMMON_NO_DISCARD detail::handle_of_t<PointCloud> GetHandle() const override;

    /*!
     * \brief Handle with care as the class has a cache,
     *        which must be reset in some cases,
     *        when changing the underlying handle.
     */
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<PointCloud>* GetHandleAddress() override;

private:
    using PointTypeC = peak::common::detail::c_type_of_t<PointType>;

    peak_icv_point_cloud_handle m_pointCloudHandle{};
    mutable std::unique_ptr<std::vector<PointType>> m_points{};

    peak_icv_point_cloud_handle CreateEmptyPointCloud();
};

template <typename PointCloudType, typename InnerPointType>
PointCloud<PointCloudType, InnerPointType>::~PointCloud()
{
    if (m_pointCloudHandle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_Destroy(m_pointCloudHandle);
    }
}

template <typename PointCloudType, typename InnerPointType>
PointCloud<PointCloudType, InnerPointType>::PointCloud(peak_icv_point_cloud_handle handle)
    : m_pointCloudHandle{ handle }
{}

template <typename PointCloudType, typename InnerPointType>
PointCloud<PointCloudType, InnerPointType>::PointCloud(const PointCloud& other)
{
    if (m_pointCloudHandle != other.m_pointCloudHandle)
    {
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_IncreaseUseCount(other.m_pointCloudHandle);
        });
        m_pointCloudHandle = other.m_pointCloudHandle;
    }
}

template <typename PointCloudType, typename InnerPointType>
PointCloud<PointCloudType, InnerPointType>::PointCloud(PointCloud&& other) noexcept
{
    if (m_pointCloudHandle != other.m_pointCloudHandle)
    {
        m_pointCloudHandle = other.m_pointCloudHandle;
        other.m_pointCloudHandle = nullptr;
    }
}

template <typename PointCloudType, typename InnerPointType>
PointCloud<PointCloudType, InnerPointType>& PointCloud<PointCloudType, InnerPointType>::operator=(const PointCloud& other)
{
    if (m_pointCloudHandle != other.m_pointCloudHandle)
    {
        if (m_pointCloudHandle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_Destroy(m_pointCloudHandle);
            });
        }
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_IncreaseUseCount(other.m_pointCloudHandle);
        });
        m_pointCloudHandle = other.m_pointCloudHandle;
        m_points = std::make_unique<std::vector<InnerPointType>>(other.GetPoints());
    }

    return *this;
}

template <typename PointCloudType, typename InnerPointType>
PointCloud<PointCloudType, InnerPointType>& PointCloud<PointCloudType, InnerPointType>::operator=(PointCloud&& other) noexcept
{
    if (m_pointCloudHandle != other.m_pointCloudHandle)
    {
        if (m_pointCloudHandle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_Destroy(m_pointCloudHandle);
            });
        }

        m_pointCloudHandle = other.m_pointCloudHandle;
        m_points = std::make_unique<std::vector<InnerPointType>>(other.GetPoints());
        other.m_pointCloudHandle = nullptr;
        other.m_points = nullptr;
    }

    return *this;
}

template <typename PointCloudType, typename InnerPointType>
bool PointCloud<PointCloudType, InnerPointType>::operator==(const PointCloud& rhs) const
{
    if (m_pointCloudHandle == rhs.m_pointCloudHandle)
    {
        return true;
    }

    auto pointLhs = this->GetPoints();
    auto pointRhs = rhs.GetPoints();

    if (pointLhs.size() != pointRhs.size())
    {
        return false;
    }

    return std::is_permutation(pointLhs.begin(), pointLhs.end(), pointRhs.begin());
}

template <typename PointCloudType, typename InnerPointType>
bool PointCloud<PointCloudType, InnerPointType>::operator!=(const PointCloud& rhs) const
{
    return !(*this == rhs);
}

template <typename PointCloudType, typename InnerPointType>
const std::vector<InnerPointType>& PointCloud<PointCloudType, InnerPointType>::GetPoints() const
{
    if (m_points)
    {
        return *m_points;
    }

    size_t numPoints = 0;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_GetPoints_GetCount(m_pointCloudHandle, &numPoints);
    });

    if (numPoints == 0)
    {
        m_points = std::make_unique<std::vector<PointType>>(0);
        return *m_points;
    }

    std::vector<PointTypeC> points(numPoints);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_GetPoints(m_pointCloudHandle, points.data(), sizeof(PointTypeC) * numPoints);
    });

    m_points = std::make_unique<std::vector<PointType>>(numPoints);
    std::transform(points.begin(), points.end(), m_points->begin(), [](const auto& point) {
        return peak::common::detail::BackendAccessor<PointType>::CreateInstance(point);
    });

    return *m_points;
}

template <typename PointCloudType, typename InnerPointType>
PointCloudType PointCloud<PointCloudType, InnerPointType>::Transform(const TransformationMatrix3D& matrix) const
{
    peak_icv_transformation_matrix_3d cMatrix{};
    std::memcpy(&cMatrix, matrix.GetData(), sizeof(cMatrix));

    PointCloudType outputPointCloud{};
    auto outputHandle = peak::common::detail::BackendAccessor<PointCloudType>::BackendHandleAddress(outputPointCloud);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_Transform(this->GetHandle(), cMatrix, outputHandle);
    });
    return outputPointCloud;
}

template <typename PointCloudType, typename InnerPointType>
PointCloudType PointCloud<PointCloudType, InnerPointType>::TransformToWorkspace(const ExtrinsicParameters& extrinsicParameters) const
{
    const auto extrinsicParametersC = peak::common::detail::BackendAccessor<ExtrinsicParameters>::CreateCType(extrinsicParameters);

    PointCloudType outputPointCloud{};
    auto outputHandle = peak::common::detail::BackendAccessor<PointCloudType>::BackendHandleAddress(outputPointCloud);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_TransformToWorkspace(
            this->GetHandle(), extrinsicParametersC, sizeof(peak_icv_extrinsic_parameters), outputHandle);
    });
    return outputPointCloud;
}

template <typename PointCloudType, typename InnerPointType>
typename std::vector<InnerPointType>::const_iterator PointCloud<PointCloudType, InnerPointType>::cbegin() const
{
    return GetPoints().cbegin();
}

template <typename PointCloudType, typename InnerPointType>
typename std::vector<InnerPointType>::const_iterator PointCloud<PointCloudType, InnerPointType>::cend() const
{
    return GetPoints().cend();
}

template <typename PointCloudType, typename InnerPointType>
PointCloud<PointCloudType, InnerPointType>::PointCloud()
    : m_pointCloudHandle{ CreateEmptyPointCloud() }
{}

template <typename PointCloudType, typename InnerPointType>
detail::handle_of_t<PointCloud<PointCloudType, InnerPointType>> PointCloud<PointCloudType, InnerPointType>::GetHandle() const
{
    return m_pointCloudHandle;
}

template <typename PointCloudType, typename InnerPointType>
detail::handle_of_t<PointCloud<PointCloudType, InnerPointType>>* PointCloud<PointCloudType, InnerPointType>::GetHandleAddress()
{
    return &m_pointCloudHandle;
}

template <typename PointCloudType, typename InnerPointType>
peak_icv_point_cloud_handle PointCloud<PointCloudType, InnerPointType>::CreateEmptyPointCloud()
{
    peak_icv_point_cloud_handle handle{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_PointCloud_Create(&handle);
    });
    return handle;
}

} // namespace detail
} /* namespace icv */
} /* namespace peak */
