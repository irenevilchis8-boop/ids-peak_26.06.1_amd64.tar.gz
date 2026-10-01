/*!
 * \file    peak_common_metadata_key.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-08-08
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */


#pragma once

#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common/types/peak_common_any.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

#include <unordered_map>
#include <sstream>

namespace peak
{
namespace common
{
/*!
 * \brief Enumerates all compile-time known metadata keys.
 *
 * \since ids_peak_common 1.0
 */
enum class MetadataKey
{
    /*!
     * \brief Device-provided image acquisition timestamp in nanoseconds.
     *
     * The timestamp is expressed in nanoseconds and is relative to an
     * unspecified reference point (t = 0). It does not represent an
     * absolute wall-clock time, but instead the elapsed time since
     * that reference. The difference between timestamps of consecutive
     * images indicates the time interval between their recordings.
     *
     * \since ids_peak_common 1.0
     */
    DeviceTimestamp,

    /*!
     * \brief A sequentially incremented identifier for the frame.
     *
     * The frame ID is a sequentially incremented value that increases by one
     * from one frame to the next. It serves as a means to detect missing or
     * out-of-order frames in a stream. Once the maximum value supported by
     * the underlying technology is reached, the frame ID wraps back to zero.
     * The exact wrap-around point is not fixed and depends on the implementation.
     *
     * \since ids_peak_common 1.0
     */
    DeviceFrameID,

    /*!
     * \brief Horizontal pixel binning factor.
     *
     * Indicates how many adjacent pixels are combined horizontally.
     *
     * \since ids_peak_common 1.1
     */
    BinningHorizontal,

    /*!
     * \brief Vertical pixel binning factor.
     *
     * Indicates how many adjacent pixels are combined vertically.
     *
     * \since ids_peak_common 1.1
     */
    BinningVertical,

    /*!
     * \brief Region of interest applied to the image.
     *
     * Defines the rectangular area of the image that remains after
     * processing steps such as cropping or scaling were applied.
     * Coordinates and dimensions are expressed in pixels.
     *
     * \since ids_peak_common 1.1
     */
    Roi,

    /*!
     * \brief Device exposure time the image was captured with.
     *
     * Specified in microseconds (µs).
     *
     * \since ids_peak_common 1.2
     */
    DeviceExposureTime,

    /*!
     *\brief Timestamp of the system since unix epoch in nanoseconds.
     *
     * Provides the system timestamp corresponding to the device timestamp,
     * expressed as nanoseconds since the Unix epoch (00:00:00 UTC on January 1, 1970).
     * This allows data to be associated with a system time, for example
     * for logging or correlating with other system events.
     *
     * \note The system timestamp is not intended for high-precision timing due to
     * device-side timestamping and host processing delays. For applications
     * requiring high timing accuracy, use the [device timestamp](\ref MetadataKey::DeviceTimestamp) directly.
     *
     * \since ids_peak_common 1.3
     */
    SystemTimestamp,

    /*!
     * \brief Device exposure time sequence the image was captured with.
     *
     * This feature applies exclusively to HDR pixel formats
     * where multiple exposures are acquired within a single image frame.
     * During unpacking, the individual exposures are separated into distinct images,
     * and the corresponding exposure time for each image is written to DeviceExposureTime
     *
     * Specified in microseconds (µs).
     *
     * \since ids_peak_common 1.3
     */
    DeviceExposureTimeSequence,

    /*!
     * \brief Device gain the image was captured with.
     *
     * \since ids_peak_common 1.3
     */
    DeviceGain,

    /*!
     * \brief Device gain sequence the image was captured with.
     *
     * This feature applies exclusively to HDR pixel formats
     * where multiple gains are acquired within a single image frame.
     * During unpacking, the individual gains are separated into distinct images,
     * and the corresponding gain for each image is written to DeviceGain
     *
     * \since ids_peak_common 1.3
     */
    DeviceGainSequence
};
} // namespace common 
} // namespace peak
