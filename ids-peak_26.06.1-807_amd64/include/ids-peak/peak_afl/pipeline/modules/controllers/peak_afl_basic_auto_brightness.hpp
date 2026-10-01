/*!
 * \file    peak_afl_basic_auto_brightness.hpp
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
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_roi.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/exceptions/peak_common_exceptions.hpp>

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
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Auto brightness control policy enumeration
 *
 * Defines the different strategies for automatic brightness control,
 * determining which camera parameters the controller is allowed to adjust
 * to achieve the target brightness level.
 *
 * \since 1.8
 */
enum class AutoBrightnessPolicy
{
    /*! \brief Use both exposure time and gain adjustments for optimal brightness control */
    ExposureAndGain,
    /*! \brief Use only exposure time adjustments, keeping gain constant */
    ExposureOnly,
    /*! \brief Use only gain adjustments, keeping exposure time constant */
    GainOnly
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Converts AutoBrightnessPolicy enumeration to string representation
 *
 * \param[in] policy The auto brightness policy to convert
 * \return String representation of the policy
 * \throws peak::afl::error::InvalidParameterException if policy is unknown
 *
 * \see AutoBrightnessPolicy
 *
 * \since 1.8
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(AutoBrightnessPolicy policy)
{
    switch (policy)
    {
    case AutoBrightnessPolicy::ExposureAndGain:
        return "ExposureAndGain";
    case AutoBrightnessPolicy::ExposureOnly:
        return "ExposureOnly";
    case AutoBrightnessPolicy::GainOnly:
        return "GainOnly";
    }

    throw peak::afl::error::InvalidParameterException("The given policy is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

inline std::ostream& operator<<(std::ostream& os, AutoBrightnessPolicy policy)
{
    return os << ToString(policy);
}

namespace detail
{

PEAK_COMMON_NO_DISCARD inline AutoBrightnessPolicy ToAutoBrightnessPolicy(const std::string& name)
{
    if (name == "ExposureAndGain")
    {
        return AutoBrightnessPolicy::ExposureAndGain;
    }
    if (name == "ExposureOnly")
    {
        return AutoBrightnessPolicy::ExposureOnly;
    }
    if (name == "GainOnly")
    {
        return AutoBrightnessPolicy::GainOnly;
    }

    throw peak::afl::error::InternalErrorException("Invalid brightness policy!", PEAK_AFL_STATUS_ERROR);
}
} // namespace detail
/*!
 * \ingroup ids_peak_afl_pipeline_controller
 * \brief Basic automatic brightness controller implementation
 *
 * The BasicAutoBrightness class provides a streamlined interface for automatic
 * brightness control. This controller offers essential
 * brightness adjustment capabilities through exposure and gain control with
 * simplified configuration options suitable for most standard use cases.
 *
 * **Key Features:**
 * - **Dual adjustment mechanisms**: Exposure time and gain control
 * - **Policy-based control**: Configurable parameter adjustment strategies
 * - **Component architecture**: Individual control over exposure and gain components
 * - **ROI support**: Region-of-interest based brightness analysis
 * - **Target-based control**: Automatic adjustment to achieve target brightness levels
 * - **Tolerance management**: Configurable acceptable deviation from target
 * - **Callback notifications**: Asynchronous operation completion events
 * - **Serialization support**: Configuration persistence and restoration
 *
 * **Control Policies:**
 * - **ExposureAndGain**: Optimal brightness using both exposure and gain (recommended)
 * - **ExposureOnly**: Brightness control via exposure time only (constant gain)
 * - **GainOnly**: Brightness control via gain only (constant exposure)
 *
 * \note This controller requires a valid manager instance for camera communication
 * \note Component availability depends on underlying device capabilities
 * \note For advanced features like custom components use AdvancedAutoBrightness
 *
 * \see AdvancedAutoBrightness
 * \see AutoBrightnessPolicy
 * \see detail::IController
 * \see BrightnessComponent
 *
 * \since 1.8
 */
class BasicAutoBrightness : public detail::IController
{
    using ProcessingCallback = std::function<void()>;

public:
    friend BrightnessComponent;

    /*!
     * \brief Constructs a BasicAutoBrightness controller with the specified manager and callback.
     *
     * Initializes the brightness controller with exposure and gain components.
     * The controller will automatically detect which components are supported by the device.
     *
     * \param manager Reference to the API manager for device communication
     * \param callback Processing callback function that will be invoked when brightness adjustment completes
     *
     * \note The callback will be called asynchronously when processing finishes
     * \note Only exposure and gain components are supported in this basic implementation
     * \note The callback function should be thread-safe as it may be called from different threads
     *
     * \see BrightnessComponentType
     * \since 1.8
     */
    explicit BasicAutoBrightness(peak::afl::Manager& manager, ProcessingCallback callback)
        : IController(manager)
        , m_genericController{ manager, std::move(callback), { BrightnessComponentType::Exposure, BrightnessComponentType::Gain } }
    {}

    /*!
     * \brief Destructor for BasicAutoBrightness.
     *
     * Cleans up resources and ensures proper shutdown of the controller.
     * \since 1.8
     */
    ~BasicAutoBrightness() override = default;

    /*!
     * \brief Sets the operation mode for the brightness controller.
     *
     * The mode is applied to individual components based on the current policy:
     * - ExposureOnly: Mode is applied to exposure component only
     * - GainOnly: Mode is applied to gain component only
     * - ExposureAndGain: Mode is applied to both components
     *
     * \param mode The controller mode to set (Off, Auto, Manual, etc.)
     *
     * \note Setting mode to Off will disable automatic brightness adjustment
     * \note Mode changes are filtered through the current policy settings
     * \note The mode is cached and reapplied when the policy changes
     *
     * \see GetMode()
     * \see SetPolicy()
     * \see ControllerMode
     * \since 1.8
     */
    void SetMode(ControllerMode mode) override
    {
        auto* exposureComponent = GetExposureComponent();
        if (exposureComponent != nullptr)
        {
            const auto controllerMode = (m_policy == AutoBrightnessPolicy::ExposureOnly
                                            || m_policy == AutoBrightnessPolicy::ExposureAndGain) ?
                mode :
                ControllerMode::Off;

            exposureComponent->SetMode(controllerMode);
        }

        auto* gainComponent = GetGainComponent();
        if (gainComponent != nullptr)
        {
            const auto controllerMode = (m_policy == AutoBrightnessPolicy::GainOnly || m_policy == AutoBrightnessPolicy::ExposureAndGain) ?
                mode :
                ControllerMode::Off;

            gainComponent->SetMode(controllerMode);
        }

        m_cachedMode = mode;
    }

    /*!
     * \brief Gets the current operation mode of the brightness controller.
     *
     * The returned mode reflects the actual state of the active components:
     * - Returns Continuous if exposure component is in Continuous mode
     * - Otherwise returns the gain component mode
     * - Returns Off if no components are active
     *
     * \return Current ControllerMode based on active component states
     *
     * \note The mode reflects the actual component states, not the cached mode
     * \note Exposure component mode takes precedence over gain component mode
     *
     * \see SetMode()
     * \see ControllerMode
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const override
    {
        auto* const exposureComponent = GetExposureComponent();
        if (exposureComponent != nullptr)
        {
            if (exposureComponent->GetMode() == ControllerMode::Continuous)
            {
                return ControllerMode::Continuous;
            }
        }

        auto* const gainComponent = GetGainComponent();
        if (gainComponent != nullptr)
        {
            return gainComponent->GetMode();
        }

        return ControllerMode::Off;
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
        return GetMode() != ControllerMode::Off;
    }

    /*!
     * \brief Sets the brightness analysis algorithm.
     *
     * Determines the computational method used for brightness analysis and adjustment decisions.
     *
     * \param algorithm The brightness analysis algorithm to use
     *
     * \note Different algorithms may be optimized for different scene types or performance requirements
     * \note Algorithm availability depends on the device and implementation capabilities
     *
     * \see GetAnalysisAlgorithm()
     * \see BrightnessAnalysisAlgorithm
     * \since 1.8
     */
    void SetAnalysisAlgorithm(BrightnessAnalysisAlgorithm algorithm)
    {
        m_genericController.AnalysisAlgorithm().Set(algorithm);
    }

    /*!
     * \brief Gets the current brightness analysis algorithm.
     *
     * \return The currently configured brightness analysis algorithm
     *
     * \note This returns the algorithm setting, not the actual algorithm being used
     *
     * \see SetAnalysisAlgorithm()
     * \see BrightnessAnalysisAlgorithm
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessAnalysisAlgorithm GetAnalysisAlgorithm() const
    {
        return m_genericController.AnalysisAlgorithm().Get();
    }

    /*!
     * \brief Sets the percentile value for brightness calculation.
     *
     * Determines which portion of the image histogram is used for brightness calculations,
     * allowing for robust brightness estimation in various lighting conditions.
     *
     * \param value The percentile value to use (typically 0.0 to 1.0)
     *
     * \note Common percentile values: 0.5 (median), 0.9 (avoiding shadows), 0.1 (avoiding highlights)
     * \note Higher percentiles focus on brighter areas, lower percentiles on darker areas
     *
     * \see GetAutoPercentile()
     * \see GetAutoPercentileRange()
     * \since 1.8
     */
    void SetAutoPercentile(double value)
    {
        m_genericController.AutoPercentile().Set(value);
    }

    /*!
     * \brief Gets the current percentile value for brightness calculation.
     *
     * \return The currently configured percentile value
     *
     * \note The percentile determines which part of the histogram is used for brightness analysis
     *
     * \see SetAutoPercentile()
     * \see GetAutoPercentileRange()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD double GetAutoPercentile() const
    {
        return m_genericController.AutoPercentile().Get();
    }

    /*!
     * \brief Gets the valid range for percentile values.
     *
     * \return Range of valid percentile values supported by the device
     *
     * \note Use this to validate percentile values before setting them
     *
     * \see SetAutoPercentile()
     * \see RangeD
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD RangeD GetAutoPercentileRange() const
    {
        return m_genericController.AutoPercentile().GetRange();
    }

    /*!
     * \brief Sets the target brightness value.
     *
     * Defines the desired brightness level that the controller will attempt to achieve
     * through automatic adjustments.
     *
     * \param value The target brightness value in device-specific units
     *
     * \note Target values are typically in device-specific units (e.g., 0-255 for 8-bit)
     * \note Optimal target values depend on the specific application and scene conditions
     *
     * \see GetAutoTarget()
     * \see GetAutoTargetRange()
     * \since 1.8
     */
    void SetAutoTarget(uint32_t value)
    {
        m_genericController.AutoTarget().Set(value);
    }

    /*!
     * \brief Gets the current target brightness value.
     *
     * \return The currently configured target brightness value
     *
     * \note This represents the desired brightness level for the analyzed region
     *
     * \see SetAutoTarget()
     * \see GetAutoTargetRange()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetAutoTarget() const
    {
        return m_genericController.AutoTarget().Get();
    }

    /*!
     * \brief Gets the valid range for target brightness values.
     *
     * \return Range of valid target brightness values supported by the device
     *
     * \note Use this to validate target values before setting them
     *
     * \see SetAutoTarget()
     * \see peak::common::RangeU
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU GetAutoTargetRange() const
    {
        return m_genericController.AutoTarget().GetRange();
    }

    /*!
     * \brief Sets the tolerance value for brightness stability control.
     *
     * Defines the acceptable deviation from the target brightness before the controller
     * triggers adjustment actions.
     *
     * \param value The tolerance value in device-specific units
     *
     * \note Smaller tolerance values provide more stable brightness but may cause oscillations
     * \note Larger tolerance values reduce adjustment frequency but may allow more brightness variation
     * \note The tolerance creates a deadband around the target to prevent continuous adjustments
     *
     * \see GetAutoTolerance()
     * \see GetAutoToleranceRange()
     * \since 1.8
     */
    void SetAutoTolerance(uint32_t value)
    {
        m_genericController.AutoTolerance().Set(value);
    }

    /*!
     * \brief Gets the current tolerance value for brightness stability control.
     *
     * \return The currently configured tolerance value
     *
     * \note This represents the acceptable deviation from the target brightness
     *
     * \see SetAutoTolerance()
     * \see GetAutoToleranceRange()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetAutoTolerance() const
    {
        return m_genericController.AutoTolerance().Get();
    }

    /*!
     * \brief Gets the valid range for tolerance values.
     *
     * \return Range of valid tolerance values supported by the device
     *
     * \note Use this to validate tolerance values before setting them
     *
     * \see SetAutoTolerance()
     * \see peak::common::RangeU
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU GetAutoToleranceRange() const
    {
        return m_genericController.AutoTolerance().GetRange();
    }

    /*!
     * \brief Sets the number of frames to skip for performance optimization.
     *
     * Skip frames allows the controller to process only every Nth frame instead of
     * every frame, reducing computational load while maintaining brightness control.
     *
     * \param value The number of frames to skip (0 means process every frame)
     *
     * \note Higher skip frame values reduce CPU usage but may decrease responsiveness
     * \note A value of 0 means process every frame (maximum responsiveness)
     * \note A value of 1 means process every other frame
     *
     * \see GetSkipFrames()
     * \see GetSkipFramesRange()
     * \since 1.8
     */
    void SetSkipFrames(uint32_t value)
    {
        m_genericController.SkipFrames().Set(value);
    }

    /*!
     * \brief Gets the current number of frames to skip.
     *
     * \return The currently configured skip frames value
     *
     * \note This affects the processing frequency and system performance
     *
     * \see SetSkipFrames()
     * \see GetSkipFramesRange()
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetSkipFrames() const
    {
        return m_genericController.SkipFrames().Get();
    }

    /*!
     * \brief Gets the valid range for skip frames values.
     *
     * \return Range of valid skip frames values supported by the device
     *
     * \note Use this to validate skip frames values before setting them
     *
     * \see SetSkipFrames()
     * \see peak::common::RangeU
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU GetSkipFramesRange() const
    {
        return m_genericController.SkipFrames().GetRange();
    }

    /*!
     * \brief Sets the region of interest (ROI) for selective brightness analysis.
     *
     * Allows the controller to focus brightness analysis on specific areas of the image
     * rather than the entire frame, providing more precise control for specific applications.
     *
     * \param roi The rectangular region of interest to analyze
     *
     * \note ROI coordinates are typically normalized or in pixel coordinates
     * \note ROI can be used to focus on subject areas while ignoring background variations
     *
     * \see GetRoi()
     * \see peak::common::Rectangle
     * \since 1.8
     */
    void SetRoi(const peak::common::Rectangle& roi)
    {
        m_genericController.Roi().Set(roi);
    }

    /*!
     * \brief Gets the current region of interest (ROI) for brightness analysis.
     *
     * \return The currently configured rectangular region of interest
     *
     * \note The ROI defines the area used for brightness calculations
     *
     * \see SetRoi()
     * \see peak::common::Rectangle
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::Rectangle GetRoi()
    {
        return m_genericController.Roi().Get();
    }

    /*!
     * \brief Sets the brightness adjustment policy.
     *
     * Determines which components are used for brightness adjustment:
     * - ExposureOnly: Uses only exposure time adjustment
     * - GainOnly: Uses only gain adjustment
     * - ExposureAndGain: Uses both exposure and gain adjustment
     *
     * \param policy The brightness adjustment policy to use
     *
     * \note Policy changes immediately affect which components are active
     * \note The cached mode is reapplied when the policy changes
     *
     * \see GetPolicy()
     * \see AutoBrightnessPolicy
     * \since 1.8
     */
    void SetPolicy(AutoBrightnessPolicy policy)
    {
        m_policy = policy;
        SetMode(m_cachedMode);
    }

    /*!
     * \brief Gets the current brightness adjustment policy.
     *
     * \return The currently configured brightness adjustment policy
     *
     * \note This determines which components are used for brightness adjustment
     *
     * \see SetPolicy()
     * \see AutoBrightnessPolicy
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD AutoBrightnessPolicy GetPolicy() const
    {
        return m_policy;
    }

    /*!
     * \brief Resets all controller settings to their default values.
     *
     * This will restore:
     * - Default policy (ExposureAndGain)
     * - Default operation mode (Off)
     * - Default algorithm settings
     * - Default target brightness and tolerance
     * - Default component configurations
     *
     * \note This operation cannot be undone
     * \note Default values are device-specific and may vary between implementations
     *
     * \see SetPolicy()
     * \see SetMode()
     * \since 1.8
     */
    void ResetToDefault() override
    {
        m_policy = AutoBrightnessPolicy::ExposureAndGain;
        m_cachedMode = ControllerMode::Off;
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
     * \note The callback will be called for each processed frame
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

    /*!
     * \brief Sets the exposure time limits for the exposure component.
     *
     * Defines the minimum and maximum exposure time values that the controller
     * is allowed to use during automatic brightness adjustment.
     *
     * \param interval The interval defining the minimum and maximum exposure limits
     *
     * \throws peak::afl::error::NotSupportedException if exposure component is not available
     *
     * \note Exposure limits prevent the controller from using extreme values
     * \note Limits help maintain acceptable motion blur characteristics
     *
     * \see GetExposureLimit()
     * \see peak::common::detail::IntervalT
     * \since 1.8
     */
    void SetExposureLimit(const IntervalD& interval)
    {
        auto* component = GetExposureComponent();
        if (component == nullptr)
        {
            throw peak::afl::error::NotSupportedException(
                "Exposure component is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
        }

        component->SetLimit(interval);
    }

    /*!
     * \brief Gets the current exposure time limits for the exposure component.
     *
     * \return The currently configured exposure time limits
     *
     * \throws peak::afl::error::NotSupportedException if exposure component is not available
     *
     * \note Returns the interval defining the minimum and maximum exposure limits
     *
     * \see SetExposureLimit()
     * \see peak::common::detail::IntervalT
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD IntervalD GetExposureLimit() const
    {
        auto* component = GetExposureComponent();
        if (component != nullptr)
        {
            return component->GetLimit();
        }

        throw peak::afl::error::NotSupportedException(
            "Exposure component is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

    /*!
     * \brief Sets the gain limits for the gain component.
     *
     * Defines the minimum and maximum gain values that the controller
     * is allowed to use during automatic brightness adjustment.
     *
     * \param interval The interval defining the minimum and maximum gain limits
     *
     * \throws peak::afl::error::NotSupportedException if gain component is not available
     *
     * \note Gain limits prevent the controller from using extreme values
     * \note Limits help maintain acceptable noise characteristics
     *
     * \see GetGainLimit()
     * \see peak::common::detail::IntervalT
     * \since 1.8
     */
    void SetGainLimit(const IntervalD& interval)
    {
        auto* component = GetGainComponent();
        if (component == nullptr)
        {
            throw peak::afl::error::NotSupportedException(
                "Gain component is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
        }

        component->SetLimit(interval);
    }

    /*!
     * \brief Gets the current gain limits for the gain component.
     *
     * \return The currently configured gain limits
     *
     * \throws peak::afl::error::NotSupportedException if gain component is not available
     *
     * \note Returns the interval defining the minimum and maximum gain limits
     *
     * \see SetGainLimit()
     * \see peak::common::detail::IntervalT
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD IntervalD GetGainLimit() const
    {
        auto* component = GetGainComponent();
        if (component != nullptr)
        {
            return component->GetLimit();
        }

        throw peak::afl::error::NotSupportedException(
            "Gain component is not supported for the current device!", PEAK_AFL_STATUS_NOT_SUPPORTED);
    }

private:
    AutoBrightnessPolicy m_policy{ AutoBrightnessPolicy::ExposureAndGain }; ///< Current brightness adjustment policy
    detail::GenericAutoBrightness m_genericController; ///< Internal generic controller implementation
    ControllerMode m_cachedMode{ ControllerMode::Off }; ///< Cached mode for policy changes

    /*!
     * \brief Gets the exposure component from the generic controller.
     *
     * \return Pointer to the exposure component, or nullptr if not available
     *
     * \note This is a convenience method for internal use
     * \note Check for nullptr before using the returned pointer
     */
    BrightnessComponent* GetExposureComponent() const
    {
        return m_genericController.GetComponent(BrightnessComponentType::Exposure);
    }

    /*!
     * \brief Gets the gain component from the generic controller.
     *
     * \return Pointer to the gain component, or nullptr if not available
     *
     * \note This is a convenience method for internal use
     * \note Check for nullptr before using the returned pointer
     */
    BrightnessComponent* GetGainComponent() const
    {
        return m_genericController.GetComponent(BrightnessComponentType::Gain);
    }

    /*!
     * \brief Gets the name identifier for this controller.
     *
     * \return String "BasicAutoBrightness" identifying this controller type
     *
     * \note Used for debugging, logging, and identification purposes
     * \note This name is used in serialization and logging systems
     */
    PEAK_COMMON_NO_DISCARD std::string GetName() const override
    {
        return "BasicAutoBrightness";
    }

    /*!
     * \brief Serializes the current controller state and configuration to an archive.
     *
     * Saves all controller settings including policy, mode, and component configurations.
     *
     * \param archive Reference to the archive where the serialized data will be stored
     *
     * \note This method is const as it doesn't modify the controller state
     * \note The policy and cached mode are handled separately from the generic controller
     *
     * \see Deserialize()
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        m_genericController.Serialize(archive);

        archive.SetString("Policy", ToString(m_policy));
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
     * \note Policy and cached mode restoration should be handled separately
     *
     * \see Serialize()
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        m_genericController.Deserialize(archive);

        m_cachedMode = GetMode();
        SetPolicy(detail::ToAutoBrightnessPolicy(archive.GetString("Policy")));
    }

    /*!
     * \brief Gets the controller type identifier.
     *
     * \return ControllerType::Brightness identifying this as a brightness controller
     *
     * \note Used for type identification and controller management
     * \note This enables runtime type checking and proper controller categorization
     */
    PEAK_COMMON_NO_DISCARD ControllerType GetType() const override
    {
        return m_genericController.GetType();
    }
};

} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
