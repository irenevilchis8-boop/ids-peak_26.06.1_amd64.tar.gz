/*!
 * \file    peak_icv_type_traits.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_type_traits.hpp>
#include <peak_icv_c/types/peak_icv_simple_types.h>
#include <type_traits>
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>


// NOLINTBEGIN(readability-identifier-naming)
struct peak_icv_archive;
struct peak_icv_calibration_parameters;
struct peak_icv_calibration_plate;
struct peak_icv_calibration_result;
struct peak_icv_calibration_view;
struct peak_icv_capture_information;
struct peak_icv_coordinate_system;
struct peak_icv_deserializer;
struct peak_icv_downsampling;
struct peak_icv_drawing_options;
struct peak_icv_extrinsic_parameters;
struct peak_icv_hdr;
struct peak_icv_hdr_response_curve;
struct peak_icv_tone_mapping_drago;
struct peak_icv_tone_mapping_linear;
struct peak_icv_image;
struct peak_icv_intrinsic_parameters;
struct peak_icv_point_xyz;
struct peak_icv_point_xyzi;
struct peak_icv_point_xyzrgb;
struct peak_icv_pointcloud;
struct peak_icv_undistortion;
struct peak_icv_region;
struct peak_icv_reprojection_error;
struct peak_icv_serializer;
struct peak_icv_polygon;
struct peak_icv_code_reader_result;

// NOLINTEND(readability-identifier-naming)

namespace peak
{
namespace common
{
namespace detail
{
template <typename T>
class Interval;

template <typename T>
class PointT;
} // namespace detail

} // namespace common 
} // namespace peak

namespace peak
{
namespace icv
{
class Archive;
class Deserializer;
class Downsampling;
class Image;
class Serializer;

class CalibrationParameters;
class CalibrationPlate;
class CalibrationResult;
class CalibrationView;
class CoordinateSystem;
class IntrinsicParameters;
class ExtrinsicParameters;
class PointCloudXYZ;
class PointCloudXYZI;
class PointCloudXYZRGB;
class PointXYZ;
class PointXYZI;
class PointXYZRGB;
class Undistortion;
class Region;
class ReprojectionError;
class XYZImage;
class HDR;
class ResponseCurve;
class DragoToneMapping;

namespace experimental
{
class CodeReaderResult;
class LinearToneMapping;
} // namespace experimental

namespace detail
{
class DrawingOptions;

template <typename PointCloudType, typename PointType>
class PointCloud;

template <typename PointType>
class Polygon;

template <typename Type>
struct is_pointcloud : std::false_type
{};

template <>
struct is_pointcloud<peak::icv::PointCloudXYZ> : std::true_type
{};

template <>
struct is_pointcloud<peak::icv::PointCloudXYZI> : std::true_type
{};

template <typename Type>
constexpr bool is_pointcloud_v = is_pointcloud<Type>::value;

template <typename Type>
struct is_threshold_interval : std::false_type
{};

template <>
struct is_threshold_interval<::peak::common::detail::IntervalT<int32_t>> : std::true_type
{};

template <>
struct is_threshold_interval<::peak::common::detail::IntervalT<float>> : std::true_type
{};

template <typename Type>
constexpr bool is_threshold_interval_v = is_threshold_interval<Type>::value;

template <typename Type>
struct point_enum_of_;

template <>
struct point_enum_of_<peak_common_point_f>
{
    static constexpr peak_icv_point_type value = PEAK_ICV_POINT_TYPE_XY;
};

template <typename Type>
using handle_of_t = peak::common::detail::c_type_of_t<Type>*;

template <typename T, typename Element>
struct is_contiguous_container : std::false_type
{};

template <typename Element, typename Alloc>
struct is_contiguous_container<std::vector<Element, Alloc>, Element> : std::true_type
{};

template <typename Element, std::size_t N>
struct is_contiguous_container<std::array<Element, N>, Element> : std::true_type
{};


} // namespace detail
} // namespace icv 
} // namespace peak

namespace peak
{
namespace common
{
namespace detail
{

template <typename Type>
struct c_type_of_;

template <>
struct c_type_of_<peak::icv::PointXYZ>
{
    using type = peak_icv_point_xyz;
};

template <>
struct c_type_of_<peak::icv::PointXYZI>
{
    using type = peak_icv_point_xyzi;
};

template <>
struct c_type_of_<peak::icv::PointXYZRGB>
{
    using type = peak_icv_point_xyzrgb;
};

template <>
struct c_type_of_<peak::icv::CalibrationResult>
{
    using type = peak_icv_calibration_result;
};

template <>
struct c_type_of_<peak::icv::ExtrinsicParameters>
{
    using type = peak_icv_extrinsic_parameters;
};

template <>
struct c_type_of_<peak::icv::IntrinsicParameters>
{
    using type = peak_icv_intrinsic_parameters;
};

template <>
struct c_type_of_<peak::icv::CalibrationView>
{
    using type = peak_icv_calibration_view;
};

template <>
struct c_type_of_<peak::icv::Region>
{
    using type = peak_icv_region;
};

template <>
struct c_type_of_<peak::icv::PointCloudXYZ>
{
    using type = peak_icv_pointcloud;
};

template <>
struct c_type_of_<peak::icv::PointCloudXYZI>
{
    using type = peak_icv_pointcloud;
};

template <>
struct c_type_of_<peak::icv::PointCloudXYZRGB>
{
    using type = peak_icv_pointcloud;
};

template <>
struct c_type_of_<peak::icv::detail::PointCloud<peak::icv::PointCloudXYZ, peak::icv::PointXYZ>>
{
    using type = peak_icv_pointcloud;
};

template <>
struct c_type_of_<peak::icv::detail::PointCloud<peak::icv::PointCloudXYZI, peak::icv::PointXYZI>>
{
    using type = peak_icv_pointcloud;
};

template <>
struct c_type_of_<peak::icv::detail::PointCloud<peak::icv::PointCloudXYZRGB, peak::icv::PointXYZRGB>>
{
    using type = peak_icv_pointcloud;
};

template <>
struct c_type_of_<peak::icv::CalibrationPlate>
{
    using type = peak_icv_calibration_plate;
};

template <>
struct c_type_of_<peak::icv::Image>
{
    using type = peak_icv_image;
};

template <>
struct c_type_of_<peak::icv::XYZImage>
{
    using type = peak_icv_image;
};

template <>
struct c_type_of_<peak::icv::Undistortion>
{
    using type = peak_icv_undistortion;
};

template <>
struct c_type_of_<peak::icv::HDR>
{
    using type = peak_icv_hdr;
};

template <>
struct c_type_of_<peak::icv::ResponseCurve>
{
    using type = peak_icv_hdr_response_curve;
};

template <>
struct c_type_of_<peak::icv::DragoToneMapping>
{
    using type = peak_icv_tone_mapping_drago;
};

template <>
struct c_type_of_<peak::icv::experimental::LinearToneMapping>
{
    using type = peak_icv_tone_mapping_linear;
};

template <>
struct c_type_of_<peak::icv::ReprojectionError>
{
    using type = peak_icv_reprojection_error;
};

template <>
struct c_type_of_<peak::icv::detail::Polygon<float>>
{
    using type = peak_icv_polygon;
};

template <>
struct c_type_of_<peak::icv::CoordinateSystem>
{
    using type = peak_icv_coordinate_system;
};

template <>
struct c_type_of_<peak::icv::CalibrationParameters>
{
    using type = peak_icv_calibration_parameters;
};

template <>
struct c_type_of_<peak::icv::Downsampling>
{
    using type = peak_icv_downsampling;
};

template <>
struct c_type_of_<peak::icv::Archive>
{
    using type = peak_icv_archive;
};

template <>
struct c_type_of_<peak::icv::Serializer>
{
    using type = peak_icv_serializer;
};

template <>
struct c_type_of_<peak::icv::Deserializer>
{
    using type = peak_icv_deserializer;
};

template <>
struct c_type_of_<peak::icv::detail::DrawingOptions>
{
    using type = peak_icv_drawing_options;
};

template <>
struct c_type_of_<peak::icv::experimental::CodeReaderResult>
{
    using type = peak_icv_code_reader_result;
};

template <typename Type>
using c_type_of_t = typename c_type_of_<Type>::type;


} // namespace detail
} // namespace common 
} // namespace peak
