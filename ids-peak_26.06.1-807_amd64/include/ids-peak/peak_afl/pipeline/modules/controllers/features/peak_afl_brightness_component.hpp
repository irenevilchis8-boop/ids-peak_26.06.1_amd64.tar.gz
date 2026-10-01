/*!
 * \file    peak_afl_brightness_component.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/peak_afl.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_icontroller.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_brightness_limit.hpp>

#include <peak_common_c/detail/peak_common_defines.h>

namespace peak
{
namespace pipeline
{
namespace modules
{
namespace autofeature
{
/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Brightness component type enumeration
 *
 * Defines the different types of brightness components that can be controlled
 * in automatic exposure systems. Each component represents a different aspect
 * of image brightness control with specific characteristics and limitations.
 *
 * \since 1.8
 */
enum class BrightnessComponentType
{
    /*! \brief Invalid or uninitialized component type */
    Invalid,
    /*! \brief Exposure time component - controls sensor integration time */
    Exposure,
    /*! \brief Analog gain component - hardware gain applied before digitization */
    AnalogGain,
    /*! \brief Digital gain component - gain applied after digitization */
    DigitalGain,
    /*! \brief Combined gain component - both analog and digital (combined) gain */
    CombinedGain,
    /*! \brief Host gain component - software-based gain processing */
    HostGain,
    /*! \brief Automatic gain component - automatic gain control */
    Gain
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Converts BrightnessComponentType enumeration to string representation
 *
 * \param[in] type The brightness component type to convert
 * \return String representation of the component type
 * \throws peak::afl::error::InternalErrorException if type is invalid
 *
 * \see BrightnessComponentType
 *
 * \since 1.8
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(BrightnessComponentType type)
{
    switch (type)
    {
    case BrightnessComponentType::Exposure:
        return "ComponentExposure";
    case BrightnessComponentType::AnalogGain:
        return "ComponentAnalogGain";
    case BrightnessComponentType::DigitalGain:
        return "ComponentDigitalGain";
    case BrightnessComponentType::CombinedGain:
        return "ComponentCombinedGain";
    case BrightnessComponentType::HostGain:
        return "ComponentHostGain";
    case BrightnessComponentType::Gain:
        return "ComponentGain";
    default:
        break;
    }

    throw peak::afl::error::InternalErrorException("Invalid component type!", PEAK_AFL_STATUS_ERROR);
}

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Stream insertion operator for BrightnessComponentType enumeration
 *
 * Enables direct output of BrightnessComponentType values to output streams
 * using their string representation.
 *
 * \param[in,out] os The output stream to write to
 * \param[in] type The BrightnessComponentType value to output
 * \return Reference to the output stream for chaining
 *
 * \note Uses ToString() function for string conversion
 *
 * \see ToString(BrightnessComponentType)
 * \see BrightnessComponentType
 *
 * \since 1.8
 */
inline std::ostream& operator<<(std::ostream& os, BrightnessComponentType type)
{
    return os << ToString(type);
}

namespace detail
{
PEAK_COMMON_NO_DISCARD inline peak_afl_controller_brightness_component ToCType(BrightnessComponentType componentType)
{
    // clang-format off
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    switch (componentType)
    {
    case BrightnessComponentType::Invalid:
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_INVALID;
    case BrightnessComponentType::Exposure:
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_EXPOSURE;
    case BrightnessComponentType::Gain:
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_GAIN;
    case BrightnessComponentType::AnalogGain:
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_ANALOG_GAIN;
    case BrightnessComponentType::DigitalGain:
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_DIGITAL_GAIN;
    case BrightnessComponentType::CombinedGain:
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_COMBINED_GAIN;
    case BrightnessComponentType::HostGain:
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_COMPONENT_HOST_GAIN;
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
    // clang-format on

    throw peak::afl::error::InvalidParameterException("Unknown brightness component type", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

class GenericAutoBrightness;
} // namespace detail

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Brightness component feature implementation for auto controllers
 *
 * The BrightnessComponent class provides a comprehensive interface for managing
 * individual brightness components in automatic exposure systems. Each component
 * represents a specific aspect of brightness control (exposure, gain types) with
 * its own mode, limits, and callback mechanisms.
 *
 * Key features:
 * - **Component-specific control**: Manage exposure, analog gain, digital gain, etc.
 * - **Mode management**: Set automatic, manual, or other control modes
 * - **Limit enforcement**: Define valid ranges for component values
 * - **Callback support**: Receive notifications when component operations complete
 * - **Serialization**: Persist component configuration
 *
 * This class is designed to work with the auto brightness system's component
 * architecture, allowing fine-grained control over individual brightness parameters.
 *
 * \note This class is non-copyable and non-movable to ensure proper resource
 *       management and callback registration.
 *
 * \see BrightnessComponentType
 * \see ControllerMode
 * \see detail::GenericAutoBrightness
 *
 * \since 1.8
 */
class BrightnessComponent
{
public:
    /*! \brief Copy constructor deleted to prevent copying \since 1.8 */
    BrightnessComponent(const BrightnessComponent&) = delete;
    /*! \brief Copy assignment deleted to prevent copying \since 1.8 */
    BrightnessComponent& operator=(const BrightnessComponent&) = delete;

    /*! \brief Move constructor deleted to prevent moving \since 1.8 */
    BrightnessComponent(BrightnessComponent&&) = delete;
    /*! \brief Move assignment deleted to prevent moving \since 1.8 */
    BrightnessComponent& operator=(BrightnessComponent&&) = delete;

    /*!
     * \brief Destructor that properly unregisters callbacks
     *
     * Automatically unregisters the component callback from the parent controller
     * to ensure proper cleanup and prevent dangling references.
     *
     * \since 1.8
     */
    ~BrightnessComponent()
    {
        m_parent->UnRegisterComponentCallback(detail::ToCType(m_componentType));
    }

    /*!
     * \brief Callback function type for component completion notifications
     * \since 1.8
     */
    using FinishedCallback = std::function<void()>;
    /*!
     * \brief Handle type for managing callback registrations
     * \since 1.8
     */
    using FinishedCallbackHandle = FinishedCallback*;

    /*! \brief Friend class for construction access \since 1.8 */
    friend class detail::GenericAutoBrightness;

    /*!
     * \brief Gets the brightness component type
     *
     * \return The type of this brightness component
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessComponentType GetType() const
    {
        return m_componentType;
    }

    /*!
     * \brief Sets the control mode for this component
     *
     * \param[in] mode The controller mode to set (automatic, manual, etc.)
     *
     * \since 1.8
     */
    void SetMode(ControllerMode mode)
    {
        m_parent->BrightnessComponentSetMode(detail::ToCType(m_componentType), detail::ToCType(mode));
    }

    /*!
     * \brief Gets the current control mode
     *
     * \return The current controller mode for this component
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const
    {
        return detail::ToControllerMode(m_parent->BrightnessComponentGetMode(detail::ToCType(m_componentType)));
    }

    /*!
     * \brief Sets the value limits for this component
     *
     * \param[in] interval The interval defining min/max limits
     *
     * \since 1.8
     */
    void SetLimit(const IntervalD& interval)
    {
        m_limit->Set(interval);
    }

    /*!
     * \brief Gets the current value limits
     *
     * \return The current limit interval for this component
     *
     * \since 1.8
     */
    IntervalD GetLimit()
    {
        return m_limit->Get();
    }

    /*!
     * \brief Serializes component configuration to archive
     *
     * \param[in,out] archive Archive to store configuration
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const
    {
        archive.SetString("Mode", ToString(GetMode()));

        auto limitArchive = archive.CreateArchive();
        m_limit->Serialize(*limitArchive);

        archive.SetArchive("Limit", limitArchive);
    }

    /*!
     * \brief Deserializes component configuration from archive
     *
     * \param[in] archive Archive containing configuration
     *
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive)
    {
        auto limitArchive = archive.GetArchive("Limit");
        m_limit->Deserialize(*limitArchive);

        SetMode(detail::ToControllerMode(archive.GetString("Mode")));
    }

    /*!
     * \brief Registers a callback for component completion
     *
     * \param[in] callback Function to call when component operation finishes
     * \return Handle for unregistering the callback
     *
     * \since 1.8
     */
    FinishedCallbackHandle RegisterFinishedCallback(const BrightnessComponent::FinishedCallback& callback)
    {
        return m_FinishedCallbackManager.RegisterCallback(callback);
    }

    /*!
     * \brief Unregisters a previously registered callback
     *
     * \param[in] callbackHandle Handle returned from RegisterFinishedCallback
     *
     * \since 1.8
     */
    void UnregisterFinishedCallback(BrightnessComponent::FinishedCallbackHandle callbackHandle)
    {
        m_FinishedCallbackManager.UnregisterCallback(callbackHandle);
    }

private:
    /*!
     * \brief Private constructor for friend class access
     *
     * \param[in] parent Shared pointer to parent controller
     * \param[in] componentType Type of brightness component
     * \param[in] limit Unique pointer to limit feature
     *
     * \since 1.8
     */
    BrightnessComponent(const std::shared_ptr<peak::afl::Controller>& parent, BrightnessComponentType componentType,
        std::unique_ptr<features::BrightnessLimit> limit)
        : m_parent{ parent }
        , m_componentType(componentType)
        , m_limit{ std::move(limit) }
    {
        m_parent->RegisterComponentCallback(detail::ToCType(m_componentType), [this]() { m_FinishedCallbackManager.TriggerCallbacks(); });
    }

    /*! \brief Callback manager for finished notifications */
    peak::core::TTriggerCallbackManager<BrightnessComponent::FinishedCallbackHandle, BrightnessComponent::FinishedCallback>
        m_FinishedCallbackManager;

    /*! \brief Shared pointer to parent controller */
    std::shared_ptr<peak::afl::Controller> m_parent;
    /*! \brief Type of this brightness component */
    BrightnessComponentType m_componentType{};
    /*! \brief Unique pointer to limit feature */
    std::unique_ptr<features::BrightnessLimit> m_limit{};
};
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
