/*!
 * \file    peak_afl_hysteresis.hpp
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
 * \brief Hysteresis feature implementation for auto controllers
 *
 * The Hysteresis class provides a feature interface for managing the hysteresis
 * parameter of auto controllers. Hysteresis prevents oscillation in automatic
 * control systems by introducing a dead zone around the target value where
 * no adjustments are made.
 *
 * Hysteresis is particularly important in automatic exposure and focus systems
 * to prevent continuous small adjustments that can cause visible flickering
 * or hunting behavior. The hysteresis value defines how far from the target
 * the measured value must move before the controller will make an adjustment.
 *
 * This class inherits from IRangeFeature<uint8_t> and provides serialization support
 * for configuration persistence.
 *
 * \note The actual range and increment values are determined by the underlying
 *       controller implementation and may vary based on the controller type
 *       and system characteristics.
 *
 * \see IRangeFeature
 * \see peak::afl::Controller::SetHysteresis()
 * \see peak::afl::Controller::GetHysteresis()
 * \see AutoTarget
 * \see AutoTolerance
 *
 * \since 1.8
 */
class Hysteresis : public IRangeFeature<uint8_t>
{
public:
    /*!
     * \brief Constructs a Hysteresis feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                       to manage the hysteresis parameter. The controller
     *                       must support hysteresis operations.
     *
     * \pre controller must not be null
     * \pre controller must support hysteresis functionality
     *
     * \since 1.8
     */
    explicit Hysteresis(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the hysteresis value
     *
     * Sets the hysteresis value that defines the dead zone around the target
     * where no automatic adjustments will be made. This prevents oscillation
     * and hunting behavior in automatic control systems.
     *
     * \param[in] value The hysteresis value to set. Higher values create a
     *                  larger dead zone, reducing sensitivity but improving
     *                  stability. The exact valid range can be obtained using GetRange().
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
    void Set(const uint8_t& value) override
    {
        m_controller->SetHysteresis(value);
    }

    /*!
     * \brief Gets the current hysteresis value
     *
     * Retrieves the currently configured hysteresis value that defines
     * the dead zone around the target for automatic adjustments.
     *
     * \return The current hysteresis value as a uint8_t
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see GetRange()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD uint8_t Get() const override
    {
        return m_controller->GetHysteresis();
    }

    /*!
     * \brief Gets the valid range for hysteresis values
     *
     * Retrieves the minimum, maximum, and increment values that are valid
     * for the hysteresis parameter. This information can be used to
     * validate input values or to populate user interface controls.
     *
     * \return A RangeU8 structure containing:
     *         - min: Minimum valid hysteresis value
     *         - max: Maximum valid hysteresis value
     *         - inc: Increment/step size for hysteresis values
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see Get()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU8 GetRange() const override
    {
        const auto result = m_controller->GetHysteresisRange();
        return { result.min, result.max, result.inc };
    }

    /*!
     * \brief Serializes the current hysteresis value to an archive
     *
     * Stores the current hysteresis value in the provided archive for
     * configuration persistence. The value is stored with the key "Hysteresis".
     *
     * \param[in,out] archive The archive to write the hysteresis value to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetInt("Hysteresis", Get());
    }

    /*!
     * \brief Deserializes the hysteresis value from an archive
     *
     * Loads the hysteresis value from the provided archive and applies it
     * to the controller. The value is expected to be stored with the key "Hysteresis".
     *
     * \param[in] archive The archive to read the hysteresis value from
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
        Set(static_cast<uint8_t>(archive.GetInt("Hysteresis")));
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual hysteresis functionality.
     * This controller must support hysteresis operations and remain valid
     * for the lifetime of this Hysteresis feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
