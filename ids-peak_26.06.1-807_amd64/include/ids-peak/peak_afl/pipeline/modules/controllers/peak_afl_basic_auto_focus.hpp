/*!
 * \file    peak_afl_basic_auto_focus.hpp
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
 * \brief Basic automatic focus controller implementation
 *
 * The BasicAutoFocus class provides a streamlined interface for automatic focus
 * control. This controller offers essential focus adjustment
 * capabilities with simplified configuration options suitable for most standard
 * focusing requirements.
 *
 * **Key Features:**
 * - **Multiple search algorithms**: Golden ratio, hill climbing, global search, and full scan
 * - **Sharpness analysis**: Configurable algorithms for focus quality measurement
 * - **ROI-based focusing**: Weighted regions of interest for targeted focus areas
 * - **Focus limits**: Configurable range restrictions for focus motor movement
 * - **Hysteresis control**: Prevents focus hunting and oscillation
 * - **Skip frames**: Performance optimization through selective frame processing
 * - **Callback notifications**: Asynchronous operation completion events
 * - **Serialization support**: Configuration persistence and restoration
 *
 * **Focus Algorithms:**
 * - **Auto**: Automatic algorithm selection based on scene conditions
 * - **Golden Ratio**: Efficient binary search for smooth focus curves
 * - **Hill Climbing**: Fast local optimization for quick focusing
 * - **Global Search**: Comprehensive search for maximum accuracy
 * - **Full Scan**: Complete range scan for challenging focus conditions
 *
 * **Sharpness Measurement:**
 * - **Tenengrad**: Gradient-based sharpness for high-contrast scenes
 * - **Sobel**: Edge detection based measurement for general use
 * - **Mean Score**: Statistical approach for textured surfaces
 * - **Histogram Variance**: Variance-based measurement for uniform lighting
 *
 * \note This controller requires a valid manager instance for camera communication
 * \note Focus motor availability depends on underlying device capabilities
 *
 * \see AdvancedAutoFocus
 * \see FocusSearchAlgorithm
 * \see FocusSharpnessAlgorithm
 * \see detail::IController
 *
 * \since 1.8
 */
class BasicAutoFocus : public detail::IController
{
public:
    /*!
     * \brief Constructs a BasicAutoFocus controller.
     *
     * \param manager Reference to the API manager instance that will manage this controller.
     *                The manager must remain valid for the lifetime of this controller.
     * \since 1.8
     */
    explicit BasicAutoFocus(peak::afl::Manager& manager)
        : IController(manager)
        , m_genericController(manager)
    {}

    /*!
     * \brief Destructor.
     *
     * Cleans up resources and ensures proper shutdown of the auto-focus controller.
     * \since 1.8
     */
    ~BasicAutoFocus() override = default;

    /*!
     * \brief Sets the operating mode of the auto-focus controller.
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
     * \brief Gets the current operating mode of the auto-focus controller.
     *
     * \return The current controller mode.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD ControllerMode GetMode() const override
    {
        return m_genericController.GetMode();
    }

    /*!
     * \brief Checks if the auto-focus controller is currently running.
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
     * resetting all settings including skip frames, hysteresis, algorithms,
     * focus limits, and ROIs to their default values.
     * \since 1.8
     */
    void ResetToDefault() override
    {
        m_genericController.ResetToDefault();
    }

    /*!
     * \brief Sets the number of frames to skip during auto-focus operations.
     *
     * Frame skipping can be used to reduce computational load by processing
     * only every nth frame during focus operations.
     *
     * \param value Number of frames to skip between focus evaluations.
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
     * \return The number of frames currently being skipped between focus evaluations.
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
     * \brief Sets the hysteresis value for focus operations.
     *
     * Hysteresis prevents oscillation around the focus point by requiring
     * a minimum change in focus quality before triggering a focus adjustment.
     * Higher values provide more stability but may reduce responsiveness.
     *
     * \param value Hysteresis value (0-255). Higher values increase stability
     *              but may reduce focus sensitivity.
     * \since 1.8
     */
    void SetHysteresis(uint8_t value)
    {
        m_genericController.Hysteresis().Set(value);
    }

    /*!
     * \brief Gets the current hysteresis value.
     *
     * \return The current hysteresis value used for focus stability.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD uint8_t GetHysteresis() const
    {
        return m_genericController.Hysteresis().Get();
    }

    /*!
     * \brief Gets the valid range for the hysteresis parameter.
     *
     * \return Range object containing the minimum and maximum allowed values
     *         for the hysteresis setting.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU8 GetHysteresisRange() const
    {
        return m_genericController.Hysteresis().GetRange();
    }

    /*!
     * \brief Sets the sharpness algorithm used for focus quality evaluation.
     *
     * The sharpness algorithm determines how focus quality is measured
     * from the image data. Different algorithms may perform better
     * under different lighting conditions or with different scene content.
     *
     * \param algorithm The sharpness algorithm to use for focus evaluation.
     *                  See FocusSharpnessAlgorithm enumeration for available options.
     * \since 1.8
     */
    void SetSharpnessAlgorithm(FocusSharpnessAlgorithm algorithm)
    {
        m_genericController.SharpnessAlgorithm().Set(algorithm);
    }

    /*!
     * \brief Gets the current sharpness algorithm.
     *
     * \return The sharpness algorithm currently being used for focus evaluation.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD FocusSharpnessAlgorithm GetSharpnessAlgorithm() const
    {
        return m_genericController.SharpnessAlgorithm().Get();
    }

    /*!
     * \brief Sets the search algorithm used for finding the optimal focus position.
     *
     * The search algorithm determines the strategy used to find the best focus position,
     * such as hill climbing, binary search, or full sweep approaches.
     *
     * \param algorithm The search algorithm to use for focus positioning.
     *                  See FocusSearchAlgorithm enumeration for available options.
     * \since 1.8
     */
    void SetSearchAlgorithm(FocusSearchAlgorithm algorithm)
    {
        m_genericController.SearchAlgorithm().Set(algorithm);
    }

    /*!
     * \brief Gets the current search algorithm.
     *
     * \return The search algorithm currently being used for focus positioning.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD FocusSearchAlgorithm GetSearchAlgorithm() const
    {
        return m_genericController.SearchAlgorithm().Get();
    }

    /*!
     * \brief Sets the focus limit range for auto-focus operations.
     *
     * The focus limit constrains the auto-focus system to operate within
     * a specified range of focus positions, preventing it from searching
     * across the entire focus range.
     *
     * \param limit Interval defining the minimum and maximum focus positions
     *              that the auto-focus system is allowed to use.
     * \since 1.8
     */
    void SetFocusLimit(const peak::common::Interval& limit)
    {
        m_genericController.FocusLimit().Set(limit);
    }

    /*!
     * \brief Gets the current focus limit range.
     *
     * \return Interval representing the current focus position limits.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::Interval GetFocusLimit() const
    {
        return m_genericController.FocusLimit().Get();
    }

    /*!
     * \brief Sets the weighted regions of interest (ROIs) for focus evaluation.
     *
     * Weighted ROIs allow the auto-focus system to prioritize certain areas
     * of the image when determining focus quality. Each ROI has an associated
     * weight that influences its contribution to the overall focus metric.
     *
     * \param rois Vector of weighted ROI objects defining the regions and their
     *             relative importance for focus evaluation. An empty vector
     *             will use the entire image for focus evaluation.
     * \since 1.8
     */
    void SetWeightedROIs(const std::vector<WeightedROI>& rois)
    {
        m_genericController.WeightedROIs().Set(rois);
    }

    /*!
     * \brief Gets the current weighted regions of interest.
     *
     * \return Vector of WeightedROI objects representing the current focus regions.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::vector<WeightedROI> GetWeightedROIs() const
    {
        return m_genericController.WeightedROIs().Get();
    }

    /*!
     * \brief Resets the weighted roi to a single center ROI.
     *
     * This effectively calls \ref features::WeightedRois::SetPreset with \ref RoiPreset::Center
     *
     * \since 2.0
     */
    void ResetWeightedROIs() const
    {
        m_genericController.WeightedROIs().SetPreset(RoiPreset::Center);
    }

    /*!
     * \brief Registers a callback function to be called when focus operations complete.
     *
     * The callback will be invoked when the auto-focus operation finishes,
     * whether it succeeds or fails. This allows for asynchronous monitoring
     * of focus operations.
     *
     * \param callback Function object to be called upon focus operation completion.
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
    detail::GenericAutoFocus m_genericController; //!< Internal generic auto-focus controller implementation

    /*!
     * \brief Gets the name identifier for this controller type.
     *
     * \return String identifier "BasicAutoFocus" for this controller implementation.
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::string GetName() const override
    {
        return "BasicAutoFocus";
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
     * \return ControllerType::Focus indicating this is a focus controller.
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
