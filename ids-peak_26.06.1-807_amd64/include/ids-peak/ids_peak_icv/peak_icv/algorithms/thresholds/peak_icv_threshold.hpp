/*!
 * \file    peak_icv_threshold.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_type_traits.hpp>
#include <peak_common/types/peak_common_interval.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv/types/peak_icv_region.hpp>
#include <peak_icv_c/algorithms/thresholds/peak_icv_threshold.h>

namespace peak
{
namespace icv
{
namespace detail
{
/*!
 * \ingroup ids_peak_icv_cpp_thresholds
 *
 * \brief Class for thresholding an image.
 *
 * \tparam Interval shall only be interval types
 *
 * \since ids_peak_icv 1.1
 */
template <typename IntervalType>
class Threshold
{
public:
    static_assert(is_threshold_interval_v<IntervalType>, "Template argument of Threshold must be an Interval.");

    /*!
     * \brief Creates an instance of class Threshold
     *
     * \param[in] interval Interval with lower and upper threshold value.
     *
     * \since ids_peak_icv 1.1
     */
    explicit Threshold(const IntervalType& interval);

    /*!
     * \brief Creates an instance of class Threshold
     *
     * \param[in] minimum Lower threshold value.
     * \param[in] maximum Upper threshold value.
     *
     * \since ids_peak_icv 1.1
     */
    explicit Threshold(typename IntervalType::type minimum, typename IntervalType::type maximum);

    /*!
     * \brief Applies a threshold on a given single-channel image and returns a region with selected pixels
     * whose gray values are in the range Interval.minimum <= gray value <= Interval.maximum.
     *
     * \param[in] image Image to threshold
     *
     * \supportedPixelformats{Threshold}
     *
     * \return Returns a region with selected pixels.
     *
     * \throws OutOfRangeException  If the interval is out of bounds for the pixel format.
     * \throws NotPossibleException If the \p image is too big for processing.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Region Process(const Image& image) const;

    /*!
     * \brief Queries the minimum and maximum value of a given image and provides it as an interval.
     *
     * \param[in] image This is the image for which the range is calculated.
     *
     * \return Returns the maximum possible range of the given image.
     *
     * \since ids_peak_icv 1.1
     */
    static IntervalType GetRange(const Image& image);

private:
    IntervalType m_interval;
};

} // namespace detail

/*!
 * \ingroup ids_peak_icv_cpp_thresholds
 *
 * \brief Class for thresholding an image of type integer.
 *
 * \since ids_peak_icv 1.1
 */
using Threshold = detail::Threshold<peak::common::Interval>;

/*!
 * \ingroup ids_peak_icv_cpp_thresholds
 *
 * \brief Class for thresholding an image of type float.
 *
 * \since ids_peak_icv 1.1
 */
using ThresholdF = detail::Threshold<peak::common::IntervalF>;

namespace detail
{
template <typename IntervalType>
Threshold<IntervalType>::Threshold(const IntervalType& interval)
    : m_interval(interval)
{}

template <typename IntervalType>
Threshold<IntervalType>::Threshold(typename IntervalType::type minimum, typename IntervalType::type maximum)
    : m_interval(minimum, maximum)
{}

template <typename IntervalType>
peak::icv::Region Threshold<IntervalType>::Process(const Image& image) const
{
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(image);

    peak::icv::Region region;
    ExecuteAndMapReturnCodes([&] {
        peak::common::detail::c_type_of_t<IntervalType> interval{ m_interval.GetMinimum(), m_interval.GetMaximum() };
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Threshold_Process(inputImageHandle, &interval, sizeof(interval),
            peak::common::detail::BackendAccessor<peak::icv::Region>::BackendHandleAddress(region));
    });

    return region;
}

template <typename IntervalType>
IntervalType Threshold<IntervalType>::GetRange(const Image& image)
{
    peak::common::detail::c_type_of_t<IntervalType> interval{};
    ExecuteAndMapReturnCodes([&] {
        auto* const handle = peak::common::detail::BackendAccessor<Image>::BackendHandle(image);
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Threshold_GetRange(handle, &interval, sizeof(interval));
    });
    return { interval.minimum, interval.maximum };
}
} // namespace detail

} /* namespace icv */
} /* namespace peak */
