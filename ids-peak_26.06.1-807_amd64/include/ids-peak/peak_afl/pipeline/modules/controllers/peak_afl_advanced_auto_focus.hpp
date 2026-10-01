/*!
 * \file    peak_afl_advanced_auto_focus.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/peak_afl.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_generic_auto_focus.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_icontroller.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_focus_limit.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_hysteresis.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_search_algorithm.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_sharpness_algorithm.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_weighted_rois.hpp>

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
 * \ingroup ids_peak_afl_pipeline_controller
 * \brief Advanced automatic focus controller with comprehensive feature set
 *
 * The AdvancedAutoFocus class provides a sophisticated and highly configurable
 * interface for automatic focus control.
 * This controller offers the complete focus feature set with granular control
 * over all focusing mechanisms and algorithmic options.
 *
 * **Advanced Features:**
 * - **Comprehensive algorithm suite**: All search and sharpness algorithms with fine-tuning
 * - **Advanced ROI management**: Complex weighted region configurations
 * - **Precision control**: Granular focus limits and hysteresis settings
 * - **Callback architecture**: Comprehensive event notification system
 * - **Full serialization**: Complete configuration state management
 * - **Processing notifications**: Real-time focus operation feedback
 *
 * **Focus Search Algorithms:**
 * - **Auto Selection**: Intelligent algorithm choice based on scene analysis
 * - **Golden Ratio Search**: Optimized for smooth, predictable focus curves
 * - **Hill Climbing**: Fast convergence for time-critical applications
 * - **Global Search**: Maximum accuracy for challenging focus conditions
 * - **Full Scan**: Complete range analysis for precision applications
 *
 * **Focus Sharpness Analysis:**
 * - **Tenengrad**: High-precision gradient analysis for technical imaging
 * - **Sobel**: Robust edge detection for varied lighting conditions
 * - **Mean Score**: Statistical analysis for textured or patterned subjects
 * - **Histogram Variance**: Optimal for uniform illumination scenarios
 * - **Auto Selection**: Scene-adaptive sharpness measurement
 *
 * \note This controller requires a valid manager instance for camera communication
 * \note Advanced features may require specific hardware capabilities
 * \note For simplified usage, consider BasicAutoFocus instead
 *
 * \see BasicAutoFocus
 * \see FocusSearchAlgorithm
 * \see FocusSharpnessAlgorithm
 * \see WeightedROI
 * \see detail::IController
 *
 * \since 1.8
 */
class AdvancedAutoFocus : public detail::IController
{
public:
    /*!
     * \brief Constructs an AdvancedAutoFocus instance
     *
     * \param manager Reference to the API manager that handles controller lifecycle
     *
     * Initializes the focus controller with the specified manager. The controller
     * will be ready to perform automatic focus operations once configured and activated.
     * \since 1.8
     */
    explicit AdvancedAutoFocus(peak::afl::Manager& manager)
        : IController(manager)
        , m_genericController(manager)
    {}

    /*!
     * \brief Destructor
     *
     * Default destructor that properly cleans up controller resources.
     */
    ~AdvancedAutoFocus() override = default;

    /*!
     * \brief Gets the controller name
     *
     * \return std::string The name identifier for this controller ("AdvancedAutoFocus")
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::string GetName() const override
    {
        return "AdvancedAutoFocus";
    }

    /*!
     * \brief Serializes the controller configuration to an archive
     *
     * \param archive Reference to the serialization archive for writing configuration data
     *
     * Saves the current controller configuration state to the provided archive.
     * This includes all focus algorithm settings, ROI configurations, and other
     * controller parameters for later restoration.
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        m_genericController.Serialize(archive);
    }

    /*!
     * \brief Deserializes the controller configuration from an archive
     *
     * \param archive Reference to the serialization archive containing configuration data
     *
     * Restores the controller configuration state from the provided archive.
     * This allows previously saved focus controller settings to be loaded and applied.
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        m_genericController.Deserialize(archive);
    }

    /*!
     * \brief Sets the controller operation mode
     *
     * \param mode The desired controller operation mode
     *
     * Changes the controller's operation mode, which determines how the automatic focus
     * behaves. Different modes may include continuous auto-focus, single-shot focus,
     * or manual override modes.
     * \since 1.8
     */
    void SetMode(ControllerMode mode) override
    {
        m_genericController.SetMode(mode);
    }

    /*!
     * \brief Gets the current controller operation mode
     *
     * \return ControllerMode The current operation mode of the controller
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const override
    {
        return m_genericController.GetMode();
    }

    /*!
     * \brief Checks if the controller is currently running
     *
     * \return bool True if the controller is active (not in Off mode), false otherwise
     *
     * A controller is considered running when it's not in the Off mode.
     * This indicates whether the automatic focus processing is currently active.
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool IsRunning() const override
    {
        return m_genericController.IsRunning();
    }

    /*!
     * \brief Resets the controller to its default configuration
     *
     * Restores all controller settings to their default values.
     * This includes resetting operation mode, focus algorithms, ROI settings,
     * and other configuration parameters to factory defaults.
     * \since 1.8
     */
    void ResetToDefault() override
    {
        m_genericController.ResetToDefault();
    }

    /*!
     * \brief Gets the skip frames feature controller
     *
     * \return features::SkipFrames& Reference to the skip frames feature controller
     *
     * The skip frames feature allows the controller to process only every Nth frame,
     * which can improve performance when full-rate focus evaluation is not required.
     * This is particularly useful for reducing computational load in high frame rate scenarios.
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::SkipFrames& SkipFrames() const
    {
        return m_genericController.SkipFrames();
    }

    /*!
     * \brief Gets the hysteresis feature controller
     *
     * \return features::Hysteresis& Reference to the hysteresis feature controller
     *
     * The hysteresis feature prevents focus hunting by adding stability to focus decisions.
     * It requires a minimum change in focus quality before triggering a focus adjustment,
     * reducing oscillation around the optimal focus position.
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::Hysteresis& Hysteresis() const
    {
        return m_genericController.Hysteresis();
    }

    /*!
     * \brief Gets the weighted regions of interest feature controller
     *
     * \return features::WeightedRois& Reference to the weighted ROIs feature controller
     *
     * The weighted ROIs feature allows defining multiple rectangular regions within the image
     * with different importance weights for focus evaluation. This enables prioritizing
     * focus on specific areas of the scene while still considering the overall image.
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::WeightedRois& WeightedROIs() const
    {
        return m_genericController.WeightedROIs();
    }

    /*!
     * \brief Gets the sharpness algorithm feature controller
     *
     * \return features::SharpnessAlgorithm& Reference to the sharpness algorithm feature controller
     *
     * The sharpness algorithm feature controls how image sharpness is evaluated.
     * Different algorithms may use gradient-based methods, variance calculations,
     * or frequency domain analysis to determine focus quality.
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::SharpnessAlgorithm& SharpnessAlgorithm() const
    {
        return m_genericController.SharpnessAlgorithm();
    }

    /*!
     * \brief Gets the search algorithm feature controller
     *
     * \return features::SearchAlgorithm& Reference to the search algorithm feature controller
     *
     * The search algorithm feature controls how the focus position is adjusted to find
     * the optimal focus. Different algorithms may use hill-climbing, binary search,
     * or other optimization strategies to efficiently locate the best focus position.
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::SearchAlgorithm& SearchAlgorithm() const
    {
        return m_genericController.SearchAlgorithm();
    }

    /*!
     * \brief Gets the focus limit feature controller
     *
     * \return features::FocusLimit& Reference to the focus limit feature controller
     *
     * The focus limit feature defines the minimum and maximum focus positions that
     * the controller is allowed to use. This prevents the focus system from searching
     * beyond physically meaningful or optically useful ranges.
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::FocusLimit& FocusLimit() const
    {
        return m_genericController.FocusLimit();
    }

    /*!
     * \brief Gets the controller type identifier
     *
     * \return ControllerType The type identifier for this controller (ControllerType::Focus)
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD ControllerType GetType() const override
    {
        return m_genericController.GetType();
    }

    /*!
     * \brief Registers a callback for processing completion notifications
     *
     * \param callback The callback function to register
     * \return IController::FinishedCallbackHandle Handle for the registered callback
     *
     * Registers a callback function that will be invoked when focus operations complete.
     * This includes both successful focus acquisitions and focus search failures.
     * The returned handle can be used to unregister the callback later.
     * \since 1.8
     */
    IController::FinishedCallbackHandle RegisterFinishedCallback(const IController::FinishedCallback& callback)
    {
        return m_genericController.RegisterFinishedCallback(callback);
    }

    /*!
     * \brief Unregisters a previously registered callback
     *
     * \param callbackHandle Handle of the callback to unregister
     *
     * Removes a previously registered callback using its handle.
     * After unregistration, the callback will no longer be invoked for focus events.
     * \since 1.8
     */
    void UnregisterFinishedCallback(IController::FinishedCallbackHandle callbackHandle)
    {
        m_genericController.UnregisterFinishedCallback(callbackHandle);
    }

private:
    /*!
     * \brief Internal generic auto-focus controller implementation
     *
     * The actual focus control logic is delegated to this generic controller instance.
     * This provides a clean separation between the public interface and the internal
     * implementation details.
     */
    detail::GenericAutoFocus m_genericController;
};

} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
