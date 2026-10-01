
/*!
 * \file    peak_common_pixel_format_traits.ipp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-01-16
 * \since   ids_peak_common 1.2
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

PEAK_COMMON_BEGIN_DISABLE_DEPRECATED_WARNINGS


namespace peak
{
namespace common
{
namespace detail
{
/// @cond HIDE_FROM_DOXYGEN
template <peak::common::PixelFormat pixelFormat>
struct PixelFormatTraits;
/// @endcond
template <>
struct PixelFormatTraits<PixelFormat::BayerGR8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR8";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR8;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR10";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR12";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG8";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG8;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG10";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG12";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB8";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB8;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB10";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB12";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG8";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG8;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG10";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG12";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG12;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono8";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono8;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono10;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono12;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono16>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono16";
    }

    static constexpr size_t storageBitsPerPixel = 16;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono16;
};

template <>
struct PixelFormatTraits<PixelFormat::Confidence8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Confidence8";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Confidence8;
};

template <>
struct PixelFormatTraits<PixelFormat::Confidence16>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Confidence16";
    }

    static constexpr size_t storageBitsPerPixel = 16;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Confidence16;
};

template <>
struct PixelFormatTraits<PixelFormat::Coord3D_C8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Coord3D_C8";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Coord3D_C8;
};

template <>
struct PixelFormatTraits<PixelFormat::Coord3D_C16>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Coord3D_C16";
    }

    static constexpr size_t storageBitsPerPixel = 16;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Coord3D_C16;
};

template <>
struct PixelFormatTraits<PixelFormat::Coord3D_C32f>
{
    using underlying_type = float;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Coord3D_C32f";
    }

    static constexpr size_t storageBitsPerPixel = 32;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Coord3D_C32f;
};

template <>
struct PixelFormatTraits<PixelFormat::Coord3D_ABC32f>
{
    using underlying_type = float;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::X, Channel::Y, Channel::Z };
    }

    static constexpr auto Name()
    {
        return "Coord3D_ABC32f";
    }

    static constexpr size_t storageBitsPerPixel = 96;
    static constexpr size_t allocatedBitsPerPixel = 96;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Coord3D_ABC32f;
};

template <>
struct PixelFormatTraits<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Intensity, Channel::ChromaU, Channel::ChromaV };
    }

    static constexpr auto Name()
    {
        return "YUV420_8_YY_UV_SemiplanarIDS";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::YUV420_8_YY_UV_SemiplanarIDS;
};

template <>
struct PixelFormatTraits<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Intensity, Channel::ChromaV, Channel::ChromaU };
    }

    static constexpr auto Name()
    {
        return "YUV420_8_YY_VU_SemiplanarIDS";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::YUV420_8_YY_VU_SemiplanarIDS;
};

template <>
struct PixelFormatTraits<PixelFormat::YUV422_8_UYVY>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Intensity, Channel::ChromaU, Channel::ChromaV };
    }

    static constexpr auto Name()
    {
        return "YUV422_8_UYVY";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::YUV422_8_UYVY;
};

template <>
struct PixelFormatTraits<PixelFormat::RGB8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue };
    }

    static constexpr auto Name()
    {
        return "RGB8";
    }

    static constexpr size_t storageBitsPerPixel = 24;
    static constexpr size_t allocatedBitsPerPixel = 24;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGB8;
};

template <>
struct PixelFormatTraits<PixelFormat::RGB10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue };
    }

    static constexpr auto Name()
    {
        return "RGB10";
    }

    static constexpr size_t storageBitsPerPixel = 30;
    static constexpr size_t allocatedBitsPerPixel = 48;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGB10;
};

template <>
struct PixelFormatTraits<PixelFormat::RGB12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue };
    }

    static constexpr auto Name()
    {
        return "RGB12";
    }

    static constexpr size_t storageBitsPerPixel = 36;
    static constexpr size_t allocatedBitsPerPixel = 48;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGB12;
};

template <>
struct PixelFormatTraits<PixelFormat::BGR8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Blue, Channel::Green, Channel::Red };
    }

    static constexpr auto Name()
    {
        return "BGR8";
    }

    static constexpr size_t storageBitsPerPixel = 24;
    static constexpr size_t allocatedBitsPerPixel = 24;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BGR8;
};

template <>
struct PixelFormatTraits<PixelFormat::BGR10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Blue, Channel::Green, Channel::Red };
    }

    static constexpr auto Name()
    {
        return "BGR10";
    }

    static constexpr size_t storageBitsPerPixel = 30;
    static constexpr size_t allocatedBitsPerPixel = 48;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BGR10;
};

template <>
struct PixelFormatTraits<PixelFormat::BGR12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Blue, Channel::Green, Channel::Red };
    }

    static constexpr auto Name()
    {
        return "BGR12";
    }

    static constexpr size_t storageBitsPerPixel = 36;
    static constexpr size_t allocatedBitsPerPixel = 48;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BGR12;
};

template <>
struct PixelFormatTraits<PixelFormat::RGBa8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue, Channel::Alpha };
    }

    static constexpr auto Name()
    {
        return "RGBa8";
    }

    static constexpr size_t storageBitsPerPixel = 32;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGBa8;
};

template <>
struct PixelFormatTraits<PixelFormat::RGBa10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue, Channel::Alpha };
    }

    static constexpr auto Name()
    {
        return "RGBa10";
    }

    static constexpr size_t storageBitsPerPixel = 40;
    static constexpr size_t allocatedBitsPerPixel = 64;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGBa10;
};

template <>
struct PixelFormatTraits<PixelFormat::RGBa12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue, Channel::Alpha };
    }

    static constexpr auto Name()
    {
        return "RGBa12";
    }

    static constexpr size_t storageBitsPerPixel = 48;
    static constexpr size_t allocatedBitsPerPixel = 64;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGBa12;
};

template <>
struct PixelFormatTraits<PixelFormat::BGRa8>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Blue, Channel::Green, Channel::Red, Channel::Alpha };
    }

    static constexpr auto Name()
    {
        return "BGRa8";
    }

    static constexpr size_t storageBitsPerPixel = 32;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BGRa8;
};

template <>
struct PixelFormatTraits<PixelFormat::BGRa10>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Blue, Channel::Green, Channel::Red, Channel::Alpha };
    }

    static constexpr auto Name()
    {
        return "BGRa10";
    }

    static constexpr size_t storageBitsPerPixel = 40;
    static constexpr size_t allocatedBitsPerPixel = 64;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BGRa10;
};

template <>
struct PixelFormatTraits<PixelFormat::BGRa12>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Blue, Channel::Green, Channel::Red, Channel::Alpha };
    }

    static constexpr auto Name()
    {
        return "BGRa12";
    }

    static constexpr size_t storageBitsPerPixel = 48;
    static constexpr size_t allocatedBitsPerPixel = 64;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BGRa12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG10p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG10p";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG12p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG12p";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB10p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB10p";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB12p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB12p";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR10p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR10p";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR12p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR12p";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG10p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG10p";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG12p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG12p";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG12;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10p";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono10;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12p>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12p";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono12;
};

template <>
struct PixelFormatTraits<PixelFormat::RGB10p32>
{
    using underlying_type = uint32_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue };
    }

    static constexpr auto Name()
    {
        return "RGB10p32";
    }

    static constexpr size_t storageBitsPerPixel = 30;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGB10;
};

template <>
struct PixelFormatTraits<PixelFormat::BGR10p32>
{
    using underlying_type = uint32_t;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Blue, Channel::Green, Channel::Red };
    }

    static constexpr auto Name()
    {
        return "BGR10p32";
    }

    static constexpr size_t storageBitsPerPixel = 30;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BGR10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG10g40IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG10g40IDS";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB10g40IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB10g40IDS";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR10g40IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR10g40IDS";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG10g40IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG10g40IDS";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG10;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG12g24IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG12g24IDS";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB12g24IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB12g24IDS";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR12g24IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR12g24IDS";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR12;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG12g24IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG12g24IDS";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG12;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10g40IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10g40IDS";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono10;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12g24IDS>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12g24IDS";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono12;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono32f>
{
    using underlying_type = float;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono32f";
    }

    static constexpr size_t storageBitsPerPixel = 32;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono32f;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono32fIDS>
{
    using underlying_type = float;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono32fIDS";
    }

    static constexpr size_t storageBitsPerPixel = 32;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono32fIDS;
};

template <>
struct PixelFormatTraits<PixelFormat::RGB32f>
{
    using underlying_type = float;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue };
    }

    static constexpr auto Name()
    {
        return "RGB32f";
    }

    static constexpr size_t storageBitsPerPixel = 96;
    static constexpr size_t allocatedBitsPerPixel = 96;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGB32f;
};

template <>
struct PixelFormatTraits<PixelFormat::RGB32fIDS>
{
    using underlying_type = float;

    static constexpr std::array<Channel, 3> Channels()
    {
        return { Channel::Red, Channel::Green, Channel::Blue };
    }

    static constexpr auto Name()
    {
        return "RGB32fIDS";
    }

    static constexpr size_t storageBitsPerPixel = 96;
    static constexpr size_t allocatedBitsPerPixel = 96;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::RGB32fIDS;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10g40IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10g40IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG10g40IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG10g40IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG10g40IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG10g40IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR10g40IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR10g40IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB10g40IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB10g40IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12g24IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12g24IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG12g24IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG12g24IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG12g24IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG12g24IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR12g24IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR12g24IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB12g24IDS_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB12g24IDS_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono8_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono8_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG8_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG8_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG8_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG8_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR8_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR8_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB8_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB8_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG10_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG10_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG10_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG10_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR10_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR10_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB10_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB10_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG12_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG12_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG12_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG12_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR12_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR12_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB12_I_A_B>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB12_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG10p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG10p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG10p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG10p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR10p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR10p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB10p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB10p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG12p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG12p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG12p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG12p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR12p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR12p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB12p_I_A_B>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB12p_I_A_B";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono8_I_AB_CD>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono8_I_AB_CD";
    }

    static constexpr size_t storageBitsPerPixel = 8;
    static constexpr size_t allocatedBitsPerPixel = 8;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono8_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10_I_AB_CD>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10_I_AB_CD";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono10_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12_I_AB_CD>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12_I_AB_CD";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono12_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10p_I_AB_CD>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10p_I_AB_CD";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono10_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12p_I_AB_CD>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12p_I_AB_CD";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono12_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10g40IDS_I_AB_CD>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10g40IDS_I_AB_CD";
    }

    static constexpr size_t storageBitsPerPixel = 10;
    static constexpr size_t allocatedBitsPerPixel = 10;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono10_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12g24IDS_I_AB_CD>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 1> Channels()
    {
        return { Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12g24IDS_I_AB_CD";
    }

    static constexpr size_t storageBitsPerPixel = 12;
    static constexpr size_t allocatedBitsPerPixel = 12;
    static constexpr bool isPacked = true;
    static constexpr bool isInterleaved = true;
    static constexpr auto unpackedFormat = PixelFormat::Mono12_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Intensity, Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10_AB";
    }

    static constexpr size_t storageBitsPerPixel = 20;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG10_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG10_AB";
    }

    static constexpr size_t storageBitsPerPixel = 20;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG10_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG10_AB";
    }

    static constexpr size_t storageBitsPerPixel = 20;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR10_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR10_AB";
    }

    static constexpr size_t storageBitsPerPixel = 20;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB10_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB10_AB";
    }

    static constexpr size_t storageBitsPerPixel = 20;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB10_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Intensity, Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12_AB";
    }

    static constexpr size_t storageBitsPerPixel = 24;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG12_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG12_AB";
    }

    static constexpr size_t storageBitsPerPixel = 24;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG12_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG12_AB";
    }

    static constexpr size_t storageBitsPerPixel = 24;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR12_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR12_AB";
    }

    static constexpr size_t storageBitsPerPixel = 24;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB12_AB>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB12_AB";
    }

    static constexpr size_t storageBitsPerPixel = 24;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB12_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono8_AB>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Intensity, Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono8_AB";
    }

    static constexpr size_t storageBitsPerPixel = 16;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerRG8_AB>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerRG8_AB";
    }

    static constexpr size_t storageBitsPerPixel = 16;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerRG8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerBG8_AB>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerBG8_AB";
    }

    static constexpr size_t storageBitsPerPixel = 16;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerBG8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGR8_AB>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGR8_AB";
    }

    static constexpr size_t storageBitsPerPixel = 16;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGR8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::BayerGB8_AB>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 2> Channels()
    {
        return { Channel::Bayer, Channel::Bayer };
    }

    static constexpr auto Name()
    {
        return "BayerGB8_AB";
    }

    static constexpr size_t storageBitsPerPixel = 16;
    static constexpr size_t allocatedBitsPerPixel = 16;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::BayerGB8_AB;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono8_ABCD>
{
    using underlying_type = uint8_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Intensity, Channel::Intensity, Channel::Intensity, Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono8_ABCD";
    }

    static constexpr size_t storageBitsPerPixel = 32;
    static constexpr size_t allocatedBitsPerPixel = 32;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono8_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono10_ABCD>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Intensity, Channel::Intensity, Channel::Intensity, Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono10_ABCD";
    }

    static constexpr size_t storageBitsPerPixel = 40;
    static constexpr size_t allocatedBitsPerPixel = 64;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono10_ABCD;
};

template <>
struct PixelFormatTraits<PixelFormat::Mono12_ABCD>
{
    using underlying_type = uint16_t;

    static constexpr std::array<Channel, 4> Channels()
    {
        return { Channel::Intensity, Channel::Intensity, Channel::Intensity, Channel::Intensity };
    }

    static constexpr auto Name()
    {
        return "Mono12_ABCD";
    }

    static constexpr size_t storageBitsPerPixel = 48;
    static constexpr size_t allocatedBitsPerPixel = 64;
    static constexpr bool isPacked = false;
    static constexpr bool isInterleaved = false;
    static constexpr auto unpackedFormat = PixelFormat::Mono12_ABCD;
};

} // namespace detail
} // namespace common 
} // namespace peak


PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS

