/*!
 * \file    peak_icv_serialization_types.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-19
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/types/peak_icv_simple_types.h>

namespace peak
{
namespace icv
{
/*!
 * \ingroup ids_peak_icv_cpp_serialization
 *
 * \brief
 *   Enumeration of supported serialization formats.
 *
 * This enumeration defines the data formats available
 * for serializing and deserializing `IArchive` objects.
 * The serialization system uses this type
 * to select the appropriate format
 * for reading and writing archive data.
 *
 * \see Serializer
 * \see Deserializer
 * \see peak::common::serialization::IArchive
 *
 * \since ids_peak_icv 1.0
 */
enum class SerializationType
{
    /*!
     * \brief
     *   JSON (JavaScript Object Notation) format
     *
     * A lightweight, text-based data interchange format
     * that is human-readable
     * and widely supported across platforms.
     *
     * \since ids_peak_icv 1.0
     */
    Json = PEAK_ICV_SERIALIZATION_TYPE_JSON
};
} /* namespace icv */
} /* namespace peak */
