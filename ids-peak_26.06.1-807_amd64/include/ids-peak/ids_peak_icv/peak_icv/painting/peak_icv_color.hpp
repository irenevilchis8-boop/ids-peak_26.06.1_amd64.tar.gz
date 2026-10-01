/*!
 * \file    peak_icv_color.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv_c/painting/peak_icv_painter.h>

#include <tuple>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_painting
 *
 * \brief Represents the red component of a color.
 *
 * \since ids_peak_icv 1.1
 */
using red_t = uint16_t;
/*!
 * \ingroup ids_peak_icv_cpp_painting
 *
 * \brief Represents the green component of a color.
 *
 * \since ids_peak_icv 1.1
 */
using green_t = uint16_t;
/*!
 * \ingroup ids_peak_icv_cpp_painting
 *
 * \brief Represents the blue component of a color.
 *
 * \since ids_peak_icv 1.1
 */
using blue_t = uint16_t;

/*!
 * \ingroup ids_peak_icv_cpp_painting
 *
 * \brief Represents predefined color constants.
 *
 * These values can be used to construct a \ref Color.
 *
 * \since ids_peak_icv 1.1
 */
enum class ColorConstant : uint64_t
{
    /*!
     * \brief Represents black with 8-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Black = PEAK_ICV_COLOR_BLACK,
    /*!
     * \brief Represents red with 8-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Red = PEAK_ICV_COLOR_RED,
    /*!
     * \brief Represents red with 8-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Red8 = PEAK_ICV_COLOR_RED_8,
    /*!
     * \brief Represents red with 10-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Red10 = PEAK_ICV_COLOR_RED_10,
    /*!
     * \brief Represents red with 12-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Red12 = PEAK_ICV_COLOR_RED_12,
    /*!
     * \brief Represents green with 8-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Green = PEAK_ICV_COLOR_GREEN,
    /*!
     * \brief Represents green with 8-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Green8 = PEAK_ICV_COLOR_GREEN_8,
    /*!
     * \brief Represents green with 10-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Green10 = PEAK_ICV_COLOR_GREEN_10,
    /*!
     * \brief Represents green with 12-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Green12 = PEAK_ICV_COLOR_GREEN_12,
    /*!
     * \brief Represents blue with 8-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Blue = PEAK_ICV_COLOR_BLUE,
    /*!
     * \brief Represents blue with 8-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Blue8 = PEAK_ICV_COLOR_BLUE_8,
    /*!
     * \brief Represents blue with 10-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Blue10 = PEAK_ICV_COLOR_BLUE_10,
    /*!
     * \brief Represents blue with 12-bit intensity.
     *
     * \since ids_peak_icv 1.1
     */
    Blue12 = PEAK_ICV_COLOR_BLUE_12
};

/*!
 * \ingroup ids_peak_icv_cpp_painting
 *
 * \brief Holds a color code composed of red, green, and blue components.
 *
 * \since ids_peak_icv 1.1
 */
class Color
{
public:
    /*!
     * \brief Constructs a default Color initialized to black.
     *
     * \since ids_peak_icv 1.1
     */
    constexpr Color() = default;

    /*!
     * \brief Constructs a Color from a raw 64-bit color code containing RGB values.
     *
     * The raw code uses the following layout:
     * - red in bits 32 to 47,
     * - green in bits 16 to 31,
     * - blue in bits 0 to 15.
     *
     * \param colorCodeRaw Raw color code encoding red, green, and blue components.
     *
     * \since ids_peak_icv 1.1
     */
    constexpr explicit Color(uint64_t colorCodeRaw)
        : m_colorCode{ colorCodeRaw }
    {}

    /*!
     * \brief Constructs a Color from separate red, green, and blue values.
     *
     * \param red Red component value.
     * \param green Green component value.
     * \param blue Blue component value.
     *
     * \since ids_peak_icv 1.1
     */
    constexpr Color(uint16_t red, uint16_t green, uint16_t blue)
        : Color(PEAK_ICV_COLOR_CODE(red, green, blue))
    {}

    /*!
     * \brief Constructs a Color from separate red, green, and blue values.
     *
     * \param red Red component value.
     * \param green Green component value.
     * \param blue Blue component value.
     * \param numBitsPerPixels Number of bits per pixel.
     *
     * \since ids_peak_icv 1.1
     */
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t numBitsPerPixels)
        : Color(PEAK_ICV_COLOR_CODE(red * ((1 << numBitsPerPixels) - 1) / 255, green * ((1 << numBitsPerPixels) - 1) / 255,
              blue * ((1 << numBitsPerPixels) - 1) / 255))
    {}

    /*!
     * \brief Constructs a Color from a predefined \ref ColorConstant.
     *
     * \param colorCode Predefined color constant.
     *
     * \since ids_peak_icv 1.1
     */
    constexpr explicit Color(ColorConstant colorCode)
        : m_colorCode{ static_cast<uint64_t>(colorCode) }
    {}

    /*!
     * \return The red component value of the color.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD constexpr uint16_t GetRed() const
    {
        return static_cast<uint16_t>(PEAK_ICV_COLOR_RED_FROM_CODE(m_colorCode));
    }

    /*!
     * \return The green component value of the color.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD constexpr uint16_t GetGreen() const
    {
        return static_cast<uint16_t>(PEAK_ICV_COLOR_GREEN_FROM_CODE(m_colorCode));
    }

    /*!
     * \return The blue component value of the color.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD constexpr uint16_t GetBlue() const
    {
        return static_cast<uint16_t>(PEAK_ICV_COLOR_BLUE_FROM_CODE(m_colorCode));
    }

    /*!
     * \return A tuple containing the red, green, and blue components.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD constexpr std::tuple<red_t, green_t, blue_t> GetRGB() const
    {
        return std::make_tuple(GetRed(), GetGreen(), GetBlue());
    }

    /*!
     * \return The raw 64-bit color code representing the color.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD constexpr uint64_t GetRaw() const
    {
        return m_colorCode;
    }

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    constexpr bool operator==(const Color& rhs) const
    {
        return m_colorCode == rhs.m_colorCode;
    }

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    constexpr bool operator!=(const Color& rhs) const
    {
        return !(rhs == *this);
    }

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    constexpr bool operator==(const ColorConstant& rhs) const
    {
        return m_colorCode == static_cast<uint64_t>(rhs);
    }

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    constexpr bool operator!=(const ColorConstant& rhs) const
    {
        return !(*this == rhs);
    }

private:
    uint64_t m_colorCode{};
};

} /* namespace icv */
} /* namespace peak */
