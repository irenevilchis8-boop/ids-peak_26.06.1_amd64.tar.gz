/*!
 * \file    peak_afl_sharpness_algorithm.hpp
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
 * \brief Focus sharpness algorithm enumeration
 *
 * Defines the available algorithms for measuring image sharpness in automatic
 * focus systems. Each algorithm provides different characteristics for detecting
 * the optimal focus position based on image analysis.
 *
 * \since 1.8
 */
enum class FocusSharpnessAlgorithm
{
    /*! \brief Automatic algorithm selection - controller chooses the best algorithm
     *
     * \deprecated This value is deprecated. The automatic selection always defaults to
     *             the Tenengrad algorithm. Use
     *             \ref FocusSharpnessAlgorithm::Tenengrad instead.
     */
    Auto PEAK_AFL_DEPRECATED_ENUM_ATTR,
    /*! \brief Tenengrad algorithm - gradient-based sharpness measurement */
    Tenengrad,
    /*! \brief Sobel algorithm - edge detection based sharpness measurement */
    Sobel,
    /*! \brief Mean score algorithm - statistical sharpness measurement */
    MeanScore,
    /*! \brief Histogram variance algorithm - variance-based sharpness measurement */
    HistogramVariance
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Converts FocusSharpnessAlgorithm enumeration to string representation
 *
 * \param[in] algorithm The focus sharpness algorithm to convert
 * \return String representation of the algorithm
 * \throws peak::afl::error::InvalidParameterException if algorithm is unknown
 *
 * \see FocusSharpnessAlgorithm
 *
 * \since 1.8
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(FocusSharpnessAlgorithm algorithm)
{
    // clang-format off
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    if (algorithm == FocusSharpnessAlgorithm::Auto)
    {
        return "Auto";
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
    // clang-format on
    if (algorithm == FocusSharpnessAlgorithm::HistogramVariance)
    {
        return "HistogramVariance";
    }
    if (algorithm == FocusSharpnessAlgorithm::MeanScore)
    {
        return "MeanScore";
    }
    if (algorithm == FocusSharpnessAlgorithm::Sobel)
    {
        return "Sobel";
    }
    if (algorithm == FocusSharpnessAlgorithm::Tenengrad)
    {
        return "Tenengrad";
    }
    throw peak::afl::error::InvalidParameterException(
        "The given focus sharpness algorithm is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Stream insertion operator for FocusSharpnessAlgorithm enumeration
 *
 * Enables direct output of FocusSharpnessAlgorithm values to output streams
 * using their string representation.
 *
 * \param[in,out] os The output stream to write to
 * \param[in] algorithm The FocusSharpnessAlgorithm value to output
 * \return Reference to the output stream for chaining
 *
 * \note Uses ToString() function for string conversion
 *
 * \see ToString(FocusSharpnessAlgorithm)
 * \see FocusSharpnessAlgorithm
 *
 * \since 1.8
 */
inline std::ostream& operator<<(std::ostream& os, FocusSharpnessAlgorithm algorithm)
{
    return os << ToString(algorithm);
}

namespace features
{
namespace detail
{
PEAK_COMMON_NO_DISCARD inline FocusSharpnessAlgorithm ToFocusSharpnessAlgorithm(const std::string& algorithm)
{
    if (algorithm == "Auto")
    {
        // clang-format off
        PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
        return FocusSharpnessAlgorithm::Auto;
        PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
        // clang-format on
    }
    if (algorithm == "Tenengrad")
    {
        return FocusSharpnessAlgorithm::Tenengrad;
    }
    if (algorithm == "Sobel")
    {
        return FocusSharpnessAlgorithm::Sobel;
    }
    if (algorithm == "MeanScore")
    {
        return FocusSharpnessAlgorithm::MeanScore;
    }
    if (algorithm == "HistogramVariance")
    {
        return FocusSharpnessAlgorithm::HistogramVariance;
    }

    throw peak::afl::error::InvalidParameterException(
        "The given focus sharpness algorithm " + algorithm + " is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

PEAK_COMMON_NO_DISCARD inline FocusSharpnessAlgorithm ToFocusSharpnessAlgorithm(peak_afl_controller_sharpness_algorithm algorithm)
{
    // clang-format off
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    switch (algorithm)
    {
    case PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_AUTO:
        return FocusSharpnessAlgorithm::Auto;
    case PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_TENENGRAD:
        return FocusSharpnessAlgorithm::Tenengrad;
    case PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_SOBEL:
        return FocusSharpnessAlgorithm::Sobel;
    case PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_MEAN_SCORE:
        return FocusSharpnessAlgorithm::MeanScore;
    case PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_HISTOGRAM_VARIANCE:
        return FocusSharpnessAlgorithm::HistogramVariance;
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
    // clang-format on

    throw peak::afl::error::InternalErrorException("Invalid focus sharpness algorithm!", PEAK_AFL_STATUS_ERROR);
}

PEAK_COMMON_NO_DISCARD inline peak_afl_controller_sharpness_algorithm ToCType(FocusSharpnessAlgorithm algorithm)
{
    // clang-format off
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    switch (algorithm)
    {
    case FocusSharpnessAlgorithm::Auto:
        return PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_AUTO;
    case FocusSharpnessAlgorithm::Tenengrad:
        return PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_TENENGRAD;
    case FocusSharpnessAlgorithm::Sobel:
        return PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_SOBEL;
    case FocusSharpnessAlgorithm::MeanScore:
        return PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_MEAN_SCORE;
    case FocusSharpnessAlgorithm::HistogramVariance:
        return PEAK_AFL_CONTROLLER_SHARPNESS_ALGORITHM_HISTOGRAM_VARIANCE;
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
    // clang-format on

    throw peak::afl::error::InternalErrorException("Invalid focus sharpness algorithm!", PEAK_AFL_STATUS_ERROR);
}
} // namespace detail

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Sharpness algorithm feature implementation for auto focus controllers
 *
 * The SharpnessAlgorithm class provides a feature interface for managing the
 * sharpness measurement algorithm used by auto focus controllers. This feature
 * controls how the automatic focus system measures image sharpness to determine
 * the optimal focus position.
 *
 * Different algorithms provide different characteristics:
 * - **Auto**: Lets the controller automatically select the best algorithm
 * - **Tenengrad**: Gradient-based, good for high-contrast edges
 * - **Sobel**: Edge detection based, robust for various scene types
 * - **MeanScore**: Statistical approach, good for textured surfaces
 * - **HistogramVariance**: Variance-based, effective for uniform lighting
 *
 * This class inherits from IListFeature<FocusSharpnessAlgorithm> and provides
 * both current algorithm management and a list of supported algorithms.
 *
 * \note Algorithm availability may vary based on the underlying controller
 *       implementation and image characteristics.
 *
 * \see IListFeature
 * \see FocusSharpnessAlgorithm
 * \see peak::afl::Controller::SetSharpnessAlgorithm()
 * \see peak::afl::Controller::GetSharpnessAlgorithm()
 *
 * \since 1.8
 */
class SharpnessAlgorithm : public IListFeature<FocusSharpnessAlgorithm>
{
public:
    /*!
     * \brief Constructs a SharpnessAlgorithm feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto focus controller that will be used
     *                      to manage the sharpness algorithm parameter. The controller must
     *                      support sharpness algorithm operations.
     *
     * \pre controller must not be null
     * \pre controller must support sharpness algorithm functionality
     *
     * \since 1.8
     */
    explicit SharpnessAlgorithm(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the focus sharpness algorithm
     *
     * Sets the algorithm that the automatic focus system will use to measure
     * image sharpness. Different algorithms provide different characteristics
     * for detecting optimal focus in various scene conditions.
     *
     * \param[in] value The focus sharpness algorithm to set. Must be one of the
     *                 algorithms supported by the controller (see GetList()).
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the algorithm is not supported or if the controller is in
     *         an invalid state.
     *
     * \see Get()
     * \see GetList()
     * \see FocusSharpnessAlgorithm
     *
     * \since 1.8
     */
    void Set(const FocusSharpnessAlgorithm& value) override
    {
        m_controller->SetSharpnessAlgorithm(detail::ToCType(value));
    }

    /*!
     * \brief Gets the current focus sharpness algorithm
     *
     * Retrieves the currently configured algorithm that the automatic
     * focus system is using to measure image sharpness.
     *
     * \return The current focus sharpness algorithm
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see GetList()
     * \see FocusSharpnessAlgorithm
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD FocusSharpnessAlgorithm Get() const override
    {
        return detail::ToFocusSharpnessAlgorithm(m_controller->GetSharpnessAlgorithm());
    }

    /*!
     * \brief Gets the list of supported focus sharpness algorithms
     *
     * Retrieves a list of all focus sharpness algorithms that are supported
     * by the current controller. This can be used to populate user interface
     * controls or to validate algorithm selections.
     *
     * \return A vector containing all supported focus sharpness algorithms
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see Get()
     * \see FocusSharpnessAlgorithm
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::vector<FocusSharpnessAlgorithm> GetList() const override
    {
        const auto cAlgorithms = m_controller->GetSharpnessAlgorithmList();
        std::vector<FocusSharpnessAlgorithm> algorithms;
        algorithms.reserve(cAlgorithms.size());

        std::transform(std::cbegin(cAlgorithms), std::cend(cAlgorithms), std::back_inserter(algorithms),
            [](const auto& value) { return detail::ToFocusSharpnessAlgorithm(value); });
        return algorithms;
    }

    /*!
     * \brief Serializes the current sharpness algorithm to an archive
     *
     * Stores the current focus sharpness algorithm in the provided archive for
     * configuration persistence. The algorithm is stored with the key "SharpnessAlgorithm".
     *
     * \param[in,out] archive The archive to write the sharpness algorithm to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetString("SharpnessAlgorithm", ToString(Get()));
    }

    /*!
     * \brief Deserializes the sharpness algorithm from an archive
     *
     * Loads the focus sharpness algorithm from the provided archive and applies it
     * to the controller. The algorithm is expected to be stored with the key "SharpnessAlgorithm".
     *
     * \param[in] archive The archive to read the sharpness algorithm from
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
        Set(detail::ToFocusSharpnessAlgorithm(archive.GetString("SharpnessAlgorithm")));
    }

private:
    /*!
     * \brief Shared pointer to the auto focus controller
     *
     * The controller instance that provides the actual sharpness algorithm functionality.
     * This controller must support sharpness algorithm operations and remain valid for
     * the lifetime of this SharpnessAlgorithm feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
