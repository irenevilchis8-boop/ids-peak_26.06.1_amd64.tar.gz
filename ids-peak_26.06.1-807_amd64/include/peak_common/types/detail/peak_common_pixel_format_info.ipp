
/*!
 * \file    peak_common_pixel_format_info.ipp
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

inline PixelFormatInfo::PixelFormatInfo(const std::string& name)
{
    static const std::unordered_map<std::string, PixelFormat> map = {
        { detail::PixelFormatInfo<PixelFormat::BayerGR8>::Name(), PixelFormat::BayerGR8 },
        { detail::PixelFormatInfo<PixelFormat::BayerGR10>::Name(), PixelFormat::BayerGR10 },
        { detail::PixelFormatInfo<PixelFormat::BayerGR12>::Name(), PixelFormat::BayerGR12 },
        { detail::PixelFormatInfo<PixelFormat::BayerRG8>::Name(), PixelFormat::BayerRG8 },
        { detail::PixelFormatInfo<PixelFormat::BayerRG10>::Name(), PixelFormat::BayerRG10 },
        { detail::PixelFormatInfo<PixelFormat::BayerRG12>::Name(), PixelFormat::BayerRG12 },
        { detail::PixelFormatInfo<PixelFormat::BayerGB8>::Name(), PixelFormat::BayerGB8 },
        { detail::PixelFormatInfo<PixelFormat::BayerGB10>::Name(), PixelFormat::BayerGB10 },
        { detail::PixelFormatInfo<PixelFormat::BayerGB12>::Name(), PixelFormat::BayerGB12 },
        { detail::PixelFormatInfo<PixelFormat::BayerBG8>::Name(), PixelFormat::BayerBG8 },
        { detail::PixelFormatInfo<PixelFormat::BayerBG10>::Name(), PixelFormat::BayerBG10 },
        { detail::PixelFormatInfo<PixelFormat::BayerBG12>::Name(), PixelFormat::BayerBG12 },
        { detail::PixelFormatInfo<PixelFormat::Mono8>::Name(), PixelFormat::Mono8 },
        { detail::PixelFormatInfo<PixelFormat::Mono10>::Name(), PixelFormat::Mono10 },
        { detail::PixelFormatInfo<PixelFormat::Mono12>::Name(), PixelFormat::Mono12 },
        { detail::PixelFormatInfo<PixelFormat::Mono16>::Name(), PixelFormat::Mono16 },
        { detail::PixelFormatInfo<PixelFormat::Confidence8>::Name(), PixelFormat::Confidence8 },
        { detail::PixelFormatInfo<PixelFormat::Confidence16>::Name(), PixelFormat::Confidence16 },
        { detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::Name(), PixelFormat::Coord3D_C8 },
        { detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::Name(), PixelFormat::Coord3D_C16 },
        { detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::Name(), PixelFormat::Coord3D_C32f },
        { detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::Name(), PixelFormat::Coord3D_ABC32f },
        { detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::Name(), PixelFormat::YUV420_8_YY_UV_SemiplanarIDS },
        { detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::Name(), PixelFormat::YUV420_8_YY_VU_SemiplanarIDS },
        { detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::Name(), PixelFormat::YUV422_8_UYVY },
        { detail::PixelFormatInfo<PixelFormat::RGB8>::Name(), PixelFormat::RGB8 },
        { detail::PixelFormatInfo<PixelFormat::RGB10>::Name(), PixelFormat::RGB10 },
        { detail::PixelFormatInfo<PixelFormat::RGB12>::Name(), PixelFormat::RGB12 },
        { detail::PixelFormatInfo<PixelFormat::BGR8>::Name(), PixelFormat::BGR8 },
        { detail::PixelFormatInfo<PixelFormat::BGR10>::Name(), PixelFormat::BGR10 },
        { detail::PixelFormatInfo<PixelFormat::BGR12>::Name(), PixelFormat::BGR12 },
        { detail::PixelFormatInfo<PixelFormat::RGBa8>::Name(), PixelFormat::RGBa8 },
        { detail::PixelFormatInfo<PixelFormat::RGBa10>::Name(), PixelFormat::RGBa10 },
        { detail::PixelFormatInfo<PixelFormat::RGBa12>::Name(), PixelFormat::RGBa12 },
        { detail::PixelFormatInfo<PixelFormat::BGRa8>::Name(), PixelFormat::BGRa8 },
        { detail::PixelFormatInfo<PixelFormat::BGRa10>::Name(), PixelFormat::BGRa10 },
        { detail::PixelFormatInfo<PixelFormat::BGRa12>::Name(), PixelFormat::BGRa12 },
        { detail::PixelFormatInfo<PixelFormat::BayerBG10p>::Name(), PixelFormat::BayerBG10p },
        { detail::PixelFormatInfo<PixelFormat::BayerBG12p>::Name(), PixelFormat::BayerBG12p },
        { detail::PixelFormatInfo<PixelFormat::BayerGB10p>::Name(), PixelFormat::BayerGB10p },
        { detail::PixelFormatInfo<PixelFormat::BayerGB12p>::Name(), PixelFormat::BayerGB12p },
        { detail::PixelFormatInfo<PixelFormat::BayerGR10p>::Name(), PixelFormat::BayerGR10p },
        { detail::PixelFormatInfo<PixelFormat::BayerGR12p>::Name(), PixelFormat::BayerGR12p },
        { detail::PixelFormatInfo<PixelFormat::BayerRG10p>::Name(), PixelFormat::BayerRG10p },
        { detail::PixelFormatInfo<PixelFormat::BayerRG12p>::Name(), PixelFormat::BayerRG12p },
        { detail::PixelFormatInfo<PixelFormat::Mono10p>::Name(), PixelFormat::Mono10p },
        { detail::PixelFormatInfo<PixelFormat::Mono12p>::Name(), PixelFormat::Mono12p },
        { detail::PixelFormatInfo<PixelFormat::RGB10p32>::Name(), PixelFormat::RGB10p32 },
        { detail::PixelFormatInfo<PixelFormat::BGR10p32>::Name(), PixelFormat::BGR10p32 },
        { detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::Name(), PixelFormat::BayerRG10g40IDS },
        { detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::Name(), PixelFormat::BayerGB10g40IDS },
        { detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::Name(), PixelFormat::BayerGR10g40IDS },
        { detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::Name(), PixelFormat::BayerBG10g40IDS },
        { detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::Name(), PixelFormat::BayerRG12g24IDS },
        { detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::Name(), PixelFormat::BayerGB12g24IDS },
        { detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::Name(), PixelFormat::BayerGR12g24IDS },
        { detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::Name(), PixelFormat::BayerBG12g24IDS },
        { detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::Name(), PixelFormat::Mono10g40IDS },
        { detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::Name(), PixelFormat::Mono12g24IDS },
        { detail::PixelFormatInfo<PixelFormat::Mono32f>::Name(), PixelFormat::Mono32f },
        { detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::Name(), PixelFormat::Mono32fIDS },
        { detail::PixelFormatInfo<PixelFormat::RGB32f>::Name(), PixelFormat::RGB32f },
        { detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::Name(), PixelFormat::RGB32fIDS },
        { detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::Name(), PixelFormat::Mono10g40IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::Name(), PixelFormat::BayerRG10g40IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::Name(), PixelFormat::BayerBG10g40IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::Name(), PixelFormat::BayerGR10g40IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::Name(), PixelFormat::BayerGB10g40IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::Name(), PixelFormat::Mono12g24IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::Name(), PixelFormat::BayerRG12g24IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::Name(), PixelFormat::BayerBG12g24IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::Name(), PixelFormat::BayerGR12g24IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::Name(), PixelFormat::BayerGB12g24IDS_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::Name(), PixelFormat::Mono8_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::Name(), PixelFormat::BayerRG8_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::Name(), PixelFormat::BayerBG8_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::Name(), PixelFormat::BayerGR8_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::Name(), PixelFormat::BayerGB8_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::Name(), PixelFormat::Mono10_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::Name(), PixelFormat::BayerRG10_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::Name(), PixelFormat::BayerBG10_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::Name(), PixelFormat::BayerGR10_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::Name(), PixelFormat::BayerGB10_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::Name(), PixelFormat::Mono12_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::Name(), PixelFormat::BayerRG12_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::Name(), PixelFormat::BayerBG12_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::Name(), PixelFormat::BayerGR12_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::Name(), PixelFormat::BayerGB12_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::Name(), PixelFormat::Mono10p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::Name(), PixelFormat::BayerRG10p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::Name(), PixelFormat::BayerBG10p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::Name(), PixelFormat::BayerGR10p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::Name(), PixelFormat::BayerGB10p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::Name(), PixelFormat::Mono12p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::Name(), PixelFormat::BayerRG12p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::Name(), PixelFormat::BayerBG12p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::Name(), PixelFormat::BayerGR12p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::Name(), PixelFormat::BayerGB12p_I_A_B },
        { detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::Name(), PixelFormat::Mono8_I_AB_CD },
        { detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::Name(), PixelFormat::Mono10_I_AB_CD },
        { detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::Name(), PixelFormat::Mono12_I_AB_CD },
        { detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::Name(), PixelFormat::Mono10p_I_AB_CD },
        { detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::Name(), PixelFormat::Mono12p_I_AB_CD },
        { detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::Name(), PixelFormat::Mono10g40IDS_I_AB_CD },
        { detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::Name(), PixelFormat::Mono12g24IDS_I_AB_CD },
        { detail::PixelFormatInfo<PixelFormat::Mono10_AB>::Name(), PixelFormat::Mono10_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::Name(), PixelFormat::BayerRG10_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::Name(), PixelFormat::BayerBG10_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::Name(), PixelFormat::BayerGR10_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::Name(), PixelFormat::BayerGB10_AB },
        { detail::PixelFormatInfo<PixelFormat::Mono12_AB>::Name(), PixelFormat::Mono12_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::Name(), PixelFormat::BayerRG12_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::Name(), PixelFormat::BayerBG12_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::Name(), PixelFormat::BayerGR12_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::Name(), PixelFormat::BayerGB12_AB },
        { detail::PixelFormatInfo<PixelFormat::Mono8_AB>::Name(), PixelFormat::Mono8_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::Name(), PixelFormat::BayerRG8_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::Name(), PixelFormat::BayerBG8_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::Name(), PixelFormat::BayerGR8_AB },
        { detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::Name(), PixelFormat::BayerGB8_AB },
        { detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::Name(), PixelFormat::Mono8_ABCD },
        { detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::Name(), PixelFormat::Mono10_ABCD },
        { detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::Name(), PixelFormat::Mono12_ABCD },

    };

    const auto iter = map.find(name);
    if (iter == map.end())
    {
        throw InvalidParameterException("The given pixel format " + name + " is unknown!");
    }
    m_pixelFormat = iter->second;
}

     
inline size_t PixelFormatInfo::GetStorageBitsPerPixel() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::storageBitsPerPixel;
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::storageBitsPerPixel;
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::storageBitsPerPixel;
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::storageBitsPerPixel;
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::storageBitsPerPixel;
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::storageBitsPerPixel;
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::storageBitsPerPixel;
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::storageBitsPerPixel;
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::storageBitsPerPixel;
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::storageBitsPerPixel;
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::storageBitsPerPixel;
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::storageBitsPerPixel;
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::storageBitsPerPixel;
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::storageBitsPerPixel;
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::storageBitsPerPixel;
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::storageBitsPerPixel;
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::storageBitsPerPixel;
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::storageBitsPerPixel;
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::storageBitsPerPixel;
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::storageBitsPerPixel;
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::storageBitsPerPixel;
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::storageBitsPerPixel;
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::storageBitsPerPixel;
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::storageBitsPerPixel;
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::storageBitsPerPixel;
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::storageBitsPerPixel;
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::storageBitsPerPixel;
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::storageBitsPerPixel;
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::storageBitsPerPixel;
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::storageBitsPerPixel;
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::storageBitsPerPixel;
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::storageBitsPerPixel;
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::storageBitsPerPixel;
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::storageBitsPerPixel;
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::storageBitsPerPixel;
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::storageBitsPerPixel;
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::storageBitsPerPixel;
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::storageBitsPerPixel;
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::storageBitsPerPixel;
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::storageBitsPerPixel;
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::storageBitsPerPixel;
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::storageBitsPerPixel;
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::storageBitsPerPixel;
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::storageBitsPerPixel;
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::storageBitsPerPixel;
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::storageBitsPerPixel;
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::storageBitsPerPixel;
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::storageBitsPerPixel;
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::storageBitsPerPixel;
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::storageBitsPerPixel;
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::storageBitsPerPixel;
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::storageBitsPerPixel;
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::storageBitsPerPixel;
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::storageBitsPerPixel;
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::storageBitsPerPixel;
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::storageBitsPerPixel;
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::storageBitsPerPixel;
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::storageBitsPerPixel;
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::storageBitsPerPixel;
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::storageBitsPerPixel;
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::storageBitsPerPixel;
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::storageBitsPerPixel;
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::storageBitsPerPixel;
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::storageBitsPerPixel;
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::storageBitsPerPixel;
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::storageBitsPerPixel;
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::storageBitsPerPixel;
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::storageBitsPerPixel;
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::storageBitsPerPixel;
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::storageBitsPerPixel;
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::storageBitsPerPixel;
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::storageBitsPerPixel;
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::storageBitsPerPixel;
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::storageBitsPerPixel;
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::storageBitsPerPixel;
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::storageBitsPerPixel;
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::storageBitsPerPixel;
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::storageBitsPerPixel;
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::storageBitsPerPixel;
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::storageBitsPerPixel;
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::storageBitsPerPixel;
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::storageBitsPerPixel;
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::storageBitsPerPixel;
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::storageBitsPerPixel;
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::storageBitsPerPixel;
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::storageBitsPerPixel;
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::storageBitsPerPixel;
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::storageBitsPerPixel;
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::storageBitsPerPixel;
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::storageBitsPerPixel;
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::storageBitsPerPixel;
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::storageBitsPerPixel;
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::storageBitsPerPixel;

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline size_t PixelFormatInfo::GetStorageBitsPerChannel() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::storageBitsPerChannel;
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::storageBitsPerChannel;
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::storageBitsPerChannel;
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::storageBitsPerChannel;
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::storageBitsPerChannel;
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::storageBitsPerChannel;
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::storageBitsPerChannel;
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::storageBitsPerChannel;
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::storageBitsPerChannel;
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::storageBitsPerChannel;
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::storageBitsPerChannel;
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::storageBitsPerChannel;
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::storageBitsPerChannel;
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::storageBitsPerChannel;
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::storageBitsPerChannel;
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::storageBitsPerChannel;
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::storageBitsPerChannel;
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::storageBitsPerChannel;
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::storageBitsPerChannel;
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::storageBitsPerChannel;
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::storageBitsPerChannel;
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::storageBitsPerChannel;
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::storageBitsPerChannel;
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::storageBitsPerChannel;
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::storageBitsPerChannel;
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::storageBitsPerChannel;
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::storageBitsPerChannel;
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::storageBitsPerChannel;
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::storageBitsPerChannel;
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::storageBitsPerChannel;
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::storageBitsPerChannel;
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::storageBitsPerChannel;
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::storageBitsPerChannel;
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::storageBitsPerChannel;
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::storageBitsPerChannel;
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::storageBitsPerChannel;
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::storageBitsPerChannel;
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::storageBitsPerChannel;
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::storageBitsPerChannel;
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::storageBitsPerChannel;
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::storageBitsPerChannel;
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::storageBitsPerChannel;
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::storageBitsPerChannel;
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::storageBitsPerChannel;
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::storageBitsPerChannel;
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::storageBitsPerChannel;
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::storageBitsPerChannel;
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::storageBitsPerChannel;
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::storageBitsPerChannel;
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::storageBitsPerChannel;
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::storageBitsPerChannel;
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::storageBitsPerChannel;
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::storageBitsPerChannel;
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::storageBitsPerChannel;
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::storageBitsPerChannel;
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::storageBitsPerChannel;
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::storageBitsPerChannel;
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::storageBitsPerChannel;
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::storageBitsPerChannel;
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::storageBitsPerChannel;
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::storageBitsPerChannel;
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::storageBitsPerChannel;
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::storageBitsPerChannel;
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::storageBitsPerChannel;
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::storageBitsPerChannel;
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::storageBitsPerChannel;
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::storageBitsPerChannel;
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::storageBitsPerChannel;
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::storageBitsPerChannel;
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::storageBitsPerChannel;
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::storageBitsPerChannel;
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::storageBitsPerChannel;
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::storageBitsPerChannel;
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::storageBitsPerChannel;
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::storageBitsPerChannel;
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::storageBitsPerChannel;
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::storageBitsPerChannel;
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::storageBitsPerChannel;
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::storageBitsPerChannel;
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::storageBitsPerChannel;
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::storageBitsPerChannel;
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::storageBitsPerChannel;
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::storageBitsPerChannel;
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::storageBitsPerChannel;
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::storageBitsPerChannel;
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::storageBitsPerChannel;
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::storageBitsPerChannel;
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::storageBitsPerChannel;
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::storageBitsPerChannel;
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::storageBitsPerChannel;
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::storageBitsPerChannel;
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::storageBitsPerChannel;
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::storageBitsPerChannel;

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline std::string PixelFormatInfo::GetName() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::Name();
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::Name();
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::Name();
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::Name();
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::Name();
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::Name();
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::Name();
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::Name();
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::Name();
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::Name();
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::Name();
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::Name();
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::Name();
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::Name();
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::Name();
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::Name();
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::Name();
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::Name();
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::Name();
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::Name();
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::Name();
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::Name();
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::Name();
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::Name();
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::Name();
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::Name();
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::Name();
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::Name();
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::Name();
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::Name();
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::Name();
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::Name();
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::Name();
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::Name();
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::Name();
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::Name();
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::Name();
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::Name();
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::Name();
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::Name();
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::Name();
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::Name();
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::Name();
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::Name();
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::Name();
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::Name();
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::Name();
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::Name();
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::Name();
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::Name();
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::Name();
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::Name();
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::Name();
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::Name();
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::Name();
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::Name();
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::Name();
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::Name();
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::Name();
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::Name();
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::Name();
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::Name();
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::Name();
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::Name();
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::Name();
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::Name();
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::Name();
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::Name();
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::Name();
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::Name();
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::Name();
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::Name();
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::Name();
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::Name();
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::Name();
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::Name();
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::Name();
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::Name();
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::Name();
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::Name();
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::Name();
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::Name();
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::Name();
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::Name();
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::Name();
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::Name();
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::Name();
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::Name();
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::Name();
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::Name();
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::Name();
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::Name();
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::Name();
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::Name();
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::Name();
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::Name();
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::Name();
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::Name();
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::Name();
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::Name();
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::Name();
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::Name();
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::Name();
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::Name();
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::Name();
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::Name();
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::Name();
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::Name();
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::Name();
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::Name();
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::Name();
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::Name();
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::Name();
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::Name();
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::Name();
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::Name();
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::Name();
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::Name();
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::Name();
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::Name();
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::Name();
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::Name();
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::Name();

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline size_t PixelFormatInfo::GetAllocatedBitsPerPixel() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::allocatedBitsPerPixel;
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::allocatedBitsPerPixel;
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::allocatedBitsPerPixel;
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::allocatedBitsPerPixel;
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::allocatedBitsPerPixel;
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::allocatedBitsPerPixel;
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::allocatedBitsPerPixel;
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::allocatedBitsPerPixel;
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::allocatedBitsPerPixel;
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::allocatedBitsPerPixel;
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::allocatedBitsPerPixel;
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::allocatedBitsPerPixel;
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::allocatedBitsPerPixel;
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::allocatedBitsPerPixel;
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::allocatedBitsPerPixel;
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::allocatedBitsPerPixel;
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::allocatedBitsPerPixel;
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::allocatedBitsPerPixel;
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::allocatedBitsPerPixel;
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::allocatedBitsPerPixel;
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::allocatedBitsPerPixel;
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::allocatedBitsPerPixel;
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::allocatedBitsPerPixel;
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::allocatedBitsPerPixel;
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::allocatedBitsPerPixel;
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::allocatedBitsPerPixel;
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::allocatedBitsPerPixel;
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::allocatedBitsPerPixel;
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::allocatedBitsPerPixel;
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::allocatedBitsPerPixel;
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::allocatedBitsPerPixel;
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::allocatedBitsPerPixel;
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::allocatedBitsPerPixel;
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::allocatedBitsPerPixel;
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::allocatedBitsPerPixel;
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::allocatedBitsPerPixel;
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::allocatedBitsPerPixel;
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::allocatedBitsPerPixel;
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::allocatedBitsPerPixel;
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::allocatedBitsPerPixel;
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::allocatedBitsPerPixel;
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::allocatedBitsPerPixel;
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::allocatedBitsPerPixel;
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::allocatedBitsPerPixel;
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::allocatedBitsPerPixel;
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::allocatedBitsPerPixel;
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::allocatedBitsPerPixel;
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::allocatedBitsPerPixel;
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::allocatedBitsPerPixel;
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::allocatedBitsPerPixel;
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::allocatedBitsPerPixel;

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline size_t PixelFormatInfo::GetSizeInBytes(const Size& size) const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::GetSizeInBytes(size);
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::GetSizeInBytes(size);
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::GetSizeInBytes(size);
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::GetSizeInBytes(size);
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::GetSizeInBytes(size);
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::GetSizeInBytes(size);
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::GetSizeInBytes(size);
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::GetSizeInBytes(size);
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::GetSizeInBytes(size);
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::GetSizeInBytes(size);
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::GetSizeInBytes(size);
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::GetSizeInBytes(size);
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::GetSizeInBytes(size);
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::GetSizeInBytes(size);
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::GetSizeInBytes(size);
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::GetSizeInBytes(size);
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::GetSizeInBytes(size);
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::GetSizeInBytes(size);
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::GetSizeInBytes(size);
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::GetSizeInBytes(size);
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::GetSizeInBytes(size);
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::GetSizeInBytes(size);
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::GetSizeInBytes(size);
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::GetSizeInBytes(size);
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::GetSizeInBytes(size);
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::GetSizeInBytes(size);
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::GetSizeInBytes(size);
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::GetSizeInBytes(size);
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::GetSizeInBytes(size);
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::GetSizeInBytes(size);
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::GetSizeInBytes(size);
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::GetSizeInBytes(size);
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::GetSizeInBytes(size);
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::GetSizeInBytes(size);
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::GetSizeInBytes(size);
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::GetSizeInBytes(size);
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::GetSizeInBytes(size);
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::GetSizeInBytes(size);
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::GetSizeInBytes(size);
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::GetSizeInBytes(size);
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::GetSizeInBytes(size);
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::GetSizeInBytes(size);
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::GetSizeInBytes(size);
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::GetSizeInBytes(size);
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::GetSizeInBytes(size);
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::GetSizeInBytes(size);
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::GetSizeInBytes(size);
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::GetSizeInBytes(size);
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::GetSizeInBytes(size);
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::GetSizeInBytes(size);
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::GetSizeInBytes(size);
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::GetSizeInBytes(size);
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::GetSizeInBytes(size);
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::GetSizeInBytes(size);
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::GetSizeInBytes(size);
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::GetSizeInBytes(size);
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::GetSizeInBytes(size);
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::GetSizeInBytes(size);
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::GetSizeInBytes(size);
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::GetSizeInBytes(size);
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::GetSizeInBytes(size);
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::GetSizeInBytes(size);
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::GetSizeInBytes(size);
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::GetSizeInBytes(size);
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::GetSizeInBytes(size);
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::GetSizeInBytes(size);
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::GetSizeInBytes(size);
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::GetSizeInBytes(size);
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::GetSizeInBytes(size);
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::GetSizeInBytes(size);
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::GetSizeInBytes(size);
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::GetSizeInBytes(size);
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::GetSizeInBytes(size);
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::GetSizeInBytes(size);
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::GetSizeInBytes(size);
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::GetSizeInBytes(size);
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::GetSizeInBytes(size);
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::GetSizeInBytes(size);

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline bool PixelFormatInfo::IsPacked() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::IsPacked();
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::IsPacked();
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::IsPacked();
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::IsPacked();
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::IsPacked();
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::IsPacked();
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::IsPacked();
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::IsPacked();
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::IsPacked();
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::IsPacked();
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::IsPacked();
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::IsPacked();
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::IsPacked();
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::IsPacked();
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::IsPacked();
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::IsPacked();
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::IsPacked();
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::IsPacked();
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::IsPacked();
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::IsPacked();
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::IsPacked();
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::IsPacked();
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::IsPacked();
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::IsPacked();
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::IsPacked();
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::IsPacked();
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::IsPacked();
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::IsPacked();
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::IsPacked();
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::IsPacked();
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::IsPacked();
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::IsPacked();
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::IsPacked();
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::IsPacked();
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::IsPacked();
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::IsPacked();
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::IsPacked();
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::IsPacked();
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::IsPacked();
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::IsPacked();
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::IsPacked();
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::IsPacked();
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::IsPacked();
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::IsPacked();
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::IsPacked();
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::IsPacked();
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::IsPacked();
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::IsPacked();
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::IsPacked();
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::IsPacked();
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::IsPacked();
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::IsPacked();
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::IsPacked();
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::IsPacked();
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::IsPacked();
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::IsPacked();
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::IsPacked();
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::IsPacked();
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::IsPacked();
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::IsPacked();
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::IsPacked();
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::IsPacked();
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::IsPacked();
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::IsPacked();
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::IsPacked();
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::IsPacked();
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::IsPacked();
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::IsPacked();
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::IsPacked();
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::IsPacked();
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::IsPacked();
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::IsPacked();
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::IsPacked();
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::IsPacked();
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::IsPacked();
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::IsPacked();
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::IsPacked();
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::IsPacked();
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::IsPacked();
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::IsPacked();
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::IsPacked();
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::IsPacked();
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::IsPacked();
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::IsPacked();
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::IsPacked();
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::IsPacked();
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::IsPacked();
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::IsPacked();
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::IsPacked();
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::IsPacked();
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::IsPacked();
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::IsPacked();
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::IsPacked();
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::IsPacked();
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::IsPacked();
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::IsPacked();
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::IsPacked();
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::IsPacked();
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::IsPacked();
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::IsPacked();
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::IsPacked();
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::IsPacked();
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::IsPacked();
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::IsPacked();
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::IsPacked();
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::IsPacked();
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::IsPacked();
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::IsPacked();
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::IsPacked();
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::IsPacked();
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::IsPacked();
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::IsPacked();
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::IsPacked();
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::IsPacked();
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::IsPacked();
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::IsPacked();
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::IsPacked();
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::IsPacked();
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::IsPacked();
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::IsPacked();
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::IsPacked();
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::IsPacked();
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::IsPacked();

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline bool PixelFormatInfo::IsInterleaved() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::IsInterleaved();
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::IsInterleaved();
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::IsInterleaved();
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::IsInterleaved();
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::IsInterleaved();
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::IsInterleaved();
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::IsInterleaved();
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::IsInterleaved();
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::IsInterleaved();
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::IsInterleaved();
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::IsInterleaved();
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::IsInterleaved();
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::IsInterleaved();
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::IsInterleaved();
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::IsInterleaved();
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::IsInterleaved();
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::IsInterleaved();
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::IsInterleaved();
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::IsInterleaved();
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::IsInterleaved();
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::IsInterleaved();
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::IsInterleaved();
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::IsInterleaved();
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::IsInterleaved();
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::IsInterleaved();
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::IsInterleaved();
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::IsInterleaved();
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::IsInterleaved();
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::IsInterleaved();
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::IsInterleaved();
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::IsInterleaved();
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::IsInterleaved();
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::IsInterleaved();
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::IsInterleaved();
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::IsInterleaved();
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::IsInterleaved();
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::IsInterleaved();
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::IsInterleaved();
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::IsInterleaved();
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::IsInterleaved();
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::IsInterleaved();
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::IsInterleaved();
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::IsInterleaved();
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::IsInterleaved();
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::IsInterleaved();
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::IsInterleaved();
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::IsInterleaved();
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::IsInterleaved();
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::IsInterleaved();
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::IsInterleaved();
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::IsInterleaved();
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::IsInterleaved();
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::IsInterleaved();
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::IsInterleaved();
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::IsInterleaved();
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::IsInterleaved();
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::IsInterleaved();
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::IsInterleaved();
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::IsInterleaved();
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::IsInterleaved();
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::IsInterleaved();
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::IsInterleaved();
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::IsInterleaved();
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::IsInterleaved();
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::IsInterleaved();
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::IsInterleaved();
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::IsInterleaved();
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::IsInterleaved();
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::IsInterleaved();
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::IsInterleaved();
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::IsInterleaved();
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::IsInterleaved();
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::IsInterleaved();
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::IsInterleaved();
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::IsInterleaved();
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::IsInterleaved();
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::IsInterleaved();
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::IsInterleaved();
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::IsInterleaved();
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::IsInterleaved();
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::IsInterleaved();
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::IsInterleaved();
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::IsInterleaved();
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::IsInterleaved();
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::IsInterleaved();
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::IsInterleaved();
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::IsInterleaved();
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::IsInterleaved();
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::IsInterleaved();
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::IsInterleaved();
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::IsInterleaved();
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::IsInterleaved();
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::IsInterleaved();
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::IsInterleaved();
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::IsInterleaved();
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::IsInterleaved();
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::IsInterleaved();
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::IsInterleaved();
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::IsInterleaved();
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::IsInterleaved();
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::IsInterleaved();
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::IsInterleaved();
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::IsInterleaved();
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::IsInterleaved();
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::IsInterleaved();
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::IsInterleaved();
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::IsInterleaved();
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::IsInterleaved();
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::IsInterleaved();
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::IsInterleaved();

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline bool PixelFormatInfo::IsFloat() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::is_floating_point;
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::is_floating_point;
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::is_floating_point;
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::is_floating_point;
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::is_floating_point;
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::is_floating_point;
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::is_floating_point;
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::is_floating_point;
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::is_floating_point;
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::is_floating_point;
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::is_floating_point;
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::is_floating_point;
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::is_floating_point;
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::is_floating_point;
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::is_floating_point;
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::is_floating_point;
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::is_floating_point;
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::is_floating_point;
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::is_floating_point;
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::is_floating_point;
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::is_floating_point;
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::is_floating_point;
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::is_floating_point;
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::is_floating_point;
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::is_floating_point;
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::is_floating_point;
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::is_floating_point;
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::is_floating_point;
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::is_floating_point;
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::is_floating_point;
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::is_floating_point;
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::is_floating_point;
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::is_floating_point;
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::is_floating_point;
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::is_floating_point;
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::is_floating_point;
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::is_floating_point;
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::is_floating_point;
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::is_floating_point;
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::is_floating_point;
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::is_floating_point;
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::is_floating_point;
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::is_floating_point;
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::is_floating_point;
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::is_floating_point;
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::is_floating_point;
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::is_floating_point;
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::is_floating_point;
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::is_floating_point;
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::is_floating_point;
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::is_floating_point;
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::is_floating_point;
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::is_floating_point;
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::is_floating_point;
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::is_floating_point;
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::is_floating_point;
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::is_floating_point;
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::is_floating_point;
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::is_floating_point;
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::is_floating_point;
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::is_floating_point;
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::is_floating_point;
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::is_floating_point;
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::is_floating_point;
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::is_floating_point;
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::is_floating_point;
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::is_floating_point;
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::is_floating_point;
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::is_floating_point;
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::is_floating_point;
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::is_floating_point;
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::is_floating_point;
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::is_floating_point;
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::is_floating_point;
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::is_floating_point;
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::is_floating_point;
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::is_floating_point;
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::is_floating_point;
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::is_floating_point;
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::is_floating_point;
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::is_floating_point;
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::is_floating_point;
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::is_floating_point;
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::is_floating_point;
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::is_floating_point;
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::is_floating_point;
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::is_floating_point;
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::is_floating_point;
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::is_floating_point;
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::is_floating_point;
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::is_floating_point;
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::is_floating_point;
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::is_floating_point;
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::is_floating_point;
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::is_floating_point;
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::is_floating_point;
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::is_floating_point;
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::is_floating_point;
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::is_floating_point;
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::is_floating_point;
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::is_floating_point;
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::is_floating_point;
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::is_floating_point;
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::is_floating_point;
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::is_floating_point;
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::is_floating_point;
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::is_floating_point;
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::is_floating_point;
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::is_floating_point;
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::is_floating_point;
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::is_floating_point;
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::is_floating_point;
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::is_floating_point;
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::is_floating_point;
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::is_floating_point;
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::is_floating_point;
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::is_floating_point;
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::is_floating_point;
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::is_floating_point;
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::is_floating_point;
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::is_floating_point;
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::is_floating_point;
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::is_floating_point;

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline PixelFormat PixelFormatInfo::GetUnpackedPixelFormat() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::GetUnpackedFormat();
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::GetUnpackedFormat();
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::GetUnpackedFormat();
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::GetUnpackedFormat();
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::GetUnpackedFormat();
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::GetUnpackedFormat();
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::GetUnpackedFormat();
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::GetUnpackedFormat();
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::GetUnpackedFormat();
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::GetUnpackedFormat();
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::GetUnpackedFormat();
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::GetUnpackedFormat();
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::GetUnpackedFormat();
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::GetUnpackedFormat();
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::GetUnpackedFormat();
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::GetUnpackedFormat();
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::GetUnpackedFormat();
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::GetUnpackedFormat();
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::GetUnpackedFormat();
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::GetUnpackedFormat();
    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::GetUnpackedFormat();
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::GetUnpackedFormat();
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::GetUnpackedFormat();
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::GetUnpackedFormat();
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::GetUnpackedFormat();
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::GetUnpackedFormat();
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::GetUnpackedFormat();
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::GetUnpackedFormat();
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::GetUnpackedFormat();
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::GetUnpackedFormat();
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::GetUnpackedFormat();
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::GetUnpackedFormat();
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::GetUnpackedFormat();
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::GetUnpackedFormat();
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::GetUnpackedFormat();
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::GetUnpackedFormat();
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::GetUnpackedFormat();
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::GetUnpackedFormat();
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::GetUnpackedFormat();
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::GetUnpackedFormat();
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::GetUnpackedFormat();
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::GetUnpackedFormat();
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::GetUnpackedFormat();
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::GetUnpackedFormat();
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::GetUnpackedFormat();
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::GetUnpackedFormat();
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::GetUnpackedFormat();
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::GetUnpackedFormat();
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::GetUnpackedFormat();
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::GetUnpackedFormat();
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::GetUnpackedFormat();
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::GetUnpackedFormat();
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::GetUnpackedFormat();
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::GetUnpackedFormat();
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::GetUnpackedFormat();
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::GetUnpackedFormat();
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::GetUnpackedFormat();
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::GetUnpackedFormat();
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::GetUnpackedFormat();
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::GetUnpackedFormat();
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::GetUnpackedFormat();
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::GetUnpackedFormat();
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::GetUnpackedFormat();
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::GetUnpackedFormat();
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::GetUnpackedFormat();
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::GetUnpackedFormat();
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::GetUnpackedFormat();
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::GetUnpackedFormat();
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::GetUnpackedFormat();
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::GetUnpackedFormat();
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::GetUnpackedFormat();
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::GetUnpackedFormat();
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::GetUnpackedFormat();
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::GetUnpackedFormat();
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::GetUnpackedFormat();
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::GetUnpackedFormat();
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::GetUnpackedFormat();
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::GetUnpackedFormat();
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::GetUnpackedFormat();
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::GetUnpackedFormat();
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::GetUnpackedFormat();
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::GetUnpackedFormat();
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::GetUnpackedFormat();
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::GetUnpackedFormat();
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::GetUnpackedFormat();
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::GetUnpackedFormat();
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::GetUnpackedFormat();
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::GetUnpackedFormat();
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::GetUnpackedFormat();
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::GetUnpackedFormat();
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::GetUnpackedFormat();
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::GetUnpackedFormat();
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::GetUnpackedFormat();

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}

     
inline std::vector<Channel> PixelFormatInfo::GetChannels() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR8>>() };
    case PixelFormat::BayerGR10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR10>>() };
    case PixelFormat::BayerGR12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR12>>() };
    case PixelFormat::BayerRG8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG8>>() };
    case PixelFormat::BayerRG10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG10>>() };
    case PixelFormat::BayerRG12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG12>>() };
    case PixelFormat::BayerGB8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB8>>() };
    case PixelFormat::BayerGB10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB10>>() };
    case PixelFormat::BayerGB12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB12>>() };
    case PixelFormat::BayerBG8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG8>>() };
    case PixelFormat::BayerBG10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG10>>() };
    case PixelFormat::BayerBG12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG12>>() };
    case PixelFormat::Mono8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono8>>() };
    case PixelFormat::Mono10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10>>() };
    case PixelFormat::Mono12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12>>() };
    case PixelFormat::Mono16:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono16>>() };
    case PixelFormat::Confidence8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Confidence8>>() };
    case PixelFormat::Confidence16:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Confidence16>>() };
    case PixelFormat::Coord3D_C8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Coord3D_C8>>() };
    case PixelFormat::Coord3D_C16:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Coord3D_C16>>() };
    case PixelFormat::Coord3D_C32f:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>>() };
    case PixelFormat::Coord3D_ABC32f:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>>() };
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>>() };
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>>() };
    case PixelFormat::YUV422_8_UYVY:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>>() };
    case PixelFormat::RGB8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGB8>>() };
    case PixelFormat::RGB10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGB10>>() };
    case PixelFormat::RGB12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGB12>>() };
    case PixelFormat::BGR8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BGR8>>() };
    case PixelFormat::BGR10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BGR10>>() };
    case PixelFormat::BGR12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BGR12>>() };
    case PixelFormat::RGBa8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGBa8>>() };
    case PixelFormat::RGBa10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGBa10>>() };
    case PixelFormat::RGBa12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGBa12>>() };
    case PixelFormat::BGRa8:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BGRa8>>() };
    case PixelFormat::BGRa10:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BGRa10>>() };
    case PixelFormat::BGRa12:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BGRa12>>() };
    case PixelFormat::BayerBG10p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG10p>>() };
    case PixelFormat::BayerBG12p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG12p>>() };
    case PixelFormat::BayerGB10p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB10p>>() };
    case PixelFormat::BayerGB12p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB12p>>() };
    case PixelFormat::BayerGR10p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR10p>>() };
    case PixelFormat::BayerGR12p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR12p>>() };
    case PixelFormat::BayerRG10p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG10p>>() };
    case PixelFormat::BayerRG12p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG12p>>() };
    case PixelFormat::Mono10p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10p>>() };
    case PixelFormat::Mono12p:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12p>>() };
    case PixelFormat::RGB10p32:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGB10p32>>() };
    case PixelFormat::BGR10p32:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BGR10p32>>() };
    case PixelFormat::BayerRG10g40IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>>() };
    case PixelFormat::BayerGB10g40IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>>() };
    case PixelFormat::BayerGR10g40IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>>() };
    case PixelFormat::BayerBG10g40IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>>() };
    case PixelFormat::BayerRG12g24IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>>() };
    case PixelFormat::BayerGB12g24IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>>() };
    case PixelFormat::BayerGR12g24IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>>() };
    case PixelFormat::BayerBG12g24IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>>() };
    case PixelFormat::Mono10g40IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>>() };
    case PixelFormat::Mono12g24IDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>>() };
    case PixelFormat::Mono32f:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono32f>>() };
    case PixelFormat::Mono32fIDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono32fIDS>>() };
    case PixelFormat::RGB32f:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGB32f>>() };
    case PixelFormat::RGB32fIDS:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::RGB32fIDS>>() };
    case PixelFormat::Mono10g40IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>>() };
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>>() };
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>>() };
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>>() };
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>>() };
    case PixelFormat::Mono12g24IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>>() };
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>>() };
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>>() };
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>>() };
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>>() };
    case PixelFormat::Mono8_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>>() };
    case PixelFormat::BayerRG8_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>>() };
    case PixelFormat::BayerBG8_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>>() };
    case PixelFormat::BayerGR8_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>>() };
    case PixelFormat::BayerGB8_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>>() };
    case PixelFormat::Mono10_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>>() };
    case PixelFormat::BayerRG10_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>>() };
    case PixelFormat::BayerBG10_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>>() };
    case PixelFormat::BayerGR10_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>>() };
    case PixelFormat::BayerGB10_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>>() };
    case PixelFormat::Mono12_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>>() };
    case PixelFormat::BayerRG12_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>>() };
    case PixelFormat::BayerBG12_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>>() };
    case PixelFormat::BayerGR12_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>>() };
    case PixelFormat::BayerGB12_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>>() };
    case PixelFormat::Mono10p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>>() };
    case PixelFormat::BayerRG10p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>>() };
    case PixelFormat::BayerBG10p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>>() };
    case PixelFormat::BayerGR10p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>>() };
    case PixelFormat::BayerGB10p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>>() };
    case PixelFormat::Mono12p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>>() };
    case PixelFormat::BayerRG12p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>>() };
    case PixelFormat::BayerBG12p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>>() };
    case PixelFormat::BayerGR12p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>>() };
    case PixelFormat::BayerGB12p_I_A_B:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>>() };
    case PixelFormat::Mono8_I_AB_CD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>>() };
    case PixelFormat::Mono10_I_AB_CD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>>() };
    case PixelFormat::Mono12_I_AB_CD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>>() };
    case PixelFormat::Mono10p_I_AB_CD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>>() };
    case PixelFormat::Mono12p_I_AB_CD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>>() };
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>>() };
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>>() };
    case PixelFormat::Mono10_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10_AB>>() };
    case PixelFormat::BayerRG10_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>>() };
    case PixelFormat::BayerBG10_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>>() };
    case PixelFormat::BayerGR10_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>>() };
    case PixelFormat::BayerGB10_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>>() };
    case PixelFormat::Mono12_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12_AB>>() };
    case PixelFormat::BayerRG12_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>>() };
    case PixelFormat::BayerBG12_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>>() };
    case PixelFormat::BayerGR12_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>>() };
    case PixelFormat::BayerGB12_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>>() };
    case PixelFormat::Mono8_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono8_AB>>() };
    case PixelFormat::BayerRG8_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>>() };
    case PixelFormat::BayerBG8_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>>() };
    case PixelFormat::BayerGR8_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>>() };
    case PixelFormat::BayerGB8_AB:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>>() };
    case PixelFormat::Mono8_ABCD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>>() };
    case PixelFormat::Mono10_ABCD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>>() };
    case PixelFormat::Mono12_ABCD:
        return { detail::ChannelsVector<detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>>() };

    }
    const auto pixelFormatValue = static_cast<typename std::underlying_type<decltype(m_pixelFormat)>::type>(m_pixelFormat);
    throw InvalidParameterException(
        "The given pixel format with the integer value of " + std::to_string(pixelFormatValue) + " is unknown!");
}
template <>
     
inline size_t PixelFormatInfo::GetMinimumValuePerChannel<size_t>() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::minimumValuePerChannel;
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::minimumValuePerChannel;
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::minimumValuePerChannel;
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::minimumValuePerChannel;
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::minimumValuePerChannel;
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::minimumValuePerChannel;
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::minimumValuePerChannel;
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::minimumValuePerChannel;
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::minimumValuePerChannel;
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::minimumValuePerChannel;
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::minimumValuePerChannel;
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::minimumValuePerChannel;
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::minimumValuePerChannel;
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::minimumValuePerChannel;
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::minimumValuePerChannel;
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::minimumValuePerChannel;
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::minimumValuePerChannel;
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::minimumValuePerChannel;
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::minimumValuePerChannel;
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::minimumValuePerChannel;
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::minimumValuePerChannel;
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::minimumValuePerChannel;
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::minimumValuePerChannel;
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::minimumValuePerChannel;
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::minimumValuePerChannel;
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::minimumValuePerChannel;
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::minimumValuePerChannel;
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::minimumValuePerChannel;
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::minimumValuePerChannel;
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::minimumValuePerChannel;
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::minimumValuePerChannel;
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::minimumValuePerChannel;
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::minimumValuePerChannel;
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::minimumValuePerChannel;
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::minimumValuePerChannel;
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::minimumValuePerChannel;
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::minimumValuePerChannel;
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::minimumValuePerChannel;
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::minimumValuePerChannel;
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::minimumValuePerChannel;
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::minimumValuePerChannel;
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::minimumValuePerChannel;
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::minimumValuePerChannel;
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::minimumValuePerChannel;
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::minimumValuePerChannel;
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::minimumValuePerChannel;
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::minimumValuePerChannel;
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::minimumValuePerChannel;
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::minimumValuePerChannel;
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::minimumValuePerChannel;
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::minimumValuePerChannel;
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::minimumValuePerChannel;
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::minimumValuePerChannel;
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::minimumValuePerChannel;
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::minimumValuePerChannel;
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::minimumValuePerChannel;
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::minimumValuePerChannel;
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::minimumValuePerChannel;
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::minimumValuePerChannel;
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::minimumValuePerChannel;
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::minimumValuePerChannel;
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::minimumValuePerChannel;
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::minimumValuePerChannel;
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::minimumValuePerChannel;
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::minimumValuePerChannel;
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::minimumValuePerChannel;
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::minimumValuePerChannel;
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::minimumValuePerChannel;
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::minimumValuePerChannel;
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::minimumValuePerChannel;
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::minimumValuePerChannel;
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::minimumValuePerChannel;
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::minimumValuePerChannel;
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::minimumValuePerChannel;
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::minimumValuePerChannel;
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::minimumValuePerChannel;
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::minimumValuePerChannel;
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::minimumValuePerChannel;
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::minimumValuePerChannel;
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::minimumValuePerChannel;
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::minimumValuePerChannel;
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::minimumValuePerChannel;
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::minimumValuePerChannel;
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::minimumValuePerChannel;
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::minimumValuePerChannel;
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::minimumValuePerChannel;
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::minimumValuePerChannel;
    default:
        throw InvalidParameterException(
            "The template does not match the data type of pixel format " + GetName() + "! Use float as template argument.");
    }
}
template <>
     
inline float PixelFormatInfo::GetMinimumValuePerChannel<float>() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::minimumValuePerChannel;
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::minimumValuePerChannel;
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::minimumValuePerChannel;
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::minimumValuePerChannel;
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::minimumValuePerChannel;
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::minimumValuePerChannel;
    default:
        throw InvalidParameterException(
            "The template does not match the data type of pixel format " + GetName() + "! Use float as template argument.");
    }
}
template <>
     
inline size_t PixelFormatInfo::GetMaximumValuePerChannel<size_t>() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::BayerGR8:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8>::maximumValuePerChannel;
    case PixelFormat::BayerGR10:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10>::maximumValuePerChannel;
    case PixelFormat::BayerGR12:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12>::maximumValuePerChannel;
    case PixelFormat::BayerRG8:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8>::maximumValuePerChannel;
    case PixelFormat::BayerRG10:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10>::maximumValuePerChannel;
    case PixelFormat::BayerRG12:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12>::maximumValuePerChannel;
    case PixelFormat::BayerGB8:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8>::maximumValuePerChannel;
    case PixelFormat::BayerGB10:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10>::maximumValuePerChannel;
    case PixelFormat::BayerGB12:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12>::maximumValuePerChannel;
    case PixelFormat::BayerBG8:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8>::maximumValuePerChannel;
    case PixelFormat::BayerBG10:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10>::maximumValuePerChannel;
    case PixelFormat::BayerBG12:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12>::maximumValuePerChannel;
    case PixelFormat::Mono8:
        return detail::PixelFormatInfo<PixelFormat::Mono8>::maximumValuePerChannel;
    case PixelFormat::Mono10:
        return detail::PixelFormatInfo<PixelFormat::Mono10>::maximumValuePerChannel;
    case PixelFormat::Mono12:
        return detail::PixelFormatInfo<PixelFormat::Mono12>::maximumValuePerChannel;
    case PixelFormat::Mono16:
        return detail::PixelFormatInfo<PixelFormat::Mono16>::maximumValuePerChannel;
    case PixelFormat::Confidence8:
        return detail::PixelFormatInfo<PixelFormat::Confidence8>::maximumValuePerChannel;
    case PixelFormat::Confidence16:
        return detail::PixelFormatInfo<PixelFormat::Confidence16>::maximumValuePerChannel;
    case PixelFormat::Coord3D_C8:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C8>::maximumValuePerChannel;
    case PixelFormat::Coord3D_C16:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C16>::maximumValuePerChannel;
    case PixelFormat::YUV420_8_YY_UV_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_UV_SemiplanarIDS>::maximumValuePerChannel;
    case PixelFormat::YUV420_8_YY_VU_SemiplanarIDS:
        return detail::PixelFormatInfo<PixelFormat::YUV420_8_YY_VU_SemiplanarIDS>::maximumValuePerChannel;
    case PixelFormat::YUV422_8_UYVY:
        return detail::PixelFormatInfo<PixelFormat::YUV422_8_UYVY>::maximumValuePerChannel;
    case PixelFormat::RGB8:
        return detail::PixelFormatInfo<PixelFormat::RGB8>::maximumValuePerChannel;
    case PixelFormat::RGB10:
        return detail::PixelFormatInfo<PixelFormat::RGB10>::maximumValuePerChannel;
    case PixelFormat::RGB12:
        return detail::PixelFormatInfo<PixelFormat::RGB12>::maximumValuePerChannel;
    case PixelFormat::BGR8:
        return detail::PixelFormatInfo<PixelFormat::BGR8>::maximumValuePerChannel;
    case PixelFormat::BGR10:
        return detail::PixelFormatInfo<PixelFormat::BGR10>::maximumValuePerChannel;
    case PixelFormat::BGR12:
        return detail::PixelFormatInfo<PixelFormat::BGR12>::maximumValuePerChannel;
    case PixelFormat::RGBa8:
        return detail::PixelFormatInfo<PixelFormat::RGBa8>::maximumValuePerChannel;
    case PixelFormat::RGBa10:
        return detail::PixelFormatInfo<PixelFormat::RGBa10>::maximumValuePerChannel;
    case PixelFormat::RGBa12:
        return detail::PixelFormatInfo<PixelFormat::RGBa12>::maximumValuePerChannel;
    case PixelFormat::BGRa8:
        return detail::PixelFormatInfo<PixelFormat::BGRa8>::maximumValuePerChannel;
    case PixelFormat::BGRa10:
        return detail::PixelFormatInfo<PixelFormat::BGRa10>::maximumValuePerChannel;
    case PixelFormat::BGRa12:
        return detail::PixelFormatInfo<PixelFormat::BGRa12>::maximumValuePerChannel;
    case PixelFormat::BayerBG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p>::maximumValuePerChannel;
    case PixelFormat::BayerBG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p>::maximumValuePerChannel;
    case PixelFormat::BayerGB10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p>::maximumValuePerChannel;
    case PixelFormat::BayerGB12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p>::maximumValuePerChannel;
    case PixelFormat::BayerGR10p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p>::maximumValuePerChannel;
    case PixelFormat::BayerGR12p:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p>::maximumValuePerChannel;
    case PixelFormat::BayerRG10p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p>::maximumValuePerChannel;
    case PixelFormat::BayerRG12p:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p>::maximumValuePerChannel;
    case PixelFormat::Mono10p:
        return detail::PixelFormatInfo<PixelFormat::Mono10p>::maximumValuePerChannel;
    case PixelFormat::Mono12p:
        return detail::PixelFormatInfo<PixelFormat::Mono12p>::maximumValuePerChannel;
    case PixelFormat::RGB10p32:
        return detail::PixelFormatInfo<PixelFormat::RGB10p32>::maximumValuePerChannel;
    case PixelFormat::BGR10p32:
        return detail::PixelFormatInfo<PixelFormat::BGR10p32>::maximumValuePerChannel;
    case PixelFormat::BayerRG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS>::maximumValuePerChannel;
    case PixelFormat::BayerGB10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS>::maximumValuePerChannel;
    case PixelFormat::BayerGR10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS>::maximumValuePerChannel;
    case PixelFormat::BayerBG10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS>::maximumValuePerChannel;
    case PixelFormat::BayerRG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS>::maximumValuePerChannel;
    case PixelFormat::BayerGB12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS>::maximumValuePerChannel;
    case PixelFormat::BayerGR12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS>::maximumValuePerChannel;
    case PixelFormat::BayerBG12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS>::maximumValuePerChannel;
    case PixelFormat::Mono10g40IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS>::maximumValuePerChannel;
    case PixelFormat::Mono12g24IDS:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS>::maximumValuePerChannel;
    case PixelFormat::Mono10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerRG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10g40IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerBG10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10g40IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGR10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10g40IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGB10g40IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10g40IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::Mono12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerRG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12g24IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerBG12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12g24IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGR12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12g24IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGB12g24IDS_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12g24IDS_I_A_B>::maximumValuePerChannel;
    case PixelFormat::Mono8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerRG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerBG8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGR8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGB8_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_I_A_B>::maximumValuePerChannel;
    case PixelFormat::Mono10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerRG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerBG10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGR10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGB10_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_I_A_B>::maximumValuePerChannel;
    case PixelFormat::Mono12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerRG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerBG12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGR12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGB12_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_I_A_B>::maximumValuePerChannel;
    case PixelFormat::Mono10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerRG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerBG10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGR10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGB10p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::Mono12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerRG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerBG12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGR12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::BayerGB12p_I_A_B:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12p_I_A_B>::maximumValuePerChannel;
    case PixelFormat::Mono8_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_I_AB_CD>::maximumValuePerChannel;
    case PixelFormat::Mono10_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_I_AB_CD>::maximumValuePerChannel;
    case PixelFormat::Mono12_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_I_AB_CD>::maximumValuePerChannel;
    case PixelFormat::Mono10p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10p_I_AB_CD>::maximumValuePerChannel;
    case PixelFormat::Mono12p_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12p_I_AB_CD>::maximumValuePerChannel;
    case PixelFormat::Mono10g40IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono10g40IDS_I_AB_CD>::maximumValuePerChannel;
    case PixelFormat::Mono12g24IDS_I_AB_CD:
        return detail::PixelFormatInfo<PixelFormat::Mono12g24IDS_I_AB_CD>::maximumValuePerChannel;
    case PixelFormat::Mono10_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono10_AB>::maximumValuePerChannel;
    case PixelFormat::BayerRG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG10_AB>::maximumValuePerChannel;
    case PixelFormat::BayerBG10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG10_AB>::maximumValuePerChannel;
    case PixelFormat::BayerGR10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR10_AB>::maximumValuePerChannel;
    case PixelFormat::BayerGB10_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB10_AB>::maximumValuePerChannel;
    case PixelFormat::Mono12_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono12_AB>::maximumValuePerChannel;
    case PixelFormat::BayerRG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG12_AB>::maximumValuePerChannel;
    case PixelFormat::BayerBG12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG12_AB>::maximumValuePerChannel;
    case PixelFormat::BayerGR12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR12_AB>::maximumValuePerChannel;
    case PixelFormat::BayerGB12_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB12_AB>::maximumValuePerChannel;
    case PixelFormat::Mono8_AB:
        return detail::PixelFormatInfo<PixelFormat::Mono8_AB>::maximumValuePerChannel;
    case PixelFormat::BayerRG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerRG8_AB>::maximumValuePerChannel;
    case PixelFormat::BayerBG8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerBG8_AB>::maximumValuePerChannel;
    case PixelFormat::BayerGR8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGR8_AB>::maximumValuePerChannel;
    case PixelFormat::BayerGB8_AB:
        return detail::PixelFormatInfo<PixelFormat::BayerGB8_AB>::maximumValuePerChannel;
    case PixelFormat::Mono8_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono8_ABCD>::maximumValuePerChannel;
    case PixelFormat::Mono10_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono10_ABCD>::maximumValuePerChannel;
    case PixelFormat::Mono12_ABCD:
        return detail::PixelFormatInfo<PixelFormat::Mono12_ABCD>::maximumValuePerChannel;
    default:
        throw InvalidParameterException(
            "The template does not match the data type of pixel format " + GetName() + "! Use float as template argument.");
    }
}
template <>
     
inline float PixelFormatInfo::GetMaximumValuePerChannel<float>() const
{
    switch (m_pixelFormat)
    {    case PixelFormat::Coord3D_C32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_C32f>::maximumValuePerChannel;
    case PixelFormat::Coord3D_ABC32f:
        return detail::PixelFormatInfo<PixelFormat::Coord3D_ABC32f>::maximumValuePerChannel;
    case PixelFormat::Mono32f:
        return detail::PixelFormatInfo<PixelFormat::Mono32f>::maximumValuePerChannel;
    case PixelFormat::Mono32fIDS:
        return detail::PixelFormatInfo<PixelFormat::Mono32fIDS>::maximumValuePerChannel;
    case PixelFormat::RGB32f:
        return detail::PixelFormatInfo<PixelFormat::RGB32f>::maximumValuePerChannel;
    case PixelFormat::RGB32fIDS:
        return detail::PixelFormatInfo<PixelFormat::RGB32fIDS>::maximumValuePerChannel;
    default:
        throw InvalidParameterException(
            "The template does not match the data type of pixel format " + GetName() + "! Use float as template argument.");
    }
}

} // namespace common 
} // namespace peak


PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS

