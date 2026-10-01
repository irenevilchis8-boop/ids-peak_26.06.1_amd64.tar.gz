/*!
 * \file    peak_icv_chromatic_adaption_feature.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-02-24
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_range.hpp>
#include <peak_icv/pipeline/detail/peak_icv_color_matrix_transformation_module.hpp>
#include <peak_icv/pipeline/features/peak_icv_ifeature.hpp>
#include <peak_icv/pipeline/types/peak_icv_chromatic_adaption_algorithm.hpp>
#include <peak_icv/pipeline/types/peak_icv_color_space.hpp>

namespace peak
{
namespace pipeline
{
namespace features
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_features
 *
 * \brief Adjusts to changes in lighting conditions to maintain consistent color perception despite variations in light sources.
 *
 * In industrial imaging, white balance can fail due to the lack of a neutral reference in the image, such as when the
 * scene contains no gray or white areas, or when the colors are unevenly distributed (as in images dominated by a single color).
 * In these cases, traditional white balance algorithms, like the gray world method, may fail to produce accurate color corrections.
 *
 * Chromatic adaptation provides an alternative solution by adjusting the image’s colors based on the known or
 * estimated correlated color temperature of the light source.
 *
 *
 * \note If chromatic adaption is used in combination with white balance, the result is indefinite.
 *
 * \defaults{defaults_feature_chromaticadaption|
 *   - chromatic adaption algorithm = Bradford
 *   - color space = SRGB_D65
 *   - color temperature = undefined (chromatic adaption won't be applied)
 * }
 *
 * \see \ref ColorSpace, \ref ChromaticAdaptionAlgorithm, \ref features::ColorCorrectionFeature
 *
 * \since ids_peak_icv 1.3
 */
class ChromaticAdaptionFeature : public IFeature
{
public:
    /*!
     * \brief Creates a ChromaticAdaptionFeature for an existing color matrix transformation module.
     *
     * \param module Reference to the underlying \ref detail::ColorMatrixTransformationModule.
     *
     * \since ids_peak_icv 1.3
     */
    explicit ChromaticAdaptionFeature(detail::ColorMatrixTransformationModule& module);

    /*!
     * \copydoc IFeature::SetEnabled
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \copydoc IFeature::IsEnabled
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Resets the chromatic adaption configuration to the default values.
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.3
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the target color space.
     *
     * A color space is a specific implementation of a color model, mapping colors to a defined range of values
     * (e.g., standard primaries, white point, and gamma).
     *
     * \param colorSpace The color space to set.
     *
     * \since ids_peak_icv 1.3
     */
    void SetTargetColorSpace(ColorSpace colorSpace);

    /*!
     * \brief Retrieves the current target color space.
     *
     * \returns The currently set color space.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD ColorSpace GetTargetColorSpace() const;

    /*!
     * \brief Sets the algorithm used for chromatic adaption.
     *
     * The algorithms use a CAT (chromatic adaptation transform) matrix.
     *
     * \param algorithm The chromatic adaption algorithm to set.
     *
     * \since ids_peak_icv 1.3
     */
    void SetAlgorithm(ChromaticAdaptionAlgorithm algorithm);

    /*!
     * \brief Retrieves the current chromatic adaption algorithm.
     *
     * \returns The currently set chromatic adaption algorithm.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD ChromaticAdaptionAlgorithm GetAlgorithm() const;

    /*!
     * \brief Sets the color temperature of the light source.
     * If no color temperature is explicitly set the chromatic adaption won't be applied.
     *
     * \param kelvin The color temperature in Kelvin to set. Must be within the allowed \ref GetColorTemperatureRange.
     *
     * \since ids_peak_icv 1.3
     */
    void SetColorTemperature(uint32_t kelvin);

    /*!
     * \brief Retrieves the current color temperature.
     *
     * \returns The current color temperature in Kelvin.
     *
     * \throws NotPossibleException If the color temperature has not been set (it has no default value).
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetColorTemperature() const;

    /*!
     * \brief Checks whether a color temperature has been set.
     *
     * \returns True if a color temperature is set, false otherwise.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD bool HasColorTemperature() const;

    /*!
     * \brief Returns the allowed temperature range for the current combination of color space and algorithm.
     *
     * \returns The allowed temperature range in Kelvin.
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD peak::common::RangeU GetColorTemperatureRange() const;

private:
    detail::ColorMatrixTransformationModule& m_module;
};

inline ChromaticAdaptionFeature::ChromaticAdaptionFeature(detail::ColorMatrixTransformationModule& module)
    : m_module{ module }
{}

inline void ChromaticAdaptionFeature::SetEnabled(bool enabled)
{
    m_module.SetChromaticAdaptionEnabled(enabled);
}

inline bool ChromaticAdaptionFeature::IsEnabled() const
{
    return m_module.IsChromaticAdaptionEnabled();
}

inline void ChromaticAdaptionFeature::ResetToDefault()
{
    m_module.ResetChromaticAdaption();
}

inline void ChromaticAdaptionFeature::SetTargetColorSpace(ColorSpace colorSpace)
{
    m_module.SetTargetColorSpace(colorSpace);
}

inline ColorSpace ChromaticAdaptionFeature::GetTargetColorSpace() const
{
    return m_module.GetTargetColorSpace();
}

inline void ChromaticAdaptionFeature::SetAlgorithm(ChromaticAdaptionAlgorithm algorithm)
{
    m_module.SetChromaticAdaptionAlgorithm(algorithm);
}

inline ChromaticAdaptionAlgorithm ChromaticAdaptionFeature::GetAlgorithm() const
{
    return m_module.GetChromaticAdaptionAlgorithm();
}

inline void ChromaticAdaptionFeature::SetColorTemperature(uint32_t kelvin)
{
    m_module.SetColorTemperature(kelvin);
}

inline uint32_t ChromaticAdaptionFeature::GetColorTemperature() const
{
    return m_module.GetColorTemperature();
}

inline bool ChromaticAdaptionFeature::HasColorTemperature() const
{
    return m_module.HasColorTemperature();
}

inline peak::common::RangeU ChromaticAdaptionFeature::GetColorTemperatureRange() const
{
    return m_module.GetColorTemperatureRange();
}

} // namespace features
} // namespace pipeline 
} // namespace peak
