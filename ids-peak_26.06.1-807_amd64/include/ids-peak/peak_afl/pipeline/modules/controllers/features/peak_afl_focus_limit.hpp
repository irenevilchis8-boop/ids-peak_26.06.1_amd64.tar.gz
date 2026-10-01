/*!
 * \file    peak_afl_focus_limit.hpp
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
#include <peak_common/types/peak_common_interval.hpp>

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
 * \brief Focus limit feature implementation for auto focus controllers
 *
 * The FocusLimit class provides a feature interface for managing the focus limit
 * parameter of auto focus controllers. This feature defines the range of focus
 * positions that the automatic focus algorithm is allowed to use during focus
 * operations.
 *
 * Focus limits are useful for:
 * - Restricting focus search to a specific distance range (e.g., macro, infinity)
 * - Preventing the lens from moving to mechanically unsafe positions
 * - Optimizing focus speed by limiting the search range
 * - Avoiding focus on unwanted objects at certain distances
 *
 * The limit is defined as an interval with minimum and maximum focus positions,
 * typically expressed in lens-specific units or motor steps.
 *
 * This class inherits from IFeature<peak::common::Interval> and provides
 * serialization support for configuration persistence.
 *
 * \note The actual focus position units and valid ranges depend on the specific
 *       lens and controller implementation.
 *
 * \see IFeature
 * \see peak::common::Interval
 * \see peak::afl::Controller::SetLimit()
 * \see peak::afl::Controller::GetLimit()
 *
 * \since 1.8
 */
class FocusLimit : public IFeature<peak::common::Interval>
{
public:
    /*!
     * \brief Constructs a FocusLimit feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto focus controller that will be used
     *                       to manage the focus limit parameter. The controller must
     *                       support focus limit operations.
     *
     * \pre controller must not be null
     * \pre controller must support focus limit functionality
     *
     * \since 1.8
     */
    explicit FocusLimit(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the focus position limits
     *
     * Sets the range of focus positions that the automatic focus algorithm
     * is allowed to use. The focus search will be restricted to positions
     * between the minimum and maximum values of the interval.
     *
     * \param[in] value The interval defining the focus limits. The minimum
     *                  value should be less than or equal to the maximum value.
     *                  Values are typically in lens-specific units or motor steps.
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the interval is invalid or if the controller is in an invalid state.
     *
     * \see Get()
     * \see peak::common::Interval
     *
     * \since 1.8
     */
    void Set(const peak::common::Interval& value) override
    {
        m_controller->SetLimit({ value.GetMinimum(), value.GetMaximum() });
    }

    /*!
     * \brief Gets the current focus position limits
     *
     * Retrieves the currently configured range of focus positions that the
     * automatic focus algorithm is allowed to use.
     *
     * \return The current focus limits as an Interval object
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see peak::common::Interval
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::Interval Get() const override
    {
        const auto result = m_controller->GetLimit();
        return { result.min, result.max };
    }

    /*!
     * \brief Serializes the current focus limits to an archive
     *
     * Stores the current focus position limits in the provided archive for
     * configuration persistence. The limits are stored with keys "Min" and "Max".
     *
     * \param[in,out] archive The archive to write the focus limits to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        const auto interval = Get();
        archive.SetInt("Min", interval.GetMinimum());
        archive.SetInt("Max", interval.GetMaximum());
    }

    /*!
     * \brief Deserializes the focus limits from an archive
     *
     * Loads the focus position limits from the provided archive and applies them
     * to the controller. The limits are expected to be stored with keys "Min" and "Max".
     *
     * \param[in] archive The archive to read the focus limits from
     *
     * \throws May throw serialization exceptions if the archive operation fails
     * \throws May throw controller exceptions if the deserialized limits are invalid
     *
     * \see Serialize()
     *
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        Set({ static_cast<int32_t>(archive.GetInt("Min")), static_cast<int32_t>(archive.GetInt("Max")) });
    }

private:
    /*!
     * \brief Shared pointer to the auto focus controller
     *
     * The controller instance that provides the actual focus limit functionality.
     * This controller must support focus limit operations and remain valid for
     * the lifetime of this FocusLimit feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller{};
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
