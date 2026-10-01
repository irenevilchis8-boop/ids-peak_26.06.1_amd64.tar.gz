/*!
 * \file    peak_icv_exception_helpers.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/peak_icv_exception.hpp>
#include <peak_icv_c/backend/peak_icv_dll_defines.h>
#include <peak_icv_c/library/peak_icv_library.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

#include <stdexcept>
#include <vector>

namespace peak
{
namespace icv
{
namespace detail
{
namespace last_error
{
template <class CallableType>
void ExecuteAndMapReturnCodesLight(const CallableType& callableObject)
{
    const auto errorCode = callableObject();
    if (errorCode != PEAK_ICV_STATUS_SUCCESS)
    {
        throw Exception("Could not query the last error!", PEAK_ICV_STATUS_INTERNAL_ERROR);
    }
}

inline std::string GetLastError()
{
    size_t lastErrorDescriptionSize{};
    ExecuteAndMapReturnCodesLight([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_GetLastErrorMessage_GetCount(&lastErrorDescriptionSize);
    });

    std::vector<char> lastErrorDescription(lastErrorDescriptionSize);
    ExecuteAndMapReturnCodesLight([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_GetLastErrorMessage(lastErrorDescription.data(), lastErrorDescriptionSize);
    });

    return { lastErrorDescription.data() };
}
} // namespace last_error

template <class CallableType>
void ExecuteAndMapReturnCodes(const CallableType& callableObject)
{
    const auto errorCode = callableObject();
    if (errorCode != PEAK_ICV_STATUS_SUCCESS)
    {
        std::string errorText = last_error::GetLastError();

        switch (errorCode)
        {
        case PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED:
        case PEAK_ICV_STATUS_DYNAMIC_DEPENDENCY_MISSING:
            throw InvalidConfigurationException(errorText, errorCode);

        case PEAK_ICV_STATUS_NULL_POINTER:
            throw NullPointerException(errorText);

        case PEAK_ICV_STATUS_MISMATCH:
            throw MismatchException(errorText);

        case PEAK_ICV_STATUS_NOT_SUPPORTED:
            throw NotSupportedException(errorText);

        case PEAK_ICV_STATUS_NOT_POSSIBLE:
            throw NotPossibleException(errorText);

        case PEAK_ICV_STATUS_OUT_OF_RANGE:
            throw OutOfRangeException(errorText);

        case PEAK_ICV_STATUS_MATH_ERROR:
            throw MathErrorException(errorText);

        case PEAK_ICV_STATUS_TARGET_NOT_FOUND:
            throw TargetNotFoundException(errorText);

        case PEAK_ICV_STATUS_CORRUPTED:
            throw CorruptedException(errorText);

        case PEAK_ICV_STATUS_IO_ERROR:
            throw IOException(errorText);

        case PEAK_ICV_STATUS_INTERNAL_ERROR:
        case PEAK_ICV_STATUS_INVALID_BUFFER_SIZE:
        case PEAK_ICV_STATUS_INVALID_HANDLE:
            throw InternalErrorException(errorText, errorCode);

        default:
            throw Exception("Generic Error!", errorCode);
        }
    }
}

} // namespace detail

} /* namespace icv */
} /* namespace peak */
