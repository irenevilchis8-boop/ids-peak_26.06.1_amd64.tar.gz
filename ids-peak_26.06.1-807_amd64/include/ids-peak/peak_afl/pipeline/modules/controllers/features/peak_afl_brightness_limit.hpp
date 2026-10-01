/*!
 * \file    peak_afl_brightness_limit.hpp
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
 * \brief Base class for brightness limit features
 *
 * The BrightnessLimit class provides a common base interface for all brightness-related
 * limit features in auto controllers. This abstract base class defines the standard
 * serialization behavior for interval-based limits used in automatic exposure and
 * brightness control.
 *
 * Brightness limits define the allowable range for various camera parameters that
 * affect image brightness, such as exposure time, gain values, and other exposure
 * components. These limits prevent the automatic algorithms from setting values
 * outside acceptable ranges.
 *
 * This class inherits from IFeature<IntervalD>
 * and provides standard serialization support for double-precision intervals.
 *
 * \note This is an abstract base class. Use the specific derived classes like
 *       BrightnessExposureLimit, BrightnessGainLimit, etc. for actual functionality.
 *
 * \see IFeature
 * \see peak::common::detail::IntervalT
 * \see BrightnessExposureLimit
 * \see BrightnessGainLimit
 *
 * \since 1.8
 */
class BrightnessLimit : public IFeature<IntervalD>
{
public:
    /*!
     * \brief Serializes the current brightness limit to an archive
     *
     * Stores the current brightness limit interval in the provided archive for
     * configuration persistence. The interval is stored with keys "Min" and "Max".
     *
     * \param[in,out] archive The archive to write the brightness limit to
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
        archive.SetDouble("Min", interval.GetMinimum());
        archive.SetDouble("Max", interval.GetMaximum());
    }

    /*!
     * \brief Deserializes the brightness limit from an archive
     *
     * Loads the brightness limit interval from the provided archive and applies it
     * to the controller. The interval is expected to be stored with keys "Min" and "Max".
     *
     * \param[in] archive The archive to read the brightness limit from
     *
     * \throws May throw serialization exceptions if the archive operation fails
     * \throws May throw controller exceptions if the deserialized interval is invalid
     *
     * \see Serialize()
     *
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        IntervalD interval{ archive.GetDouble("Min"), archive.GetDouble("Max") };
        Set(interval);
    }
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Exposure limit feature implementation for brightness controllers
 *
 * The BrightnessExposureLimit class provides a feature interface for managing
 * the exposure time limits in automatic brightness control. This feature defines
 * the minimum and maximum exposure times that the automatic exposure algorithm
 * is allowed to use.
 *
 * Exposure limits are essential for:
 * - Preventing motion blur by limiting maximum exposure time
 * - Avoiding underexposure by setting minimum exposure time
 * - Maintaining frame rate requirements
 * - Preventing camera shake in handheld applications
 *
 * The limits are typically expressed in seconds or microseconds, depending on
 * the camera implementation.
 *
 * \see BrightnessLimit
 * \see peak::afl::Controller::SetExposureLimit()
 * \see peak::afl::Controller::GetExposureLimit()
 *
 * \since 1.8
 */
class BrightnessExposureLimit : public BrightnessLimit
{
public:
    /*!
     * \brief Constructs a BrightnessExposureLimit feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the exposure limit parameter. The controller must
     *                      support exposure limit operations.
     *
     * \pre controller must not be null
     * \pre controller must support exposure limit functionality
     *
     * \since 1.8
     */
    explicit BrightnessExposureLimit(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the exposure time limits
     *
     * Sets the minimum and maximum exposure times that the automatic brightness
     * algorithm is allowed to use. The exposure time will be constrained to
     * values within this interval.
     *
     * \param[in] value The interval defining the exposure limits. Minimum value
     *                 should be less than or equal to maximum value. Units are
     *                 typically seconds or microseconds.
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the interval is invalid or if the controller is in an invalid state.
     *
     * \see Get()
     *
     * \since 1.8
     */
    void Set(const IntervalD& value) override
    {
        m_controller->SetExposureLimit({ value.GetMinimum(), value.GetMaximum() });
    }

    /*!
     * \brief Gets the current exposure time limits
     *
     * Retrieves the currently configured minimum and maximum exposure times
     * that constrain the automatic brightness algorithm.
     *
     * \return The current exposure limits as an IntervalD object
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD IntervalD Get() const override
    {
        const auto result = m_controller->GetExposureLimit();
        return { result.min, result.max };
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual exposure limit functionality.
     * This controller must support exposure limit operations and remain valid for
     * the lifetime of this BrightnessExposureLimit feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Gain limit feature implementation for brightness controllers
 *
 * The BrightnessGainLimit class provides a feature interface for managing
 * the overall gain limits in automatic brightness control. This feature defines
 * the minimum and maximum gain values that the automatic exposure algorithm
 * is allowed to use.
 *
 * Gain limits help control:
 * - Image noise by limiting maximum gain
 * - Minimum sensitivity requirements
 * - Dynamic range optimization
 * - Signal-to-noise ratio management
 *
 * \see BrightnessLimit
 * \see peak::afl::Controller::SetGainLimit()
 * \see peak::afl::Controller::GetGainLimit()
 *
 * \since 1.8
 */
class BrightnessGainLimit : public BrightnessLimit
{
public:
    /*!
     * \brief Constructs a BrightnessGainLimit feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the gain limit parameter.
     *
     * \pre controller must not be null
     * \pre controller must support gain limit functionality
     *
     * \since 1.8
     */
    explicit BrightnessGainLimit(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the overall gain limits
     *
     * \param[in] value The interval defining the gain limits
     *
     * \since 1.8
     */
    void Set(const IntervalD& value) override
    {
        m_controller->SetGainLimit({ value.GetMinimum(), value.GetMaximum() });
    }

    /*!
     * \brief Gets the current overall gain limits
     *
     * \return The current gain limits as an IntervalD object
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD IntervalD Get() const override
    {
        const auto result = m_controller->GetGainLimit();
        return { result.min, result.max };
    }

private:
    std::shared_ptr<peak::afl::Controller> m_controller;
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Analog gain limit feature implementation for brightness controllers
 *
 * The BrightnessGainAnalogLimit class manages analog gain limits that are applied
 * at the sensor level before digitization. Analog gain affects the signal before
 * it is converted to digital values, providing clean amplification with minimal
 * noise impact compared to digital gain.
 *
 * This feature allows automatic brightness controllers to constrain the analog
 * gain values within specified limits, ensuring optimal image quality while
 * preventing excessive noise or saturation.
 *
 * \see BrightnessLimit
 * \see peak::afl::Controller::SetGainAnalogLimit()
 * \see peak::afl::Controller::GetGainAnalogLimit()
 * \see BrightnessGainDigitalLimit
 *
 * \since 1.8
 */
class BrightnessGainAnalogLimit : public BrightnessLimit
{
public:
    /*!
     * \brief Constructs an analog gain limit feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the analog gain limits. The controller must
     *                      support analog gain operations.
     *
     * \pre controller must not be null
     * \pre controller must support analog gain functionality
     *
     * \since 1.8
     */
    explicit BrightnessGainAnalogLimit(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the analog gain limits
     *
     * \param[in] value The interval defining the minimum and maximum analog gain limits
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the limits are invalid or if the controller is in an invalid state
     *
     * \see Get()
     *
     * \since 1.8
     */
    void Set(const IntervalD& value) override
    {
        m_controller->SetGainAnalogLimit({ value.GetMinimum(), value.GetMaximum() });
    }

    /*!
     * \brief Gets the current analog gain limits
     *
     * \return The current analog gain limits as an IntervalD object
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state
     *
     * \see Set()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD IntervalD Get() const override
    {
        const auto result = m_controller->GetGainAnalogLimit();
        return { result.min, result.max };
    }

private:
    std::shared_ptr<peak::afl::Controller> m_controller;
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Digital gain limit feature implementation for brightness controllers
 *
 * The BrightnessGainDigitalLimit class manages digital gain limits that are applied
 * after sensor digitization. Digital gain is applied to the digital signal after
 * analog-to-digital conversion, providing additional amplification but potentially
 * introducing more noise compared to analog gain.
 *
 * This feature allows automatic brightness controllers to constrain the digital
 * gain values within specified limits, balancing brightness requirements with
 * acceptable noise levels.
 *
 * \see BrightnessLimit
 * \see peak::afl::Controller::SetGainDigitalLimit()
 * \see peak::afl::Controller::GetGainDigitalLimit()
 * \see BrightnessGainAnalogLimit
 *
 * \since 1.8
 */
class BrightnessGainDigitalLimit : public BrightnessLimit
{
public:
    /*!
     * \brief Constructs a digital gain limit feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the digital gain limits. The controller must
     *                      support digital gain operations.
     *
     * \pre controller must not be null
     * \pre controller must support digital gain functionality
     *
     * \since 1.8
     */
    explicit BrightnessGainDigitalLimit(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the digital gain limits
     *
     * \param[in] value The interval defining the minimum and maximum digital gain limits
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the limits are invalid or if the controller is in an invalid state
     *
     * \see Get()
     *
     * \since 1.8
     */
    void Set(const IntervalD& value) override
    {
        m_controller->SetGainDigitalLimit({ value.GetMinimum(), value.GetMaximum() });
    }

    /*!
     * \brief Gets the current digital gain limits
     *
     * \return The current digital gain limits as an IntervalD object
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state
     *
     * \see Set()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD IntervalD Get() const override
    {
        const auto result = m_controller->GetGainDigitalLimit();
        return { result.min, result.max };
    }

private:
    std::shared_ptr<peak::afl::Controller> m_controller;
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Combined gain limit feature implementation for brightness controllers
 *
 * The BrightnessGainCombinedLimit class manages combined analog and digital gain
 * limits as a unified control. This feature treats both analog and digital gain
 * as a single combined gain parameter, allowing for simplified gain management
 * when the distinction between analog and digital gain is not critical.
 *
 * This approach is useful when the camera system handles the distribution between
 * analog and digital gain automatically, or when the application requires unified
 * gain control without concern for the specific gain type.
 *
 * \see BrightnessLimit
 * \see peak::afl::Controller::SetGainCombinedLimit()
 * \see peak::afl::Controller::GetGainCombinedLimit()
 * \see BrightnessGainAnalogLimit
 * \see BrightnessGainDigitalLimit
 *
 * \since 1.8
 */
class BrightnessGainCombinedLimit : public BrightnessLimit
{
public:
    /*!
     * \brief Constructs a combined gain limit feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the combined gain limits. The controller must
     *                      support combined gain operations.
     *
     * \pre controller must not be null
     * \pre controller must support combined gain functionality
     *
     * \since 1.8
     */
    explicit BrightnessGainCombinedLimit(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the combined gain limits
     *
     * \param[in] value The interval defining the minimum and maximum combined gain limits
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the limits are invalid or if the controller is in an invalid state
     *
     * \see Get()
     *
     * \since 1.8
     */
    void Set(const IntervalD& value) override
    {
        m_controller->SetGainCombinedLimit({ value.GetMinimum(), value.GetMaximum() });
    }

    /*!
     * \brief Gets the current combined gain limits
     *
     * \return The current combined gain limits as an IntervalD object
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state
     *
     * \see Set()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD IntervalD Get() const override
    {
        const auto result = m_controller->GetGainCombinedLimit();
        return { result.min, result.max };
    }

private:
    std::shared_ptr<peak::afl::Controller> m_controller;
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Host gain limit feature implementation for brightness controllers
 *
 * The BrightnessGainHostLimit class manages host-side gain limits that are applied
 * in software on the host system rather than in the camera hardware. Host gain
 * provides additional amplification through software processing, allowing for
 * extended gain ranges beyond hardware capabilities.
 *
 * This feature is particularly useful when hardware gain limits are insufficient
 * for the required brightness levels, or when software-based gain processing
 * provides better control over the amplification characteristics.
 *
 * \note Host gain is applied after image acquisition and may affect processing
 *       performance depending on the implementation.
 *
 * \see BrightnessLimit
 * \see peak::afl::Controller::SetGainHostLimit()
 * \see peak::afl::Controller::GetGainHostLimit()
 * \see BrightnessGainAnalogLimit
 * \see BrightnessGainDigitalLimit
 *
 * \since 1.8
 */
class BrightnessGainHostLimit : public BrightnessLimit
{
public:
    /*!
     * \brief Constructs a host gain limit feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the host gain limits. The controller must
     *                      support host gain operations.
     *
     * \pre controller must not be null
     * \pre controller must support host gain functionality
     *
     * \since 1.8
     */
    explicit BrightnessGainHostLimit(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the host gain limits
     *
     * \param[in] value The interval defining the minimum and maximum host gain limits
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the limits are invalid or if the controller is in an invalid state
     *
     * \see Get()
     *
     * \since 1.8
     */
    void Set(const IntervalD& value) override
    {
        m_controller->SetGainHostLimit({ value.GetMinimum(), value.GetMaximum() });
    }

    /*!
     * \brief Gets the current host gain limits
     *
     * \return The current host gain limits as an IntervalD object
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state
     *
     * \see Set()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD IntervalD Get() const override
    {
        const auto result = m_controller->GetGainHostLimit();
        return { result.min, result.max };
    }

private:
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
