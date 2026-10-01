/*!
 * \file    peak_common_metadata_traits.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-08-08
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/geometry/peak_common_rectangle.hpp>
#include <peak_common/types/peak_common_metadata_key.hpp>
#include <array>
#include <cstdint>

namespace peak
{
namespace common
{
namespace detail
{
/// @cond HIDE_FROM_DOXYGEN

template <MetadataKey metadataKey>
struct MetadataKeyTraits;

/// @endcond

/*!
 * \since ids_peak_common 1.0
 */
template <>
struct MetadataKeyTraits<MetadataKey::DeviceTimestamp>
{
    using type = uint64_t;

    /*!
     * \since ids_peak_common 1.1
     */
    static constexpr const char* Name()
    {
        return "DeviceTimestamp";
    }
};

/*!
 * \since ids_peak_common 1.0
 */
template <>
struct MetadataKeyTraits<MetadataKey::DeviceFrameID>
{
    using type = uint64_t;

    /*!
     * \since ids_peak_common 1.1
     */
    static constexpr const char* Name()
    {
        return "DeviceFrameID";
    }
};

/*!
 * \since ids_peak_common 1.1
 */
template <>
struct MetadataKeyTraits<MetadataKey::BinningHorizontal>
{
    using type = uint64_t;

    /*!
     * \since ids_peak_common 1.1
     */
    static constexpr const char* Name()
    {
        return "BinningHorizontal";
    }
};

/*!
 * \since ids_peak_common 1.1
 */
template <>
struct MetadataKeyTraits<MetadataKey::BinningVertical>
{
    using type = uint64_t;

    /*!
     * \since ids_peak_common 1.1
     */
    static constexpr const char* Name()
    {
        return "BinningVertical";
    }
};

/*!
 * \since ids_peak_common 1.1
 */
template <>
struct MetadataKeyTraits<MetadataKey::Roi>
{
    using type = RectangleU;

    /*!
     * \since ids_peak_common 1.1
     */
    static constexpr const char* Name()
    {
        return "Roi";
    }
};

/*!
 * \since ids_peak_common 1.2
 */
template <>
struct MetadataKeyTraits<MetadataKey::DeviceExposureTime>
{
    using type = double;

    /*!
     * \since ids_peak_common 1.2
     */
    static constexpr const char* Name()
    {
        return "DeviceExposureTime";
    }
};

/*!
 * \since ids_peak_common 1.3
 */
template <>
struct MetadataKeyTraits<MetadataKey::DeviceExposureTimeSequence>
{
    using type = std::vector<double>;

    /*!
     * \since ids_peak_common 1.3
     */
    static constexpr const char* Name()
    {
        return "DeviceExposureTimeSequence";
    }
};

/*!
 * \since ids_peak_common 1.3
 */
template <>
struct MetadataKeyTraits<MetadataKey::SystemTimestamp>
{
    using type = uint64_t;

    /*!
     * \since ids_peak_common 1.3
     */
    static constexpr const char* Name()
    {
        return "SystemTimestamp";
    }
};

/*!
 * \since ids_peak_common 1.3
 */
template <>
struct MetadataKeyTraits<MetadataKey::DeviceGain>
{
    using type = double;

    /*!
     * \since ids_peak_common 1.3
     */
    static constexpr const char* Name()
    {
        return "DeviceGain";
    }
};

/*!
 * \since ids_peak_common 1.3
 */
template <>
struct MetadataKeyTraits<MetadataKey::DeviceGainSequence>
{
    using type = std::vector<double>;

    /*!
     * \since ids_peak_common 1.3
     */
    static constexpr const char* Name()
    {
        return "DeviceGainSequence";
    }
};

/*!
 * \since ids_peak_common 1.1
 */
constexpr std::array<MetadataKey, 10> allMetadataKeys{ MetadataKey::DeviceTimestamp, MetadataKey::DeviceFrameID,
    MetadataKey::BinningHorizontal, MetadataKey::BinningVertical, MetadataKey::Roi, MetadataKey::DeviceExposureTime,
    MetadataKey::SystemTimestamp, MetadataKey::DeviceExposureTimeSequence, MetadataKey::DeviceGain, MetadataKey::DeviceGainSequence };

/// @cond HIDE_FROM_DOXYGEN
template <typename T, typename Tuple>
struct is_in_tuple;

template <typename T>
struct is_in_tuple<T, std::tuple<>> : std::false_type
{};

template <typename T, typename First, typename... Rest>
struct is_in_tuple<T, std::tuple<First, Rest...>>
    : std::integral_constant<bool, std::is_same<T, First>::value || is_in_tuple<T, std::tuple<Rest...>>::value>
{};

template <typename T, typename Enable = void>
struct NormalizeType
{
    using type = T;
};

template <typename T>
struct NormalizeType<T, typename std::enable_if_t<!std::is_same<T, bool>::value && std::is_integral<T>::value && std::is_signed<T>::value>>
{
    using type = int64_t;
};

template <typename T>
struct NormalizeType<T, typename std::enable_if_t<std::is_floating_point<T>::value>>
{
    using type = double;
};

template <typename T>
struct NormalizeType<T, typename std::enable_if_t<!std::is_same<T, bool>::value && std::is_integral<T>::value && !std::is_signed<T>::value>>
{
    using type = uint64_t;
};

template <typename T>
using normalize_t = typename NormalizeType<typename std::decay_t<T>>::type;
/// @endcond

} // namespace detail
} // namespace common 
} // namespace peak
