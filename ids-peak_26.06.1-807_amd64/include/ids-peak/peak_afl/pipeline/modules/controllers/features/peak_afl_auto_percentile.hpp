/*!
 * \file    peak_afl_auto_percentile.hpp
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
 * \brief Auto percentile feature implementation for auto controllers
 *
 * The AutoPercentile class provides a feature interface for managing the auto percentile
 * parameter of auto controllers. This feature controls the percentile value used in
 * automatic exposure and brightness calculations, determining which portion of the
 * histogram is considered for the automatic adjustments.
 *
 * The percentile value typically ranges from 0.0 to 100.0, where:
 * - Lower values (e.g., 10.0) focus on darker regions of the image
 * - Higher values (e.g., 90.0) focus on brighter regions of the image
 * - Common values like 50.0 represent the median brightness
 *
 * This class inherits from IRangeFeature<double> and provides serialization support
 * for configuration persistence.
 *
 * \note The actual range and increment values are determined by the underlying
 *       controller implementation and may vary based on the specific auto feature
 *       algorithm being used.
 *
 * \see IRangeFeature
 * \see peak::afl::Controller::SetAutoPercentile()
 * \see peak::afl::Controller::GetAutoPercentile()
 *
 * \since 1.8
 */
class AutoPercentile : public IRangeFeature<double>
{
public:
    /*!
     * \brief Constructs an AutoPercentile feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the auto percentile parameter. The controller
     *                      must support auto percentile operations.
     *
     * \pre controller must not be null
     * \pre controller must support auto percentile functionality
     *
     * \since 1.8
     */
    explicit AutoPercentile(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the auto percentile value
     *
     * Sets the percentile value used for automatic exposure and brightness calculations.
     * The percentile determines which portion of the image histogram is considered
     * when calculating automatic adjustments.
     *
     * \param[in] value The percentile value to set. Typically ranges from 0.0 to 100.0.
     *                  The exact valid range can be obtained using GetRange().
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
    void Set(const double& value) override
    {
        m_controller->SetAutoPercentile(value);
    }

    /*!
     * \brief Gets the current auto percentile value
     *
     * Retrieves the currently configured percentile value used for automatic
     * exposure and brightness calculations.
     *
     * \return The current auto percentile value as a double
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see GetRange()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD double Get() const override
    {
        return m_controller->GetAutoPercentile();
    }

    /*!
     * \brief Gets the valid range for auto percentile values
     *
     * Retrieves the minimum, maximum, and increment values that are valid
     * for the auto percentile parameter. This information can be used to
     * validate input values or to populate user interface controls.
     *
     * \return A RangeT<double> structure containing:
     *         - min: Minimum valid percentile value
     *         - max: Maximum valid percentile value
     *         - inc: Increment/step size for percentile values
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see Get()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD RangeD GetRange() const override
    {
        const auto result = m_controller->GetAutoPercentileRange();
        return { result.min, result.max, result.inc };
    }

    /*!
     * \brief Serializes the current auto percentile value to an archive
     *
     * Stores the current auto percentile value in the provided archive for
     * configuration persistence. The value is stored with the key "AutoPercentile".
     *
     * \param[in,out] archive The archive to write the auto percentile value to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetDouble("AutoPercentile", Get());
    }

    /*!
     * \brief Deserializes the auto percentile value from an archive
     *
     * Loads the auto percentile value from the provided archive and applies it
     * to the controller. The value is expected to be stored with the key "AutoPercentile".
     *
     * \param[in] archive The archive to read the auto percentile value from
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
        Set(archive.GetDouble("AutoPercentile"));
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual auto percentile functionality.
     * This controller must support auto percentile operations and remain valid
     * for the lifetime of this AutoPercentile feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
