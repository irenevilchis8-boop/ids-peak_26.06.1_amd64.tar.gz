/*!
 * \file    peak_icv_binary_header.h
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-11-28
 * \since   1.0
 *
 * Copyright (c) 2024, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include "peak_common_c/types/peak_common_simple_types.h"

#ifdef __cplusplus
#    include <cstddef>
#    include <cstdint>
extern "C" {
#else
#    include <stddef.h>
#    include <stdint.h>
#endif

/*!
 * \ingroup ids_peak_icv_c_binary
 * \typedef peak_icv_binary_header_type
 * \brief Type definition in which the header is included. the possible values are defined as macros
 * (e.g. PEAK_ICV_BINARY_HEADER_TYPE_CALIBRATION_PARAMETERS)
 */
typedef uint32_t peak_icv_binary_header_type;

/*!
 * \ingroup ids_peak_icv_c_binary
 * \def PEAK_ICV_BINARY_HEADER_TYPE_CALIBRATION_PARAMETERS
 * \brief Indicates the type of the data structure is calibration information.
 */
#define PEAK_ICV_BINARY_HEADER_TYPE_CALIBRATION_PARAMETERS ((peak_icv_binary_header_type)0)

/*!
 * \ingroup ids_peak_icv_c_binary
 * \typedef peak_icv_binary_header_flags
 * \brief Type definition for peak_icv flags.
 *
 * Flags are used to indicate various properties or states of the data structure.
 * Each bit in this type can represent a different flag.
 */
typedef uint32_t peak_icv_binary_header_flags;

/*!
 * \ingroup ids_peak_icv_c_binary
 * \def PEAK_ICV_FLAG_FACTORY
 * \brief Indicates the information is created by IDS imaging development systems.
 *
 * This constant flag is used to denote that the peak_icv information was created
 * by IDS Imaging Development Systems GmbH. The value is represented in binary form.
 */
#define PEAK_ICV_BINARY_HEADER_FLAG_FACTORY ((peak_icv_binary_header_flags)0b0)

/*!
 * \ingroup ids_peak_icv_c_binary
 * \brief Represents the header of the peak_icv.
 *
 * This structure contains metadata about the data structure, including version information,
 * type, a CRC checksum for validation, and various flags.
 */
typedef struct peak_icv_binary_header
{
    /*! default value is 0xC0FFEE */
    uint32_t marker;

    /*!  Type of the peak_icv, indicating the kind of data it holds. */
    peak_icv_binary_header_type type;

    /*!
     * \brief Flags indicating various properties of the peak_icv.
     *
     * Each bit in the peak_icv_binary_header_flags can be activated (1) or deactivated (0). These
     * flags provide additional information about the state or characteristics of the file.
     * To use multiple flags concatenate them with the binary OR operator.
     */
    peak_icv_binary_header_flags flags;

    /*!  Version information. */
    peak_common_version version;

    /*!
     * \brief CRC checksum for validation.
     *
     * The CRC checksum is calculated with the CRC value set to 0. To validate the
     * checksum, set this value to 0 before computing the CRC.
     */
    uint32_t crc;
} peak_icv_binary_header;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
