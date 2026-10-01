/*!
 * \file    peak_afl_basic_auto_white_balance.hpp
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
 * \brief Basic automatic white balance controller implementation
 *
 * The BasicAutoWhiteBalance class provides a streamlined interface for automatic
 * white balance control. This controller offers essential
 * color correction capabilities with simplified configuration options suitable
 * for most standard white balance requirements.
 *
 * **Key Features:**
 * - **ROI-based analysis**: Region-of-interest selection for targeted white balance areas
 * - **Processing callbacks**: Real-time notifications during white balance operations
 * - **Multiple control modes**: Continuous, once, and manual white balance modes
 * - **Serialization support**: Configuration persistence and restoration
 *
 * \note This controller requires a valid manager instance for camera communication
 * \note White balance capability depends on underlying device support
 *
 * \see AdvancedAutoWhiteBalance
 * \see detail::IController
 * \see features::Roi
 *
 * \since 1.8
 */
class BasicAutoWhiteBalance : public detail::IController
{
    //! Function type for processing callbacks that notify when white balance processing occurs
    using ProcessingCallback = std::function<void()>;

public:
    /*!
     * \brief Constructs a BasicAutoWhiteBalance controller.
     *
     * \param manager Reference to the API manager instance that will manage this controller.
     *                The manager must remain valid for the lifetime of this controller.
     * \param callback Processing callback function that will be invoked during white balance
     *                 processing operations. This callback allows for custom processing
     *                 or notification when white balance adjustments are being performed.
     * \since 1.8
     */
    explicit BasicAutoWhiteBalance(peak::afl::Manager& manager, ProcessingCallback callback)
        : IController(manager)
        , m_genericController(manager, std::move(callback))
    {}

    /*!
     * \brief Destructor.
     *
     * Cleans up resources and ensures proper shutdown of the auto white balance controller.
     * \since 1.8
     */
    ~BasicAutoWhiteBalance() override = default;

    /*!
     * \brief Sets the operating mode of the auto white balance controller.
     *
     * \param mode The desired controller mode (e.g., Off, On, Auto, Manual).
     *             See ControllerMode enumeration for available options.
     * \since 1.8
     */
    void SetMode(ControllerMode mode) override
    {
        m_genericController.SetMode(mode);
    }

    /*!
     * \brief Gets the current operating mode of the auto white balance controller.
     *
     * \return The current controller mode.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const override
    {
        return m_genericController.GetMode();
    }

    /*!
     * \brief Checks if the auto white balance controller is currently running.
     *
     * \return true if the controller is running (mode is not Off), false otherwise.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD bool IsRunning() const override
    {
        return m_genericController.IsRunning();
    }

    /*!
     * \brief Resets all controller parameters to their default values.
     *
     * This method restores the controller to its initial configuration,
     * resetting all settings including skip frames and ROI to their default values.
     * \since 1.8
     */
    void ResetToDefault() override
    {
        m_genericController.ResetToDefault();
    }

    /*!
     * \brief Sets the number of frames to skip during auto white balance operations.
     *
     * Frame skipping can be used to reduce computational load by processing
     * only every nth frame during white balance operations. This can improve
     * performance while maintaining acceptable color correction quality.
     *
     * \param value Number of frames to skip between white balance evaluations.
     *              Must be within the valid range returned by GetSkipFramesRange().
     * \since 1.8
     */
    void SetSkipFrames(uint32_t value)
    {
        m_genericController.SkipFrames().Set(value);
    }

    /*!
     * \brief Gets the current number of frames being skipped.
     *
     * \return The number of frames currently being skipped between white balance evaluations.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetSkipFrames() const
    {
        return m_genericController.SkipFrames().Get();
    }

    /*!
     * \brief Gets the valid range for the skip frames parameter.
     *
     * \return Range object containing the minimum and maximum allowed values
     *         for the skip frames setting.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU GetSkipFramesRange() const
    {
        return m_genericController.SkipFrames().GetRange();
    }

    /*!
     * \brief Sets the region of interest (ROI) for white balance evaluation.
     *
     * The ROI defines the specific area of the image that will be used for
     * white balance calculations. This allows the system to focus on particular
     * regions that are more representative of the desired color temperature,
     * ignoring areas that might contain misleading color information.
     *
     * \param roi Rectangle defining the region of interest in image coordinates.
     *            The rectangle should be within the bounds of the image and
     *            contain sufficient pixel data for accurate white balance calculation.
     * \since 1.8
     */
    void SetRoi(const peak::common::Rectangle& roi)
    {
        m_genericController.Roi().Set(roi);
    }

    /*!
     * \brief Gets the current region of interest for white balance evaluation.
     *
     * \return Rectangle representing the current ROI used for white balance calculations.
     *         If no ROI has been set, this typically returns the entire image area.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::Rectangle GetRoi()
    {
        return m_genericController.Roi().Get();
    }

    /*!
     * \brief Registers a callback function to be called when white balance operations complete.
     *
     * The callback will be invoked when the auto white balance operation finishes,
     * whether it succeeds or fails. This allows for asynchronous monitoring
     * of white balance operations and integration with application workflows.
     *
     * \param callback Function object to be called upon white balance operation completion.
     *                 The callback should accept parameters indicating the operation result.
     * \return Handle that can be used to unregister the callback later.
     * \since 1.8
     */
    IController::FinishedCallbackHandle RegisterFinishedCallback(const IController::FinishedCallback& callback)
    {
        return m_genericController.RegisterFinishedCallback(callback);
    }

    /*!
     * \brief Unregisters a previously registered finished callback.
     *
     * \param callbackHandle Handle returned by RegisterFinishedCallback() that
     *                       identifies the callback to be removed.
     * \since 1.8
     */
    void UnregisterFinishedCallback(IController::FinishedCallbackHandle callbackHandle)
    {
        m_genericController.UnregisterFinishedCallback(callbackHandle);
    }

private:
    detail::GenericWhiteBalance m_genericController; //!< Internal generic white balance controller implementation

    /*!
     * \brief Gets the name identifier for this controller type.
     *
     * \return String identifier "BasicAutoWhiteBalance" for this controller implementation.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::string GetName() const override
    {
        return "BasicAutoWhiteBalance";
    }

    /*!
     * \brief Serializes the controller state to an archive.
     *
     * This method saves the current controller configuration and state
     * to the provided archive for persistence or transmission.
     *
     * \param archive Archive object to write the controller state to.
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        m_genericController.Serialize(archive);
    }

    /*!
     * \brief Deserializes the controller state from an archive.
     *
     * This method restores the controller configuration and state
     * from the provided archive, typically after loading from storage.
     *
     * \param archive Archive object to read the controller state from.
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        m_genericController.Deserialize(archive);
    }

    /*!
     * \brief Gets the controller type identifier.
     *
     * \return ControllerType::WhiteBalance indicating this is a white balance controller.
     * \since 1.8
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
