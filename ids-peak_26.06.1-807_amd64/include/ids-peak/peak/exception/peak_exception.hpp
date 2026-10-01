/*!
 * \file    peak_exception.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2019-05-01
 * \since   1.0
 *
 * Copyright (c) 2019 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once


#include <stdexcept>
#include <peak_common/exceptions/peak_common_exceptions.hpp>


namespace peak
{
namespace core
{

/*!
 * \ingroup ids_peak_exceptions
 * \brief The base class for all exceptions thrown by the library.
 */
class Exception : public virtual peak::common::Exception
{
    using peak::common::Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling an aborted operation.
 */
class AbortedException : public Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling an access error.
 */
class BadAccessException : public Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling a failed memory allocation.
 */
class BadAllocException : public Exception, public peak::common::BadAllocException
{
public:
    explicit BadAllocException(const std::string& what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::BadAllocException(what)
    {}

    explicit BadAllocException(const char* what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::BadAllocException(what)
    {}

    BadAllocException(const BadAllocException& other)
        : peak::common::Exception(other)
        , peak::core::Exception(other)
        , peak::common::BadAllocException(other)
    {}
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for internal errors.
 */
class InternalErrorException : public Exception, public peak::common::InternalErrorException
{
public:
    explicit InternalErrorException(const std::string& what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::InternalErrorException(what)
    {}

    explicit InternalErrorException(const char* what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::InternalErrorException(what)
    {}

    InternalErrorException(const InternalErrorException& other)
        : peak::common::Exception(other)
        , peak::core::Exception(other)
        , peak::common::InternalErrorException(other)
    {}
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for trying to work on an invalid address.
 */
class InvalidAddressException : public Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for passing an invalid argument to a function.
 */
class InvalidArgumentException : public Exception, public peak::common::InvalidParameterException
{
public:
    explicit InvalidArgumentException(const std::string& what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::InvalidParameterException(what)
    {}

    explicit InvalidArgumentException(const char* what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::InvalidParameterException(what)
    {}

    InvalidArgumentException(const InvalidArgumentException& other)
        : peak::common::Exception(other)
        , peak::core::Exception(other)
        , peak::common::InvalidParameterException(other)
    {}
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for trying to apply an invalid cast.
 */
class InvalidCastException : public Exception, public peak::common::InvalidCastException
{
public:
    explicit InvalidCastException(const std::string& what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::InvalidCastException(what)
    {}

    explicit InvalidCastException(const char* what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::InvalidCastException(what)
    {}

    InvalidCastException(const InvalidCastException& other)
        : peak::common::Exception(other)
        , peak::core::Exception(other)
        , peak::common::InvalidCastException(other)
    {}
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for trying to work on an invalid instance.
 */
class InvalidInstanceException : public Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling that a feature is not available in the device.
 */
class NotAvailableException : public Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling a failed find operation.
 */
class NotFoundException : public Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling that a feature is not implemented.
 */
class NotImplementedException : public Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling that the library was not initialized.
 *
 * \note Remember to call peak::Library::Initialize() / PEAK_Library_Initialize() before anything else.
 */
class NotInitializedException : public Exception, public peak::common::LibraryNotInitializedException
{
public:
    explicit NotInitializedException(const std::string& what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::LibraryNotInitializedException(what)
    {}

    explicit NotInitializedException(const char* what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::LibraryNotInitializedException(what)
    {}

    NotInitializedException(const NotInitializedException& other)
        : peak::common::Exception(other)
        , peak::core::Exception(other)
        , peak::common::LibraryNotInitializedException(other)
    {}
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for trying to access a value that is out of range.
 */
class OutOfRangeException : public Exception, public peak::common::OutOfRangeException
{
public:
    explicit OutOfRangeException(const std::string& what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::OutOfRangeException(what)
    {}

    explicit OutOfRangeException(const char* what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::OutOfRangeException(what)
    {}

    OutOfRangeException(const OutOfRangeException& other)
        : peak::common::Exception(other)
        , peak::core::Exception(other)
        , peak::common::OutOfRangeException(other)
    {}
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling an exceeded timeout during a function call.
 */
class TimeoutException : public Exception, public peak::common::TimeoutException
{
public:
    explicit TimeoutException(const std::string& what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::TimeoutException(what)
    {}

    explicit TimeoutException(const char* what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::TimeoutException(what)
    {}

    TimeoutException(const TimeoutException& other)
        : peak::common::Exception(other)
        , peak::core::Exception(other)
        , peak::common::TimeoutException(other)
    {}
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for a communication error.
 * 
 * A communication error has occured. Most likely due to the device being
 * disconnected.
 */
class IOException : public Exception, public peak::common::IOException
{
public:
    explicit IOException(const std::string& what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::IOException(what)
    {}

    explicit IOException(const char* what)
        : peak::common::Exception(what)
        , peak::core::Exception(what)
        , peak::common::IOException(what)
    {}

    IOException(const IOException& other)
        : peak::common::Exception(other)
        , peak::core::Exception(other)
        , peak::common::IOException(other)
    {}
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signalling that the requested data is not available.
 *
 * The requested data or information is not available.
 */
class NoDataException : public Exception
{
    using Exception::Exception;
};

/*!
 * \ingroup ids_peak_exceptions
 * \brief The exception thrown for signaling an error on opening
 *        a CTI (Common Transport Interface) file.
 */
class CTILoadingException : public Exception
{
    using Exception::Exception;
};

} /* namespace core */
} /* namespace peak */
