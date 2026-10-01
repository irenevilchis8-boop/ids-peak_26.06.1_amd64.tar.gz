/*!
 * \file    peak_afl_search_algorithm.hpp
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
 * \brief Focus search algorithm enumeration
 *
 * Defines the available algorithms for automatic focus search operations.
 * Each algorithm provides different characteristics in terms of speed,
 * accuracy, and robustness for various focusing scenarios.
 *
 * \since 1.8
 */
enum class FocusSearchAlgorithm
{
    /*!
     * \brief Automatic algorithm selection - default algorithm
     *
     * \deprecated This value is deprecated. The automatic selection always defaults to
     *             the Golden Ratio algorithm. Use
     *             \ref FocusSearchAlgorithm::GoldenRatio instead.
     */
    Auto PEAK_AFL_DEPRECATED_ENUM_ATTR,
    /*! \brief Golden ratio search - efficient for unimodal focus curves */
    GoldenRatio,
    /*! \brief Hill climbing search - good for local optimization */
    HillClimbing,
    /*! \brief Global search - comprehensive but slower search */
    GlobalSearch,
    /*! \brief Full scan - scans entire focus range for maximum accuracy */
    FullScan
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Converts FocusSearchAlgorithm enumeration to string representation
 *
 * \param[in] algorithm The focus search algorithm to convert
 * \return String representation of the algorithm
 * \throws peak::afl::error::InvalidParameterException if algorithm is unknown
 *
 * \see FocusSearchAlgorithm
 *
 * \since 1.8
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(FocusSearchAlgorithm algorithm)
{
    // clang-format off
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    switch (algorithm)
    {
    case FocusSearchAlgorithm::Auto:
        return "Auto";
    case FocusSearchAlgorithm::GoldenRatio:
        return "GoldenRatio";
    case FocusSearchAlgorithm::HillClimbing:
        return "HillClimbing";
    case FocusSearchAlgorithm::GlobalSearch:
        return "GlobalSearch";
    case FocusSearchAlgorithm::FullScan:
        return "FullScan";
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
    // clang-format on

    throw peak::afl::error::InvalidParameterException(
        "The given focus search algorithm is unknown!", PEAK_AFL_STATUS_INVALID_PARAMETER);
}

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Stream insertion operator for FocusSearchAlgorithm enumeration
 *
 * Enables direct output of FocusSearchAlgorithm values to output streams
 * using their string representation.
 *
 * \param[in,out] os The output stream to write to
 * \param[in] algorithm The FocusSearchAlgorithm value to output
 * \return Reference to the output stream for chaining
 *
 * \note Uses ToString() function for string conversion
 *
 * \see ToString(FocusSearchAlgorithm)
 * \see FocusSearchAlgorithm
 *
 * \since 1.8
 */
inline std::ostream& operator<<(std::ostream& os, FocusSearchAlgorithm algorithm)
{
    return os << ToString(algorithm);
}

namespace features
{
namespace detail
{
PEAK_COMMON_NO_DISCARD inline FocusSearchAlgorithm ToFocusSearchAlgorithm(const std::string& name)
{
    if (name == "Auto")
    {
        // clang-format off
        PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
        return FocusSearchAlgorithm::Auto;
        PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
        // clang-format on
    }
    if (name == "GoldenRatio")
    {
        return FocusSearchAlgorithm::GoldenRatio;
    }
    if (name == "HillClimbing")
    {
        return FocusSearchAlgorithm::HillClimbing;
    }
    if (name == "GlobalSearch")
    {
        return FocusSearchAlgorithm::GlobalSearch;
    }
    if (name == "FullScan")
    {
        return FocusSearchAlgorithm::FullScan;
    }

    throw peak::afl::error::InternalErrorException("Invalid focus search algorithm!", PEAK_AFL_STATUS_ERROR);
}

PEAK_COMMON_NO_DISCARD inline peak_afl_controller_algorithm ToCType(FocusSearchAlgorithm algorithm)
{
    // clang-format off
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    switch (algorithm)
    {
    case FocusSearchAlgorithm::Auto:
        return PEAK_AFL_CONTROLLER_ALGORITHM_AUTO;
    case FocusSearchAlgorithm::GoldenRatio:
        return PEAK_AFL_CONTROLLER_ALGORITHM_GOLDEN_RATIO_SEARCH;
    case FocusSearchAlgorithm::HillClimbing:
        return PEAK_AFL_CONTROLLER_ALGORITHM_HILL_CLIMBING_SEARCH;
    case FocusSearchAlgorithm::GlobalSearch:
        return PEAK_AFL_CONTROLLER_ALGORITHM_GLOBAL_SEARCH;
    case FocusSearchAlgorithm::FullScan:
        return PEAK_AFL_CONTROLLER_ALGORITHM_FULL_SCAN;
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
    // clang-format on

    throw peak::afl::error::InternalErrorException("Invalid focus search algorithm!", PEAK_AFL_STATUS_ERROR);
}

PEAK_COMMON_NO_DISCARD inline FocusSearchAlgorithm ToFocusSearchAlgorithm(peak_afl_controller_algorithm algorithm)
{
    // clang-format off
    PEAK_AFL_BEGIN_DISABLE_DEPRECATED_WARNINGS
    switch (algorithm)
    {
    case PEAK_AFL_CONTROLLER_ALGORITHM_AUTO:
        return FocusSearchAlgorithm::Auto;
    case PEAK_AFL_CONTROLLER_ALGORITHM_GOLDEN_RATIO_SEARCH:
        return FocusSearchAlgorithm::GoldenRatio;
    case PEAK_AFL_CONTROLLER_ALGORITHM_HILL_CLIMBING_SEARCH:
        return FocusSearchAlgorithm::HillClimbing;
    case PEAK_AFL_CONTROLLER_ALGORITHM_GLOBAL_SEARCH:
        return FocusSearchAlgorithm::GlobalSearch;
    case PEAK_AFL_CONTROLLER_ALGORITHM_FULL_SCAN:
        return FocusSearchAlgorithm::FullScan;
    }
    PEAK_AFL_END_DISABLE_DEPRECATED_WARNINGS
    // clang-format on

    throw peak::afl::error::InternalErrorException("Invalid focus search algorithm!", PEAK_AFL_STATUS_ERROR);
}
} // namespace detail

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Search algorithm feature implementation for auto focus controllers
 *
 * The SearchAlgorithm class provides a feature interface for managing the focus
 * search algorithm used by auto focus controllers. This feature controls which
 * algorithm the automatic focus system uses to find the optimal focus position.
 *
 * Different algorithms provide different trade-offs:
 * - **Auto**: Lets the controller automatically select the default algorithm
 * - **GoldenRatio**: Efficient binary search, good for smooth focus curves
 * - **HillClimbing**: Fast local search, good when starting near optimal focus
 * - **GlobalSearch**: Comprehensive search, more robust but slower
 * - **FullScan**: Scans entire range, most accurate but slowest
 *
 * This class inherits from IListFeature<FocusSearchAlgorithm> and provides both
 * current algorithm management and a list of supported algorithms.
 *
 * \note Algorithm availability may vary based on the underlying controller
 *       implementation and lens characteristics.
 *
 * \see IListFeature
 * \see FocusSearchAlgorithm
 * \see peak::afl::Controller::SetAlgorithm()
 * \see peak::afl::Controller::GetAlgorithm()
 * \see peak::afl::Controller::GetAlgorithmList()
 *
 * \since 1.8
 */
class SearchAlgorithm : public IListFeature<FocusSearchAlgorithm>
{
public:
    /*!
     * \brief Constructs a SearchAlgorithm feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto focus controller that will be used
     *                       to manage the search algorithm parameter. The controller must
     *                       support search algorithm operations.
     *
     * \pre controller must not be null
     * \pre controller must support search algorithm functionality
     *
     * \since 1.8
     */
    explicit SearchAlgorithm(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the focus search algorithm
     *
     * Sets the algorithm that the automatic focus system will use to find
     * the optimal focus position. Different algorithms provide different
     * trade-offs between speed, accuracy, and robustness.
     *
     * \param[in] value The focus search algorithm to set. Must be one of the
     *                  algorithms supported by the controller (see GetList()).
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the algorithm is not supported or if the controller is in
     *         an invalid state.
     *
     * \see Get()
     * \see GetList()
     * \see FocusSearchAlgorithm
     *
     * \since 1.8
     */
    void Set(const FocusSearchAlgorithm& value) override
    {
        m_controller->SetAlgorithm(detail::ToCType(value));
    }

    /*!
     * \brief Gets the current focus search algorithm
     *
     * Retrieves the currently configured algorithm that the automatic
     * focus system is using to find the optimal focus position.
     *
     * \return The current focus search algorithm
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see GetList()
     * \see FocusSearchAlgorithm
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD FocusSearchAlgorithm Get() const override
    {
        return detail::ToFocusSearchAlgorithm(m_controller->GetAlgorithm());
    }

    /*!
     * \brief Gets the list of supported focus search algorithms
     *
     * Retrieves a list of all focus search algorithms that are supported
     * by the current controller. This can be used to populate user interface
     * controls or to validate algorithm selections.
     *
     * \return A vector containing all supported focus search algorithms
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see Get()
     * \see FocusSearchAlgorithm
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::vector<FocusSearchAlgorithm> GetList() const override
    {
        const auto cAlgorithms = m_controller->GetAlgorithmList();

        std::vector<FocusSearchAlgorithm> algorithms;
        algorithms.reserve(cAlgorithms.size());

        std::transform(std::cbegin(cAlgorithms), std::cend(cAlgorithms), std::back_inserter(algorithms),
            [](const auto& value) { return detail::ToFocusSearchAlgorithm(value); });
        return algorithms;
    }

    /*!
     * \brief Serializes the current search algorithm to an archive
     *
     * Stores the current focus search algorithm in the provided archive for
     * configuration persistence. The algorithm is stored with the key "SearchAlgorithm".
     *
     * \param[in,out] archive The archive to write the search algorithm to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        archive.SetString("SearchAlgorithm", ToString(Get()));
    }

    /*!
     * \brief Deserializes the search algorithm from an archive
     *
     * Loads the focus search algorithm from the provided archive and applies it
     * to the controller. The algorithm is expected to be stored with the key "SearchAlgorithm".
     *
     * \param[in] archive The archive to read the search algorithm from
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
        Set(detail::ToFocusSearchAlgorithm(archive.GetString("SearchAlgorithm")));
    }

private:
    /*!
     * \brief Shared pointer to the auto focus controller
     *
     * The controller instance that provides the actual search algorithm functionality.
     * This controller must support search algorithm operations and remain valid for
     * the lifetime of this SearchAlgorithm feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
