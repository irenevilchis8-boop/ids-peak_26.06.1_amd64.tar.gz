/*!
 * \file    peak_ipl_chromatic_adaption.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-04-01
 * \since   1.16
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_ipl/types/peak_ipl_color_correction_factors.hpp>
#include <peak_ipl/types/peak_ipl_range.hpp>
#include <peak_ipl/backend/peak_ipl_backend.h>
#include <peak_ipl/exception/peak_ipl_exception.hpp>

/*!
 * \namespace peak::ipl
 * \brief The "peak::ipl" namespace contains the whole image processing library.
 */

namespace peak
{
namespace ipl
{
/*!
 * \ingroup ids_peak_ipl_algorithm
 * \brief Adjust to changes in lighting conditions to maintain consistent color perception despite variations in light sources.
 *
 * In industrial imaging, white balance can fail due to the lack of a neutral reference in the image, such as when the
 * scene contains no gray or white areas, or when the colors are unevenly distributed (as in images dominated by a single color).
 * In these cases, traditional white balance algorithms, like the gray world method, may fail to produce accurate color corrections.
 *
 * Chromatic adaptation provides an alternative solution by adjusting the image’s colors based on the known or
 * estimated correlated color temperature of the light source.
 *
 * \note
 * If chromatic adaption is used in combination with white balance, the result is indefinite.
 */
class ChromaticAdapter final
{
public:
    /*!
     * \brief Enumeration that defines the available color spaces.
     *
     * A color space is a specific implementation of a color model, mapping colors to a defined range of values.
     * For example, sRGB is a standardized color space based on the RGB color model, but it also defines color primaries,
     * the white point, and gamma to ensure consistent color representation across various platforms and devices.
     */
    enum class ColorSpace
    {
        //! sRGB (standard RGB): standard illuminant D50 (5000 K), gamma 2.2.
        SRGB_D50 = PEAK_IPL_CHROMATIC_ADAPTER_COLOR_SPACE_SRGB_D50,

        //! sRGB (standard RGB): standard illuminant D65 (6500 K), gamma 2.2.
        SRGB_D65 = PEAK_IPL_CHROMATIC_ADAPTER_COLOR_SPACE_SRGB_D65,

        //! CIE-RGB: standard illuminant E (equal energy distribution), gamma 2.2.
        CIE_RGB_E = PEAK_IPL_CHROMATIC_ADAPTER_COLOR_SPACE_CIE_RGB_E,

        //! ECI-RGB: standard illuminant D50 (5000 K), gamma 1.8.
        ECI_RGB_D50 = PEAK_IPL_CHROMATIC_ADAPTER_COLOR_SPACE_ECI_RGB_D50,

        //! Adobe RGB: standard illuminant D65 (6500 K), gamma 2.2.
        Adobe_RGB_D65 = PEAK_IPL_CHROMATIC_ADAPTER_COLOR_SPACE_ADOBE_RGB_D65
    };

    /*!
     * \brief Enumeration that defines the available chromatic adaption algorithms.
     *
     * The algorithms use a CAT (chromatic adaptation transform) matrix for [chromatic adaption](#chromatic_adaption).
     * There are various available CATs describing the transformation.
     */
    enum class Algorithm
    {
        /*! The legacy algorithm */
        Legacy = PEAK_IPL_CHROMATIC_ADAPTER_ALGORITHM_LEGACY,

        /*! The Bradford CAT matrix algorithm. This is the default. */
        Bradford = PEAK_IPL_CHROMATIC_ADAPTER_ALGORITHM_BRADFORD,
    };

    /*! \brief Constructor for a new Chromatic Adapter instance
     *
     * \since 1.16
     */
    ChromaticAdapter();

    /*! \brief Destructor for the Chromatic Adapter
     *
     * \since 1.16
     */
    ~ChromaticAdapter();

    /*! \brief Copy Constructor for a new Chromatic Adapter instance
     *
     * \note This only creates a shallow copy. See \ref shallowCopy for a detailed explanation.
     *
     * \param[in] other The other instance to acquire a reference for.
     *
     * \since 1.16
     */
    ChromaticAdapter(const ChromaticAdapter& other);

    /*! \brief Copy assigment for Chromatic Adapter instance
     *
     * Acquires a reference from \p other to this instance.
     * If this instance already has a reference, it will be destroyed.
     *
     * \note See \ref shallowCopy for a detailed explanation.
     *
     * \param[in] other The other instance to acquire a reference for.
     *
     * \since 1.16
     */
    ChromaticAdapter& operator=(const ChromaticAdapter& other);

    /*! \brief Move constructor for Chromatic Adapter instance
     *
     * Moves the instance from \p other to this, leaving \p other in an invalid state.
     *
     * \param[in] other The other instance to move.
     *
     * \since 1.16
     */
    ChromaticAdapter(ChromaticAdapter&& other) noexcept;

    /*! \brief Move assignment for Chromatic Adapter instance
     *
     * Moves the instance from \p other to this, leaving \p other in an invalid state.
     *
     * \param[in] other The other instance to move.
     *
     * \since 1.16
     */
    ChromaticAdapter& operator=(ChromaticAdapter&& other) noexcept;

    /*!
     * \brief Get the target color space
     *
     * There are many available color spaces.
     * The implemented color spaces are listed in the enum \ref ColorSpace.
     *
     * \returns The currently set color space.
     *
     * \since 1.16
     */
    PEAK_IPL_NO_DISCARD ColorSpace TargetColorSpace() const;

    /*!
     * \brief Set the target color space
     *
     * The available color spaces are listed in the enum \ref ColorSpace.
     *
     * \param[in] colorSpace The color space to set.
     *
     * \since 1.16
     */
    void SetTargetColorSpace(ColorSpace colorSpace);

    /*!
     * \brief Get the current algorithm used for chromatic adaption
     *
     * The implemented algorithms are listed in the enum \ref Algorithm.
     *
     * \returns The currently set algorithm.
     *
     * \since 1.16
     */
    PEAK_IPL_NO_DISCARD Algorithm AdaptionAlgorithm() const;

    /*!
     * \brief Set the algorithm used for chromatic adaption
     *
     * The available algorithms are listed in the enum \ref Algorithm.
     *
     * \param[in] algorithm The algorithm to set.
     *
     * \since 1.16
     */
    void SetAdaptionAlgorithm(Algorithm algorithm);

    /*!
     * \brief Returns the allowed temperature range for the current combination of color space and algorithm.
     *
     * \returns The allowed temperature range in Kelvin.
     *
     * \since 1.16
     */
    PEAK_IPL_NO_DISCARD Range<uint32_t> TemperatureRange() const;

    /*!
     * \brief Calculate the color correction factors for colorTemperature using the current algorithm and color space.
     *
     * The optional parameter \p correctionFactors can be used if the chromatic adaption is to be applied in parallel
     * with another color correction, e.g. the HQ matrix for the camera filter glass. The result will be a
     * matrix multiplication of the initial CCM and the chromatic adaption. It can directly be used.
     * When using the \ref ColorCorrector module, it might be advantageous to adjust an already set CCM using the comfort function
     * \ref ColorCorrector::ApplyChromaticAdaption
     *
     * \param[in] colorTemperature  The color temperature in Kelvin for which the factors are be.
     * \param[in] correctionFactors The input color correction matrix. Default is the identity matrix.
     *
     * \returns The calculated color correction factors.
     *
     * \since 1.16
     */
    PEAK_IPL_NO_DISCARD ColorCorrectionFactors CalculateColorCorrectionMatrix(uint32_t colorTemperature,
        const ColorCorrectionFactors& correctionFactors = ColorCorrectionFactors::Identity()) const;

private:
    PEAK_IPL_CHROMATIC_ADAPTER_HANDLE m_backendHandle{};
};

inline ChromaticAdapter::ChromaticAdapter()
{
    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_Construct(&m_backendHandle);
    });
}

inline ChromaticAdapter::~ChromaticAdapter()
{
    if (m_backendHandle)
    {
        (void)PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_Destruct(m_backendHandle);
    }
}

inline ChromaticAdapter::ChromaticAdapter(const ChromaticAdapter& other)
{
    if (other.m_backendHandle)
    {
        ExecuteAndMapReturnCodes(
            [&] { return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_Acquire(other.m_backendHandle); });
    }

    m_backendHandle = other.m_backendHandle;
}

inline ChromaticAdapter& ChromaticAdapter::operator=(const ChromaticAdapter& other)
{
    if (this != &other)
    {
        if (m_backendHandle)
        {
            (void)PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_Destruct(m_backendHandle);
        }

        if (other.m_backendHandle)
        {
            ExecuteAndMapReturnCodes(
                [&] { return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_Acquire(other.m_backendHandle); });
        }
    }

    m_backendHandle = other.m_backendHandle;

    return *this;
}

inline ChromaticAdapter::ChromaticAdapter(ChromaticAdapter&& other) noexcept
{
    *this = std::move(other);
}

inline ChromaticAdapter& ChromaticAdapter::operator=(ChromaticAdapter&& other) noexcept
{
    if (this != &other)
    {
        if (m_backendHandle != nullptr)
        {
            (void)PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_Destruct(m_backendHandle);
        }

        m_backendHandle = other.m_backendHandle;
        other.m_backendHandle = nullptr;
    }

    return *this;
}

inline ChromaticAdapter::ColorSpace ChromaticAdapter::TargetColorSpace() const
{
    ColorSpace colorSpace{};

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_GetTargetColorSpace(
            m_backendHandle, reinterpret_cast<PEAK_IPL_CHROMATIC_ADAPTER_COLOR_SPACE*>(&colorSpace));
    });

    return colorSpace;
}

inline void ChromaticAdapter::SetTargetColorSpace(ColorSpace colorSpace)
{
    ExecuteAndMapReturnCodes([&] {
    return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_SetTargetColorSpace(
        m_backendHandle, static_cast<PEAK_IPL_CHROMATIC_ADAPTER_COLOR_SPACE>(colorSpace));
});
}

inline ChromaticAdapter::Algorithm ChromaticAdapter::AdaptionAlgorithm() const
{
    Algorithm algorithm{};

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_GetAdaptionAlgorithm(
            m_backendHandle, reinterpret_cast<PEAK_IPL_CHROMATIC_ADAPTER_ALGORITHM*>(&algorithm));
    });

    return algorithm;
}

inline void ChromaticAdapter::SetAdaptionAlgorithm(Algorithm algorithm)
{
    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_SetAdaptionAlgorithm(
            m_backendHandle, static_cast<PEAK_IPL_CHROMATIC_ADAPTER_ALGORITHM>(algorithm));
    });
}

inline ColorCorrectionFactors ChromaticAdapter::CalculateColorCorrectionMatrix(uint32_t colorTemperature,
    const ColorCorrectionFactors& correctionFactors) const
{
    ColorCorrectionFactors correctionFactorsCalculated{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_CalculateColorCorrectionMatrix(
            m_backendHandle, colorTemperature, reinterpret_cast<const float*>(&correctionFactors),
            reinterpret_cast<float*>(&correctionFactorsCalculated));
    });

    return correctionFactorsCalculated;
}

inline Range<uint32_t> ChromaticAdapter::TemperatureRange() const
{
    uint32_t minTemp{};
    uint32_t maxTemp{};
    uint32_t incTemp{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ChromaticAdapter_GetTemperatureRange(m_backendHandle, &minTemp, &maxTemp, &incTemp);
    });

    return Range<uint32_t>{minTemp, maxTemp, incTemp};
}

} /* namespace ipl */
} /* namespace peak */
