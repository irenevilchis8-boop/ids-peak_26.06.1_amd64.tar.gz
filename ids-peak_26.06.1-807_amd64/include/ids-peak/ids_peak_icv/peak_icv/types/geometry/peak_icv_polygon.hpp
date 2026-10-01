/*!
 * \file    peak_icv_polygon.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-01-09
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_point.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv_c/types/peak_icv_polygon.h>
#include <vector>

namespace peak
{
namespace icv
{
namespace detail
{
/*!
 * \brief
 * \ingroup ids_peak_icv_cpp_geometry
 *
 * A polygon is a two-dimensional geometric shape that is made up of a finite number of straight line segments connected end-to-end to form
 * an open or closed figure. A polygon is represented by the points where the line segments meet.
 *
 * \since ids_peak_icv 1.1
 */
template <typename PointType>
class Polygon
    : private detail::IBackendAccessible<Polygon<PointType>>
    , private detail::IBackendExchangeable<Polygon<PointType>>
{
public:
    /*!
     * \brief Creates an empty polygon
     *
     * \since ids_peak_icv 1.1
     */
    Polygon();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    ~Polygon() override;

    /*!
     * \brief Creates a polygon from a set of points
     *
     * \param points Vector of points representing the polygon.
     *
     * \since ids_peak_icv 1.1
     */
    explicit Polygon(const std::vector<peak::common::detail::PointT<PointType>>& points);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    Polygon(const Polygon& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    Polygon(Polygon&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    Polygon& operator=(const Polygon& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    Polygon& operator=(Polygon&& other) noexcept;

    /*!
     * \brief Provides the points from a polygon.
     *
     * \return Returns the points from a polygon.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD std::vector<peak::common::detail::PointT<PointType>> GetPoints() const;

    /*!
     * \brief Checks if a polygon is closed. A closed polygon contains the same point as first and last point. Returns True if closed, False if open.
     *
     * \return Returns True if closed, False if open.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD bool IsClosed() const;

private:
    friend peak::common::detail::BackendAccessor<Polygon>;

    using PointTypeC = peak::common::detail::c_type_of_t<peak::common::detail::PointT<PointType>>;

    explicit Polygon(peak_icv_polygon_handle handle);
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<Polygon> GetHandle() const override;
    PEAK_COMMON_NO_DISCARD detail::handle_of_t<Polygon>* GetHandleAddress() override;

    peak_icv_polygon_handle m_handle{};
};

template <typename PointType>
inline Polygon<PointType>::Polygon()
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_Create(&m_handle);
    });
}

template <typename PointType>
inline Polygon<PointType>::Polygon(const std::vector<peak::common::detail::PointT<PointType>>& points)
{
    std::vector<PointTypeC> cPoints;
    cPoints.reserve(points.size());
    std::transform(points.begin(), points.end(), std::back_inserter(cPoints), [](const auto& cppPoint) {
        return peak::common::detail::BackendAccessor<peak::common::detail::PointT<PointType>>::CreateCType(cppPoint);
    });
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_CreateFromPoints(
            &m_handle, cPoints.data(), cPoints.size(), point_enum_of_<PointTypeC>::value);
    });
}

template <typename PointType>
inline Polygon<PointType>::Polygon(peak_icv_polygon_handle polygonHandle)
    : m_handle{ polygonHandle }
{}

template <typename PointType>
inline Polygon<PointType>::Polygon(const Polygon& other)
{
    if (m_handle != other.m_handle)
    {
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_IncreaseUseCount(other.m_handle);
        });
        m_handle = other.m_handle;
    }
}

template <typename PointType>
inline Polygon<PointType>::Polygon(Polygon&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        m_handle = other.m_handle;
        other.m_handle = nullptr;
    }
}

template <typename PointType>
inline Polygon<PointType>::~Polygon()
{
    static_cast<void>(PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_Destroy(m_handle));
}

template <typename PointType>
inline Polygon<PointType>& Polygon<PointType>::operator=(const Polygon& other)
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_Destroy(m_handle);
            });
        }

        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_IncreaseUseCount(other.m_handle);
        });
        m_handle = other.m_handle;
    }
    return *this;
}

template <typename PointType>
inline Polygon<PointType>& Polygon<PointType>::operator=(Polygon&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_Destroy(m_handle);
            });
        }

        m_handle = other.m_handle;
        other.m_handle = nullptr;
    }
    return *this;
}

template <typename PointType>
inline std::vector<peak::common::detail::PointT<PointType>> Polygon<PointType>::GetPoints() const
{
    size_t numPoints = 0;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_GetPoints_GetCount(m_handle, &numPoints);
    });
    if (numPoints == 0)
    {
        return {};
    }

    std::vector<PointTypeC> cPoints(numPoints);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_GetPoints(m_handle, cPoints.data(), numPoints * sizeof(PointTypeC));
    });

    std::vector<peak::common::detail::PointT<PointType>> cppPoints{};
    cppPoints.reserve(numPoints);
    std::transform(cPoints.begin(), cPoints.end(), std::back_inserter(cppPoints), [](const auto& cPoint) {
        return peak::common::detail::BackendAccessor<peak::common::detail::PointT<PointType>>::CreateInstance(cPoint);
    });

    return cppPoints;
}

template <typename PointType>
inline bool Polygon<PointType>::IsClosed() const
{
    bool isClosed = false;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Polygon_IsClosed(m_handle, &isClosed);
    });

    return isClosed;
}

template <typename PointType>
inline detail::handle_of_t<Polygon<PointType>> Polygon<PointType>::GetHandle() const
{
    return m_handle;
}

template <typename PointType>
inline detail::handle_of_t<Polygon<PointType>>* Polygon<PointType>::GetHandleAddress()
{
    return &m_handle;
}

} // namespace detail

/*!
 * \ingroup ids_peak_icv_cpp_types
 * \brief Polygon of type float.
 * \since ids_peak_icv 1.1
 */
using PolygonF = detail::Polygon<float>;
} /* namespace icv */
} /* namespace peak */
