/*!
 * \file    peak_icv_color_space.hpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-02-13
 * \since ids_peak_icv 1.3
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/peak_icv_exception.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_color_matrix_transformation.h>

#include <ostream>
#include <string>

namespace peak
{
namespace pipeline
{
/*!
 * \ingroup ids_peak_icv_cpp_pipeline_types
 * \brief Color spaces supported by the chromatic adaptation feature.
 *
 * \since ids_peak_icv 1.3
 */
enum class ColorSpace
{
    SRGB_D50 = PEAK_ICV_COLOR_SPACE_SRGB_D50,
    SRGB_D65 = PEAK_ICV_COLOR_SPACE_SRGB_D65,
    CIE_RGB_E = PEAK_ICV_COLOR_SPACE_CIE_RGB_E,
    ECI_RGB_D50 = PEAK_ICV_COLOR_SPACE_ECI_RGB_D50,
    Adobe_RGB_D65 = PEAK_ICV_COLOR_SPACE_ADOBE_RGB_D65
};

/*!
 * \brief Converts a ColorSpace enum value to its string representation.
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(ColorSpace colorSpace)
{
    switch (colorSpace)
    {
    case ColorSpace::SRGB_D50:
        return "SRGB_D50";
    case ColorSpace::SRGB_D65:
        return "SRGB_D65";
    case ColorSpace::CIE_RGB_E:
        return "CIE_RGB_E";
    case ColorSpace::ECI_RGB_D50:
        return "ECI_RGB_D50";
    case ColorSpace::Adobe_RGB_D65:
        return "Adobe_RGB_D65";
    default:
        const auto csStr = std::to_string(static_cast<int>(colorSpace));
        throw peak::icv::NotSupportedException("The given color space " + csStr + " is unknown!");
    }
}

inline std::ostream& operator<<(std::ostream& os, ColorSpace colorSpace)
{
    return os << ToString(colorSpace);
}

namespace detail
{
PEAK_COMMON_NO_DISCARD inline ColorSpace ToColorSpace(const std::string& colorSpace)
{
    if (colorSpace == "SRGB_D50")
    {
        return ColorSpace::SRGB_D50;
    }
    if (colorSpace == "SRGB_D65")
    {
        return ColorSpace::SRGB_D65;
    }
    if (colorSpace == "CIE_RGB_E")
    {
        return ColorSpace::CIE_RGB_E;
    }
    if (colorSpace == "ECI_RGB_D50")
    {
        return ColorSpace::ECI_RGB_D50;
    }
    if (colorSpace == "Adobe_RGB_D65")
    {
        return ColorSpace::Adobe_RGB_D65;
    }

    throw peak::icv::NotSupportedException("The given color space " + colorSpace + " is unknown!");
}
} // namespace detail
} // namespace pipeline 
} // namespace peak
