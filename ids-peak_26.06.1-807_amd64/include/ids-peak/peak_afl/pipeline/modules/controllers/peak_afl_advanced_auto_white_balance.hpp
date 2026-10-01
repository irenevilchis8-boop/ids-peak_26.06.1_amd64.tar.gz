/*!
 * \file    peak_afl_advanced_auto_white_balance.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/peak_afl.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_generic_auto_white_balance.hpp>
#include <peak_afl/pipeline/modules/controllers/detail/peak_afl_icontroller.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_roi.hpp>

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
 * \brief Advanced automatic white balance controller with comprehensive feature set
 *
 * The AdvancedAutoWhiteBalance class provides a sophisticated and highly configurable
 * interface for automatic white balance control.
 * This controller offers the complete white balance feature set with granular control
 * over all color correction mechanisms and algorithmic options.
 *
 * **Advanced Features:**
 * - **Precision color analysis**: Algorithms for accurate color temperature detection
 * - **Complex ROI management**: Multiple region analysis for challenging lighting scenarios
 * - **Processing callbacks**: Real-time feedback during white balance operations
 * - **Full serialization**: Complete configuration state management
 * - **Controller modes**: Continuous, once, and manual white balance control
 *
 * \note This controller requires a valid manager instance for camera communication
 * \note Advanced features may require specific hardware color processing capabilities
 * \note Processing callback provides real-time operation feedback
 * \note For simplified usage, consider BasicAutoWhiteBalance instead
 *
 * \see BasicAutoWhiteBalance
 * \see detail::IController
 * \see features::Roi
 *
 * \since 1.8
 */
class AdvancedAutoWhiteBalance : public detail::IController
{
    /*!
     * \brief Type alias for processing completion callback functions
     *
     * Callback function type that is invoked when white balance processing operations
     * complete. This callback receives no parameters and returns void.
     * \since 1.8
     */
    using ProcessingCallback = std::function<void()>;

public:
    /*!
     * \brief Constructs an AdvancedAutoWhiteBalance instance
     *
     * \param manager Reference to the API manager that handles controller lifecycle
     * \param callback Processing completion callback function
     *
     * Initializes the white balance controller with the specified manager and callback.
     * The callback will be invoked when white balance processing operations complete.
     * \since 1.8
     */
    explicit AdvancedAutoWhiteBalance(peak::afl::Manager& manager, ProcessingCallback callback)
        : IController(manager)
        , m_genericController(manager, std::move(callback))
    {}

    /*!
     * \brief Destructor
     *
     * Default destructor that properly cleans up controller resources.
     * \since 1.8
     */
    ~AdvancedAutoWhiteBalance() override = default;

    /*!
     * \brief Gets the controller name
     *
     * \return std::string The name identifier for this controller ("AdvancedAutoWhiteBalance")
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::string GetName() const override
    {
        return "AdvancedAutoWhiteBalance";
    }

    /*!
     * \brief Serializes the controller configuration to an archive
     *
     * \param archive Reference to the serialization archive for writing configuration data
     *
     * Saves the current controller configuration state to the provided archive.
     * This includes white balance algorithm settings, ROI configurations, and other
     * controller parameters, allowing the controller settings to be persisted and restored later.
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
     * This allows previously saved white balance controller settings to be loaded and applied.
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
     * Changes the controller's operation mode, which determines how the white balance
     * processing behaves. Different modes may include automatic white balance calculation,
     * manual override, or disabled states.
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
     * This indicates whether the white balance processing is currently active.
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
     * This includes resetting operation mode, white balance algorithm settings,
     * ROI configurations, and other configuration parameters to factory defaults.
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
     * which can improve performance when full-rate white balance processing is not required.
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
     * \brief Gets the region of interest (ROI) feature controller
     *
     * \return features::Roi& Reference to the ROI feature controller
     *
     * The ROI feature allows limiting white balance analysis to a specific
     * rectangular region within the image, which can improve accuracy and performance
     * by focusing the color analysis on the most relevant area of the scene.
     *
     * \note This method is marked as NO_DISCARD to ensure the return value is used
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD features::Roi& Roi() const
    {
        return m_genericController.Roi();
    }

    /*!
     * \brief Gets the controller type identifier
     *
     * \return ControllerType The type identifier for this controller (ControllerType::WhiteBalance)
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
     * Registers a callback function that will be invoked when white balance
     * processing operations complete. This includes both successful white balance
     * adjustments and processing failures. The returned handle can be used to
     * unregister the callback later.
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
     * After unregistration, the callback will no longer be invoked for
     * white balance processing events.
     * \since 1.8
     */
    void UnregisterFinishedCallback(IController::FinishedCallbackHandle callbackHandle)
    {
        m_genericController.UnregisterFinishedCallback(callbackHandle);
    }

private:
    /*!
     * \brief Internal generic white balance controller implementation
     *
     * The actual white balance control logic is delegated to this generic controller instance.
     * This provides a clean separation between the public interface and the internal
     * implementation details, handling color analysis and gain adjustments.
     */
    detail::GenericWhiteBalance m_genericController;
};

} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
