/*!
 * \file    peak_afl_ifeature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/serialization/peak_common_iserializable.hpp>
#include <peak_common/types/peak_common_range.hpp>

namespace peak
{
namespace pipeline
{
namespace modules
{
namespace autofeature
{
/*! \brief Type alias for double-precision range values */
using RangeD = peak::common::detail::RangeT<double>;
/*! \brief Type alias for double-precision interval values */
using IntervalD = peak::common::detail::IntervalT<double>;

namespace features
{
/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Base interface for auto feature implementations
 *
 * The IFeature template class provides the fundamental interface for all
 * auto feature implementations in the pipeline system. It defines the basic
 * operations that all features must support: getting and setting values,
 * plus serialization for configuration persistence.
 *
 * This interface is designed to be type-safe and provides a consistent
 * API across all feature types, whether they manage simple values like
 * integers, complex types like algorithms, or geometric types like rectangles.
 *
 * All feature implementations inherit from this interface and must implement
 * the pure virtual methods for their specific value type.
 *
 * \tparam T The type of value that this feature manages (e.g., uint32_t,
 *           BrightnessAnalysisAlgorithm, Rectangle, etc.)
 *
 * \see IRangeFeature
 * \see IListFeature
 * \see peak::common::serialization::ISerializable
 *
 * \since 1.8
 */
template <typename T>
class IFeature : public peak::common::serialization::ISerializable
{
public:
    /*!
     * \brief Virtual destructor for proper cleanup of derived classes
     *
     * \since 1.8
     */
    virtual ~IFeature() = default;

    /*!
     * \brief Sets the feature value
     *
     * Sets the current value of this feature. The specific behavior depends
     * on the feature implementation and the type of value being managed.
     *
     * \param[in] value The new value to set for this feature
     *
     * \throws Implementation-specific exceptions may be thrown if the value
     *         is invalid or if the underlying system is in an invalid state.
     *
     * \see Get()
     *
     * \since 1.8
     */
    virtual void Set(const T& value) = 0;

    /*!
     * \brief Gets the current feature value
     *
     * Retrieves the current value of this feature from the underlying system.
     *
     * \return The current value of this feature
     *
     * \throws Implementation-specific exceptions may be thrown if the
     *         underlying system is in an invalid state.
     *
     * \see Set()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD virtual T Get() const = 0;
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Interface for features that have a valid range of values
 *
 * The IRangeFeature template class extends IFeature to provide additional
 * functionality for features that have a defined range of valid values.
 * This is useful for numeric parameters that have minimum, maximum, and
 * increment constraints.
 *
 * Examples of range features include:
 * - Auto target brightness (0-255 range)
 * - Auto tolerance (0-100 range)
 * - Skip frames (0-N range)
 * - Hysteresis values
 *
 * \tparam T The numeric type that this range feature manages
 *
 * \see IFeature
 * \see peak::common::detail::RangeT
 *
 * \since 1.8
 */
template <typename T>
class IRangeFeature : public IFeature<T>
{
public:
    /*!
     * \brief Gets the valid range for this feature's values
     *
     * Retrieves the minimum, maximum, and increment values that define
     * the valid range for this feature. This information can be used for
     * input validation and user interface constraints.
     *
     * \return A RangeT structure containing min, max, and increment values
     *
     * \throws Implementation-specific exceptions may be thrown if the
     *         underlying system is in an invalid state.
     *
     * \see IFeature::Set()
     * \see IFeature::Get()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD virtual peak::common::detail::RangeT<T> GetRange() const = 0;
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Interface for features that have a list of valid values
 *
 * The IListFeature template class extends IFeature to provide additional
 * functionality for features that have a discrete set of valid values.
 * This is useful for enumerated parameters like algorithms or modes.
 *
 * Examples of list features include:
 * - Focus search algorithms (Auto, GoldenRatio, HillClimbing, etc.)
 * - Brightness analysis algorithms (Mean, Median)
 * - Controller modes
 *
 * \tparam T The enumerated type that this list feature manages
 *
 * \see IFeature
 *
 * \since 1.8
 */
template <typename T>
class IListFeature : public IFeature<T>
{
public:
    /*!
     * \brief Gets the list of valid values for this feature
     *
     * Retrieves all valid values that this feature can be set to.
     * This information can be used for input validation and to populate
     * user interface controls like dropdown lists.
     *
     * \return A vector containing all valid values for this feature
     *
     * \throws Implementation-specific exceptions may be thrown if the
     *         underlying system is in an invalid state.
     *
     * \see IFeature::Set()
     * \see IFeature::Get()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD virtual std::vector<T> GetList() const = 0;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
