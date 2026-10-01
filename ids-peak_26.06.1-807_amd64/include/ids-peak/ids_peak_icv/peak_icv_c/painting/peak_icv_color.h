/*!
 * \file    peak_icv_color.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-10-15
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once
/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Red value from color code
 */
#define PEAK_ICV_COLOR_RED_FROM_CODE(colorCode) (uint64_t)(colorCode) >> 32
/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Green value from color code
 */
#define PEAK_ICV_COLOR_GREEN_FROM_CODE(colorCode) (uint64_t)(colorCode) >> 16
/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Blue value from color code
 */
#define PEAK_ICV_COLOR_BLUE_FROM_CODE(colorCode) (colorCode)

/*!
 * \ingroup ids_peak_icv_c_painting
 *
 * \brief Packs red, green, and blue components into a 64-bit integer.
 *
 * Combines color components
 * into a single 64-bit unsigned integer
 * with the following layout:
 * - `red` is stored in bits 32 to 47,
 * - `green` is stored in bits 16 to 31,
 * - `blue` is stored in bits 0 to 15.
 *
 * Each component is cast to `uint64_t` and shifted accordingly before being combined.
 *
 * \note Ensure that each color component fits within 16 bits to avoid overflow.
 */
#define PEAK_ICV_COLOR_CODE(red, green, blue) (((uint64_t)(red) << 32) | ((uint64_t)(green) << 16) | (uint64_t)(blue))

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color black
 */
#define PEAK_ICV_COLOR_BLACK_8 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color white
 */
#define PEAK_ICV_COLOR_WHITE_8 PEAK_ICV_COLOR_CODE(0xFF, 0xFF, 0xFF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color red
 */
#define PEAK_ICV_COLOR_RED_8 PEAK_ICV_COLOR_CODE(0xFF, 0x0, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color green
 */
#define PEAK_ICV_COLOR_GREEN_8 PEAK_ICV_COLOR_CODE(0x0, 0xFF, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color blue
 */
#define PEAK_ICV_COLOR_BLUE_8 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0xFF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dim gray
 */
#define PEAK_ICV_COLOR_DIM_GRAY_8 PEAK_ICV_COLOR_CODE(0x69, 0x69, 0x69)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color gray
 */
#define PEAK_ICV_COLOR_GRAY_8 PEAK_ICV_COLOR_CODE(0x80, 0x80, 0x80)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light gray
 */
#define PEAK_ICV_COLOR_LIGHT_GRAY_8 PEAK_ICV_COLOR_CODE(0xD3, 0xD3, 0xD3)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cyan
 */
#define PEAK_ICV_COLOR_CYAN_8 PEAK_ICV_COLOR_CODE(0x0, 0xFF, 0xFF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color magenta
 */
#define PEAK_ICV_COLOR_MAGENTA_8 PEAK_ICV_COLOR_CODE(0xFF, 0x0, 0xFF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color yellow
 */
#define PEAK_ICV_COLOR_YELLOW_8 PEAK_ICV_COLOR_CODE(0xFF, 0xFF, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color medium slate blue
 */
#define PEAK_ICV_COLOR_MEDIUM_SLATE_BLUE_8 PEAK_ICV_COLOR_CODE(0x7B, 0x68, 0xEE)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color coral
 */
#define PEAK_ICV_COLOR_CORAL_8 PEAK_ICV_COLOR_CODE(0xFF, 0x7F, 0x50)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color slate blue
 */
#define PEAK_ICV_COLOR_SLATE_BLUE_8 PEAK_ICV_COLOR_CODE(0x6A, 0x5A, 0xCD)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color spring green
 */
#define PEAK_ICV_COLOR_SPRING_GREEN_8 PEAK_ICV_COLOR_CODE(0x0, 0xFF, 0x7F)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color orange red
 */
#define PEAK_ICV_COLOR_ORANGE_RED_8 PEAK_ICV_COLOR_CODE(0xFF, 0x45, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dark olive green
 */
#define PEAK_ICV_COLOR_DARK_OLIVE_GREEN_8 PEAK_ICV_COLOR_CODE(0x55, 0x6B, 0x2F)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color pink
 */
#define PEAK_ICV_COLOR_PINK_8 PEAK_ICV_COLOR_CODE(0xFF, 0xC0, 0xCB)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cadet blue
 */
#define PEAK_ICV_COLOR_CADET_BLUE_8 PEAK_ICV_COLOR_CODE(0x5F, 0x9E, 0xA0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color goldenrod
 */
#define PEAK_ICV_COLOR_GOLDENROD_8 PEAK_ICV_COLOR_CODE(0xDA, 0xA5, 0x20)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color orange
 */
#define PEAK_ICV_COLOR_ORANGE_8 PEAK_ICV_COLOR_CODE(0xFF, 0xA5, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color gold
 */
#define PEAK_ICV_COLOR_GOLD_8 PEAK_ICV_COLOR_CODE(0xFF, 0xD7, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color forest green
 */
#define PEAK_ICV_COLOR_FOREST_GREEN_8 PEAK_ICV_COLOR_CODE(0x22, 0x8B, 0x22)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cornflower blue
 */
#define PEAK_ICV_COLOR_CORNFLOWER_BLUE_8 PEAK_ICV_COLOR_CODE(0x64, 0x95, 0xED)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color navy
 */
#define PEAK_ICV_COLOR_NAVY_8 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0x80)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color turquoise
 */
#define PEAK_ICV_COLOR_TURQUOISE_8 PEAK_ICV_COLOR_CODE(0x40, 0xE0, 0xD0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dark slate blue
 */
#define PEAK_ICV_COLOR_DARK_SLATE_BLUE_8 PEAK_ICV_COLOR_CODE(0x48, 0x3D, 0x8B)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light blue
 */
#define PEAK_ICV_COLOR_LIGHT_BLUE_8 PEAK_ICV_COLOR_CODE(0xAD, 0xD8, 0xE6)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color indian red
 */
#define PEAK_ICV_COLOR_INDIAN_RED_8 PEAK_ICV_COLOR_CODE(0xCD, 0x5C, 0x5C)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color violet red
 */
#define PEAK_ICV_COLOR_VIOLET_RED_8 PEAK_ICV_COLOR_CODE(0xD0, 0x20, 0x90)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light steel blue
 */
#define PEAK_ICV_COLOR_LIGHT_STEEL_BLUE_8 PEAK_ICV_COLOR_CODE(0xB0, 0xC4, 0xDE)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color medium blue
 */
#define PEAK_ICV_COLOR_MEDIUM_BLUE_8 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0xCD)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color khaki
 */
#define PEAK_ICV_COLOR_KHAKI_8 PEAK_ICV_COLOR_CODE(0xF0, 0xE6, 0x8C)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color violet
 */
#define PEAK_ICV_COLOR_VIOLET_8 PEAK_ICV_COLOR_CODE(0xEE, 0x82, 0xEE)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color firebrick
 */
#define PEAK_ICV_COLOR_FIREBRICK_8 PEAK_ICV_COLOR_CODE(0xB2, 0x22, 0x22)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color midnight blue
 */
#define PEAK_ICV_COLOR_MIDNIGHT_BLUE_8 PEAK_ICV_COLOR_CODE(0x19, 0x19, 0x70)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color black
 */
#define PEAK_ICV_COLOR_BLACK_10 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color white
 */
#define PEAK_ICV_COLOR_WHITE_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x3FF, 0x3FF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color red
 */
#define PEAK_ICV_COLOR_RED_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x0, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color green
 */
#define PEAK_ICV_COLOR_GREEN_10 PEAK_ICV_COLOR_CODE(0x0, 0x3FF, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color blue
 */
#define PEAK_ICV_COLOR_BLUE_10 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0x3FF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dim gray
 */
#define PEAK_ICV_COLOR_DIM_GRAY_10 PEAK_ICV_COLOR_CODE(0x155, 0x155, 0x155)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color gray
 */
#define PEAK_ICV_COLOR_GRAY_10 PEAK_ICV_COLOR_CODE(0x200, 0x200, 0x200)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light gray
 */
#define PEAK_ICV_COLOR_LIGHT_GRAY_10 PEAK_ICV_COLOR_CODE(0x355, 0x355, 0x355)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cyan
 */
#define PEAK_ICV_COLOR_CYAN_10 PEAK_ICV_COLOR_CODE(0x0, 0x3FF, 0x3FF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color magenta
 */
#define PEAK_ICV_COLOR_MAGENTA_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x0, 0x3FF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color yellow
 */
#define PEAK_ICV_COLOR_YELLOW_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x3FF, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color medium slate blue
 */
#define PEAK_ICV_COLOR_MEDIUM_SLATE_BLUE_10 PEAK_ICV_COLOR_CODE(0x1FB, 0x1A4, 0x3EE)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color coral
 */
#define PEAK_ICV_COLOR_CORAL_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x1FE, 0x140)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color slate blue
 */
#define PEAK_ICV_COLOR_SLATE_BLUE_10 PEAK_ICV_COLOR_CODE(0x1AA, 0x168, 0x324)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color spring green
 */
#define PEAK_ICV_COLOR_SPRING_GREEN_10 PEAK_ICV_COLOR_CODE(0x0, 0x3FF, 0x1FE)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color orange red
 */
#define PEAK_ICV_COLOR_ORANGE_RED_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x11D, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dark olive green
 */
#define PEAK_ICV_COLOR_DARK_OLIVE_GREEN_10 PEAK_ICV_COLOR_CODE(0x156, 0x21B, 0x2F)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color pink
 */
#define PEAK_ICV_COLOR_PINK_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x180, 0x18B)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cadet blue
 */
#define PEAK_ICV_COLOR_CADET_BLUE_10 PEAK_ICV_COLOR_CODE(0x17E, 0x27C, 0x280)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color goldenrod
 */
#define PEAK_ICV_COLOR_GOLDENROD_10 PEAK_ICV_COLOR_CODE(0x1DA, 0x1A5, 0x20)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color orange
 */
#define PEAK_ICV_COLOR_ORANGE_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x1A5, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color gold
 */
#define PEAK_ICV_COLOR_GOLD_10 PEAK_ICV_COLOR_CODE(0x3FF, 0x1D7, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color forest green
 */
#define PEAK_ICV_COLOR_FOREST_GREEN_10 PEAK_ICV_COLOR_CODE(0x56, 0x22B, 0x56)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cornflower blue
 */
#define PEAK_ICV_COLOR_CORNFLOWER_BLUE_10 PEAK_ICV_COLOR_CODE(0x190, 0x259, 0x3ED)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color navy
 */
#define PEAK_ICV_COLOR_NAVY_10 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0x140)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color turquoise
 */
#define PEAK_ICV_COLOR_TURQUOISE_10 PEAK_ICV_COLOR_CODE(0x104, 0x360, 0x340)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dark slate blue
 */
#define PEAK_ICV_COLOR_DARK_SLATE_BLUE_10 PEAK_ICV_COLOR_CODE(0x120, 0xF7, 0x22B)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light blue
 */
#define PEAK_ICV_COLOR_LIGHT_BLUE_10 PEAK_ICV_COLOR_CODE(0x2B5, 0x368, 0x3A6)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color indian red
 */
#define PEAK_ICV_COLOR_INDIAN_RED_10 PEAK_ICV_COLOR_CODE(0x269, 0x11C, 0x11C)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color violet red
 */
#define PEAK_ICV_COLOR_VIOLET_RED_10 PEAK_ICV_COLOR_CODE(0x280, 0x50, 0x160)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light steel blue
 */
#define PEAK_ICV_COLOR_LIGHT_STEEL_BLUE_10 PEAK_ICV_COLOR_CODE(0x2B0, 0x3E8, 0x37E)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color medium blue
 */
#define PEAK_ICV_COLOR_MEDIUM_BLUE_10 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0x2A5)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color khaki
 */
#define PEAK_ICV_COLOR_KHAKI_10 PEAK_ICV_COLOR_CODE(0x3DF, 0x3E8, 0x2B0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color violet
 */
#define PEAK_ICV_COLOR_VIOLET_10 PEAK_ICV_COLOR_CODE(0x3EE, 0x2A5, 0x3EE)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color firebrick
 */
#define PEAK_ICV_COLOR_FIREBRICK_10 PEAK_ICV_COLOR_CODE(0x2B2, 0x22B, 0x22B)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color midnight blue
 */
#define PEAK_ICV_COLOR_MIDNIGHT_BLUE_10 PEAK_ICV_COLOR_CODE(0x19, 0x19, 0x2A5)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color black
 */
#define PEAK_ICV_COLOR_BLACK_12 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color white
 */
#define PEAK_ICV_COLOR_WHITE_12 PEAK_ICV_COLOR_CODE(0xFFF, 0xFFF, 0xFFF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color red
 */
#define PEAK_ICV_COLOR_RED_12 PEAK_ICV_COLOR_CODE(0xFFF, 0x0, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color green
 */
#define PEAK_ICV_COLOR_GREEN_12 PEAK_ICV_COLOR_CODE(0x0, 0xFFF, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color blue
 */
#define PEAK_ICV_COLOR_BLUE_12 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0xFFF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dim gray
 */
#define PEAK_ICV_COLOR_DIM_GRAY_12 PEAK_ICV_COLOR_CODE(0xAAA, 0xAAA, 0xAAA)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color gray
 */
#define PEAK_ICV_COLOR_GRAY_12 PEAK_ICV_COLOR_CODE(0x800, 0x800, 0x800)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light gray
 */
#define PEAK_ICV_COLOR_LIGHT_GRAY_12 PEAK_ICV_COLOR_CODE(0xD55, 0xD55, 0xD55)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cyan
 */
#define PEAK_ICV_COLOR_CYAN_12 PEAK_ICV_COLOR_CODE(0x0, 0xFFF, 0xFFF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color magenta
 */
#define PEAK_ICV_COLOR_MAGENTA_12 PEAK_ICV_COLOR_CODE(0xFFF, 0x0, 0xFFF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color yellow
 */
#define PEAK_ICV_COLOR_YELLOW_12 PEAK_ICV_COLOR_CODE(0xFFF, 0xFFF, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color medium slate blue
 */
#define PEAK_ICV_COLOR_MEDIUM_SLATE_BLUE_12 PEAK_ICV_COLOR_CODE(0x1FFF, 0x1FFF, 0x3FF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color coral
 */
#define PEAK_ICV_COLOR_CORAL_12 PEAK_ICV_COLOR_CODE(0xFFF, 0x7FF, 0x700)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color slate blue
 */
#define PEAK_ICV_COLOR_SLATE_BLUE_12 PEAK_ICV_COLOR_CODE(0x1AAA, 0x1AAA, 0x3FF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color spring green
 */
#define PEAK_ICV_COLOR_SPRING_GREEN_12 PEAK_ICV_COLOR_CODE(0x0, 0xFFF, 0x7FF)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color orange red
 */
#define PEAK_ICV_COLOR_ORANGE_RED_12 PEAK_ICV_COLOR_CODE(0xFFF, 0x2B5, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dark olive green
 */
#define PEAK_ICV_COLOR_DARK_OLIVE_GREEN_12 PEAK_ICV_COLOR_CODE(0x555, 0x7FF, 0x555)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color pink
 */
#define PEAK_ICV_COLOR_PINK_12 PEAK_ICV_COLOR_CODE(0xFFF, 0x960, 0x960)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cadet blue
 */
#define PEAK_ICV_COLOR_CADET_BLUE_12 PEAK_ICV_COLOR_CODE(0x5D5, 0x9D5, 0xA00)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color goldenrod
 */
#define PEAK_ICV_COLOR_GOLDENROD_12 PEAK_ICV_COLOR_CODE(0xDA5, 0xA50, 0x200)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color orange
 */
#define PEAK_ICV_COLOR_ORANGE_12 PEAK_ICV_COLOR_CODE(0xFFF, 0xA50, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color gold
 */
#define PEAK_ICV_COLOR_GOLD_12 PEAK_ICV_COLOR_CODE(0xFFF, 0xD70, 0x0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color forest green
 */
#define PEAK_ICV_COLOR_FOREST_GREEN_12 PEAK_ICV_COLOR_CODE(0x550, 0x9D5, 0x550)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color cornflower blue
 */
#define PEAK_ICV_COLOR_CORNFLOWER_BLUE_12 PEAK_ICV_COLOR_CODE(0x960, 0xD60, 0x9F0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color navy
 */
#define PEAK_ICV_COLOR_NAVY_12 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0x550)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color turquoise
 */
#define PEAK_ICV_COLOR_TURQUOISE_12 PEAK_ICV_COLOR_CODE(0x190, 0x6D0, 0x680)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color dark slate blue
 */
#define PEAK_ICV_COLOR_DARK_SLATE_BLUE_12 PEAK_ICV_COLOR_CODE(0x299, 0x1CC, 0x555)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light blue
 */
#define PEAK_ICV_COLOR_LIGHT_BLUE_12 PEAK_ICV_COLOR_CODE(0x555, 0x999, 0xAA0)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color indian red
 */
#define PEAK_ICV_COLOR_INDIAN_RED_12 PEAK_ICV_COLOR_CODE(0xCCC, 0x444, 0x444)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color violet red
 */
#define PEAK_ICV_COLOR_VIOLET_RED_12 PEAK_ICV_COLOR_CODE(0xD00, 0x290, 0x960)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color light steel blue
 */
#define PEAK_ICV_COLOR_LIGHT_STEEL_BLUE_12 PEAK_ICV_COLOR_CODE(0xD00, 0xF80, 0xD70)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color medium blue
 */
#define PEAK_ICV_COLOR_MEDIUM_BLUE_12 PEAK_ICV_COLOR_CODE(0x0, 0x0, 0xAA5)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color khaki
 */
#define PEAK_ICV_COLOR_KHAKI_12 PEAK_ICV_COLOR_CODE(0xBBF, 0x9F0, 0xD00)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color violet
 */
#define PEAK_ICV_COLOR_VIOLET_12 PEAK_ICV_COLOR_CODE(0xD70, 0x555, 0xD70)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color firebrick
 */
#define PEAK_ICV_COLOR_FIREBRICK_12 PEAK_ICV_COLOR_CODE(0xD99, 0x955, 0x955)

/*!
 * \ingroup ids_peak_icv_c_painting
 * \brief Color midnight blue
 */
#define PEAK_ICV_COLOR_MIDNIGHT_BLUE_12 PEAK_ICV_COLOR_CODE(0x33, 0x33, 0xAA5)


#define PEAK_ICV_COLOR_BLACK             PEAK_ICV_COLOR_BLACK_8
#define PEAK_ICV_COLOR_WHITE             PEAK_ICV_COLOR_WHITE_8
#define PEAK_ICV_COLOR_RED               PEAK_ICV_COLOR_RED_8
#define PEAK_ICV_COLOR_GREEN             PEAK_ICV_COLOR_GREEN_8
#define PEAK_ICV_COLOR_BLUE              PEAK_ICV_COLOR_BLUE_8
#define PEAK_ICV_COLOR_DIM_GRAY          PEAK_ICV_COLOR_DIM_GRAY_8
#define PEAK_ICV_COLOR_GRAY              PEAK_ICV_COLOR_GRAY_8
#define PEAK_ICV_COLOR_LIGHT_GRAY        PEAK_ICV_COLOR_LIGHT_GRAY_8
#define PEAK_ICV_COLOR_CYAN              PEAK_ICV_COLOR_CYAN_8
#define PEAK_ICV_COLOR_MAGENTA           PEAK_ICV_COLOR_MAGENTA_8
#define PEAK_ICV_COLOR_YELLOW            PEAK_ICV_COLOR_YELLOW_8
#define PEAK_ICV_COLOR_MEDIUM_SLATE_BLUE PEAK_ICV_COLOR_MEDIUM_SLATE_BLUE_8
#define PEAK_ICV_COLOR_CORAL             PEAK_ICV_COLOR_CORAL_8
#define PEAK_ICV_COLOR_SLATE_BLUE        PEAK_ICV_COLOR_SLATE_BLUE_8
#define PEAK_ICV_COLOR_SPRING_GREEN      PEAK_ICV_COLOR_SPRING_GREEN_8
#define PEAK_ICV_COLOR_ORANGE_RED        PEAK_ICV_COLOR_ORANGE_RED_8
#define PEAK_ICV_COLOR_DARK_OLIVE_GREEN  PEAK_ICV_COLOR_DARK_OLIVE_GREEN_8
#define PEAK_ICV_COLOR_PINK              PEAK_ICV_COLOR_PINK_8
#define PEAK_ICV_COLOR_CADET_BLUE        PEAK_ICV_COLOR_CADET_BLUE_8
#define PEAK_ICV_COLOR_GOLDENROD         PEAK_ICV_COLOR_GOLDENROD_8
#define PEAK_ICV_COLOR_ORANGE            PEAK_ICV_COLOR_ORANGE_8
#define PEAK_ICV_COLOR_GOLD              PEAK_ICV_COLOR_GOLD_8
#define PEAK_ICV_COLOR_FOREST_GREEN      PEAK_ICV_COLOR_FOREST_GREEN_8
#define PEAK_ICV_COLOR_CORNFLOWER_BLUE   PEAK_ICV_COLOR_CORNFLOWER_BLUE_8
#define PEAK_ICV_COLOR_NAVY              PEAK_ICV_COLOR_NAVY_8
#define PEAK_ICV_COLOR_TURQUOISE         PEAK_ICV_COLOR_TURQUOISE_8
#define PEAK_ICV_COLOR_DARK_SLATE_BLUE   PEAK_ICV_COLOR_DARK_SLATE_BLUE_8
#define PEAK_ICV_COLOR_LIGHT_BLUE        PEAK_ICV_COLOR_LIGHT_BLUE_8
#define PEAK_ICV_COLOR_INDIAN_RED        PEAK_ICV_COLOR_INDIAN_RED_8
#define PEAK_ICV_COLOR_VIOLET_RED        PEAK_ICV_COLOR_VIOLET_RED_8
#define PEAK_ICV_COLOR_LIGHT_STEEL_BLUE  PEAK_ICV_COLOR_LIGHT_STEEL_BLUE_8
#define PEAK_ICV_COLOR_MEDIUM_BLUE       PEAK_ICV_COLOR_MEDIUM_BLUE_8
#define PEAK_ICV_COLOR_KHAKI             PEAK_ICV_COLOR_KHAKI_8
#define PEAK_ICV_COLOR_VIOLET            PEAK_ICV_COLOR_VIOLET_8
#define PEAK_ICV_COLOR_FIREBRICK         PEAK_ICV_COLOR_FIREBRICK_8
#define PEAK_ICV_COLOR_MIDNIGHT_BLUE     PEAK_ICV_COLOR_MIDNIGHT_BLUE_8
