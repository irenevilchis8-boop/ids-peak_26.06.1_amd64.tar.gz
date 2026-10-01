/*!
 * \file    peak_common_type_traits.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-28
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <type_traits>
#include <cstddef>
#include <cstdint>


// NOLINTBEGIN(readability-identifier-naming)
struct peak_common_interval;
struct peak_common_interval_u;
struct peak_common_interval_f;
struct peak_common_range;
struct peak_common_range_u;
struct peak_common_range_f;
struct peak_common_rectangle;
struct peak_common_rectangle_f;
struct peak_common_rectangle_u;
struct peak_common_point;
struct peak_common_point_f;
struct peak_common_point_u;
struct peak_common_size;
struct peak_common_size_f;
struct peak_common_version;

// NOLINTEND(readability-identifier-naming)

/// @cond HIDE_FROM_DOXYGEN

namespace peak
{
namespace common
{

class Version;

namespace detail
{

template <typename PointType, typename SizeType>
class RectangleT;
template <typename T>
class PointT;
template <typename T>
class SizeT;

template <typename T>
class IntervalT;

template <typename T>
class RangeT;

template <typename T>
class SizeT;

template <typename T>
struct c_type_of_;

template <>
struct c_type_of_<IntervalT<uint32_t>>
{
    using type = peak_common_interval_u;
};

template <>
struct c_type_of_<IntervalT<int32_t>>
{
    using type = peak_common_interval;
};

template <>
struct c_type_of_<IntervalT<float>>
{
    using type = peak_common_interval_f;
};

template <>
struct c_type_of_<RangeT<uint32_t>>
{
    using type = peak_common_range_u;
};

template <>
struct c_type_of_<RangeT<int32_t>>
{
    using type = peak_common_range;
};

template <>
struct c_type_of_<RangeT<float>>
{
    using type = peak_common_range_f;
};

template <>
struct c_type_of_<RectangleT<int32_t, uint32_t>>
{
    using type = peak_common_rectangle;
};

template <>
struct c_type_of_<RectangleT<float, float>>
{
    using type = peak_common_rectangle_f;
};

template <>
struct c_type_of_<RectangleT<uint32_t, uint32_t>>
{
    using type = peak_common_rectangle_u;
};

template <>
struct c_type_of_<PointT<int32_t>>
{
    using type = peak_common_point;
};

template <>
struct c_type_of_<PointT<uint32_t>>
{
    using type = peak_common_point_u;
};

template <>
struct c_type_of_<PointT<float>>
{
    using type = peak_common_point_f;
};

template <>
struct c_type_of_<SizeT<uint32_t>>
{
    using type = peak_common_size;
};

template <>
struct c_type_of_<SizeT<float>>
{
    using type = peak_common_size_f;
};

template <>
struct c_type_of_<Version>
{
    using type = peak_common_version;
};

template <typename...>
using void_t = void;

template <typename T>
using c_type_of_t = typename c_type_of_<T>::type;

template <typename T>
using handle_of_t = c_type_of_t<T>*;

template <typename, typename = void>
struct has_c_type_of : std::false_type
{};

template <typename T>
struct has_c_type_of<T, void_t<typename c_type_of_<T>::type>> : std::true_type
{};

} // namespace detail
} // namespace common 
} // namespace peak

/// @endcond
