/*!
 * \file    peak_afl_advanced_auto_features.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/pipeline/modules/detail/peak_afl_generic_auto_features.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/exceptions/peak_common_exceptions.hpp>

namespace peak
{
namespace pipeline
{
namespace modules
{
/*!
 * \ingroup ids_peak_afl_pipeline_module
 * \brief Advanced automatic features module
 *
 * The AdvancedAutoFeatures class provides a sophisticated and highly configurable
 * interface for managing automatic camera features. This module integrates advanced
 * controllers for brightness, focus, and white balance with comprehensive feature sets
 * and granular control options.
 *
 * **Integrated Advanced Controllers:**
 * - **AdvancedAutoBrightness**: Complete brightness control with multiple gain types
 * - **AdvancedAutoFocus**: Comprehensive focus control with all algorithms
 * - **AdvancedAutoWhiteBalance**: Professional color correction capabilities
 *
 * **Professional Features:**
 * - **Granular Control**: Individual access to all controller features and algorithms
 * - **Advanced Algorithms**: Complete algorithm suites for each auto feature
 * - **Complex Configurations**: Support for sophisticated imaging scenarios
 * - **Performance Tuning**: Fine-grained optimization for specific applications
 * - **Full Serialization**: Complete state management and configuration persistence
 *
 * **Advanced Capabilities:**
 * - **Multi-component Brightness**: Exposure, analog gain, digital gain, combined gain, host gain
 * - **Precision Focus Control**: All search algorithms, sharpness measurements, weighted ROIs
 * - **Professional White Balance**: Advanced color analysis and correction algorithms
 * - **Algorithmic Flexibility**: Configurable algorithms for each auto feature
 * - **Complex ROI Management**: Weighted regions and multi-area analysis
 *
 * \note This class requires a valid device instance that supports advanced auto features
 * \note Individual controller access allows for maximum customization and control
 * \note For simplified usage, consider BasicAutoFeatures instead
 *
 * \see BasicAutoFeatures
 * \see IAutoFeature
 * \see autofeature::AdvancedAutoBrightness
 * \see autofeature::AdvancedAutoFocus
 * \see autofeature::AdvancedAutoWhiteBalance
 *
 * \since 1.8
 */
class AdvancedAutoFeatures : public IAutoFeature
{
public:
    /*!
     * \brief Constructs an AdvancedAutoFeatures instance with the specified device.
     *
     * Initializes the generic module with the provided device and sets up the
     * advanced automatic feature controllers based on device capabilities.
     *
     * \param device Shared pointer to the device instance that will be used for camera operations.
     *               Must be valid and non-null.
     *
     * \pre device must be a valid, non-null shared pointer
     * \pre device must support advanced auto features for full functionality
     *
     * \throws peak::afl::error::InvalidParameterException if device is nullptr
     * \throws peak::afl::error::InternalErrorException if an internal error occurs
     *
     * \note The device must support advanced auto features for full functionality
     * \since 1.8
     */
    explicit AdvancedAutoFeatures(const std::shared_ptr<peak::core::Device>& device)
        : m_genericModule{ device }
    {}

    /*!
     * \brief Serializes the current state of all advanced auto features to an archive.
     *
     * Saves the configuration and state of all advanced controllers including their
     * current settings, modes, algorithms, and parameters. This allows for state persistence
     * and restoration across application sessions.
     *
     * \param archive Reference to the archive where the serialized data will be stored
     *
     * \pre archive must be a valid, writable archive
     * \post archive contains serialized state of all advanced auto features
     *
     * \note This method is const as it doesn't modify the object state
     * \note Advanced controllers may have more complex serialization data than basic versions
     *
     * \see Deserialize()
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        m_genericModule.Serialize(archive);
    }

    /*!
     * \brief Deserializes advanced auto features state from an archive.
     *
     * Restores the configuration and state of all advanced controllers from previously
     * serialized data, including algorithm settings and parameters.
     *
     * \param archive Reference to the archive containing the serialized data
     *
     * \pre archive must contain valid serialized AdvancedAutoFeatures data
     * \post Current controller settings are restored from archive
     *
     * \throws peak::afl::error::Exception if deserialization fails
     *
     * \warning This will overwrite current controller settings
     * \note Advanced features may require device compatibility validation during deserialization
     *
     * \see Serialize()
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        m_genericModule.Deserialize(archive);
    }

    /*!
     * \brief Returns the type identifier for this advanced auto features implementation.
     *
     * \return Constant string "AdvancedAutoFeatures" identifying this implementation
     *
     * \note This is used for type identification in serialization and factory patterns
     * \note Distinguishes this from the basic auto features implementation
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD const char* GetType() const override
    {
        return "AdvancedAutoFeatures";
    }

    /*!
     * \brief Processes input data through all enabled advanced auto feature controllers.
     *
     * Applies advanced automatic adjustments for brightness, focus, and white balance
     * using sophisticated algorithms and processing capabilities.
     *
     * \param input The input data to be processed by the advanced auto features
     * \return Processed data with advanced automatic adjustments applied
     *
     * \pre input must be compatible with the underlying advanced controllers
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
     * \brief Resets all advanced auto feature controllers to their default settings.
     *
     * This will restore factory defaults for all advanced controllers including:
     * - Default algorithms and processing modes
     * - Default parameters and thresholds
     * - Default enable/disable states
     * - Advanced calibration settings
     *
     * \post All controllers are reset to factory default settings
     *
     * \warning This operation cannot be undone
     * \note Advanced controllers may have more complex default configurations
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
     * The gain module is utilized by the advanced auto features when host-side gain
     * adjustments are being used, allowing the controllers to compensate and optimize
     * their algorithms based on the applied gain values.
     *
     * \param gainModule Shared pointer to the gain module implementation.
     *                   Pass nullptr to disable host gain integration.
     *
     * \note Passing nullptr will disable host gain integration with auto features
     * \note This is only relevant when using host-side gain control rather than hardware gain
     * \note Advanced controllers use gain information for auto white balance
     * \since 1.8
     */
    void SetGainModule(std::shared_ptr<peak::pipeline::modules::IGain> gainModule) override
    {
        m_genericModule.SetGainModule(gainModule);
    }

    /*!
     * \brief Sets the color correction matrix for advanced image processing.
     *
     * The color correction matrix is a 3x3 matrix used by advanced controllers
     * for enhanced color processing and white balance calculations.
     *
     * \param ccm Array of 9 float values representing the 3x3 color correction matrix
     *            in row-major order: [0,0] [0,1] [0,2] [1,0] [1,1] [1,2] [2,0] [2,1] [2,2]
     *
     * \pre ccm must contain 9 valid float values
     * \pre Matrix values should be within reasonable ranges to avoid poor image quality
     * \post Color correction matrix is set and available for advanced processing
     *
     * \throws peak::afl::error::Exception if matrix values are invalid
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
     * \brief Sets the enabled state for all advanced auto feature controllers.
     *
     * Controls the overall enabled state of the advanced auto features system.
     *
     * \param enabled True to enable advanced auto features, false to disable them
     *
     * \post Overall enabled state is set to the specified value
     *
     * \note Individual controllers can still be enabled/disabled separately
     * \note Advanced controllers may have different enable/disable behavior than basic versions
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
     * \brief Checks if advanced auto features are currently enabled.
     *
     * \return True if advanced auto features are enabled, false otherwise
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
     * \brief Gets a reference to the advanced brightness controller.
     *
     * Provides access to the advanced brightness controller for sophisticated control
     * over automatic brightness adjustments with enhanced algorithms and precision.
     *
     * \return Reference to the advanced AutoBrightness controller
     *
     * \pre Device must support advanced brightness control
     * \post Returns valid reference to brightness controller
     *
     * \throws peak::afl::error::NotSupportedException if advanced brightness control is not supported by the device
     *
     * \note Check HasAutoBrightness() before calling this method to avoid exceptions
     * \note Advanced brightness controller offers more sophisticated algorithms than basic version
     *
     * \see HasAutoBrightness()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD autofeature::AdvancedAutoBrightness& AutoBrightness() const
    {
        auto* controller = m_genericModule.GetController(autofeature::ControllerType::Brightness);
        if (controller != nullptr)
        {
            return *static_cast<autofeature::AdvancedAutoBrightness*>(controller);
        }
        throw peak::afl::error::NotSupportedException(
            "Brightness controller is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

    /*!
     * \brief Checks if advanced brightness control is available.
     *
     * \return True if the device supports advanced brightness control, false otherwise
     *
     * \note Use this method before calling AutoBrightness() to avoid exceptions
     * \note Advanced brightness control may have different availability than basic version
     *
     * \see AutoBrightness()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasAutoBrightness() const
    {
        return m_genericModule.HasController(autofeature::ControllerType::Brightness);
    }

    /*!
     * \brief Gets a reference to the advanced focus controller.
     *
     * Provides access to the advanced focus controller for sophisticated control
     * over automatic focus adjustments with enhanced precision and algorithms.
     *
     * \return Reference to the advanced AutoFocus controller
     *
     * \pre Device must support advanced focus control
     * \post Returns valid reference to focus controller
     *
     * \throws peak::afl::error::NotSupportedException if advanced focus control is not supported by the device
     *
     * \note Check HasAutoFocus() before calling this method to avoid exceptions
     * \note Advanced focus controller offers more precise control than basic version
     *
     * \see HasAutoFocus()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD autofeature::AdvancedAutoFocus& AutoFocus() const
    {
        auto* controller = m_genericModule.GetController(autofeature::ControllerType::Focus);
        if (controller != nullptr)
        {
            return *static_cast<autofeature::AdvancedAutoFocus*>(controller);
        }

        throw peak::afl::error::NotSupportedException(
            "Focus controller is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

    /*!
     * \brief Checks if advanced focus control is available.
     *
     * \return True if the device supports advanced focus control, false otherwise
     *
     * \note Use this method before calling AutoFocus() to avoid exceptions
     * \note Advanced focus control may have different availability than basic version
     *
     * \see AutoFocus()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasAutoFocus() const
    {
        return m_genericModule.HasController(autofeature::ControllerType::Focus);
    }

    /*!
     * \brief Gets a reference to the advanced white balance controller.
     *
     * Provides access to the advanced white balance controller for sophisticated control
     * over automatic white balance adjustments with enhanced algorithms and calibration.
     *
     * \return Reference to the advanced AutoWhiteBalance controller
     *
     * \pre Device must support advanced white balance control
     * \post Returns valid reference to white balance controller
     *
     * \throws peak::afl::error::NotSupportedException if advanced white balance control is not supported by the device
     *
     * \note Check HasAutoWhiteBalance() before calling this method to avoid exceptions
     * \note Advanced white balance controller offers more sophisticated algorithms than basic version
     *
     * \see HasAutoWhiteBalance()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD autofeature::AdvancedAutoWhiteBalance& AutoWhiteBalance() const
    {
        auto* controller = m_genericModule.GetController(autofeature::ControllerType::WhiteBalance);
        if (controller != nullptr)
        {
            return *static_cast<autofeature::AdvancedAutoWhiteBalance*>(controller);
        }

        throw peak::afl::error::NotSupportedException(
            "White balance controller is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

    /*!
     * \brief Checks if advanced white balance control is available.
     *
     * \return True if the device supports advanced white balance control, false otherwise
     *
     * \note Use this method before calling AutoWhiteBalance() to avoid exceptions
     * \note Advanced white balance control may have different availability than basic version
     *
     * \see AutoWhiteBalance()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasAutoWhiteBalance() const
    {
        return m_genericModule.HasController(autofeature::ControllerType::WhiteBalance);
    }

private:
    /*!
     * \brief Internal generic module handling the actual implementation.
     *
     * This member provides the underlying implementation for all auto feature
     * operations through a generic interface.
     */
    detail::GenericAutoFeatures m_genericModule;
};
} /* namespace modules */
} /* namespace pipeline */
} /* namespace peak */
