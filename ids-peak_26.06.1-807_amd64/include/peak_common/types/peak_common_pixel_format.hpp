/*!
 * \file    peak_common_pixel_format.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * \brief   Enum holding the possible pixel format names.
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common/types/geometry/peak_common_size.hpp>
#include <peak_common/types/peak_common_channel.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common_c/types/peak_common_pixel_format.h>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

// helper to suppress c enum deprecation warnings
#define PEAK_COMMON_CREATE_DEPRECATED_HELPER(SUFFIX, CONST)  \
    constexpr uint64_t DeprecatedHelperGet##SUFFIX##CEnumValue() \
    {                                                            \
        return CPixelFormatCast(CONST);                          \
    }

namespace peak
{
namespace common
{
namespace detail
{
constexpr uint64_t CPixelFormatCast(peak_common_pixel_format pixelFormat) noexcept
{
    return static_cast<uint32_t>(static_cast<std::underlying_type_t<peak_common_pixel_format>>(pixelFormat));
}

PEAK_COMMON_BEGIN_DISABLE_DEPRECATED_WARNINGS
PEAK_COMMON_CREATE_DEPRECATED_HELPER(Mono32FIDS, PEAK_COMMON_PIXEL_FORMAT_MONO_32F_IDS)
PEAK_COMMON_CREATE_DEPRECATED_HELPER(RGB32FIDS, PEAK_COMMON_PIXEL_FORMAT_RGB_32F_IDS)
PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS

} // namespace detail

// clang-format off
/*!
 * \ingroup ids_peak_common_types
 * \brief Enum listing all supported pixel formats and their internal IDs.
 *
 * Each enumerator represents a specific pixel layout and bit depth,
 * used for interpreting raw image data correctly.
 *
 * \since ids_peak_common 1.0
 */
enum class PixelFormat : uint64_t
{
    BayerGR8 = PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_8,                                                                        //!< BayerGR  8-Bit pixel format
    BayerGR10 = PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10,                                                                      //!< BayerGR 10-Bit pixel format
    BayerGR12 = PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12,                                                                      //!< BayerGR 12-Bit pixel format

    BayerRG8 = PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_8,                                                                        //!< BayerRG  8-Bit pixel format
    BayerRG10 = PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10,                                                                      //!< BayerRG 10-Bit pixel format
    BayerRG12 = PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12,                                                                      //!< BayerRG 12-Bit pixel format

    BayerGB8 = PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_8,                                                                        //!< BayerGB  8-Bit pixel format
    BayerGB10 = PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10,                                                                      //!< BayerGB 10-Bit pixel format
    BayerGB12 = PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12,                                                                      //!< BayerGB 12-Bit pixel format

    BayerBG8 = PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_8,                                                                        //!< BayerBG  8-Bit pixel format
    BayerBG10 = PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10,                                                                      //!< BayerBG 10-Bit pixel format
    BayerBG12 = PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12,                                                                      //!< BayerBG 12-Bit pixel format

    Mono8 = PEAK_COMMON_PIXEL_FORMAT_MONO_8,                                                                               //!< Mono     8-Bit pixel format
    Mono10 = PEAK_COMMON_PIXEL_FORMAT_MONO_10,                                                                             //!< Mono    10-Bit pixel format
    Mono12 = PEAK_COMMON_PIXEL_FORMAT_MONO_12,                                                                             //!< Mono    12-Bit pixel format
    Mono16 = PEAK_COMMON_PIXEL_FORMAT_MONO_16,                                                                             //!< Mono    16-Bit pixel format
    Mono32f = PEAK_COMMON_PIXEL_FORMAT_MONO_32F,                                                                           //!< Mono    32-Bit float pixel format

    Confidence8 = PEAK_COMMON_PIXEL_FORMAT_CONFIDENCE_8,                                                                   //!< Confidence  8-Bit format
    Confidence16 = PEAK_COMMON_PIXEL_FORMAT_CONFIDENCE_16,                                                                 //!< Confidence 16-Bit format

    Coord3D_C8 = PEAK_COMMON_PIXEL_FORMAT_COORD3D_C8,                                                                      //!< 3D coordinate C  8-Bit format
    Coord3D_C16 = PEAK_COMMON_PIXEL_FORMAT_COORD3D_C16,                                                                    //!< 3D coordinate C 16-Bit format
    Coord3D_C32f = PEAK_COMMON_PIXEL_FORMAT_COORD3D_C32F,                                                                  //!< 3D coordinate C 32-Bit float format

    Coord3D_ABC32f = PEAK_COMMON_PIXEL_FORMAT_COORD3D_ABC32F,                                                              //!< 3D coordinates A, B, C 32-Bit float format

    YUV420_8_YY_UV_SemiplanarIDS = PEAK_COMMON_PIXEL_FORMAT_YUV420_8_YY_UV_SemiplanarIDS,                                  //!< YUV4:2:0 8-Bit YY/UV semiplanar (IDS)
    YUV420_8_YY_VU_SemiplanarIDS = PEAK_COMMON_PIXEL_FORMAT_YUV420_8_YY_VU_SemiplanarIDS,                                  //!< YUV4:2:0 8-Bit YY/VU semiplanar (IDS)

    YUV422_8_UYVY = PEAK_COMMON_PIXEL_FORMAT_YUV422_8_UYVY,                                                                //!< UYVY 4:2:2 8-Bit format

    RGB8 = PEAK_COMMON_PIXEL_FORMAT_RGB_8,                                                                                 //!< RGB      8-Bit pixel format
    RGB10 = PEAK_COMMON_PIXEL_FORMAT_RGB_10,                                                                               //!< RGB     10-Bit pixel format
    RGB12 = PEAK_COMMON_PIXEL_FORMAT_RGB_12,                                                                               //!< RGB     12-Bit pixel format
    RGB32f = PEAK_COMMON_PIXEL_FORMAT_RGB_32F,                                                                             //!< RGB     32-Bit float pixel format

    BGR8 = PEAK_COMMON_PIXEL_FORMAT_BGR_8,                                                                                 //!< BGR      8-Bit pixel format
    BGR10 = PEAK_COMMON_PIXEL_FORMAT_BGR_10,                                                                               //!< BGR     10-Bit pixel format
    BGR12 = PEAK_COMMON_PIXEL_FORMAT_BGR_12,                                                                               //!< BGR     12-Bit pixel format

    RGBa8 = PEAK_COMMON_PIXEL_FORMAT_RGBA_8,                                                                               //!< RGBA     8-Bit pixel format
    RGBa10 = PEAK_COMMON_PIXEL_FORMAT_RGBA_10,                                                                             //!< RGBA    10-Bit pixel format
    RGBa12 = PEAK_COMMON_PIXEL_FORMAT_RGBA_12,                                                                             //!< RGBA    12-Bit pixel format

    BGRa8 = PEAK_COMMON_PIXEL_FORMAT_BGRA_8,                                                                               //!< BGRA     8-Bit pixel format
    BGRa10 = PEAK_COMMON_PIXEL_FORMAT_BGRA_10,                                                                             //!< BGRA    10-Bit pixel format
    BGRa12 = PEAK_COMMON_PIXEL_FORMAT_BGRA_12,                                                                             //!< BGRA    12-Bit pixel format

    BayerBG10p = PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_PACKED,                                                              //!< BayerBG 10-Bit packed format
    BayerBG12p = PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_PACKED,                                                              //!< BayerBG 12-Bit packed format

    BayerGB10p = PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_PACKED,                                                              //!< BayerGB 10-Bit packed format
    BayerGB12p = PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_PACKED,                                                              //!< BayerGB 12-Bit packed format

    BayerGR10p = PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_PACKED,                                                              //!< BayerGR 10-Bit packed format
    BayerGR12p = PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_PACKED,                                                              //!< BayerGR 12-Bit packed format

    BayerRG10p = PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_PACKED,                                                              //!< BayerRG 10-Bit packed format
    BayerRG12p = PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_PACKED,                                                              //!< BayerRG 12-Bit packed format

    Mono10p = PEAK_COMMON_PIXEL_FORMAT_MONO_10_PACKED,                                                                     //!< Mono    10-Bit packed format
    Mono12p = PEAK_COMMON_PIXEL_FORMAT_MONO_12_PACKED,                                                                     //!< Mono    12-Bit packed format

    RGB10p32 = PEAK_COMMON_PIXEL_FORMAT_RGB_10_PACKED_32,                                                                  //!< RGB     10-Bit packed 32-bit format
    BGR10p32 = PEAK_COMMON_PIXEL_FORMAT_BGR_10_PACKED_32,                                                                  //!< BGR     10-Bit packed 32-bit format

    BayerRG10g40IDS = PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_GROUPED_40_IDS,                                                 //!< BayerRG 10-Bit grouped 40-bit (IDS)
    BayerGB10g40IDS = PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_GROUPED_40_IDS,                                                 //!< BayerGB 10-Bit grouped 40-bit (IDS)
    BayerGR10g40IDS = PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_GROUPED_40_IDS,                                                 //!< BayerGR 10-Bit grouped 40-bit (IDS)
    BayerBG10g40IDS = PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_GROUPED_40_IDS,                                                 //!< BayerBG 10-Bit grouped 40-bit (IDS)

    BayerRG12g24IDS = PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_GROUPED_24_IDS,                                                 //!< BayerRG 12-Bit grouped 24-bit (IDS)
    BayerGB12g24IDS = PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_GROUPED_24_IDS,                                                 //!< BayerGB 12-Bit grouped 24-bit (IDS)
    BayerGR12g24IDS = PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_GROUPED_24_IDS,                                                 //!< BayerGR 12-Bit grouped 24-bit (IDS)
    BayerBG12g24IDS = PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_GROUPED_24_IDS,                                                 //!< BayerBG 12-Bit grouped 24-bit (IDS)

    Mono10g40IDS = PEAK_COMMON_PIXEL_FORMAT_MONO_10_GROUPED_40_IDS,                                                        //!< Mono    10-Bit grouped 40-bit (IDS)
    Mono12g24IDS = PEAK_COMMON_PIXEL_FORMAT_MONO_12_GROUPED_24_IDS,                                                        //!< Mono    12-Bit grouped 24-bit (IDS)

    Mono32fIDS PEAK_COMMON_DEPRECATED_ENUM_MSG("This value will be removed in a future Version. Use Mono32f instead.") = detail::DeprecatedHelperGetMono32FIDSCEnumValue(), //!< Mono 32-Bit float format (IDS)
    RGB32fIDS PEAK_COMMON_DEPRECATED_ENUM_MSG("This value will be removed in a future Version. Use RGB32fIDS instead.") = detail::DeprecatedHelperGetRGB32FIDSCEnumValue(), //!< RGB  32-Bit float format (IDS)

    Mono10g40IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_10_GROUPED_40_IDS_INTERLEAVED_A_B),        //!< Mono    10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    BayerRG10g40IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_GROUPED_40_IDS_INTERLEAVED_A_B), //!< BayerRG 10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    BayerBG10g40IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_GROUPED_40_IDS_INTERLEAVED_A_B), //!< BayerBG 10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    BayerGR10g40IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_GROUPED_40_IDS_INTERLEAVED_A_B), //!< BayerGR 10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    BayerGB10g40IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_GROUPED_40_IDS_INTERLEAVED_A_B), //!< BayerGB 10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    Mono12g24IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_12_GROUPED_24_IDS_INTERLEAVED_A_B),        //!< Mono    12-Bit grouped 24-bit (IDS) line Interleaved Components A, B
    BayerRG12g24IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_GROUPED_24_IDS_INTERLEAVED_A_B), //!< BayerRG 10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    BayerBG12g24IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_GROUPED_24_IDS_INTERLEAVED_A_B), //!< BayerBG 10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    BayerGR12g24IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_GROUPED_24_IDS_INTERLEAVED_A_B), //!< BayerGR 10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    BayerGB12g24IDS_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_GROUPED_24_IDS_INTERLEAVED_A_B), //!< BayerGB 10-Bit grouped 40-bit (IDS) line Interleaved Components A, B
    Mono8_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_8_INTERLEAVED_A_B),                               //!< Mono     8-Bit pixel format line Interleaved Components A, B
    BayerRG8_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_8_INTERLEAVED_A_B),                        //!< BayerRG  8-Bit pixel format line Interleaved Components A, B
    BayerBG8_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_8_INTERLEAVED_A_B),                        //!< BayerBG  8-Bit pixel format line Interleaved Components A, B
    BayerGR8_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_8_INTERLEAVED_A_B),                        //!< BayerGR  8-Bit pixel format line Interleaved Components A, B
    BayerGB8_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_8_INTERLEAVED_A_B),                        //!< BayerGB  8-Bit pixel format line Interleaved Components A, B
    Mono10_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_10_INTERLEAVED_A_B),                             //!< Mono    10-Bit pixel format line Interleaved Components A, B
    BayerRG10_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_INTERLEAVED_A_B),                      //!< BayerRG 10-Bit pixel format line Interleaved Components A, B
    BayerBG10_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_INTERLEAVED_A_B),                      //!< BayerBG 10-Bit pixel format line Interleaved Components A, B
    BayerGR10_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_INTERLEAVED_A_B),                      //!< BayerGR 10-Bit pixel format line Interleaved Components A, B
    BayerGB10_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_INTERLEAVED_A_B),                      //!< BayerGB 10-Bit pixel format line Interleaved Components A, B
    Mono12_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_12_INTERLEAVED_A_B),                             //!< Mono    12-Bit pixel format line Interleaved Components A, B
    BayerRG12_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_INTERLEAVED_A_B),                      //!< BayerRG 12-Bit pixel format line Interleaved Components A, B
    BayerBG12_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_INTERLEAVED_A_B),                      //!< BayerBG 12-Bit pixel format line Interleaved Components A, B
    BayerGR12_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_INTERLEAVED_A_B),                      //!< BayerGR 12-Bit pixel format line Interleaved Components A, B
    BayerGB12_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_INTERLEAVED_A_B),                      //!< BayerGB 12-Bit pixel format line Interleaved Components A, B
    Mono10p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_10_PACKED_INTERLEAVED_A_B),                     //!< Mono    10-Bit packed format line Interleaved Components A, B
    BayerRG10p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_PACKED_INTERLEAVED_A_B),              //!< BayerRG 10-Bit packed format line Interleaved Components A, B
    BayerBG10p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_PACKED_INTERLEAVED_A_B),              //!< BayerBG 10-Bit packed format line Interleaved Components A, B
    BayerGR10p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_PACKED_INTERLEAVED_A_B),              //!< BayerGR 10-Bit packed format line Interleaved Components A, B
    BayerGB10p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_PACKED_INTERLEAVED_A_B),              //!< BayerGB 10-Bit packed format line Interleaved Components A, B
    Mono12p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_12_PACKED_INTERLEAVED_A_B),                     //!< Mono    12-Bit packed format line Interleaved Components A, B
    BayerRG12p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_PACKED_INTERLEAVED_A_B),              //!< BayerRG 12-Bit packed format line Interleaved Components A, B
    BayerBG12p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_PACKED_INTERLEAVED_A_B),              //!< BayerBG 12-Bit packed format line Interleaved Components A, B
    BayerGR12p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_PACKED_INTERLEAVED_A_B),              //!< BayerGR 12-Bit packed format line Interleaved Components A, B
    BayerGB12p_I_A_B = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_PACKED_INTERLEAVED_A_B),              //!< BayerGB 12-Bit packed format line Interleaved Components A, B
    Mono8_I_AB_CD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_8_INTERLEAVED_AB_CD),                           //!< Mono     8-Bit pixel format pixel Interleaved Components A, B, C, D
    Mono10_I_AB_CD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_10_INTERLEAVED_AB_CD),                         //!< Mono    10-Bit pixel format pixel Interleaved Components A, B, C, D
    Mono12_I_AB_CD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_12_INTERLEAVED_AB_CD),                         //!< Mono    12-Bit pixel format pixel Interleaved Components A, B, C, D
    Mono10p_I_AB_CD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_10_PACKED_INTERLEAVED_AB_CD),                 //!< Mono    10-Bit packed format pixel Interleaved Components A, B, C, D
    Mono12p_I_AB_CD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_12_PACKED_INTERLEAVED_AB_CD),                 //!< Mono    12-Bit packed format pixel Interleaved Components A, B, C, D
    Mono10g40IDS_I_AB_CD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_10_GROUPED_40_IDS_INTERLEAVED_AB_CD),    //!< Mono    10-Bit grouped 40-bit (IDS) pixel Interleaved Components A, B, C, D
    Mono12g24IDS_I_AB_CD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_12_GROUPED_24_IDS_INTERLEAVED_AB_CD),    //!< Mono    12-Bit grouped 24-bit (IDS) pixel Interleaved Components A, B, C, D

    Mono10_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_10_AB),                                             //!< Mono    10-Bit pixel format Components A, B
    BayerRG10_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_AB),                                      //!< BayerRG 10-Bit pixel format Components A, B
    BayerBG10_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_AB),                                      //!< BayerBG 10-Bit pixel format Components A, B
    BayerGR10_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_AB),                                      //!< BayerGR 10-Bit pixel format Components A, B
    BayerGB10_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_AB),                                      //!< BayerGB 10-Bit pixel format Components A, B
    Mono12_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_12_AB),                                             //!< Mono    12-Bit pixel format Components A, B
    BayerRG12_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_AB),                                      //!< BayerRG 12-Bit pixel format Components A, B
    BayerBG12_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_AB),                                      //!< BayerBG 12-Bit pixel format Components A, B
    BayerGR12_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_AB),                                      //!< BayerGR 12-Bit pixel format Components A, B
    BayerGB12_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_AB),                                      //!< BayerGB 12-Bit pixel format Components A, B
    Mono8_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_8_AB),                                               //!< Mono     8-Bit pixel format Components A, B
    BayerRG8_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_8_AB),                                        //!< BayerRG  8-Bit pixel format Components A, B
    BayerBG8_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_8_AB),                                        //!< BayerBG  8-Bit pixel format Components A, B
    BayerGR8_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_8_AB),                                        //!< BayerGR  8-Bit pixel format Components A, B
    BayerGB8_AB = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_8_AB),                                        //!< BayerGB  8-Bit pixel format Components A, B
    Mono8_ABCD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_8_ABCD),                                           //!< Mono     8-Bit pixel format Components A, B, C, D
    Mono10_ABCD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_10_ABCD),                                         //!< Mono    10-Bit pixel format Components A, B, C, D
    Mono12_ABCD = detail::CPixelFormatCast(PEAK_COMMON_PIXEL_FORMAT_MONO_12_ABCD),                                         //!< Mono    12-Bit pixel format Components A, B, C, D
};
// clang-format on

namespace detail
{
constexpr PixelFormat CPixelFormatToCppPixelFormat(peak_common_pixel_format pixelFormat) noexcept
{
    return static_cast<PixelFormat>(CPixelFormatCast(pixelFormat));
}

constexpr peak_common_pixel_format CppPixelFormatToCPixelFormat(PixelFormat pixelFormat) noexcept
{
    return static_cast<peak_common_pixel_format>(static_cast<uint32_t>(pixelFormat));
}
} // namespace detail

/*!
 * \ingroup ids_peak_common_types
 * \brief Provides information and utility functions for pixel formats.
 *
 * The PixelFormatInfo class offers methods to query characteristics of specific pixel formats,
 * such as value ranges, storage sizes, and channel configurations.
 *
 * \since ids_peak_common 1.0
 */
class PixelFormatInfo
{
public:
    /*!
     * \brief Constructs a PixelFormatInfo object for the specified pixel format.
     *
     * \param pixelFormat The pixel format to describe.
     * \since ids_peak_common 1.0
     */
    explicit PixelFormatInfo(peak::common::PixelFormat pixelFormat);

    /*!
     * \brief Constructs a PixelFormatInfo object from the name of a pixel format.
     *
     * \param name The name of the pixel format.
     * \since ids_peak_common 1.0
     */
    explicit PixelFormatInfo(const std::string& name);

    /*!
     * \brief Returns the minimum possible value per channel for the pixel format.
     *
     * \tparam T The value type (default is size_t).
     * \return The minimum value per channel.
     * \since ids_peak_common 1.0
     */
    template <typename T = size_t>
    PEAK_COMMON_NO_DISCARD T GetMinimumValuePerChannel() const;

    /*!
     * \brief Returns the maximum possible value per channel for the pixel format.
     *
     * \tparam T The value type (default is size_t).
     * \return The maximum value per channel.
     * \since ids_peak_common 1.0
     */
    template <typename T = size_t>
    PEAK_COMMON_NO_DISCARD T GetMaximumValuePerChannel() const;

    /*!
     * \brief Returns the total number of bits used per pixel for storage.
     *
     * \return Bits per pixel used for storage.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetStorageBitsPerPixel() const;

    /*!
     * \brief Returns the number of bits used per channel for storage.
     *
     * \return Bits per channel used for storage.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetStorageBitsPerChannel() const;

    /*!
     * \brief Returns the human-readable name of the pixel format.
     *
     * \return Name of the pixel format.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD std::string GetName() const;

    /*!
     * \brief Returns the list of channels in the pixel format.
     *
     * \return A vector containing the channels present in the pixel format.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<Channel> GetChannels() const;

    /*!
     * \brief Returns the number of allocated bits per pixel.
     *
     * \return Number of allocated bits per pixel.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetAllocatedBitsPerPixel() const;

    /*!
     * \brief Checks whether the pixel format includes an intensity channel.
     *
     * \return True if an intensity channel is present, false otherwise.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool HasIntensityChannel() const;

    /*!
     * \brief Returns the index of a specific channel within the pixel format.
     *
     * \param channel The channel to locate.
     * \return The zero-based index of the channel.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetChannelIndex(Channel channel) const;

    /*!
     * \brief Returns the total number of channels in the pixel format.
     *
     * \return Number of channels.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetNumberOfChannels() const;

    /*!
     * \brief Checks whether the pixel format contains only a single channel.
     *
     * \return True if the pixel format is single-channel, false otherwise.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool IsSingleChannel() const;

    /*!
     * \brief Checks whether a specific channel is present in the pixel format.
     *
     * \param channel The channel to check for.
     * \return True if the channel exists in the pixel format, false otherwise.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool HasChannel(Channel channel) const;

    /*!
     * \brief Returns the underlying pixel format enumeration value.
     *
     * \return The pixel format.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::PixelFormat GetPixelFormat() const;

    /*!
     * \brief Calculates the memory size in bytes for a given image size.
     *
     * \param size The size of the image.
     * \return The total memory size in bytes.
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetSizeInBytes(const Size& size) const;

    /*!
     * \brief Returns whether the pixel format is packed.
     *
     * \return Bool whether format is packed
     * \since ids_peak_common 1.1
     */
    PEAK_COMMON_NO_DISCARD bool IsPacked() const;

    /*!
     * \brief Indicates whether the pixel format is interleaved.
     *
     * Interleaved pixel formats arrange multiple image streams in memory
     * using different patterns. The exact interleaving strategy depends
     * on the pixel format family:
     *
     * **Mono*_A_B**
     *     Images A and B alternate by row:
     *
     *     Memory row 1: Image A (row 1)
     *     Memory row 2: Image B (row 1)
     *     Memory row 3: Image A (row 2)
     *     Memory row 4: Image B (row 2)
     *     ...
     *
     * **Bayer*_A_B**
     *     Images A and B are grouped in pairs of rows:
     *
     *     Memory row 1: Image A (row 1)
     *     Memory row 2: Image A (row 2)
     *     Memory row 3: Image B (row 1)
     *     Memory row 4: Image B (row 2)
     *     Memory row 5: Image A (row 3)
     *     Memory row 6: Image A (row 4)
     *     Memory row 7: Image B (row 3)
     *     Memory row 8: Image B (row 4)
     *     ...
     *
     * **Mono*_AB_CD**
     *     Four image streams (A, B, C, D) are interleaved within each row:
     *
     *     Memory row 1: | A | B | A | B | A | B |
     *     Memory row 2: | C | D | C | D | C | D |
     *     Memory row 3: | A | B | A | B | A | B |
     *     Memory row 4: | C | D | C | D | C | D |
     *     ...
     * \since ids_peak_common 1.2
     */
    PEAK_COMMON_NO_DISCARD bool IsInterleaved() const;

    /*!
     * \brief Returns whether the pixel format uses floating points
     *
     * \return Bool whether format uses floating points
     * \since ids_peak_common 1.1
     */
    PEAK_COMMON_NO_DISCARD bool IsFloat() const;

    /*!
     * \brief Returns the unpacked pixel format for a packed pixel format.
     *
     * If the pixel format is already unpacked, the same format is returned.
     *
     * \return An unpacked pixel format
     * \since ids_peak_common 1.1
     */
    PEAK_COMMON_NO_DISCARD PixelFormat GetUnpackedPixelFormat() const;

private:
    peak::common::PixelFormat m_pixelFormat;
};

inline PixelFormatInfo::PixelFormatInfo(peak::common::PixelFormat pixelFormat)
    : m_pixelFormat{ pixelFormat }
{}

inline bool PixelFormatInfo::HasIntensityChannel() const
{
    return HasChannel(Channel::Intensity);
}

inline size_t PixelFormatInfo::GetChannelIndex(Channel channel) const
{
    const auto channels = this->GetChannels();
    const auto it = std::find(channels.cbegin(), channels.cend(), channel);
    if (it == channels.end())
    {
        throw InvalidParameterException("The given channel is not part of the pixel format " + GetName() + '!');
    }

    return static_cast<size_t>(std::distance(channels.begin(), it));
}

inline size_t PixelFormatInfo::GetNumberOfChannels() const
{
    return this->GetChannels().size();
}

inline bool PixelFormatInfo::IsSingleChannel() const
{
    return GetNumberOfChannels() == 1;
}

inline bool PixelFormatInfo::HasChannel(Channel channel) const
{
    const auto channels = this->GetChannels();
    return std::find(channels.cbegin(), channels.cend(), channel) != channels.cend();
}

inline peak::common::PixelFormat PixelFormatInfo::GetPixelFormat() const
{
    return m_pixelFormat;
}
} // namespace common 
} // namespace peak

#include <peak_common/types/detail/peak_common_pixel_format.ipp>
