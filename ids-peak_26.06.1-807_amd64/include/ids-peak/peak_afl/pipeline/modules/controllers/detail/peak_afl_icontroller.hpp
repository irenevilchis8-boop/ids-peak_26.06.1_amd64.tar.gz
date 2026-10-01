/*!
 * \file    peak_afl_icontroller.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/peak_afl.h>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_skip_frames.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common/serialization/peak_common_iarchive.hpp>
#include <peak_common/serialization/peak_common_iserializable.hpp>

namespace peak
{
namespace pipeline
{
namespace modules
{
namespace autofeature
{
/*!
 * \ingroup ids_peak_afl_pipeline_controller
 * \brief Controller type enumeration
 *
 * Defines the different types of automatic controllers available in the
 * auto feature pipeline system. Each controller type specializes in a
 * specific aspect of automatic camera control.
 *
 * \since 1.8
 */
enum class ControllerType
{
    /*! \brief Automatic focus controller - manages lens focus positioning */
    Focus,
    /*! \brief Automatic brightness controller - manages exposure and gain */
    Brightness,
    /*! \brief Automatic white balance controller - manages color correction */
    WhiteBalance,
};

/*!
 * \ingroup ids_peak_afl_pipeline_controller
 * \brief Controller operation mode enumeration
 *
 * Defines the operational modes that automatic controllers can operate in.
 * These modes control when and how the automatic algorithms are executed.
 *
 * \since 1.8
 */
enum class ControllerMode
{
    /*! \brief Controller is disabled - no automatic processing */
    Off,
    /*! \brief Continuous operation - automatic processing on every frame */
    Continuous,
    /*! \brief Single operation - automatic processing triggered once */
    Once
};

/*!
 * \ingroup ids_peak_afl_pipeline_controller
 * \brief Converts ControllerType enumeration to string representation
 *
 * \param[in] mode The controller type to convert
 * \return String representation of the controller type
 * \throws peak::afl::error::InvalidParameterException if type is unknown
 *
 * \since 1.8
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(ControllerType mode)
{
    if (mode == ControllerType::Focus)
    {
        return "Focus";
    }
    if (mode == ControllerType::Brightness)
    {
        return "Brightness";
    }
    if (mode == ControllerType::WhiteBalance)
    {
        return "WhiteBalance";
    }
    throw peak::afl::error::InvalidParameterException("The given controller type is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

inline std::ostream& operator<<(std::ostream& os, ControllerType mode)
{
    return os << ToString(mode);
}

/*!
 * \ingroup ids_peak_afl_pipeline_controller
 * \brief Converts ControllerMode enumeration to string representation
 *
 * \param[in] mode The controller mode to convert
 * \return String representation of the controller mode
 * \throws peak::afl::error::InvalidParameterException if mode is unknown
 *
 * \since 1.8
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(ControllerMode mode)
{
    if (mode == ControllerMode::Off)
    {
        return "Off";
    }
    if (mode == ControllerMode::Continuous)
    {
        return "Continuous";
    }
    if (mode == ControllerMode::Once)
    {
        return "Once";
    }
    throw peak::afl::error::InvalidParameterException("The given controller mode is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

inline std::ostream& operator<<(std::ostream& os, ControllerMode mode)
{
    return os << ToString(mode);
}

namespace detail
{
PEAK_COMMON_NO_DISCARD inline ControllerMode ToControllerMode(const std::string& mode)
{
    if (mode == "Off")
    {
        return ControllerMode::Off;
    }
    if (mode == "Continuous")
    {
        return ControllerMode::Continuous;
    }
    if (mode == "Once")
    {
        return ControllerMode::Once;
    }
    throw peak::afl::error::InvalidParameterException(
        "The given controller mode " + mode + " is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

PEAK_COMMON_NO_DISCARD inline peak_afl_controller_automode ToCType(ControllerMode controllerMode)
{
    switch (controllerMode)
    {
    case ControllerMode::Off:
        return PEAK_AFL_CONTROLLER_AUTOMODE_OFF;
    case ControllerMode::Continuous:
        return PEAK_AFL_CONTROLLER_AUTOMODE_CONTINUOUS;
    case ControllerMode::Once:
        return PEAK_AFL_CONTROLLER_AUTOMODE_ONCE;
    }

    throw peak::afl::error::InvalidParameterException("Unknown controller mode type", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

PEAK_COMMON_NO_DISCARD inline ControllerMode ToControllerMode(peak_afl_controller_automode controllerMode)
{
    switch (controllerMode)
    {
    case PEAK_AFL_CONTROLLER_AUTOMODE_OFF:
        return ControllerMode::Off;
    case PEAK_AFL_CONTROLLER_AUTOMODE_CONTINUOUS:
        return ControllerMode::Continuous;
    case PEAK_AFL_CONTROLLER_AUTOMODE_ONCE:
        return ControllerMode::Once;
    }

    throw peak::afl::error::InvalidParameterException("Unknown controller mode type", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

PEAK_COMMON_NO_DISCARD inline peak_afl_controllerType ToCType(ControllerType controllerType)
{
    switch (controllerType)
    {
    case ControllerType::Focus:
        return PEAK_AFL_CONTROLLER_TYPE_AUTOFOCUS;
    case ControllerType::Brightness:
        return PEAK_AFL_CONTROLLER_TYPE_BRIGHTNESS;
    case ControllerType::WhiteBalance:
        return PEAK_AFL_CONTROLLER_TYPE_WHITE_BALANCE;
    }

    throw peak::afl::error::InvalidParameterException("Unknown controller type", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

/*!
 * \ingroup ids_peak_afl_pipeline_controller
 * \brief Abstract base interface for all automatic controllers
 *
 * The IController class defines the fundamental interface that all automatic
 * controllers must implement. This interface provides the common functionality
 * required for controller management, mode control, and integration with the
 * auto feature pipeline system.
 *
 * **Core Responsibilities:**
 * - **Controller Identity**: Provide name and type identification
 * - **Mode Management**: Control operational modes (Off, Continuous, Once)
 * - **Status Monitoring**: Report running state and operational status
 * - **Configuration Management**: Support serialization and default reset
 * - **Manager Integration**: Coordinate with the API manager system
 *
 * \note This class is non-copyable and non-movable to ensure proper resource management
 * \note All controllers require a valid API manager for camera communication
 * \note Derived classes should implement thread-safe operations where applicable
 *
 * \see BasicAutoBrightness
 * \see AdvancedAutoBrightness
 * \see BasicAutoFocus
 * \see AdvancedAutoFocus
 * \see BasicAutoWhiteBalance
 * \see AdvancedAutoWhiteBalance
 *
 * \since 1.8
 */
class IController : public peak::common::serialization::ISerializable
{
public:
    /*!
     * \brief Callback function type for operation completion notifications
     * \since 1.8
     */
    using FinishedCallback = std::function<void()>;
    /*!
     * \brief Handle type for managing callback registrations
     * \since 1.8
     */
    using FinishedCallbackHandle = FinishedCallback*;

    explicit IController(peak::afl::Manager& manager)
        : m_manager{ manager }
    {}

    /*!
     * \brief Virtual destructor for proper cleanup of derived classes
     *
     * \since 1.8
     */
    virtual ~IController() = default;

    /*!
     * \brief Copy constructor deleted to prevent copying
     * \since 1.8
     */
    IController(const IController&) = delete;
    /*!
     * \brief Copy assignment deleted to prevent copying
     * \since 1.8
     */
    IController& operator=(const IController&) = delete;

    /*!
     * \brief Move constructor deleted to prevent moving
     * \since 1.8
     */
    IController(IController&&) = delete;
    /*!
     * \brief Move assignment deleted to prevent moving
     * \since 1.8
     */
    IController& operator=(IController&&) = delete;

    /*!
     * \brief Gets the unique name of this controller
     *
     * Returns a human-readable name that uniquely identifies this controller
     * instance. This name is used for logging, debugging, and user interface
     * display purposes.
     *
     * \return Unique string name for this controller
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD virtual std::string GetName() const = 0;

    /*!
     * \brief Gets the type of this controller
     *
     * Returns the controller type enumeration that identifies what kind of
     * automatic functionality this controller provides (Focus, Brightness,
     * or WhiteBalance).
     *
     * \return ControllerType enumeration identifying the controller type
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD virtual ControllerType GetType() const = 0;

    /*!
     * \brief Sets the operational mode for this controller
     *
     * Configures how the controller operates: Off (disabled), Continuous
     * (automatic processing on every frame), or Once (single operation).
     *
     * \param[in] mode The operational mode to set
     *
     * \throws Implementation-specific exceptions may be thrown if the mode
     *         cannot be set or if the controller is in an invalid state
     *
     * \see GetMode()
     * \see ControllerMode
     *
     * \since 1.8
     */
    virtual void SetMode(ControllerMode mode) = 0;

    /*!
     * \brief Gets the current operational mode of this controller
     *
     * Returns the currently configured operational mode that determines
     * when and how the automatic algorithms are executed.
     *
     * \return Current ControllerMode of this controller
     *
     * \see SetMode()
     * \see ControllerMode
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD virtual ControllerMode GetMode() const = 0;

    /*!
     * \brief Checks if the controller is currently running
     *
     * Returns true if the controller is actively processing or executing
     * automatic algorithms, false if it is idle or disabled.
     *
     * \return true if controller is running, false otherwise
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD virtual bool IsRunning() const = 0;

    /*!
     * \brief Resets the controller to its default configuration
     *
     * Restores all controller parameters, features, and settings to their
     * default values. This provides a clean state for reconfiguration.
     *
     * \throws Implementation-specific exceptions may be thrown if the reset
     *         operation fails or if the controller is in an invalid state
     *
     * \since 1.8
     */
    virtual void ResetToDefault() = 0;

protected:
    /*!
     * \brief Gets a reference to the API manager
     *
     * Provides derived classes with access to the API manager for camera
     * communication and system coordination.
     *
     * \return Reference to the API manager instance
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::afl::Manager& GetManager()
    {
        return m_manager;
    }

private:
    /*!
     * \brief Reference to the API manager
     *
     * The API manager instance that coordinates this controller's operations
     * with the camera system. This reference must remain valid for the
     * lifetime of the controller.
     */
    peak::afl::Manager& m_manager;
};
} // namespace detail
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
