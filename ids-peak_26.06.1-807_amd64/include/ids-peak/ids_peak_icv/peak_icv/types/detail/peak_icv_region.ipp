/*!
 * \file    peak_icv_region.ipp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-03-19
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/types/peak_icv_image.hpp>

namespace peak
{
namespace icv
{
inline detail::handle_of_t<Region> Region::GetHandle() const
{
    return m_regionHandle;
}

inline detail::handle_of_t<Region>* Region::GetHandleAddress()
{
    return &m_regionHandle;
}

inline Region::Region()
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Create(&m_regionHandle);
    });
}

inline Region::Region(const std::vector<peak::common::Point>& points)
{
    std::vector<peak_common_point> cPoints(points.size());
    std::transform(points.begin(), points.end(), cPoints.begin(), [](const auto& cppPoint) -> peak_common_point {
        return { cppPoint.GetX(), cppPoint.GetY() };
    });
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_CreateFromPoints(&m_regionHandle, cPoints.data(), cPoints.size());
    });
}

inline Region::Region(const peak::common::Rectangle& rect)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_CreateFromRectangle(
            &m_regionHandle, peak::common::detail::BackendAccessor<peak::common::Rectangle>::CreateCType(rect));
    });
}

inline Region::Region(peak_icv_region_handle regionHandle) noexcept
    : m_regionHandle{ regionHandle }
{}

inline Region::Region(const Region& other)
{
    if (m_regionHandle != other.m_regionHandle)
    {
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_IncreaseUseCount(other.m_regionHandle);
        });
        m_regionHandle = other.m_regionHandle;
    }
}

inline Region::Region(Region&& other) noexcept
{
    if (m_regionHandle != other.m_regionHandle)
    {
        m_regionHandle = other.m_regionHandle;
        other.m_regionHandle = nullptr;
    }
}

inline Region::~Region()
{
    if (m_regionHandle)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Destroy(m_regionHandle);
    }
}

inline Region& Region::operator=(const Region& other)
{
    if (m_regionHandle != other.m_regionHandle)
    {
        if (m_regionHandle)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Destroy(m_regionHandle);
            });
        }

        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_IncreaseUseCount(other.m_regionHandle);
        });
        m_regionHandle = other.m_regionHandle;
    }

    return *this;
}

inline Region& Region::operator=(Region&& other) noexcept
{
    if (m_regionHandle != other.m_regionHandle)
    {
        if (m_regionHandle)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Destroy(m_regionHandle);
            });
        }

        m_regionHandle = other.m_regionHandle;
        other.m_regionHandle = nullptr;
    }

    return *this;
}

inline std::vector<peak::common::Point> Region::GetPoints() const
{
    size_t numPoints = 0;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_GetPoints_GetCount(m_regionHandle, &numPoints);
    });

    if (numPoints == 0)
    {
        return {};
    }

    std::vector<peak_common_point> points(numPoints);
    std::vector<peak::common::Point> cppPoints{};
    cppPoints.reserve(numPoints);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_GetPoints(m_regionHandle, points.data(), numPoints);
    });

    std::transform(points.begin(), points.end(), std::back_inserter(cppPoints), [](const auto& cPoint) {
        return peak::common::detail::BackendAccessor<peak::common::Point>::CreateInstance(cPoint);
    });

    return cppPoints;
}

inline std::vector<Region> Region::GetConnectedComponents() const
{
    size_t numConnectedComponents = 0;

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_GetConnectedComponents_GetCount(m_regionHandle, &numConnectedComponents);
    });

    if (numConnectedComponents == 0)
    {
        return {};
    }

    std::vector<peak_icv_region_handle> regionHandles(numConnectedComponents);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Array_Create(regionHandles.data(), numConnectedComponents);
    });

    try
    {
        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_GetConnectedComponents(
                m_regionHandle, regionHandles.data(), numConnectedComponents);
        });

        return peak::common::detail::BackendAccessor<Region>::CreateInstances(regionHandles);
    }
    catch (const std::exception&)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Array_Destroy(regionHandles.data(), numConnectedComponents);
        throw;
    }
}

inline size_t Region::GetArea() const
{
    size_t area = 0;

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_GetArea(m_regionHandle, &area);
    });

    return area;
}

inline peak::common::PointF Region::GetCenterOfGravity() const
{
    peak_common_point_f centerOfGravity{};

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_GetCenterOfGravity(m_regionHandle, &centerOfGravity);
    });

    return peak::common::detail::BackendAccessor<peak::common::PointF>::CreateInstance(centerOfGravity);
}

inline bool Region::operator==(const Region& rhs) const
{
    if (m_regionHandle == rhs.m_regionHandle)
    {
        return true;
    }

    bool is_equal = false;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Compare(m_regionHandle, rhs.m_regionHandle, &is_equal);
    });

    return is_equal;
}

inline bool Region::operator!=(const Region& rhs) const
{
    return !(*this == rhs);
}

inline void Region::Draw(Image& image, const detail::DrawingOptions& options) const
{
    const auto imageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(image);
    const auto optionsC = peak::common::detail::BackendAccessor<detail::DrawingOptions>::CreateCType(options);
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Draw(imageHandle, m_regionHandle, optionsC);
    });
}

inline Region Region::Intersection(const Region& other) const
{
    Region outputRegion;
    detail::ExecuteAndMapReturnCodes([&] {
        const auto otherHandle = peak::common::detail::BackendAccessor<Region>::BackendHandle(other);
        const auto outputRegionHandleAddress = peak::common::detail::BackendAccessor<Region>::BackendHandleAddress(outputRegion);
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Intersection(m_regionHandle, otherHandle, outputRegionHandleAddress);
    });
    return outputRegion;
}

inline Region Region::Difference(const Region& other) const
{
    Region outputRegion;
    detail::ExecuteAndMapReturnCodes([&] {
        const auto otherHandle = peak::common::detail::BackendAccessor<Region>::BackendHandle(other);
        const auto outputRegionHandleAddress = peak::common::detail::BackendAccessor<Region>::BackendHandleAddress(outputRegion);
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Difference(m_regionHandle, otherHandle, outputRegionHandleAddress);
    });
    return outputRegion;
}

inline Region Region::Union(const Region& other) const
{
    Region outputRegion;
    detail::ExecuteAndMapReturnCodes([&] {
        const auto otherHandle = peak::common::detail::BackendAccessor<Region>::BackendHandle(other);
        const auto outputRegionHandleAddress = peak::common::detail::BackendAccessor<Region>::BackendHandleAddress(outputRegion);
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Union(m_regionHandle, otherHandle, outputRegionHandleAddress);
    });
    return outputRegion;
}

inline Region Region::Dilation(const Region& structuringElement) const
{
    Region outputRegion;
    detail::ExecuteAndMapReturnCodes([&] {
        const auto seHandle = peak::common::detail::BackendAccessor<Region>::BackendHandle(structuringElement);
        const auto outputRegionHandleAddress = peak::common::detail::BackendAccessor<Region>::BackendHandleAddress(outputRegion);
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Dilation(m_regionHandle, seHandle, outputRegionHandleAddress);
    });
    return outputRegion;
}

inline Region Region::Erosion(const Region& structuringElement) const
{
    Region outputRegion;
    detail::ExecuteAndMapReturnCodes([&] {
        const auto seHandle = peak::common::detail::BackendAccessor<Region>::BackendHandle(structuringElement);
        const auto outputRegionHandleAddress = peak::common::detail::BackendAccessor<Region>::BackendHandleAddress(outputRegion);
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Erosion(m_regionHandle, seHandle, outputRegionHandleAddress);
    });
    return outputRegion;
}

inline Region Region::Scale(
    const peak::common::Size& inputSize, const peak::common::Size& outputSize, const Interpolation& interpolation) const
{
    Region outputRegion;
    detail::ExecuteAndMapReturnCodes([&] {
        const auto outputRegionHandleAddress = peak::common::detail::BackendAccessor<Region>::BackendHandleAddress(outputRegion);
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Region_Scale(m_regionHandle, { inputSize.GetWidth(), inputSize.GetHeight() },
            { outputSize.GetWidth(), outputSize.GetHeight() }, static_cast<peak_icv_interpolation>(interpolation),
            outputRegionHandleAddress);
    });
    return outputRegion;
}

} /* namespace icv */
} /* namespace peak */
