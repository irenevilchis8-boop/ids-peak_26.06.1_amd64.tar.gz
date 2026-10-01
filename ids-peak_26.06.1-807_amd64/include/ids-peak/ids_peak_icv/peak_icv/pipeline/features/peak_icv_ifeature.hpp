/*!
 * \file    peak_icv_ifeature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>

namespace peak
{
namespace pipeline
{
namespace features
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_features
 *
 * \brief Abstract base class for all image processing pipeline features.
 *
 * IFeature defines the common interface that all pipeline features must implement.
 * Features represent configurable image processing operations that can be enabled
 * or disabled within an image processing pipeline.
 *
 * Each feature provides:
 * - Enable/disable functionality through SetEnabled() and IsEnabled()
 * - Reset capability to restore default settings via ResetToDefault()
 * - Feature-specific configuration methods (implemented in derived classes)
 *
 * Features are typically used within a pipeline context where they can be
 * selectively enabled or disabled to customize the image processing workflow.
 * When a feature is disabled, it has no effect on the processed image.
 *
 * \note All derived classes must implement the three pure virtual methods:
 *       SetEnabled(), IsEnabled(), and ResetToDefault().
 *
 * \note The enabled state is independent of the feature's configuration.
 *       Calling ResetToDefault() will reset the feature's parameters to their
 *       default values but will not change the enabled/disabled state.
 *
 * Example usage:
 * \code
 * // Assuming we have a concrete feature implementation
 * std::unique_ptr<IFeature> feature = std::make_unique<SomeConcreteFeature>();
 *
 * // Enable the feature
 * feature->SetEnabled(true);
 *
 * // Check if enabled
 * if (feature->IsEnabled()) {
 *     // Feature will be applied during processing
 * }
 *
 * // Reset to default configuration (but keep enabled state)
 * feature->ResetToDefault();
 * \endcode
 *
 * \see ColorCorrectionFeature, SharpeningFeature, GainFeature
 * \since ids_peak_icv 1.0
 */
class IFeature
{
public:
    virtual ~IFeature() = default;

    /*!
     * \brief Enables or disables the feature.
     *
     * \param enabled Set to \c true to enable, or \c false to disable.
     *
     * \since ids_peak_icv 1.0
     */
    virtual void SetEnabled(bool enabled) = 0;

    /*!
     * \brief Gets whether this feature is currently enabled.
     *
     * \return \c true if enabled; otherwise \c false.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual bool IsEnabled() const = 0;

    /*!
     * \brief Restores the feature's default values.
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    virtual void ResetToDefault() = 0;
};

} // namespace features
} // namespace pipeline 
} // namespace peak
