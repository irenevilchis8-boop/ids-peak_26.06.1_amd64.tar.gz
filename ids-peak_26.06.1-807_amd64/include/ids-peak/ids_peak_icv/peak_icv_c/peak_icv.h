/*!
 * \file    peak_icv.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-04-04
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

/*! \defgroup ids_peak_icv_c C
\ingroup ids_peak_icv_library

# Prerequisites

The library requires the use of C99 for the client application.

You also need to have the \htmlonly IDS peak IPL \endhtmlonly libraries and their headers.

# How to use

In order to use \htmlonly IDS peak ICV \endhtmlonly you need to include the interface header file
`peak_icv_c/peak_icv.h`
and link your application with the `ids_peak_icv` and the `ids_peak_ipl` library.

In order to run an application, the shared libraries must be found by the system.\n

- _Windows_: copy the deployed shared libraries (dll) into the folder with the applications executable.\n
- _Linux_: add the path to the deployed shared libraries (so) to `LD_LIBRARY_PATH`.

# Terms {#terms}

This section defines several terms that are used throughout the \htmlonly IDS peak ICV \endhtmlonly library.

## Library {#term_library}

The term library is used to refer to the \htmlonly IDS peak ICV \endhtmlonly library and its implementation.


# Core Principles {#principles}

This section describes some basic principles and programming paradigms of the library.

The application programmer can rely on the library following these principles' throughout the whole interface.

## Strong Exception Safety {#principle_strong_exception_safety}

Wherever possible the library guarantees strong exception safety.

Strong exception safety is also known as commit or rollback semantics. \n
The point of strong exception safety is that a failed operation has no side effects. This means that the system
status after a failed function is the same as it was before the function call.

Please note that may not be possible to achieve this goal for every specific situation.

##Function Return Values {#principle_function_return_values}

In principle, all functions of the library return a status code of type \ref peak_icv_status.

If a function succeeds, it will return \ref PEAK_ICV_STATUS_SUCCESS.
If a function fails, it will return an error code.

It is strongly recommended checking the return value of every library function call for an error indication.

If a function returns an error code, i.e. \ref PEAK_ICV_STATUS_INTERNAL_ERROR, the details on
the error can be queried via \ref peak_icv_GetLastErrorMessage. See also \ref principle_last_error_handling.

## Last Error Handling {#principle_last_error_handling}

The library stores the last error separately for each application thread.

A descriptive message on the last error that occurred in the current thread context can be queried via
\ref peak_icv_GetLastErrorMessage. This message describes the error and its cause in as much detail as possible.

The last error is not cleared after \ref peak_icv_GetLastErrorMessage has been called. \n
It is therefore strongly advised to evaluate the last error only in the immediate context of a failed
library function call, i.e. a library function indicating an error by a \ref peak_icv_status error code.

A code example on how to query the last error is given in the section \ref principle_two_stage_query.

\note In case \ref peak_icv_GetLastErrorMessage itself fails it will return the appropriate error code, but it
      will not store the error internally, so that succeeding calls to \ref peak_icv_GetLastErrorMessage will still be
      able to report the original error.

## Two Staged Data Query {#principle_two_stage_query}

Several library functions provide data of dynamic size in a memory buffer that is to be provided by the application.
As the size of the data depends on the required memory buffer, the size can not be known a priori.

To access such data, the application should implement the following procedure:
- Stage One: Query the required size of the memory buffer by calling the "sibling" function with the additional name
  suffix "_GetCount"
- Stage Two: Receive the data by calling the function with a buffer that was allocated to the size that
  Stage one returned.

The following code demonstrates this procedure by the example of \ref peak_icv_GetLastErrorMessage.
~~~{.c}
peak_icv_status errCode = PEAK_ICV_STATUS_SUCCESS;
char* errMsg = NULL;
size_t errMsgSize = 0;

// For Stage One, i.e. the size query, we call the "_GetCount" sibling function of peak_icv_GetLastErrorMsg.
peak_icv_status status = peak_icv_GetLastErrorMsg_GetCount(&errMsgSize);
if (status == PEAK_ICV_STATUS_SUCCESS)
{
    // The size of the last error message was successfully stored in errMsgSize.
    // This is the size of memory we have to allocate to receive the message.
    errMsg = (char*)malloc(errMsgSize);
    memset(errMsg, 0, errMsgSize);

    // For Stage Two, i.e. the data query, we pass the allocated memory as the buffer parameter.
    status = peak_icv_GetLastErrorMsg(errMsg, &errMsgSize);
    if (status == PEAK_ICV_STATUS_SUCCESS)
    {
        // The last error message was successfully stored in errMsg.
    }
}
~~~

\note The size may change in the time between Stage One and Stage Two, if a call to
      a function is executed in this time, for example in a different thread. \n
      If this happens, the function will return with #PEAK_ICV_STATUS_INVALID_BUFFER_SIZE.

\since 1.0
*/

/*! \defgroup ids_peak_icv_c_library Library
 *  \ingroup ids_peak_icv_c
 *
 * General utility functions for managing the library runtime.
 *
 * Provides functions
 * that control the behavior of the library at a global level.
 * These functions do not perform image processing operations directly,
 * but instead handle tasks such as initialization and error handling.
 */

/*! \defgroup ids_peak_icv_c_algorithms Algorithms
 *  \ingroup ids_peak_icv_c
 *
 * Algorithms.
 */

/*! \defgroup ids_peak_icv_c_threshold Threshold
 *  \ingroup ids_peak_icv_c_algorithms
 *
 * Thresholds.
 */

/*! \defgroup ids_peak_icv_c_calibration Calibration
 *  \ingroup ids_peak_icv_c_algorithms
 *
 * Calibration.
 */

/*!
 * \defgroup ids_peak_icv_c_hdr HDR
 * \ingroup ids_peak_icv_c_experimental
 * \brief High Dynamic Range (HDR) processing.
 */

/*!
 * \defgroup ids_peak_icv_c_tone_mapping Tone mapping
 * \ingroup ids_peak_icv_c_hdr
 * \brief Maps High Dynamic Range (HDR) images to displayable Low Dynamic Range (LDR) formats.
 */

/*! \defgroup ids_peak_icv_c_preprocessing Preprocessing
 *  \ingroup ids_peak_icv_c_algorithms
 *
 * Functions for preparing images before core processing.
 */

/*! \defgroup ids_peak_icv_c_calibration_result Calibration Result
 *  \ingroup ids_peak_icv_c_calibration
 *
 * Calibration Result.
 */

/*! \defgroup ids_peak_icv_c_calibration_view Calibration View
 *  \ingroup ids_peak_icv_c_calibration
 *
 * Calibration View.
 */

/*! \defgroup ids_peak_icv_c_calibration_plate Calibration Plate
 *  \ingroup ids_peak_icv_c_calibration
 *
 * Calibration Plate.
 */

/*! \defgroup ids_peak_icv_c_transformations Transformations
 *  \ingroup ids_peak_icv_c_algorithms
 *
 * \brief A collection of functions that implement
 *        geometric transformations for image processing.
 */

/*! \defgroup ids_peak_icv_c_code_reader Code Reader
 *  \ingroup ids_peak_icv_c_algorithms
 *
 * \brief A collection of functions that implement
 *        code detection and decoding.
 */

/*! \defgroup ids_peak_icv_c_painting Painting
 *  \ingroup ids_peak_icv_c
 *
 * Functions for painting on an image.
 */

/*! \defgroup ids_peak_icv_c_filter Filter
 *  \ingroup ids_peak_icv_c
 *
 * Functions for image filters.
 */

/*! \defgroup ids_peak_icv_c_status Status types and values
 *  \ingroup ids_peak_icv_c
 *
 * Definitions on status types and values.
 */

/*! \defgroup ids_peak_icv_c_types Types
 *  \ingroup ids_peak_icv_c
 *
 * Types.
 */

/*! \defgroup ids_peak_icv_c_image Image
 *  \ingroup ids_peak_icv_c_types
 * Image level functions and types.
 */

/*! \defgroup ids_peak_icv_c_buffer Buffer
 *  \ingroup ids_peak_icv_c_types
 * Buffer level functions and types.
 */

/*! \defgroup ids_peak_icv_c_pointcloud PointCloud
 *  \ingroup ids_peak_icv_c_types
 * Point cloud level functions and types.
 */

/*! \defgroup ids_peak_icv_c_region Region
 *  \ingroup ids_peak_icv_c_types
 * Region level functions and types.
 */

/*! \defgroup ids_peak_icv_c_polygon Polygon
 *  \ingroup ids_peak_icv_c_types
 * Polygon level functions and types.
 */

/*! \defgroup ids_peak_icv_c_binary Binary
 *  \ingroup ids_peak_icv_c
 * Objects used to be saved on the camera
 */

/*! \defgroup ids_peak_icv_c_serialization Serialization
 *  \ingroup ids_peak_icv_c
 * Objects used for serialization
 */

/*! \defgroup ids_peak_icv_c_serializer Serializer
 *  \ingroup ids_peak_icv_c_serialization
 * Objects used for the Serializer
 */

/*! \defgroup ids_peak_icv_c_deserializer Deserializer
 *  \ingroup ids_peak_icv_c_serialization
 * Objects used for the Deserializer
 */

/*! \defgroup ids_peak_icv_c_archive Archive
 *  \ingroup ids_peak_icv_c_serialization
 * Archive functions and types.
 */

#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_parameters.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_plate.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_calibration_view.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_camera_calibration.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_extrinsic_parameters.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_intrinsic_parameters.h>
#include <peak_icv_c/algorithms/calibration/peak_icv_workspace_calibration.h>

#include <peak_icv_c/algorithms/code_reader/peak_icv_code_reader.h>

#include <peak_icv_c/algorithms/filters/peak_icv_image_filter_sharpening.h>
#include <peak_icv_c/algorithms/filters/peak_icv_median_filter.h>

#include <peak_icv_c/algorithms/hdr/peak_icv_hdr.h>
#include <peak_icv_c/algorithms/hdr/tone_mapping/peak_icv_drago_tone_mapping.h>
#include <peak_icv_c/algorithms/hdr/tone_mapping/peak_icv_linear_tone_mapping.h>

#include <peak_icv_c/algorithms/preprocessing/peak_icv_color_matrix_transformation.h>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_downsampling.h>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_gain.h>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_hotpixel_correction.h>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_image_converter.h>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_image_transformation.h>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_tone_curve_correction.h>

#include <peak_icv_c/algorithms/thresholds/peak_icv_threshold.h>

#include <peak_icv_c/algorithms/transformations/peak_icv_undistortion.h>
#include <peak_icv_c/algorithms/transformations/peak_icv_xyz_image_transformer.h>

#include <peak_icv_c/library/peak_icv_library.h>

#include <peak_icv_c/painting/peak_icv_color.h>
#include <peak_icv_c/painting/peak_icv_painter.h>

#include <peak_icv_c/selectors/peak_icv_region_selector.h>

#include <peak_icv_c/serialization/peak_icv_archive.h>

#include <peak_icv_c/types/peak_icv_buffer.h>
#include <peak_icv_c/types/peak_icv_image.h>
#include <peak_icv_c/types/peak_icv_metadata.h>
#include <peak_icv_c/types/peak_icv_point_cloud.h>
#include <peak_icv_c/types/peak_icv_polygon.h>
#include <peak_icv_c/types/peak_icv_region.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

#include <peak_icv_c/binary/peak_icv_binary_validator.h>

#include <peak_icv_c/backend/peak_icv_defines.h>

#include <peak_icv_c/binary/peak_icv_binary_validator.h>

#include <peak_icv_c/binary/peak_icv_binary_header.h>
