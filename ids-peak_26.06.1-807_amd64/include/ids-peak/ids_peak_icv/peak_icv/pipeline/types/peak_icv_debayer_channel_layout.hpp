/*!
 * \file    peak_icv_debayer_channel_layout.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/peak_icv_exception.hpp>

#include <unordered_map>
#include <string>

namespace peak
{
namespace pipeline
{
/*!
 * \ingroup ids_peak_icv_cpp_pipeline_types
 * \brief Specifies the channel layout used by the debayer module in image processing pipelines.
 *
 * \since ids_peak_icv 1.0
 */
enum class DebayerChannelLayout
{
    RGB = 0, //!< Red-Green-Blue format with 3 channels.
    BGR,     //!< Blue-Green-Red format with 3 channels.
    RGBA,    //!< Red-Green-Blue-Alpha format with 4 channels.
    BGRA     //!< Blue-Green-Red-Alpha format with 4 channels.
};

/*!
 * \brief Converts a DebayerChannelLayout enum value to its string representation.
 *
 * \param layout The debayer channel layout value to convert.
 * \return A string representation of the channel layout value.
 * \throws NotSupportedException If the layout value is unknown.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(DebayerChannelLayout layout)
{
    switch (layout)
    {
    case DebayerChannelLayout::RGB:
        return "RGB";
    case DebayerChannelLayout::BGR:
        return "BGR";
    case DebayerChannelLayout::RGBA:
        return "RGBA";
    case DebayerChannelLayout::BGRA:
        return "BGRA";
    }
    const auto layoutStr = std::to_string(static_cast<int>(layout));
    throw peak::icv::NotSupportedException("The given debayer channel layout " + layoutStr + " is unknown!");
}

/*!
 * \brief Stream output operator for DebayerChannelLayout enum.
 *
 * \param os The output stream.
 * \param layout The debayer channel layout value to output.
 * \return Reference to the output stream.
 * \since ids_peak_icv 1.0
 */
inline std::ostream& operator<<(std::ostream& os, DebayerChannelLayout layout)
{
    return os << ToString(layout);
}

namespace detail
{
/*!
 * \brief Converts a string representation to a DebayerChannelLayout enum value.
 *
 * \param layout The string representation of the channel layout value.
 * \return The corresponding DebayerChannelLayout enum value.
 * \throws NotSupportedException If the string does not match any known layout value.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline DebayerChannelLayout ToDebayerChannelLayout(const std::string& layout)
{
    static const std::unordered_map<std::string, DebayerChannelLayout> channelLayoutMap{ { "RGB", DebayerChannelLayout::RGB },
        { "BGR", DebayerChannelLayout::BGR }, { "RGBA", DebayerChannelLayout::RGBA }, { "BGRA", DebayerChannelLayout::BGRA } };

    auto it = channelLayoutMap.find(layout);
    if (it == channelLayoutMap.end())
    {
        throw peak::icv::NotSupportedException("The given debayer channel layout " + layout + " is unknown!");
    }
    return it->second;
}
} // namespace detail

} // namespace pipeline 
} // namespace peak
