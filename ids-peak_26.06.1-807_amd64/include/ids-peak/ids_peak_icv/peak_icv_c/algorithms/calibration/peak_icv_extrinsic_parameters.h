/*!
 * \file    peak_icv_extrinsic_parameters.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-28
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/backend/peak_icv_defines.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif


/*!
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Represents the extrinsic camera parameters
 *        that define the camera's position and orientation relative to the world coordinate system.
 */
typedef struct peak_icv_extrinsic_parameters
{
    peak_icv_point_xyz rotation;    //!< Rotation parameters using rodrigues formula.
    peak_icv_point_xyz translation; //!< Translation parameters in 3D space.
} peak_icv_extrinsic_parameters;

/*!
 * \ingroup ids_peak_icv_c_calibration
 *
 * \brief Provides the transformation matrix calculated based on the given extrinsic parameters.
 *
 * \param[in]  extrinsic_parameters      Extrinsic parameters.
 * \param[in]  extrinsic_parameters_size Size of the extrinsic parameters.
 * \param[out] transformation_matrix     Transformation matrix.
 *
 * \return #PEAK_ICV_STATUS_SUCCESS                 Operation was successful; no error occurred.
 * \return #PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED The library is not initialized.
 * \return #PEAK_ICV_STATUS_NULL_POINTER            The \p transformation_matrix_3d is an invalid pointer.
 * \return #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE     The size of the extrinsic parameters is invalid.
 * \return #PEAK_ICV_STATUS_INTERNAL_ERROR          An unexpected internal error occurred.
 *
 * \since ids_peak_icv 1.0
 */
PEAK_ICV_API_STATUS peak_icv_Calibration_Extrinsic_CalculateTransformationMatrix(peak_icv_extrinsic_parameters extrinsic_parameters,
    size_t extrinsic_parameters_size, peak_icv_transformation_matrix_3d* transformation_matrix);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
