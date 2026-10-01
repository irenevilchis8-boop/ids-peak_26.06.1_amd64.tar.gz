/*!
 * \file    peak_afl_advanced_auto_brightness.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/peak_afl.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_generic_auto_brightness.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_icontroller.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_auto_percentile.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_auto_target.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_auto_tolerance.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_brightness_algorithm.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_brightness_component.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_brightness_limit.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_roi.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/exceptions/peak_common_exceptions.hpp>

#include <memory>
#include <utility>
#include <vector>

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
 * \brief Advanced automatic brightness controller with comprehensive feature set
 *
 * The AdvancedAutoBrightness class provides a sophisticated and highly configurable
 * interface for automatic brightness control. This controller offers the complete
 * feature set with granular control over all brightness adjustment mechanisms and
 * algorithmic options.
 *
 * **Advanced Features:**
 * - **Multiple gain types**: Analog, digital, combined, and host gain control
 * - **Algorithmic flexibility**: Configurable brightness analysis algorithms
 * - **ROI support**: Region-of-interest configurations
 * - **Granular limits**: Individual limit control for each brightness component
 * - **Component-level control**: Fine-grained management of individual brightness components
 * - **Callback architecture**: Comprehensive event notification system
 * - **Full serialization**: Complete configuration state management
 *
 * **Brightness Components:**
 * - **Exposure Component**: Sensor integration time control
 * - **Analog Gain Component**: Hardware amplification before digitization
 * - **Digital Gain Component**: Post-digitization amplification
 * - **Combined Gain Component**: Unified analog and digital gain management
 * - **Host Gain Component**: Software-based gain processing
 *
 * **Algorithm Support:**
 * - **Brightness Analysis**: Mean, median
 * - **Percentile Calculation**: Configurable histogram percentile analysis
 * - **Target Achievement**: Sophisticated convergence algorithms
 * - **Tolerance Management**: Advanced stability and hysteresis control
 *
 * \note This controller requires a valid manager instance for camera communication
 * \note Component availability depends on underlying device capabilities
 * \note For simplified usage, consider BasicAutoBrightness instead
 *
 * \see BasicAutoBrightness
 * \see BrightnessComponent
 * \see detail::GenericAutoBrightness
 * \see detail::IController
 *
 * \since 1.8
 */
class AdvancedAutoBrightness : public detail::IController
{
    using ProcessingCallback = std::function<void()>;

public:
    friend BrightnessComponent;

    /*!
     * \brief Constructs an AdvancedAutoBrightness controller with the specified manager and callback.
     *
     * Initializes the brightness controller with all available brightness components
     * including exposure, analog gain, digital gain, combined gain, and host gain.
     * The controller will automatically detect which components are supported by the device.
     *
     * \param manager Reference to the API manager for device communication
     * \param callback Processing callback function that will be invoked when brightness adjustment completes (host gain)
     *
     * \note The callback will be called asynchronously when processing finishes
     * \note Component initialization depends on device capabilities
     *
     * \see BrightnessComponentType
     * \since 1.8
     */
    explicit AdvancedAutoBrightness(peak::afl::Manager& manager, ProcessingCallback callback)
        : IController(manager)
        , m_genericController{ manager, std::move(callback),
            { BrightnessComponentType::Exposure, BrightnessComponentType::AnalogGain, BrightnessComponentType::DigitalGain,
                BrightnessComponentType::CombinedGain, BrightnessComponentType::HostGain } }
    {}

    /*!
     * \brief Destructor for AdvancedAutoBrightness.
     *
     * Cleans up resources and ensures proper shutdown of the controller.
     */
    ~AdvancedAutoBrightness() override = default;

    /*!
     * \brief Gets the name identifier for this controller.
     *
     * \return String "AdvancedAutoBrightness" identifying this controller type
     *
     * \note This is used for type identification in serialization and factory patterns
     * \note Distinguishes this from the basic auto features implementation
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::string GetName() const override
    {
        return "AdvancedAutoBrightness";
    }

    /*!
     * \brief Serializes the current controller state and configuration to an archive.
     *
     * Saves all controller settings including:
     * - Current mode and algorithm settings
     * - Component configurations and states
     * - Target brightness and tolerance values
     * - ROI and percentile settings
     * - Feature configurations
     *
     * \param archive Reference to the archive where the serialized data will be stored
     *
     * \note This method is const as it doesn't modify the controller state
     * \note The serialized data can be used to restore the controller state later
     * \note Component availability is not serialized as it depends on device capabilities
     *
     * \see Deserialize()
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        m_genericController.Serialize(archive);
    }

    /*!
     * \brief Deserializes controller state and configuration from an archive.
     *
     * Restores all controller settings and component configurations from
     * previously serialized data.
     *
     * \param archive Reference to the archive containing the serialized data
     *
     * \note This will overwrite current controller settings
     * \note Component availability is validated during deserialization
     * \note If a component is not available, its settings will be ignored
     *
     * \see Serialize()
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        m_genericController.Deserialize(archive);
    }

    /*!
     * \brief Gets the controller type identifier.
     *
     * \return ControllerType::Brightness identifying this as a brightness controller
     *
     * \note Used for type identification and controller management
     * \note This enables runtime type checking and proper controller categorization
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD ControllerType GetType() const override
    {
        return m_genericController.GetType();
    }

    /*!
     * \brief Sets the operation mode for the brightness controller.
     *
     * \param mode The controller mode to set (Off, Continuous, Once).
     *
     * \note Setting mode to Off will disable automatic brightness adjustment
     *
     * \see GetMode()
     * \see ControllerMode
     * \since 1.8
     */
    void SetMode(ControllerMode mode) override
    {
        m_genericController.SetMode(mode);
    }

    /*!
     * \brief Gets the current operation mode of the brightness controller.
     *
     * \return Current ControllerMode of the brightness controller
     *
     * \note Use this to check if automatic brightness adjustment is active
     *
     * \see SetMode()
     * \see ControllerMode
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const override
    {
        return m_genericController.GetMode();
    }

    /*!
     * \brief Checks if the brightness controller is currently running.
     *
     * \return True if the controller is in any active mode (not Off), false otherwise
     *
     * \note A running controller will actively adjust brightness based on scene analysis
     * \note This is equivalent to checking if GetMode() != ControllerMode::Off
     *
     * \see GetMode()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool IsRunning() const override
    {
        return m_genericController.IsRunning();
    }

    /*!
     * \brief Gets access to the skip frames feature.
     *
     * Skip frames allows the controller to process only every Nth frame instead of
     * every frame, reducing computational load while maintaining brightness control.
     *
     * \return Reference to the SkipFrames feature for configuration
     *
     * \note A value of 0 means process every frame (maximum responsiveness)
     * \note A value of 1 means process every other frame
     * \note Optimal values depend on frame rate and scene dynamics
     *
     * \see features::SkipFrames
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::SkipFrames& SkipFrames()
    {
        return m_genericController.SkipFrames();
    }

    /*!
     * \brief Gets access to the auto target feature for brightness target configuration.
     *
     * Auto target defines the desired brightness level that the controller will
     * attempt to achieve through automatic adjustments.
     *
     * \return Reference to the AutoTarget feature for configuration
     *
     * \note Target values are typically normalized (0 to 255) or in device-specific units
     * \note Optimal target values depend on the specific application and scene conditions
     * \note The target represents the desired brightness level of the analyzed region
     *
     * \see features::AutoTarget
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::AutoTarget& AutoTarget()
    {
        return m_genericController.AutoTarget();
    }

    /*!
     * \brief Gets access to the auto tolerance feature for brightness stability control.
     *
     * Auto tolerance defines the acceptable deviation from the target brightness
     * before the controller triggers adjustment actions.
     *
     * \return Reference to the AutoTolerance feature for configuration
     *
     * \note Smaller tolerance values provide more stable brightness but may cause oscillations
     * \note Larger tolerance values reduce adjustment frequency but may allow more brightness variation
     * \note The tolerance creates a deadband around the target to prevent continuous adjustments
     *
     * \see features::AutoTolerance
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::AutoTolerance& AutoTolerance()
    {
        return m_genericController.AutoTolerance();
    }

    /*!
     * \brief Gets access to the auto percentile feature used for automatic brightness adjustment.
     *
     * Determines the pixel intensity percentile to consider when adjusting
     * exposure or gain. A higher percentile emphasizes brighter regions,
     * while a lower percentile focuses on mid-tones or shadows.
     *
     * Typical range: 0-100.
     *
     * \return Reference to the AutoPercentile feature for configuration
     *
     * \see features::AutoPercentile
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::AutoPercentile& AutoPercentile()
    {
        return m_genericController.AutoPercentile();
    }

    /*!
     * \brief Gets access to the region of interest (ROI) feature for selective brightness analysis.
     *
     * ROI allows the controller to focus brightness analysis on specific areas of the image
     * rather than the entire frame, providing more precise control for specific applications.
     *
     * \return Reference to the Roi feature for configuration
     *
     * \note ROI can be used to focus on subject areas while ignoring background variations
     *
     * \see features::Roi
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::Roi& Roi()
    {
        return m_genericController.Roi();
    }

    /*!
     * \brief Gets access to the brightness algorithm feature for algorithm selection.
     *
     * Brightness algorithm determines the computational method used for brightness
     * analysis and adjustment decisions.
     *
     * \return Reference to the BrightnessAlgorithm feature for configuration
     *
     * \note Different algorithms may be optimized for different scene types or performance requirements
     * \note Some algorithms may be better suited for specific lighting conditions or subject types
     *
     * \see features::BrightnessAlgorithm
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::BrightnessAlgorithm& AnalysisAlgorithm()
    {
        return m_genericController.AnalysisAlgorithm();
    }

    /*!
     * \brief Gets access to the exposure component for exposure time control.
     *
     * The exposure component controls camera exposure time to adjust image brightness.
     * This is typically the primary method for brightness control as it doesn't introduce noise.
     *
     * \return Reference to the exposure BrightnessComponent
     *
     * \throws peak::afl::error::NotSupportedException if exposure component is not supported by the device
     *
     * \note Check HasExposure() before calling to avoid exceptions
     *
     * \see HasExposure()
     * \see BrightnessComponent
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessComponent& Exposure() const
    {
        return m_genericController.ExposureComponent();
    }

    /*!
     * \brief Checks if the exposure component is available on the current device.
     *
     * \return True if exposure control is supported, false otherwise
     *
     * \note Use this before calling Exposure() to avoid exceptions
     * \note Availability depends on the underlying device capabilities
     *
     * \see Exposure()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasExposure() const
    {
        return m_genericController.HasExposureComponent();
    }

    /*!
     * \brief Gets access to the analog gain component for sensor-level gain control.
     *
     * The analog gain component controls sensor-level amplification before digitization.
     * This provides brightness increase with better noise characteristics than digital gain.
     *
     * \return Reference to the analog gain BrightnessComponent
     *
     * \throws peak::afl::error::NotSupportedException if analog gain component is not supported by the device
     *
     * \note Check HasAnalogGain() before calling to avoid exceptions
     * \note Analog gain affects noise characteristics less than digital gain
     * \note Higher analog gain values may introduce some noise but less than digital gain
     *
     * \see HasAnalogGain()
     * \see BrightnessComponent
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessComponent& AnalogGain() const
    {
        return m_genericController.AnalogGainComponent();
    }

    /*!
     * \brief Checks if the analog gain component is available on the current device.
     *
     * \return True if analog gain control is supported, false otherwise
     *
     * \note Use this before calling AnalogGain() to avoid exceptions
     * \note Availability depends on the underlying device capabilities
     *
     * \see AnalogGain()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasAnalogGain() const
    {
        return m_genericController.HasAnalogGainComponent();
    }

    /*!
     * \brief Gets access to the digital gain component for post-processing gain control.
     *
     * The digital gain component controls post-digitization amplification.
     * This provides brightness increase but may introduce more noise than analog methods.
     *
     * \return Reference to the digital gain BrightnessComponent
     *
     * \throws peak::afl::error::NotSupportedException if digital gain component is not supported by the device
     *
     * \note Check HasDigitalGain() before calling to avoid exceptions
     * \note Digital gain may introduce more noise than exposure or analog gain
     * \note Digital gain is applied after analog-to-digital conversion
     *
     * \see HasDigitalGain()
     * \see BrightnessComponent
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessComponent& DigitalGain() const
    {
        return m_genericController.DigitalGainComponent();
    }

    /*!
     * \brief Checks if the digital gain component is available on the current device.
     *
     * \return True if digital gain control is supported, false otherwise
     *
     * \note Use this before calling DigitalGain() to avoid exceptions
     * \note Availability depends on the underlying device capabilities
     *
     * \see DigitalGain()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasDigitalGain() const
    {
        return m_genericController.HasDigitalGainComponent();
    }

    /*!
     * \brief Gets access to the combined gain component for unified gain control.
     *
     * The combined gain component provides a unified interface for both analog and
     * digital gain control, automatically selecting the optimal combination.
     *
     * \return Reference to the combined gain BrightnessComponent
     *
     * \throws peak::afl::error::NotSupportedException if combined gain component is not supported by the device
     *
     * \note Check HasCombinedGain() before calling to avoid exceptions
     * \note Combined gain automatically optimizes between analog and digital gain
     * \note The controller will prefer analog gain over digital gain when possible
     *
     * \see HasCombinedGain()
     * \see BrightnessComponent
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessComponent& CombinedGain() const
    {
        return m_genericController.CombinedGainComponent();
    }

    /*!
     * \brief Checks if the combined gain component is available on the current device.
     *
     * \return True if combined gain control is supported, false otherwise
     *
     * \note Use this before calling CombinedGain() to avoid exceptions
     * \note Availability depends on the underlying device capabilities
     *
     * \see CombinedGain()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasCombinedGain() const
    {
        return m_genericController.HasCombinedGainComponent();
    }

    /*!
     * \brief Gets access to the host gain component for software-based gain control.
     *
     * The host gain component controls software-based gain adjustment performed
     * on the host system after image acquisition.
     *
     * \return Reference to the host gain BrightnessComponent
     *
     * \throws peak::afl::error::NotSupportedException if host gain component is not supported by the device
     *
     * \note Check HasHostGain() before calling to avoid exceptions
     * \note Host gain processing may impact performance and introduce processing delays
     * \note Host gain is applied in software after image transfer from the device
     *
     * \see HasHostGain()
     * \see BrightnessComponent
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessComponent& HostGain() const
    {
        return m_genericController.HostGainComponent();
    }

    /*!
     * \brief Checks if the host gain component is available on the current device.
     *
     * \return True if host gain control is supported, false otherwise
     *
     * \note Use this before calling HostGain() to avoid exceptions
     * \note Availability depends on the underlying device capabilities
     *
     * \see HostGain()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool HasHostGain() const
    {
        return m_genericController.HasHostGainComponent();
    }

    /*!
     * \brief Gets a vector of all available brightness components.
     *
     * Returns pointers to all brightness components that are supported and available
     * on the current device configuration.
     *
     * \return Vector of pointers to available BrightnessComponent instances
     *
     * \note The returned vector only contains components that are actually available
     * \note Use this for iterating over all available brightness adjustment methods
     * \note The order of components in the vector is not guaranteed
     *
     * \see GetComponent()
     * \see BrightnessComponent
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::vector<BrightnessComponent*> GetComponents() const
    {
        return m_genericController.GetComponents();
    }

    /*!
     * \brief Gets a specific brightness component by type.
     *
     * \param componentType The type of brightness component to retrieve
     * \return Pointer to the requested BrightnessComponent, or nullptr if not available
     *
     * \note Check for nullptr return value before using the component
     * \note This provides type-safe access to specific component types
     * \note Null return indicates the component is not supported on this device
     *
     * \see GetComponents()
     * \see BrightnessComponentType
     * \see BrightnessComponent
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessComponent* GetComponent(BrightnessComponentType componentType) const
    {
        return m_genericController.GetComponent(componentType);
    }

    /*!
     * \brief Resets all controller settings and components to their default values.
     *
     * This will restore:
     * - Default operation mode (typically Off)
     * - Default algorithm settings
     * - Default target brightness and tolerance
     * - Default component configurations
     * - Default ROI and percentile settings
     * - Default feature configurations
     *
     * \note This operation cannot be undone
     * \note Default values are device-specific and may vary between implementations
     * \note Component states are reset but availability is not changed
     *
     * \see SetMode()
     * \since 1.8
     */
    void ResetToDefault() override
    {
        m_genericController.ResetToDefault();
    }

    /*!
     * \brief Registers a callback function to be invoked when brightness adjustment completes.
     *
     * The callback will be called asynchronously when the brightness controller
     * finishes processing a frame and applying adjustments.
     *
     * \param callback The callback function to register for completion notification
     * \return Handle that can be used to unregister the callback later
     *
     * \note Multiple callbacks can be registered simultaneously
     * \note Callbacks are invoked asynchronously and should be thread-safe
     *
     * \see UnregisterFinishedCallback()
     * \see IController::FinishedCallback
     * \since 1.8
     */
    IController::FinishedCallbackHandle RegisterFinishedCallback(const IController::FinishedCallback& callback)
    {
        return m_genericController.RegisterFinishedCallback(callback);
    }

    /*!
     * \brief Unregisters a previously registered completion callback.
     *
     * \param callbackHandle Handle returned from RegisterFinishedCallback() for the callback to remove
     *
     * \note Invalid handles are ignored safely
     * \note Unregistering a callback that's currently executing is safe
     * \note After unregistering, the callback will no longer be invoked
     *
     * \see RegisterFinishedCallback()
     * \since 1.8
     */
    void UnregisterFinishedCallback(IController::FinishedCallbackHandle callbackHandle)
    {
        m_genericController.UnregisterFinishedCallback(callbackHandle);
    }

private:
    detail::GenericAutoBrightness m_genericController; ///< Internal generic controller implementation
};

} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
