/*!
 * \file    peak_icv_serialization_helper.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-19
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/peak_icv_exception.hpp>
#include <peak_icv/serialization/peak_icv_serialization_types.hpp>
#include <peak_icv_c/types/peak_icv_simple_types.h>

namespace peak
{
namespace icv
{
namespace helper
{

inline peak_icv_serialization_type MapSerializationTypeToApi(SerializationType type)
{
    switch (type)
    {
    case SerializationType::Json:
        return PEAK_ICV_SERIALIZATION_TYPE_JSON;
    default:
        throw NotSupportedException("The given serialization type is not supported.");
    }
}

} /* namespace helper */
} /* namespace icv */
} /* namespace peak */
