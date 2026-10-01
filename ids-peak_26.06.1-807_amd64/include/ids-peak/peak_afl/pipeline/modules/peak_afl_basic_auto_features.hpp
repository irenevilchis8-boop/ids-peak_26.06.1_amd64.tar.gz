/*!
 * \file    peak_afl_basic_auto_features.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/pipeline/modules/controllers/peak_afl_basic_auto_brightness.hpp>
#include <peak_afl/pipeline/modules/controllers/peak_afl_basic_auto_white_balance.hpp>
#include <peak_afl/pipeline/modules/detail/peak_afl_generic_auto_features.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak/device/peak_device.hpp>

namespace peak
{
namespace pipeline
{
namespace modules
{

/*!
 * \ingroup ids_peak_afl_pipeline_module
 * \brief Basic automatic features module
 *
 * The BasicAutoFeatures class provides a comprehensive yet simplified interface for
 * managing automatic camera features. This module integrates basic controllers for
 * brightness, focus, and white balance with streamlined configuration options suitable
 * for most common use cases.
 *
 * **Integrated Controllers:**
 * - **BasicAutoBrightness**: Essential exposure and gain control
 * - **BasicAutoFocus**: Standard focus algorithms and ROI support
 * - **BasicAutoWhiteBalance**: Fundamental color correction capabilities
 *
 * **Key Features:**
 * - **Unified Interface**: Single point of access for all auto features
 * - **Bulk Configuration**: Convenient methods for configuring multiple controllers
 * - **Serialization Support**: Complete configuration persistence
 *
 * **Bulk Configuration Methods:**
 * - **SetAllModes()**: Configure operation mode for all controllers simultaneously
 * - **SetAllSkipFrames()**: Set frame skipping strategy across all controllers
 *
 * \note This class requires a valid device instance that supports basic auto features
 * \note For advanced control, consider AdvancedAutoFeatures
 *
 * \see AdvancedAutoFeatures
 * \see IAutoFeature
 * \see autofeature::BasicAutoBrightness
 * \see autofeature::BasicAutoFocus
 * \see autofeature::BasicAutoWhiteBalance
 *
 * \since 1.8
 */
class BasicAutoFeatures : public IAutoFeature
{
public:
    /*!
     * \brief Constructs a BasicAutoFeatures instance with the specified device.
     *
     * Initializes the generic module with the provided device in basic mode and sets up
     * the basic automatic feature controllers based on device capabilities.
     *
     * \param device Shared pointer to the device instance that will be used for camera operations.
     *               Must be valid and non-null.
     *
     * \pre device must be a valid, non-null shared pointer
     * \pre device must support basic auto features for full functionality
     *
     * \throws peak::afl::error::InvalidParameterException if device is nullptr
     * \throws peak::afl::error::InternalErrorException if an internal error occurs
     *
     * \note The device must support basic auto features for full functionality
     * \since 1.8
     */
    explicit BasicAutoFeatures(const std::shared_ptr<peak::core::Device>& device)
        : m_genericModule{ device, false }
    {}

    /*!
     * \brief Serializes the current state of all basic auto features to an archive.
     *
     * Saves the configuration and state of all basic controllers including their
     * current settings, modes, and parameters.
     *
     * \param archive Reference to the archive where the serialized data will be stored
     *
     * \pre archive must be a valid, writable archive
     * \post archive contains serialized state of all basic auto features
     *
     * \note This method is const as it doesn't modify the object state
     * \note Basic controllers have simpler serialization data than advanced versions
     *
     * \see Deserialize()
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        m_genericModule.Serialize(archive);
    }

    /*!
     * \brief Deserializes basic auto features state from an archive.
     *
     * Restores the configuration and state of all basic controllers from previously
     * serialized data, including settings and parameters.
     *
     * \param archive Reference to the archive containing the serialized data
     *
     * \pre archive must contain valid serialized BasicAutoFeatures data
     * \post Current controller settings are restored from archive
     *
     * \throws peak::afl::error::Exception if deserialization fails
     *
     * \warning This will overwrite current controller settings
     * \note Basic features require less device compatibility validation during deserialization
     *
     * \see Serialize()
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        m_genericModule.Deserialize(archive);
    }

    /*!
     * \brief Returns the type identifier for this basic auto features implementation.
     *
     * \return Constant string "BasicAutoFeatures" identifying this implementation
     *
     * \note This is used for type identification in serialization and factory patterns
     * \note Distinguishes this from the advanced auto features implementation
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD const char* GetType() const override
    {
        return "BasicAutoFeatures";
    }

    /*!
     * \brief Processes input data through all enabled basic auto feature controllers.
     *
     * Applies basic automatic adjustments for brightness, focus, and white balance
     * using standard algorithms and processing capabilities.
     *
     * \param input The input data to be processed by the basic auto features
     * \return Processed data with basic automatic adjustments applied
     *
     * \pre input must be compatible with the underlying basic controllers
     * \post Returns processed data with automatic adjustments applied
     *
     * \throws peak::afl::error::InvalidCastException if input type is incompatible
     *
     * \note Only enabled controllers will process the input
     * \note Processing order: brightness → white balance → focus
     *
     * \see SetEnabled()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override
    {
        return m_genericModule.Process(input);
    }

    /*!
     * \brief Resets all basic auto feature controllers to their default settings.
     *
     * This will restore factory defaults for all basic controllers including:
     * - Default processing modes
     * - Default parameters and thresholds
     * - Default enable/disable states
     * - Default skip frame values
     *
     * \post All controllers are reset to factory default settings
     *
     * \warning This operation cannot be undone
     * \note Basic controllers have simpler default configurations than advanced versions
     * \note Consider using Serialize() before calling this method to save current state
     * \since 1.8
     */
    void ResetToDefault() override
    {
        m_genericModule.ResetToDefault();
    }

    /*!
     * \brief Sets the gain module for use when host gains are applied.
     *
     * The gain module is utilized by the basic auto features when host-side gain
     * adjustments are being used, allowing the controllers to compensate and optimize
     * their algorithms based on the applied gain values.
     *
     * \param gainModule Shared pointer to the gain module implementation.
     *                   Pass nullptr to disable host gain integration.
     *
     * \note Passing nullptr will disable host gain integration with auto features
     * \note This is only relevant when using host-side gain control rather than hardware gain
     * \note Basic controllers use gain information for auto white balance
     * \since 1.8
     */
    void SetGainModule(std::shared_ptr<peak::pipeline::modules::IGain> gainModule) override
    {
        m_genericModule.SetGainModule(gainModule);
    }

    /*!
     * \brief Sets the color correction matrix for basic image processing.
     *
     * The color correction matrix is a 3x3 matrix used by basic controllers
     * for standard color processing and white balance calculations.
     *
     * \param ccm Array of 9 float values representing the 3x3 color correction matrix
     *            in row-major order: [0,0] [0,1] [0,2] [1,0] [1,1] [1,2] [2,0] [2,1] [2,2]
     *
     * \pre ccm must contain 9 valid float values
     * \pre Matrix values should be within reasonable ranges to avoid poor image quality
     * \post Color correction matrix is set and available for basic processing
     *
     * \throws peak::afl::error::InvalidParameterException if matrix values are invalid
     *
     * \note Matrix elements should be in row-major order
     * \note Invalid matrix values may result in poor image quality
     * \since 1.8
     */
    void SetColorCorrectionMatrix(const std::array<float, 9>& ccm) override
    {
        m_genericModule.SetColorCorrectionMatrix(ccm);
    }

    /*!
     * \brief Sets the enabled state for all basic auto feature controllers.
     *
     * Controls the overall enabled state of the basic auto features system.
     *
     * \param enabled True to enable basic auto features, false to disable them
     *
     * \post Overall enabled state is set to the specified value
     *
     * \note Individual controllers can still be enabled/disabled separately
     * \note Basic controllers may have different enable/disable behavior than advanced versions
     * \note Disabling does not affect individual controller settings, only their operation
     *
     * \see IsEnabled()
     * \since 1.8
     */
    void SetEnabled(const bool enabled) override
    {
        m_genericModule.SetEnabled(enabled);
    }

    /*!
     * \brief Checks if basic auto features are currently enabled.
     *
     * \return True if basic auto features are enabled, false otherwise
     *
     * \note This returns the overall enabled state, individual controllers may have different states
     * \note Use individual controller GetMode() methods to check specific controller availability
     *
     * \see SetEnabled()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override
    {
        return m_genericModule.IsEnabled();
    }

    /*!
     * \brief Gets a reference to the basic brightness controller.
     *
     * Provides access to the basic brightness controller for standard control
     * over automatic brightness adjustments with standard algorithms.
     *
     * \return Reference to the basic AutoBrightness controller
     *
     * \pre Device must support basic brightness control
     * \post Returns valid reference to brightness controller
     *
     * \throws peak::afl::error::NotSupportedException if basic brightness control is not supported by the device
     *
     * \note Check HasAutoBrightness() before calling this method to avoid exceptions
     *
     * \see HasAutoBrightness()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD autofeature::BasicAutoBrightness& AutoBrightness() const
    {
        auto* controller = m_genericModule.GetController(autofeature::ControllerType::Brightness);
        if (controller != nullptr)
        {
            return *static_cast<autofeature::BasicAutoBrightness*>(controller);
        }
        throw peak::afl::error::NotSupportedException(
            "Brightness controller is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

    /*!
     * \brief Checks if basic brightness control is available.
     *
     * \return True if the device supports basic brightness control, false otherwise
     *
     * \note Use this method before calling AutoBrightness() to avoid exceptions
     * \note Basic brightness control may have different availability than advanced version
     *
     * \see AutoBrightness()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasAutoBrightness() const
    {
        return m_genericModule.HasController(autofeature::ControllerType::Brightness);
    }

    /*!
     * \brief Gets a reference to the basic focus controller.
     *
     * Provides access to the basic focus controller for standard control
     * over automatic focus adjustments with standard algorithms.
     *
     * \return Reference to the basic AutoFocus controller
     *
     * \pre Device must support basic focus control
     * \post Returns valid reference to focus controller
     *
     * \throws peak::afl::error::NotSupportedException if basic focus control is not supported by the device
     *
     * \note Check HasAutoFocus() before calling this method to avoid exceptions
     *
     * \see HasAutoFocus()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD autofeature::BasicAutoFocus& AutoFocus() const
    {
        auto* controller = m_genericModule.GetController(autofeature::ControllerType::Focus);
        if (controller != nullptr)
        {
            return *static_cast<autofeature::BasicAutoFocus*>(controller);
        }

        throw peak::afl::error::NotSupportedException(
            "Focus controller is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

    /*!
     * \brief Checks if basic focus control is available.
     *
     * \return True if the device supports basic focus control, false otherwise
     *
     * \note Use this method before calling AutoFocus() to avoid exceptions
     * \note Basic focus control may have different availability than advanced version
     *
     * \see AutoFocus()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasAutoFocus() const
    {
        return m_genericModule.HasController(autofeature::ControllerType::Focus);
    }

    /*!
     * \brief Gets a reference to the basic white balance controller.
     *
     * Provides access to the basic white balance controller for standard control
     * over automatic white balance adjustments with standard algorithms.
     *
     * \return Reference to the basic AutoWhiteBalance controller
     *
     * \pre Device must support basic white balance control
     * \post Returns valid reference to white balance controller
     *
     * \throws peak::afl::error::NotSupportedException if basic white balance control is not supported by the device
     *
     * \note Check HasAutoWhiteBalance() before calling this method to avoid exceptions
     *
     * \see HasAutoWhiteBalance()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD autofeature::BasicAutoWhiteBalance& AutoWhiteBalance() const
    {
        auto* controller = m_genericModule.GetController(autofeature::ControllerType::WhiteBalance);
        if (controller != nullptr)
        {
            return *static_cast<autofeature::BasicAutoWhiteBalance*>(controller);
        }

        throw peak::afl::error::NotSupportedException(
            "White balance controller is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

    /*!
     * \brief Checks if basic white balance control is available.
     *
     * \return True if the device supports basic white balance control, false otherwise
     *
     * \note Use this method before calling AutoWhiteBalance() to avoid exceptions
     * \note Basic white balance control may have different availability than advanced version
     *
     * \see AutoWhiteBalance()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasAutoWhiteBalance() const
    {
        return m_genericModule.HasController(autofeature::ControllerType::WhiteBalance);
    }

    /*!
     * \brief Sets the operating mode for all available auto feature controllers.
     *
     * This convenience method applies the specified controller mode to all available
     * controllers (brightness, focus, and white balance) simultaneously.
     *
     * \param mode The controller mode to apply to all controllers
     *
     * \post All available controllers have their mode set to the specified value
     *
     * \note Only controllers that are supported by the device will be affected
     * \note This method will not fail if some controllers are not available
     * \note Individual controller modes can still be changed separately after this call
     *
     * \see autofeature::ControllerMode
     * \see SetAllSkipFrames()
     * \since 1.8
     */
    void SetAllModes(autofeature::ControllerMode mode)
    {
        for (auto* controller : m_genericModule.GetControllers())
        {
            controller->SetMode(mode);
        }
    }

    /*!
     * \brief Sets the skip frames value for all available auto feature controllers.
     *
     * This convenience method sets the number of frames to skip before processing
     * for all available controllers (brightness, focus, and white balance) simultaneously.
     * Skip frames help reduce computational load by processing only every Nth frame.
     *
     * \param value Number of frames to skip between processing cycles
     *
     * \post All available controllers have their skip frames value set to the specified value
     *
     * \note Only controllers that are supported by the device will be affected
     * \note This method will not fail if some controllers are not available
     * \note Individual controller skip frames can still be changed separately after this call
     * \note Higher skip frame values reduce computational load but may decrease responsiveness
     *
     * \see SetAllModes()
     * \since 1.8
     */
    void SetAllSkipFrames(uint32_t value)
    {
        auto* brightnessController = m_genericModule.GetController(autofeature::ControllerType::Brightness);
        if (brightnessController != nullptr)
        {
            static_cast<autofeature::BasicAutoBrightness*>(brightnessController)->SetSkipFrames(value);
        }

        auto* focusController = m_genericModule.GetController(autofeature::ControllerType::Focus);
        if (focusController != nullptr)
        {
            static_cast<autofeature::BasicAutoFocus*>(focusController)->SetSkipFrames(value);
        }

        auto* awbController = m_genericModule.GetController(autofeature::ControllerType::WhiteBalance);
        if (awbController != nullptr)
        {
            static_cast<autofeature::BasicAutoWhiteBalance*>(awbController)->SetSkipFrames(value);
        }
    }

private:
    /*!
     * \brief Internal generic module handling the actual implementation.
     *
     * This member provides the underlying implementation for all auto feature
     * operations through a generic interface. Initialized in basic mode (false parameter).
     */
    detail::GenericAutoFeatures m_genericModule;
};


} /* namespace modules */
} /* namespace pipeline */
} /* namespace peak */
