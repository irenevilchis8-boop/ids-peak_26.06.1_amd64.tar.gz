/*!
 * \file    peak_afl_skip_frames.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/peak_afl.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_ifeature.hpp>

#include <peak_common_c/detail/peak_common_defines.h>

#include <memory>

namespace peak
{
namespace pipeline
{
namespace modules
{
namespace autofeature
{
namespace features
{
/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Skip frames feature implementation for auto controllers
 *
 * The SkipFrames class provides a feature interface for managing the skip frames
 * parameter of auto controllers. This feature controls how many frames the
 * automatic algorithms should skip between processing cycles.
 *
 * Frame skipping is useful for performance optimization and to allow camera
 * parameters to stabilize between auto adjustments. For example, setting
 * skip frames to 5 means the auto algorithm will process every 6th frame
 * (skip 5, process 1), giving the camera time to settle after parameter changes.
 *
 * This class inherits from IRangeFeature<uint32_t> and provides serialization support
 * for configuration persistence.
 *
 * \note The actual range and increment values are determined by the underlying
 *       controller implementation and may vary based on the controller type
 *       and system capabilities.
 *
 * \see IRangeFeature
 * \see peak::afl::Controller::SetSkipFrames()
 * \see peak::afl::Controller::GetSkipFrames()
 *
 * \since 1.8
 */
class SkipFrames : public IRangeFeature<uint32_t>
{
public:
    /*!
     * \brief Constructs a SkipFrames feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the skip frames parameter. The controller
     *                      must support skip frames operations.
     *
     * \pre controller must not be null
     * \pre controller must support skip frames functionality
     *
     * \since 1.8
     */
    explicit SkipFrames(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the number of frames to skip
     *
     * Sets the number of frames that the automatic algorithms should skip
     * between processing cycles. This allows for performance optimization
     * and gives camera parameters time to stabilize between adjustments.
     *
     * \param[in] value The number of frames to skip. A value of 0 means
     *                 process every frame, 1 means skip 1 frame (process
     *                 every other frame), etc. The exact valid range can
     *                 be obtained using GetRange().
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the value is outside the valid range or if the controller is in
     *         an invalid state.
     *
     * \see Get()
     * \see GetRange()
     *
     * \since 1.8
     */
    void Set(const uint32_t& value) override
    {
        m_controller->SetSkipFrames(value);
    }

    /*!
     * \brief Gets the current number of frames to skip
     *
     * Retrieves the currently configured number of frames that the
     * automatic algorithms skip between processing cycles.
     *
     * \return The current skip frames value as a uint32_t
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see GetRange()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD uint32_t Get() const override
    {
        return m_controller->GetSkipFrames();
    }

    /*!
     * \brief Gets the valid range for skip frames values
     *
     * Retrieves the minimum, maximum, and increment values that are valid
     * for the skip frames parameter. This information can be used to
     * validate input values or to populate user interface controls.
     *
     * \return A RangeU structure containing:
     *         - min: Minimum valid skip frames value (typically 0)
     *         - max: Maximum valid skip frames value
     *         - inc: Increment/step size for skip frames values (typically 1)
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see Get()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU GetRange() const override
    {
        const auto result = m_controller->GetSkipFramesRange();
        return { result.min, result.max, result.inc };
    }

    /*!
     * \brief Serializes the current skip frames value to an archive
     *
     * Stores the current skip frames value in the provided archive for
     * configuration persistence. The value is stored with the key "SkipFrames".
     *
     * \param[in,out] archive The archive to write the skip frames value to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetInt("SkipFrames", Get());
    }

    /*!
     * \brief Deserializes the skip frames value from an archive
     *
     * Loads the skip frames value from the provided archive and applies it
     * to the controller. The value is expected to be stored with the key "SkipFrames".
     *
     * \param[in] archive The archive to read the skip frames value from
     *
     * \throws May throw serialization exceptions if the archive operation fails
     * \throws May throw controller exceptions if the deserialized value is invalid
     *
     * \see Serialize()
     *
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        Set(static_cast<uint32_t>(archive.GetInt("SkipFrames")));
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual skip frames functionality.
     * This controller must support skip frames operations and remain valid
     * for the lifetime of this SkipFrames feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
