/*!
 * \file    peak_afl.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-01-22
 * \since   1.1
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once


#ifdef PEAK_AFL_DYNAMIC_LOADING
#    define PEAK_AFL_C_ABI_PREFIX peak::afl::dynamic::DynamicLoader::
#else
#    define PEAK_AFL_C_ABI_PREFIX // we could also set ::
#endif

#include <peak_afl/peak_afl.h>
#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_ipl/algorithm/peak_ipl_gain.hpp>
#include <peak_ipl/types/peak_ipl_image.hpp>
#include <peak/node_map/peak_node_map.hpp>

#include <type_traits>
#include <array>
#include <cstdint>
#include <exception>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#if __cplusplus >= 201703L || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L))
#    define PEAK_AFL_NO_DISCARD [[nodiscard]]
#    define PEAK_AFL_MAYBE_UNUSED [[maybe_unused]]
#else
#    ifdef _MSC_VER
#        define PEAK_AFL_NO_DISCARD _Check_return_
#        define PEAK_AFL_MAYBE_UNUSED
#    elif defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
#        define PEAK_AFL_NO_DISCARD __attribute__((warn_unused_result))
#        define PEAK_AFL_MAYBE_UNUSED __attribute__((unused))
#    else
#        define PEAK_AFL_NO_DISCARD
#        define PEAK_AFL_MAYBE_UNUSED
#    endif
#endif

/*! \defgroup ids_peak_afl IDS peak AFL
 *
 * \brief IDS peak AFL provides host-based auto features.
 */

/*!
 * \defgroup ids_peak_afl_cpp C++
 * \ingroup ids_peak_afl
 *
 * \brief The C++ interface for the IDS peak AFL library.
 */

/*!
 * \defgroup ids_peak_afl_library Library
 * \ingroup ids_peak_afl_cpp
 *
 * \brief Library level functions and types.
 */

/*!
 * \defgroup ids_peak_afl_exceptions Exceptions
 * \ingroup ids_peak_afl_cpp
 *
 * \brief Library exception types and functions
 */

/*!
 * \defgroup ids_peak_afl_types Types
 * \ingroup ids_peak_afl_cpp
 *
 * \brief General-purpose types and interfaces used throughout the library.
 */

/*!
 * \defgroup ids_peak_afl_pipeline Pipeline
 * \ingroup ids_peak_afl_cpp
 *
 * \brief Image pipeline modules and functions provided by IDS peak AFL
 *
 * For more information see \ref ids_peak_common_pipeline.
 */

/*!
 * \defgroup ids_peak_afl_pipeline_module Pipeline Modules
 * \ingroup ids_peak_afl_pipeline
 *
 * \brief High-level interfaces for automatic camera control through integrated auto feature management.
 *
 * For more information see \ref ids_peak_common_pipeline_modules.
 */

/*!
 * \defgroup ids_peak_afl_pipeline_controller Pipeline Controller
 * \ingroup ids_peak_afl_pipeline
 *
 * \brief Specialized automatic control implementations for camera features within the pipeline module framework.
 */

/*!
 * \defgroup ids_peak_afl_pipeline_features Pipeline Features
 * \ingroup ids_peak_afl_pipeline
 *
 * \brief Configurable parameters and algorithms for automatic camera control within the pipeline framework.
 */


namespace peak
{
namespace afl
{
namespace library
{

/*!
 * \ingroup ids_peak_afl_library
 * \brief Version information for ids_peak_afl
 */
struct Version_t
{
    std::uint32_t major; //! Major
    std::uint32_t minor; //! Minor
    std::uint32_t subminor; //! Subminor
    std::uint32_t patch; //! Patch

    /*!
     * The String representation for the ids_peak_afl version
     * \returns the string representation
     */
    PEAK_AFL_NO_DISCARD std::string ToString() const
    {
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(subminor) + "." + std::to_string(patch);
    }

    /*!
     * \brief Returns the major part of the version which is the first part of the version scheme separated by dots.
     *
     * \return <b>a</b>.b.c.d
     */
    PEAK_AFL_NO_DISCARD uint32_t Major() const
    {
        return major;
    }

    /*!
     * \brief Returns the minor part of the version which is the second part of the version scheme separated by dots.
     *
     * \return a.<b>b</b>.c.d
     */
    PEAK_AFL_NO_DISCARD uint32_t Minor() const
    {
        return minor;
    }
    /*!
     * \brief Returns the subminor part of the version which is the third part of the version scheme separated by dots.
     *
     * \return a.b.<b>c</b>.d
     */
    PEAK_AFL_NO_DISCARD uint32_t Subminor() const
    {
        return subminor;
    }

    /*!
     * \brief Returns the patch part of the version which is the fourth part of the version scheme separated by dots.
     *
     * \return a.b.c.<b>d</b>
     */
    PEAK_AFL_NO_DISCARD uint32_t Patch() const
    {
        return patch;
    }
};

/*!
 * \ingroup ids_peak_afl_library
 * \brief Init the peak_afl auto feature library
 *
 * Initializes the internal library status.
 *
 * This function must be called prior to any other function call.\n
 * The function may be called multiple times from a single client process.
 * For each call there must be a corresponding call to #peak::afl::library::Exit
 * to ensure proper deinitialization of the library status.
 *
 * \throws peak::afl::error::Exception if initialization fails
 *
 * \since 1.1
 */
inline void Init();

/*!
 * \ingroup ids_peak_afl_library
 * \brief Exit the peak_afl auto feature library
 *
 * Deinitializes the internal library status.
 *
 * For each call to #peak::afl::library::Init there must be a corresponding call to this function
 * to ensure proper deinitialization of the library status. \n
 * After the library has been exited its functions (besides #peak::afl::library::Init) will not be operable
 * until #peak::afl::library::Init has been called again.
 *
 * \throws peak::afl::error::Exception if deinitialization fails
 *
 * \since 1.1
 */
inline void Exit();

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief Get the last error message
 *
 * \returns the last error as string or the error as string
 *
 * \since 1.1
 */
PEAK_AFL_NO_DISCARD inline std::string GetLastError();

/*!
 * \ingroup ids_peak_afl_library
 * \brief Query the library version
 *
 * Provides the version of the library divided in major, minor, subminor and patch, in that order of magnitude.
 *
 * \returns The version struct
 *
 * \throws peak::afl::error::Exception if an error occurs. Check code() and what() for an explanation of the error
 *
 * \note This function can be used even if the library is not initialized.
 *
 * \since 1.1
 */
PEAK_AFL_NO_DISCARD inline Version_t Version();
} // namespace library


namespace error
{

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief General Error type
 */
class Exception : public virtual peak::common::Exception
{
public:
    explicit Exception(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , m_code(code)
    {}

    explicit Exception(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , m_code(code)
    {}

    /*!
     * \brief Get the return code for the failure
     *
     * \returns the return code
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD peak_afl_status code() const
    {
        return m_code;
    }

    /*!
     *
     * \brief Get a string representation for an error code
     *
     * \param status the status code of an exception
     * \returns the string representation for that code
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD static std::string translateCode(peak_afl_status status)
    {
        switch (status)
        {
        case PEAK_AFL_STATUS_SUCCESS:
            return "PEAK_AFL_STATUS_SUCCESS";

        case PEAK_AFL_STATUS_ERROR:
            return "PEAK_AFL_STATUS_ERROR";

        case PEAK_AFL_STATUS_NOT_INITIALIZED:
            return "PEAK_AFL_STATUS_NOT_INITIALIZED";

        case PEAK_AFL_STATUS_INVALID_PARAMETER:
            return "PEAK_AFL_STATUS_INVALID_PARAMETER";

        case PEAK_AFL_STATUS_ACCESS_DENIED:
            return "PEAK_AFL_STATUS_ACCESS_DENIED";

        case PEAK_AFL_STATUS_BUSY:
            return "PEAK_AFL_STATUS_BUSY";

        case PEAK_AFL_STATUS_BUFFER_TOO_SMALL:
            return "PEAK_AFL_STATUS_BUFFER_TOO_SMALL";

        case PEAK_AFL_STATUS_INVALID_IMAGE_FORMAT:
            return "PEAK_AFL_STATUS_INVALID_IMAGE_FORMAT";

        case PEAK_AFL_STATUS_NOT_SUPPORTED:
            return "PEAK_AFL_STATUS_NOT_SUPPORTED";

        case PEAK_AFL_STATUS_VALUE_ADJUSTED:
            return "PEAK_AFL_STATUS_VALUE_ADJUSTED";
        }

        return "Unknown Status code";
    }

private:
    peak_afl_status m_code{};
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown for signaling an unspecified error.
 *
 * \since 2.0
 */
class InternalErrorException
    : public Exception
    , public peak::common::InternalErrorException
{
public:
    explicit InternalErrorException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::InternalErrorException(string)
    {}

    explicit InternalErrorException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::InternalErrorException(string)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown for signaling that the library was not initialized.
 *
 * \note Remember to call peak::afl::Library::Init() / PEAK_AFL_Library_Init() before anything else.
 */
class NotInitializedException
    : public Exception
    , public peak::common::LibraryNotInitializedException
{
public:
    explicit NotInitializedException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::LibraryNotInitializedException(string)
    {}

    explicit NotInitializedException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::LibraryNotInitializedException(string)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown for passing an invalid parameter to a function.
 *
 * One or more function parameters are invalid (e.g., nullptr where valid
 * pointers are required, out-of-range values, invalid handles).
 *
 * \note Check parameter documentation for valid ranges and requirements
 */
class InvalidParameterException
    : public Exception
    , public peak::common::InvalidParameterException
{
public:
    explicit InvalidParameterException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::InvalidParameterException(string)
    {}

    explicit InvalidParameterException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::InvalidParameterException(string)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown when a functionality is not supported.
 *
 * The requested feature or operation is not supported by the current device
 * or configuration. Check feature availability before use.
 */
class NotSupportedException
    : public Exception
    , public peak::common::NotSupportedException
{
public:
    explicit NotSupportedException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::NotSupportedException(string)
    {}

    explicit NotSupportedException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::NotSupportedException(string)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown for signaling a busy operation.
 *
 * \note Try checking the status. If thrown by peak::afl::Manager, call \ref peak::afl::Manager::Status() first.
 */
class BusyException : public Exception
{
public:
    explicit BusyException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}

    explicit BusyException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown for signaling an invalid image format.
 *
 * The provided image format is not supported by the auto feature algorithms
 * or the format parameters are invalid.
 *
 * \note Check supported pixel formats in the documentation
 */
class InvalidImageFormatException : public Exception
{
public:
    explicit InvalidImageFormatException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}

    explicit InvalidImageFormatException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown for signaling an access error.
 *
 * The requested operation could not be performed due to insufficient permissions
 * or the resource being locked by another process.
 */
class BadAccessException : public Exception
{
public:
    explicit BadAccessException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}

    explicit BadAccessException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown when the supplied buffer is too small.
 *
 * The buffer provided for output data is smaller than required.
 */
class BufferTooSmallException : public Exception
{
public:
    explicit BufferTooSmallException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}

    explicit BufferTooSmallException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief Thrown when input data or a file is malformed, unreadable, or otherwise corrupted.
 *
 * This exception occurs, when reading from a file or stream that is incomplete, damaged, or in an unexpected format.
 */
class CorruptedDataException : public Exception
{
public:
    explicit CorruptedDataException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}

    explicit CorruptedDataException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
    {}
};

/*!
 * \ingroup ids_peak_afl_exceptions
 * \brief The exception thrown when a cast to the required type failed.
 */
class InvalidCastException
    : public Exception
    , public peak::common::InvalidCastException
{
public:
    explicit InvalidCastException(const std::string& string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::InvalidCastException(string)
    {}

    explicit InvalidCastException(const char* string, peak_afl_status code)
        : peak::common::Exception(string)
        , Exception(string, code)
        , peak::common::InvalidCastException(string)
    {}
};

/*!
 * \internal
 * \brief Maps an peak_afl_status to the corresponding cpp exception
 *
 * \param[in] code     Status code from a C function which should be mapped
 * \param[in] get_text When true, the exception text is retrieved by calling library::GetLastError()
 *                     otherwise a fallback text is used
 *
 * \throws An exception which maps the peak_afl_status to the correct c++ exception
 */
static void ThrowException(peak_afl_status code, bool get_text = true)
{
    const auto text = get_text ? library::GetLastError() : "No additional text";

    switch (code)
    {
    case PEAK_AFL_STATUS_ERROR:
        throw InternalErrorException(text, code);

    case PEAK_AFL_STATUS_NOT_INITIALIZED:
        throw NotInitializedException(text, code);

    case PEAK_AFL_STATUS_INVALID_PARAMETER:
        throw InvalidParameterException(text, code);

    case PEAK_AFL_STATUS_ACCESS_DENIED:
        throw BadAccessException(text, code);

    case PEAK_AFL_STATUS_BUSY:
        throw BusyException(text, code);

    case PEAK_AFL_STATUS_BUFFER_TOO_SMALL:
        throw BufferTooSmallException(text, code);

    case PEAK_AFL_STATUS_INVALID_IMAGE_FORMAT:
        throw InvalidImageFormatException(text, code);

    case PEAK_AFL_STATUS_NOT_SUPPORTED:
        throw NotSupportedException(text, code);

    case PEAK_AFL_STATUS_VALUE_ADJUSTED:
    case PEAK_AFL_STATUS_SUCCESS:
        break;
    }
}

} // namespace error

class Controller;

/*!
 * \ingroup ids_peak_afl_cpp
 * \brief Central coordination object for automatic camera feature control.
 *
 * \details
 * The Manager class links the device’s `NodeMap` with one or more automatic
 * feature controllers and orchestrates their operation during image
 * processing. It is responsible for creating, owning, and managing controllers
 * of various types (see ::peak_afl_controllerType), forwarding image data
 * to them, and maintaining shared configuration resources such as gain and
 * color correction matrices.
 *
 * ## Purpose
 * A Manager forms the root object of the auto-feature subsystem.
 * It manages the lifecycle of controllers, ensures that each controller type
 * is only instantiated once, and provides the infrastructure required by
 * controllers to execute their algorithms. Image frames passed to `Process()`
 * are distributed to all active controllers so they can update their internal
 * state accordingly.
 *
 * ## Controller Management
 * Controllers must be added to the Manager before they can be used.
 * Each controller type can appear only once, and a controller may belong to
 * only one Manager at a time.
 * The Manager provides functions to:
 *
 * - add or remove individual controllers,
 * - enumerate existing controllers,
 * - query support for specific controller types,
 * - create and immediately register new controllers via `CreateController()`,
 * - destroy one or all controllers.
 *
 * ## Image Processing
 * The `Process()` function forwards image data to the auto-feature system,
 * allowing all attached controllers to evaluate the frame and apply their
 * algorithmic updates. The current processing state can be queried via
 * `Status()`. The manager’s status **should always be checked before calling**
 * `Process()`, as invoking it while a previous frame is still being processed
 * may result in a \ref error::BusyException.
 *
 * ## Shared Configuration
 * The Manager also maintains selected shared parameters, such as IPL gain
 * and the 3×3 Color Correction Matrix (CCM). These settings are applied as
 * part of the internal auto-feature processing pipeline and may affect the
 * behavior or results of individual controllers.
 *
 * ## Lifetime and Ownership
 * A Manager instance owns all controllers registered with it. Destroying a
 * controller via Manager APIs invalidates the associated Controller object.
 *
 * ## Exceptions
 * Most operations may throw ::peak::afl::error::Exception if the
 * underlying API call fails. Callers should handle errors accordingly and
 * refer to `code()` and `what()` for diagnostic details.
 */
class Manager
{
public:
    /*!
     * \brief Create an automanager instance
     *
     * Creates an automanager instance.
     *
     * \param[in]  node_map the shared pointer to the device nodemap
     *
     * \throws peak::afl::error::Exception if an error occurs. Check code() and what() for an explanation of the error
     *
     * \since 1.1
     */
    inline explicit Manager(const std::shared_ptr<peak::core::NodeMap>& node_map);

    /*!
     * \brief Destructor of an automanager instance
     */
    inline ~Manager();

    Manager(const Manager&) = delete;
    inline Manager(Manager&&) noexcept;

    Manager& operator=(const Manager&) noexcept = delete;
    inline Manager& operator=(Manager&&) noexcept;

    /*!
     * \brief Add a controller to an automanager
     *
     * An autocontroller instance can only be added to one autofeature manager at the same time.
     * The same type can only be added one time.
     *
     * \param[in] controller shared_ptr to a controller
     *
     * \throws peak::afl::error::Exception if an error occurs. Check code() and what() for an explanation of the error
     *
     * \since 1.1
     */
    inline void AddController(const std::shared_ptr<Controller>& controller);

    /*!
     * \brief Remove a controller from an automanager
     *
     * Remove a controller from a manager.
     * For a function which destroys the object in one call, see #peak_afl_AutoFeatureManager_DestroyController.
     *
     * \param[in] controller shared_ptr to a controller
     *
     * \throws peak::afl::error::Exception if an error occurs. Check code() and what() for an explanation of the error
     *
     * \since 1.1
     */
    inline void RemoveController(const std::shared_ptr<Controller>& controller);

    /*!
     * \brief Process an image
     *
     * Processes an image.
     *
     * \param[in] image an peak::ipl::Image image
     *
     * \throws peak::afl::error::Exception if an error occurs. Check code() and what() for an explanation of the error
     *
     * \since 1.1
     */
    inline void Process(const peak::ipl::Image& image) const;

    /*!
     * \brief Create a controller and append it to Manager
     *
     * Convenience function to create an autofeature controller and add it to the manager.
     * The same type can only be added one time.
     *
     * \param[in]  type controller type, see #peak_afl_controllerType
     *
     * \returns the shared ptr to the created controller
     *
     * \throws peak::afl::error::Exception if deinitialization fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::shared_ptr<Controller> CreateController(peak_afl_controllerType type);

    /*!
     * \brief Destroy all controllers for a manager.
     *
     * After this operation all controllers associated with the given manager will be invalid.
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void DestroyAllController();

    /*!
     * \brief Destroy a controller.
     *
     * After this operation the controller will be invalid.
     *
     * \param[in] controller shared ptr to a controller
     *
     * \throws peak::afl::error::Exception if function fails
     */
    inline void DestroyController(const std::shared_ptr<Controller>& controller);

    /*!
     * \brief Sets the ipl gain.
     *
     * \param[in] gain an peak::ipl::Gain gain
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.2
     */
    inline void SetGainIPL(const peak::ipl::Gain& gain);

    /*!
     * \brief Set the Color Correction Matrix (CCM)
     *
     * Sets a 3x3 color correction matrix for the auto feature manager. The CCM is used to correct
     * color values during image processing. The matrix should be provided as a std::array of 9 float values
     * in row-major order: [R->R, R->G, R->B, G->R, G->G, G->B, B->R, B->G, B->B].
     * The CCM is currently used exclusively by the Auto White Balance (AWB) controller.
     * Internally, the inverse of the configured CCM is computed and used by the AWB regulation algorithm.
     *
     * If no CCM is configured, an identity matrix is used as default.
     *
     * The matrix must be invertible. If the inverse matrix cannot be computed,
     * processing the image fails and an error is returned within the processing callback.
     *
     * \param[in] ccm std::array of 9 float values representing the 3x3 CCM in row-major order
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.8
     */
    inline void SetCCM(std::array<float, 9> ccm);

    /*!
     * \brief Get the status of a manager.
     *
     * The returned value will contain whether the manager currently processes an image (true) or is idle (false).
     *
     * \returns manager status
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool Status() const;

    /*!
     * \brief Get the list of the controller associated with the manager
     *
     * \returns controller list
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::vector<std::shared_ptr<Controller>> ControllerList() const;

    /*!
     * \brief Get the list count of the controller associated with the manager
     *
     * \returns number of controllers in list
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline size_t ControllerCount() const;

    /*!
     * \brief Get the controller for a type
     *
     * \param[in] type controller type.
     *
     * \returns controller
     *
     * \throws peak::afl::error::Exception if no controller is found
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::shared_ptr<Controller> GetController(peak_afl_controllerType type) const;

    /*!
     * \brief Get if the given controller type is supported
     *
     * \param[in] type controller type.
     *
     * \returns True if controller is supported
     *
     * \since 1.11
     */
    PEAK_AFL_NO_DISCARD inline bool IsControllerSupported(peak_afl_controllerType type) const;

private:
    std::vector<std::shared_ptr<Controller>> m_controllerList;
    mutable std::mutex m_mutex{};
    peak_afl_manager_handle m_handle{};
};

/*!
 * \ingroup ids_peak_afl_cpp
 * \brief Convenience function to create a manager with the supplied controllers
 *
 * \param[in] node_map shared ptr to the node map of the camera
 * \param[in] types    variable argument list of controllers to create
 *
 * \returns two pair tuple with the manager and a vector of the created controllers
 */
template <typename... ControllerTypes>
std::tuple<Manager, std::vector<std::shared_ptr<Controller>>> CreateManager(
    const std::shared_ptr<peak::core::NodeMap>& node_map, ControllerTypes... types)
{
    constexpr int size = sizeof...(types);
    constexpr std::array<peak_afl_controllerType, size> controller_types{ types... };
    std::vector<std::shared_ptr<Controller>> controller{};
    Manager manager{ node_map };
    controller.reserve(size);

    std::for_each(controller_types.cbegin(), controller_types.cend(),
        [&manager, &controller](peak_afl_controllerType type) { controller.emplace_back(manager.CreateController(type)); });

    return { std::move(manager), std::move(controller) };
}


/*!
 * \ingroup ids_peak_afl_types
 * \brief Generic arithmetic range with inclusive endpoints and a defined step size.
 *
 * Represents a numeric interval where both \c min and \c max are included,
 * and \c inc specifies the step between successive admissible values.
 */
template <typename T, typename std::enable_if_t<std::is_arithmetic<T>::value, int> = 0>
struct Range
{
    T min;
    T max;
    T inc;
};

namespace callback
{
using FinishedCallback = std::function<void(void)>;
using DataProcessingCallback = std::function<void(int, int)>;
using ProcessingCallback = std::function<void(peak_afl_process_data*)>;
using ComponentCallback = std::function<void(void)>;

using RegisterFunction = std::function<PEAK_AFL_API_STATUS(void*, void*)>;
using UnRegisterFunction = std::function<void()>;
} // namespace callback

/*!
 * \ingroup ids_peak_afl_cpp
 * \brief High-level interface for automatic camera feature control, providing
 * access to algorithms such as auto-brightness, auto-exposure, auto-gain,
 * white balance, and autofocus. The available functionality depends on the
 * selected controller type (see ::peak_afl_controllerType).
 *
 * \details
 * The Controller class represents a managed interface to one of the available
 * automatic camera feature controllers provided by the auto-feature system.
 * A controller encapsulates all logic necessary to tune a specific set of
 * camera parameters — such as exposure time, gain, brightness, white balance,
 * or focus — depending on the selected controller type
 * (see ::peak_afl_controllerType).
 *
 * ## Controller Types
 * A Controller instance is created using `Create()` and initialized with a
 * specific controller type. Each type specializes in a particular automatic
 * feature:
 *
 * - ::PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS
 *   Controls automatic brightness by adjusting exposure, gain (analog, digital,
 *   combined, host), and related limits or algorithms.
 *
 * - ::PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE
 *   Controls automatic white-balance algorithms and channel gain adjustments.
 *
 * - ::PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS
 *   Controls focus algorithms, sharpness evaluation, and focus search modes.
 *
 * The chosen type determines which features, ranges, and algorithms are
 * available.
 *
 * ## Feature Management
 * A controller provides a broad set of functions for querying capabilities,
 * configuring parameters, and selecting algorithms.
 * Before using optional features—such as ROI handling, limits, or specific
 * algorithms—you must first check whether the controller supports them.
 * Parameter getters typically return \ref Range values with inclusive endpoints
 * and a defined step size, and component-specific controls are available where
 * applicable.
 *
 * ## Regions of Interest
 * Controllers may support simple ROIs, weighted ROIs, or predefined ROI
 * presets, each of which restricts the image region used by the auto-feature
 * algorithm.
 * Support for these features must be checked beforehand using
 * `IsROISupported()`, `IsWeightedROISupported()`, and
 * `IsROIPresetSupported()`.
 *
 * ## Callback Management
 * Controllers allow registration of several callback types:
 *
 * - **Finished callbacks** (when an algorithm iteration completes),
 * - **Component callbacks** (per exposure/gain component),
 * - **Processing callbacks** (image data or metadata processing),
 *
 * All callbacks are RAII-managed via an internal template mechanism that
 * ensures correct registration and safe automatic unregistration.
 *
 * ## Lifetime and Ownership
 * Controller instances are always created as `std::shared_ptr<Controller>` via
 * `Create()`.
 *
 * ## Exceptions
 * Almost all operations may throw ::peak::afl::error::Exception if the
 * underlying API call fails. Capability checks should be performed before
 * attempting unsupported operations.
 *
 * ---
 *
 * In summary, the Controller class acts as the central C++ abstraction for
 * interacting with the automatic camera feature system, providing complete
 * management of parameters, algorithms, ROI behavior, limits, and callbacks
 * for all supported controller types.
 */
class Controller : public std::enable_shared_from_this<Controller>
{
    friend class Manager;

    template <class T>
    class Callback
    {
#ifndef SWIG
    public:
        template <typename R, typename... Args>
        Callback(const std::shared_ptr<peak::afl::Controller>& controller, callback::RegisterFunction register_function,
            callback::UnRegisterFunction unregister_function, std::function<R(Args...)> callback)
            : m_unregister_function(std::move(unregister_function))
            , m_callback(std::move(callback))
        {
            const auto ret = register_function(reinterpret_cast<void*>(&Callback::Func<Args...>), this);
            if (ret != PEAK_AFL_STATUS_SUCCESS)
            {
                error::ThrowException(ret);
            }
            m_controller = controller;
        }

        virtual ~Callback()
        {
            if (auto controller = m_controller.lock())
            {
                m_unregister_function();
            }
        }

    private:
        template <typename... Args>
        static void Func(Args... args, void* ptr)
        {
            static_cast<Callback*>(ptr)->m_callback(args...);
        };
#endif

        std::weak_ptr<peak::afl::Controller> m_controller{};
        callback::UnRegisterFunction m_unregister_function{};
        T m_callback{};
    };


    /*!
     * \brief Creates a controller from a handle
     *
     * This is a internal function. See #Controller::Create
     *
     * \param handle the handle to a controller
     *
     * \since 1.1
     */
    inline explicit Controller(peak_afl_controller_handle handle)
        : m_handle(handle) {};

public:
    /*!
     * Destructor for the controller
     */
    inline ~Controller();

    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&) = delete;

    /*!
     * \brief Create a new controller
     *
     * \param[in]  type controller type
     *
     * \returns the shared ptr to the created controller
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline static std::shared_ptr<Controller> Create(peak_afl_controllerType type);

    /*!
     * \brief Check if skip frames is supported for a controller.
     *
     * \returns  boolean if controller supports skipping frames
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsSkipFramesSupported() const;

    /*!
     * \brief Set number of frames skipped for a controller.
     *
     * Sets the skipped frames for the controller. Only every N-th image will be processed.
     *
     * \param[in] count      number of frames skipped
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetSkipFrames(std::uint32_t count);

    /*!
     * \brief Get number of frames skipped for a controller.
     *
     * Gets the skipped frames for the controller. Only every N-th image will be processed.
     *
     * \returns  number of frames skipped
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::uint32_t GetSkipFrames() const;

    /*!
     * \brief Get range for frames skipped for a controller.
     *
     * \returns valid peak::afl::Range for frames skipped
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline Range<std::uint32_t> GetSkipFramesRange() const;

    /*!
     * \brief Check if setting a region of interest is supported for a controller.
     *
     * If true region of interest is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports setting a region of interest
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsROISupported() const;

    /*!
     * \brief Set the autofeature region of interest for a controller.
     *
     * Set the region of interest for a controller. The processed image will be cropped to the region of interest set.
     *
     * \param[in] rect        region of interest
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetROI(peak_afl_rectangle rect);

    /*!
     * \brief Get the autofeature region of interest for a controller.
     *
     * Get the region of interest for a controller. The processed image will be cropped to the region of interest set.
     *
     * \returns region of interest
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_rectangle GetROI() const;

    /*!
     * \brief Check if ROI preset is supported for a controller.
     *
     * true if ROI preset is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports ROI preset
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsROIPresetSupported() const;

    /*!
     * \brief Set the autofeature region of interest preset for a controller.
     *
     * Will set the supplied preset as region of interest. See also #SetROI.
     *
     * \param[in] preset  region of interest preset
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetROIPreset(peak_afl_roi_preset preset);

    /*!
     * \brief Check if auto mode is supported for a controller.
     *
     * true if auto mode is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports auto mode
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsModeSupported() const;

    /*!
     * \brief Set the autofeature mode for a controller.
     *
     * Will set the controller mode to mode. See #peak_afl_controller_automode for a list of valid values.
     *
     * \param[in] mode       autofeature mode
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetMode(peak_afl_controller_automode mode);

    /*!
     * \brief Get the current autofeature mode for a controller.
     *
     * \returns autofeature mode
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controller_automode GetMode() const;

    /*!
     * \brief Check if auto brightness algorithm is supported for a controller.
     *
     * true if auto brightness algorithm is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports auto brightness algorithm
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    PEAK_AFL_NO_DISCARD bool IsBrightnessAlgorithmSupported() const;

    /*!
     * \brief Set the autofeature brightness algorithm for a controller.
     *
     * Will set the controller brightness algorithm to algorithm. See #peak_afl_controller_brightness_algorithm for a list of valid
     * values.
     *
     * \param[in] algorithm autofeature brightness algorithm
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    void SetBrightnessAlgorithm(peak_afl_controller_brightness_algorithm algorithm);

    /*!
     * \brief Get the current autofeature brightness algorithm for a controller.
     *
     * \returns autofeature brightness algorithm
     *
     * \throws peak::afl::error::Exception if function fails
     */
    PEAK_AFL_NO_DISCARD peak_afl_controller_brightness_algorithm GetBrightnessAlgorithm() const;

    /*!
     * \brief Get the status for a controller.
     *
     * See #peak_afl_controller_status for a list of values.
     *
     * \returns controller status
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controller_status Status() const;

    /*!
     * \brief Get the last auto average for a controller.
     *
     * Used by Controllers processing a mono image.
     *
     * \returns autofeature average
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::uint8_t GetLastAutoAverage() const;

    /*!
     * \brief Get the last auto average for a controller.
     *
     * Used by Controllers processing a color image.
     *
     * \returns std::tuple<red, green, blue> in that order
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> GetLastAutoAverages() const;

    /*!
     * \brief check if auto target is supported for a controller.
     *
     * True if auto target is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports auto target
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsAutoTargetSupported() const;

    /*!
     * \brief Set the auto target for a controller.
     *
     * Set an auto target. Call #peak_afl_AutoController_AutoTarget_GetRange to get the valid range.
     * End value which will be targeted by the controller.
     *
     * \param[in] target     auto target value
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetAutoTarget(uint32_t target);

    /*!
     * \brief Get the currently set auto target for a controller.
     *
     * \returns auto target value
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::uint32_t GetAutoTarget() const;

    /*!
     * \brief Get the auto target range for a controller.
     *
     * Call this function to get the range of valid values which can be set by a call to
     * #SetAutoTarget.
     *
     * \returns peak::afl::Range with valid values
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline Range<std::uint32_t> GetAutoTargetRange() const;

    /*!
     * \brief check if auto tolerance is supported for a controller.
     *
     * True if auto tolerance is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports auto tolerance
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsAutoToleranceSupported() const;

    /*!
     * \brief Set the auto tolerance for a controller.
     *
     * Sets the +/- tolerance for the auto target value.
     *
     * \param[in] tolerance  auto target value
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetAutoTolerance(std::uint32_t tolerance);

    /*!
     * \brief Get the current auto tolerance for a controller.
     *
     * \returns auto tolerance value
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::uint32_t GetAutoTolerance() const;

    /*!
     * \brief Get the auto tolerance range for a controller.
     *
     * Call this function to get the range of valid values which can be set by a call to
     * #SetAutoTolerance.
     *
     * \returns peak::afl::Range with valid values
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline Range<std::uint32_t> GetAutoToleranceRange() const;

    /*!
     * \brief check if auto percentile is supported for a controller.
     *
     * True if auto percentile is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports auto percentile
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsAutoPercentileSupported() const;

    /*!
     * \brief Set the auto percentile for a controller.
     *
     * This is the used percentile value for a controller.
     * To get the valid range, call #peak_afl_AutoController_AutoPercentile_GetRange.
     *
     * \param[in] percentile auto percentile value
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetAutoPercentile(double percentile);

    /*!
     * \brief Get the auto percentile for a controller.
     *
     * \returns auto percentile value
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline double GetAutoPercentile() const;

    /*!
     * \brief Get the auto percentile range for a controller.
     *
     * Call this function to get the range of valid values which can be set by a call to
     * #SetAutoPercentile.
     *
     * \returns peak::afl::Range with valid values
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline Range<double> GetAutoPercentileRange() const;

    /*!
     * \brief Get the controller type.
     *
     * See #peak_afl_controllerType for a list of values.
     *
     * \returns auto controller type
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controllerType Type() const;

    /*!
     * \brief check if setting an algorithm is supported for a controller.
     *
     * True if algorithm is supported, otherwise it is unsupported.
     *
     * Call #GetAlgorithmList to get a list of supported algorithms.
     *
     * \returns boolean if controller supports setting an algorithm
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsAlgorithmSupported() const;

    /*!
     * \brief Set the used algorithm for a controller.
     *
     * To get a list of supported algorithms see #peak_afl_AutoController_Algorithm_GetList.
     *
     * \param[in] algorithm auto controller algorithm
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetAlgorithm(peak_afl_controller_algorithm algorithm);

    /*!
     * \brief Get the used algorithm for a controller.
     *
     * \returns auto controller algorithm
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controller_algorithm GetAlgorithm() const;

    /*!
     * \brief Get the list of supported algorithms for a controller.
     *
     * To set a value, see #SetAlgorithm.
     *
     * \returns vector of supported algorithms
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::vector<peak_afl_controller_algorithm> GetAlgorithmList() const;

    /*!
     * \brief check setting a sharpness algorithm is supported by a controller.
     *
     * True if sharpness algorithm is supported, otherwise it is unsupported.
     *
     * Call #GetSharpnessAlgorithmList to get a list of supported sharpness algorithms.
     *
     * \returns boolean if controller supports setting a sharpness algorithm
     *
     * \throws peak::afl::error::Exception if function fails
     */
    PEAK_AFL_NO_DISCARD inline bool IsSharpnessAlgorithmSupported() const;

    /*!
     * \brief Set the used sharpness algorithm for a controller.
     *
     * To get a list of supported algorithms see #peak_afl_AutoController_SharpnessAlgorithm_GetList.
     *
     * \param[in] algorithm  auto controller sharpness algorithm
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetSharpnessAlgorithm(peak_afl_controller_sharpness_algorithm algorithm);

    /*!
     * \brief Get the used sharpness algorithm for a controller.
     *
     * \returns auto controller sharpness algorithm
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controller_sharpness_algorithm GetSharpnessAlgorithm() const;

    /*!
     * \brief Get the list of supported sharpness algorithms for a controller.
     *
     * To set a value, see #SetSharpnessAlgorithm.
     *
     * \returns vector of supported algorithms
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::vector<peak_afl_controller_sharpness_algorithm> GetSharpnessAlgorithmList() const;

    /*!
     * \brief Set finished callback for a controller.
     *
     * Registers the controller finished callback.
     *
     * \param callback the finished callback
     *
     * \since 1.1
     */
    inline void RegisterFinishedCallback(const callback::FinishedCallback& callback);

    /*!
     * \brief Reset the finished callback for a controller.
     *
     * Removes the previously registered finished callback.
     *
     * \since 1.1
     */
    inline void UnRegisterFinishedCallback();

    /*!
     * \brief Set component callback for a controller.
     *
     * \param component the controller brightness component
     * \param callback the component finished callback
     *
     * \since 1.2
     */
    inline void RegisterComponentCallback(peak_afl_controller_brightness_component component, const callback::FinishedCallback& callback);

    /*!
     * \brief Reset the component callback for a controller.
     *
     * Removes the previously registered component callback.
     *
     * \param component the controller brightness component
     *
     * \since 1.2
     */
    inline void UnRegisterComponentCallback(peak_afl_controller_brightness_component component);

    /*!
     * \brief Set the data callback for a controller.
     *
     * \param callback the Data processing callback
     *
     * \deprecated use #RegisterProcessingCallback instead
     *
     * \since 1.1
     */
    PEAK_AFL_DEPRECATED_ATTR inline void RegisterDataProcessingCallback(const callback::DataProcessingCallback& callback);

    /*!
     * \brief Reset the data callback for a controller.
     *
     * \deprecated use #UnRegisterProcessingCallback instead
     *
     * \since 1.1
     */
    PEAK_AFL_DEPRECATED_ATTR inline void UnRegisterDataProcessingCallback();

    /*!
     * \brief Set the data callback for a controller.
     *
     * \param callback the processing callback
     *
     * \since 1.7
     */
    inline void RegisterProcessingCallback(const callback::ProcessingCallback& callback);

    /*!
     * \brief Reset the data callback for a controller.
     *
     * Removes the previously registered callback.
     *
     * \since 1.7
     */
    inline void UnRegisterProcessingCallback();

    /*!
     * \brief Check if weighted region of interest is supported for a controller.
     *
     * True if weighted region of interest is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports weighted roi
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsWeightedROISupported() const;

    /*!
     * \brief Set the autofeature weighted region of interest for a controller.
     *
     * Already set weighted regions of interest will be overwritten
     *
     * \param[in] list vector of weighted region of interest
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetWeightedROIs(const std::vector<peak_afl_weighted_rectangle>& list);

    /*!
     * \brief Set single autofeature weighted region of interest for a controller.
     *
     * Already set weighted regions of interest will be overwritten
     *
     * \param[in] rect weighted region of interest
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetWeightedROI(const peak_afl_weighted_rectangle& rect);

    /*!
     * \brief Get the autofeature minimum size of weighted region of interest for a controller.
     *
     * \returns the minimum size
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_size GetWeightedROIMinSize() const;

    /*!
     * \brief Get the autofeature weighted region of interest for a controller.
     *
     * \returns vector with set #peak_afl_weighted_rectangle
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::vector<peak_afl_weighted_rectangle> GetWeightedROIs() const;

    /*!
     * \brief Check if limit is supported for a controller.
     *
     * True if limit is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsLimitSupported() const;

    /*!
     * \brief Set the autofeature limit for a controller.
     *
     * Sets the minimum and maximum limit for the algorithm set by #peak_afl_AutoController_Algorithm_Set
     *
     * \param[in] limit      the limit to set
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetLimit(peak_afl_controller_limit limit);

    /*!
     * \brief Get the autofeature limit for a controller.
     *
     * \returns the limit set
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controller_limit GetLimit() const;

    /*!
     * \brief Get the autofeature default limit.
     *
     * \returns the default limit set
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controller_limit GetDefaultLimit() const;

    /*!
     * \brief Check if hysteresis is supported for a controller.
     *
     * True if hysteresis is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports hysteresis
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline bool IsHysteresisSupported() const;

    /*!
     * \brief Set the autofeature hysteresis for a controller.
     *
     * Set the hysteresis for the algorithm set by #SetAlgorithm
     *
     * \param[in] hysteresis the hysteresis to set
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    inline void SetHysteresis(std::uint8_t hysteresis);

    /*!
     * \brief Get the autofeature hysteresis for a controller.
     *
     * \returns the hysteresis set
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::uint8_t GetHysteresis() const;

    /*!
     * \brief Get the autofeature hysteresis default.
     *
     * \returns the default hysteresis
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline std::uint8_t GetDefaultHysteresis() const;

    /*!
     * \brief Get autofeature hysteresis range for a controller.
     *
     * \returns the peak::afl::Range of the hysteresis
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.1
     */
    PEAK_AFL_NO_DISCARD inline Range<std::uint8_t> GetHysteresisRange() const;

    /*!
     * \brief Check if auto mode is supported for a brightness controller component.
     *
     * true if auto mode is supported, otherwise it is unsupported.
     *
     * \returns boolean if controller supports auto mode
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.2
     */
    PEAK_AFL_NO_DISCARD inline bool IsBrightnessComponentModeSupported() const;

    /*!
     * \brief Check if a specific unit is supported for a brightness controller component.
     *
     * true if auto unit is supported, otherwise it is unsupported.
     *
     * \param[in] component  autofeature brightness unit
     * \returns boolean if controller supports auto unit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    PEAK_AFL_NO_DISCARD inline bool IsBrightnessComponentUnitSupported(peak_afl_controller_brightness_component component) const;

    /*!
     * \brief Set the autofeature mode for a brightness controller component.
     *
     * Will set the controller mode to mode. See #peak_afl_controller_automode for a list of valid values.
     *
     * \param[in] component  autofeature brightness component
     * \param[in] mode       autofeature mode
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.2
     */
    inline void BrightnessComponentSetMode(peak_afl_controller_brightness_component component, peak_afl_controller_automode mode);

    /*!
     * \brief Get the current autofeature mode for a brightness controller component.
     *
     * \param[in] component autofeature brightness component
     * \returns autofeature mode
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.2
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controller_automode BrightnessComponentGetMode(
        peak_afl_controller_brightness_component component) const;

    /*!
     * \brief Get the status for a brightness controller component.
     *
     * See #peak_afl_controller_status for a list of values.
     *
     * \param[in] component autofeature brightness component
     * \returns controller status
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.2
     */
    PEAK_AFL_NO_DISCARD inline peak_afl_controller_status BrightnessComponentStatus(
        peak_afl_controller_brightness_component component) const;

    /*!
     * \brief Check if auto gain limit is supported for a controller.
     *
     * \returns true if auto gain limit is supported, otherwise returns false.
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.3
     */
    PEAK_AFL_NO_DISCARD inline bool IsGainLimitSupported() const;

    /*!
     * \brief Set the gain limit for a controller
     *
     * The valid values are dependend on the used gain node and can be between minimum and maximum.
     * Default is the complete range.
     * The used priority list is: Analog -> Digital -> Any -> IPL (if supplied).
     *
     * If any value of the limit is out of range, the value is clamped to be valid. In this case no exception is thrown.
     * It is recommended to check the current values by calling #GetGainLimit after this call.
     *
     * \param[in]  limit      limits the controller to adjust the gain to the supplied range between min and max of \p limit.
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.3
     */
    inline void SetGainLimit(peak_afl_double_limit limit);

    /*!
     * \brief Get autofeature gain limit for a controller
     *
     * \returns the current gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.3
     */
    inline peak_afl_double_limit GetGainLimit() const;

    /*!
     * \brief Get autofeature gain limit range for a controller
     *
     * \returns the possible range for gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.3
     */
    inline peak_afl_double_limit GetGainLimitRange() const;

    /*!
     * \brief Set the analog gain limit for a controller
     *
     * The valid values are dependend on the used gain node and can be between minimum and maximum.
     * Default is the complete range.
     *
     * If any value of the limit is out of range, the value is clamped to be valid. In this case no exception is thrown.
     * It is recommended to check the current values by calling #SetGainAnalogLimit after this call.
     *
     * \param[in]  limit      limits the controller to adjust the analog gain to the supplied range between min and max of \p limit.
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline void SetGainAnalogLimit(peak_afl_double_limit limit);

    /*!
     * \brief Get autofeature analog gain limit for a controller
     *
     * \returns the current analog gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline peak_afl_double_limit GetGainAnalogLimit() const;

    /*!
     * \brief Get autofeature analog gain limit range for a controller
     *
     * \returns the possible range for analog gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline peak_afl_double_limit GetGainAnalogLimitRange() const;

    /*!
     * \brief Set the digital gain limit for a controller
     *
     * The valid values are dependend on the used gain node and can be between minimum and maximum.
     * Default is the complete range.
     *
     * If any value of the limit is out of range, the value is clamped to be valid. In this case no exception is thrown.
     * It is recommended to check the current values by calling #GetGainDigitalLimit after this call.
     *
     * \param[in]  limit      limits the controller to adjust the digital gain to the supplied range between min and max of \p limit.
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline void SetGainDigitalLimit(peak_afl_double_limit limit);

    /*!
     * \brief Get autofeature digital gain limit for a controller
     *
     * \returns the current digital gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline peak_afl_double_limit GetGainDigitalLimit() const;

    /*!
     * \brief Get autofeature digital gain limit range for a controller
     *
     * \returns the possible range for digital gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline peak_afl_double_limit GetGainDigitalLimitRange() const;

    /*!
     * \brief Set the combined gain limit for a controller
     *
     * The valid values are dependend on the used gain node and can be between minimum and maximum.
     * Default is the complete range.
     *
     * If any value of the limit is out of range, the value is clamped to be valid. In this case no exception is thrown.
     * It is recommended to check the current values by calling #GetGainCombinedLimit after this call.
     *
     * \param[in]  limit      limits the controller to adjust the combined gain to the supplied range between min and max of \p limit.
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline void SetGainCombinedLimit(peak_afl_double_limit limit);

    /*!
     * \brief Get autofeature combined gain limit for a controller
     *
     * \returns the current combined gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline peak_afl_double_limit GetGainCombinedLimit() const;

    /*!
     * \brief Get autofeature combined gain limit range for a controller
     *
     * \returns the possible range for combined gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline peak_afl_double_limit GetGainCombinedLimitRange() const;

    /*!
     * \brief Set the host gain limit for a controller
     *
     * The valid values are dependend on the used gain node and can be between minimum and maximum.
     * Default is the complete range.
     *
     * If any value of the limit is out of range, the value is clamped to be valid. In this case no exception is thrown.
     * It is recommended to check the current values by calling #GetGainHostLimit after this call.
     *
     * \param[in]  limit      limits the controller to adjust the host gain to the supplied range between min and max of \p limit.
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline void SetGainHostLimit(peak_afl_double_limit limit);

    /*!
     * \brief Get autofeature host gain limit for a controller
     *
     * \returns the current host gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline peak_afl_double_limit GetGainHostLimit() const;

    /*!
     * \brief Get autofeature host gain limit range for a controller
     *
     * \returns the possible range for host gain limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.6
     */
    inline peak_afl_double_limit GetGainHostLimitRange() const;

    /*!
     * \brief Set the exposure limit for a controller
     *
     * \param[in]  limit      limits the controller to adjust the exposure to the supplied range between min and max of \p limit.
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.4
     */
    inline void SetExposureLimit(peak_afl_double_limit limit);

    /*!
     * \brief Get autofeature exposure limit for a controller
     *
     * \returns the current exposure limit
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.4
     */
    inline peak_afl_double_limit GetExposureLimit() const;

    /*!
     * \brief Get autofeature exposure limit range for a controller
     *
     * \returns the current exposure limit range
     *
     * \throws peak::afl::error::Exception if function fails
     *
     * \since 1.4
     */
    inline peak_afl_double_limit GetExposureLimitRange() const;


private:
    using FinishedCallbackType = Callback<callback::FinishedCallback>;
    using DataProcessingCallbackType = Callback<callback::DataProcessingCallback>;
    using ProcessingCallbackType = Callback<callback::ProcessingCallback>;
    using ComponentCallbackType = Callback<callback::ComponentCallback>;

    peak_afl_controller_handle m_handle{};
    std::unique_ptr<FinishedCallbackType> m_finishedCallback{};
    std::unique_ptr<DataProcessingCallbackType> m_dataProcessingCallback{};
    std::unique_ptr<ProcessingCallbackType> m_ProcessingCallback{};
    std::unique_ptr<ComponentCallbackType> m_finishedExposureCallback{};

    std::unique_ptr<ComponentCallbackType> m_finishedGainCallback{};

    std::unique_ptr<ComponentCallbackType> m_AnalogGainCallback{};
    std::unique_ptr<ComponentCallbackType> m_DigitalGainCallback{};
    std::unique_ptr<ComponentCallbackType> m_CombinedGainCallback{};
    std::unique_ptr<ComponentCallbackType> m_HostGainCallback{};
};

namespace library
{
inline void Init()
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_Init();
    if (ret != PEAK_AFL_STATUS_SUCCESS)

    {
        error::ThrowException(ret, false);
    }
}

inline void Exit()
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_Exit();
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret, false);
    }
}

inline Version_t Version()
{
    Version_t version{};

    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_GetVersion(&version.major, &version.minor, &version.subminor, &version.patch);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret, false);
    }

    return version;
}

inline std::string GetLastError()
{
    std::size_t lastErrorMessageSize;
    peak_afl_status code;

    auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_GetLastError(&code, nullptr, &lastErrorMessageSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        return "Cannot get last error!";
    }

    std::vector<char> text;
    text.resize(lastErrorMessageSize);

    ret = PEAK_AFL_C_ABI_PREFIX peak_afl_GetLastError(&code, text.data(), &lastErrorMessageSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        return "Cannot get last error!";
    }

    return { text.begin(), text.end() };
}
} // namespace library

inline Manager::Manager(const std::shared_ptr<peak::core::NodeMap>& node_map)
{
    if (node_map == nullptr)
    {
        throw error::InvalidParameterException("Invalid node map handle!", PEAK_AFL_STATUS_INVALID_PARAMETER);
    }

    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_Create(&m_handle, node_map->Handle());
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline Manager::~Manager()
{
    if (m_handle != nullptr)
    {
        PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_DestroyAllController(m_handle);

        {
            std::lock_guard<std::mutex> lck(m_mutex);
            for (auto& c : m_controllerList)
            {
                c->m_handle = nullptr;
            }
        }

        PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_Destroy(m_handle);
        m_handle = nullptr;
    }
}

inline Manager::Manager(Manager&& other) noexcept
{
    m_handle = other.m_handle;
    other.m_handle = nullptr;

    std::lock_guard<std::mutex> lck(other.m_mutex);
    m_controllerList = std::move(other.m_controllerList);
}

inline Manager& Manager::operator=(Manager&& other) noexcept
{
    m_handle = other.m_handle;
    other.m_handle = nullptr;

    std::lock_guard<std::mutex> lck(other.m_mutex);
    m_controllerList = std::move(other.m_controllerList);

    return *this;
}

inline void Manager::AddController(const std::shared_ptr<Controller>& controller)
{
    std::lock_guard<std::mutex> lck(m_mutex);

    auto cnt = std::any_of(
        m_controllerList.begin(), m_controllerList.end(), [controller](const std::shared_ptr<Controller>& c) { return c == controller; });

    if (cnt)
    {
        return;
    }

    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_AddController(m_handle, controller->m_handle);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    m_controllerList.emplace_back(controller);
}

inline void Manager::RemoveController(const std::shared_ptr<Controller>& controller)
{
    std::lock_guard<std::mutex> lck(m_mutex);

    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_RemoveController(m_handle, controller->m_handle);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    auto it = std::remove_if(
        m_controllerList.begin(), m_controllerList.end(), [controller](const std::shared_ptr<Controller>& c) { return c == controller; });

    m_controllerList.erase(it, m_controllerList.end());
}

inline void Manager::Process(const peak::ipl::Image& image) const
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_Process(m_handle, ImageBackendAccessor::BackendHandle(image));
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline std::shared_ptr<Controller> Manager::CreateController(peak_afl_controllerType type)
{
    std::lock_guard<std::mutex> lck(m_mutex);

    peak_afl_controller_handle handle{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_CreateController(m_handle, &handle, type);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    auto shared = std::shared_ptr<Controller>(new Controller(handle));
    m_controllerList.emplace_back(shared);

    return shared;
}

inline void Manager::DestroyAllController()
{
    std::lock_guard<std::mutex> lck(m_mutex);

    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_DestroyAllController(m_handle);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    for (auto& c : m_controllerList)
    {
        c->m_handle = nullptr;
    }

    m_controllerList.clear();
}

inline void Manager::DestroyController(const std::shared_ptr<Controller>& controller)
{
    std::lock_guard<std::mutex> lck(m_mutex);

    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_DestroyController(m_handle, controller->m_handle);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    auto it = std::remove_if(
        m_controllerList.begin(), m_controllerList.end(), [controller](const std::shared_ptr<Controller>& c) { return c == controller; });

    m_controllerList.erase(it, m_controllerList.end());

    controller->m_handle = nullptr;
}

inline void Manager::SetGainIPL(const peak::ipl::Gain& gain)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_SetGainIPL(m_handle, GainBackendAccessor::BackendHandle(gain));
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline void Manager::SetCCM(std::array<float, 9> ccm)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_SetCCM(m_handle, ccm.data(), ccm.size());
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline bool Manager::Status() const
{
    std::uint8_t status;
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_Status(m_handle, &status);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return status;
}

inline std::vector<std::shared_ptr<Controller>> Manager::ControllerList() const
{
    std::lock_guard<std::mutex> lck(m_mutex);

    std::vector<std::shared_ptr<Controller>> controller{};

    std::copy(m_controllerList.begin(), m_controllerList.end(), std::back_inserter(controller));

    return controller;
}

inline size_t Manager::ControllerCount() const
{
    return m_controllerList.size();
}

inline std::shared_ptr<Controller> Manager::GetController(peak_afl_controllerType type) const
{
    std::lock_guard<std::mutex> lck(m_mutex);

    auto it = std::find_if(m_controllerList.cbegin(), m_controllerList.cend(),
        [=](const std::shared_ptr<Controller>& controller) { return type == controller->Type(); });

    if (it != m_controllerList.cend())
    {
        return *it;
    }
    else
    {
        throw error::InternalErrorException("No controller found!", PEAK_AFL_STATUS_ERROR);
    }
}

inline bool Manager::IsControllerSupported(peak_afl_controllerType type) const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoFeatureManager_Controller_IsSupported(m_handle, type, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported != PEAK_AFL_FALSE;
}


inline std::shared_ptr<Controller> Controller::Create(peak_afl_controllerType type)
{
    peak_afl_controller_handle handle{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Create(&handle, type);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return std::shared_ptr<Controller>(new Controller(handle));
}

inline Controller::~Controller()
{
    if (m_handle != nullptr)
    {
        PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Destroy(m_handle);
        m_handle = nullptr;
    }
}

inline bool Controller::IsSkipFramesSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SkipFrames_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetSkipFrames(std::uint32_t count)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SkipFrames_Set(m_handle, count);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline std::uint32_t Controller::GetSkipFrames() const
{
    std::uint32_t count{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SkipFrames_Get(m_handle, &count);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return count;
}

inline Range<std::uint32_t> Controller::GetSkipFramesRange() const
{
    Range<std::uint32_t> range{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SkipFrames_GetRange(m_handle, &range.min, &range.max, &range.inc);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return range;
}

inline bool Controller::IsROISupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_ROI_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetROI(peak_afl_rectangle rect)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_ROI_Set(m_handle, rect);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_rectangle Controller::GetROI() const
{
    peak_afl_rectangle rect{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_ROI_Get(m_handle, &rect);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return rect;
}

inline bool Controller::IsROIPresetSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_ROI_Preset_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetROIPreset(peak_afl_roi_preset preset)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_ROI_Preset_Set(m_handle, preset);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline bool Controller::IsModeSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Mode_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetMode(peak_afl_controller_automode mode)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Mode_Set(m_handle, mode);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_controller_automode Controller::GetMode() const
{
    peak_afl_controller_automode mode{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Mode_Get(m_handle, &mode);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return mode;
}

inline bool Controller::IsBrightnessAlgorithmSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessAlgorithm_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetBrightnessAlgorithm(peak_afl_controller_brightness_algorithm algorithm)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessAlgorithm_Set(m_handle, algorithm);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_controller_brightness_algorithm Controller::GetBrightnessAlgorithm() const
{
    peak_afl_controller_brightness_algorithm algorithm{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessAlgorithm_Get(m_handle, &algorithm);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return algorithm;
}

inline peak_afl_controller_status Controller::Status() const
{
    peak_afl_controller_status status{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Status(m_handle, &status);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return status;
}


inline std::uint8_t Controller::GetLastAutoAverage() const
{
    std::uint8_t average{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GetLastAutoAverage(m_handle, &average);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return average;
}

inline std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> Controller::GetLastAutoAverages() const
{
    std::uint8_t averageRed{}, averageGreen{}, averageBlue{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GetLastAutoAverages(m_handle, &averageRed, &averageGreen, &averageBlue);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return { averageRed, averageGreen, averageBlue };
}

inline bool Controller::IsAutoTargetSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoTarget_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetAutoTarget(std::uint32_t target)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoTarget_Set(m_handle, target);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline std::uint32_t Controller::GetAutoTarget() const
{
    std::uint32_t target{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoTarget_Get(m_handle, &target);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return target;
}

inline Range<std::uint32_t> Controller::GetAutoTargetRange() const
{
    Range<std::uint32_t> range{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoTarget_GetRange(m_handle, &range.min, &range.max, &range.inc);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return range;
}

inline bool Controller::IsAutoToleranceSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoTolerance_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetAutoTolerance(uint32_t tolerance)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoTolerance_Set(m_handle, tolerance);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline uint32_t Controller::GetAutoTolerance() const
{
    std::uint32_t tolerance;
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoTolerance_Get(m_handle, &tolerance);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return tolerance;
}

inline Range<uint32_t> Controller::GetAutoToleranceRange() const
{
    Range<uint32_t> range{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoTolerance_GetRange(m_handle, &range.min, &range.max, &range.inc);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return range;
}

inline bool Controller::IsAutoPercentileSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoPercentile_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetAutoPercentile(double percentile)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoPercentile_Set(m_handle, percentile);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline double Controller::GetAutoPercentile() const
{
    double percentile;
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoPercentile_Get(m_handle, &percentile);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return percentile;
}

inline Range<double> Controller::GetAutoPercentileRange() const
{
    Range<double> range{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_AutoPercentile_GetRange(m_handle, &range.min, &range.max, &range.inc);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return range;
}

inline peak_afl_controllerType Controller::Type() const
{
    peak_afl_controllerType type{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Type_Get(m_handle, &type);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return type;
}

inline bool Controller::IsAlgorithmSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Algorithm_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetAlgorithm(peak_afl_controller_algorithm alg)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Algorithm_Set(m_handle, alg);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_controller_algorithm Controller::GetAlgorithm() const
{
    peak_afl_controller_algorithm alg{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Algorithm_Get(m_handle, &alg);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return alg;
}

inline std::vector<peak_afl_controller_algorithm> Controller::GetAlgorithmList() const
{
    std::vector<peak_afl_controller_algorithm> algList{};
    std::uint32_t listSize{};

    auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Algorithm_GetList(m_handle, nullptr, &listSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    algList.resize(listSize);

    ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Algorithm_GetList(m_handle, algList.data(), &listSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return algList;
}

inline bool Controller::IsSharpnessAlgorithmSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SharpnessAlgorithm_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetSharpnessAlgorithm(peak_afl_controller_sharpness_algorithm alg)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SharpnessAlgorithm_Set(m_handle, alg);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_controller_sharpness_algorithm Controller::GetSharpnessAlgorithm() const
{
    peak_afl_controller_sharpness_algorithm alg{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SharpnessAlgorithm_Get(m_handle, &alg);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return alg;
}

inline std::vector<peak_afl_controller_sharpness_algorithm> Controller::GetSharpnessAlgorithmList() const
{
    std::vector<peak_afl_controller_sharpness_algorithm> algList{};
    std::uint32_t listSize{};

    auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SharpnessAlgorithm_GetList(m_handle, nullptr, &listSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    algList.resize(listSize);

    ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_SharpnessAlgorithm_GetList(m_handle, algList.data(), &listSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return algList;
}

inline void Controller::RegisterFinishedCallback(const callback::FinishedCallback& callback)
{
    m_finishedCallback = std::make_unique<FinishedCallbackType>(
        shared_from_this(),
        [handle = m_handle](void* ptr, void* ctx) {
            return PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Callback_Set(handle, PEAK_AFL_CONTROLLER_CALLBACK_FINISHED, ptr, ctx);
        },
        [handle = m_handle] {
            PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Callback_Set(
                handle, PEAK_AFL_CONTROLLER_CALLBACK_FINISHED, nullptr, nullptr);
        },
        callback);
}

inline void Controller::UnRegisterFinishedCallback()
{
    m_finishedCallback.reset();
}

inline void Controller::RegisterComponentCallback(
    peak_afl_controller_brightness_component component, const callback::FinishedCallback& callback)
{
    if (!IsBrightnessComponentModeSupported())
    {
        throw error::NotSupportedException("Brightness component not supported!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

    const auto registerCallback = [&](peak_afl_controller_brightness_component component) {
        return std::make_unique<ComponentCallbackType>(
            shared_from_this(),
            [handle = m_handle, component](void* ptr, void* ctx) {
                return PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessComponent_Callback_Set(
                    handle, component, PEAK_AFL_CONTROLLER_CALLBACK_FINISHED, ptr, ctx);
            },
            [handle = m_handle, component] {
                PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessComponent_Callback_Set(
                    handle, component, PEAK_AFL_CONTROLLER_CALLBACK_FINISHED, nullptr, nullptr);
            },
            callback);
    };

    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_EXPOSURE == component)
    {
        m_finishedExposureCallback = registerCallback(component);
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_GAIN == component)
    {
        m_finishedGainCallback = registerCallback(component);
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_ANALOG_GAIN == component)
    {
        m_AnalogGainCallback = registerCallback(component);
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_DIGITAL_GAIN == component)
    {
        m_DigitalGainCallback = registerCallback(component);
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_COMBINED_GAIN == component)
    {
        m_CombinedGainCallback = registerCallback(component);
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_HOST_GAIN == component)
    {
        m_HostGainCallback = registerCallback(component);
    }
    else
    {
        throw error::InvalidParameterException("Brightness component type is invalid!", PEAK_AFL_STATUS_INVALID_PARAMETER);
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
}

inline void Controller::UnRegisterComponentCallback(peak_afl_controller_brightness_component component)
{
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_EXPOSURE == component)
    {
        m_finishedExposureCallback.reset();
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_GAIN == component)
    {
        m_finishedGainCallback.reset();
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_ANALOG_GAIN == component)
    {
        m_AnalogGainCallback.reset();
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_DIGITAL_GAIN == component)
    {
        m_DigitalGainCallback.reset();
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_COMBINED_GAIN == component)
    {
        m_CombinedGainCallback.reset();
    }
    else if (PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_HOST_GAIN == component)
    {
        m_HostGainCallback.reset();
    }
    else
    {
        throw error::InvalidParameterException("Brightness component type is invalid!", PEAK_AFL_STATUS_INVALID_PARAMETER);
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
}

inline void Controller::RegisterDataProcessingCallback(const callback::DataProcessingCallback& callback)
{
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    m_dataProcessingCallback = std::make_unique<DataProcessingCallbackType>(
        shared_from_this(),
        [handle = m_handle](void* ptr, void* ctx) {
            return PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Callback_Set(
                handle, PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING_DATA, ptr, ctx);
        },
        [handle = m_handle] {
            PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Callback_Set(
                handle, PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING_DATA, nullptr, nullptr);
        },
        callback);
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
}

inline void Controller::RegisterProcessingCallback(const callback::ProcessingCallback& callback)
{
    m_ProcessingCallback = std::make_unique<ProcessingCallbackType>(
        shared_from_this(),
        [handle = m_handle](void* ptr, void* ctx) {
            return PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Callback_Set(
                handle, PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING, ptr, ctx);
        },
        [handle = m_handle] {
            PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Callback_Set(
                handle, PEAK_AFL_CONTROLLER_CALLBACK_PROCESSING, nullptr, nullptr);
        },
        callback);
}

inline void Controller::UnRegisterProcessingCallback()
{
    m_ProcessingCallback.reset();
}

inline void Controller::UnRegisterDataProcessingCallback()
{
    m_dataProcessingCallback.reset();
}

inline bool Controller::IsWeightedROISupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Weighted_ROI_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetWeightedROIs(const std::vector<peak_afl_weighted_rectangle>& list)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Weighted_ROI_Set(
        m_handle, list.data(), static_cast<uint32_t>(list.size()));
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline void Controller::SetWeightedROI(const peak_afl_weighted_rectangle& rect)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Weighted_ROI_Set(m_handle, &rect, 1);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_size Controller::GetWeightedROIMinSize() const
{
    peak_afl_size minSize{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Weighted_ROI_Min_Size(m_handle, &minSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return minSize;
}

inline std::vector<peak_afl_weighted_rectangle> Controller::GetWeightedROIs() const
{
    std::vector<peak_afl_weighted_rectangle> list;
    std::uint32_t listSize{};

    auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Weighted_ROI_Get(m_handle, nullptr, &listSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    list.resize(listSize);

    ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Weighted_ROI_Get(m_handle, list.data(), &listSize);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return list;
}

inline bool Controller::IsLimitSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Limit_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetLimit(peak_afl_controller_limit limit)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Limit_Set(m_handle, limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_controller_limit Controller::GetLimit() const
{
    peak_afl_controller_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Limit_Get(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return limit;
}

inline peak_afl_controller_limit Controller::GetDefaultLimit() const
{
    peak_afl_controller_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Limit_Default(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return limit;
}

inline bool Controller::IsHysteresisSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Hysteresis_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetHysteresis(std::uint8_t hysteresis)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Hysteresis_Set(m_handle, hysteresis);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline std::uint8_t Controller::GetHysteresis() const
{
    std::uint8_t hysteresis{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Hysteresis_Get(m_handle, &hysteresis);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return hysteresis;
}

inline std::uint8_t Controller::GetDefaultHysteresis() const
{
    std::uint8_t hysteresis{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Hysteresis_Default(m_handle, &hysteresis);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return hysteresis;
}

inline Range<std::uint8_t> Controller::GetHysteresisRange() const
{
    Range<std::uint8_t> hysteresis{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_Hysteresis_GetRange(
        m_handle, &hysteresis.min, &hysteresis.max, &hysteresis.inc);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return hysteresis;
}

PEAK_AFL_NO_DISCARD inline bool Controller::IsBrightnessComponentModeSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessComponent_Mode_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

PEAK_AFL_NO_DISCARD inline bool Controller::IsBrightnessComponentUnitSupported(
    peak_afl_controller_brightness_component component) const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessComponent_Unit_IsSupported(m_handle, component, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::BrightnessComponentSetMode(
    peak_afl_controller_brightness_component component, peak_afl_controller_automode mode)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessComponent_Mode_Set(m_handle, component, mode);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

PEAK_AFL_NO_DISCARD inline peak_afl_controller_automode Controller::BrightnessComponentGetMode(
    peak_afl_controller_brightness_component component) const
{
    peak_afl_controller_automode mode{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessComponent_Mode_Get(m_handle, component, &mode);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return mode;
}

PEAK_AFL_NO_DISCARD inline peak_afl_controller_status Controller::BrightnessComponentStatus(
    peak_afl_controller_brightness_component component) const
{
    peak_afl_controller_status status{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_BrightnessComponent_Status(m_handle, component, &status);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
    return status;
}

inline bool Controller::IsGainLimitSupported() const
{
    peak_afl_BOOL8 supported{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainLimit_IsSupported(m_handle, &supported);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return supported;
}

inline void Controller::SetGainLimit(peak_afl_double_limit limit)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainLimit_Set(m_handle, limit);
    if (ret == PEAK_AFL_STATUS_VALUE_ADJUSTED)
    {
        // Do nothing. Not an error.
    }
    else if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_double_limit Controller::GetGainLimit() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainLimit_Get(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline peak_afl_double_limit Controller::GetGainLimitRange() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainLimit_GetRange(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline void Controller::SetGainAnalogLimit(peak_afl_double_limit limit)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainAnalogLimit_Set(m_handle, limit);
    if (ret == PEAK_AFL_STATUS_VALUE_ADJUSTED)
    {
        // Do nothing. Not an error.
    }
    else if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_double_limit Controller::GetGainAnalogLimit() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainAnalogLimit_Get(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline peak_afl_double_limit Controller::GetGainAnalogLimitRange() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainAnalogLimit_GetRange(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline void Controller::SetGainDigitalLimit(peak_afl_double_limit limit)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainDigitalLimit_Set(m_handle, limit);
    if (ret == PEAK_AFL_STATUS_VALUE_ADJUSTED)
    {
        // Do nothing. Not an error.
    }
    else if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_double_limit Controller::GetGainDigitalLimit() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainDigitalLimit_Get(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline peak_afl_double_limit Controller::GetGainDigitalLimitRange() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainDigitalLimit_GetRange(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline void Controller::SetGainCombinedLimit(peak_afl_double_limit limit)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainCombinedLimit_Set(m_handle, limit);
    if (ret == PEAK_AFL_STATUS_VALUE_ADJUSTED)
    {
        // Do nothing. Not an error.
    }
    else if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_double_limit Controller::GetGainCombinedLimit() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainCombinedLimit_Get(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline peak_afl_double_limit Controller::GetGainCombinedLimitRange() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainCombinedLimit_GetRange(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline void Controller::SetGainHostLimit(peak_afl_double_limit limit)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainHostLimit_Set(m_handle, limit);
    if (ret == PEAK_AFL_STATUS_VALUE_ADJUSTED)
    {
        // Do nothing. Not an error.
    }
    else if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_double_limit Controller::GetGainHostLimit() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainHostLimit_Get(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline peak_afl_double_limit Controller::GetGainHostLimitRange() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_GainHostLimit_GetRange(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline void Controller::SetExposureLimit(peak_afl_double_limit limit)
{
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_ExposureLimit_Set(m_handle, limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }
}

inline peak_afl_double_limit Controller::GetExposureLimit() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_ExposureLimit_Get(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

inline peak_afl_double_limit Controller::GetExposureLimitRange() const
{
    peak_afl_double_limit limit{};
    const auto ret = PEAK_AFL_C_ABI_PREFIX peak_afl_AutoController_ExposureLimit_GetRange(m_handle, &limit);
    if (ret != PEAK_AFL_STATUS_SUCCESS)
    {
        error::ThrowException(ret);
    }

    return limit;
}

} /* namespace afl */
} /* namespace peak */
