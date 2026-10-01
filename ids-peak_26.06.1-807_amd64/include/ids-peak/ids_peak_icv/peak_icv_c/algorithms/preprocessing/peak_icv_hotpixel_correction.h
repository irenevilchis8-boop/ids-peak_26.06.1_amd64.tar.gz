/*!
 * \file    peak_icv_hotpixel_correction.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_image.h>

#ifdef __cplusplus
#    include <cstdint>
extern "C" {
#else
#    include <stdbool.h>
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \defgroup ids_peak_icv_c_preprocessing_hotpixel HotpixelCorrection
 * \ingroup ids_peak_icv_c_preprocessing
 *
 * \brief HotpixelCorrection is responsible for identifying defective pixels that consistently report
 *        higher-than-expected intensity values.
 *
 * Hot pixels can be detected using \ref peak_icv_Preprocessing_HotpixelCorrection_Detect. The detection can be fine-tuned
 * by setting the sensitivity. Alternatively, a hot pixel list, can be set manually by calling
 * \ref peak_icv_Preprocessing_HotpixelCorrection_SetList.
 * The hot pixels are corrected when calling the \ref peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace method.
 *
 * \since ids_peak_icv 1.0
 */
struct peak_icv_hotpixel_correction;
typedef struct peak_icv_hotpixel_correction* peak_icv_hotpixel_correction_handle;

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Creates a hot pixel correction object.
 *
 * \param[out] hotpixel_correction_handle  Handle for the hot pixel correction object.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_Create(
    peak_icv_hotpixel_correction_handle* hotpixel_correction_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Destroys a hot pixel correction handle.
 *
 * \destroyHandle{hot pixel correction}
 *
 * \param[in] hotpixel_correction_handle  Hot pixel correction handle to destroy.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p hotpixel_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_Destroy(
    peak_icv_hotpixel_correction_handle hotpixel_correction_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 * \brief Increases the use count of the specified hotpixel_correction_handle. In order to decrease it, you need to call
 * \ref peak_icv_Preprocessing_HotpixelCorrection_Destroy. If you copy the hotpixel correction handle, you should call
 * this method, because otherwise, when one handle will be destroyed, the other will be invalid.
 *
 * \param[in] hotpixel_correction_handle Hotpixel correction handle (which was copied).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount(
    peak_icv_hotpixel_correction_handle hotpixel_correction_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Performs immediate hot pixel detection on the given image.
 *
 * This method analyzes the provided image and detects hot pixels based on the current sensitivity setting.
 * The results are stored internally and can be accessed using \ref peak_icv_Preprocessing_HotpixelCorrection_GetList.
 *
 * \note This operation disregards any specified image regions. It processes the entire image.
 *
 * \param[in]  hotpixel_correction_handle  Handle to the hot pixel correction.
 * \param[in]  input_image_handle          The handle to the image to be processed.
 * \param[in]  sensitivity                 Sensitivity for hot pixel detection. A higher sensitivity
 *                                         may result in detecting more hot pixels, including possible
 *                                         false positives.
 * \param[in]  gainFactor                  Gain factor applied to the image. Used to account for
 *                                         increased noise levels when detecting hot pixels.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           One or more handles (\p input_image_handle, \p hotpixel_correction_handle) were not created.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_Detect(peak_icv_hotpixel_correction_handle hotpixel_correction_handle,
    peak_icv_image_handle input_image_handle, uint32_t sensitivity, float gainFactor);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Processes the \p input_image_handle in-place based on current settings.
 *
 * \note This operation disregards any specified image regions. It processes the entire image.
 *
 * \param[in]  hotpixel_correction_handle  Handle to the hot pixel correction.
 * \param[in]  input_image_handle          The handle to the image to be processed.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           One or more handles (\p input_image_handle, \p hotpixel_correction_handle) were not created.
 * \return #PEAK_ICV_STATUS_MISMATCH                 The output image size or pixel format does not match.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace(
    peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_icv_image_handle input_image_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Sets the internal hot pixel list to \p list.
 *
 * \param[in]  hotpixel_correction_handle  Handle to the hot pixel correction.
 * \param[in]  list                        The list of hot pixel coordinates "points" to set.
 * \param[in]  count                       The list size.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p hotpixel_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p list is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_SetList(
    peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_point* list, size_t count);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Resets the internal hot pixel list to an empty list.
 *
 * \param[in]  hotpixel_correction_handle  Handle to the hot pixel correction.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p hotpixel_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_ResetList(
    peak_icv_hotpixel_correction_handle hotpixel_correction_handle);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Returns the number of hot pixels currently stored in the module.
 *
 * This function retrieves the number of hot pixels available in the current list.
 * Use this value to allocate an appropriately sized buffer before calling
 * \ref peak_icv_Preprocessing_HotpixelCorrection_GetList.
 *
 * \param[in]  hotpixel_correction_handle  Handle to the hot pixel correction.
 * \param[out] count                       Pointer to a size_t variable that will receive the number of hot pixels.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p hotpixel_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p count is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount(
    peak_icv_hotpixel_correction_handle hotpixel_correction_handle, size_t* count);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Returns the current list of hot pixels into a user-provided buffer.
 *
 * This function retrieves the list of detected or manually set hot pixels and stores them
 * in the provided buffer. The number of elements to retrieve must first be obtained by calling
 * \ref peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount.
 *
 * \param[in]  hotpixel_correction_handle  Handle to the hot pixel correction.
 * \param[out] list                        Pointer to a buffer of point_type elements that will be filled with hot pixel coordinates.
 * \param[in]  count                       The size of the provided buffer (number of point_type elements).
 *
 * \return #PEAK_ICV_STATUS_SUCCESS             Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED     The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE      The \p hotpixel_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER        The \p list is not a valid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE The provided buffer is too small to hold the hot pixel list.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR               An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_GetList(
    peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_point* list, size_t count);

/*!
 * \ingroup ids_peak_icv_c_preprocessing_hotpixel
 *
 * \brief Returns the valid range of sensitivities.
 *
 * Provides the minimum and maximum values that are accepted by the \ref peak_icv_Preprocessing_HotpixelCorrection_Detect function.
 *
 * \param[in]  hotpixel_correction_handle  Handle to the hot pixel correction.
 * \param[out] range                       The interval containing the minimum and maximum valid sensitivity values.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                  Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED  The library is not initialized.
 * \return #PEAK_ICV_STATUS_INVALID_HANDLE           The \p hotpixel_correction_handle must be valid and created first.
 * \return #PEAK_ICV_STATUS_NULL_POINTER             The \p range is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR           An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange(
    peak_icv_hotpixel_correction_handle hotpixel_correction_handle, peak_common_interval_u* range);


#ifdef __cplusplus
} // extern "C"

#endif // __cplusplus
