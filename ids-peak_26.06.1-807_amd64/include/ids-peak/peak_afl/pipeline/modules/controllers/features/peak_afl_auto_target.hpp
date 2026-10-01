/*!
 * \file    peak_afl_auto_target.hpp
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
 * \brief Auto target feature implementation for auto controllers
 *
 * The AutoTarget class provides a feature interface for managing the auto target
 * parameter of auto controllers. This feature controls the target brightness value
 * that the automatic exposure and brightness algorithms aim to achieve.
 *
 * The target value represents the desired brightness level in the image, typically
 * expressed as a value in the range of 0-255 for 8-bit images or scaled accordingly
 * for other bit depths. The auto algorithms will adjust exposure, gain, and other
 * parameters to achieve this target brightness in the specified region of interest.
 *
 * This class inherits from IRangeFeature<uint32_t> and provides serialization support
 * for configuration persistence.
 *
 * \note The actual range and increment values are determined by the underlying
 *       controller implementation and may vary based on the image format and
 *       controller capabilities.
 *
 * \see IRangeFeature
 * \see peak::afl::Controller::SetAutoTarget()
 * \see peak::afl::Controller::GetAutoTarget()
 * \see AutoTolerance
 * \see AutoPercentile
 *
 * \since 1.8
 */
class AutoTarget : public IRangeFeature<uint32_t>
{
public:
    /*!
     * \brief Constructs an AutoTarget feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the auto target parameter. The controller
     *                      must support auto target operations.
     *
     * \pre controller must not be null
     * \pre controller must support auto target functionality
     *
     * \since 1.8
     */
    explicit AutoTarget(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the auto target brightness value
     *
     * Sets the target brightness value that the automatic exposure and brightness
     * algorithms will aim to achieve. The auto algorithms will adjust camera
     * parameters to reach this target brightness level in the analyzed region.
     *
     * \param[in] value The target brightness value to set. Typically ranges from
     *                  0 to 255 for 8-bit images. The exact valid range can be
     *                  obtained using GetRange().
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the value is outside the valid range or if the controller is in
     *         an invalid state.
     *
     * \see Get()
     * \see GetRange()
     * \see AutoTolerance::Set()
     *
     * \since 1.8
     */
    void Set(const uint32_t& value) override
    {
        m_controller->SetAutoTarget(value);
    }

    /*!
     * \brief Gets the current auto target brightness value
     *
     * Retrieves the currently configured target brightness value that the
     * automatic algorithms are trying to achieve.
     *
     * \return The current auto target brightness value as a uint32_t
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
        return m_controller->GetAutoTarget();
    }

    /*!
     * \brief Gets the valid range for auto target values
     *
     * Retrieves the minimum, maximum, and increment values that are valid
     * for the auto target parameter. This information can be used to
     * validate input values or to populate user interface controls.
     *
     * \return A RangeU structure containing:
     *         - min: Minimum valid target brightness value
     *         - max: Maximum valid target brightness value
     *         - inc: Increment/step size for target values
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
        const auto result = m_controller->GetAutoTargetRange();
        return { result.min, result.max, result.inc };
    }

    /*!
     * \brief Serializes the current auto target value to an archive
     *
     * Stores the current auto target value in the provided archive for
     * configuration persistence. The value is stored with the key "AutoTarget".
     *
     * \param[in,out] archive The archive to write the auto target value to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetInt("AutoTarget", Get());
    }

    /*!
     * \brief Deserializes the auto target value from an archive
     *
     * Loads the auto target value from the provided archive and applies it
     * to the controller. The value is expected to be stored with the key "AutoTarget".
     *
     * \param[in] archive The archive to read the auto target value from
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
        Set(static_cast<uint32_t>(archive.GetInt("AutoTarget")));
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual auto target functionality.
     * This controller must support auto target operations and remain valid
     * for the lifetime of this AutoTarget feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
