/*!
 * \file    peak_common_channel.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-03
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <ostream>
#include <string>

namespace peak
{
namespace common
{

/*!
 * \ingroup ids_peak_common_types
 * \brief Represents the various data channels in image or spatial data formats.
 *
 * This enumeration defines semantic labels for the different components
 * that can be found in pixel-based or point cloud data representations.
 *
 * \since ids_peak_common 1.0
 */
enum class Channel
{
    Intensity, /*!< Luminance or grayscale intensity channel. Common in single-channel images. */
    Red,       /*!< Red color channel. May appear in various layouts (e.g., RGB, ARGB). */
    Green,     /*!< Green color channel. Commonly part of multichannel color formats. */
    Blue,      /*!< Blue color channel. Present in formats like BGR, RGBA, etc. */
    Alpha,     /*!< Alpha (opacity or transparency) channel. Often used for blending and masking. */
    X,         /*!< Represents the X coordinate channel (e.g., in point clouds). */
    Y,         /*!< Represents the Y coordinate channel (e.g., in point clouds). */
    Z,         /*!< Represents the Z coordinate channel (e.g., in point clouds). */
    Bayer,     /*!< Raw Bayer pattern data from image sensors (e.g., BGGR, RGGB). */
    ChromaU,   /*!< Chrominance U channel (Cb). Represents the blue-difference chroma component in YUV/YCbCr color spaces. */
    ChromaV    /*!< Chrominance V channel (Cr). Represents the red-difference chroma component in YUV/YCbCr color spaces. */
};

/*!
 * \brief Converts a Channel enum value to its string representation.
 * \since ids_peak_common 2.0
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(Channel channel)
{
    switch (channel)
    {
    case Channel::Intensity:
        return "Intensity";
    case Channel::Red:
        return "Red";
    case Channel::Green:
        return "Green";
    case Channel::Blue:
        return "Blue";
    case Channel::Alpha:
        return "Alpha";
    case Channel::X:
        return "X";
    case Channel::Y:
        return "Y";
    case Channel::Z:
        return "Z";
    case Channel::Bayer:
        return "Bayer";
    case Channel::ChromaU:
        return "ChromaU";
    case Channel::ChromaV:
        return "ChromaV";
    }

    throw InvalidParameterException("The specified channel " + std::to_string(static_cast<int>(channel)) + " is unknown.");
}

/*!
 * \since ids_peak_common 2.0
 */
inline std::ostream& operator<<(std::ostream& os, const Channel channel)
{
    return os << ToString(channel);
}

namespace detail
{

/*!
 * \since ids_peak_common 2.0
 */
PEAK_COMMON_NO_DISCARD inline Channel ToChannel(const std::string& channel)
{
    if (channel == "Intensity")
    {
        return Channel::Intensity;
    }
    if (channel == "Red")
    {
        return Channel::Red;
    }
    if (channel == "Green")
    {
        return Channel::Green;
    }
    if (channel == "Blue")
    {
        return Channel::Blue;
    }
    if (channel == "Alpha")
    {
        return Channel::Alpha;
    }
    if (channel == "X")
    {
        return Channel::X;
    }
    if (channel == "Y")
    {
        return Channel::Y;
    }
    if (channel == "Z")
    {
        return Channel::Z;
    }
    if (channel == "Bayer")
    {
        return Channel::Bayer;
    }
    if (channel == "ChromaU")
    {
        return Channel::ChromaU;
    }
    if (channel == "ChromaV")
    {
        return Channel::ChromaV;
    }

    throw InvalidParameterException("The specified channel '" + channel + "' is unknown.");
}
} // namespace detail

} // namespace common 
} // namespace peak
