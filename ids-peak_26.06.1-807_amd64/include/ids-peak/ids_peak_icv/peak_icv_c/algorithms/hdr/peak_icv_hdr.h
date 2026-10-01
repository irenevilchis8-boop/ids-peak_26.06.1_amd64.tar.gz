/*!
 * \file    peak_icv_hdr.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-01-20
 * \since   1.2
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/algorithms/hdr/peak_icv_response_curve.h>
#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>

#ifdef __cplusplus

#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \since ids_peak_icv 1.2
 * \ingroup ids_peak_icv_c_hdr
 */
struct peak_icv_hdr;

/*!
 * \since ids_peak_icv 1.2
 * \ingroup ids_peak_icv_c_hdr
 */
typedef struct peak_icv_hdr* peak_icv_hdr_handle;

/*!
 * \since ids_peak_icv 1.2
 * \ingroup ids_peak_icv_c_hdr
 */
typedef enum peak_icv_hdr_algorithm
{
    //! The debevec algorithm is used to calculate an hdr image
    PEAK_ICV_DEBEVEC = 0
} peak_icv_hdr_algorithm;

/*!
 * \brief Creates an HDR processing object.
 *
 * Creates and initializes an HDR object using the Debevec HDR reconstruction
 * algorithm. This algorithm is the default and currently the only HDR
 * algorithm supported by the library. Support for additional HDR algorithms
 * may be added in future releases.
 *
 * \param[out] hdr_handle      The created hdr object handle.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_Create(peak_icv_hdr_handle* hdr_handle);

/*!
 * \brief Estimates the camera response curve (CRC) for an HDR object from a set of input images.
 *
 * This function calculates the specific response characteristics of the camera sensor
 * for the HDR object referenced by the given handle. The CRC defines the relationship
 * between scene radiance and measured pixel values.
 *
 * Performing this estimation step explicitly based on the provided input images
 * (which are expected to represent the same scene captured with either different exposure
 * times or different gains) can significantly reduce the processing time of subsequent calls to
 * \ref peak_icv_HDR_Process, as the curve does not need to be re-calculated.
 *
 * If this step is omitted, the response curve is estimated automatically during
 * the first processing step, which results in increased HDR processing time.
 *
 * \supportedPixelformats{HDR}
 *
 * \param[in] hdr_handle
 *      Handle to a previously created HDR object.
 * \param[in] input_images
 *      Pointer to an array of image handles used for response curve estimation.
 *      The images should contain either varying exposure times or varying gains.
 *      Simultaneous variation of both is not supported.
 * \param[in] num_input_images
 *      Number of images provided in the \p input_images array.
 *      Must be greater than zero.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 *      Response curve estimation completed successfully.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 *      The library has not been initialized prior to this call.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *      An unexpected internal error occurred during estimation.
 *
 * \since ids_peak_icv 1.3
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_EstimateResponseCurve(
    peak_icv_hdr_handle hdr_handle, peak_icv_image_handle* input_images, size_t num_input_images);

/*!
 * \brief Determines the output pixel format for HDR processing.
 *
 * Queries the HDR object to determine the pixel format of the resulting HDR
 * image when processing an input image with the specified pixel format.
 *
 * This function can be used to allocate or validate the output image prior to
 * calling \ref peak_icv_HDR_Process.
 *
 * \param[in] hdr_handle
 *      Handle to a previously created HDR object.
 * \param[in] input_pixel_format
 *      Pixel format of the input images used for HDR processing.
 * \param[out] output_pixel_format
 *      Pointer that receives the pixel format of the resulting HDR image.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 *      The output pixel format was successfully determined.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 *      The library has not been initialized prior to this call.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *      An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_Process_GetOutputPixelFormat(
    peak_icv_hdr_handle hdr_handle, peak_common_pixel_format input_pixel_format, peak_common_pixel_format* output_pixel_format);

/*!
 * \brief Processes input images to generate an HDR result.
 *
 * Processes a set of input images using the HDR object referenced by the given
 * handle. The HDR reconstruction is performed using the algorithm associated
 * with the HDR object (currently the Debevec algorithm).
 *
 * If a pixel is under- or overexposed across all input images
 * this pixel is clamped to the HDR image's global minimum or maximum values, respectively.
 * All clamped pixels are excluded from the image region.
 *
 * The input images are expected to represent the same scene captured with
 * different exposure settings. All images must be valid and compatible with
 * the HDR object configuration. They must vary exactly one parameter: either
 * exposure time or gain, and this parameter must match the one used during
 * calibration if \ref peak_icv_HDR_EstimateResponseCurve was called. They
 * must contain the corresponding capture information (\ref peak_icv_capture_information).
 *
 * If the HDR object has not been calibrated explicitly using
 * \ref peak_icv_HDR_EstimateResponseCurve, an internal calibration step is performed
 * automatically during processing. This implicit calibration estimates the
 * camera response characteristics and will increase the overall processing
 * time.
 *
 * The resulting HDR image is stored internally in the HDR object and can be
 * retrieved using the appropriate HDR result access functions.
 *
 * \supportedPixelformats{HDR}
 *
 * \param[in] hdr_handle
 *      Handle to a previously created HDR object.
 * \param[in] input_images
 *      Pointer to an array of image handles used as input for HDR processing.
 * \param[in] num_input_images
 *      Number of images provided in the \p input_images array.
 *      Must be greater than zero.
 * \param[out] output_image
 *      Image handle used to store the result of HDR processing.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 *      HDR processing completed successfully.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 *      The library has not been initialized prior to this call.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *      An unexpected internal error occurred during HDR processing.
 *
 * \since ids_peak_icv 1.2
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_Process(
    peak_icv_hdr_handle hdr_handle, peak_icv_image_handle* input_images, size_t num_input_images, peak_icv_image_handle output_image);

/*!
 * \brief Retrieves the HDR algorithm used by an HDR object.
 *
 * Returns the HDR reconstruction algorithm associated with the specified HDR
 * object. The algorithm is defined at creation time and determines how input
 * images are combined during HDR processing.
 *
 * \param[in] hdr_handle
 *      Handle to a previously created HDR object.
 * \param[out] algorithm
 *      Pointer that receives the HDR algorithm identifier currently used by
 *      the HDR object.
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 *      The HDR algorithm was successfully retrieved.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 *      The library has not been initialized prior to this call.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *      An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_GetAlgorithm(peak_icv_hdr_handle hdr_handle, peak_icv_hdr_algorithm* algorithm);

/*!
 * \brief Destroys an HDR handle.
 *
 * \destroyHandle{HDR}
 *
 * \param[in] hdr_handle
 *     HDR handle to destroy
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 *     Operation was successful; no error occurred.
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 *     The library is not initialized.
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 *     The \p hdr_handle does not exist, it must be created first.
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *     An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.2
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_Destroy(peak_icv_hdr_handle hdr_handle);

/*!
 * \param[out] response_curve_handle
 *     Must be previously initialized (e.g., from peak_icv_HDR_ResponseCurve_Create()).
 *
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 * \retval #PEAK_ICV_STATUS_NOT_POSSIBLE
 *     No response curve is currently set.
 *     Use peak_icv_HDR_SetResponseCurve()
 *     or peak_icv_HDR_EstimateResponseCurve()
 *     to set a response curve first.
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_GetResponseCurve(
    peak_icv_hdr_handle hdr_handle, peak_icv_hdr_response_curve_handle* response_curve_handle);

/*!
 * \retval #PEAK_ICV_STATUS_SUCCESS
 * \retval #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED
 * \retval #PEAK_ICV_STATUS_INVALID_HANDLE
 * \retval #PEAK_ICV_STATUS_INTERNAL_ERROR
 *
 * \since ids_peak_icv 1.4
 * \ingroup ids_peak_icv_c_hdr
 */
PEAK_ICV_API_STATUS peak_icv_HDR_SetResponseCurve(
    peak_icv_hdr_handle hdr_handle, peak_icv_hdr_response_curve_handle response_curve_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
