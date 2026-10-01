/*!
 * \file    peak_common_pixel_format.ipp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-01-16
 * \since   ids_peak_common 1.2
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/detail/peak_common_pixel_format_traits.ipp>

namespace peak
{
namespace common
{
inline std::ostream& operator<<(std::ostream& os, PixelFormat pixelFormat)
{
    PixelFormatInfo info(pixelFormat);
    os << info.GetName();
    return os;
}

namespace detail
{
/// @cond HIDE_FROM_DOXYGEN
template <typename T, bool isFloat>
struct ValueRangeHelper;

template <typename T>
struct ValueRangeHelper<T, false> // Integer
{
    static constexpr T Minimum(size_t)
    {
        return 0;
    }

    static constexpr T Maximum(size_t bitsPerChannel)
    {
        return static_cast<T>((1ULL << bitsPerChannel) - 1);
    }
};

template <typename T>
struct ValueRangeHelper<T, true> // Float
{
    static constexpr T Minimum(size_t)
    {
        return std::numeric_limits<T>::lowest();
    }

    static constexpr T Maximum(size_t)
    {
        return (std::numeric_limits<T>::max)();
    }
};

template <PixelFormat pixelFormat>
struct PixelFormatInfo
{
    using traits = PixelFormatTraits<pixelFormat>;
    using underlying_type = typename traits::underlying_type;
    static constexpr bool is_floating_point = std::is_floating_point<underlying_type>::value;

    static constexpr size_t storageBitsPerPixel = traits::storageBitsPerPixel;
    static constexpr size_t allocatedBitsPerPixel = traits::allocatedBitsPerPixel;

    static constexpr bool isYUV = storageBitsPerPixel / traits::Channels().size() < 8;

    static constexpr size_t storageBitsPerChannel = isYUV ? storageBitsPerPixel : storageBitsPerPixel / traits::Channels().size();

    using unpacked_underlying_type = typename PixelFormatTraits<traits::unpackedFormat>::underlying_type;

    static constexpr unpacked_underlying_type minimumValuePerChannel =
        ValueRangeHelper<unpacked_underlying_type, is_floating_point>::Minimum(storageBitsPerChannel);

    static constexpr unpacked_underlying_type maximumValuePerChannel =
        ValueRangeHelper<unpacked_underlying_type, is_floating_point>::Maximum(storageBitsPerChannel);

    static constexpr auto Channels()
    {
        return traits::Channels();
    }

    static constexpr const char* Name()
    {
        return traits::Name();
    }

    static constexpr size_t GetSizeInBytes(const Size& size)
    {
        const auto area = static_cast<uint64_t>(size.GetWidth()) * size.GetHeight();
        return static_cast<size_t>(((area * PixelFormatInfo<pixelFormat>::allocatedBitsPerPixel) + 7) / 8);
    }

    static constexpr bool IsPacked()
    {
        return traits::isPacked;
    }

    static constexpr bool IsInterleaved()
    {
        return traits::isInterleaved;
    }

    static constexpr PixelFormat GetUnpackedFormat()
    {
        return traits::unpackedFormat;
    }
};

template <typename PixelFormatInfo>
inline auto ChannelsVector()
{
    constexpr auto arr = PixelFormatInfo::Channels();
    using T = typename std::decay_t<typename decltype(arr)::value_type>;
    return std::vector<T>(arr.begin(), arr.end());
}

/// @endcond
} // namespace detail

template <typename T>
T PixelFormatInfo::GetMinimumValuePerChannel() const
{
    static_assert(true, "The given template type is not supported! Only size_t and float can be used.");
}

template <typename T>
T PixelFormatInfo::GetMaximumValuePerChannel() const
{
    static_assert(true, "The given template type is not supported! Only size_t and float can be used.");
}
} // namespace common 
} // namespace peak

#include <peak_common/types/detail/peak_common_pixel_format_info.ipp>
