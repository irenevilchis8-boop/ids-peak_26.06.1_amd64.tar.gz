/*!
 * \file    peak_icv_dynamic_loader.h
 *
 * \author  IDS Imaging Development Systems GmbH All rights reserved
 * \date    2019-05-01
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */
#pragma once

#include "../../peak_icv_c/algorithms/calibration/peak_icv_calibration_parameters.h"
#include "../../peak_icv_c/algorithms/calibration/peak_icv_calibration_plate.h"
#include "../../peak_icv_c/algorithms/calibration/peak_icv_calibration_result.h"
#include "../../peak_icv_c/algorithms/calibration/peak_icv_calibration_view.h"
#include "../../peak_icv_c/algorithms/calibration/peak_icv_camera_calibration.h"
#include "../../peak_icv_c/algorithms/calibration/peak_icv_extrinsic_parameters.h"
#include "../../peak_icv_c/algorithms/calibration/peak_icv_intrinsic_parameters.h"
#include "../../peak_icv_c/algorithms/calibration/peak_icv_workspace_calibration.h"
#include "../../peak_icv_c/algorithms/code_reader/peak_icv_code_reader.h"
#include "../../peak_icv_c/algorithms/filters/peak_icv_image_filter_sharpening.h"
#include "../../peak_icv_c/algorithms/filters/peak_icv_median_filter.h"
#include "../../peak_icv_c/algorithms/hdr/peak_icv_hdr.h"
#include "../../peak_icv_c/algorithms/hdr/peak_icv_response_curve.h"
#include "../../peak_icv_c/algorithms/hdr/tone_mapping/peak_icv_drago_tone_mapping.h"
#include "../../peak_icv_c/algorithms/hdr/tone_mapping/peak_icv_linear_tone_mapping.h"
#include "../../peak_icv_c/algorithms/preprocessing/peak_icv_color_matrix_transformation.h"
#include "../../peak_icv_c/algorithms/preprocessing/peak_icv_downsampling.h"
#include "../../peak_icv_c/algorithms/preprocessing/peak_icv_gain.h"
#include "../../peak_icv_c/algorithms/preprocessing/peak_icv_hotpixel_correction.h"
#include "../../peak_icv_c/algorithms/preprocessing/peak_icv_image_converter.h"
#include "../../peak_icv_c/algorithms/preprocessing/peak_icv_image_transformation.h"
#include "../../peak_icv_c/algorithms/preprocessing/peak_icv_tone_curve_correction.h"
#include "../../peak_icv_c/algorithms/thresholds/peak_icv_threshold.h"
#include "../../peak_icv_c/algorithms/transformations/peak_icv_undistortion.h"
#include "../../peak_icv_c/algorithms/transformations/peak_icv_xyz_image_transformer.h"
#include "../../peak_icv_c/backend/peak_icv_defines.h"
#include "../../peak_icv_c/backend/peak_icv_dll_defines.h"
#include "../../peak_icv_c/binary/peak_icv_binary_header.h"
#include "../../peak_icv_c/binary/peak_icv_binary_validator.h"
#include "../../peak_icv_c/library/peak_icv_library.h"
#include "../../peak_icv_c/painting/peak_icv_color.h"
#include "../../peak_icv_c/painting/peak_icv_painter.h"
#include "../../peak_icv_c/peak_icv.h"
#include "../../peak_icv_c/selectors/peak_icv_region_selector.h"
#include "../../peak_icv_c/serialization/peak_icv_archive.h"
#include "../../peak_icv_c/types/peak_icv_buffer.h"
#include "../../peak_icv_c/types/peak_icv_image.h"
#include "../../peak_icv_c/types/peak_icv_metadata.h"
#include "../../peak_icv_c/types/peak_icv_point_cloud.h"
#include "../../peak_icv_c/types/peak_icv_polygon.h"
#include "../../peak_icv_c/types/peak_icv_region.h"
#include "../../peak_icv_c/types/peak_icv_simple_types.h"
            
#include <string>
#include <cstdint>

#ifdef __linux__
    #include <dlfcn.h>
#else
    #include <vector>
    #include <windows.h>
    #include <tchar.h>
#endif
 
#include <stdexcept>

#undef PEAK_COMMON_NO_DISCARD
#define PEAK_COMMON_NO_DISCARD
#undef PEAK_ICV_EXPORT
#define PEAK_ICV_EXPORT

PEAK_COMMON_BEGIN_DISABLE_DEPRECATED_WARNINGS

namespace peak
{
namespace icv
{
namespace dynamic
{

typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_CalibrationParameters_CreateFromFile)(peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size, const char* file_path);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_CalibrationParameters_SaveToFile)(peak_icv_calibration_parameters calibration_parameters, size_t calibration_parameters_size, const char* file_path, peak_icv_calibration_parameters_save_options save_options);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_CalibrationParameters_ToBinary)(peak_icv_calibration_parameters calibration_parameters, size_t calibration_parameters_size, uint8_t* calibration_parameters_binary, size_t calibration_parameters_binary_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes)(size_t calibration_parameters_size, size_t* binary_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_CalibrationParameters_CreateFromBinary)(const uint8_t* binary_data, size_t binary_data_size, peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Plate_Create)(peak_icv_calibration_plate_handle* calibration_plate_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Plate_CreateFromFile)(peak_icv_calibration_plate_handle* calibration_plate_handle, const char* file_path);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Plate_IncreaseUseCount)(peak_icv_calibration_plate_handle calibration_plate_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Plate_Destroy)(peak_icv_calibration_plate_handle calibration_plate_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_Create)(peak_icv_calibration_result_handle* calibration_result_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_SaveToFile)(peak_icv_calibration_result_handle calibration_result_handle, const char* file_path, peak_icv_calibration_result_save_options save_options);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_CreateFromFile)(peak_icv_calibration_result_handle* calibration_result_handle, const char* file_path);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_Destroy)(peak_icv_calibration_result_handle calibration_result_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_IncreaseUseCount)(peak_icv_calibration_result_handle calibration_result_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_GetMeanReprojectionError)(peak_icv_calibration_result_handle calibration_result_handle, double* mean_reprojection_error);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_GetCalibrationViews_GetCount)(peak_icv_calibration_result_handle calibration_result_handle, size_t* calibration_view_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_GetCalibrationViews)(peak_icv_calibration_result_handle calibration_result_handle, peak_icv_calibration_view_handle* calibration_views, size_t calibration_views_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Result_ToParameters)(peak_icv_calibration_result_handle calibration_result_handle, peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_Create)(peak_icv_calibration_view_handle* calibration_view_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_Array_Create)(peak_icv_calibration_view_handle* calibration_view_handles, size_t num_calibration_views);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_IncreaseUseCount)(peak_icv_calibration_view_handle calibration_view_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_Destroy)(peak_icv_calibration_view_handle calibration_view_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_Array_Destroy)(peak_icv_calibration_view_handle* calibration_view_handles, size_t num_calibration_views);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_GetReprojectionErrors)(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_reprojection_error* reprojection_errors, size_t num_reprojection_errors);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_GetMeanReprojectionError)(peak_icv_calibration_view_handle calibration_view_handle, double* mean_reprojection_error);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_GetMaximumReprojectionError)(peak_icv_calibration_view_handle calibration_view_handle, double* maximum_reprojection_error);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_GetReprojectionErrors_GetCount)(peak_icv_calibration_view_handle calibration_view_handle, size_t* num_reprojection_errors);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_GetExtrinsicParameters)(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_extrinsic_parameters* extrinsic_parameters, size_t extrinsic_parameters_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_GetConvexHull)(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_polygon_handle* polygon_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_View_GetCoordinateSystem)(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_coordinate_system* coordinate_system);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Process)(peak_icv_calibration_plate_handle input_calibration_plate, peak_icv_image_handle* input_images, size_t num_input_images, peak_icv_calibration_result_handle* output_calibration_result);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix)(peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_transformation_matrix_3d* transformation_matrix);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_WorkspaceCalibration_Process)(peak_icv_calibration_plate_handle calibration_plate, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_image_handle image, peak_icv_calibration_result_handle* calibration_result);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReaderResult_Create)(peak_icv_code_reader_result_handle* result);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReaderResult_Array_Create)(peak_icv_code_reader_result_handle* result, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReaderResult_Destroy)(peak_icv_code_reader_result_handle result);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes)(peak_icv_code_reader_result_handle result, size_t* text_size_in_bytes);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReaderResult_GetText)(peak_icv_code_reader_result_handle result, char* text, size_t text_size_in_bytes);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReaderResult_GetType)(peak_icv_code_reader_result_handle result, peak_icv_code_type* code_type);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReader_Create)(peak_icv_code_reader_handle* handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReader_Destroy)(peak_icv_code_reader_handle handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReader_GetCodeTypesGetCount)(peak_icv_code_reader_handle handle, size_t* count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReader_GetCodeTypes)(peak_icv_code_reader_handle handle, peak_icv_code_type* barcode_types, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReader_SetCodeTypes)(peak_icv_code_reader_handle handle, peak_icv_code_type* barcode_types, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReader_DetectAndDecode)(peak_icv_code_reader_handle handle, peak_icv_image_handle input_image, peak_icv_code_reader_result_handle* result, size_t result_count, size_t* found_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect)(peak_icv_code_reader_handle handle, size_t max_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect)(peak_icv_code_reader_handle handle, size_t* max_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ImageFilter_Sharpening_ProcessInPlace)(peak_icv_image_handle input_image, uint32_t sharpness_level);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ImageFilter_Sharpening_GetRange)(peak_common_interval_u* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Filter_Image_Median)(peak_icv_image_handle input_image, size_t kernel_size, peak_icv_image_handle output_image);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_Create)(peak_icv_hdr_handle* hdr_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_EstimateResponseCurve)(peak_icv_hdr_handle hdr_handle, peak_icv_image_handle* input_images, size_t num_input_images);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_Process_GetOutputPixelFormat)(peak_icv_hdr_handle hdr_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_Process)(peak_icv_hdr_handle hdr_handle, peak_icv_image_handle* input_images, size_t num_input_images, peak_icv_image_handle output_image);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_GetAlgorithm)(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_algorithm* algorithm);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_Destroy)(peak_icv_hdr_handle hdr_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_GetResponseCurve)(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_response_curve_handle* response_curve_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_SetResponseCurve)(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_response_curve_handle response_curve_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_ResponseCurve_Create)(peak_icv_hdr_response_curve_handle* response_curve_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_ResponseCurve_CreateFromFile)(peak_icv_hdr_response_curve_handle* response_curve_handle, const char* file_path);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_ResponseCurve_IncreaseUseCount)(peak_icv_hdr_response_curve_handle response_curve_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_ResponseCurve_Destroy)(peak_icv_hdr_response_curve_handle response_curve_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_ResponseCurve_SaveToFile)(peak_icv_hdr_response_curve_handle response_curve_handle, const char* file_path);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_HDR_ResponseCurve_Compare)(peak_icv_hdr_response_curve_handle response_curve_handle_lhs, peak_icv_hdr_response_curve_handle response_curve_handle_rhs, bool* is_equal);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Drago_Create)(peak_icv_tone_mapping_drago_handle* tone_mapping_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Drago_Destroy)(peak_icv_tone_mapping_drago_handle tone_mapping_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Drago_GetOutputPixelFormat)(peak_icv_tone_mapping_drago_handle tone_mapping_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Drago_Process)(peak_icv_tone_mapping_drago_handle tone_mapping_handle, peak_icv_image_handle input_hdr_image, peak_icv_image_handle output_ldr_image);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Linear_Create)(peak_icv_tone_mapping_linear_handle* tone_mapping_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Linear_Destroy)(peak_icv_tone_mapping_linear_handle tone_mapping_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Linear_GetOutputPixelFormat)(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Linear_Process)(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_icv_image_handle hdr_image, float center_exposure_value, float number_of_stops, peak_icv_image_handle ldr_image);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ToneMapping_Linear_GetExposureValueRange)(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_icv_image_handle hdr_image, peak_common_interval_f* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Create)(peak_icv_color_matrix_transformation_handle* color_matrix_transformation_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Destroy)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* needs_processing);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_image_handle input_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix color_correction_matrix);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix* color_correction_matrix);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, float saturation);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, float* saturation);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_common_interval_f* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix* color_correction_matrix);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_space* color_space);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_space color_space);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_chromatic_adaption_algorithm* algorithm);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_chromatic_adaption_algorithm algorithm);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, uint32_t color_temperature);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, uint32_t* color_temperature);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_common_range_u* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* has_color_temperature);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled)(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_Create)(peak_icv_downsampling_handle* downsampling_handle, peak_icv_downsampling_factor factor, peak_icv_downsampling_mode mode);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_Destroy)(peak_icv_downsampling_handle downsampling_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_SetFactor)(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_factor factor);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_GetFactor)(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_factor* factor);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_GetRange)(peak_icv_downsampling_handle downsampling_handle, peak_common_interval_u* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_SetMode)(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_mode mode);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_GetMode)(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_mode* mode);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_GetOutputImageSize)(peak_icv_downsampling_handle downsampling_handle, peak_icv_image_handle input_image_handle, peak_common_size* output_image_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_NeedsProcessing)(peak_icv_downsampling_handle downsampling_handle, bool* needs_processing);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Downsampling_Process)(peak_icv_downsampling_handle downsampling_handle, peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Gain_Create)(peak_icv_gain_handle* gain_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Gain_Destroy)(peak_icv_gain_handle gain_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Gain_ProcessInplace)(peak_icv_gain_handle gain_handle, peak_icv_image_handle input_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Gain_NeedsProcessing)(peak_icv_gain_handle gain_handle, bool* needs_processing);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Gain_SetValue)(peak_icv_gain_handle gain_handle, peak_icv_gain_type type, float value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Gain_GetValue)(peak_icv_gain_handle gain_handle, peak_icv_gain_type type, float* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Gain_GetRange)(peak_icv_gain_handle gain_handle, peak_common_interval_f* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_Create)(peak_icv_hotpixel_correction_handle* hotpixel_correction_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_Destroy)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_Detect)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_icv_image_handle input_image_handle, uint32_t sensitivity, float gainFactor);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_icv_image_handle input_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_SetList)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_point* list, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_ResetList)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, size_t* count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_GetList)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_point* list, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange)(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_interval_u* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ImageConverter_Create)(peak_icv_image_converter_handle* image_converter_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ImageConverter_Destroy)(peak_icv_image_converter_handle image_converter_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ImageConverter_Convert)(peak_icv_image_converter_handle converter_handle, peak_icv_image_handle input_handle, enum peak_common_pixel_format pixel_format, peak_icv_image_handle* output_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ImageConverter_ReleaseBuffers)(peak_icv_image_converter_handle converter_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Transformation_GetOutputPixelFormat)(peak_common_pixel_format input_pixel_format, peak_icv_preprocessing_transformation_parameters parameters, peak_common_pixel_format* output_pixel_format);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_Transformation_Process)(peak_icv_image_handle input_image_handle, peak_icv_preprocessing_transformation_parameters parameters, peak_icv_image_handle output_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_Create)(peak_icv_tone_curve_correction_handle* tone_curve_correction_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_Destroy)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_common_interval_f* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_common_interval_f* range);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetGamma)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_SetGamma)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, bool* needs_processing);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace)(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_icv_image_handle input_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Threshold_Process)(peak_icv_image_handle input_image, c_peak_icv_variant_interval interval, size_t size_of_interval, peak_icv_region_handle* output_region);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Threshold_GetRange)(peak_icv_image_handle image, peak_icv_variant_interval interval, size_t size_of_interval);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_Undistortion_Process)(peak_icv_undistortion_handle undistortion_handle, peak_icv_image_handle input_image, peak_icv_image_handle output_image);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_Undistortion_Create)(peak_icv_undistortion_handle* undistortion_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation)(peak_icv_undistortion_handle* undistortion_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_capture_information image_capture_information, size_t capture_information_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_Undistortion_CreateWithImageMetadata)(peak_icv_undistortion_handle* undistortion_handle, peak_icv_metadata_handle metadata_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_Undistortion_IncreaseUseCount)(peak_icv_undistortion_handle undistortion_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_Undistortion_Destroy)(peak_icv_undistortion_handle undistortion_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_Undistortion_SetInterpolation)(peak_icv_undistortion_handle undistortion_handle, enum peak_icv_interpolation interpolation);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_Undistortion_GetInterpolation)(peak_icv_undistortion_handle undistortion_handle, enum peak_icv_interpolation* interpolation);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Transform_DepthMap_To_XYZImage)(peak_icv_image_handle xyz_image_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_image_handle depth_map_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_ValidateBinary)(const uint8_t* binary, size_t binary_size, bool* is_valid);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Init)();
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Exit)();
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_GetVersion)(uint32_t* major_version, uint32_t* minor_version, uint32_t* subminor_version, uint32_t* patch_version);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_GetLastErrorMessage_GetCount)(size_t* last_error_message_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_GetLastErrorMessage)(char* last_error_message, size_t last_error_message_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Draw)(peak_icv_image_handle image, peak_icv_region_handle input_region, peak_icv_drawing_options drawing_options);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_SelectByArea_GetCount)(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_u area, size_t* num_output_regions);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_SelectByArea)(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_u area, peak_icv_region_handle* output_regions, size_t num_output_regions);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_SelectByCenterOfGravityX_GetCount)(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f x, size_t* num_output_regions);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_SelectByCenterOfGravityX)(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f x, peak_icv_region_handle* output_regions, size_t num_output_regions);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_SelectByCenterOfGravityY_GetCount)(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f y, size_t* num_output_regions);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_SelectByCenterOfGravityY)(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f y, peak_icv_region_handle* output_regions, size_t num_output_regions);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_SelectByCenterOfGravityRect_GetCount)(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_rectangle_f rect, size_t* num_output_regions);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_SelectByCenterOfGravityRect)(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_rectangle_f rect, peak_icv_region_handle* output_regions, size_t num_output_regions);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_Create)(peak_icv_archive_handle* archive_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_CreateFromString)(peak_icv_archive_handle* archive_handle, peak_icv_serialization_type data_type, const char* data);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_Destroy)(peak_icv_archive_handle archive_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_HasKey)(peak_icv_archive_handle archive_handle, const char* key, bool* has_key);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetKeys_GetCount)(peak_icv_archive_handle archive_handle, size_t* count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetKeysElement_GetSizeInBytes)(peak_icv_archive_handle archive_handle, size_t index, size_t* size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetKeysElement)(peak_icv_archive_handle archive_handle, size_t index, char* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetValueType)(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_value_type_t* type);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetArray_GetCount)(peak_icv_archive_handle archive_handle, const char* key, size_t* count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetInt)(peak_icv_archive_handle archive_handle, const char* key, int64_t* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetInt)(peak_icv_archive_handle archive_handle, const char* key, int64_t value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetIntArray)(peak_icv_archive_handle archive_handle, const char* key, int64_t* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetIntArray)(peak_icv_archive_handle archive_handle, const char* key, const int64_t* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetDouble)(peak_icv_archive_handle archive_handle, const char* key, double* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetDouble)(peak_icv_archive_handle archive_handle, const char* key, double value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetDoubleArray)(peak_icv_archive_handle archive_handle, const char* key, double* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetDoubleArray)(peak_icv_archive_handle archive_handle, const char* key, const double* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetBool)(peak_icv_archive_handle archive_handle, const char* key, bool* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetBool)(peak_icv_archive_handle archive_handle, const char* key, bool value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetBoolArray)(peak_icv_archive_handle archive_handle, const char* key, bool* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetBoolArray)(peak_icv_archive_handle archive_handle, const char* key, const bool* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetString_GetSizeInBytes)(peak_icv_archive_handle archive_handle, const char* key, size_t* size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetString)(peak_icv_archive_handle archive_handle, const char* key, char* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetString)(peak_icv_archive_handle archive_handle, const char* key, const char* data);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetStringArrayElement_GetSizeInBytes)(peak_icv_archive_handle archive_handle, const char* key, size_t index, size_t* size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetStringArrayElement)(peak_icv_archive_handle archive_handle, const char* key, size_t index, char* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetStringArray)(peak_icv_archive_handle archive_handle, const char* key, const char* const* data, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetArchive)(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle* sub_archive);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetArchive)(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle sub_archive);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_GetArchiveArray)(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle* sub_archives, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_SetArchiveArray)(peak_icv_archive_handle archive_handle, const char* key, const peak_icv_archive_handle* sub_archives, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_ToString_GetSizeInBytes)(peak_icv_archive_handle archive_handle, peak_icv_serialization_type type, size_t* size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Archive_ToString)(peak_icv_archive_handle archive_handle, peak_icv_serialization_type type, char* data, size_t* size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Buffer_CutBytes)(const uint8_t* data, size_t line_start_offset, size_t bytes_per_line, size_t valid_bytes_per_line, size_t number_of_lines, peak_icv_image_handle output_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Create)(peak_icv_image_handle* image_handle, enum peak_common_pixel_format pixelformat, peak_common_size size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_CreateWithZeroInit)(peak_icv_image_handle* image_handle, enum peak_common_pixel_format pixelformat, peak_common_size size, bool zero_init);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_CreateFromImageInfo)(peak_icv_image_handle* image_handle, peak_icv_image_info image_info, size_t image_info_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_CreateFromFile)(peak_icv_image_handle* image_handle, const char* file_path);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_CreateFromFileWithPixelFormat)(peak_icv_image_handle* image_handle, const char* file_path, enum peak_common_pixel_format forced_pixelformat);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_CreateFromExistingImage)(peak_icv_image_handle* image_handle, peak_icv_image_handle source_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_SaveToFile)(peak_icv_image_handle image_handle, const char* file_path);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_IncreaseUseCount)(peak_icv_image_handle image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Destroy)(peak_icv_image_handle image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_ConvertPixelFormat)(peak_icv_image_handle input_image_handle, enum peak_common_pixel_format destination_pixelformat, peak_icv_image_handle output_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_ConvertPixelFormatWithFactor)(peak_icv_image_handle input_image_handle, enum peak_common_pixel_format destination_pixelformat, double factor, peak_icv_image_handle output_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_GetInfo)(peak_icv_image_handle image_handle, peak_icv_image_info* image_info, size_t image_info_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_GetRegion)(peak_icv_image_handle image_handle, peak_icv_region_handle* region_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_SetRegion)(peak_icv_image_handle image_handle, peak_icv_region_handle region_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_ResetRegion)(peak_icv_image_handle image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Compare)(peak_icv_image_handle image_handle_lhs, peak_icv_image_handle image_handle_rhs, bool* is_equal);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_GetCaptureInformation)(peak_icv_image_handle image_handle, peak_icv_capture_information* capture_information, size_t capture_information_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_SetCaptureInformation)(peak_icv_image_handle image_handle, peak_icv_capture_information capture_information, size_t capture_information_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Subtract)(peak_icv_image_handle image_handle_minuend, peak_icv_image_handle image_handle_subtrahend, peak_icv_image_handle image_handle_difference);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_TransformToWorkspace)(peak_icv_image_handle input_image_handle, peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_image_handle output_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Crop)(peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle, peak_common_rectangle rectangle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Scale)(peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle, peak_icv_interpolation interpolation);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Deinterleave)(peak_icv_image_handle input_image_handle, peak_icv_image_handle* output_image_handles, size_t output_image_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Deinterleave_GetOutputPixelFormat)(peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Deinterleave_GetOutputImageCount)(peak_common_pixel_format input_pixel_format, size_t* output_image_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_Deinterleave_GetOutputImageSize)(peak_common_pixel_format input_pixel_format, peak_common_size input_image_size, peak_common_size* output_image_size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_GetMetadata)(peak_icv_image_handle image_handle, peak_icv_metadata_handle* metadata_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Image_SetMetadata)(peak_icv_image_handle image_handle, peak_icv_metadata_handle metadata_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_Create)(peak_icv_metadata_handle* handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_Destroy)(peak_icv_metadata_handle handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetInt)(peak_icv_metadata_handle handle, const char* key, int64_t* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetInt)(peak_icv_metadata_handle handle, const char* key, int64_t value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetIntArray)(peak_icv_metadata_handle handle, const char* key, int64_t* values, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetIntArray)(peak_icv_metadata_handle handle, const char* key, const int64_t* values, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetUInt)(peak_icv_metadata_handle handle, const char* key, uint64_t* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetUInt)(peak_icv_metadata_handle handle, const char* key, uint64_t value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetUIntArray)(peak_icv_metadata_handle handle, const char* key, uint64_t* values, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetUIntArray)(peak_icv_metadata_handle handle, const char* key, const uint64_t* values, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetDouble)(peak_icv_metadata_handle handle, const char* key, double* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetDouble)(peak_icv_metadata_handle handle, const char* key, double value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetDoubleArray)(peak_icv_metadata_handle handle, const char* key, double* values, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetDoubleArray)(peak_icv_metadata_handle handle, const char* key, const double* values, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetBool)(peak_icv_metadata_handle handle, const char* key, bool* value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetBool)(peak_icv_metadata_handle handle, const char* key, bool value);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetBoolArray)(peak_icv_metadata_handle handle, const char* key, bool* values, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetBoolArray)(peak_icv_metadata_handle handle, const char* key, const bool* values, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetString_GetSizeInBytes)(peak_icv_metadata_handle handle, const char* key, size_t* size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetString)(peak_icv_metadata_handle handle, const char* key, char* buffer, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetString)(peak_icv_metadata_handle handle, const char* key, const char* buffer);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes)(peak_icv_metadata_handle handle, const char* key, size_t index, size_t* size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetStringArrayElement)(peak_icv_metadata_handle handle, const char* key, size_t index, char* buffer, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_SetStringArray)(peak_icv_metadata_handle handle, const char* key, const char* const* buffers, size_t count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetArray_GetCount)(peak_icv_metadata_handle handle, const char* key, size_t* count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_HasKey)(peak_icv_metadata_handle handle, const char* key, bool* has_key);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetEntryCount)(peak_icv_metadata_handle handle, size_t* count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetKey_GetSizeInBytes)(peak_icv_metadata_handle handle, size_t index, size_t* size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetKey)(peak_icv_metadata_handle handle, size_t index, char* buffer, size_t size);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Metadata_GetValueType)(peak_icv_metadata_handle handle, const char* key, peak_icv_metadata_value_type_t* type);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_Create)(peak_icv_point_cloud_handle* point_cloud_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_CreateFromXYZImage)(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage)(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle, peak_icv_image_handle overlay_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage)(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle, peak_icv_image_handle intensity_image_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_CreateFromFile)(peak_icv_point_cloud_handle* point_cloud_handle, enum peak_icv_point_type point_type, const char* file_path);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_CreateFromPoints)(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_point_xyz_variant points, size_t num_points, enum peak_icv_point_type point_type);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_IncreaseUseCount)(peak_icv_point_cloud_handle point_cloud_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_Destroy)(peak_icv_point_cloud_handle point_cloud_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_GetType)(peak_icv_point_cloud_handle point_cloud_handle, enum peak_icv_point_type* point_type);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_GetPoints_GetCount)(peak_icv_point_cloud_handle point_cloud_handle, size_t* num_points);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_GetPoints_GetSizeInBytes)(peak_icv_point_cloud_handle point_cloud_handle, size_t* byte_size_points);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_GetPoints)(peak_icv_point_cloud_handle point_cloud_handle, peak_icv_point_xyz_variant points, size_t byte_size_points);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_SaveToFile)(peak_icv_point_cloud_handle point_cloud_handle, const char* file_path, peak_icv_point_cloud_save_options save_options);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_Transform)(peak_icv_point_cloud_handle input_point_cloud, peak_icv_transformation_matrix_3d matrix_3d, peak_icv_point_cloud_handle* output_point_cloud);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_PointCloud_TransformToWorkspace)(peak_icv_point_cloud_handle input_point_cloud, peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_point_cloud_handle* output_point_cloud);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_Create)(peak_icv_polygon_handle* polygon_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_CreateFromPoints)(peak_icv_polygon_handle* polygon_handle, peak_icv_point_type_variant points, size_t num_points, enum peak_icv_point_type point_type);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_Destroy)(peak_icv_polygon_handle polygon_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_IncreaseUseCount)(peak_icv_polygon_handle polygon_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_GetPoints_GetCount)(peak_icv_polygon_handle polygon_handle, size_t* points_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_GetPointType)(peak_icv_polygon_handle polygon_handle, enum peak_icv_point_type* point_type);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_IsClosed)(peak_icv_polygon_handle polygon_handle, bool* is_closed);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_GetPoints_GetSizeInBytes)(peak_icv_polygon_handle polygon_handle, size_t* byte_size_points);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Polygon_GetPoints)(peak_icv_polygon_handle polygon_handle, peak_icv_point_type_variant points, size_t byte_size_points);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Create)(peak_icv_region_handle* region_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_CreateFromPoints)(peak_icv_region_handle* region_handle, peak_common_point* points, size_t num_points);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_CreateFromRectangle)(peak_icv_region_handle* region_handle, peak_common_rectangle rect);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_IncreaseUseCount)(peak_icv_region_handle region_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Destroy)(peak_icv_region_handle region_handle);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Array_Create)(peak_icv_region_handle* region_handles, size_t num_region_handles);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Array_Destroy)(peak_icv_region_handle* region_handles, size_t num_region_handles);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_GetConnectedComponents_GetCount)(peak_icv_region_handle input_region, size_t* output_regions_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_GetConnectedComponents)(peak_icv_region_handle input_region, peak_icv_region_handle* output_regions, size_t region_handles_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_GetArea)(peak_icv_region_handle input_region, size_t* area);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_GetCenterOfGravity)(peak_icv_region_handle input_region, peak_common_point_f* center_of_gravity);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_GetPoints_GetCount)(peak_icv_region_handle input_region, size_t* points_count);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_GetPoints)(peak_icv_region_handle input_region, peak_common_point* points, size_t num_points);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Difference)(peak_icv_region_handle input_region_minuend, peak_icv_region_handle input_region_subtrahend, peak_icv_region_handle* output_region_difference);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Intersection)(peak_icv_region_handle input_region_1, peak_icv_region_handle input_region_2, peak_icv_region_handle* output_region_intersection);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Union)(peak_icv_region_handle input_region_1, peak_icv_region_handle input_region_2, peak_icv_region_handle* output_region_united);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Dilation)(peak_icv_region_handle input_region, peak_icv_region_handle input_structuring_element, peak_icv_region_handle* output_region_dilation);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Erosion)(peak_icv_region_handle input_region, peak_icv_region_handle input_structuring_element, peak_icv_region_handle* output_region_erosion);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Compare)(peak_icv_region_handle region_handle_lhs, peak_icv_region_handle region_handle_rhs, bool* is_equal);
typedef PEAK_ICV_API_STATUS (*dyn_peak_icv_Region_Scale)(peak_icv_region_handle input_region_handle, peak_common_size input_size, peak_common_size output_size, peak_icv_interpolation interpolation, peak_icv_region_handle* output_region_handle);


class LoadLibraryException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};
                        
class DynamicLoader
{
private:
    DynamicLoader();
    
    static DynamicLoader& instance()
    {
        static DynamicLoader dynamicLoader{};
        return dynamicLoader;
    }
    bool loadLib(const char* file);
    void unload();
    bool setPointers(bool load);

public:
    ~DynamicLoader();
    
    static bool isLoaded();
    
    static PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_CreateFromFile(peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size, const char* file_path);
    static PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_SaveToFile(peak_icv_calibration_parameters calibration_parameters, size_t calibration_parameters_size, const char* file_path, peak_icv_calibration_parameters_save_options save_options);
    static PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_ToBinary(peak_icv_calibration_parameters calibration_parameters, size_t calibration_parameters_size, uint8_t* calibration_parameters_binary, size_t calibration_parameters_binary_size);
    static PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes(size_t calibration_parameters_size, size_t* binary_size);
    static PEAK_ICV_API_STATUS peak_icv_CalibrationParameters_CreateFromBinary(const uint8_t* binary_data, size_t binary_data_size, peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Plate_Create(peak_icv_calibration_plate_handle* calibration_plate_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Plate_CreateFromFile(peak_icv_calibration_plate_handle* calibration_plate_handle, const char* file_path);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Plate_IncreaseUseCount(peak_icv_calibration_plate_handle calibration_plate_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Plate_Destroy(peak_icv_calibration_plate_handle calibration_plate_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_Create(peak_icv_calibration_result_handle* calibration_result_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_SaveToFile(peak_icv_calibration_result_handle calibration_result_handle, const char* file_path, peak_icv_calibration_result_save_options save_options);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_CreateFromFile(peak_icv_calibration_result_handle* calibration_result_handle, const char* file_path);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_Destroy(peak_icv_calibration_result_handle calibration_result_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_IncreaseUseCount(peak_icv_calibration_result_handle calibration_result_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_GetMeanReprojectionError(peak_icv_calibration_result_handle calibration_result_handle, double* mean_reprojection_error);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_GetCalibrationViews_GetCount(peak_icv_calibration_result_handle calibration_result_handle, size_t* calibration_view_count);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_GetCalibrationViews(peak_icv_calibration_result_handle calibration_result_handle, peak_icv_calibration_view_handle* calibration_views, size_t calibration_views_count);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Result_ToParameters(peak_icv_calibration_result_handle calibration_result_handle, peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_Create(peak_icv_calibration_view_handle* calibration_view_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_Array_Create(peak_icv_calibration_view_handle* calibration_view_handles, size_t num_calibration_views);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_IncreaseUseCount(peak_icv_calibration_view_handle calibration_view_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_Destroy(peak_icv_calibration_view_handle calibration_view_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_Array_Destroy(peak_icv_calibration_view_handle* calibration_view_handles, size_t num_calibration_views);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetReprojectionErrors(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_reprojection_error* reprojection_errors, size_t num_reprojection_errors);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetMeanReprojectionError(peak_icv_calibration_view_handle calibration_view_handle, double* mean_reprojection_error);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetMaximumReprojectionError(peak_icv_calibration_view_handle calibration_view_handle, double* maximum_reprojection_error);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetReprojectionErrors_GetCount(peak_icv_calibration_view_handle calibration_view_handle, size_t* num_reprojection_errors);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetExtrinsicParameters(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_extrinsic_parameters* extrinsic_parameters, size_t extrinsic_parameters_size);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetConvexHull(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_polygon_handle* polygon_handle);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_View_GetCoordinateSystem(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_coordinate_system* coordinate_system);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Process(peak_icv_calibration_plate_handle input_calibration_plate, peak_icv_image_handle* input_images, size_t num_input_images, peak_icv_calibration_result_handle* output_calibration_result);
    static PEAK_ICV_API_STATUS peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix(peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_transformation_matrix_3d* transformation_matrix);
    static PEAK_ICV_API_STATUS peak_icv_WorkspaceCalibration_Process(peak_icv_calibration_plate_handle calibration_plate, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_image_handle image, peak_icv_calibration_result_handle* calibration_result);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_Create(peak_icv_code_reader_result_handle* result);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_Array_Create(peak_icv_code_reader_result_handle* result, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_Destroy(peak_icv_code_reader_result_handle result);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes(peak_icv_code_reader_result_handle result, size_t* text_size_in_bytes);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_GetText(peak_icv_code_reader_result_handle result, char* text, size_t text_size_in_bytes);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReaderResult_GetType(peak_icv_code_reader_result_handle result, peak_icv_code_type* code_type);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReader_Create(peak_icv_code_reader_handle* handle);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReader_Destroy(peak_icv_code_reader_handle handle);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReader_GetCodeTypesGetCount(peak_icv_code_reader_handle handle, size_t* count);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReader_GetCodeTypes(peak_icv_code_reader_handle handle, peak_icv_code_type* barcode_types, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReader_SetCodeTypes(peak_icv_code_reader_handle handle, peak_icv_code_type* barcode_types, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReader_DetectAndDecode(peak_icv_code_reader_handle handle, peak_icv_image_handle input_image, peak_icv_code_reader_result_handle* result, size_t result_count, size_t* found_count);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect(peak_icv_code_reader_handle handle, size_t max_count);
    static PEAK_ICV_API_STATUS peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect(peak_icv_code_reader_handle handle, size_t* max_count);
    static PEAK_ICV_API_STATUS peak_icv_ImageFilter_Sharpening_ProcessInPlace(peak_icv_image_handle input_image, uint32_t sharpness_level);
    static PEAK_ICV_API_STATUS peak_icv_ImageFilter_Sharpening_GetRange(peak_common_interval_u* range);
    static PEAK_ICV_API_STATUS peak_icv_Filter_Image_Median(peak_icv_image_handle input_image, size_t kernel_size, peak_icv_image_handle output_image);
    static PEAK_ICV_API_STATUS peak_icv_HDR_Create(peak_icv_hdr_handle* hdr_handle);
    static PEAK_ICV_API_STATUS peak_icv_HDR_EstimateResponseCurve(peak_icv_hdr_handle hdr_handle, peak_icv_image_handle* input_images, size_t num_input_images);
    static PEAK_ICV_API_STATUS peak_icv_HDR_Process_GetOutputPixelFormat(peak_icv_hdr_handle hdr_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);
    static PEAK_ICV_API_STATUS peak_icv_HDR_Process(peak_icv_hdr_handle hdr_handle, peak_icv_image_handle* input_images, size_t num_input_images, peak_icv_image_handle output_image);
    static PEAK_ICV_API_STATUS peak_icv_HDR_GetAlgorithm(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_algorithm* algorithm);
    static PEAK_ICV_API_STATUS peak_icv_HDR_Destroy(peak_icv_hdr_handle hdr_handle);
    static PEAK_ICV_API_STATUS peak_icv_HDR_GetResponseCurve(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_response_curve_handle* response_curve_handle);
    static PEAK_ICV_API_STATUS peak_icv_HDR_SetResponseCurve(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_response_curve_handle response_curve_handle);
    static PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_Create(peak_icv_hdr_response_curve_handle* response_curve_handle);
    static PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_CreateFromFile(peak_icv_hdr_response_curve_handle* response_curve_handle, const char* file_path);
    static PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_IncreaseUseCount(peak_icv_hdr_response_curve_handle response_curve_handle);
    static PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_Destroy(peak_icv_hdr_response_curve_handle response_curve_handle);
    static PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_SaveToFile(peak_icv_hdr_response_curve_handle response_curve_handle, const char* file_path);
    static PEAK_ICV_API_STATUS peak_icv_HDR_ResponseCurve_Compare(peak_icv_hdr_response_curve_handle response_curve_handle_lhs, peak_icv_hdr_response_curve_handle response_curve_handle_rhs, bool* is_equal);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Drago_Create(peak_icv_tone_mapping_drago_handle* tone_mapping_handle);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Drago_Destroy(peak_icv_tone_mapping_drago_handle tone_mapping_handle);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Drago_GetOutputPixelFormat(peak_icv_tone_mapping_drago_handle tone_mapping_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Drago_Process(peak_icv_tone_mapping_drago_handle tone_mapping_handle, peak_icv_image_handle input_hdr_image, peak_icv_image_handle output_ldr_image);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_Create(peak_icv_tone_mapping_linear_handle* tone_mapping_handle);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_Destroy(peak_icv_tone_mapping_linear_handle tone_mapping_handle);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_GetOutputPixelFormat(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_Process(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_icv_image_handle hdr_image, float center_exposure_value, float number_of_stops, peak_icv_image_handle ldr_image);
    static PEAK_ICV_API_STATUS peak_icv_ToneMapping_Linear_GetExposureValueRange(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_icv_image_handle hdr_image, peak_common_interval_f* range);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_Create(peak_icv_color_matrix_transformation_handle* color_matrix_transformation_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_Destroy(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* needs_processing);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_image_handle input_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix color_correction_matrix);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix* color_correction_matrix);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, float saturation);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, float* saturation);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_common_interval_f* range);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix* color_correction_matrix);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_space* color_space);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_space color_space);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_chromatic_adaption_algorithm* algorithm);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_chromatic_adaption_algorithm algorithm);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, uint32_t color_temperature);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, uint32_t* color_temperature);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_common_range_u* range);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* has_color_temperature);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_Create(peak_icv_downsampling_handle* downsampling_handle, peak_icv_downsampling_factor factor, peak_icv_downsampling_mode mode);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_Destroy(peak_icv_downsampling_handle downsampling_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_SetFactor(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_factor factor);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_GetFactor(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_factor* factor);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_GetRange(peak_icv_downsampling_handle downsampling_handle, peak_common_interval_u* range);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_SetMode(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_mode mode);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_GetMode(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_mode* mode);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_GetOutputImageSize(peak_icv_downsampling_handle downsampling_handle, peak_icv_image_handle input_image_handle, peak_common_size* output_image_size);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_NeedsProcessing(peak_icv_downsampling_handle downsampling_handle, bool* needs_processing);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Downsampling_Process(peak_icv_downsampling_handle downsampling_handle, peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_Create(peak_icv_gain_handle* gain_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_Destroy(peak_icv_gain_handle gain_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_ProcessInplace(peak_icv_gain_handle gain_handle, peak_icv_image_handle input_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_NeedsProcessing(peak_icv_gain_handle gain_handle, bool* needs_processing);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_SetValue(peak_icv_gain_handle gain_handle, peak_icv_gain_type type, float value);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_GetValue(peak_icv_gain_handle gain_handle, peak_icv_gain_type type, float* value);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Gain_GetRange(peak_icv_gain_handle gain_handle, peak_common_interval_f* range);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_Create(peak_icv_hotpixel_correction_handle* hotpixel_correction_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_Destroy(peak_icv_hotpixel_correction_handle hotpixel_correction_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount(peak_icv_hotpixel_correction_handle hotpixel_correction_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_Detect(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_icv_image_handle input_image_handle, uint32_t sensitivity, float gainFactor);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_icv_image_handle input_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_SetList(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_point* list, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_ResetList(peak_icv_hotpixel_correction_handle hotpixel_correction_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, size_t* count);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_GetList(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_point* list, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_interval_u* range);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ImageConverter_Create(peak_icv_image_converter_handle* image_converter_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ImageConverter_Destroy(peak_icv_image_converter_handle image_converter_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ImageConverter_Convert(peak_icv_image_converter_handle converter_handle, peak_icv_image_handle input_handle, enum peak_common_pixel_format pixel_format, peak_icv_image_handle* output_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ImageConverter_ReleaseBuffers(peak_icv_image_converter_handle converter_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Transformation_GetOutputPixelFormat(peak_common_pixel_format input_pixel_format, peak_icv_preprocessing_transformation_parameters parameters, peak_common_pixel_format* output_pixel_format);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_Transformation_Process(peak_icv_image_handle input_image_handle, peak_icv_preprocessing_transformation_parameters parameters, peak_icv_image_handle output_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_Create(peak_icv_tone_curve_correction_handle* tone_curve_correction_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_Destroy(peak_icv_tone_curve_correction_handle tone_curve_correction_handle);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_common_interval_f* range);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_common_interval_f* range);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_GetGamma(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float* value);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float* value);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_SetGamma(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float value);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float value);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, bool* needs_processing);
    static PEAK_ICV_API_STATUS peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_icv_image_handle input_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Threshold_Process(peak_icv_image_handle input_image, c_peak_icv_variant_interval interval, size_t size_of_interval, peak_icv_region_handle* output_region);
    static PEAK_ICV_API_STATUS peak_icv_Threshold_GetRange(peak_icv_image_handle image, peak_icv_variant_interval interval, size_t size_of_interval);
    static PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_Process(peak_icv_undistortion_handle undistortion_handle, peak_icv_image_handle input_image, peak_icv_image_handle output_image);
    static PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_Create(peak_icv_undistortion_handle* undistortion_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters);
    static PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation(peak_icv_undistortion_handle* undistortion_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_capture_information image_capture_information, size_t capture_information_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters);
    static PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_CreateWithImageMetadata(peak_icv_undistortion_handle* undistortion_handle, peak_icv_metadata_handle metadata_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters);
    static PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_IncreaseUseCount(peak_icv_undistortion_handle undistortion_handle);
    static PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_Destroy(peak_icv_undistortion_handle undistortion_handle);
    static PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_SetInterpolation(peak_icv_undistortion_handle undistortion_handle, enum peak_icv_interpolation interpolation);
    static PEAK_ICV_API_STATUS peak_icv_Transform_Undistortion_GetInterpolation(peak_icv_undistortion_handle undistortion_handle, enum peak_icv_interpolation* interpolation);
    static PEAK_ICV_API_STATUS peak_icv_Transform_DepthMap_To_XYZImage(peak_icv_image_handle xyz_image_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_image_handle depth_map_handle);
    static PEAK_ICV_API_STATUS peak_icv_ValidateBinary(const uint8_t* binary, size_t binary_size, bool* is_valid);
    static PEAK_ICV_API_STATUS peak_icv_Init();
    static PEAK_ICV_API_STATUS peak_icv_Exit();
    static PEAK_ICV_API_STATUS peak_icv_GetVersion(uint32_t* major_version, uint32_t* minor_version, uint32_t* subminor_version, uint32_t* patch_version);
    static PEAK_ICV_API_STATUS peak_icv_GetLastErrorMessage_GetCount(size_t* last_error_message_size);
    static PEAK_ICV_API_STATUS peak_icv_GetLastErrorMessage(char* last_error_message, size_t last_error_message_size);
    static PEAK_ICV_API_STATUS peak_icv_Region_Draw(peak_icv_image_handle image, peak_icv_region_handle input_region, peak_icv_drawing_options drawing_options);
    static PEAK_ICV_API_STATUS peak_icv_Region_SelectByArea_GetCount(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_u area, size_t* num_output_regions);
    static PEAK_ICV_API_STATUS peak_icv_Region_SelectByArea(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_u area, peak_icv_region_handle* output_regions, size_t num_output_regions);
    static PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityX_GetCount(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f x, size_t* num_output_regions);
    static PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityX(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f x, peak_icv_region_handle* output_regions, size_t num_output_regions);
    static PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityY_GetCount(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f y, size_t* num_output_regions);
    static PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityY(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f y, peak_icv_region_handle* output_regions, size_t num_output_regions);
    static PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityRect_GetCount(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_rectangle_f rect, size_t* num_output_regions);
    static PEAK_ICV_API_STATUS peak_icv_Region_SelectByCenterOfGravityRect(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_rectangle_f rect, peak_icv_region_handle* output_regions, size_t num_output_regions);
    static PEAK_ICV_API_STATUS peak_icv_Archive_Create(peak_icv_archive_handle* archive_handle);
    static PEAK_ICV_API_STATUS peak_icv_Archive_CreateFromString(peak_icv_archive_handle* archive_handle, peak_icv_serialization_type data_type, const char* data);
    static PEAK_ICV_API_STATUS peak_icv_Archive_Destroy(peak_icv_archive_handle archive_handle);
    static PEAK_ICV_API_STATUS peak_icv_Archive_HasKey(peak_icv_archive_handle archive_handle, const char* key, bool* has_key);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetKeys_GetCount(peak_icv_archive_handle archive_handle, size_t* count);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetKeysElement_GetSizeInBytes(peak_icv_archive_handle archive_handle, size_t index, size_t* size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetKeysElement(peak_icv_archive_handle archive_handle, size_t index, char* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetValueType(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_value_type_t* type);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetArray_GetCount(peak_icv_archive_handle archive_handle, const char* key, size_t* count);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetInt(peak_icv_archive_handle archive_handle, const char* key, int64_t* value);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetInt(peak_icv_archive_handle archive_handle, const char* key, int64_t value);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetIntArray(peak_icv_archive_handle archive_handle, const char* key, int64_t* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetIntArray(peak_icv_archive_handle archive_handle, const char* key, const int64_t* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetDouble(peak_icv_archive_handle archive_handle, const char* key, double* value);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetDouble(peak_icv_archive_handle archive_handle, const char* key, double value);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetDoubleArray(peak_icv_archive_handle archive_handle, const char* key, double* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetDoubleArray(peak_icv_archive_handle archive_handle, const char* key, const double* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetBool(peak_icv_archive_handle archive_handle, const char* key, bool* value);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetBool(peak_icv_archive_handle archive_handle, const char* key, bool value);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetBoolArray(peak_icv_archive_handle archive_handle, const char* key, bool* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetBoolArray(peak_icv_archive_handle archive_handle, const char* key, const bool* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetString_GetSizeInBytes(peak_icv_archive_handle archive_handle, const char* key, size_t* size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetString(peak_icv_archive_handle archive_handle, const char* key, char* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetString(peak_icv_archive_handle archive_handle, const char* key, const char* data);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetStringArrayElement_GetSizeInBytes(peak_icv_archive_handle archive_handle, const char* key, size_t index, size_t* size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetStringArrayElement(peak_icv_archive_handle archive_handle, const char* key, size_t index, char* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetStringArray(peak_icv_archive_handle archive_handle, const char* key, const char* const* data, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetArchive(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle* sub_archive);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetArchive(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle sub_archive);
    static PEAK_ICV_API_STATUS peak_icv_Archive_GetArchiveArray(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle* sub_archives, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_SetArchiveArray(peak_icv_archive_handle archive_handle, const char* key, const peak_icv_archive_handle* sub_archives, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_ToString_GetSizeInBytes(peak_icv_archive_handle archive_handle, peak_icv_serialization_type type, size_t* size);
    static PEAK_ICV_API_STATUS peak_icv_Archive_ToString(peak_icv_archive_handle archive_handle, peak_icv_serialization_type type, char* data, size_t* size);
    static PEAK_ICV_API_STATUS peak_icv_Buffer_CutBytes(const uint8_t* data, size_t line_start_offset, size_t bytes_per_line, size_t valid_bytes_per_line, size_t number_of_lines, peak_icv_image_handle output_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_Create(peak_icv_image_handle* image_handle, enum peak_common_pixel_format pixelformat, peak_common_size size);
    static PEAK_ICV_API_STATUS peak_icv_Image_CreateWithZeroInit(peak_icv_image_handle* image_handle, enum peak_common_pixel_format pixelformat, peak_common_size size, bool zero_init);
    static PEAK_ICV_API_STATUS peak_icv_Image_CreateFromImageInfo(peak_icv_image_handle* image_handle, peak_icv_image_info image_info, size_t image_info_size);
    static PEAK_ICV_API_STATUS peak_icv_Image_CreateFromFile(peak_icv_image_handle* image_handle, const char* file_path);
    static PEAK_ICV_API_STATUS peak_icv_Image_CreateFromFileWithPixelFormat(peak_icv_image_handle* image_handle, const char* file_path, enum peak_common_pixel_format forced_pixelformat);
    static PEAK_ICV_API_STATUS peak_icv_Image_CreateFromExistingImage(peak_icv_image_handle* image_handle, peak_icv_image_handle source_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_SaveToFile(peak_icv_image_handle image_handle, const char* file_path);
    static PEAK_ICV_API_STATUS peak_icv_Image_IncreaseUseCount(peak_icv_image_handle image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_Destroy(peak_icv_image_handle image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_ConvertPixelFormat(peak_icv_image_handle input_image_handle, enum peak_common_pixel_format destination_pixelformat, peak_icv_image_handle output_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_ConvertPixelFormatWithFactor(peak_icv_image_handle input_image_handle, enum peak_common_pixel_format destination_pixelformat, double factor, peak_icv_image_handle output_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_GetInfo(peak_icv_image_handle image_handle, peak_icv_image_info* image_info, size_t image_info_size);
    static PEAK_ICV_API_STATUS peak_icv_Image_GetRegion(peak_icv_image_handle image_handle, peak_icv_region_handle* region_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_SetRegion(peak_icv_image_handle image_handle, peak_icv_region_handle region_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_ResetRegion(peak_icv_image_handle image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_Compare(peak_icv_image_handle image_handle_lhs, peak_icv_image_handle image_handle_rhs, bool* is_equal);
    static PEAK_ICV_API_STATUS peak_icv_Image_GetCaptureInformation(peak_icv_image_handle image_handle, peak_icv_capture_information* capture_information, size_t capture_information_size);
    static PEAK_ICV_API_STATUS peak_icv_Image_SetCaptureInformation(peak_icv_image_handle image_handle, peak_icv_capture_information capture_information, size_t capture_information_size);
    static PEAK_ICV_API_STATUS peak_icv_Image_Subtract(peak_icv_image_handle image_handle_minuend, peak_icv_image_handle image_handle_subtrahend, peak_icv_image_handle image_handle_difference);
    static PEAK_ICV_API_STATUS peak_icv_Image_TransformToWorkspace(peak_icv_image_handle input_image_handle, peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_image_handle output_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_Crop(peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle, peak_common_rectangle rectangle);
    static PEAK_ICV_API_STATUS peak_icv_Image_Scale(peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle, peak_icv_interpolation interpolation);
    static PEAK_ICV_API_STATUS peak_icv_Image_Deinterleave(peak_icv_image_handle input_image_handle, peak_icv_image_handle* output_image_handles, size_t output_image_count);
    static PEAK_ICV_API_STATUS peak_icv_Image_Deinterleave_GetOutputPixelFormat(peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);
    static PEAK_ICV_API_STATUS peak_icv_Image_Deinterleave_GetOutputImageCount(peak_common_pixel_format input_pixel_format, size_t* output_image_count);
    static PEAK_ICV_API_STATUS peak_icv_Image_Deinterleave_GetOutputImageSize(peak_common_pixel_format input_pixel_format, peak_common_size input_image_size, peak_common_size* output_image_size);
    static PEAK_ICV_API_STATUS peak_icv_Image_GetMetadata(peak_icv_image_handle image_handle, peak_icv_metadata_handle* metadata_handle);
    static PEAK_ICV_API_STATUS peak_icv_Image_SetMetadata(peak_icv_image_handle image_handle, peak_icv_metadata_handle metadata_handle);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_Create(peak_icv_metadata_handle* handle);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_Destroy(peak_icv_metadata_handle handle);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetInt(peak_icv_metadata_handle handle, const char* key, int64_t* value);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetInt(peak_icv_metadata_handle handle, const char* key, int64_t value);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetIntArray(peak_icv_metadata_handle handle, const char* key, int64_t* values, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetIntArray(peak_icv_metadata_handle handle, const char* key, const int64_t* values, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetUInt(peak_icv_metadata_handle handle, const char* key, uint64_t* value);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetUInt(peak_icv_metadata_handle handle, const char* key, uint64_t value);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetUIntArray(peak_icv_metadata_handle handle, const char* key, uint64_t* values, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetUIntArray(peak_icv_metadata_handle handle, const char* key, const uint64_t* values, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetDouble(peak_icv_metadata_handle handle, const char* key, double* value);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetDouble(peak_icv_metadata_handle handle, const char* key, double value);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetDoubleArray(peak_icv_metadata_handle handle, const char* key, double* values, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetDoubleArray(peak_icv_metadata_handle handle, const char* key, const double* values, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetBool(peak_icv_metadata_handle handle, const char* key, bool* value);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetBool(peak_icv_metadata_handle handle, const char* key, bool value);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetBoolArray(peak_icv_metadata_handle handle, const char* key, bool* values, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetBoolArray(peak_icv_metadata_handle handle, const char* key, const bool* values, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetString_GetSizeInBytes(peak_icv_metadata_handle handle, const char* key, size_t* size);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetString(peak_icv_metadata_handle handle, const char* key, char* buffer, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetString(peak_icv_metadata_handle handle, const char* key, const char* buffer);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes(peak_icv_metadata_handle handle, const char* key, size_t index, size_t* size);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetStringArrayElement(peak_icv_metadata_handle handle, const char* key, size_t index, char* buffer, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_SetStringArray(peak_icv_metadata_handle handle, const char* key, const char* const* buffers, size_t count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetArray_GetCount(peak_icv_metadata_handle handle, const char* key, size_t* count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_HasKey(peak_icv_metadata_handle handle, const char* key, bool* has_key);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetEntryCount(peak_icv_metadata_handle handle, size_t* count);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetKey_GetSizeInBytes(peak_icv_metadata_handle handle, size_t index, size_t* size);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetKey(peak_icv_metadata_handle handle, size_t index, char* buffer, size_t size);
    static PEAK_ICV_API_STATUS peak_icv_Metadata_GetValueType(peak_icv_metadata_handle handle, const char* key, peak_icv_metadata_value_type_t* type);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_Create(peak_icv_point_cloud_handle* point_cloud_handle);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromXYZImage(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle, peak_icv_image_handle overlay_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle, peak_icv_image_handle intensity_image_handle);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromFile(peak_icv_point_cloud_handle* point_cloud_handle, enum peak_icv_point_type point_type, const char* file_path);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_CreateFromPoints(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_point_xyz_variant points, size_t num_points, enum peak_icv_point_type point_type);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_IncreaseUseCount(peak_icv_point_cloud_handle point_cloud_handle);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_Destroy(peak_icv_point_cloud_handle point_cloud_handle);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_GetType(peak_icv_point_cloud_handle point_cloud_handle, enum peak_icv_point_type* point_type);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_GetPoints_GetCount(peak_icv_point_cloud_handle point_cloud_handle, size_t* num_points);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_GetPoints_GetSizeInBytes(peak_icv_point_cloud_handle point_cloud_handle, size_t* byte_size_points);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_GetPoints(peak_icv_point_cloud_handle point_cloud_handle, peak_icv_point_xyz_variant points, size_t byte_size_points);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_SaveToFile(peak_icv_point_cloud_handle point_cloud_handle, const char* file_path, peak_icv_point_cloud_save_options save_options);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_Transform(peak_icv_point_cloud_handle input_point_cloud, peak_icv_transformation_matrix_3d matrix_3d, peak_icv_point_cloud_handle* output_point_cloud);
    static PEAK_ICV_API_STATUS peak_icv_PointCloud_TransformToWorkspace(peak_icv_point_cloud_handle input_point_cloud, peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_point_cloud_handle* output_point_cloud);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_Create(peak_icv_polygon_handle* polygon_handle);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_CreateFromPoints(peak_icv_polygon_handle* polygon_handle, peak_icv_point_type_variant points, size_t num_points, enum peak_icv_point_type point_type);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_Destroy(peak_icv_polygon_handle polygon_handle);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_IncreaseUseCount(peak_icv_polygon_handle polygon_handle);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_GetPoints_GetCount(peak_icv_polygon_handle polygon_handle, size_t* points_count);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_GetPointType(peak_icv_polygon_handle polygon_handle, enum peak_icv_point_type* point_type);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_IsClosed(peak_icv_polygon_handle polygon_handle, bool* is_closed);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_GetPoints_GetSizeInBytes(peak_icv_polygon_handle polygon_handle, size_t* byte_size_points);
    static PEAK_ICV_API_STATUS peak_icv_Polygon_GetPoints(peak_icv_polygon_handle polygon_handle, peak_icv_point_type_variant points, size_t byte_size_points);
    static PEAK_ICV_API_STATUS peak_icv_Region_Create(peak_icv_region_handle* region_handle);
    static PEAK_ICV_API_STATUS peak_icv_Region_CreateFromPoints(peak_icv_region_handle* region_handle, peak_common_point* points, size_t num_points);
    static PEAK_ICV_API_STATUS peak_icv_Region_CreateFromRectangle(peak_icv_region_handle* region_handle, peak_common_rectangle rect);
    static PEAK_ICV_API_STATUS peak_icv_Region_IncreaseUseCount(peak_icv_region_handle region_handle);
    static PEAK_ICV_API_STATUS peak_icv_Region_Destroy(peak_icv_region_handle region_handle);
    static PEAK_ICV_API_STATUS peak_icv_Region_Array_Create(peak_icv_region_handle* region_handles, size_t num_region_handles);
    static PEAK_ICV_API_STATUS peak_icv_Region_Array_Destroy(peak_icv_region_handle* region_handles, size_t num_region_handles);
    static PEAK_ICV_API_STATUS peak_icv_Region_GetConnectedComponents_GetCount(peak_icv_region_handle input_region, size_t* output_regions_count);
    static PEAK_ICV_API_STATUS peak_icv_Region_GetConnectedComponents(peak_icv_region_handle input_region, peak_icv_region_handle* output_regions, size_t region_handles_count);
    static PEAK_ICV_API_STATUS peak_icv_Region_GetArea(peak_icv_region_handle input_region, size_t* area);
    static PEAK_ICV_API_STATUS peak_icv_Region_GetCenterOfGravity(peak_icv_region_handle input_region, peak_common_point_f* center_of_gravity);
    static PEAK_ICV_API_STATUS peak_icv_Region_GetPoints_GetCount(peak_icv_region_handle input_region, size_t* points_count);
    static PEAK_ICV_API_STATUS peak_icv_Region_GetPoints(peak_icv_region_handle input_region, peak_common_point* points, size_t num_points);
    static PEAK_ICV_API_STATUS peak_icv_Region_Difference(peak_icv_region_handle input_region_minuend, peak_icv_region_handle input_region_subtrahend, peak_icv_region_handle* output_region_difference);
    static PEAK_ICV_API_STATUS peak_icv_Region_Intersection(peak_icv_region_handle input_region_1, peak_icv_region_handle input_region_2, peak_icv_region_handle* output_region_intersection);
    static PEAK_ICV_API_STATUS peak_icv_Region_Union(peak_icv_region_handle input_region_1, peak_icv_region_handle input_region_2, peak_icv_region_handle* output_region_united);
    static PEAK_ICV_API_STATUS peak_icv_Region_Dilation(peak_icv_region_handle input_region, peak_icv_region_handle input_structuring_element, peak_icv_region_handle* output_region_dilation);
    static PEAK_ICV_API_STATUS peak_icv_Region_Erosion(peak_icv_region_handle input_region, peak_icv_region_handle input_structuring_element, peak_icv_region_handle* output_region_erosion);
    static PEAK_ICV_API_STATUS peak_icv_Region_Compare(peak_icv_region_handle region_handle_lhs, peak_icv_region_handle region_handle_rhs, bool* is_equal);
    static PEAK_ICV_API_STATUS peak_icv_Region_Scale(peak_icv_region_handle input_region_handle, peak_common_size input_size, peak_common_size output_size, peak_icv_interpolation interpolation, peak_icv_region_handle* output_region_handle);
       
private:
    void* m_handle = nullptr;
    dyn_peak_icv_CalibrationParameters_CreateFromFile m_peak_icv_CalibrationParameters_CreateFromFile{};
    dyn_peak_icv_CalibrationParameters_SaveToFile m_peak_icv_CalibrationParameters_SaveToFile{};
    dyn_peak_icv_CalibrationParameters_ToBinary m_peak_icv_CalibrationParameters_ToBinary{};
    dyn_peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes m_peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes{};
    dyn_peak_icv_CalibrationParameters_CreateFromBinary m_peak_icv_CalibrationParameters_CreateFromBinary{};
    dyn_peak_icv_Calibration_Plate_Create m_peak_icv_Calibration_Plate_Create{};
    dyn_peak_icv_Calibration_Plate_CreateFromFile m_peak_icv_Calibration_Plate_CreateFromFile{};
    dyn_peak_icv_Calibration_Plate_IncreaseUseCount m_peak_icv_Calibration_Plate_IncreaseUseCount{};
    dyn_peak_icv_Calibration_Plate_Destroy m_peak_icv_Calibration_Plate_Destroy{};
    dyn_peak_icv_Calibration_Result_Create m_peak_icv_Calibration_Result_Create{};
    dyn_peak_icv_Calibration_Result_SaveToFile m_peak_icv_Calibration_Result_SaveToFile{};
    dyn_peak_icv_Calibration_Result_CreateFromFile m_peak_icv_Calibration_Result_CreateFromFile{};
    dyn_peak_icv_Calibration_Result_Destroy m_peak_icv_Calibration_Result_Destroy{};
    dyn_peak_icv_Calibration_Result_IncreaseUseCount m_peak_icv_Calibration_Result_IncreaseUseCount{};
    dyn_peak_icv_Calibration_Result_GetMeanReprojectionError m_peak_icv_Calibration_Result_GetMeanReprojectionError{};
    dyn_peak_icv_Calibration_Result_GetCalibrationViews_GetCount m_peak_icv_Calibration_Result_GetCalibrationViews_GetCount{};
    dyn_peak_icv_Calibration_Result_GetCalibrationViews m_peak_icv_Calibration_Result_GetCalibrationViews{};
    dyn_peak_icv_Calibration_Result_ToParameters m_peak_icv_Calibration_Result_ToParameters{};
    dyn_peak_icv_Calibration_View_Create m_peak_icv_Calibration_View_Create{};
    dyn_peak_icv_Calibration_View_Array_Create m_peak_icv_Calibration_View_Array_Create{};
    dyn_peak_icv_Calibration_View_IncreaseUseCount m_peak_icv_Calibration_View_IncreaseUseCount{};
    dyn_peak_icv_Calibration_View_Destroy m_peak_icv_Calibration_View_Destroy{};
    dyn_peak_icv_Calibration_View_Array_Destroy m_peak_icv_Calibration_View_Array_Destroy{};
    dyn_peak_icv_Calibration_View_GetReprojectionErrors m_peak_icv_Calibration_View_GetReprojectionErrors{};
    dyn_peak_icv_Calibration_View_GetMeanReprojectionError m_peak_icv_Calibration_View_GetMeanReprojectionError{};
    dyn_peak_icv_Calibration_View_GetMaximumReprojectionError m_peak_icv_Calibration_View_GetMaximumReprojectionError{};
    dyn_peak_icv_Calibration_View_GetReprojectionErrors_GetCount m_peak_icv_Calibration_View_GetReprojectionErrors_GetCount{};
    dyn_peak_icv_Calibration_View_GetExtrinsicParameters m_peak_icv_Calibration_View_GetExtrinsicParameters{};
    dyn_peak_icv_Calibration_View_GetConvexHull m_peak_icv_Calibration_View_GetConvexHull{};
    dyn_peak_icv_Calibration_View_GetCoordinateSystem m_peak_icv_Calibration_View_GetCoordinateSystem{};
    dyn_peak_icv_Calibration_Process m_peak_icv_Calibration_Process{};
    dyn_peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix m_peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix{};
    dyn_peak_icv_WorkspaceCalibration_Process m_peak_icv_WorkspaceCalibration_Process{};
    dyn_peak_icv_BarcodeReaderResult_Create m_peak_icv_BarcodeReaderResult_Create{};
    dyn_peak_icv_BarcodeReaderResult_Array_Create m_peak_icv_BarcodeReaderResult_Array_Create{};
    dyn_peak_icv_BarcodeReaderResult_Destroy m_peak_icv_BarcodeReaderResult_Destroy{};
    dyn_peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes m_peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes{};
    dyn_peak_icv_BarcodeReaderResult_GetText m_peak_icv_BarcodeReaderResult_GetText{};
    dyn_peak_icv_BarcodeReaderResult_GetType m_peak_icv_BarcodeReaderResult_GetType{};
    dyn_peak_icv_BarcodeReader_Create m_peak_icv_BarcodeReader_Create{};
    dyn_peak_icv_BarcodeReader_Destroy m_peak_icv_BarcodeReader_Destroy{};
    dyn_peak_icv_BarcodeReader_GetCodeTypesGetCount m_peak_icv_BarcodeReader_GetCodeTypesGetCount{};
    dyn_peak_icv_BarcodeReader_GetCodeTypes m_peak_icv_BarcodeReader_GetCodeTypes{};
    dyn_peak_icv_BarcodeReader_SetCodeTypes m_peak_icv_BarcodeReader_SetCodeTypes{};
    dyn_peak_icv_BarcodeReader_DetectAndDecode m_peak_icv_BarcodeReader_DetectAndDecode{};
    dyn_peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect m_peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect{};
    dyn_peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect m_peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect{};
    dyn_peak_icv_ImageFilter_Sharpening_ProcessInPlace m_peak_icv_ImageFilter_Sharpening_ProcessInPlace{};
    dyn_peak_icv_ImageFilter_Sharpening_GetRange m_peak_icv_ImageFilter_Sharpening_GetRange{};
    dyn_peak_icv_Filter_Image_Median m_peak_icv_Filter_Image_Median{};
    dyn_peak_icv_HDR_Create m_peak_icv_HDR_Create{};
    dyn_peak_icv_HDR_EstimateResponseCurve m_peak_icv_HDR_EstimateResponseCurve{};
    dyn_peak_icv_HDR_Process_GetOutputPixelFormat m_peak_icv_HDR_Process_GetOutputPixelFormat{};
    dyn_peak_icv_HDR_Process m_peak_icv_HDR_Process{};
    dyn_peak_icv_HDR_GetAlgorithm m_peak_icv_HDR_GetAlgorithm{};
    dyn_peak_icv_HDR_Destroy m_peak_icv_HDR_Destroy{};
    dyn_peak_icv_HDR_GetResponseCurve m_peak_icv_HDR_GetResponseCurve{};
    dyn_peak_icv_HDR_SetResponseCurve m_peak_icv_HDR_SetResponseCurve{};
    dyn_peak_icv_HDR_ResponseCurve_Create m_peak_icv_HDR_ResponseCurve_Create{};
    dyn_peak_icv_HDR_ResponseCurve_CreateFromFile m_peak_icv_HDR_ResponseCurve_CreateFromFile{};
    dyn_peak_icv_HDR_ResponseCurve_IncreaseUseCount m_peak_icv_HDR_ResponseCurve_IncreaseUseCount{};
    dyn_peak_icv_HDR_ResponseCurve_Destroy m_peak_icv_HDR_ResponseCurve_Destroy{};
    dyn_peak_icv_HDR_ResponseCurve_SaveToFile m_peak_icv_HDR_ResponseCurve_SaveToFile{};
    dyn_peak_icv_HDR_ResponseCurve_Compare m_peak_icv_HDR_ResponseCurve_Compare{};
    dyn_peak_icv_ToneMapping_Drago_Create m_peak_icv_ToneMapping_Drago_Create{};
    dyn_peak_icv_ToneMapping_Drago_Destroy m_peak_icv_ToneMapping_Drago_Destroy{};
    dyn_peak_icv_ToneMapping_Drago_GetOutputPixelFormat m_peak_icv_ToneMapping_Drago_GetOutputPixelFormat{};
    dyn_peak_icv_ToneMapping_Drago_Process m_peak_icv_ToneMapping_Drago_Process{};
    dyn_peak_icv_ToneMapping_Linear_Create m_peak_icv_ToneMapping_Linear_Create{};
    dyn_peak_icv_ToneMapping_Linear_Destroy m_peak_icv_ToneMapping_Linear_Destroy{};
    dyn_peak_icv_ToneMapping_Linear_GetOutputPixelFormat m_peak_icv_ToneMapping_Linear_GetOutputPixelFormat{};
    dyn_peak_icv_ToneMapping_Linear_Process m_peak_icv_ToneMapping_Linear_Process{};
    dyn_peak_icv_ToneMapping_Linear_GetExposureValueRange m_peak_icv_ToneMapping_Linear_GetExposureValueRange{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Create m_peak_icv_Preprocessing_ColorMatrixTransformation_Create{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Destroy m_peak_icv_Preprocessing_ColorMatrixTransformation_Destroy{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing m_peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace m_peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix m_peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix m_peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation m_peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix m_peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled{};
    dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled{};
    dyn_peak_icv_Preprocessing_Downsampling_Create m_peak_icv_Preprocessing_Downsampling_Create{};
    dyn_peak_icv_Preprocessing_Downsampling_Destroy m_peak_icv_Preprocessing_Downsampling_Destroy{};
    dyn_peak_icv_Preprocessing_Downsampling_SetFactor m_peak_icv_Preprocessing_Downsampling_SetFactor{};
    dyn_peak_icv_Preprocessing_Downsampling_GetFactor m_peak_icv_Preprocessing_Downsampling_GetFactor{};
    dyn_peak_icv_Preprocessing_Downsampling_GetRange m_peak_icv_Preprocessing_Downsampling_GetRange{};
    dyn_peak_icv_Preprocessing_Downsampling_SetMode m_peak_icv_Preprocessing_Downsampling_SetMode{};
    dyn_peak_icv_Preprocessing_Downsampling_GetMode m_peak_icv_Preprocessing_Downsampling_GetMode{};
    dyn_peak_icv_Preprocessing_Downsampling_GetOutputImageSize m_peak_icv_Preprocessing_Downsampling_GetOutputImageSize{};
    dyn_peak_icv_Preprocessing_Downsampling_NeedsProcessing m_peak_icv_Preprocessing_Downsampling_NeedsProcessing{};
    dyn_peak_icv_Preprocessing_Downsampling_Process m_peak_icv_Preprocessing_Downsampling_Process{};
    dyn_peak_icv_Preprocessing_Gain_Create m_peak_icv_Preprocessing_Gain_Create{};
    dyn_peak_icv_Preprocessing_Gain_Destroy m_peak_icv_Preprocessing_Gain_Destroy{};
    dyn_peak_icv_Preprocessing_Gain_ProcessInplace m_peak_icv_Preprocessing_Gain_ProcessInplace{};
    dyn_peak_icv_Preprocessing_Gain_NeedsProcessing m_peak_icv_Preprocessing_Gain_NeedsProcessing{};
    dyn_peak_icv_Preprocessing_Gain_SetValue m_peak_icv_Preprocessing_Gain_SetValue{};
    dyn_peak_icv_Preprocessing_Gain_GetValue m_peak_icv_Preprocessing_Gain_GetValue{};
    dyn_peak_icv_Preprocessing_Gain_GetRange m_peak_icv_Preprocessing_Gain_GetRange{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_Create m_peak_icv_Preprocessing_HotpixelCorrection_Create{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_Destroy m_peak_icv_Preprocessing_HotpixelCorrection_Destroy{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount m_peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_Detect m_peak_icv_Preprocessing_HotpixelCorrection_Detect{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace m_peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_SetList m_peak_icv_Preprocessing_HotpixelCorrection_SetList{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_ResetList m_peak_icv_Preprocessing_HotpixelCorrection_ResetList{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount m_peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_GetList m_peak_icv_Preprocessing_HotpixelCorrection_GetList{};
    dyn_peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange m_peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange{};
    dyn_peak_icv_Preprocessing_ImageConverter_Create m_peak_icv_Preprocessing_ImageConverter_Create{};
    dyn_peak_icv_Preprocessing_ImageConverter_Destroy m_peak_icv_Preprocessing_ImageConverter_Destroy{};
    dyn_peak_icv_Preprocessing_ImageConverter_Convert m_peak_icv_Preprocessing_ImageConverter_Convert{};
    dyn_peak_icv_Preprocessing_ImageConverter_ReleaseBuffers m_peak_icv_Preprocessing_ImageConverter_ReleaseBuffers{};
    dyn_peak_icv_Preprocessing_Transformation_GetOutputPixelFormat m_peak_icv_Preprocessing_Transformation_GetOutputPixelFormat{};
    dyn_peak_icv_Preprocessing_Transformation_Process m_peak_icv_Preprocessing_Transformation_Process{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_Create m_peak_icv_Preprocessing_ToneCurveCorrection_Create{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_Destroy m_peak_icv_Preprocessing_ToneCurveCorrection_Destroy{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange m_peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetGamma m_peak_icv_Preprocessing_ToneCurveCorrection_GetGamma{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_SetGamma m_peak_icv_Preprocessing_ToneCurveCorrection_SetGamma{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack m_peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing m_peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing{};
    dyn_peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace m_peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace{};
    dyn_peak_icv_Threshold_Process m_peak_icv_Threshold_Process{};
    dyn_peak_icv_Threshold_GetRange m_peak_icv_Threshold_GetRange{};
    dyn_peak_icv_Transform_Undistortion_Process m_peak_icv_Transform_Undistortion_Process{};
    dyn_peak_icv_Transform_Undistortion_Create m_peak_icv_Transform_Undistortion_Create{};
    dyn_peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation m_peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation{};
    dyn_peak_icv_Transform_Undistortion_CreateWithImageMetadata m_peak_icv_Transform_Undistortion_CreateWithImageMetadata{};
    dyn_peak_icv_Transform_Undistortion_IncreaseUseCount m_peak_icv_Transform_Undistortion_IncreaseUseCount{};
    dyn_peak_icv_Transform_Undistortion_Destroy m_peak_icv_Transform_Undistortion_Destroy{};
    dyn_peak_icv_Transform_Undistortion_SetInterpolation m_peak_icv_Transform_Undistortion_SetInterpolation{};
    dyn_peak_icv_Transform_Undistortion_GetInterpolation m_peak_icv_Transform_Undistortion_GetInterpolation{};
    dyn_peak_icv_Transform_DepthMap_To_XYZImage m_peak_icv_Transform_DepthMap_To_XYZImage{};
    dyn_peak_icv_ValidateBinary m_peak_icv_ValidateBinary{};
    dyn_peak_icv_Init m_peak_icv_Init{};
    dyn_peak_icv_Exit m_peak_icv_Exit{};
    dyn_peak_icv_GetVersion m_peak_icv_GetVersion{};
    dyn_peak_icv_GetLastErrorMessage_GetCount m_peak_icv_GetLastErrorMessage_GetCount{};
    dyn_peak_icv_GetLastErrorMessage m_peak_icv_GetLastErrorMessage{};
    dyn_peak_icv_Region_Draw m_peak_icv_Region_Draw{};
    dyn_peak_icv_Region_SelectByArea_GetCount m_peak_icv_Region_SelectByArea_GetCount{};
    dyn_peak_icv_Region_SelectByArea m_peak_icv_Region_SelectByArea{};
    dyn_peak_icv_Region_SelectByCenterOfGravityX_GetCount m_peak_icv_Region_SelectByCenterOfGravityX_GetCount{};
    dyn_peak_icv_Region_SelectByCenterOfGravityX m_peak_icv_Region_SelectByCenterOfGravityX{};
    dyn_peak_icv_Region_SelectByCenterOfGravityY_GetCount m_peak_icv_Region_SelectByCenterOfGravityY_GetCount{};
    dyn_peak_icv_Region_SelectByCenterOfGravityY m_peak_icv_Region_SelectByCenterOfGravityY{};
    dyn_peak_icv_Region_SelectByCenterOfGravityRect_GetCount m_peak_icv_Region_SelectByCenterOfGravityRect_GetCount{};
    dyn_peak_icv_Region_SelectByCenterOfGravityRect m_peak_icv_Region_SelectByCenterOfGravityRect{};
    dyn_peak_icv_Archive_Create m_peak_icv_Archive_Create{};
    dyn_peak_icv_Archive_CreateFromString m_peak_icv_Archive_CreateFromString{};
    dyn_peak_icv_Archive_Destroy m_peak_icv_Archive_Destroy{};
    dyn_peak_icv_Archive_HasKey m_peak_icv_Archive_HasKey{};
    dyn_peak_icv_Archive_GetKeys_GetCount m_peak_icv_Archive_GetKeys_GetCount{};
    dyn_peak_icv_Archive_GetKeysElement_GetSizeInBytes m_peak_icv_Archive_GetKeysElement_GetSizeInBytes{};
    dyn_peak_icv_Archive_GetKeysElement m_peak_icv_Archive_GetKeysElement{};
    dyn_peak_icv_Archive_GetValueType m_peak_icv_Archive_GetValueType{};
    dyn_peak_icv_Archive_GetArray_GetCount m_peak_icv_Archive_GetArray_GetCount{};
    dyn_peak_icv_Archive_GetInt m_peak_icv_Archive_GetInt{};
    dyn_peak_icv_Archive_SetInt m_peak_icv_Archive_SetInt{};
    dyn_peak_icv_Archive_GetIntArray m_peak_icv_Archive_GetIntArray{};
    dyn_peak_icv_Archive_SetIntArray m_peak_icv_Archive_SetIntArray{};
    dyn_peak_icv_Archive_GetDouble m_peak_icv_Archive_GetDouble{};
    dyn_peak_icv_Archive_SetDouble m_peak_icv_Archive_SetDouble{};
    dyn_peak_icv_Archive_GetDoubleArray m_peak_icv_Archive_GetDoubleArray{};
    dyn_peak_icv_Archive_SetDoubleArray m_peak_icv_Archive_SetDoubleArray{};
    dyn_peak_icv_Archive_GetBool m_peak_icv_Archive_GetBool{};
    dyn_peak_icv_Archive_SetBool m_peak_icv_Archive_SetBool{};
    dyn_peak_icv_Archive_GetBoolArray m_peak_icv_Archive_GetBoolArray{};
    dyn_peak_icv_Archive_SetBoolArray m_peak_icv_Archive_SetBoolArray{};
    dyn_peak_icv_Archive_GetString_GetSizeInBytes m_peak_icv_Archive_GetString_GetSizeInBytes{};
    dyn_peak_icv_Archive_GetString m_peak_icv_Archive_GetString{};
    dyn_peak_icv_Archive_SetString m_peak_icv_Archive_SetString{};
    dyn_peak_icv_Archive_GetStringArrayElement_GetSizeInBytes m_peak_icv_Archive_GetStringArrayElement_GetSizeInBytes{};
    dyn_peak_icv_Archive_GetStringArrayElement m_peak_icv_Archive_GetStringArrayElement{};
    dyn_peak_icv_Archive_SetStringArray m_peak_icv_Archive_SetStringArray{};
    dyn_peak_icv_Archive_GetArchive m_peak_icv_Archive_GetArchive{};
    dyn_peak_icv_Archive_SetArchive m_peak_icv_Archive_SetArchive{};
    dyn_peak_icv_Archive_GetArchiveArray m_peak_icv_Archive_GetArchiveArray{};
    dyn_peak_icv_Archive_SetArchiveArray m_peak_icv_Archive_SetArchiveArray{};
    dyn_peak_icv_Archive_ToString_GetSizeInBytes m_peak_icv_Archive_ToString_GetSizeInBytes{};
    dyn_peak_icv_Archive_ToString m_peak_icv_Archive_ToString{};
    dyn_peak_icv_Buffer_CutBytes m_peak_icv_Buffer_CutBytes{};
    dyn_peak_icv_Image_Create m_peak_icv_Image_Create{};
    dyn_peak_icv_Image_CreateWithZeroInit m_peak_icv_Image_CreateWithZeroInit{};
    dyn_peak_icv_Image_CreateFromImageInfo m_peak_icv_Image_CreateFromImageInfo{};
    dyn_peak_icv_Image_CreateFromFile m_peak_icv_Image_CreateFromFile{};
    dyn_peak_icv_Image_CreateFromFileWithPixelFormat m_peak_icv_Image_CreateFromFileWithPixelFormat{};
    dyn_peak_icv_Image_CreateFromExistingImage m_peak_icv_Image_CreateFromExistingImage{};
    dyn_peak_icv_Image_SaveToFile m_peak_icv_Image_SaveToFile{};
    dyn_peak_icv_Image_IncreaseUseCount m_peak_icv_Image_IncreaseUseCount{};
    dyn_peak_icv_Image_Destroy m_peak_icv_Image_Destroy{};
    dyn_peak_icv_Image_ConvertPixelFormat m_peak_icv_Image_ConvertPixelFormat{};
    dyn_peak_icv_Image_ConvertPixelFormatWithFactor m_peak_icv_Image_ConvertPixelFormatWithFactor{};
    dyn_peak_icv_Image_GetInfo m_peak_icv_Image_GetInfo{};
    dyn_peak_icv_Image_GetRegion m_peak_icv_Image_GetRegion{};
    dyn_peak_icv_Image_SetRegion m_peak_icv_Image_SetRegion{};
    dyn_peak_icv_Image_ResetRegion m_peak_icv_Image_ResetRegion{};
    dyn_peak_icv_Image_Compare m_peak_icv_Image_Compare{};
    dyn_peak_icv_Image_GetCaptureInformation m_peak_icv_Image_GetCaptureInformation{};
    dyn_peak_icv_Image_SetCaptureInformation m_peak_icv_Image_SetCaptureInformation{};
    dyn_peak_icv_Image_Subtract m_peak_icv_Image_Subtract{};
    dyn_peak_icv_Image_TransformToWorkspace m_peak_icv_Image_TransformToWorkspace{};
    dyn_peak_icv_Image_Crop m_peak_icv_Image_Crop{};
    dyn_peak_icv_Image_Scale m_peak_icv_Image_Scale{};
    dyn_peak_icv_Image_Deinterleave m_peak_icv_Image_Deinterleave{};
    dyn_peak_icv_Image_Deinterleave_GetOutputPixelFormat m_peak_icv_Image_Deinterleave_GetOutputPixelFormat{};
    dyn_peak_icv_Image_Deinterleave_GetOutputImageCount m_peak_icv_Image_Deinterleave_GetOutputImageCount{};
    dyn_peak_icv_Image_Deinterleave_GetOutputImageSize m_peak_icv_Image_Deinterleave_GetOutputImageSize{};
    dyn_peak_icv_Image_GetMetadata m_peak_icv_Image_GetMetadata{};
    dyn_peak_icv_Image_SetMetadata m_peak_icv_Image_SetMetadata{};
    dyn_peak_icv_Metadata_Create m_peak_icv_Metadata_Create{};
    dyn_peak_icv_Metadata_Destroy m_peak_icv_Metadata_Destroy{};
    dyn_peak_icv_Metadata_GetInt m_peak_icv_Metadata_GetInt{};
    dyn_peak_icv_Metadata_SetInt m_peak_icv_Metadata_SetInt{};
    dyn_peak_icv_Metadata_GetIntArray m_peak_icv_Metadata_GetIntArray{};
    dyn_peak_icv_Metadata_SetIntArray m_peak_icv_Metadata_SetIntArray{};
    dyn_peak_icv_Metadata_GetUInt m_peak_icv_Metadata_GetUInt{};
    dyn_peak_icv_Metadata_SetUInt m_peak_icv_Metadata_SetUInt{};
    dyn_peak_icv_Metadata_GetUIntArray m_peak_icv_Metadata_GetUIntArray{};
    dyn_peak_icv_Metadata_SetUIntArray m_peak_icv_Metadata_SetUIntArray{};
    dyn_peak_icv_Metadata_GetDouble m_peak_icv_Metadata_GetDouble{};
    dyn_peak_icv_Metadata_SetDouble m_peak_icv_Metadata_SetDouble{};
    dyn_peak_icv_Metadata_GetDoubleArray m_peak_icv_Metadata_GetDoubleArray{};
    dyn_peak_icv_Metadata_SetDoubleArray m_peak_icv_Metadata_SetDoubleArray{};
    dyn_peak_icv_Metadata_GetBool m_peak_icv_Metadata_GetBool{};
    dyn_peak_icv_Metadata_SetBool m_peak_icv_Metadata_SetBool{};
    dyn_peak_icv_Metadata_GetBoolArray m_peak_icv_Metadata_GetBoolArray{};
    dyn_peak_icv_Metadata_SetBoolArray m_peak_icv_Metadata_SetBoolArray{};
    dyn_peak_icv_Metadata_GetString_GetSizeInBytes m_peak_icv_Metadata_GetString_GetSizeInBytes{};
    dyn_peak_icv_Metadata_GetString m_peak_icv_Metadata_GetString{};
    dyn_peak_icv_Metadata_SetString m_peak_icv_Metadata_SetString{};
    dyn_peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes m_peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes{};
    dyn_peak_icv_Metadata_GetStringArrayElement m_peak_icv_Metadata_GetStringArrayElement{};
    dyn_peak_icv_Metadata_SetStringArray m_peak_icv_Metadata_SetStringArray{};
    dyn_peak_icv_Metadata_GetArray_GetCount m_peak_icv_Metadata_GetArray_GetCount{};
    dyn_peak_icv_Metadata_HasKey m_peak_icv_Metadata_HasKey{};
    dyn_peak_icv_Metadata_GetEntryCount m_peak_icv_Metadata_GetEntryCount{};
    dyn_peak_icv_Metadata_GetKey_GetSizeInBytes m_peak_icv_Metadata_GetKey_GetSizeInBytes{};
    dyn_peak_icv_Metadata_GetKey m_peak_icv_Metadata_GetKey{};
    dyn_peak_icv_Metadata_GetValueType m_peak_icv_Metadata_GetValueType{};
    dyn_peak_icv_PointCloud_Create m_peak_icv_PointCloud_Create{};
    dyn_peak_icv_PointCloud_CreateFromXYZImage m_peak_icv_PointCloud_CreateFromXYZImage{};
    dyn_peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage m_peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage{};
    dyn_peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage m_peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage{};
    dyn_peak_icv_PointCloud_CreateFromFile m_peak_icv_PointCloud_CreateFromFile{};
    dyn_peak_icv_PointCloud_CreateFromPoints m_peak_icv_PointCloud_CreateFromPoints{};
    dyn_peak_icv_PointCloud_IncreaseUseCount m_peak_icv_PointCloud_IncreaseUseCount{};
    dyn_peak_icv_PointCloud_Destroy m_peak_icv_PointCloud_Destroy{};
    dyn_peak_icv_PointCloud_GetType m_peak_icv_PointCloud_GetType{};
    dyn_peak_icv_PointCloud_GetPoints_GetCount m_peak_icv_PointCloud_GetPoints_GetCount{};
    dyn_peak_icv_PointCloud_GetPoints_GetSizeInBytes m_peak_icv_PointCloud_GetPoints_GetSizeInBytes{};
    dyn_peak_icv_PointCloud_GetPoints m_peak_icv_PointCloud_GetPoints{};
    dyn_peak_icv_PointCloud_SaveToFile m_peak_icv_PointCloud_SaveToFile{};
    dyn_peak_icv_PointCloud_Transform m_peak_icv_PointCloud_Transform{};
    dyn_peak_icv_PointCloud_TransformToWorkspace m_peak_icv_PointCloud_TransformToWorkspace{};
    dyn_peak_icv_Polygon_Create m_peak_icv_Polygon_Create{};
    dyn_peak_icv_Polygon_CreateFromPoints m_peak_icv_Polygon_CreateFromPoints{};
    dyn_peak_icv_Polygon_Destroy m_peak_icv_Polygon_Destroy{};
    dyn_peak_icv_Polygon_IncreaseUseCount m_peak_icv_Polygon_IncreaseUseCount{};
    dyn_peak_icv_Polygon_GetPoints_GetCount m_peak_icv_Polygon_GetPoints_GetCount{};
    dyn_peak_icv_Polygon_GetPointType m_peak_icv_Polygon_GetPointType{};
    dyn_peak_icv_Polygon_IsClosed m_peak_icv_Polygon_IsClosed{};
    dyn_peak_icv_Polygon_GetPoints_GetSizeInBytes m_peak_icv_Polygon_GetPoints_GetSizeInBytes{};
    dyn_peak_icv_Polygon_GetPoints m_peak_icv_Polygon_GetPoints{};
    dyn_peak_icv_Region_Create m_peak_icv_Region_Create{};
    dyn_peak_icv_Region_CreateFromPoints m_peak_icv_Region_CreateFromPoints{};
    dyn_peak_icv_Region_CreateFromRectangle m_peak_icv_Region_CreateFromRectangle{};
    dyn_peak_icv_Region_IncreaseUseCount m_peak_icv_Region_IncreaseUseCount{};
    dyn_peak_icv_Region_Destroy m_peak_icv_Region_Destroy{};
    dyn_peak_icv_Region_Array_Create m_peak_icv_Region_Array_Create{};
    dyn_peak_icv_Region_Array_Destroy m_peak_icv_Region_Array_Destroy{};
    dyn_peak_icv_Region_GetConnectedComponents_GetCount m_peak_icv_Region_GetConnectedComponents_GetCount{};
    dyn_peak_icv_Region_GetConnectedComponents m_peak_icv_Region_GetConnectedComponents{};
    dyn_peak_icv_Region_GetArea m_peak_icv_Region_GetArea{};
    dyn_peak_icv_Region_GetCenterOfGravity m_peak_icv_Region_GetCenterOfGravity{};
    dyn_peak_icv_Region_GetPoints_GetCount m_peak_icv_Region_GetPoints_GetCount{};
    dyn_peak_icv_Region_GetPoints m_peak_icv_Region_GetPoints{};
    dyn_peak_icv_Region_Difference m_peak_icv_Region_Difference{};
    dyn_peak_icv_Region_Intersection m_peak_icv_Region_Intersection{};
    dyn_peak_icv_Region_Union m_peak_icv_Region_Union{};
    dyn_peak_icv_Region_Dilation m_peak_icv_Region_Dilation{};
    dyn_peak_icv_Region_Erosion m_peak_icv_Region_Erosion{};
    dyn_peak_icv_Region_Compare m_peak_icv_Region_Compare{};
    dyn_peak_icv_Region_Scale m_peak_icv_Region_Scale{};

};

inline void* import_function(void *module, const char* proc_name)
{
#ifdef __linux__
    return dlsym(module, proc_name);
#else
    return reinterpret_cast<void*>(GetProcAddress(static_cast<HMODULE>(module), proc_name));
#endif
}
            
inline DynamicLoader::DynamicLoader()
{
#if defined _WIN32 || defined _WIN64
    size_t sz = 0;
    if (_wgetenv_s(&sz, NULL, 0, L"IDS_PEAK_GENERIC_SDK_PATH") == 0
        && sz > 0)
    {
        std::vector<wchar_t> env_ids_peak_icv(sz);
        if (_wgetenv_s(&sz, env_ids_peak_icv.data(), sz, L"IDS_PEAK_GENERIC_SDK_PATH") == 0)
        {
            if (_wgetenv_s(&sz, NULL, 0, L"PATH") == 0
                && sz > 0)
            {
                std::vector<wchar_t> env_path(sz);
                if (_wgetenv_s(&sz, env_path.data(), sz, L"PATH") == 0)
                {
                    std::wstring ids_peak_icv_path(env_ids_peak_icv.data());
#ifdef _WIN64
                    ids_peak_icv_path.append(L"\\icv\\lib\\x86_64");
#else
                    ids_peak_icv_path.append(L"\\icv\\lib\\x86_32");
#endif
                    AddDllDirectory(ids_peak_icv_path.c_str());
                }
            }
        }
    }
    
    loadLib("ids_peak_icv.dll");
#else
    loadLib("libids_peak_icv.so");
#endif
}

inline DynamicLoader::~DynamicLoader()
{
    if(m_handle != nullptr)
    {
        unload();
    }
}

inline bool DynamicLoader::isLoaded()
{
    auto&& inst = instance();
    return inst.m_handle != nullptr;
}

inline void DynamicLoader::unload()
{
    setPointers(false);
    
    if (m_handle != nullptr)
    {
#ifdef __linux__
        dlclose(m_handle);
#else
        FreeLibrary(static_cast<HMODULE>(m_handle));
#endif
    }
    m_handle = nullptr;
}


inline bool DynamicLoader::loadLib(const char* file)
{
    bool ret = false;
    
    if (file)
    {
#ifdef __linux__
        m_handle = dlopen(file, RTLD_NOW);
#else
        m_handle = LoadLibraryExA(file, nullptr, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
#endif
        if (m_handle != nullptr)
        {
            try {
                setPointers(true);
                ret = true;
            } catch (const std::exception&) {
                unload();
                throw;
            }
        }
        else
        {
            throw LoadLibraryException(std::string("Lib load failed: ") + file);
        }
    }
    else
    {
        throw LoadLibraryException("Filename empty");
    }

    return ret;
}

inline bool DynamicLoader::setPointers(bool load)
{

    m_peak_icv_CalibrationParameters_CreateFromFile = reinterpret_cast<dyn_peak_icv_CalibrationParameters_CreateFromFile>(load ? import_function(m_handle, "peak_icv_CalibrationParameters_CreateFromFile") : nullptr);
    if(m_peak_icv_CalibrationParameters_CreateFromFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_CalibrationParameters_CreateFromFile");
    }        

    m_peak_icv_CalibrationParameters_SaveToFile = reinterpret_cast<dyn_peak_icv_CalibrationParameters_SaveToFile>(load ? import_function(m_handle, "peak_icv_CalibrationParameters_SaveToFile") : nullptr);
    if(m_peak_icv_CalibrationParameters_SaveToFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_CalibrationParameters_SaveToFile");
    }        

    m_peak_icv_CalibrationParameters_ToBinary = reinterpret_cast<dyn_peak_icv_CalibrationParameters_ToBinary>(load ? import_function(m_handle, "peak_icv_CalibrationParameters_ToBinary") : nullptr);
    if(m_peak_icv_CalibrationParameters_ToBinary == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_CalibrationParameters_ToBinary");
    }        

    m_peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes = reinterpret_cast<dyn_peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes>(load ? import_function(m_handle, "peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes") : nullptr);
    if(m_peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes");
    }        

    m_peak_icv_CalibrationParameters_CreateFromBinary = reinterpret_cast<dyn_peak_icv_CalibrationParameters_CreateFromBinary>(load ? import_function(m_handle, "peak_icv_CalibrationParameters_CreateFromBinary") : nullptr);
    if(m_peak_icv_CalibrationParameters_CreateFromBinary == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_CalibrationParameters_CreateFromBinary");
    }        

    m_peak_icv_Calibration_Plate_Create = reinterpret_cast<dyn_peak_icv_Calibration_Plate_Create>(load ? import_function(m_handle, "peak_icv_Calibration_Plate_Create") : nullptr);
    if(m_peak_icv_Calibration_Plate_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Plate_Create");
    }        

    m_peak_icv_Calibration_Plate_CreateFromFile = reinterpret_cast<dyn_peak_icv_Calibration_Plate_CreateFromFile>(load ? import_function(m_handle, "peak_icv_Calibration_Plate_CreateFromFile") : nullptr);
    if(m_peak_icv_Calibration_Plate_CreateFromFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Plate_CreateFromFile");
    }        

    m_peak_icv_Calibration_Plate_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_Calibration_Plate_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_Calibration_Plate_IncreaseUseCount") : nullptr);
    if(m_peak_icv_Calibration_Plate_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Plate_IncreaseUseCount");
    }        

    m_peak_icv_Calibration_Plate_Destroy = reinterpret_cast<dyn_peak_icv_Calibration_Plate_Destroy>(load ? import_function(m_handle, "peak_icv_Calibration_Plate_Destroy") : nullptr);
    if(m_peak_icv_Calibration_Plate_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Plate_Destroy");
    }        

    m_peak_icv_Calibration_Result_Create = reinterpret_cast<dyn_peak_icv_Calibration_Result_Create>(load ? import_function(m_handle, "peak_icv_Calibration_Result_Create") : nullptr);
    if(m_peak_icv_Calibration_Result_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_Create");
    }        

    m_peak_icv_Calibration_Result_SaveToFile = reinterpret_cast<dyn_peak_icv_Calibration_Result_SaveToFile>(load ? import_function(m_handle, "peak_icv_Calibration_Result_SaveToFile") : nullptr);
    if(m_peak_icv_Calibration_Result_SaveToFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_SaveToFile");
    }        

    m_peak_icv_Calibration_Result_CreateFromFile = reinterpret_cast<dyn_peak_icv_Calibration_Result_CreateFromFile>(load ? import_function(m_handle, "peak_icv_Calibration_Result_CreateFromFile") : nullptr);
    if(m_peak_icv_Calibration_Result_CreateFromFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_CreateFromFile");
    }        

    m_peak_icv_Calibration_Result_Destroy = reinterpret_cast<dyn_peak_icv_Calibration_Result_Destroy>(load ? import_function(m_handle, "peak_icv_Calibration_Result_Destroy") : nullptr);
    if(m_peak_icv_Calibration_Result_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_Destroy");
    }        

    m_peak_icv_Calibration_Result_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_Calibration_Result_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_Calibration_Result_IncreaseUseCount") : nullptr);
    if(m_peak_icv_Calibration_Result_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_IncreaseUseCount");
    }        

    m_peak_icv_Calibration_Result_GetMeanReprojectionError = reinterpret_cast<dyn_peak_icv_Calibration_Result_GetMeanReprojectionError>(load ? import_function(m_handle, "peak_icv_Calibration_Result_GetMeanReprojectionError") : nullptr);
    if(m_peak_icv_Calibration_Result_GetMeanReprojectionError == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_GetMeanReprojectionError");
    }        

    m_peak_icv_Calibration_Result_GetCalibrationViews_GetCount = reinterpret_cast<dyn_peak_icv_Calibration_Result_GetCalibrationViews_GetCount>(load ? import_function(m_handle, "peak_icv_Calibration_Result_GetCalibrationViews_GetCount") : nullptr);
    if(m_peak_icv_Calibration_Result_GetCalibrationViews_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_GetCalibrationViews_GetCount");
    }        

    m_peak_icv_Calibration_Result_GetCalibrationViews = reinterpret_cast<dyn_peak_icv_Calibration_Result_GetCalibrationViews>(load ? import_function(m_handle, "peak_icv_Calibration_Result_GetCalibrationViews") : nullptr);
    if(m_peak_icv_Calibration_Result_GetCalibrationViews == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_GetCalibrationViews");
    }        

    m_peak_icv_Calibration_Result_ToParameters = reinterpret_cast<dyn_peak_icv_Calibration_Result_ToParameters>(load ? import_function(m_handle, "peak_icv_Calibration_Result_ToParameters") : nullptr);
    if(m_peak_icv_Calibration_Result_ToParameters == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Result_ToParameters");
    }        

    m_peak_icv_Calibration_View_Create = reinterpret_cast<dyn_peak_icv_Calibration_View_Create>(load ? import_function(m_handle, "peak_icv_Calibration_View_Create") : nullptr);
    if(m_peak_icv_Calibration_View_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_Create");
    }        

    m_peak_icv_Calibration_View_Array_Create = reinterpret_cast<dyn_peak_icv_Calibration_View_Array_Create>(load ? import_function(m_handle, "peak_icv_Calibration_View_Array_Create") : nullptr);
    if(m_peak_icv_Calibration_View_Array_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_Array_Create");
    }        

    m_peak_icv_Calibration_View_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_Calibration_View_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_Calibration_View_IncreaseUseCount") : nullptr);
    if(m_peak_icv_Calibration_View_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_IncreaseUseCount");
    }        

    m_peak_icv_Calibration_View_Destroy = reinterpret_cast<dyn_peak_icv_Calibration_View_Destroy>(load ? import_function(m_handle, "peak_icv_Calibration_View_Destroy") : nullptr);
    if(m_peak_icv_Calibration_View_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_Destroy");
    }        

    m_peak_icv_Calibration_View_Array_Destroy = reinterpret_cast<dyn_peak_icv_Calibration_View_Array_Destroy>(load ? import_function(m_handle, "peak_icv_Calibration_View_Array_Destroy") : nullptr);
    if(m_peak_icv_Calibration_View_Array_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_Array_Destroy");
    }        

    m_peak_icv_Calibration_View_GetReprojectionErrors = reinterpret_cast<dyn_peak_icv_Calibration_View_GetReprojectionErrors>(load ? import_function(m_handle, "peak_icv_Calibration_View_GetReprojectionErrors") : nullptr);
    if(m_peak_icv_Calibration_View_GetReprojectionErrors == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_GetReprojectionErrors");
    }        

    m_peak_icv_Calibration_View_GetMeanReprojectionError = reinterpret_cast<dyn_peak_icv_Calibration_View_GetMeanReprojectionError>(load ? import_function(m_handle, "peak_icv_Calibration_View_GetMeanReprojectionError") : nullptr);
    if(m_peak_icv_Calibration_View_GetMeanReprojectionError == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_GetMeanReprojectionError");
    }        

    m_peak_icv_Calibration_View_GetMaximumReprojectionError = reinterpret_cast<dyn_peak_icv_Calibration_View_GetMaximumReprojectionError>(load ? import_function(m_handle, "peak_icv_Calibration_View_GetMaximumReprojectionError") : nullptr);
    if(m_peak_icv_Calibration_View_GetMaximumReprojectionError == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_GetMaximumReprojectionError");
    }        

    m_peak_icv_Calibration_View_GetReprojectionErrors_GetCount = reinterpret_cast<dyn_peak_icv_Calibration_View_GetReprojectionErrors_GetCount>(load ? import_function(m_handle, "peak_icv_Calibration_View_GetReprojectionErrors_GetCount") : nullptr);
    if(m_peak_icv_Calibration_View_GetReprojectionErrors_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_GetReprojectionErrors_GetCount");
    }        

    m_peak_icv_Calibration_View_GetExtrinsicParameters = reinterpret_cast<dyn_peak_icv_Calibration_View_GetExtrinsicParameters>(load ? import_function(m_handle, "peak_icv_Calibration_View_GetExtrinsicParameters") : nullptr);
    if(m_peak_icv_Calibration_View_GetExtrinsicParameters == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_GetExtrinsicParameters");
    }        

    m_peak_icv_Calibration_View_GetConvexHull = reinterpret_cast<dyn_peak_icv_Calibration_View_GetConvexHull>(load ? import_function(m_handle, "peak_icv_Calibration_View_GetConvexHull") : nullptr);
    if(m_peak_icv_Calibration_View_GetConvexHull == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_GetConvexHull");
    }        

    m_peak_icv_Calibration_View_GetCoordinateSystem = reinterpret_cast<dyn_peak_icv_Calibration_View_GetCoordinateSystem>(load ? import_function(m_handle, "peak_icv_Calibration_View_GetCoordinateSystem") : nullptr);
    if(m_peak_icv_Calibration_View_GetCoordinateSystem == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_View_GetCoordinateSystem");
    }        

    m_peak_icv_Calibration_Process = reinterpret_cast<dyn_peak_icv_Calibration_Process>(load ? import_function(m_handle, "peak_icv_Calibration_Process") : nullptr);
    if(m_peak_icv_Calibration_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Process");
    }        

    m_peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix = reinterpret_cast<dyn_peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix>(load ? import_function(m_handle, "peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix") : nullptr);
    if(m_peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix");
    }        

    m_peak_icv_WorkspaceCalibration_Process = reinterpret_cast<dyn_peak_icv_WorkspaceCalibration_Process>(load ? import_function(m_handle, "peak_icv_WorkspaceCalibration_Process") : nullptr);
    if(m_peak_icv_WorkspaceCalibration_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_WorkspaceCalibration_Process");
    }        

    m_peak_icv_BarcodeReaderResult_Create = reinterpret_cast<dyn_peak_icv_BarcodeReaderResult_Create>(load ? import_function(m_handle, "peak_icv_BarcodeReaderResult_Create") : nullptr);
    if(m_peak_icv_BarcodeReaderResult_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReaderResult_Create");
    }        

    m_peak_icv_BarcodeReaderResult_Array_Create = reinterpret_cast<dyn_peak_icv_BarcodeReaderResult_Array_Create>(load ? import_function(m_handle, "peak_icv_BarcodeReaderResult_Array_Create") : nullptr);
    if(m_peak_icv_BarcodeReaderResult_Array_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReaderResult_Array_Create");
    }        

    m_peak_icv_BarcodeReaderResult_Destroy = reinterpret_cast<dyn_peak_icv_BarcodeReaderResult_Destroy>(load ? import_function(m_handle, "peak_icv_BarcodeReaderResult_Destroy") : nullptr);
    if(m_peak_icv_BarcodeReaderResult_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReaderResult_Destroy");
    }        

    m_peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes") : nullptr);
    if(m_peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes");
    }        

    m_peak_icv_BarcodeReaderResult_GetText = reinterpret_cast<dyn_peak_icv_BarcodeReaderResult_GetText>(load ? import_function(m_handle, "peak_icv_BarcodeReaderResult_GetText") : nullptr);
    if(m_peak_icv_BarcodeReaderResult_GetText == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReaderResult_GetText");
    }        

    m_peak_icv_BarcodeReaderResult_GetType = reinterpret_cast<dyn_peak_icv_BarcodeReaderResult_GetType>(load ? import_function(m_handle, "peak_icv_BarcodeReaderResult_GetType") : nullptr);
    if(m_peak_icv_BarcodeReaderResult_GetType == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReaderResult_GetType");
    }        

    m_peak_icv_BarcodeReader_Create = reinterpret_cast<dyn_peak_icv_BarcodeReader_Create>(load ? import_function(m_handle, "peak_icv_BarcodeReader_Create") : nullptr);
    if(m_peak_icv_BarcodeReader_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReader_Create");
    }        

    m_peak_icv_BarcodeReader_Destroy = reinterpret_cast<dyn_peak_icv_BarcodeReader_Destroy>(load ? import_function(m_handle, "peak_icv_BarcodeReader_Destroy") : nullptr);
    if(m_peak_icv_BarcodeReader_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReader_Destroy");
    }        

    m_peak_icv_BarcodeReader_GetCodeTypesGetCount = reinterpret_cast<dyn_peak_icv_BarcodeReader_GetCodeTypesGetCount>(load ? import_function(m_handle, "peak_icv_BarcodeReader_GetCodeTypesGetCount") : nullptr);
    if(m_peak_icv_BarcodeReader_GetCodeTypesGetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReader_GetCodeTypesGetCount");
    }        

    m_peak_icv_BarcodeReader_GetCodeTypes = reinterpret_cast<dyn_peak_icv_BarcodeReader_GetCodeTypes>(load ? import_function(m_handle, "peak_icv_BarcodeReader_GetCodeTypes") : nullptr);
    if(m_peak_icv_BarcodeReader_GetCodeTypes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReader_GetCodeTypes");
    }        

    m_peak_icv_BarcodeReader_SetCodeTypes = reinterpret_cast<dyn_peak_icv_BarcodeReader_SetCodeTypes>(load ? import_function(m_handle, "peak_icv_BarcodeReader_SetCodeTypes") : nullptr);
    if(m_peak_icv_BarcodeReader_SetCodeTypes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReader_SetCodeTypes");
    }        

    m_peak_icv_BarcodeReader_DetectAndDecode = reinterpret_cast<dyn_peak_icv_BarcodeReader_DetectAndDecode>(load ? import_function(m_handle, "peak_icv_BarcodeReader_DetectAndDecode") : nullptr);
    if(m_peak_icv_BarcodeReader_DetectAndDecode == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReader_DetectAndDecode");
    }        

    m_peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect = reinterpret_cast<dyn_peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect>(load ? import_function(m_handle, "peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect") : nullptr);
    if(m_peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect");
    }        

    m_peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect = reinterpret_cast<dyn_peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect>(load ? import_function(m_handle, "peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect") : nullptr);
    if(m_peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect");
    }        

    m_peak_icv_ImageFilter_Sharpening_ProcessInPlace = reinterpret_cast<dyn_peak_icv_ImageFilter_Sharpening_ProcessInPlace>(load ? import_function(m_handle, "peak_icv_ImageFilter_Sharpening_ProcessInPlace") : nullptr);
    if(m_peak_icv_ImageFilter_Sharpening_ProcessInPlace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ImageFilter_Sharpening_ProcessInPlace");
    }        

    m_peak_icv_ImageFilter_Sharpening_GetRange = reinterpret_cast<dyn_peak_icv_ImageFilter_Sharpening_GetRange>(load ? import_function(m_handle, "peak_icv_ImageFilter_Sharpening_GetRange") : nullptr);
    if(m_peak_icv_ImageFilter_Sharpening_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ImageFilter_Sharpening_GetRange");
    }        

    m_peak_icv_Filter_Image_Median = reinterpret_cast<dyn_peak_icv_Filter_Image_Median>(load ? import_function(m_handle, "peak_icv_Filter_Image_Median") : nullptr);
    if(m_peak_icv_Filter_Image_Median == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Filter_Image_Median");
    }        

    m_peak_icv_HDR_Create = reinterpret_cast<dyn_peak_icv_HDR_Create>(load ? import_function(m_handle, "peak_icv_HDR_Create") : nullptr);
    if(m_peak_icv_HDR_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_Create");
    }        

    m_peak_icv_HDR_EstimateResponseCurve = reinterpret_cast<dyn_peak_icv_HDR_EstimateResponseCurve>(load ? import_function(m_handle, "peak_icv_HDR_EstimateResponseCurve") : nullptr);
    if(m_peak_icv_HDR_EstimateResponseCurve == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_EstimateResponseCurve");
    }        

    m_peak_icv_HDR_Process_GetOutputPixelFormat = reinterpret_cast<dyn_peak_icv_HDR_Process_GetOutputPixelFormat>(load ? import_function(m_handle, "peak_icv_HDR_Process_GetOutputPixelFormat") : nullptr);
    if(m_peak_icv_HDR_Process_GetOutputPixelFormat == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_Process_GetOutputPixelFormat");
    }        

    m_peak_icv_HDR_Process = reinterpret_cast<dyn_peak_icv_HDR_Process>(load ? import_function(m_handle, "peak_icv_HDR_Process") : nullptr);
    if(m_peak_icv_HDR_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_Process");
    }        

    m_peak_icv_HDR_GetAlgorithm = reinterpret_cast<dyn_peak_icv_HDR_GetAlgorithm>(load ? import_function(m_handle, "peak_icv_HDR_GetAlgorithm") : nullptr);
    if(m_peak_icv_HDR_GetAlgorithm == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_GetAlgorithm");
    }        

    m_peak_icv_HDR_Destroy = reinterpret_cast<dyn_peak_icv_HDR_Destroy>(load ? import_function(m_handle, "peak_icv_HDR_Destroy") : nullptr);
    if(m_peak_icv_HDR_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_Destroy");
    }        

    m_peak_icv_HDR_GetResponseCurve = reinterpret_cast<dyn_peak_icv_HDR_GetResponseCurve>(load ? import_function(m_handle, "peak_icv_HDR_GetResponseCurve") : nullptr);
    if(m_peak_icv_HDR_GetResponseCurve == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_GetResponseCurve");
    }        

    m_peak_icv_HDR_SetResponseCurve = reinterpret_cast<dyn_peak_icv_HDR_SetResponseCurve>(load ? import_function(m_handle, "peak_icv_HDR_SetResponseCurve") : nullptr);
    if(m_peak_icv_HDR_SetResponseCurve == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_SetResponseCurve");
    }        

    m_peak_icv_HDR_ResponseCurve_Create = reinterpret_cast<dyn_peak_icv_HDR_ResponseCurve_Create>(load ? import_function(m_handle, "peak_icv_HDR_ResponseCurve_Create") : nullptr);
    if(m_peak_icv_HDR_ResponseCurve_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_ResponseCurve_Create");
    }        

    m_peak_icv_HDR_ResponseCurve_CreateFromFile = reinterpret_cast<dyn_peak_icv_HDR_ResponseCurve_CreateFromFile>(load ? import_function(m_handle, "peak_icv_HDR_ResponseCurve_CreateFromFile") : nullptr);
    if(m_peak_icv_HDR_ResponseCurve_CreateFromFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_ResponseCurve_CreateFromFile");
    }        

    m_peak_icv_HDR_ResponseCurve_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_HDR_ResponseCurve_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_HDR_ResponseCurve_IncreaseUseCount") : nullptr);
    if(m_peak_icv_HDR_ResponseCurve_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_ResponseCurve_IncreaseUseCount");
    }        

    m_peak_icv_HDR_ResponseCurve_Destroy = reinterpret_cast<dyn_peak_icv_HDR_ResponseCurve_Destroy>(load ? import_function(m_handle, "peak_icv_HDR_ResponseCurve_Destroy") : nullptr);
    if(m_peak_icv_HDR_ResponseCurve_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_ResponseCurve_Destroy");
    }        

    m_peak_icv_HDR_ResponseCurve_SaveToFile = reinterpret_cast<dyn_peak_icv_HDR_ResponseCurve_SaveToFile>(load ? import_function(m_handle, "peak_icv_HDR_ResponseCurve_SaveToFile") : nullptr);
    if(m_peak_icv_HDR_ResponseCurve_SaveToFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_ResponseCurve_SaveToFile");
    }        

    m_peak_icv_HDR_ResponseCurve_Compare = reinterpret_cast<dyn_peak_icv_HDR_ResponseCurve_Compare>(load ? import_function(m_handle, "peak_icv_HDR_ResponseCurve_Compare") : nullptr);
    if(m_peak_icv_HDR_ResponseCurve_Compare == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_HDR_ResponseCurve_Compare");
    }        

    m_peak_icv_ToneMapping_Drago_Create = reinterpret_cast<dyn_peak_icv_ToneMapping_Drago_Create>(load ? import_function(m_handle, "peak_icv_ToneMapping_Drago_Create") : nullptr);
    if(m_peak_icv_ToneMapping_Drago_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Drago_Create");
    }        

    m_peak_icv_ToneMapping_Drago_Destroy = reinterpret_cast<dyn_peak_icv_ToneMapping_Drago_Destroy>(load ? import_function(m_handle, "peak_icv_ToneMapping_Drago_Destroy") : nullptr);
    if(m_peak_icv_ToneMapping_Drago_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Drago_Destroy");
    }        

    m_peak_icv_ToneMapping_Drago_GetOutputPixelFormat = reinterpret_cast<dyn_peak_icv_ToneMapping_Drago_GetOutputPixelFormat>(load ? import_function(m_handle, "peak_icv_ToneMapping_Drago_GetOutputPixelFormat") : nullptr);
    if(m_peak_icv_ToneMapping_Drago_GetOutputPixelFormat == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Drago_GetOutputPixelFormat");
    }        

    m_peak_icv_ToneMapping_Drago_Process = reinterpret_cast<dyn_peak_icv_ToneMapping_Drago_Process>(load ? import_function(m_handle, "peak_icv_ToneMapping_Drago_Process") : nullptr);
    if(m_peak_icv_ToneMapping_Drago_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Drago_Process");
    }        

    m_peak_icv_ToneMapping_Linear_Create = reinterpret_cast<dyn_peak_icv_ToneMapping_Linear_Create>(load ? import_function(m_handle, "peak_icv_ToneMapping_Linear_Create") : nullptr);
    if(m_peak_icv_ToneMapping_Linear_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Linear_Create");
    }        

    m_peak_icv_ToneMapping_Linear_Destroy = reinterpret_cast<dyn_peak_icv_ToneMapping_Linear_Destroy>(load ? import_function(m_handle, "peak_icv_ToneMapping_Linear_Destroy") : nullptr);
    if(m_peak_icv_ToneMapping_Linear_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Linear_Destroy");
    }        

    m_peak_icv_ToneMapping_Linear_GetOutputPixelFormat = reinterpret_cast<dyn_peak_icv_ToneMapping_Linear_GetOutputPixelFormat>(load ? import_function(m_handle, "peak_icv_ToneMapping_Linear_GetOutputPixelFormat") : nullptr);
    if(m_peak_icv_ToneMapping_Linear_GetOutputPixelFormat == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Linear_GetOutputPixelFormat");
    }        

    m_peak_icv_ToneMapping_Linear_Process = reinterpret_cast<dyn_peak_icv_ToneMapping_Linear_Process>(load ? import_function(m_handle, "peak_icv_ToneMapping_Linear_Process") : nullptr);
    if(m_peak_icv_ToneMapping_Linear_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Linear_Process");
    }        

    m_peak_icv_ToneMapping_Linear_GetExposureValueRange = reinterpret_cast<dyn_peak_icv_ToneMapping_Linear_GetExposureValueRange>(load ? import_function(m_handle, "peak_icv_ToneMapping_Linear_GetExposureValueRange") : nullptr);
    if(m_peak_icv_ToneMapping_Linear_GetExposureValueRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ToneMapping_Linear_GetExposureValueRange");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_Create = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Create>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_Create") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_Create");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_Destroy = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Destroy>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_Destroy") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_Destroy");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled");
    }        

    m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled = reinterpret_cast<dyn_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled>(load ? import_function(m_handle, "peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled") : nullptr);
    if(m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled");
    }        

    m_peak_icv_Preprocessing_Downsampling_Create = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_Create>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_Create") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_Create");
    }        

    m_peak_icv_Preprocessing_Downsampling_Destroy = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_Destroy>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_Destroy") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_Destroy");
    }        

    m_peak_icv_Preprocessing_Downsampling_SetFactor = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_SetFactor>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_SetFactor") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_SetFactor == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_SetFactor");
    }        

    m_peak_icv_Preprocessing_Downsampling_GetFactor = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_GetFactor>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_GetFactor") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_GetFactor == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_GetFactor");
    }        

    m_peak_icv_Preprocessing_Downsampling_GetRange = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_GetRange>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_GetRange") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_GetRange");
    }        

    m_peak_icv_Preprocessing_Downsampling_SetMode = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_SetMode>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_SetMode") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_SetMode == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_SetMode");
    }        

    m_peak_icv_Preprocessing_Downsampling_GetMode = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_GetMode>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_GetMode") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_GetMode == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_GetMode");
    }        

    m_peak_icv_Preprocessing_Downsampling_GetOutputImageSize = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_GetOutputImageSize>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_GetOutputImageSize") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_GetOutputImageSize == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_GetOutputImageSize");
    }        

    m_peak_icv_Preprocessing_Downsampling_NeedsProcessing = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_NeedsProcessing>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_NeedsProcessing") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_NeedsProcessing == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_NeedsProcessing");
    }        

    m_peak_icv_Preprocessing_Downsampling_Process = reinterpret_cast<dyn_peak_icv_Preprocessing_Downsampling_Process>(load ? import_function(m_handle, "peak_icv_Preprocessing_Downsampling_Process") : nullptr);
    if(m_peak_icv_Preprocessing_Downsampling_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Downsampling_Process");
    }        

    m_peak_icv_Preprocessing_Gain_Create = reinterpret_cast<dyn_peak_icv_Preprocessing_Gain_Create>(load ? import_function(m_handle, "peak_icv_Preprocessing_Gain_Create") : nullptr);
    if(m_peak_icv_Preprocessing_Gain_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Gain_Create");
    }        

    m_peak_icv_Preprocessing_Gain_Destroy = reinterpret_cast<dyn_peak_icv_Preprocessing_Gain_Destroy>(load ? import_function(m_handle, "peak_icv_Preprocessing_Gain_Destroy") : nullptr);
    if(m_peak_icv_Preprocessing_Gain_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Gain_Destroy");
    }        

    m_peak_icv_Preprocessing_Gain_ProcessInplace = reinterpret_cast<dyn_peak_icv_Preprocessing_Gain_ProcessInplace>(load ? import_function(m_handle, "peak_icv_Preprocessing_Gain_ProcessInplace") : nullptr);
    if(m_peak_icv_Preprocessing_Gain_ProcessInplace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Gain_ProcessInplace");
    }        

    m_peak_icv_Preprocessing_Gain_NeedsProcessing = reinterpret_cast<dyn_peak_icv_Preprocessing_Gain_NeedsProcessing>(load ? import_function(m_handle, "peak_icv_Preprocessing_Gain_NeedsProcessing") : nullptr);
    if(m_peak_icv_Preprocessing_Gain_NeedsProcessing == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Gain_NeedsProcessing");
    }        

    m_peak_icv_Preprocessing_Gain_SetValue = reinterpret_cast<dyn_peak_icv_Preprocessing_Gain_SetValue>(load ? import_function(m_handle, "peak_icv_Preprocessing_Gain_SetValue") : nullptr);
    if(m_peak_icv_Preprocessing_Gain_SetValue == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Gain_SetValue");
    }        

    m_peak_icv_Preprocessing_Gain_GetValue = reinterpret_cast<dyn_peak_icv_Preprocessing_Gain_GetValue>(load ? import_function(m_handle, "peak_icv_Preprocessing_Gain_GetValue") : nullptr);
    if(m_peak_icv_Preprocessing_Gain_GetValue == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Gain_GetValue");
    }        

    m_peak_icv_Preprocessing_Gain_GetRange = reinterpret_cast<dyn_peak_icv_Preprocessing_Gain_GetRange>(load ? import_function(m_handle, "peak_icv_Preprocessing_Gain_GetRange") : nullptr);
    if(m_peak_icv_Preprocessing_Gain_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Gain_GetRange");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_Create = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_Create>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_Create") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_Create");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_Destroy = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_Destroy>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_Destroy") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_Destroy");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_Detect = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_Detect>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_Detect") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_Detect == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_Detect");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_SetList = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_SetList>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_SetList") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_SetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_SetList");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_ResetList = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_ResetList>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_ResetList") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_ResetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_ResetList");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_GetList = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_GetList>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_GetList") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_GetList == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_GetList");
    }        

    m_peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange = reinterpret_cast<dyn_peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange>(load ? import_function(m_handle, "peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange") : nullptr);
    if(m_peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange");
    }        

    m_peak_icv_Preprocessing_ImageConverter_Create = reinterpret_cast<dyn_peak_icv_Preprocessing_ImageConverter_Create>(load ? import_function(m_handle, "peak_icv_Preprocessing_ImageConverter_Create") : nullptr);
    if(m_peak_icv_Preprocessing_ImageConverter_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ImageConverter_Create");
    }        

    m_peak_icv_Preprocessing_ImageConverter_Destroy = reinterpret_cast<dyn_peak_icv_Preprocessing_ImageConverter_Destroy>(load ? import_function(m_handle, "peak_icv_Preprocessing_ImageConverter_Destroy") : nullptr);
    if(m_peak_icv_Preprocessing_ImageConverter_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ImageConverter_Destroy");
    }        

    m_peak_icv_Preprocessing_ImageConverter_Convert = reinterpret_cast<dyn_peak_icv_Preprocessing_ImageConverter_Convert>(load ? import_function(m_handle, "peak_icv_Preprocessing_ImageConverter_Convert") : nullptr);
    if(m_peak_icv_Preprocessing_ImageConverter_Convert == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ImageConverter_Convert");
    }        

    m_peak_icv_Preprocessing_ImageConverter_ReleaseBuffers = reinterpret_cast<dyn_peak_icv_Preprocessing_ImageConverter_ReleaseBuffers>(load ? import_function(m_handle, "peak_icv_Preprocessing_ImageConverter_ReleaseBuffers") : nullptr);
    if(m_peak_icv_Preprocessing_ImageConverter_ReleaseBuffers == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ImageConverter_ReleaseBuffers");
    }        

    m_peak_icv_Preprocessing_Transformation_GetOutputPixelFormat = reinterpret_cast<dyn_peak_icv_Preprocessing_Transformation_GetOutputPixelFormat>(load ? import_function(m_handle, "peak_icv_Preprocessing_Transformation_GetOutputPixelFormat") : nullptr);
    if(m_peak_icv_Preprocessing_Transformation_GetOutputPixelFormat == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Transformation_GetOutputPixelFormat");
    }        

    m_peak_icv_Preprocessing_Transformation_Process = reinterpret_cast<dyn_peak_icv_Preprocessing_Transformation_Process>(load ? import_function(m_handle, "peak_icv_Preprocessing_Transformation_Process") : nullptr);
    if(m_peak_icv_Preprocessing_Transformation_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_Transformation_Process");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_Create = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_Create>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_Create") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_Create");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_Destroy = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_Destroy>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_Destroy") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_Destroy");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_GetGamma = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetGamma>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_GetGamma") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_GetGamma == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_GetGamma");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_SetGamma = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_SetGamma>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_SetGamma") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_SetGamma == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_SetGamma");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing");
    }        

    m_peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace = reinterpret_cast<dyn_peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace>(load ? import_function(m_handle, "peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace") : nullptr);
    if(m_peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace");
    }        

    m_peak_icv_Threshold_Process = reinterpret_cast<dyn_peak_icv_Threshold_Process>(load ? import_function(m_handle, "peak_icv_Threshold_Process") : nullptr);
    if(m_peak_icv_Threshold_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Threshold_Process");
    }        

    m_peak_icv_Threshold_GetRange = reinterpret_cast<dyn_peak_icv_Threshold_GetRange>(load ? import_function(m_handle, "peak_icv_Threshold_GetRange") : nullptr);
    if(m_peak_icv_Threshold_GetRange == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Threshold_GetRange");
    }        

    m_peak_icv_Transform_Undistortion_Process = reinterpret_cast<dyn_peak_icv_Transform_Undistortion_Process>(load ? import_function(m_handle, "peak_icv_Transform_Undistortion_Process") : nullptr);
    if(m_peak_icv_Transform_Undistortion_Process == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_Undistortion_Process");
    }        

    m_peak_icv_Transform_Undistortion_Create = reinterpret_cast<dyn_peak_icv_Transform_Undistortion_Create>(load ? import_function(m_handle, "peak_icv_Transform_Undistortion_Create") : nullptr);
    if(m_peak_icv_Transform_Undistortion_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_Undistortion_Create");
    }        

    m_peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation = reinterpret_cast<dyn_peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation>(load ? import_function(m_handle, "peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation") : nullptr);
    if(m_peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation");
    }        

    m_peak_icv_Transform_Undistortion_CreateWithImageMetadata = reinterpret_cast<dyn_peak_icv_Transform_Undistortion_CreateWithImageMetadata>(load ? import_function(m_handle, "peak_icv_Transform_Undistortion_CreateWithImageMetadata") : nullptr);
    if(m_peak_icv_Transform_Undistortion_CreateWithImageMetadata == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_Undistortion_CreateWithImageMetadata");
    }        

    m_peak_icv_Transform_Undistortion_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_Transform_Undistortion_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_Transform_Undistortion_IncreaseUseCount") : nullptr);
    if(m_peak_icv_Transform_Undistortion_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_Undistortion_IncreaseUseCount");
    }        

    m_peak_icv_Transform_Undistortion_Destroy = reinterpret_cast<dyn_peak_icv_Transform_Undistortion_Destroy>(load ? import_function(m_handle, "peak_icv_Transform_Undistortion_Destroy") : nullptr);
    if(m_peak_icv_Transform_Undistortion_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_Undistortion_Destroy");
    }        

    m_peak_icv_Transform_Undistortion_SetInterpolation = reinterpret_cast<dyn_peak_icv_Transform_Undistortion_SetInterpolation>(load ? import_function(m_handle, "peak_icv_Transform_Undistortion_SetInterpolation") : nullptr);
    if(m_peak_icv_Transform_Undistortion_SetInterpolation == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_Undistortion_SetInterpolation");
    }        

    m_peak_icv_Transform_Undistortion_GetInterpolation = reinterpret_cast<dyn_peak_icv_Transform_Undistortion_GetInterpolation>(load ? import_function(m_handle, "peak_icv_Transform_Undistortion_GetInterpolation") : nullptr);
    if(m_peak_icv_Transform_Undistortion_GetInterpolation == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_Undistortion_GetInterpolation");
    }        

    m_peak_icv_Transform_DepthMap_To_XYZImage = reinterpret_cast<dyn_peak_icv_Transform_DepthMap_To_XYZImage>(load ? import_function(m_handle, "peak_icv_Transform_DepthMap_To_XYZImage") : nullptr);
    if(m_peak_icv_Transform_DepthMap_To_XYZImage == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Transform_DepthMap_To_XYZImage");
    }        

    m_peak_icv_ValidateBinary = reinterpret_cast<dyn_peak_icv_ValidateBinary>(load ? import_function(m_handle, "peak_icv_ValidateBinary") : nullptr);
    if(m_peak_icv_ValidateBinary == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_ValidateBinary");
    }        

    m_peak_icv_Init = reinterpret_cast<dyn_peak_icv_Init>(load ? import_function(m_handle, "peak_icv_Init") : nullptr);
    if(m_peak_icv_Init == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Init");
    }        

    m_peak_icv_Exit = reinterpret_cast<dyn_peak_icv_Exit>(load ? import_function(m_handle, "peak_icv_Exit") : nullptr);
    if(m_peak_icv_Exit == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Exit");
    }        

    m_peak_icv_GetVersion = reinterpret_cast<dyn_peak_icv_GetVersion>(load ? import_function(m_handle, "peak_icv_GetVersion") : nullptr);
    if(m_peak_icv_GetVersion == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_GetVersion");
    }        

    m_peak_icv_GetLastErrorMessage_GetCount = reinterpret_cast<dyn_peak_icv_GetLastErrorMessage_GetCount>(load ? import_function(m_handle, "peak_icv_GetLastErrorMessage_GetCount") : nullptr);
    if(m_peak_icv_GetLastErrorMessage_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_GetLastErrorMessage_GetCount");
    }        

    m_peak_icv_GetLastErrorMessage = reinterpret_cast<dyn_peak_icv_GetLastErrorMessage>(load ? import_function(m_handle, "peak_icv_GetLastErrorMessage") : nullptr);
    if(m_peak_icv_GetLastErrorMessage == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_GetLastErrorMessage");
    }        

    m_peak_icv_Region_Draw = reinterpret_cast<dyn_peak_icv_Region_Draw>(load ? import_function(m_handle, "peak_icv_Region_Draw") : nullptr);
    if(m_peak_icv_Region_Draw == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Draw");
    }        

    m_peak_icv_Region_SelectByArea_GetCount = reinterpret_cast<dyn_peak_icv_Region_SelectByArea_GetCount>(load ? import_function(m_handle, "peak_icv_Region_SelectByArea_GetCount") : nullptr);
    if(m_peak_icv_Region_SelectByArea_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_SelectByArea_GetCount");
    }        

    m_peak_icv_Region_SelectByArea = reinterpret_cast<dyn_peak_icv_Region_SelectByArea>(load ? import_function(m_handle, "peak_icv_Region_SelectByArea") : nullptr);
    if(m_peak_icv_Region_SelectByArea == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_SelectByArea");
    }        

    m_peak_icv_Region_SelectByCenterOfGravityX_GetCount = reinterpret_cast<dyn_peak_icv_Region_SelectByCenterOfGravityX_GetCount>(load ? import_function(m_handle, "peak_icv_Region_SelectByCenterOfGravityX_GetCount") : nullptr);
    if(m_peak_icv_Region_SelectByCenterOfGravityX_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_SelectByCenterOfGravityX_GetCount");
    }        

    m_peak_icv_Region_SelectByCenterOfGravityX = reinterpret_cast<dyn_peak_icv_Region_SelectByCenterOfGravityX>(load ? import_function(m_handle, "peak_icv_Region_SelectByCenterOfGravityX") : nullptr);
    if(m_peak_icv_Region_SelectByCenterOfGravityX == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_SelectByCenterOfGravityX");
    }        

    m_peak_icv_Region_SelectByCenterOfGravityY_GetCount = reinterpret_cast<dyn_peak_icv_Region_SelectByCenterOfGravityY_GetCount>(load ? import_function(m_handle, "peak_icv_Region_SelectByCenterOfGravityY_GetCount") : nullptr);
    if(m_peak_icv_Region_SelectByCenterOfGravityY_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_SelectByCenterOfGravityY_GetCount");
    }        

    m_peak_icv_Region_SelectByCenterOfGravityY = reinterpret_cast<dyn_peak_icv_Region_SelectByCenterOfGravityY>(load ? import_function(m_handle, "peak_icv_Region_SelectByCenterOfGravityY") : nullptr);
    if(m_peak_icv_Region_SelectByCenterOfGravityY == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_SelectByCenterOfGravityY");
    }        

    m_peak_icv_Region_SelectByCenterOfGravityRect_GetCount = reinterpret_cast<dyn_peak_icv_Region_SelectByCenterOfGravityRect_GetCount>(load ? import_function(m_handle, "peak_icv_Region_SelectByCenterOfGravityRect_GetCount") : nullptr);
    if(m_peak_icv_Region_SelectByCenterOfGravityRect_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_SelectByCenterOfGravityRect_GetCount");
    }        

    m_peak_icv_Region_SelectByCenterOfGravityRect = reinterpret_cast<dyn_peak_icv_Region_SelectByCenterOfGravityRect>(load ? import_function(m_handle, "peak_icv_Region_SelectByCenterOfGravityRect") : nullptr);
    if(m_peak_icv_Region_SelectByCenterOfGravityRect == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_SelectByCenterOfGravityRect");
    }        

    m_peak_icv_Archive_Create = reinterpret_cast<dyn_peak_icv_Archive_Create>(load ? import_function(m_handle, "peak_icv_Archive_Create") : nullptr);
    if(m_peak_icv_Archive_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_Create");
    }        

    m_peak_icv_Archive_CreateFromString = reinterpret_cast<dyn_peak_icv_Archive_CreateFromString>(load ? import_function(m_handle, "peak_icv_Archive_CreateFromString") : nullptr);
    if(m_peak_icv_Archive_CreateFromString == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_CreateFromString");
    }        

    m_peak_icv_Archive_Destroy = reinterpret_cast<dyn_peak_icv_Archive_Destroy>(load ? import_function(m_handle, "peak_icv_Archive_Destroy") : nullptr);
    if(m_peak_icv_Archive_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_Destroy");
    }        

    m_peak_icv_Archive_HasKey = reinterpret_cast<dyn_peak_icv_Archive_HasKey>(load ? import_function(m_handle, "peak_icv_Archive_HasKey") : nullptr);
    if(m_peak_icv_Archive_HasKey == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_HasKey");
    }        

    m_peak_icv_Archive_GetKeys_GetCount = reinterpret_cast<dyn_peak_icv_Archive_GetKeys_GetCount>(load ? import_function(m_handle, "peak_icv_Archive_GetKeys_GetCount") : nullptr);
    if(m_peak_icv_Archive_GetKeys_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetKeys_GetCount");
    }        

    m_peak_icv_Archive_GetKeysElement_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_Archive_GetKeysElement_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_Archive_GetKeysElement_GetSizeInBytes") : nullptr);
    if(m_peak_icv_Archive_GetKeysElement_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetKeysElement_GetSizeInBytes");
    }        

    m_peak_icv_Archive_GetKeysElement = reinterpret_cast<dyn_peak_icv_Archive_GetKeysElement>(load ? import_function(m_handle, "peak_icv_Archive_GetKeysElement") : nullptr);
    if(m_peak_icv_Archive_GetKeysElement == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetKeysElement");
    }        

    m_peak_icv_Archive_GetValueType = reinterpret_cast<dyn_peak_icv_Archive_GetValueType>(load ? import_function(m_handle, "peak_icv_Archive_GetValueType") : nullptr);
    if(m_peak_icv_Archive_GetValueType == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetValueType");
    }        

    m_peak_icv_Archive_GetArray_GetCount = reinterpret_cast<dyn_peak_icv_Archive_GetArray_GetCount>(load ? import_function(m_handle, "peak_icv_Archive_GetArray_GetCount") : nullptr);
    if(m_peak_icv_Archive_GetArray_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetArray_GetCount");
    }        

    m_peak_icv_Archive_GetInt = reinterpret_cast<dyn_peak_icv_Archive_GetInt>(load ? import_function(m_handle, "peak_icv_Archive_GetInt") : nullptr);
    if(m_peak_icv_Archive_GetInt == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetInt");
    }        

    m_peak_icv_Archive_SetInt = reinterpret_cast<dyn_peak_icv_Archive_SetInt>(load ? import_function(m_handle, "peak_icv_Archive_SetInt") : nullptr);
    if(m_peak_icv_Archive_SetInt == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetInt");
    }        

    m_peak_icv_Archive_GetIntArray = reinterpret_cast<dyn_peak_icv_Archive_GetIntArray>(load ? import_function(m_handle, "peak_icv_Archive_GetIntArray") : nullptr);
    if(m_peak_icv_Archive_GetIntArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetIntArray");
    }        

    m_peak_icv_Archive_SetIntArray = reinterpret_cast<dyn_peak_icv_Archive_SetIntArray>(load ? import_function(m_handle, "peak_icv_Archive_SetIntArray") : nullptr);
    if(m_peak_icv_Archive_SetIntArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetIntArray");
    }        

    m_peak_icv_Archive_GetDouble = reinterpret_cast<dyn_peak_icv_Archive_GetDouble>(load ? import_function(m_handle, "peak_icv_Archive_GetDouble") : nullptr);
    if(m_peak_icv_Archive_GetDouble == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetDouble");
    }        

    m_peak_icv_Archive_SetDouble = reinterpret_cast<dyn_peak_icv_Archive_SetDouble>(load ? import_function(m_handle, "peak_icv_Archive_SetDouble") : nullptr);
    if(m_peak_icv_Archive_SetDouble == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetDouble");
    }        

    m_peak_icv_Archive_GetDoubleArray = reinterpret_cast<dyn_peak_icv_Archive_GetDoubleArray>(load ? import_function(m_handle, "peak_icv_Archive_GetDoubleArray") : nullptr);
    if(m_peak_icv_Archive_GetDoubleArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetDoubleArray");
    }        

    m_peak_icv_Archive_SetDoubleArray = reinterpret_cast<dyn_peak_icv_Archive_SetDoubleArray>(load ? import_function(m_handle, "peak_icv_Archive_SetDoubleArray") : nullptr);
    if(m_peak_icv_Archive_SetDoubleArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetDoubleArray");
    }        

    m_peak_icv_Archive_GetBool = reinterpret_cast<dyn_peak_icv_Archive_GetBool>(load ? import_function(m_handle, "peak_icv_Archive_GetBool") : nullptr);
    if(m_peak_icv_Archive_GetBool == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetBool");
    }        

    m_peak_icv_Archive_SetBool = reinterpret_cast<dyn_peak_icv_Archive_SetBool>(load ? import_function(m_handle, "peak_icv_Archive_SetBool") : nullptr);
    if(m_peak_icv_Archive_SetBool == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetBool");
    }        

    m_peak_icv_Archive_GetBoolArray = reinterpret_cast<dyn_peak_icv_Archive_GetBoolArray>(load ? import_function(m_handle, "peak_icv_Archive_GetBoolArray") : nullptr);
    if(m_peak_icv_Archive_GetBoolArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetBoolArray");
    }        

    m_peak_icv_Archive_SetBoolArray = reinterpret_cast<dyn_peak_icv_Archive_SetBoolArray>(load ? import_function(m_handle, "peak_icv_Archive_SetBoolArray") : nullptr);
    if(m_peak_icv_Archive_SetBoolArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetBoolArray");
    }        

    m_peak_icv_Archive_GetString_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_Archive_GetString_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_Archive_GetString_GetSizeInBytes") : nullptr);
    if(m_peak_icv_Archive_GetString_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetString_GetSizeInBytes");
    }        

    m_peak_icv_Archive_GetString = reinterpret_cast<dyn_peak_icv_Archive_GetString>(load ? import_function(m_handle, "peak_icv_Archive_GetString") : nullptr);
    if(m_peak_icv_Archive_GetString == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetString");
    }        

    m_peak_icv_Archive_SetString = reinterpret_cast<dyn_peak_icv_Archive_SetString>(load ? import_function(m_handle, "peak_icv_Archive_SetString") : nullptr);
    if(m_peak_icv_Archive_SetString == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetString");
    }        

    m_peak_icv_Archive_GetStringArrayElement_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_Archive_GetStringArrayElement_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_Archive_GetStringArrayElement_GetSizeInBytes") : nullptr);
    if(m_peak_icv_Archive_GetStringArrayElement_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetStringArrayElement_GetSizeInBytes");
    }        

    m_peak_icv_Archive_GetStringArrayElement = reinterpret_cast<dyn_peak_icv_Archive_GetStringArrayElement>(load ? import_function(m_handle, "peak_icv_Archive_GetStringArrayElement") : nullptr);
    if(m_peak_icv_Archive_GetStringArrayElement == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetStringArrayElement");
    }        

    m_peak_icv_Archive_SetStringArray = reinterpret_cast<dyn_peak_icv_Archive_SetStringArray>(load ? import_function(m_handle, "peak_icv_Archive_SetStringArray") : nullptr);
    if(m_peak_icv_Archive_SetStringArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetStringArray");
    }        

    m_peak_icv_Archive_GetArchive = reinterpret_cast<dyn_peak_icv_Archive_GetArchive>(load ? import_function(m_handle, "peak_icv_Archive_GetArchive") : nullptr);
    if(m_peak_icv_Archive_GetArchive == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetArchive");
    }        

    m_peak_icv_Archive_SetArchive = reinterpret_cast<dyn_peak_icv_Archive_SetArchive>(load ? import_function(m_handle, "peak_icv_Archive_SetArchive") : nullptr);
    if(m_peak_icv_Archive_SetArchive == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetArchive");
    }        

    m_peak_icv_Archive_GetArchiveArray = reinterpret_cast<dyn_peak_icv_Archive_GetArchiveArray>(load ? import_function(m_handle, "peak_icv_Archive_GetArchiveArray") : nullptr);
    if(m_peak_icv_Archive_GetArchiveArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_GetArchiveArray");
    }        

    m_peak_icv_Archive_SetArchiveArray = reinterpret_cast<dyn_peak_icv_Archive_SetArchiveArray>(load ? import_function(m_handle, "peak_icv_Archive_SetArchiveArray") : nullptr);
    if(m_peak_icv_Archive_SetArchiveArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_SetArchiveArray");
    }        

    m_peak_icv_Archive_ToString_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_Archive_ToString_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_Archive_ToString_GetSizeInBytes") : nullptr);
    if(m_peak_icv_Archive_ToString_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_ToString_GetSizeInBytes");
    }        

    m_peak_icv_Archive_ToString = reinterpret_cast<dyn_peak_icv_Archive_ToString>(load ? import_function(m_handle, "peak_icv_Archive_ToString") : nullptr);
    if(m_peak_icv_Archive_ToString == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Archive_ToString");
    }        

    m_peak_icv_Buffer_CutBytes = reinterpret_cast<dyn_peak_icv_Buffer_CutBytes>(load ? import_function(m_handle, "peak_icv_Buffer_CutBytes") : nullptr);
    if(m_peak_icv_Buffer_CutBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Buffer_CutBytes");
    }        

    m_peak_icv_Image_Create = reinterpret_cast<dyn_peak_icv_Image_Create>(load ? import_function(m_handle, "peak_icv_Image_Create") : nullptr);
    if(m_peak_icv_Image_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Create");
    }        

    m_peak_icv_Image_CreateWithZeroInit = reinterpret_cast<dyn_peak_icv_Image_CreateWithZeroInit>(load ? import_function(m_handle, "peak_icv_Image_CreateWithZeroInit") : nullptr);
    if(m_peak_icv_Image_CreateWithZeroInit == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_CreateWithZeroInit");
    }        

    m_peak_icv_Image_CreateFromImageInfo = reinterpret_cast<dyn_peak_icv_Image_CreateFromImageInfo>(load ? import_function(m_handle, "peak_icv_Image_CreateFromImageInfo") : nullptr);
    if(m_peak_icv_Image_CreateFromImageInfo == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_CreateFromImageInfo");
    }        

    m_peak_icv_Image_CreateFromFile = reinterpret_cast<dyn_peak_icv_Image_CreateFromFile>(load ? import_function(m_handle, "peak_icv_Image_CreateFromFile") : nullptr);
    if(m_peak_icv_Image_CreateFromFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_CreateFromFile");
    }        

    m_peak_icv_Image_CreateFromFileWithPixelFormat = reinterpret_cast<dyn_peak_icv_Image_CreateFromFileWithPixelFormat>(load ? import_function(m_handle, "peak_icv_Image_CreateFromFileWithPixelFormat") : nullptr);
    if(m_peak_icv_Image_CreateFromFileWithPixelFormat == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_CreateFromFileWithPixelFormat");
    }        

    m_peak_icv_Image_CreateFromExistingImage = reinterpret_cast<dyn_peak_icv_Image_CreateFromExistingImage>(load ? import_function(m_handle, "peak_icv_Image_CreateFromExistingImage") : nullptr);
    if(m_peak_icv_Image_CreateFromExistingImage == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_CreateFromExistingImage");
    }        

    m_peak_icv_Image_SaveToFile = reinterpret_cast<dyn_peak_icv_Image_SaveToFile>(load ? import_function(m_handle, "peak_icv_Image_SaveToFile") : nullptr);
    if(m_peak_icv_Image_SaveToFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_SaveToFile");
    }        

    m_peak_icv_Image_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_Image_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_Image_IncreaseUseCount") : nullptr);
    if(m_peak_icv_Image_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_IncreaseUseCount");
    }        

    m_peak_icv_Image_Destroy = reinterpret_cast<dyn_peak_icv_Image_Destroy>(load ? import_function(m_handle, "peak_icv_Image_Destroy") : nullptr);
    if(m_peak_icv_Image_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Destroy");
    }        

    m_peak_icv_Image_ConvertPixelFormat = reinterpret_cast<dyn_peak_icv_Image_ConvertPixelFormat>(load ? import_function(m_handle, "peak_icv_Image_ConvertPixelFormat") : nullptr);
    if(m_peak_icv_Image_ConvertPixelFormat == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_ConvertPixelFormat");
    }        

    m_peak_icv_Image_ConvertPixelFormatWithFactor = reinterpret_cast<dyn_peak_icv_Image_ConvertPixelFormatWithFactor>(load ? import_function(m_handle, "peak_icv_Image_ConvertPixelFormatWithFactor") : nullptr);
    if(m_peak_icv_Image_ConvertPixelFormatWithFactor == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_ConvertPixelFormatWithFactor");
    }        

    m_peak_icv_Image_GetInfo = reinterpret_cast<dyn_peak_icv_Image_GetInfo>(load ? import_function(m_handle, "peak_icv_Image_GetInfo") : nullptr);
    if(m_peak_icv_Image_GetInfo == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_GetInfo");
    }        

    m_peak_icv_Image_GetRegion = reinterpret_cast<dyn_peak_icv_Image_GetRegion>(load ? import_function(m_handle, "peak_icv_Image_GetRegion") : nullptr);
    if(m_peak_icv_Image_GetRegion == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_GetRegion");
    }        

    m_peak_icv_Image_SetRegion = reinterpret_cast<dyn_peak_icv_Image_SetRegion>(load ? import_function(m_handle, "peak_icv_Image_SetRegion") : nullptr);
    if(m_peak_icv_Image_SetRegion == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_SetRegion");
    }        

    m_peak_icv_Image_ResetRegion = reinterpret_cast<dyn_peak_icv_Image_ResetRegion>(load ? import_function(m_handle, "peak_icv_Image_ResetRegion") : nullptr);
    if(m_peak_icv_Image_ResetRegion == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_ResetRegion");
    }        

    m_peak_icv_Image_Compare = reinterpret_cast<dyn_peak_icv_Image_Compare>(load ? import_function(m_handle, "peak_icv_Image_Compare") : nullptr);
    if(m_peak_icv_Image_Compare == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Compare");
    }        

    m_peak_icv_Image_GetCaptureInformation = reinterpret_cast<dyn_peak_icv_Image_GetCaptureInformation>(load ? import_function(m_handle, "peak_icv_Image_GetCaptureInformation") : nullptr);
    if(m_peak_icv_Image_GetCaptureInformation == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_GetCaptureInformation");
    }        

    m_peak_icv_Image_SetCaptureInformation = reinterpret_cast<dyn_peak_icv_Image_SetCaptureInformation>(load ? import_function(m_handle, "peak_icv_Image_SetCaptureInformation") : nullptr);
    if(m_peak_icv_Image_SetCaptureInformation == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_SetCaptureInformation");
    }        

    m_peak_icv_Image_Subtract = reinterpret_cast<dyn_peak_icv_Image_Subtract>(load ? import_function(m_handle, "peak_icv_Image_Subtract") : nullptr);
    if(m_peak_icv_Image_Subtract == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Subtract");
    }        

    m_peak_icv_Image_TransformToWorkspace = reinterpret_cast<dyn_peak_icv_Image_TransformToWorkspace>(load ? import_function(m_handle, "peak_icv_Image_TransformToWorkspace") : nullptr);
    if(m_peak_icv_Image_TransformToWorkspace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_TransformToWorkspace");
    }        

    m_peak_icv_Image_Crop = reinterpret_cast<dyn_peak_icv_Image_Crop>(load ? import_function(m_handle, "peak_icv_Image_Crop") : nullptr);
    if(m_peak_icv_Image_Crop == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Crop");
    }        

    m_peak_icv_Image_Scale = reinterpret_cast<dyn_peak_icv_Image_Scale>(load ? import_function(m_handle, "peak_icv_Image_Scale") : nullptr);
    if(m_peak_icv_Image_Scale == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Scale");
    }        

    m_peak_icv_Image_Deinterleave = reinterpret_cast<dyn_peak_icv_Image_Deinterleave>(load ? import_function(m_handle, "peak_icv_Image_Deinterleave") : nullptr);
    if(m_peak_icv_Image_Deinterleave == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Deinterleave");
    }        

    m_peak_icv_Image_Deinterleave_GetOutputPixelFormat = reinterpret_cast<dyn_peak_icv_Image_Deinterleave_GetOutputPixelFormat>(load ? import_function(m_handle, "peak_icv_Image_Deinterleave_GetOutputPixelFormat") : nullptr);
    if(m_peak_icv_Image_Deinterleave_GetOutputPixelFormat == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Deinterleave_GetOutputPixelFormat");
    }        

    m_peak_icv_Image_Deinterleave_GetOutputImageCount = reinterpret_cast<dyn_peak_icv_Image_Deinterleave_GetOutputImageCount>(load ? import_function(m_handle, "peak_icv_Image_Deinterleave_GetOutputImageCount") : nullptr);
    if(m_peak_icv_Image_Deinterleave_GetOutputImageCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Deinterleave_GetOutputImageCount");
    }        

    m_peak_icv_Image_Deinterleave_GetOutputImageSize = reinterpret_cast<dyn_peak_icv_Image_Deinterleave_GetOutputImageSize>(load ? import_function(m_handle, "peak_icv_Image_Deinterleave_GetOutputImageSize") : nullptr);
    if(m_peak_icv_Image_Deinterleave_GetOutputImageSize == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_Deinterleave_GetOutputImageSize");
    }        

    m_peak_icv_Image_GetMetadata = reinterpret_cast<dyn_peak_icv_Image_GetMetadata>(load ? import_function(m_handle, "peak_icv_Image_GetMetadata") : nullptr);
    if(m_peak_icv_Image_GetMetadata == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_GetMetadata");
    }        

    m_peak_icv_Image_SetMetadata = reinterpret_cast<dyn_peak_icv_Image_SetMetadata>(load ? import_function(m_handle, "peak_icv_Image_SetMetadata") : nullptr);
    if(m_peak_icv_Image_SetMetadata == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Image_SetMetadata");
    }        

    m_peak_icv_Metadata_Create = reinterpret_cast<dyn_peak_icv_Metadata_Create>(load ? import_function(m_handle, "peak_icv_Metadata_Create") : nullptr);
    if(m_peak_icv_Metadata_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_Create");
    }        

    m_peak_icv_Metadata_Destroy = reinterpret_cast<dyn_peak_icv_Metadata_Destroy>(load ? import_function(m_handle, "peak_icv_Metadata_Destroy") : nullptr);
    if(m_peak_icv_Metadata_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_Destroy");
    }        

    m_peak_icv_Metadata_GetInt = reinterpret_cast<dyn_peak_icv_Metadata_GetInt>(load ? import_function(m_handle, "peak_icv_Metadata_GetInt") : nullptr);
    if(m_peak_icv_Metadata_GetInt == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetInt");
    }        

    m_peak_icv_Metadata_SetInt = reinterpret_cast<dyn_peak_icv_Metadata_SetInt>(load ? import_function(m_handle, "peak_icv_Metadata_SetInt") : nullptr);
    if(m_peak_icv_Metadata_SetInt == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetInt");
    }        

    m_peak_icv_Metadata_GetIntArray = reinterpret_cast<dyn_peak_icv_Metadata_GetIntArray>(load ? import_function(m_handle, "peak_icv_Metadata_GetIntArray") : nullptr);
    if(m_peak_icv_Metadata_GetIntArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetIntArray");
    }        

    m_peak_icv_Metadata_SetIntArray = reinterpret_cast<dyn_peak_icv_Metadata_SetIntArray>(load ? import_function(m_handle, "peak_icv_Metadata_SetIntArray") : nullptr);
    if(m_peak_icv_Metadata_SetIntArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetIntArray");
    }        

    m_peak_icv_Metadata_GetUInt = reinterpret_cast<dyn_peak_icv_Metadata_GetUInt>(load ? import_function(m_handle, "peak_icv_Metadata_GetUInt") : nullptr);
    if(m_peak_icv_Metadata_GetUInt == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetUInt");
    }        

    m_peak_icv_Metadata_SetUInt = reinterpret_cast<dyn_peak_icv_Metadata_SetUInt>(load ? import_function(m_handle, "peak_icv_Metadata_SetUInt") : nullptr);
    if(m_peak_icv_Metadata_SetUInt == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetUInt");
    }        

    m_peak_icv_Metadata_GetUIntArray = reinterpret_cast<dyn_peak_icv_Metadata_GetUIntArray>(load ? import_function(m_handle, "peak_icv_Metadata_GetUIntArray") : nullptr);
    if(m_peak_icv_Metadata_GetUIntArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetUIntArray");
    }        

    m_peak_icv_Metadata_SetUIntArray = reinterpret_cast<dyn_peak_icv_Metadata_SetUIntArray>(load ? import_function(m_handle, "peak_icv_Metadata_SetUIntArray") : nullptr);
    if(m_peak_icv_Metadata_SetUIntArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetUIntArray");
    }        

    m_peak_icv_Metadata_GetDouble = reinterpret_cast<dyn_peak_icv_Metadata_GetDouble>(load ? import_function(m_handle, "peak_icv_Metadata_GetDouble") : nullptr);
    if(m_peak_icv_Metadata_GetDouble == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetDouble");
    }        

    m_peak_icv_Metadata_SetDouble = reinterpret_cast<dyn_peak_icv_Metadata_SetDouble>(load ? import_function(m_handle, "peak_icv_Metadata_SetDouble") : nullptr);
    if(m_peak_icv_Metadata_SetDouble == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetDouble");
    }        

    m_peak_icv_Metadata_GetDoubleArray = reinterpret_cast<dyn_peak_icv_Metadata_GetDoubleArray>(load ? import_function(m_handle, "peak_icv_Metadata_GetDoubleArray") : nullptr);
    if(m_peak_icv_Metadata_GetDoubleArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetDoubleArray");
    }        

    m_peak_icv_Metadata_SetDoubleArray = reinterpret_cast<dyn_peak_icv_Metadata_SetDoubleArray>(load ? import_function(m_handle, "peak_icv_Metadata_SetDoubleArray") : nullptr);
    if(m_peak_icv_Metadata_SetDoubleArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetDoubleArray");
    }        

    m_peak_icv_Metadata_GetBool = reinterpret_cast<dyn_peak_icv_Metadata_GetBool>(load ? import_function(m_handle, "peak_icv_Metadata_GetBool") : nullptr);
    if(m_peak_icv_Metadata_GetBool == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetBool");
    }        

    m_peak_icv_Metadata_SetBool = reinterpret_cast<dyn_peak_icv_Metadata_SetBool>(load ? import_function(m_handle, "peak_icv_Metadata_SetBool") : nullptr);
    if(m_peak_icv_Metadata_SetBool == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetBool");
    }        

    m_peak_icv_Metadata_GetBoolArray = reinterpret_cast<dyn_peak_icv_Metadata_GetBoolArray>(load ? import_function(m_handle, "peak_icv_Metadata_GetBoolArray") : nullptr);
    if(m_peak_icv_Metadata_GetBoolArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetBoolArray");
    }        

    m_peak_icv_Metadata_SetBoolArray = reinterpret_cast<dyn_peak_icv_Metadata_SetBoolArray>(load ? import_function(m_handle, "peak_icv_Metadata_SetBoolArray") : nullptr);
    if(m_peak_icv_Metadata_SetBoolArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetBoolArray");
    }        

    m_peak_icv_Metadata_GetString_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_Metadata_GetString_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_Metadata_GetString_GetSizeInBytes") : nullptr);
    if(m_peak_icv_Metadata_GetString_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetString_GetSizeInBytes");
    }        

    m_peak_icv_Metadata_GetString = reinterpret_cast<dyn_peak_icv_Metadata_GetString>(load ? import_function(m_handle, "peak_icv_Metadata_GetString") : nullptr);
    if(m_peak_icv_Metadata_GetString == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetString");
    }        

    m_peak_icv_Metadata_SetString = reinterpret_cast<dyn_peak_icv_Metadata_SetString>(load ? import_function(m_handle, "peak_icv_Metadata_SetString") : nullptr);
    if(m_peak_icv_Metadata_SetString == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetString");
    }        

    m_peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes") : nullptr);
    if(m_peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes");
    }        

    m_peak_icv_Metadata_GetStringArrayElement = reinterpret_cast<dyn_peak_icv_Metadata_GetStringArrayElement>(load ? import_function(m_handle, "peak_icv_Metadata_GetStringArrayElement") : nullptr);
    if(m_peak_icv_Metadata_GetStringArrayElement == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetStringArrayElement");
    }        

    m_peak_icv_Metadata_SetStringArray = reinterpret_cast<dyn_peak_icv_Metadata_SetStringArray>(load ? import_function(m_handle, "peak_icv_Metadata_SetStringArray") : nullptr);
    if(m_peak_icv_Metadata_SetStringArray == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_SetStringArray");
    }        

    m_peak_icv_Metadata_GetArray_GetCount = reinterpret_cast<dyn_peak_icv_Metadata_GetArray_GetCount>(load ? import_function(m_handle, "peak_icv_Metadata_GetArray_GetCount") : nullptr);
    if(m_peak_icv_Metadata_GetArray_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetArray_GetCount");
    }        

    m_peak_icv_Metadata_HasKey = reinterpret_cast<dyn_peak_icv_Metadata_HasKey>(load ? import_function(m_handle, "peak_icv_Metadata_HasKey") : nullptr);
    if(m_peak_icv_Metadata_HasKey == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_HasKey");
    }        

    m_peak_icv_Metadata_GetEntryCount = reinterpret_cast<dyn_peak_icv_Metadata_GetEntryCount>(load ? import_function(m_handle, "peak_icv_Metadata_GetEntryCount") : nullptr);
    if(m_peak_icv_Metadata_GetEntryCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetEntryCount");
    }        

    m_peak_icv_Metadata_GetKey_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_Metadata_GetKey_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_Metadata_GetKey_GetSizeInBytes") : nullptr);
    if(m_peak_icv_Metadata_GetKey_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetKey_GetSizeInBytes");
    }        

    m_peak_icv_Metadata_GetKey = reinterpret_cast<dyn_peak_icv_Metadata_GetKey>(load ? import_function(m_handle, "peak_icv_Metadata_GetKey") : nullptr);
    if(m_peak_icv_Metadata_GetKey == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetKey");
    }        

    m_peak_icv_Metadata_GetValueType = reinterpret_cast<dyn_peak_icv_Metadata_GetValueType>(load ? import_function(m_handle, "peak_icv_Metadata_GetValueType") : nullptr);
    if(m_peak_icv_Metadata_GetValueType == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Metadata_GetValueType");
    }        

    m_peak_icv_PointCloud_Create = reinterpret_cast<dyn_peak_icv_PointCloud_Create>(load ? import_function(m_handle, "peak_icv_PointCloud_Create") : nullptr);
    if(m_peak_icv_PointCloud_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_Create");
    }        

    m_peak_icv_PointCloud_CreateFromXYZImage = reinterpret_cast<dyn_peak_icv_PointCloud_CreateFromXYZImage>(load ? import_function(m_handle, "peak_icv_PointCloud_CreateFromXYZImage") : nullptr);
    if(m_peak_icv_PointCloud_CreateFromXYZImage == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_CreateFromXYZImage");
    }        

    m_peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage = reinterpret_cast<dyn_peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage>(load ? import_function(m_handle, "peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage") : nullptr);
    if(m_peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage");
    }        

    m_peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage = reinterpret_cast<dyn_peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage>(load ? import_function(m_handle, "peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage") : nullptr);
    if(m_peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage");
    }        

    m_peak_icv_PointCloud_CreateFromFile = reinterpret_cast<dyn_peak_icv_PointCloud_CreateFromFile>(load ? import_function(m_handle, "peak_icv_PointCloud_CreateFromFile") : nullptr);
    if(m_peak_icv_PointCloud_CreateFromFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_CreateFromFile");
    }        

    m_peak_icv_PointCloud_CreateFromPoints = reinterpret_cast<dyn_peak_icv_PointCloud_CreateFromPoints>(load ? import_function(m_handle, "peak_icv_PointCloud_CreateFromPoints") : nullptr);
    if(m_peak_icv_PointCloud_CreateFromPoints == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_CreateFromPoints");
    }        

    m_peak_icv_PointCloud_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_PointCloud_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_PointCloud_IncreaseUseCount") : nullptr);
    if(m_peak_icv_PointCloud_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_IncreaseUseCount");
    }        

    m_peak_icv_PointCloud_Destroy = reinterpret_cast<dyn_peak_icv_PointCloud_Destroy>(load ? import_function(m_handle, "peak_icv_PointCloud_Destroy") : nullptr);
    if(m_peak_icv_PointCloud_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_Destroy");
    }        

    m_peak_icv_PointCloud_GetType = reinterpret_cast<dyn_peak_icv_PointCloud_GetType>(load ? import_function(m_handle, "peak_icv_PointCloud_GetType") : nullptr);
    if(m_peak_icv_PointCloud_GetType == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_GetType");
    }        

    m_peak_icv_PointCloud_GetPoints_GetCount = reinterpret_cast<dyn_peak_icv_PointCloud_GetPoints_GetCount>(load ? import_function(m_handle, "peak_icv_PointCloud_GetPoints_GetCount") : nullptr);
    if(m_peak_icv_PointCloud_GetPoints_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_GetPoints_GetCount");
    }        

    m_peak_icv_PointCloud_GetPoints_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_PointCloud_GetPoints_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_PointCloud_GetPoints_GetSizeInBytes") : nullptr);
    if(m_peak_icv_PointCloud_GetPoints_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_GetPoints_GetSizeInBytes");
    }        

    m_peak_icv_PointCloud_GetPoints = reinterpret_cast<dyn_peak_icv_PointCloud_GetPoints>(load ? import_function(m_handle, "peak_icv_PointCloud_GetPoints") : nullptr);
    if(m_peak_icv_PointCloud_GetPoints == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_GetPoints");
    }        

    m_peak_icv_PointCloud_SaveToFile = reinterpret_cast<dyn_peak_icv_PointCloud_SaveToFile>(load ? import_function(m_handle, "peak_icv_PointCloud_SaveToFile") : nullptr);
    if(m_peak_icv_PointCloud_SaveToFile == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_SaveToFile");
    }        

    m_peak_icv_PointCloud_Transform = reinterpret_cast<dyn_peak_icv_PointCloud_Transform>(load ? import_function(m_handle, "peak_icv_PointCloud_Transform") : nullptr);
    if(m_peak_icv_PointCloud_Transform == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_Transform");
    }        

    m_peak_icv_PointCloud_TransformToWorkspace = reinterpret_cast<dyn_peak_icv_PointCloud_TransformToWorkspace>(load ? import_function(m_handle, "peak_icv_PointCloud_TransformToWorkspace") : nullptr);
    if(m_peak_icv_PointCloud_TransformToWorkspace == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_PointCloud_TransformToWorkspace");
    }        

    m_peak_icv_Polygon_Create = reinterpret_cast<dyn_peak_icv_Polygon_Create>(load ? import_function(m_handle, "peak_icv_Polygon_Create") : nullptr);
    if(m_peak_icv_Polygon_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_Create");
    }        

    m_peak_icv_Polygon_CreateFromPoints = reinterpret_cast<dyn_peak_icv_Polygon_CreateFromPoints>(load ? import_function(m_handle, "peak_icv_Polygon_CreateFromPoints") : nullptr);
    if(m_peak_icv_Polygon_CreateFromPoints == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_CreateFromPoints");
    }        

    m_peak_icv_Polygon_Destroy = reinterpret_cast<dyn_peak_icv_Polygon_Destroy>(load ? import_function(m_handle, "peak_icv_Polygon_Destroy") : nullptr);
    if(m_peak_icv_Polygon_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_Destroy");
    }        

    m_peak_icv_Polygon_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_Polygon_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_Polygon_IncreaseUseCount") : nullptr);
    if(m_peak_icv_Polygon_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_IncreaseUseCount");
    }        

    m_peak_icv_Polygon_GetPoints_GetCount = reinterpret_cast<dyn_peak_icv_Polygon_GetPoints_GetCount>(load ? import_function(m_handle, "peak_icv_Polygon_GetPoints_GetCount") : nullptr);
    if(m_peak_icv_Polygon_GetPoints_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_GetPoints_GetCount");
    }        

    m_peak_icv_Polygon_GetPointType = reinterpret_cast<dyn_peak_icv_Polygon_GetPointType>(load ? import_function(m_handle, "peak_icv_Polygon_GetPointType") : nullptr);
    if(m_peak_icv_Polygon_GetPointType == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_GetPointType");
    }        

    m_peak_icv_Polygon_IsClosed = reinterpret_cast<dyn_peak_icv_Polygon_IsClosed>(load ? import_function(m_handle, "peak_icv_Polygon_IsClosed") : nullptr);
    if(m_peak_icv_Polygon_IsClosed == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_IsClosed");
    }        

    m_peak_icv_Polygon_GetPoints_GetSizeInBytes = reinterpret_cast<dyn_peak_icv_Polygon_GetPoints_GetSizeInBytes>(load ? import_function(m_handle, "peak_icv_Polygon_GetPoints_GetSizeInBytes") : nullptr);
    if(m_peak_icv_Polygon_GetPoints_GetSizeInBytes == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_GetPoints_GetSizeInBytes");
    }        

    m_peak_icv_Polygon_GetPoints = reinterpret_cast<dyn_peak_icv_Polygon_GetPoints>(load ? import_function(m_handle, "peak_icv_Polygon_GetPoints") : nullptr);
    if(m_peak_icv_Polygon_GetPoints == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Polygon_GetPoints");
    }        

    m_peak_icv_Region_Create = reinterpret_cast<dyn_peak_icv_Region_Create>(load ? import_function(m_handle, "peak_icv_Region_Create") : nullptr);
    if(m_peak_icv_Region_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Create");
    }        

    m_peak_icv_Region_CreateFromPoints = reinterpret_cast<dyn_peak_icv_Region_CreateFromPoints>(load ? import_function(m_handle, "peak_icv_Region_CreateFromPoints") : nullptr);
    if(m_peak_icv_Region_CreateFromPoints == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_CreateFromPoints");
    }        

    m_peak_icv_Region_CreateFromRectangle = reinterpret_cast<dyn_peak_icv_Region_CreateFromRectangle>(load ? import_function(m_handle, "peak_icv_Region_CreateFromRectangle") : nullptr);
    if(m_peak_icv_Region_CreateFromRectangle == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_CreateFromRectangle");
    }        

    m_peak_icv_Region_IncreaseUseCount = reinterpret_cast<dyn_peak_icv_Region_IncreaseUseCount>(load ? import_function(m_handle, "peak_icv_Region_IncreaseUseCount") : nullptr);
    if(m_peak_icv_Region_IncreaseUseCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_IncreaseUseCount");
    }        

    m_peak_icv_Region_Destroy = reinterpret_cast<dyn_peak_icv_Region_Destroy>(load ? import_function(m_handle, "peak_icv_Region_Destroy") : nullptr);
    if(m_peak_icv_Region_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Destroy");
    }        

    m_peak_icv_Region_Array_Create = reinterpret_cast<dyn_peak_icv_Region_Array_Create>(load ? import_function(m_handle, "peak_icv_Region_Array_Create") : nullptr);
    if(m_peak_icv_Region_Array_Create == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Array_Create");
    }        

    m_peak_icv_Region_Array_Destroy = reinterpret_cast<dyn_peak_icv_Region_Array_Destroy>(load ? import_function(m_handle, "peak_icv_Region_Array_Destroy") : nullptr);
    if(m_peak_icv_Region_Array_Destroy == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Array_Destroy");
    }        

    m_peak_icv_Region_GetConnectedComponents_GetCount = reinterpret_cast<dyn_peak_icv_Region_GetConnectedComponents_GetCount>(load ? import_function(m_handle, "peak_icv_Region_GetConnectedComponents_GetCount") : nullptr);
    if(m_peak_icv_Region_GetConnectedComponents_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_GetConnectedComponents_GetCount");
    }        

    m_peak_icv_Region_GetConnectedComponents = reinterpret_cast<dyn_peak_icv_Region_GetConnectedComponents>(load ? import_function(m_handle, "peak_icv_Region_GetConnectedComponents") : nullptr);
    if(m_peak_icv_Region_GetConnectedComponents == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_GetConnectedComponents");
    }        

    m_peak_icv_Region_GetArea = reinterpret_cast<dyn_peak_icv_Region_GetArea>(load ? import_function(m_handle, "peak_icv_Region_GetArea") : nullptr);
    if(m_peak_icv_Region_GetArea == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_GetArea");
    }        

    m_peak_icv_Region_GetCenterOfGravity = reinterpret_cast<dyn_peak_icv_Region_GetCenterOfGravity>(load ? import_function(m_handle, "peak_icv_Region_GetCenterOfGravity") : nullptr);
    if(m_peak_icv_Region_GetCenterOfGravity == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_GetCenterOfGravity");
    }        

    m_peak_icv_Region_GetPoints_GetCount = reinterpret_cast<dyn_peak_icv_Region_GetPoints_GetCount>(load ? import_function(m_handle, "peak_icv_Region_GetPoints_GetCount") : nullptr);
    if(m_peak_icv_Region_GetPoints_GetCount == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_GetPoints_GetCount");
    }        

    m_peak_icv_Region_GetPoints = reinterpret_cast<dyn_peak_icv_Region_GetPoints>(load ? import_function(m_handle, "peak_icv_Region_GetPoints") : nullptr);
    if(m_peak_icv_Region_GetPoints == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_GetPoints");
    }        

    m_peak_icv_Region_Difference = reinterpret_cast<dyn_peak_icv_Region_Difference>(load ? import_function(m_handle, "peak_icv_Region_Difference") : nullptr);
    if(m_peak_icv_Region_Difference == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Difference");
    }        

    m_peak_icv_Region_Intersection = reinterpret_cast<dyn_peak_icv_Region_Intersection>(load ? import_function(m_handle, "peak_icv_Region_Intersection") : nullptr);
    if(m_peak_icv_Region_Intersection == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Intersection");
    }        

    m_peak_icv_Region_Union = reinterpret_cast<dyn_peak_icv_Region_Union>(load ? import_function(m_handle, "peak_icv_Region_Union") : nullptr);
    if(m_peak_icv_Region_Union == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Union");
    }        

    m_peak_icv_Region_Dilation = reinterpret_cast<dyn_peak_icv_Region_Dilation>(load ? import_function(m_handle, "peak_icv_Region_Dilation") : nullptr);
    if(m_peak_icv_Region_Dilation == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Dilation");
    }        

    m_peak_icv_Region_Erosion = reinterpret_cast<dyn_peak_icv_Region_Erosion>(load ? import_function(m_handle, "peak_icv_Region_Erosion") : nullptr);
    if(m_peak_icv_Region_Erosion == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Erosion");
    }        

    m_peak_icv_Region_Compare = reinterpret_cast<dyn_peak_icv_Region_Compare>(load ? import_function(m_handle, "peak_icv_Region_Compare") : nullptr);
    if(m_peak_icv_Region_Compare == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Compare");
    }        

    m_peak_icv_Region_Scale = reinterpret_cast<dyn_peak_icv_Region_Scale>(load ? import_function(m_handle, "peak_icv_Region_Scale") : nullptr);
    if(m_peak_icv_Region_Scale == nullptr && load)
    {
        throw std::runtime_error("Failed to load peak_icv_Region_Scale");
    }        

            
            return true;
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_CalibrationParameters_CreateFromFile(peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size, const char* file_path)
{
    auto& inst = instance();
    if(inst.m_peak_icv_CalibrationParameters_CreateFromFile)
    {
        return inst.m_peak_icv_CalibrationParameters_CreateFromFile(calibration_parameters, calibration_parameters_size, file_path);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_CalibrationParameters_SaveToFile(peak_icv_calibration_parameters calibration_parameters, size_t calibration_parameters_size, const char* file_path, peak_icv_calibration_parameters_save_options save_options)
{
    auto& inst = instance();
    if(inst.m_peak_icv_CalibrationParameters_SaveToFile)
    {
        return inst.m_peak_icv_CalibrationParameters_SaveToFile(calibration_parameters, calibration_parameters_size, file_path, save_options);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_CalibrationParameters_ToBinary(peak_icv_calibration_parameters calibration_parameters, size_t calibration_parameters_size, uint8_t* calibration_parameters_binary, size_t calibration_parameters_binary_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_CalibrationParameters_ToBinary)
    {
        return inst.m_peak_icv_CalibrationParameters_ToBinary(calibration_parameters, calibration_parameters_size, calibration_parameters_binary, calibration_parameters_binary_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes(size_t calibration_parameters_size, size_t* binary_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes)
    {
        return inst.m_peak_icv_CalibrationParameters_ToBinaryGetSizeInBytes(calibration_parameters_size, binary_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_CalibrationParameters_CreateFromBinary(const uint8_t* binary_data, size_t binary_data_size, peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_CalibrationParameters_CreateFromBinary)
    {
        return inst.m_peak_icv_CalibrationParameters_CreateFromBinary(binary_data, binary_data_size, calibration_parameters, calibration_parameters_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Plate_Create(peak_icv_calibration_plate_handle* calibration_plate_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Plate_Create)
    {
        return inst.m_peak_icv_Calibration_Plate_Create(calibration_plate_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Plate_CreateFromFile(peak_icv_calibration_plate_handle* calibration_plate_handle, const char* file_path)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Plate_CreateFromFile)
    {
        return inst.m_peak_icv_Calibration_Plate_CreateFromFile(calibration_plate_handle, file_path);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Plate_IncreaseUseCount(peak_icv_calibration_plate_handle calibration_plate_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Plate_IncreaseUseCount)
    {
        return inst.m_peak_icv_Calibration_Plate_IncreaseUseCount(calibration_plate_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Plate_Destroy(peak_icv_calibration_plate_handle calibration_plate_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Plate_Destroy)
    {
        return inst.m_peak_icv_Calibration_Plate_Destroy(calibration_plate_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_Create(peak_icv_calibration_result_handle* calibration_result_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_Create)
    {
        return inst.m_peak_icv_Calibration_Result_Create(calibration_result_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_SaveToFile(peak_icv_calibration_result_handle calibration_result_handle, const char* file_path, peak_icv_calibration_result_save_options save_options)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_SaveToFile)
    {
        return inst.m_peak_icv_Calibration_Result_SaveToFile(calibration_result_handle, file_path, save_options);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_CreateFromFile(peak_icv_calibration_result_handle* calibration_result_handle, const char* file_path)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_CreateFromFile)
    {
        return inst.m_peak_icv_Calibration_Result_CreateFromFile(calibration_result_handle, file_path);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_Destroy(peak_icv_calibration_result_handle calibration_result_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_Destroy)
    {
        return inst.m_peak_icv_Calibration_Result_Destroy(calibration_result_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_IncreaseUseCount(peak_icv_calibration_result_handle calibration_result_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_IncreaseUseCount)
    {
        return inst.m_peak_icv_Calibration_Result_IncreaseUseCount(calibration_result_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_GetMeanReprojectionError(peak_icv_calibration_result_handle calibration_result_handle, double* mean_reprojection_error)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_GetMeanReprojectionError)
    {
        return inst.m_peak_icv_Calibration_Result_GetMeanReprojectionError(calibration_result_handle, mean_reprojection_error);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_GetCalibrationViews_GetCount(peak_icv_calibration_result_handle calibration_result_handle, size_t* calibration_view_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_GetCalibrationViews_GetCount)
    {
        return inst.m_peak_icv_Calibration_Result_GetCalibrationViews_GetCount(calibration_result_handle, calibration_view_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_GetCalibrationViews(peak_icv_calibration_result_handle calibration_result_handle, peak_icv_calibration_view_handle* calibration_views, size_t calibration_views_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_GetCalibrationViews)
    {
        return inst.m_peak_icv_Calibration_Result_GetCalibrationViews(calibration_result_handle, calibration_views, calibration_views_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Result_ToParameters(peak_icv_calibration_result_handle calibration_result_handle, peak_icv_calibration_parameters* calibration_parameters, size_t calibration_parameters_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Result_ToParameters)
    {
        return inst.m_peak_icv_Calibration_Result_ToParameters(calibration_result_handle, calibration_parameters, calibration_parameters_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_Create(peak_icv_calibration_view_handle* calibration_view_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_Create)
    {
        return inst.m_peak_icv_Calibration_View_Create(calibration_view_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_Array_Create(peak_icv_calibration_view_handle* calibration_view_handles, size_t num_calibration_views)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_Array_Create)
    {
        return inst.m_peak_icv_Calibration_View_Array_Create(calibration_view_handles, num_calibration_views);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_IncreaseUseCount(peak_icv_calibration_view_handle calibration_view_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_IncreaseUseCount)
    {
        return inst.m_peak_icv_Calibration_View_IncreaseUseCount(calibration_view_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_Destroy(peak_icv_calibration_view_handle calibration_view_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_Destroy)
    {
        return inst.m_peak_icv_Calibration_View_Destroy(calibration_view_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_Array_Destroy(peak_icv_calibration_view_handle* calibration_view_handles, size_t num_calibration_views)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_Array_Destroy)
    {
        return inst.m_peak_icv_Calibration_View_Array_Destroy(calibration_view_handles, num_calibration_views);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_GetReprojectionErrors(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_reprojection_error* reprojection_errors, size_t num_reprojection_errors)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_GetReprojectionErrors)
    {
        return inst.m_peak_icv_Calibration_View_GetReprojectionErrors(calibration_view_handle, reprojection_errors, num_reprojection_errors);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_GetMeanReprojectionError(peak_icv_calibration_view_handle calibration_view_handle, double* mean_reprojection_error)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_GetMeanReprojectionError)
    {
        return inst.m_peak_icv_Calibration_View_GetMeanReprojectionError(calibration_view_handle, mean_reprojection_error);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_GetMaximumReprojectionError(peak_icv_calibration_view_handle calibration_view_handle, double* maximum_reprojection_error)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_GetMaximumReprojectionError)
    {
        return inst.m_peak_icv_Calibration_View_GetMaximumReprojectionError(calibration_view_handle, maximum_reprojection_error);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_GetReprojectionErrors_GetCount(peak_icv_calibration_view_handle calibration_view_handle, size_t* num_reprojection_errors)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_GetReprojectionErrors_GetCount)
    {
        return inst.m_peak_icv_Calibration_View_GetReprojectionErrors_GetCount(calibration_view_handle, num_reprojection_errors);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_GetExtrinsicParameters(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_extrinsic_parameters* extrinsic_parameters, size_t extrinsic_parameters_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_GetExtrinsicParameters)
    {
        return inst.m_peak_icv_Calibration_View_GetExtrinsicParameters(calibration_view_handle, extrinsic_parameters, extrinsic_parameters_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_GetConvexHull(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_polygon_handle* polygon_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_GetConvexHull)
    {
        return inst.m_peak_icv_Calibration_View_GetConvexHull(calibration_view_handle, polygon_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_View_GetCoordinateSystem(peak_icv_calibration_view_handle calibration_view_handle, peak_icv_coordinate_system* coordinate_system)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_View_GetCoordinateSystem)
    {
        return inst.m_peak_icv_Calibration_View_GetCoordinateSystem(calibration_view_handle, coordinate_system);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Process(peak_icv_calibration_plate_handle input_calibration_plate, peak_icv_image_handle* input_images, size_t num_input_images, peak_icv_calibration_result_handle* output_calibration_result)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Process)
    {
        return inst.m_peak_icv_Calibration_Process(input_calibration_plate, input_images, num_input_images, output_calibration_result);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix(peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_transformation_matrix_3d* transformation_matrix)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix)
    {
        return inst.m_peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix(extrinsic_parameters, extrinsic_parameters_size, transformation_matrix);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_WorkspaceCalibration_Process(peak_icv_calibration_plate_handle calibration_plate, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_image_handle image, peak_icv_calibration_result_handle* calibration_result)
{
    auto& inst = instance();
    if(inst.m_peak_icv_WorkspaceCalibration_Process)
    {
        return inst.m_peak_icv_WorkspaceCalibration_Process(calibration_plate, intrinsic_parameters, intrinsic_parameters_size, image, calibration_result);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReaderResult_Create(peak_icv_code_reader_result_handle* result)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReaderResult_Create)
    {
        return inst.m_peak_icv_BarcodeReaderResult_Create(result);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReaderResult_Array_Create(peak_icv_code_reader_result_handle* result, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReaderResult_Array_Create)
    {
        return inst.m_peak_icv_BarcodeReaderResult_Array_Create(result, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReaderResult_Destroy(peak_icv_code_reader_result_handle result)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReaderResult_Destroy)
    {
        return inst.m_peak_icv_BarcodeReaderResult_Destroy(result);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes(peak_icv_code_reader_result_handle result, size_t* text_size_in_bytes)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes)
    {
        return inst.m_peak_icv_BarcodeReaderResult_GetText_GetSizeInBytes(result, text_size_in_bytes);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReaderResult_GetText(peak_icv_code_reader_result_handle result, char* text, size_t text_size_in_bytes)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReaderResult_GetText)
    {
        return inst.m_peak_icv_BarcodeReaderResult_GetText(result, text, text_size_in_bytes);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReaderResult_GetType(peak_icv_code_reader_result_handle result, peak_icv_code_type* code_type)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReaderResult_GetType)
    {
        return inst.m_peak_icv_BarcodeReaderResult_GetType(result, code_type);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReader_Create(peak_icv_code_reader_handle* handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReader_Create)
    {
        return inst.m_peak_icv_BarcodeReader_Create(handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReader_Destroy(peak_icv_code_reader_handle handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReader_Destroy)
    {
        return inst.m_peak_icv_BarcodeReader_Destroy(handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReader_GetCodeTypesGetCount(peak_icv_code_reader_handle handle, size_t* count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReader_GetCodeTypesGetCount)
    {
        return inst.m_peak_icv_BarcodeReader_GetCodeTypesGetCount(handle, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReader_GetCodeTypes(peak_icv_code_reader_handle handle, peak_icv_code_type* barcode_types, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReader_GetCodeTypes)
    {
        return inst.m_peak_icv_BarcodeReader_GetCodeTypes(handle, barcode_types, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReader_SetCodeTypes(peak_icv_code_reader_handle handle, peak_icv_code_type* barcode_types, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReader_SetCodeTypes)
    {
        return inst.m_peak_icv_BarcodeReader_SetCodeTypes(handle, barcode_types, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReader_DetectAndDecode(peak_icv_code_reader_handle handle, peak_icv_image_handle input_image, peak_icv_code_reader_result_handle* result, size_t result_count, size_t* found_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReader_DetectAndDecode)
    {
        return inst.m_peak_icv_BarcodeReader_DetectAndDecode(handle, input_image, result, result_count, found_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect(peak_icv_code_reader_handle handle, size_t max_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect)
    {
        return inst.m_peak_icv_BarcodeReader_SetMaximumNumberOfCodesToDetect(handle, max_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect(peak_icv_code_reader_handle handle, size_t* max_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect)
    {
        return inst.m_peak_icv_BarcodeReader_GetMaximumNumberOfCodesToDetect(handle, max_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ImageFilter_Sharpening_ProcessInPlace(peak_icv_image_handle input_image, uint32_t sharpness_level)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ImageFilter_Sharpening_ProcessInPlace)
    {
        return inst.m_peak_icv_ImageFilter_Sharpening_ProcessInPlace(input_image, sharpness_level);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ImageFilter_Sharpening_GetRange(peak_common_interval_u* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ImageFilter_Sharpening_GetRange)
    {
        return inst.m_peak_icv_ImageFilter_Sharpening_GetRange(range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Filter_Image_Median(peak_icv_image_handle input_image, size_t kernel_size, peak_icv_image_handle output_image)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Filter_Image_Median)
    {
        return inst.m_peak_icv_Filter_Image_Median(input_image, kernel_size, output_image);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_Create(peak_icv_hdr_handle* hdr_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_Create)
    {
        return inst.m_peak_icv_HDR_Create(hdr_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_EstimateResponseCurve(peak_icv_hdr_handle hdr_handle, peak_icv_image_handle* input_images, size_t num_input_images)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_EstimateResponseCurve)
    {
        return inst.m_peak_icv_HDR_EstimateResponseCurve(hdr_handle, input_images, num_input_images);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_Process_GetOutputPixelFormat(peak_icv_hdr_handle hdr_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_Process_GetOutputPixelFormat)
    {
        return inst.m_peak_icv_HDR_Process_GetOutputPixelFormat(hdr_handle, input_pixel_format, output_pixel_format);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_Process(peak_icv_hdr_handle hdr_handle, peak_icv_image_handle* input_images, size_t num_input_images, peak_icv_image_handle output_image)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_Process)
    {
        return inst.m_peak_icv_HDR_Process(hdr_handle, input_images, num_input_images, output_image);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_GetAlgorithm(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_algorithm* algorithm)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_GetAlgorithm)
    {
        return inst.m_peak_icv_HDR_GetAlgorithm(hdr_handle, algorithm);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_Destroy(peak_icv_hdr_handle hdr_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_Destroy)
    {
        return inst.m_peak_icv_HDR_Destroy(hdr_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_GetResponseCurve(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_response_curve_handle* response_curve_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_GetResponseCurve)
    {
        return inst.m_peak_icv_HDR_GetResponseCurve(hdr_handle, response_curve_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_SetResponseCurve(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_response_curve_handle response_curve_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_SetResponseCurve)
    {
        return inst.m_peak_icv_HDR_SetResponseCurve(hdr_handle, response_curve_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_ResponseCurve_Create(peak_icv_hdr_response_curve_handle* response_curve_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_ResponseCurve_Create)
    {
        return inst.m_peak_icv_HDR_ResponseCurve_Create(response_curve_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_ResponseCurve_CreateFromFile(peak_icv_hdr_response_curve_handle* response_curve_handle, const char* file_path)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_ResponseCurve_CreateFromFile)
    {
        return inst.m_peak_icv_HDR_ResponseCurve_CreateFromFile(response_curve_handle, file_path);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_ResponseCurve_IncreaseUseCount(peak_icv_hdr_response_curve_handle response_curve_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_ResponseCurve_IncreaseUseCount)
    {
        return inst.m_peak_icv_HDR_ResponseCurve_IncreaseUseCount(response_curve_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_ResponseCurve_Destroy(peak_icv_hdr_response_curve_handle response_curve_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_ResponseCurve_Destroy)
    {
        return inst.m_peak_icv_HDR_ResponseCurve_Destroy(response_curve_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_ResponseCurve_SaveToFile(peak_icv_hdr_response_curve_handle response_curve_handle, const char* file_path)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_ResponseCurve_SaveToFile)
    {
        return inst.m_peak_icv_HDR_ResponseCurve_SaveToFile(response_curve_handle, file_path);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_HDR_ResponseCurve_Compare(peak_icv_hdr_response_curve_handle response_curve_handle_lhs, peak_icv_hdr_response_curve_handle response_curve_handle_rhs, bool* is_equal)
{
    auto& inst = instance();
    if(inst.m_peak_icv_HDR_ResponseCurve_Compare)
    {
        return inst.m_peak_icv_HDR_ResponseCurve_Compare(response_curve_handle_lhs, response_curve_handle_rhs, is_equal);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Drago_Create(peak_icv_tone_mapping_drago_handle* tone_mapping_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Drago_Create)
    {
        return inst.m_peak_icv_ToneMapping_Drago_Create(tone_mapping_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Drago_Destroy(peak_icv_tone_mapping_drago_handle tone_mapping_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Drago_Destroy)
    {
        return inst.m_peak_icv_ToneMapping_Drago_Destroy(tone_mapping_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Drago_GetOutputPixelFormat(peak_icv_tone_mapping_drago_handle tone_mapping_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Drago_GetOutputPixelFormat)
    {
        return inst.m_peak_icv_ToneMapping_Drago_GetOutputPixelFormat(tone_mapping_handle, input_pixel_format, output_pixel_format);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Drago_Process(peak_icv_tone_mapping_drago_handle tone_mapping_handle, peak_icv_image_handle input_hdr_image, peak_icv_image_handle output_ldr_image)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Drago_Process)
    {
        return inst.m_peak_icv_ToneMapping_Drago_Process(tone_mapping_handle, input_hdr_image, output_ldr_image);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Linear_Create(peak_icv_tone_mapping_linear_handle* tone_mapping_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Linear_Create)
    {
        return inst.m_peak_icv_ToneMapping_Linear_Create(tone_mapping_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Linear_Destroy(peak_icv_tone_mapping_linear_handle tone_mapping_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Linear_Destroy)
    {
        return inst.m_peak_icv_ToneMapping_Linear_Destroy(tone_mapping_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Linear_GetOutputPixelFormat(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Linear_GetOutputPixelFormat)
    {
        return inst.m_peak_icv_ToneMapping_Linear_GetOutputPixelFormat(tone_mapping_handle, input_pixel_format, output_pixel_format);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Linear_Process(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_icv_image_handle hdr_image, float center_exposure_value, float number_of_stops, peak_icv_image_handle ldr_image)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Linear_Process)
    {
        return inst.m_peak_icv_ToneMapping_Linear_Process(tone_mapping_handle, hdr_image, center_exposure_value, number_of_stops, ldr_image);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ToneMapping_Linear_GetExposureValueRange(peak_icv_tone_mapping_linear_handle tone_mapping_handle, peak_icv_image_handle hdr_image, peak_common_interval_f* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ToneMapping_Linear_GetExposureValueRange)
    {
        return inst.m_peak_icv_ToneMapping_Linear_GetExposureValueRange(tone_mapping_handle, hdr_image, range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_Create(peak_icv_color_matrix_transformation_handle* color_matrix_transformation_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_Create)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_Create(color_matrix_transformation_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_Destroy(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_Destroy)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_Destroy(color_matrix_transformation_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* needs_processing)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_NeedsProcessing(color_matrix_transformation_handle, needs_processing);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_image_handle input_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ProcessInplace(color_matrix_transformation_handle, input_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix color_correction_matrix)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_SetColorCorrectionMatrix(color_matrix_transformation_handle, color_correction_matrix);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix* color_correction_matrix)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_GetColorCorrectionMatrix(color_matrix_transformation_handle, color_correction_matrix);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, float saturation)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_SetSaturation(color_matrix_transformation_handle, saturation);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, float* saturation)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturation(color_matrix_transformation_handle, saturation);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_common_interval_f* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_GetSaturationRange(color_matrix_transformation_handle, range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_correction_matrix* color_correction_matrix)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_GetEffectiveMatrix(color_matrix_transformation_handle, color_correction_matrix);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_space* color_space)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetTargetColorSpace(color_matrix_transformation_handle, color_space);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_color_space color_space)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetTargetColorSpace(color_matrix_transformation_handle, color_space);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_chromatic_adaption_algorithm* algorithm)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetAlgorithm(color_matrix_transformation_handle, algorithm);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_icv_chromatic_adaption_algorithm algorithm)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetAlgorithm(color_matrix_transformation_handle, algorithm);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, uint32_t color_temperature)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetColorTemperature(color_matrix_transformation_handle, color_temperature);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, uint32_t* color_temperature)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperature(color_matrix_transformation_handle, color_temperature);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_ResetColorTemperature(color_matrix_transformation_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, peak_common_range_u* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_GetColorTemperatureRange(color_matrix_transformation_handle, range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* has_color_temperature)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_HasColorTemperature(color_matrix_transformation_handle, has_color_temperature);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_SetEnabled(color_matrix_transformation_handle, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ChromaticAdaption_IsEnabled(color_matrix_transformation_handle, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_SetEnabled(color_matrix_transformation_handle, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_Saturation_IsEnabled(color_matrix_transformation_handle, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool enabled)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_SetEnabled(color_matrix_transformation_handle, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled(peak_icv_color_matrix_transformation_handle color_matrix_transformation_handle, bool* enabled)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled)
    {
        return inst.m_peak_icv_Preprocessing_ColorMatrixTransformation_ColorCorrection_IsEnabled(color_matrix_transformation_handle, enabled);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_Create(peak_icv_downsampling_handle* downsampling_handle, peak_icv_downsampling_factor factor, peak_icv_downsampling_mode mode)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_Create)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_Create(downsampling_handle, factor, mode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_Destroy(peak_icv_downsampling_handle downsampling_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_Destroy)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_Destroy(downsampling_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_SetFactor(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_factor factor)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_SetFactor)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_SetFactor(downsampling_handle, factor);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_GetFactor(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_factor* factor)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_GetFactor)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_GetFactor(downsampling_handle, factor);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_GetRange(peak_icv_downsampling_handle downsampling_handle, peak_common_interval_u* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_GetRange)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_GetRange(downsampling_handle, range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_SetMode(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_mode mode)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_SetMode)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_SetMode(downsampling_handle, mode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_GetMode(peak_icv_downsampling_handle downsampling_handle, peak_icv_downsampling_mode* mode)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_GetMode)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_GetMode(downsampling_handle, mode);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_GetOutputImageSize(peak_icv_downsampling_handle downsampling_handle, peak_icv_image_handle input_image_handle, peak_common_size* output_image_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_GetOutputImageSize)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_GetOutputImageSize(downsampling_handle, input_image_handle, output_image_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_NeedsProcessing(peak_icv_downsampling_handle downsampling_handle, bool* needs_processing)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_NeedsProcessing)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_NeedsProcessing(downsampling_handle, needs_processing);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Downsampling_Process(peak_icv_downsampling_handle downsampling_handle, peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Downsampling_Process)
    {
        return inst.m_peak_icv_Preprocessing_Downsampling_Process(downsampling_handle, input_image_handle, output_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Gain_Create(peak_icv_gain_handle* gain_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Gain_Create)
    {
        return inst.m_peak_icv_Preprocessing_Gain_Create(gain_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Gain_Destroy(peak_icv_gain_handle gain_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Gain_Destroy)
    {
        return inst.m_peak_icv_Preprocessing_Gain_Destroy(gain_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Gain_ProcessInplace(peak_icv_gain_handle gain_handle, peak_icv_image_handle input_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Gain_ProcessInplace)
    {
        return inst.m_peak_icv_Preprocessing_Gain_ProcessInplace(gain_handle, input_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Gain_NeedsProcessing(peak_icv_gain_handle gain_handle, bool* needs_processing)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Gain_NeedsProcessing)
    {
        return inst.m_peak_icv_Preprocessing_Gain_NeedsProcessing(gain_handle, needs_processing);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Gain_SetValue(peak_icv_gain_handle gain_handle, peak_icv_gain_type type, float value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Gain_SetValue)
    {
        return inst.m_peak_icv_Preprocessing_Gain_SetValue(gain_handle, type, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Gain_GetValue(peak_icv_gain_handle gain_handle, peak_icv_gain_type type, float* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Gain_GetValue)
    {
        return inst.m_peak_icv_Preprocessing_Gain_GetValue(gain_handle, type, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Gain_GetRange(peak_icv_gain_handle gain_handle, peak_common_interval_f* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Gain_GetRange)
    {
        return inst.m_peak_icv_Preprocessing_Gain_GetRange(gain_handle, range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_Create(peak_icv_hotpixel_correction_handle* hotpixel_correction_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_Create)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_Create(hotpixel_correction_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_Destroy(peak_icv_hotpixel_correction_handle hotpixel_correction_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_Destroy)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_Destroy(hotpixel_correction_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount(peak_icv_hotpixel_correction_handle hotpixel_correction_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount(hotpixel_correction_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_Detect(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_icv_image_handle input_image_handle, uint32_t sensitivity, float gainFactor)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_Detect)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_Detect(hotpixel_correction_handle, input_image_handle, sensitivity, gainFactor);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_icv_image_handle input_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace(hotpixel_correction_handle, input_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_SetList(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_point* list, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_SetList)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_SetList(hotpixel_correction_handle, list, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_ResetList(peak_icv_hotpixel_correction_handle hotpixel_correction_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_ResetList)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_ResetList(hotpixel_correction_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, size_t* count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount(hotpixel_correction_handle, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_GetList(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_point* list, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_GetList)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_GetList(hotpixel_correction_handle, list, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange(peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_interval_u* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange)
    {
        return inst.m_peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange(hotpixel_correction_handle, range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ImageConverter_Create(peak_icv_image_converter_handle* image_converter_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ImageConverter_Create)
    {
        return inst.m_peak_icv_Preprocessing_ImageConverter_Create(image_converter_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ImageConverter_Destroy(peak_icv_image_converter_handle image_converter_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ImageConverter_Destroy)
    {
        return inst.m_peak_icv_Preprocessing_ImageConverter_Destroy(image_converter_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ImageConverter_Convert(peak_icv_image_converter_handle converter_handle, peak_icv_image_handle input_handle, enum peak_common_pixel_format pixel_format, peak_icv_image_handle* output_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ImageConverter_Convert)
    {
        return inst.m_peak_icv_Preprocessing_ImageConverter_Convert(converter_handle, input_handle, pixel_format, output_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ImageConverter_ReleaseBuffers(peak_icv_image_converter_handle converter_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ImageConverter_ReleaseBuffers)
    {
        return inst.m_peak_icv_Preprocessing_ImageConverter_ReleaseBuffers(converter_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Transformation_GetOutputPixelFormat(peak_common_pixel_format input_pixel_format, peak_icv_preprocessing_transformation_parameters parameters, peak_common_pixel_format* output_pixel_format)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Transformation_GetOutputPixelFormat)
    {
        return inst.m_peak_icv_Preprocessing_Transformation_GetOutputPixelFormat(input_pixel_format, parameters, output_pixel_format);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_Transformation_Process(peak_icv_image_handle input_image_handle, peak_icv_preprocessing_transformation_parameters parameters, peak_icv_image_handle output_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_Transformation_Process)
    {
        return inst.m_peak_icv_Preprocessing_Transformation_Process(input_image_handle, parameters, output_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_Create(peak_icv_tone_curve_correction_handle* tone_curve_correction_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_Create)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_Create(tone_curve_correction_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_Destroy(peak_icv_tone_curve_correction_handle tone_curve_correction_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_Destroy)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_Destroy(tone_curve_correction_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_common_interval_f* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_GetGammaRange(tone_curve_correction_handle, range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_common_interval_f* range)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlackRange(tone_curve_correction_handle, range);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_GetGamma(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_GetGamma)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_GetGamma(tone_curve_correction_handle, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_GetDigitalBlack(tone_curve_correction_handle, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_SetGamma(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_SetGamma)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_SetGamma(tone_curve_correction_handle, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, float value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_SetDigitalBlack(tone_curve_correction_handle, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, bool* needs_processing)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_NeedsProcessing(tone_curve_correction_handle, needs_processing);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace(peak_icv_tone_curve_correction_handle tone_curve_correction_handle, peak_icv_image_handle input_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace)
    {
        return inst.m_peak_icv_Preprocessing_ToneCurveCorrection_ProcessInplace(tone_curve_correction_handle, input_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Threshold_Process(peak_icv_image_handle input_image, c_peak_icv_variant_interval interval, size_t size_of_interval, peak_icv_region_handle* output_region)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Threshold_Process)
    {
        return inst.m_peak_icv_Threshold_Process(input_image, interval, size_of_interval, output_region);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Threshold_GetRange(peak_icv_image_handle image, peak_icv_variant_interval interval, size_t size_of_interval)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Threshold_GetRange)
    {
        return inst.m_peak_icv_Threshold_GetRange(image, interval, size_of_interval);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_Undistortion_Process(peak_icv_undistortion_handle undistortion_handle, peak_icv_image_handle input_image, peak_icv_image_handle output_image)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_Undistortion_Process)
    {
        return inst.m_peak_icv_Transform_Undistortion_Process(undistortion_handle, input_image, output_image);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_Undistortion_Create(peak_icv_undistortion_handle* undistortion_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_Undistortion_Create)
    {
        return inst.m_peak_icv_Transform_Undistortion_Create(undistortion_handle, intrinsic_parameters, intrinsic_parameters_size, new_intrinsic_parameters);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation(peak_icv_undistortion_handle* undistortion_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_capture_information image_capture_information, size_t capture_information_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation)
    {
        return inst.m_peak_icv_Transform_Undistortion_Create_With_Image_CaptureInformation(undistortion_handle, intrinsic_parameters, intrinsic_parameters_size, image_capture_information, capture_information_size, new_intrinsic_parameters);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_Undistortion_CreateWithImageMetadata(peak_icv_undistortion_handle* undistortion_handle, peak_icv_metadata_handle metadata_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_intrinsic_parameters* new_intrinsic_parameters)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_Undistortion_CreateWithImageMetadata)
    {
        return inst.m_peak_icv_Transform_Undistortion_CreateWithImageMetadata(undistortion_handle, metadata_handle, intrinsic_parameters, intrinsic_parameters_size, new_intrinsic_parameters);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_Undistortion_IncreaseUseCount(peak_icv_undistortion_handle undistortion_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_Undistortion_IncreaseUseCount)
    {
        return inst.m_peak_icv_Transform_Undistortion_IncreaseUseCount(undistortion_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_Undistortion_Destroy(peak_icv_undistortion_handle undistortion_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_Undistortion_Destroy)
    {
        return inst.m_peak_icv_Transform_Undistortion_Destroy(undistortion_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_Undistortion_SetInterpolation(peak_icv_undistortion_handle undistortion_handle, enum peak_icv_interpolation interpolation)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_Undistortion_SetInterpolation)
    {
        return inst.m_peak_icv_Transform_Undistortion_SetInterpolation(undistortion_handle, interpolation);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_Undistortion_GetInterpolation(peak_icv_undistortion_handle undistortion_handle, enum peak_icv_interpolation* interpolation)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_Undistortion_GetInterpolation)
    {
        return inst.m_peak_icv_Transform_Undistortion_GetInterpolation(undistortion_handle, interpolation);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Transform_DepthMap_To_XYZImage(peak_icv_image_handle xyz_image_handle, peak_icv_intrinsic_parameters intrinsic_parameters, size_t intrinsic_parameters_size, peak_icv_image_handle depth_map_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Transform_DepthMap_To_XYZImage)
    {
        return inst.m_peak_icv_Transform_DepthMap_To_XYZImage(xyz_image_handle, intrinsic_parameters, intrinsic_parameters_size, depth_map_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_ValidateBinary(const uint8_t* binary, size_t binary_size, bool* is_valid)
{
    auto& inst = instance();
    if(inst.m_peak_icv_ValidateBinary)
    {
        return inst.m_peak_icv_ValidateBinary(binary, binary_size, is_valid);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Init()
{
    auto& inst = instance();
    if(inst.m_peak_icv_Init)
    {
        return inst.m_peak_icv_Init();
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Exit()
{
    auto& inst = instance();
    if(inst.m_peak_icv_Exit)
    {
        return inst.m_peak_icv_Exit();
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_GetVersion(uint32_t* major_version, uint32_t* minor_version, uint32_t* subminor_version, uint32_t* patch_version)
{
    auto& inst = instance();
    if(inst.m_peak_icv_GetVersion)
    {
        return inst.m_peak_icv_GetVersion(major_version, minor_version, subminor_version, patch_version);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_GetLastErrorMessage_GetCount(size_t* last_error_message_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_GetLastErrorMessage_GetCount)
    {
        return inst.m_peak_icv_GetLastErrorMessage_GetCount(last_error_message_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_GetLastErrorMessage(char* last_error_message, size_t last_error_message_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_GetLastErrorMessage)
    {
        return inst.m_peak_icv_GetLastErrorMessage(last_error_message, last_error_message_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Draw(peak_icv_image_handle image, peak_icv_region_handle input_region, peak_icv_drawing_options drawing_options)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Draw)
    {
        return inst.m_peak_icv_Region_Draw(image, input_region, drawing_options);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_SelectByArea_GetCount(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_u area, size_t* num_output_regions)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_SelectByArea_GetCount)
    {
        return inst.m_peak_icv_Region_SelectByArea_GetCount(input_regions, num_input_regions, area, num_output_regions);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_SelectByArea(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_u area, peak_icv_region_handle* output_regions, size_t num_output_regions)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_SelectByArea)
    {
        return inst.m_peak_icv_Region_SelectByArea(input_regions, num_input_regions, area, output_regions, num_output_regions);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_SelectByCenterOfGravityX_GetCount(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f x, size_t* num_output_regions)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_SelectByCenterOfGravityX_GetCount)
    {
        return inst.m_peak_icv_Region_SelectByCenterOfGravityX_GetCount(input_regions, num_input_regions, x, num_output_regions);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_SelectByCenterOfGravityX(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f x, peak_icv_region_handle* output_regions, size_t num_output_regions)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_SelectByCenterOfGravityX)
    {
        return inst.m_peak_icv_Region_SelectByCenterOfGravityX(input_regions, num_input_regions, x, output_regions, num_output_regions);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_SelectByCenterOfGravityY_GetCount(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f y, size_t* num_output_regions)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_SelectByCenterOfGravityY_GetCount)
    {
        return inst.m_peak_icv_Region_SelectByCenterOfGravityY_GetCount(input_regions, num_input_regions, y, num_output_regions);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_SelectByCenterOfGravityY(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_interval_f y, peak_icv_region_handle* output_regions, size_t num_output_regions)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_SelectByCenterOfGravityY)
    {
        return inst.m_peak_icv_Region_SelectByCenterOfGravityY(input_regions, num_input_regions, y, output_regions, num_output_regions);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_SelectByCenterOfGravityRect_GetCount(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_rectangle_f rect, size_t* num_output_regions)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_SelectByCenterOfGravityRect_GetCount)
    {
        return inst.m_peak_icv_Region_SelectByCenterOfGravityRect_GetCount(input_regions, num_input_regions, rect, num_output_regions);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_SelectByCenterOfGravityRect(peak_icv_region_handle* input_regions, size_t num_input_regions, peak_common_rectangle_f rect, peak_icv_region_handle* output_regions, size_t num_output_regions)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_SelectByCenterOfGravityRect)
    {
        return inst.m_peak_icv_Region_SelectByCenterOfGravityRect(input_regions, num_input_regions, rect, output_regions, num_output_regions);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_Create(peak_icv_archive_handle* archive_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_Create)
    {
        return inst.m_peak_icv_Archive_Create(archive_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_CreateFromString(peak_icv_archive_handle* archive_handle, peak_icv_serialization_type data_type, const char* data)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_CreateFromString)
    {
        return inst.m_peak_icv_Archive_CreateFromString(archive_handle, data_type, data);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_Destroy(peak_icv_archive_handle archive_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_Destroy)
    {
        return inst.m_peak_icv_Archive_Destroy(archive_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_HasKey(peak_icv_archive_handle archive_handle, const char* key, bool* has_key)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_HasKey)
    {
        return inst.m_peak_icv_Archive_HasKey(archive_handle, key, has_key);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetKeys_GetCount(peak_icv_archive_handle archive_handle, size_t* count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetKeys_GetCount)
    {
        return inst.m_peak_icv_Archive_GetKeys_GetCount(archive_handle, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetKeysElement_GetSizeInBytes(peak_icv_archive_handle archive_handle, size_t index, size_t* size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetKeysElement_GetSizeInBytes)
    {
        return inst.m_peak_icv_Archive_GetKeysElement_GetSizeInBytes(archive_handle, index, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetKeysElement(peak_icv_archive_handle archive_handle, size_t index, char* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetKeysElement)
    {
        return inst.m_peak_icv_Archive_GetKeysElement(archive_handle, index, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetValueType(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_value_type_t* type)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetValueType)
    {
        return inst.m_peak_icv_Archive_GetValueType(archive_handle, key, type);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetArray_GetCount(peak_icv_archive_handle archive_handle, const char* key, size_t* count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetArray_GetCount)
    {
        return inst.m_peak_icv_Archive_GetArray_GetCount(archive_handle, key, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetInt(peak_icv_archive_handle archive_handle, const char* key, int64_t* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetInt)
    {
        return inst.m_peak_icv_Archive_GetInt(archive_handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetInt(peak_icv_archive_handle archive_handle, const char* key, int64_t value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetInt)
    {
        return inst.m_peak_icv_Archive_SetInt(archive_handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetIntArray(peak_icv_archive_handle archive_handle, const char* key, int64_t* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetIntArray)
    {
        return inst.m_peak_icv_Archive_GetIntArray(archive_handle, key, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetIntArray(peak_icv_archive_handle archive_handle, const char* key, const int64_t* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetIntArray)
    {
        return inst.m_peak_icv_Archive_SetIntArray(archive_handle, key, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetDouble(peak_icv_archive_handle archive_handle, const char* key, double* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetDouble)
    {
        return inst.m_peak_icv_Archive_GetDouble(archive_handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetDouble(peak_icv_archive_handle archive_handle, const char* key, double value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetDouble)
    {
        return inst.m_peak_icv_Archive_SetDouble(archive_handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetDoubleArray(peak_icv_archive_handle archive_handle, const char* key, double* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetDoubleArray)
    {
        return inst.m_peak_icv_Archive_GetDoubleArray(archive_handle, key, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetDoubleArray(peak_icv_archive_handle archive_handle, const char* key, const double* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetDoubleArray)
    {
        return inst.m_peak_icv_Archive_SetDoubleArray(archive_handle, key, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetBool(peak_icv_archive_handle archive_handle, const char* key, bool* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetBool)
    {
        return inst.m_peak_icv_Archive_GetBool(archive_handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetBool(peak_icv_archive_handle archive_handle, const char* key, bool value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetBool)
    {
        return inst.m_peak_icv_Archive_SetBool(archive_handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetBoolArray(peak_icv_archive_handle archive_handle, const char* key, bool* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetBoolArray)
    {
        return inst.m_peak_icv_Archive_GetBoolArray(archive_handle, key, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetBoolArray(peak_icv_archive_handle archive_handle, const char* key, const bool* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetBoolArray)
    {
        return inst.m_peak_icv_Archive_SetBoolArray(archive_handle, key, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetString_GetSizeInBytes(peak_icv_archive_handle archive_handle, const char* key, size_t* size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetString_GetSizeInBytes)
    {
        return inst.m_peak_icv_Archive_GetString_GetSizeInBytes(archive_handle, key, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetString(peak_icv_archive_handle archive_handle, const char* key, char* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetString)
    {
        return inst.m_peak_icv_Archive_GetString(archive_handle, key, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetString(peak_icv_archive_handle archive_handle, const char* key, const char* data)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetString)
    {
        return inst.m_peak_icv_Archive_SetString(archive_handle, key, data);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetStringArrayElement_GetSizeInBytes(peak_icv_archive_handle archive_handle, const char* key, size_t index, size_t* size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetStringArrayElement_GetSizeInBytes)
    {
        return inst.m_peak_icv_Archive_GetStringArrayElement_GetSizeInBytes(archive_handle, key, index, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetStringArrayElement(peak_icv_archive_handle archive_handle, const char* key, size_t index, char* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetStringArrayElement)
    {
        return inst.m_peak_icv_Archive_GetStringArrayElement(archive_handle, key, index, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetStringArray(peak_icv_archive_handle archive_handle, const char* key, const char* const* data, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetStringArray)
    {
        return inst.m_peak_icv_Archive_SetStringArray(archive_handle, key, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetArchive(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle* sub_archive)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetArchive)
    {
        return inst.m_peak_icv_Archive_GetArchive(archive_handle, key, sub_archive);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetArchive(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle sub_archive)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetArchive)
    {
        return inst.m_peak_icv_Archive_SetArchive(archive_handle, key, sub_archive);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_GetArchiveArray(peak_icv_archive_handle archive_handle, const char* key, peak_icv_archive_handle* sub_archives, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_GetArchiveArray)
    {
        return inst.m_peak_icv_Archive_GetArchiveArray(archive_handle, key, sub_archives, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_SetArchiveArray(peak_icv_archive_handle archive_handle, const char* key, const peak_icv_archive_handle* sub_archives, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_SetArchiveArray)
    {
        return inst.m_peak_icv_Archive_SetArchiveArray(archive_handle, key, sub_archives, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_ToString_GetSizeInBytes(peak_icv_archive_handle archive_handle, peak_icv_serialization_type type, size_t* size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_ToString_GetSizeInBytes)
    {
        return inst.m_peak_icv_Archive_ToString_GetSizeInBytes(archive_handle, type, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Archive_ToString(peak_icv_archive_handle archive_handle, peak_icv_serialization_type type, char* data, size_t* size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Archive_ToString)
    {
        return inst.m_peak_icv_Archive_ToString(archive_handle, type, data, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Buffer_CutBytes(const uint8_t* data, size_t line_start_offset, size_t bytes_per_line, size_t valid_bytes_per_line, size_t number_of_lines, peak_icv_image_handle output_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Buffer_CutBytes)
    {
        return inst.m_peak_icv_Buffer_CutBytes(data, line_start_offset, bytes_per_line, valid_bytes_per_line, number_of_lines, output_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Create(peak_icv_image_handle* image_handle, enum peak_common_pixel_format pixelformat, peak_common_size size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Create)
    {
        return inst.m_peak_icv_Image_Create(image_handle, pixelformat, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_CreateWithZeroInit(peak_icv_image_handle* image_handle, enum peak_common_pixel_format pixelformat, peak_common_size size, bool zero_init)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_CreateWithZeroInit)
    {
        return inst.m_peak_icv_Image_CreateWithZeroInit(image_handle, pixelformat, size, zero_init);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_CreateFromImageInfo(peak_icv_image_handle* image_handle, peak_icv_image_info image_info, size_t image_info_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_CreateFromImageInfo)
    {
        return inst.m_peak_icv_Image_CreateFromImageInfo(image_handle, image_info, image_info_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_CreateFromFile(peak_icv_image_handle* image_handle, const char* file_path)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_CreateFromFile)
    {
        return inst.m_peak_icv_Image_CreateFromFile(image_handle, file_path);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_CreateFromFileWithPixelFormat(peak_icv_image_handle* image_handle, const char* file_path, enum peak_common_pixel_format forced_pixelformat)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_CreateFromFileWithPixelFormat)
    {
        return inst.m_peak_icv_Image_CreateFromFileWithPixelFormat(image_handle, file_path, forced_pixelformat);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_CreateFromExistingImage(peak_icv_image_handle* image_handle, peak_icv_image_handle source_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_CreateFromExistingImage)
    {
        return inst.m_peak_icv_Image_CreateFromExistingImage(image_handle, source_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_SaveToFile(peak_icv_image_handle image_handle, const char* file_path)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_SaveToFile)
    {
        return inst.m_peak_icv_Image_SaveToFile(image_handle, file_path);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_IncreaseUseCount(peak_icv_image_handle image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_IncreaseUseCount)
    {
        return inst.m_peak_icv_Image_IncreaseUseCount(image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Destroy(peak_icv_image_handle image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Destroy)
    {
        return inst.m_peak_icv_Image_Destroy(image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_ConvertPixelFormat(peak_icv_image_handle input_image_handle, enum peak_common_pixel_format destination_pixelformat, peak_icv_image_handle output_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_ConvertPixelFormat)
    {
        return inst.m_peak_icv_Image_ConvertPixelFormat(input_image_handle, destination_pixelformat, output_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_ConvertPixelFormatWithFactor(peak_icv_image_handle input_image_handle, enum peak_common_pixel_format destination_pixelformat, double factor, peak_icv_image_handle output_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_ConvertPixelFormatWithFactor)
    {
        return inst.m_peak_icv_Image_ConvertPixelFormatWithFactor(input_image_handle, destination_pixelformat, factor, output_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_GetInfo(peak_icv_image_handle image_handle, peak_icv_image_info* image_info, size_t image_info_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_GetInfo)
    {
        return inst.m_peak_icv_Image_GetInfo(image_handle, image_info, image_info_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_GetRegion(peak_icv_image_handle image_handle, peak_icv_region_handle* region_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_GetRegion)
    {
        return inst.m_peak_icv_Image_GetRegion(image_handle, region_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_SetRegion(peak_icv_image_handle image_handle, peak_icv_region_handle region_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_SetRegion)
    {
        return inst.m_peak_icv_Image_SetRegion(image_handle, region_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_ResetRegion(peak_icv_image_handle image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_ResetRegion)
    {
        return inst.m_peak_icv_Image_ResetRegion(image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Compare(peak_icv_image_handle image_handle_lhs, peak_icv_image_handle image_handle_rhs, bool* is_equal)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Compare)
    {
        return inst.m_peak_icv_Image_Compare(image_handle_lhs, image_handle_rhs, is_equal);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_GetCaptureInformation(peak_icv_image_handle image_handle, peak_icv_capture_information* capture_information, size_t capture_information_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_GetCaptureInformation)
    {
        return inst.m_peak_icv_Image_GetCaptureInformation(image_handle, capture_information, capture_information_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_SetCaptureInformation(peak_icv_image_handle image_handle, peak_icv_capture_information capture_information, size_t capture_information_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_SetCaptureInformation)
    {
        return inst.m_peak_icv_Image_SetCaptureInformation(image_handle, capture_information, capture_information_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Subtract(peak_icv_image_handle image_handle_minuend, peak_icv_image_handle image_handle_subtrahend, peak_icv_image_handle image_handle_difference)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Subtract)
    {
        return inst.m_peak_icv_Image_Subtract(image_handle_minuend, image_handle_subtrahend, image_handle_difference);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_TransformToWorkspace(peak_icv_image_handle input_image_handle, peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_image_handle output_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_TransformToWorkspace)
    {
        return inst.m_peak_icv_Image_TransformToWorkspace(input_image_handle, extrinsic_parameters, extrinsic_parameters_size, output_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Crop(peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle, peak_common_rectangle rectangle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Crop)
    {
        return inst.m_peak_icv_Image_Crop(input_image_handle, output_image_handle, rectangle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Scale(peak_icv_image_handle input_image_handle, peak_icv_image_handle output_image_handle, peak_icv_interpolation interpolation)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Scale)
    {
        return inst.m_peak_icv_Image_Scale(input_image_handle, output_image_handle, interpolation);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Deinterleave(peak_icv_image_handle input_image_handle, peak_icv_image_handle* output_image_handles, size_t output_image_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Deinterleave)
    {
        return inst.m_peak_icv_Image_Deinterleave(input_image_handle, output_image_handles, output_image_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Deinterleave_GetOutputPixelFormat(peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Deinterleave_GetOutputPixelFormat)
    {
        return inst.m_peak_icv_Image_Deinterleave_GetOutputPixelFormat(input_pixel_format, output_pixel_format);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Deinterleave_GetOutputImageCount(peak_common_pixel_format input_pixel_format, size_t* output_image_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Deinterleave_GetOutputImageCount)
    {
        return inst.m_peak_icv_Image_Deinterleave_GetOutputImageCount(input_pixel_format, output_image_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_Deinterleave_GetOutputImageSize(peak_common_pixel_format input_pixel_format, peak_common_size input_image_size, peak_common_size* output_image_size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_Deinterleave_GetOutputImageSize)
    {
        return inst.m_peak_icv_Image_Deinterleave_GetOutputImageSize(input_pixel_format, input_image_size, output_image_size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_GetMetadata(peak_icv_image_handle image_handle, peak_icv_metadata_handle* metadata_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_GetMetadata)
    {
        return inst.m_peak_icv_Image_GetMetadata(image_handle, metadata_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Image_SetMetadata(peak_icv_image_handle image_handle, peak_icv_metadata_handle metadata_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Image_SetMetadata)
    {
        return inst.m_peak_icv_Image_SetMetadata(image_handle, metadata_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_Create(peak_icv_metadata_handle* handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_Create)
    {
        return inst.m_peak_icv_Metadata_Create(handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_Destroy(peak_icv_metadata_handle handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_Destroy)
    {
        return inst.m_peak_icv_Metadata_Destroy(handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetInt(peak_icv_metadata_handle handle, const char* key, int64_t* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetInt)
    {
        return inst.m_peak_icv_Metadata_GetInt(handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetInt(peak_icv_metadata_handle handle, const char* key, int64_t value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetInt)
    {
        return inst.m_peak_icv_Metadata_SetInt(handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetIntArray(peak_icv_metadata_handle handle, const char* key, int64_t* values, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetIntArray)
    {
        return inst.m_peak_icv_Metadata_GetIntArray(handle, key, values, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetIntArray(peak_icv_metadata_handle handle, const char* key, const int64_t* values, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetIntArray)
    {
        return inst.m_peak_icv_Metadata_SetIntArray(handle, key, values, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetUInt(peak_icv_metadata_handle handle, const char* key, uint64_t* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetUInt)
    {
        return inst.m_peak_icv_Metadata_GetUInt(handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetUInt(peak_icv_metadata_handle handle, const char* key, uint64_t value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetUInt)
    {
        return inst.m_peak_icv_Metadata_SetUInt(handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetUIntArray(peak_icv_metadata_handle handle, const char* key, uint64_t* values, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetUIntArray)
    {
        return inst.m_peak_icv_Metadata_GetUIntArray(handle, key, values, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetUIntArray(peak_icv_metadata_handle handle, const char* key, const uint64_t* values, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetUIntArray)
    {
        return inst.m_peak_icv_Metadata_SetUIntArray(handle, key, values, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetDouble(peak_icv_metadata_handle handle, const char* key, double* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetDouble)
    {
        return inst.m_peak_icv_Metadata_GetDouble(handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetDouble(peak_icv_metadata_handle handle, const char* key, double value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetDouble)
    {
        return inst.m_peak_icv_Metadata_SetDouble(handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetDoubleArray(peak_icv_metadata_handle handle, const char* key, double* values, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetDoubleArray)
    {
        return inst.m_peak_icv_Metadata_GetDoubleArray(handle, key, values, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetDoubleArray(peak_icv_metadata_handle handle, const char* key, const double* values, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetDoubleArray)
    {
        return inst.m_peak_icv_Metadata_SetDoubleArray(handle, key, values, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetBool(peak_icv_metadata_handle handle, const char* key, bool* value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetBool)
    {
        return inst.m_peak_icv_Metadata_GetBool(handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetBool(peak_icv_metadata_handle handle, const char* key, bool value)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetBool)
    {
        return inst.m_peak_icv_Metadata_SetBool(handle, key, value);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetBoolArray(peak_icv_metadata_handle handle, const char* key, bool* values, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetBoolArray)
    {
        return inst.m_peak_icv_Metadata_GetBoolArray(handle, key, values, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetBoolArray(peak_icv_metadata_handle handle, const char* key, const bool* values, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetBoolArray)
    {
        return inst.m_peak_icv_Metadata_SetBoolArray(handle, key, values, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetString_GetSizeInBytes(peak_icv_metadata_handle handle, const char* key, size_t* size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetString_GetSizeInBytes)
    {
        return inst.m_peak_icv_Metadata_GetString_GetSizeInBytes(handle, key, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetString(peak_icv_metadata_handle handle, const char* key, char* buffer, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetString)
    {
        return inst.m_peak_icv_Metadata_GetString(handle, key, buffer, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetString(peak_icv_metadata_handle handle, const char* key, const char* buffer)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetString)
    {
        return inst.m_peak_icv_Metadata_SetString(handle, key, buffer);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes(peak_icv_metadata_handle handle, const char* key, size_t index, size_t* size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes)
    {
        return inst.m_peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes(handle, key, index, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetStringArrayElement(peak_icv_metadata_handle handle, const char* key, size_t index, char* buffer, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetStringArrayElement)
    {
        return inst.m_peak_icv_Metadata_GetStringArrayElement(handle, key, index, buffer, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_SetStringArray(peak_icv_metadata_handle handle, const char* key, const char* const* buffers, size_t count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_SetStringArray)
    {
        return inst.m_peak_icv_Metadata_SetStringArray(handle, key, buffers, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetArray_GetCount(peak_icv_metadata_handle handle, const char* key, size_t* count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetArray_GetCount)
    {
        return inst.m_peak_icv_Metadata_GetArray_GetCount(handle, key, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_HasKey(peak_icv_metadata_handle handle, const char* key, bool* has_key)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_HasKey)
    {
        return inst.m_peak_icv_Metadata_HasKey(handle, key, has_key);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetEntryCount(peak_icv_metadata_handle handle, size_t* count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetEntryCount)
    {
        return inst.m_peak_icv_Metadata_GetEntryCount(handle, count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetKey_GetSizeInBytes(peak_icv_metadata_handle handle, size_t index, size_t* size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetKey_GetSizeInBytes)
    {
        return inst.m_peak_icv_Metadata_GetKey_GetSizeInBytes(handle, index, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetKey(peak_icv_metadata_handle handle, size_t index, char* buffer, size_t size)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetKey)
    {
        return inst.m_peak_icv_Metadata_GetKey(handle, index, buffer, size);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Metadata_GetValueType(peak_icv_metadata_handle handle, const char* key, peak_icv_metadata_value_type_t* type)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Metadata_GetValueType)
    {
        return inst.m_peak_icv_Metadata_GetValueType(handle, key, type);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_Create(peak_icv_point_cloud_handle* point_cloud_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_Create)
    {
        return inst.m_peak_icv_PointCloud_Create(point_cloud_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_CreateFromXYZImage(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_CreateFromXYZImage)
    {
        return inst.m_peak_icv_PointCloud_CreateFromXYZImage(point_cloud_handle, xyz_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle, peak_icv_image_handle overlay_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage)
    {
        return inst.m_peak_icv_PointCloud_CreateFromXYZImageAndOverlayImage(point_cloud_handle, xyz_image_handle, overlay_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_image_handle xyz_image_handle, peak_icv_image_handle intensity_image_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage)
    {
        return inst.m_peak_icv_PointCloud_CreateFromXYZImageAndIntensityImage(point_cloud_handle, xyz_image_handle, intensity_image_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_CreateFromFile(peak_icv_point_cloud_handle* point_cloud_handle, enum peak_icv_point_type point_type, const char* file_path)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_CreateFromFile)
    {
        return inst.m_peak_icv_PointCloud_CreateFromFile(point_cloud_handle, point_type, file_path);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_CreateFromPoints(peak_icv_point_cloud_handle* point_cloud_handle, peak_icv_point_xyz_variant points, size_t num_points, enum peak_icv_point_type point_type)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_CreateFromPoints)
    {
        return inst.m_peak_icv_PointCloud_CreateFromPoints(point_cloud_handle, points, num_points, point_type);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_IncreaseUseCount(peak_icv_point_cloud_handle point_cloud_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_IncreaseUseCount)
    {
        return inst.m_peak_icv_PointCloud_IncreaseUseCount(point_cloud_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_Destroy(peak_icv_point_cloud_handle point_cloud_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_Destroy)
    {
        return inst.m_peak_icv_PointCloud_Destroy(point_cloud_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_GetType(peak_icv_point_cloud_handle point_cloud_handle, enum peak_icv_point_type* point_type)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_GetType)
    {
        return inst.m_peak_icv_PointCloud_GetType(point_cloud_handle, point_type);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_GetPoints_GetCount(peak_icv_point_cloud_handle point_cloud_handle, size_t* num_points)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_GetPoints_GetCount)
    {
        return inst.m_peak_icv_PointCloud_GetPoints_GetCount(point_cloud_handle, num_points);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_GetPoints_GetSizeInBytes(peak_icv_point_cloud_handle point_cloud_handle, size_t* byte_size_points)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_GetPoints_GetSizeInBytes)
    {
        return inst.m_peak_icv_PointCloud_GetPoints_GetSizeInBytes(point_cloud_handle, byte_size_points);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_GetPoints(peak_icv_point_cloud_handle point_cloud_handle, peak_icv_point_xyz_variant points, size_t byte_size_points)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_GetPoints)
    {
        return inst.m_peak_icv_PointCloud_GetPoints(point_cloud_handle, points, byte_size_points);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_SaveToFile(peak_icv_point_cloud_handle point_cloud_handle, const char* file_path, peak_icv_point_cloud_save_options save_options)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_SaveToFile)
    {
        return inst.m_peak_icv_PointCloud_SaveToFile(point_cloud_handle, file_path, save_options);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_Transform(peak_icv_point_cloud_handle input_point_cloud, peak_icv_transformation_matrix_3d matrix_3d, peak_icv_point_cloud_handle* output_point_cloud)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_Transform)
    {
        return inst.m_peak_icv_PointCloud_Transform(input_point_cloud, matrix_3d, output_point_cloud);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_PointCloud_TransformToWorkspace(peak_icv_point_cloud_handle input_point_cloud, peak_icv_extrinsic_parameters extrinsic_parameters, size_t extrinsic_parameters_size, peak_icv_point_cloud_handle* output_point_cloud)
{
    auto& inst = instance();
    if(inst.m_peak_icv_PointCloud_TransformToWorkspace)
    {
        return inst.m_peak_icv_PointCloud_TransformToWorkspace(input_point_cloud, extrinsic_parameters, extrinsic_parameters_size, output_point_cloud);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_Create(peak_icv_polygon_handle* polygon_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_Create)
    {
        return inst.m_peak_icv_Polygon_Create(polygon_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_CreateFromPoints(peak_icv_polygon_handle* polygon_handle, peak_icv_point_type_variant points, size_t num_points, enum peak_icv_point_type point_type)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_CreateFromPoints)
    {
        return inst.m_peak_icv_Polygon_CreateFromPoints(polygon_handle, points, num_points, point_type);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_Destroy(peak_icv_polygon_handle polygon_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_Destroy)
    {
        return inst.m_peak_icv_Polygon_Destroy(polygon_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_IncreaseUseCount(peak_icv_polygon_handle polygon_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_IncreaseUseCount)
    {
        return inst.m_peak_icv_Polygon_IncreaseUseCount(polygon_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_GetPoints_GetCount(peak_icv_polygon_handle polygon_handle, size_t* points_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_GetPoints_GetCount)
    {
        return inst.m_peak_icv_Polygon_GetPoints_GetCount(polygon_handle, points_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_GetPointType(peak_icv_polygon_handle polygon_handle, enum peak_icv_point_type* point_type)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_GetPointType)
    {
        return inst.m_peak_icv_Polygon_GetPointType(polygon_handle, point_type);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_IsClosed(peak_icv_polygon_handle polygon_handle, bool* is_closed)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_IsClosed)
    {
        return inst.m_peak_icv_Polygon_IsClosed(polygon_handle, is_closed);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_GetPoints_GetSizeInBytes(peak_icv_polygon_handle polygon_handle, size_t* byte_size_points)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_GetPoints_GetSizeInBytes)
    {
        return inst.m_peak_icv_Polygon_GetPoints_GetSizeInBytes(polygon_handle, byte_size_points);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Polygon_GetPoints(peak_icv_polygon_handle polygon_handle, peak_icv_point_type_variant points, size_t byte_size_points)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Polygon_GetPoints)
    {
        return inst.m_peak_icv_Polygon_GetPoints(polygon_handle, points, byte_size_points);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Create(peak_icv_region_handle* region_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Create)
    {
        return inst.m_peak_icv_Region_Create(region_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_CreateFromPoints(peak_icv_region_handle* region_handle, peak_common_point* points, size_t num_points)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_CreateFromPoints)
    {
        return inst.m_peak_icv_Region_CreateFromPoints(region_handle, points, num_points);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_CreateFromRectangle(peak_icv_region_handle* region_handle, peak_common_rectangle rect)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_CreateFromRectangle)
    {
        return inst.m_peak_icv_Region_CreateFromRectangle(region_handle, rect);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_IncreaseUseCount(peak_icv_region_handle region_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_IncreaseUseCount)
    {
        return inst.m_peak_icv_Region_IncreaseUseCount(region_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Destroy(peak_icv_region_handle region_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Destroy)
    {
        return inst.m_peak_icv_Region_Destroy(region_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Array_Create(peak_icv_region_handle* region_handles, size_t num_region_handles)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Array_Create)
    {
        return inst.m_peak_icv_Region_Array_Create(region_handles, num_region_handles);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Array_Destroy(peak_icv_region_handle* region_handles, size_t num_region_handles)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Array_Destroy)
    {
        return inst.m_peak_icv_Region_Array_Destroy(region_handles, num_region_handles);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_GetConnectedComponents_GetCount(peak_icv_region_handle input_region, size_t* output_regions_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_GetConnectedComponents_GetCount)
    {
        return inst.m_peak_icv_Region_GetConnectedComponents_GetCount(input_region, output_regions_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_GetConnectedComponents(peak_icv_region_handle input_region, peak_icv_region_handle* output_regions, size_t region_handles_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_GetConnectedComponents)
    {
        return inst.m_peak_icv_Region_GetConnectedComponents(input_region, output_regions, region_handles_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_GetArea(peak_icv_region_handle input_region, size_t* area)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_GetArea)
    {
        return inst.m_peak_icv_Region_GetArea(input_region, area);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_GetCenterOfGravity(peak_icv_region_handle input_region, peak_common_point_f* center_of_gravity)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_GetCenterOfGravity)
    {
        return inst.m_peak_icv_Region_GetCenterOfGravity(input_region, center_of_gravity);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_GetPoints_GetCount(peak_icv_region_handle input_region, size_t* points_count)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_GetPoints_GetCount)
    {
        return inst.m_peak_icv_Region_GetPoints_GetCount(input_region, points_count);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_GetPoints(peak_icv_region_handle input_region, peak_common_point* points, size_t num_points)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_GetPoints)
    {
        return inst.m_peak_icv_Region_GetPoints(input_region, points, num_points);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Difference(peak_icv_region_handle input_region_minuend, peak_icv_region_handle input_region_subtrahend, peak_icv_region_handle* output_region_difference)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Difference)
    {
        return inst.m_peak_icv_Region_Difference(input_region_minuend, input_region_subtrahend, output_region_difference);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Intersection(peak_icv_region_handle input_region_1, peak_icv_region_handle input_region_2, peak_icv_region_handle* output_region_intersection)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Intersection)
    {
        return inst.m_peak_icv_Region_Intersection(input_region_1, input_region_2, output_region_intersection);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Union(peak_icv_region_handle input_region_1, peak_icv_region_handle input_region_2, peak_icv_region_handle* output_region_united)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Union)
    {
        return inst.m_peak_icv_Region_Union(input_region_1, input_region_2, output_region_united);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Dilation(peak_icv_region_handle input_region, peak_icv_region_handle input_structuring_element, peak_icv_region_handle* output_region_dilation)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Dilation)
    {
        return inst.m_peak_icv_Region_Dilation(input_region, input_structuring_element, output_region_dilation);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Erosion(peak_icv_region_handle input_region, peak_icv_region_handle input_structuring_element, peak_icv_region_handle* output_region_erosion)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Erosion)
    {
        return inst.m_peak_icv_Region_Erosion(input_region, input_structuring_element, output_region_erosion);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Compare(peak_icv_region_handle region_handle_lhs, peak_icv_region_handle region_handle_rhs, bool* is_equal)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Compare)
    {
        return inst.m_peak_icv_Region_Compare(region_handle_lhs, region_handle_rhs, is_equal);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

inline PEAK_ICV_API_STATUS DynamicLoader::peak_icv_Region_Scale(peak_icv_region_handle input_region_handle, peak_common_size input_size, peak_common_size output_size, peak_icv_interpolation interpolation, peak_icv_region_handle* output_region_handle)
{
    auto& inst = instance();
    if(inst.m_peak_icv_Region_Scale)
    {
        return inst.m_peak_icv_Region_Scale(input_region_handle, input_size, output_size, interpolation, output_region_handle);
    }
    else
    {
        throw std::runtime_error("Library not loaded!");
    }
}

} /* namespace dynamic */
} /* namespace icv */
} /* namespace peak */
PEAK_COMMON_END_DISABLE_DEPRECATED_WARNINGS
