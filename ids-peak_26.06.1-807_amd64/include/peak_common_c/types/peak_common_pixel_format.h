/*!
 * \file    peak_common_pixel_format.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-28
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>

// This silences -Wmicrosoft-enum-value
#    define PEAK_COMMON_PIXEL_FORMAT_CAST(x) static_cast<int32_t>(x)

extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>

// This silences -Wmicrosoft-enum-value
#    define PEAK_COMMON_PIXEL_FORMAT_CAST(x) (int32_t)(x)
#endif

#include <peak_common_c/detail/peak_common_defines.h>

/*!
 * \ingroup ids_peak_common_c_types
 * \enum peak_common_pixel_format
 * \brief Enum listing all supported pixel formats and their internal IDs.
 *
 * Each enumerator represents a specific pixel layout and bit depth,
 * used for interpreting raw image data correctly.
 *
 * \since ids_peak_common 1.0
 */
typedef enum peak_common_pixel_format
{
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_8 = 0x01080008,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10 = 0x0110000C,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12 = 0x01100010,

    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_8 = 0x01080009,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10 = 0x0110000D,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12 = 0x01100011,

    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_8 = 0x0108000A,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10 = 0x0110000E,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12 = 0x01100012,

    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_8 = 0x0108000B,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10 = 0x0110000F,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12 = 0x01100013,

    PEAK_COMMON_PIXEL_FORMAT_MONO_8 = 0x01080001,
    PEAK_COMMON_PIXEL_FORMAT_MONO_10 = 0x01100003,
    PEAK_COMMON_PIXEL_FORMAT_MONO_12 = 0x01100005,
    PEAK_COMMON_PIXEL_FORMAT_MONO_16 = 0x01100007,
    PEAK_COMMON_PIXEL_FORMAT_MONO_32F = 0x0120012F,

    PEAK_COMMON_PIXEL_FORMAT_CONFIDENCE_8 = 0x010800C6,
    PEAK_COMMON_PIXEL_FORMAT_CONFIDENCE_16 = 0x011000C7,

    PEAK_COMMON_PIXEL_FORMAT_COORD3D_C8 = 0x010800B1,
    PEAK_COMMON_PIXEL_FORMAT_COORD3D_C16 = 0x011000B8,
    PEAK_COMMON_PIXEL_FORMAT_COORD3D_C32F = 0x012000BF,

    PEAK_COMMON_PIXEL_FORMAT_COORD3D_ABC32F = 0x026000C0,

    PEAK_COMMON_PIXEL_FORMAT_YUV420_8_YY_UV_SemiplanarIDS = 0x420C0001,
    PEAK_COMMON_PIXEL_FORMAT_YUV420_8_YY_VU_SemiplanarIDS = 0x420C0002,

    PEAK_COMMON_PIXEL_FORMAT_YUV422_8_UYVY = 0x0210001F,

    PEAK_COMMON_PIXEL_FORMAT_RGB_8 = 0x02180014,
    PEAK_COMMON_PIXEL_FORMAT_RGB_10 = 0x02300018,
    PEAK_COMMON_PIXEL_FORMAT_RGB_12 = 0x0230001A,
    PEAK_COMMON_PIXEL_FORMAT_RGB_32F = 0x02600130,

    PEAK_COMMON_PIXEL_FORMAT_BGR_8 = 0x02180015,
    PEAK_COMMON_PIXEL_FORMAT_BGR_10 = 0x02300019,
    PEAK_COMMON_PIXEL_FORMAT_BGR_12 = 0x0230001B,

    PEAK_COMMON_PIXEL_FORMAT_RGBA_8 = 0x02200016,
    PEAK_COMMON_PIXEL_FORMAT_RGBA_10 = 0x0240005F,
    PEAK_COMMON_PIXEL_FORMAT_RGBA_12 = 0x02400061,

    PEAK_COMMON_PIXEL_FORMAT_BGRA_8 = 0x02200017,
    PEAK_COMMON_PIXEL_FORMAT_BGRA_10 = 0x0240004C,
    PEAK_COMMON_PIXEL_FORMAT_BGRA_12 = 0x0240004E,

    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_PACKED = 0x010A0052,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_PACKED = 0x010C0053,

    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_PACKED = 0x010A0054,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_PACKED = 0x010C0055,

    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_PACKED = 0x010A0056,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_PACKED = 0x010C0057,

    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_PACKED = 0x010A0058,
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_PACKED = 0x010C0059,

    PEAK_COMMON_PIXEL_FORMAT_MONO_10_PACKED = 0x010A0046,
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_PACKED = 0x010C0047,

    PEAK_COMMON_PIXEL_FORMAT_RGB_10_PACKED_32 = 0x0220001D,

    PEAK_COMMON_PIXEL_FORMAT_BGR_10_PACKED_32 = 0x0220001E,

    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_GROUPED_40_IDS = 0x40000001,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_GROUPED_40_IDS = 0x40000002,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_GROUPED_40_IDS = 0x40000003,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_GROUPED_40_IDS = 0x40000004,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_GROUPED_24_IDS = 0x40000011,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_GROUPED_24_IDS = 0x40000012,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_GROUPED_24_IDS = 0x40000013,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_GROUPED_24_IDS = 0x40000014,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_GROUPED_40_IDS = 0x4000000f,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_GROUPED_24_IDS = 0x4000001f,
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_32F_IDS PEAK_COMMON_DEPRECATED_ENUM_MSG(
        "This value will be removed in a future Version. Use PEAK_COMMON_PIXEL_FORMAT_MONO_32F instead.") =
        PEAK_COMMON_PIXEL_FORMAT_CAST(0x81200020),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_RGB_32F_IDS PEAK_COMMON_DEPRECATED_ENUM_MSG(
        "This value will be removed in a future Version. Use PEAK_COMMON_PIXEL_FORMAT_RGB_32F instead.") =
        PEAK_COMMON_PIXEL_FORMAT_CAST(0x82600021),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_GROUPED_40_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x9200000F),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_GROUPED_40_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92000001),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_GROUPED_40_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92000004),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_GROUPED_40_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92000003),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_GROUPED_40_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92000002),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_GROUPED_24_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x9200001F),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_GROUPED_24_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92000011),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_GROUPED_24_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92000014),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_GROUPED_24_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92000013),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_GROUPED_24_IDS_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92000012),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_8_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92080001),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_8_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92080009),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_8_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x9208000B),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_8_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92080008),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_8_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x9208000A),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92100003),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x9210000D),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x9210000F),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x9210000C),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x9210000E),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92100005),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92100011),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92100013),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92100010),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x92100012),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920A0046),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920A0058),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920A0052),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920A0056),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920A0054),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920C0047),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920C0059),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920C0053),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920C0057),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_PACKED_INTERLEAVED_A_B = PEAK_COMMON_PIXEL_FORMAT_CAST(0x920C0055),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_8_INTERLEAVED_AB_CD = PEAK_COMMON_PIXEL_FORMAT_CAST(0xB2080001),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_INTERLEAVED_AB_CD = PEAK_COMMON_PIXEL_FORMAT_CAST(0xB2100003),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_INTERLEAVED_AB_CD = PEAK_COMMON_PIXEL_FORMAT_CAST(0xB2100005),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_PACKED_INTERLEAVED_AB_CD = PEAK_COMMON_PIXEL_FORMAT_CAST(0xB20A0046),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_PACKED_INTERLEAVED_AB_CD = PEAK_COMMON_PIXEL_FORMAT_CAST(0xB20C0047),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_GROUPED_40_IDS_INTERLEAVED_AB_CD = PEAK_COMMON_PIXEL_FORMAT_CAST(0xB200000F),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_GROUPED_24_IDS_INTERLEAVED_AB_CD = PEAK_COMMON_PIXEL_FORMAT_CAST(0xB200001F),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81200022),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_10_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81100003),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_10_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81100004),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_10_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81100005),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_10_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81100006),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81100007),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_12_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81100008),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_12_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81100009),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_12_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x8110000a),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_12_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x8110000b),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_8_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x8110000c),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_RG_8_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x8110000d),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_BG_8_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x8110000e),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GR_8_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x8110000f),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_BAYER_GB_8_AB = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81100010),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_8_ABCD = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81200011),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_10_ABCD = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81400012),
    /*!
     * \attention This pixel format is preliminary, and its name and value may change in a future product version.
     */
    PEAK_COMMON_PIXEL_FORMAT_MONO_12_ABCD = PEAK_COMMON_PIXEL_FORMAT_CAST(0x81400013)
} peak_common_pixel_format;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
