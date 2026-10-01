/*!
 * \file    peak_common_exceptions.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

/*!
 * \defgroup ids_peak_common_exceptions Exceptions
 * \ingroup ids_peak_common_cpp
 *
 * \brief Custom exceptions used throughout the library.
 *
 */

#pragma once

#include <stdexcept>

namespace peak
{
namespace common
{
/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Base class for all exceptions thrown by the library.
 *
 * All custom exceptions in the library derive from this class.
 *
 * \since ids_peak_common 1.0
 */
class Exception : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};


#if defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wpadded"
#elif defined(__GNUC__)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wpadded"
#endif

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when a function receives an invalid parameter.
 *
 * Typically, indicates a null or otherwise invalid value passed to a parameter.
 *
 * \since ids_peak_common 1.0
 */
class InvalidParameterException : public virtual Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when memory allocation fails.
 *
 * Indicates that the system was unable to allocate the required memory.
 *
 * \since ids_peak_common 1.0
 */
class BadAllocException : public virtual Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when an unexpected internal error occurs.
 *
 * \since ids_peak_common 1.0
 */
class InternalErrorException : public virtual Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when a cast to an incompatible type is attempted.
 *
 * \since ids_peak_common 1.0
 */
class InvalidCastException : public virtual Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when the library is used before proper initialization.
 *
 * Ensure that the library initialization function has been called before using other features.
 *
 * \since ids_peak_common 1.0
 */
class LibraryNotInitializedException : public virtual Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when a parameter is outside the valid range.
 *
 * Indicates a value that is either too high or too low for the expected bounds.
 *
 * \since ids_peak_common 1.0
 */
class OutOfRangeException : public virtual Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when an operation exceeds its time limit.
 *
 * May indicate a hang, deadlock, or unresponsive resource.
 *
 * \since ids_peak_common 1.0
 */
class TimeoutException : public virtual Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when an input, output, file or device communication error occurs.
 *
 * Often indicates a disconnection or failure to access a hardware device or file.
 *
 * \since ids_peak_common 1.0
 */
class IOException : public virtual Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_common_exceptions
 * \brief Thrown when an unsupported operation or feature is used.
 *
 * Indicates functionality that is not available in the current context or platform.
 *
 * \since ids_peak_common 1.0
 */
class NotSupportedException : public virtual Exception
{
    using Exception::Exception;
};

#if defined(__clang__)
#    pragma clang diagnostic pop
#elif defined(__GNUC__)
#    pragma GCC diagnostic pop
#endif

} // namespace common 
} // namespace peak
