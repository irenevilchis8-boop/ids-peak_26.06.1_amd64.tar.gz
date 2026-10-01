/*!
 * \file    peak_afl_auto_tolerance.hpp
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
#include <peak_common/types/peak_common_range.hpp>

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
 * \brief Auto tolerance feature implementation for auto controllers
 *
 * The AutoTolerance class provides a feature interface for managing the auto tolerance
 * parameter of auto controllers. This feature controls the tolerance range around the
 * target brightness value within which the automatic algorithms consider the image
 * to be properly exposed.
 *
 * The tolerance value defines an acceptable deviation from the target brightness.
 * For example, if the target is 128 and tolerance is 10, then brightness values
 * between 118 and 138 would be considered acceptable, and the auto algorithms
 * would not make further adjustments.
 *
 * This class inherits from IRangeFeature<uint32_t> and provides serialization support
 * for configuration persistence.
 *
 * \note The actual range and increment values are determined by the underlying
 *       controller implementation and may vary based on the image format and
 *       controller capabilities.
 *
 * \see IRangeFeature
 * \see peak::afl::Controller::SetAutoTolerance()
 * \see peak::afl::Controller::GetAutoTolerance()
 * \see AutoTarget
 * \see AutoPercentile
 *
 * \since 1.8
 */
class AutoTolerance : public IRangeFeature<uint32_t>
{
public:
    /*!
     * \brief Constructs an AutoTolerance feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                       to manage the auto tolerance parameter. The controller
     *                       must support auto tolerance operations.
     *
     * \pre controller must not be null
     * \pre controller must support auto tolerance functionality
     *
     * \since 1.8
     */
    explicit AutoTolerance(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the auto tolerance value
     *
     * Sets the tolerance range around the target brightness value within which
     * the automatic algorithms consider the image to be properly exposed.
     * A larger tolerance value makes the algorithm less sensitive to brightness
     * variations, while a smaller tolerance makes it more precise.
     *
     * \param[in] value The tolerance value to set. This represents the acceptable
     *                  deviation from the target brightness. The exact valid range
     *                  can be obtained using GetRange().
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the value is outside the valid range or if the controller is in
     *         an invalid state.
     *
     * \see Get()
     * \see GetRange()
     * \see AutoTarget::Set()
     *
     * \since 1.8
     */
    void Set(const uint32_t& value) override
    {
        m_controller->SetAutoTolerance(value);
    }

    /*!
     * \brief Gets the current auto tolerance value
     *
     * Retrieves the currently configured tolerance value that defines the
     * acceptable deviation from the target brightness.
     *
     * \return The current auto tolerance value as a uint32_t
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
        return m_controller->GetAutoTolerance();
    }

    /*!
     * \brief Gets the valid range for auto tolerance values
     *
     * Retrieves the minimum, maximum, and increment values that are valid
     * for the auto tolerance parameter. This information can be used to
     * validate input values or to populate user interface controls.
     *
     * \return A RangeU structure containing:
     *         - min: Minimum valid tolerance value
     *         - max: Maximum valid tolerance value
     *         - inc: Increment/step size for tolerance values
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
        const auto result = m_controller->GetAutoToleranceRange();
        return { result.min, result.max, result.inc };
    }

    /*!
     * \brief Serializes the current auto tolerance value to an archive
     *
     * Stores the current auto tolerance value in the provided archive for
     * configuration persistence. The value is stored with the key "AutoTolerance".
     *
     * \param[in,out] archive The archive to write the auto tolerance value to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetInt("AutoTolerance", Get());
    }

    /*!
     * \brief Deserializes the auto tolerance value from an archive
     *
     * Loads the auto tolerance value from the provided archive and applies it
     * to the controller. The value is expected to be stored with the key "AutoTolerance".
     *
     * \param[in] archive The archive to read the auto tolerance value from
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
        Set(static_cast<uint32_t>(archive.GetInt("AutoTolerance")));
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual auto tolerance functionality.
     * This controller must support auto tolerance operations and remain valid
     * for the lifetime of this AutoTolerance feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
