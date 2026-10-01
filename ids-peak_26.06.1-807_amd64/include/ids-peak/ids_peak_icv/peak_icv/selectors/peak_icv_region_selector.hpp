/*!
 * \file    peak_icv_region_selector.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_rectangle.hpp>
#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/selectors/detail/peak_icv__region_selector_c_helper.hpp>
#include <peak_icv/types/peak_icv_region.hpp>
#include <peak_icv_c/selectors/peak_icv_region_selector.h>

#include <functional>

namespace peak
{
namespace icv
{
/*!
 * \ingroup ids_peak_icv_cpp_selectors
 *
 * \brief Selects regions based on feature criteria.
 *
 * Represents a region selector used to filter a specified set of regions
 * based on features such as area or center of gravity.
 * Used to select the regions the user is interested in.
 *
 * \since ids_peak_icv 1.1
 */
class RegionSelector
{
public:
    /*!
     * \brief Constructs a selector for the specified set of regions.
     *
     * \param regions Regions to select from.
     *
     * \since ids_peak_icv 1.1
     */
    explicit RegionSelector(const std::vector<Region>& regions);

    /*!
     * \return Vector of selected regions.
     *
     * \since ids_peak_icv 1.1
     */
    std::vector<Region> GetRegions();

    /*!
     * \brief Selects regions by area.
     *
     * Provides regions where:
     * interval.minimum <= area(region) <= interval.maximum.
     *
     * \param interval Area interval to select by.
     *
     * \return Selector with filtered regions.
     *
     * \since ids_peak_icv 1.1
     */
    RegionSelector SelectByArea(const peak::common::IntervalU& interval);

    /*!
     * \brief Selects regions by center of gravity X.
     *
     * Provides regions where:
     * interval.minimum <= x(region) <= interval.maximum.
     *
     * \param interval X interval to select by.
     *
     * \return Selector with filtered regions.
     *
     * \since ids_peak_icv 1.1
     */
    RegionSelector SelectByCenterOfGravityX(const peak::common::IntervalF& interval);

    /*!
     * \brief Selects regions by center of gravity Y.
     *
     * Provides regions where:
     * interval.minimum <= y(region) <= interval.maximum.
     *
     * \param interval Y interval to select by.
     *
     * \return Selector with filtered regions.
     *
     * \since ids_peak_icv 1.1
     */
    RegionSelector SelectByCenterOfGravityY(const peak::common::IntervalF& interval);

    /*!
     * \brief Selects regions by center of gravity within a rectangle.
     *
     * Provides regions where:
     * rect.x <= x(region) <= rect.x + rect.width &&
     * rect.y <= y(region) <= rect.y + rect.height.
     *
     * \note If rect.width and rect.height are zero,
     *       the selection is based solely on the point (rect.x, rect.y).
     *
     * \param rect Rectangular interval to select by.
     *
     * \return Selector with filtered regions.
     *
     * \since ids_peak_icv 1.1
     */
    RegionSelector SelectByCenterOfGravityRect(const peak::common::RectangleF& rect);

protected:
    RegionSelector() = default;

private:
    template <typename T>
    RegionSelector SelectBy(const detail::select_by_get_count_function_t<peak::common::detail::c_type_of_t<T>>& selectByGetCount,
        const detail::select_by_function_t<peak::common::detail::c_type_of_t<T>>& selectBy, const T& interval);

    std::vector<Region> m_regions;
};

inline RegionSelector::RegionSelector(const std::vector<Region>& regions)
    : m_regions{ regions }
{}

inline std::vector<Region> RegionSelector::GetRegions()
{
    return m_regions;
}

inline RegionSelector RegionSelector::SelectByArea(const peak::common::IntervalU& interval)
{
    return SelectBy<peak::common::IntervalU>(
        PEAK_ICV_C_ABI_PREFIX peak_icv_Region_SelectByArea_GetCount, PEAK_ICV_C_ABI_PREFIX peak_icv_Region_SelectByArea, interval);
}

inline RegionSelector RegionSelector::SelectByCenterOfGravityX(const peak::common::IntervalF& interval)
{
    return SelectBy<peak::common::IntervalF>(PEAK_ICV_C_ABI_PREFIX peak_icv_Region_SelectByCenterOfGravityX_GetCount,
        PEAK_ICV_C_ABI_PREFIX peak_icv_Region_SelectByCenterOfGravityX, interval);
}

inline RegionSelector RegionSelector::SelectByCenterOfGravityY(const peak::common::IntervalF& interval)
{
    return SelectBy<peak::common::IntervalF>(PEAK_ICV_C_ABI_PREFIX peak_icv_Region_SelectByCenterOfGravityY_GetCount,
        PEAK_ICV_C_ABI_PREFIX peak_icv_Region_SelectByCenterOfGravityY, interval);
}

inline RegionSelector RegionSelector::SelectByCenterOfGravityRect(const peak::common::RectangleF& rect)
{
    return SelectBy<peak::common::RectangleF>(PEAK_ICV_C_ABI_PREFIX peak_icv_Region_SelectByCenterOfGravityRect_GetCount,
        PEAK_ICV_C_ABI_PREFIX peak_icv_Region_SelectByCenterOfGravityRect, rect);
}

template <typename T>
RegionSelector RegionSelector::SelectBy(
    const detail::select_by_get_count_function_t<peak::common::detail::c_type_of_t<T>>& selectByGetCount,
    const detail::select_by_function_t<peak::common::detail::c_type_of_t<T>>& selectBy, const T& interval)
{
    if (m_regions.empty())
    {
        return {};
    }

    std::vector<peak_icv_region_handle> handles;
    handles.reserve(m_regions.size());

    std::transform(m_regions.begin(), m_regions.end(), std::back_inserter(handles), [](const auto& region) {
        return peak::common::detail::BackendAccessor<peak::icv::Region>::BackendHandle(region);
    });

    size_t count = 0;
    detail::ExecuteAndMapReturnCodes([&] {
        return selectByGetCount(
            handles.data(), handles.size(), peak::common::detail::BackendAccessor<T>::CreateCType(interval), &count);
    });

    if (count == 0)
    {
        return {};
    }

    std::vector<peak_icv_region_handle> selectedHandles(count);
    detail::ExecuteAndMapReturnCodes([&] {
        return selectBy(handles.data(), handles.size(), peak::common::detail::BackendAccessor<T>::CreateCType(interval),
            selectedHandles.data(), selectedHandles.size());
    });
    return RegionSelector(peak::common::detail::BackendAccessor<peak::icv::Region>::CreateInstances(selectedHandles));
}

} /* namespace icv */
} /* namespace peak */
