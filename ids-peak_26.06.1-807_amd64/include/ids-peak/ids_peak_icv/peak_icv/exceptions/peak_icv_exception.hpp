/*!
 * \file    peak_icv_exception.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

#include <stdexcept>
#include <string>
#include <vector>

namespace peak
{
namespace icv
{

/*!
 * \brief Base class for all exceptions thrown by the IDS peak ICV library.
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class Exception : public virtual peak::common::Exception
{
private:
    peak_icv_status m_status;

public:
    Exception(const std::string& msg, peak_icv_status status)
        : peak::common::Exception(msg)
        , m_status{ status }
    {}

    PEAK_COMMON_NO_DISCARD peak_icv_status GetStatus() const;
};

/*!
 * \brief Occurs when a required dependency is missing, the library is not initialized, or a misconfiguration arises.
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class InvalidConfigurationException final : public Exception
{
public:
    explicit InvalidConfigurationException(const std::string& msg, peak_icv_status status)
        : peak::common::Exception(msg)
        , Exception(msg, status)
    {}

    InvalidConfigurationException(const InvalidConfigurationException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
    {}
};

/*!
 * \brief Occurs when a failure happens during processing due to an unhandled internal routine condition.
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class InternalErrorException final
    : public Exception
    , public peak::common::InternalErrorException
{
public:
    explicit InternalErrorException(const std::string& msg, peak_icv_status status)
        : peak::common::Exception(msg)
        , Exception(msg, status)
        , peak::common::InternalErrorException(msg)
    {}

    InternalErrorException(const InternalErrorException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
        , peak::common::InternalErrorException(other)
    {}
};

/*!
 * \brief Occurs when input parameters do not match expected conditions (e.g., two input images have different sizes).
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class MismatchException final : public Exception
{
public:
    explicit MismatchException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_MISMATCH)
    {}

    MismatchException(const MismatchException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
    {}
};

/*!
 * \brief Occurs when a requested operation is not implemented or supported (e.g., exporting to an unsupported file format).
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class NotSupportedException final
    : public Exception
    , public peak::common::NotSupportedException
{
public:
    explicit NotSupportedException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_NOT_SUPPORTED)
        , peak::common::NotSupportedException(msg)
    {}

    NotSupportedException(const NotSupportedException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
        , peak::common::NotSupportedException(other)
    {}
};

/*!
 * \brief Occurs when an operation cannot be performed due to logical constraints (e.g., camera calibration without input images).
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class NotPossibleException final : public Exception
{
public:
    explicit NotPossibleException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_NOT_POSSIBLE)
    {}

    NotPossibleException(const NotPossibleException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
    {}
};

/*!
 * \brief Occurs when a provided value falls outside the allowed valid range.
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class OutOfRangeException final
    : public Exception
    , public peak::common::OutOfRangeException
{
public:
    explicit OutOfRangeException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_OUT_OF_RANGE)
        , peak::common::OutOfRangeException(msg)
    {}

    OutOfRangeException(const OutOfRangeException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
        , peak::common::OutOfRangeException(other)
    {}
};

/*!
 * \brief Occurs when a mathematical computation fails (e.g., division by zero or invalid matrix operations).
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class MathErrorException final : public Exception
{
public:
    explicit MathErrorException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_MATH_ERROR)
    {}

    MathErrorException(const MathErrorException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
    {}
};

/*!
 * \brief Occurs when an expected target object (e.g., calibration plate or marker) is not detected in the input image.
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class TargetNotFoundException final : public Exception
{
public:
    explicit TargetNotFoundException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_TARGET_NOT_FOUND)
    {}

    TargetNotFoundException(const TargetNotFoundException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
    {}
};

/*!
 * \brief Occurs when reading from a file or stream that is incomplete, damaged, or in an unexpected format.
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class CorruptedException final : public Exception
{
public:
    explicit CorruptedException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_CORRUPTED)
    {}

    CorruptedException(const CorruptedException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
    {}
};

/*!
 * \brief Occurs when a file operation fails (e.g., missing file, insufficient permissions, or inaccessible directory).
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class IOException final
    : public Exception
    , public peak::common::IOException
{
public:
    explicit IOException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_IO_ERROR)
        , peak::common::IOException(msg)
    {}

    IOException(const IOException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
        , peak::common::IOException(other)
    {}
};

/*!
 * \brief Occurs when attempting to access an object or value via an uninitialized or null pointer.
 *
 * \ingroup ids_peak_icv_cpp_exceptions
 * \since ids_peak_icv 1.0
 */
class NullPointerException final : public Exception
{
public:
    explicit NullPointerException(const std::string& msg)
        : peak::common::Exception(msg)
        , Exception(msg, PEAK_ICV_STATUS_NULL_POINTER)
    {}

    NullPointerException(const NullPointerException& other) noexcept
        : peak::common::Exception(other)
        , Exception(other)
    {}
};

inline peak_icv_status Exception::GetStatus() const
{
    return m_status;
}

} /* namespace icv */
} /* namespace peak */
