/*!
 * \file    peak_afl_brightness_algorithm.hpp
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
/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Brightness analysis algorithm enumeration
 *
 * Defines the available algorithms for analyzing brightness in automatic
 * exposure and brightness control systems. Each algorithm provides a
 * different method for calculating the representative brightness value
 * from the image data.
 *
 * \since 1.8
 */
enum class BrightnessAnalysisAlgorithm
{
    /*! \brief Median-based brightness calculation - uses the median value of pixel intensities */
    Median,
    /*! \brief Mean-based brightness calculation - uses the average value of pixel intensities */
    Mean
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Converts BrightnessAnalysisAlgorithm enumeration to string representation
 *
 * \param[in] algorithm The brightness analysis algorithm to convert
 * \return String representation of the algorithm
 * \throws peak::afl::error::InvalidParameterException if algorithm is unknown
 *
 * \see BrightnessAnalysisAlgorithm
 *
 * \since 1.8
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(BrightnessAnalysisAlgorithm algorithm)
{
    if (algorithm == BrightnessAnalysisAlgorithm::Mean)
    {
        return "Mean";
    }
    if (algorithm == BrightnessAnalysisAlgorithm::Median)
    {
        return "Median";
    }

    throw peak::afl::error::InvalidParameterException(
        "The given brightness algorithm is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Stream insertion operator for BrightnessAnalysisAlgorithm enumeration
 *
 * Enables direct output of BrightnessAnalysisAlgorithm values to output streams
 * using their string representation.
 *
 * \param[in,out] os The output stream to write to
 * \param[in] algorithm The BrightnessAnalysisAlgorithm value to output
 * \return Reference to the output stream for chaining
 *
 * \note Uses ToString() function for string conversion
 *
 * \see ToString(BrightnessAnalysisAlgorithm)
 * \see BrightnessAnalysisAlgorithm
 *
 * \since 1.8
 */
inline std::ostream& operator<<(std::ostream& os, BrightnessAnalysisAlgorithm algorithm)
{
    return os << ToString(algorithm);
}

namespace features
{
namespace detail
{
PEAK_COMMON_NO_DISCARD inline BrightnessAnalysisAlgorithm ToBrightnessAnalysisAlgorithm(const std::string& algorithm)
{
    if (algorithm == "Median")
    {
        return BrightnessAnalysisAlgorithm::Median;
    }
    if (algorithm == "Mean")
    {
        return BrightnessAnalysisAlgorithm::Mean;
    }

    throw peak::afl::error::InvalidParameterException(
        "The given brightness algorithm " + algorithm + " is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

PEAK_COMMON_NO_DISCARD inline peak_afl_controller_brightness_algorithm ToCType(BrightnessAnalysisAlgorithm algorithm)
{
    if (algorithm == BrightnessAnalysisAlgorithm::Median)
    {
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_ALGORITHM_MEDIAN;
    }
    if (algorithm == BrightnessAnalysisAlgorithm::Mean)
    {
        return PEAK_AFL_CONTROLLER_BRIGHTNESS_ALGORITHM_MEAN;
    }

    throw peak::afl::error::InternalErrorException("The given brightness algorithm is unknown!", PEAK_AFL_STATUS_ERROR);
}

PEAK_COMMON_NO_DISCARD inline BrightnessAnalysisAlgorithm ToBrightnessAnalysisAlgorithm(
    peak_afl_controller_brightness_algorithm algorithm)
{
    if (algorithm == PEAK_AFL_CONTROLLER_BRIGHTNESS_ALGORITHM_MEDIAN)
    {
        return BrightnessAnalysisAlgorithm::Median;
    }
    if (algorithm == PEAK_AFL_CONTROLLER_BRIGHTNESS_ALGORITHM_MEAN)
    {
        return BrightnessAnalysisAlgorithm::Mean;
    }

    throw peak::afl::error::InternalErrorException("The given brightness algorithm is unknown!", PEAK_AFL_STATUS_ERROR);
}
} // namespace detail

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Brightness algorithm feature implementation for auto controllers
 *
 * The BrightnessAlgorithm class provides a feature interface for managing the
 * brightness analysis algorithm used by auto controllers. This feature controls
 * how the automatic exposure and brightness systems calculate the representative
 * brightness value from the image data.
 *
 * Different algorithms provide different characteristics:
 * - **Median**: More robust to outliers and extreme values, provides stable results
 *   in scenes with high contrast or bright/dark spots
 * - **Mean**: Faster computation, considers all pixel values equally, may be
 *   influenced by extreme brightness values
 *
 * This class inherits from IFeature<BrightnessAnalysisAlgorithm> and provides
 * serialization support for configuration persistence.
 *
 * \note Algorithm availability may vary based on the underlying controller
 *       implementation and hardware capabilities.
 *
 * \see IFeature
 * \see BrightnessAnalysisAlgorithm
 * \see peak::afl::Controller::SetBrightnessAlgorithm()
 * \see peak::afl::Controller::GetBrightnessAlgorithm()
 *
 * \since 1.8
 */
class BrightnessAlgorithm : public IFeature<BrightnessAnalysisAlgorithm>
{
public:
    /*!
     * \brief Constructs a BrightnessAlgorithm feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                      to manage the brightness algorithm parameter. The controller
     *                      must support brightness algorithm operations.
     *
     * \pre controller must not be null
     * \pre controller must support brightness algorithm functionality
     *
     * \since 1.8
     */
    explicit BrightnessAlgorithm(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the brightness analysis algorithm
     *
     * Sets the algorithm used for analyzing brightness in automatic exposure
     * and brightness control. Different algorithms provide different characteristics
     * in terms of robustness, speed, and sensitivity to outliers.
     *
     * \param[in] value The brightness analysis algorithm to set. Must be one of
     *                 the values from BrightnessAnalysisAlgorithm enumeration.
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the algorithm is not supported or if the controller is in
     *         an invalid state.
     *
     * \see Get()
     * \see BrightnessAnalysisAlgorithm
     *
     * \since 1.8
     */
    void Set(const BrightnessAnalysisAlgorithm& value) override
    {
        m_controller->SetBrightnessAlgorithm(detail::ToCType(value));
    }

    /*!
     * \brief Gets the current brightness analysis algorithm
     *
     * Retrieves the currently configured algorithm used for brightness
     * analysis in automatic exposure and brightness control.
     *
     * \return The current brightness analysis algorithm
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see BrightnessAnalysisAlgorithm
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD BrightnessAnalysisAlgorithm Get() const override
    {
        return detail::ToBrightnessAnalysisAlgorithm(m_controller->GetBrightnessAlgorithm());
    }

    /*!
     * \brief Serializes the current brightness algorithm to an archive
     *
     * Stores the current brightness analysis algorithm in the provided archive for
     * configuration persistence. The algorithm is stored with the key "BrightnessAlgorithm".
     *
     * \param[in,out] archive The archive to write the brightness algorithm to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetString("BrightnessAlgorithm", ToString(Get()));
    }

    /*!
     * \brief Deserializes the brightness algorithm from an archive
     *
     * Loads the brightness analysis algorithm from the provided archive and applies it
     * to the controller. The algorithm is expected to be stored with the key "BrightnessAlgorithm".
     *
     * \param[in] archive The archive to read the brightness algorithm from
     *
     * \throws May throw serialization exceptions if the archive operation fails
     * \throws May throw controller exceptions if the deserialized algorithm is invalid
     *
     * \see Serialize()
     *
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        Set(detail::ToBrightnessAnalysisAlgorithm(archive.GetString("BrightnessAlgorithm")));
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual brightness algorithm functionality.
     * This controller must support brightness algorithm operations and remain valid
     * for the lifetime of this BrightnessAlgorithm feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
