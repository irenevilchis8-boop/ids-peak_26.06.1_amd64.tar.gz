/*!
 * \file    peak_ipl_color_corrector.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2019-05-01
 * \since   1.0
 *
 * Copyright (c) 2019 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_ipl/backend/peak_ipl_backend.h>
#include <peak_ipl/exception/peak_ipl_exception.hpp>
#include <peak_ipl/types/peak_ipl_image.hpp>
#include <peak_ipl/types/peak_ipl_pixel_format.hpp>
#include <peak_ipl/types/peak_ipl_simple_types.hpp>
#include <peak_ipl/types/peak_ipl_color_correction_factors.hpp>
#include <peak_ipl/algorithm/peak_ipl_chromatic_adaption.hpp>

#include <type_traits>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

/*!
 * \namespace peak::ipl
 * \brief The "peak::ipl" namespace contains the whole image processing library.
 */

namespace peak
{
namespace ipl
{

class Image;

/*!
 * \ingroup ids_peak_ipl_algorithm
 * \brief Applies a 3x3 color correction matrix to the data.
 */
class ColorCorrector final
{
public:
    /*! \brief Constructor for a new ColorCorrector instance
     *
     * Creates a new ColorCorrector instance.
     *
     * \since 1.0
     */
    ColorCorrector();
    
    /*! \brief Destructor for the ColorCorrector instance
     *
     * Destroys a ColorCorrector instance.
     *
     * \since 1.0
     */
    ~ColorCorrector();
    
    /*! \brief Copy Constructor for a new ColorCorrector instance
     *
     * Creates a new ColorCorrector instance.
     *
     * \note This only creates a shallow copy. See \ref shallowCopy for a detailed explanation.
     * 
     * \param[in] other The other instance to acquire a reference for.
     *
     * \since 1.0 Deleted.
     * \since 1.8 Implemented as shallow copy.
     */
    ColorCorrector(const ColorCorrector& other);
    
    /*! \brief Copy assigment for ColorCorrector instance
     *
     * Acquires a reference from \p other to this instance. If this instance already has a reference, it will be destroyed.
     *
     * \note See \ref shallowCopy for a detailed explanation.
     *
     * \param[in] other The other instance to acquire a reference for.
     *
     * \since 1.0 Deleted.
     * \since 1.8 Implemented as shallow copy.
     */
    ColorCorrector& operator=(const ColorCorrector& other);
    
    /*! \brief Move constructor for ColorCorrector instance
     *
     * Moves the instance from \p other to this.
     * Afterward, \p other is invalid.
     * 
     * \param[in] other The other instance to move.
     *
     * \since 1.0
     */
    ColorCorrector(ColorCorrector&& other) noexcept;
    
    /*! \brief Move assignment for ColorCorrector instance
     *
     * Moves the instance from \p other to this.
     * Afterward, \p other is invalid.
     * 
     * \param[in] other The other instance to move.
     *
     * \since 1.3.3
     */
    ColorCorrector& operator=(ColorCorrector&& other) noexcept;

    /*!
     * \brief Sets the values of the color correction matrix.
     *
     * The matrix is row-wise sorted:
     * |    |    |    |
     * | -- | -- | -- |
     * | RR | GR | BR |
     * | RG | GG | BG |
     * | RB | GB | BB |
     *
     * \param[in] colorCorrectorFactors The factors of the color correction matrix.
     *
     * \since 1.0
     */
    void SetColorCorrectionFactors(ColorCorrectionFactors colorCorrectorFactors);

    /*!
     * \brief Returns the factors of the color correction matrix.
     *
     * \returns colorCorrectorFactors The factors of the color correction matrix
     *
     * \since 1.0
     */
    PEAK_IPL_NO_DISCARD peak::ipl::ColorCorrectionFactors ColorCorrectionFactors();

    /*!
     * \brief Returns the factors of the color correction matrix.
     *
     * \returns colorCorrectorFactors The factors of the color correction matrix
     *
     * \since 1.3.2
     */
    PEAK_IPL_NO_DISCARD peak::ipl::ColorCorrectionFactors ColorCorrectionFactors() const;

    /*!
     * \brief Returns the color saturation value.
     *
     * \returns The color saturation value
     *
     * \since 1.6
     */
    PEAK_IPL_NO_DISCARD float Saturation() const;

    /*!
     * \brief Returns the minimum color saturation value.
     *
     * \returns The minimum color saturation value
     *
     * \since 1.6
     */
    PEAK_IPL_NO_DISCARD float SaturationMin() const;

    /*!
     * \brief Returns the maximum color saturation value.
     *
     * \returns The maximum color saturation value
     *
     * \since 1.6
     */
    PEAK_IPL_NO_DISCARD float SaturationMax() const;

    /*!
     * \brief Sets the color saturation value.
     *
     * \param[in] saturation The color saturation value.
     *
     * \since 1.6
     */
    void SetSaturation(float saturation);

    /*!
     * \brief Applies the chromatic adaption matrix to the color corrector matrix.
     *
     * This calculates and applies the chromatic adaption matrix to the existing color corrector matrix.
     *
     * \note The existing matrix will be overwritten and cannot be restored.
     * If this is not the intended behavior, it is advised to store the factors beforehand.
     *
     * \param[in] chromaticAdapter The chromatic adapter instance.
     * \param[in] colorTemperature The color temperature to set in Kelvin.
     *
     * \since 1.16
     */
    void ApplyChromaticAdaption(const ChromaticAdapter& chromaticAdapter, uint32_t colorTemperature);

    /*!
     * \brief Returns whether the color corrector supports the given pixel format.
     *
     * \returns Flag whether the given pixel format is supported.
     *
     * \param[in] pixelFormatName The pixel format of interest.
     *
     * \since 1.0
     */
    PEAK_IPL_NO_DISCARD bool IsPixelFormatSupported(PixelFormatName pixelFormatName) const;

    /*!
     * \brief Corrects the colors of the given image by applying a 3x3 color correction matrix to the data
     *        in place that is it will change the input image.
     *
     * \param[in] image Image to process.
     *
     * \note Will not work with packed pixel formats. See \ref unpackPixelformat for the correct handling of this.
     *
     * \throws ImageFormatNotSupportedException image has unsupported pixel format (for example packed pixel format)
     *
     * \since 1.0
     * \since 1.2 Will throw ImageFormatNotSupportedException if image has packed a pixel format
     */
    void ProcessInPlace(Image& image) const;

    /*! \brief Corrects the colors of the given image by applying a 3x3 color correction matrix to the data.
     *
     * \param[in] inputImage Image to process.
     *
     * \note Will not work with packed pixel formats. See \ref unpackPixelformat for the correct handling of this.
     *
     * \returns A new created image containing the color corrected pixels
     *
     * \throws ImageFormatNotSupportedException image has unsupported pixel format (for example packed pixel format)
     *
     * \since 1.0
     * \since 1.2 Will throw ImageFormatNotSupportedException if inputImage has a packed pixel format
     */
    PEAK_IPL_NO_DISCARD Image Process(const Image& inputImage) const;

private:
    PEAK_IPL_COLOR_CORRECTOR_HANDLE m_backendHandle{};
};

inline ColorCorrector::ColorCorrector()
{
    ExecuteAndMapReturnCodes([&] { return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_Construct(&m_backendHandle); });
}

inline ColorCorrector::~ColorCorrector()
{
    if (m_backendHandle)
    {
        (void)PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_Destruct(m_backendHandle);
    }
}

inline ColorCorrector::ColorCorrector(const ColorCorrector& other)
{
    if (other.m_backendHandle)
    {
        ExecuteAndMapReturnCodes([&] { return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_Acquire(other.m_backendHandle); });
    }

    m_backendHandle = other.m_backendHandle;
}

inline ColorCorrector& ColorCorrector::operator=(const ColorCorrector& other)
{
    if (this != &other)
    {
        if (m_backendHandle)
        {
            (void)PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_Destruct(m_backendHandle);
        }

        if (other.m_backendHandle)
        {
            ExecuteAndMapReturnCodes(
                [&] { return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_Acquire(other.m_backendHandle); });
        }
    }

    m_backendHandle = other.m_backendHandle;

    return *this;
}

inline ColorCorrector::ColorCorrector(ColorCorrector&& other) noexcept
{
    *this = std::move(other);
}

inline ColorCorrector& ColorCorrector::operator=(ColorCorrector&& other) noexcept
{
    if (this != &other)
    {
        if (m_backendHandle != nullptr)
        {
            (void)PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_Destruct(m_backendHandle);
        }
        m_backendHandle = other.m_backendHandle;
        other.m_backendHandle = nullptr;
    }

    return *this;
}

inline void ColorCorrector::SetColorCorrectionFactors(peak::ipl::ColorCorrectionFactors colorCorrectorFactors)
{
    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_SetColorCorrectionFactors(
            m_backendHandle, reinterpret_cast<float*>(&colorCorrectorFactors));
    });
}

inline peak::ipl::ColorCorrectionFactors ColorCorrector::ColorCorrectionFactors()
{
    size_t colorCorrectorFactorsSize = 0;

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_GetColorCorrectionFactors(
            m_backendHandle, nullptr, &colorCorrectorFactorsSize);
    });

    peak::ipl::ColorCorrectionFactors colorCorrectorFactors;

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_GetColorCorrectionFactors(
            m_backendHandle, reinterpret_cast<float*>(&colorCorrectorFactors), &colorCorrectorFactorsSize);
    });

    return colorCorrectorFactors;
}

inline peak::ipl::ColorCorrectionFactors ColorCorrector::ColorCorrectionFactors() const
{
    size_t colorCorrectorFactorsSize = 0;

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_GetColorCorrectionFactors(
            m_backendHandle, nullptr, &colorCorrectorFactorsSize);
    });

    peak::ipl::ColorCorrectionFactors colorCorrectorFactors;

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_GetColorCorrectionFactors(
            m_backendHandle, reinterpret_cast<float*>(&colorCorrectorFactors), &colorCorrectorFactorsSize);
    });

    return colorCorrectorFactors;
}

inline float ColorCorrector::Saturation() const
{
    float saturation;

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_GetSaturation(
            m_backendHandle, reinterpret_cast<float*>(&saturation));
    });

    return saturation;
}

inline float ColorCorrector::SaturationMin() const
{
    float saturationMin;

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_GetSaturationMin(
            m_backendHandle, reinterpret_cast<float*>(&saturationMin));
    });

    return saturationMin;
}

inline float ColorCorrector::SaturationMax() const
{
    float saturationMax;

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_GetSaturationMax(
            m_backendHandle, reinterpret_cast<float*>(&saturationMax));
    });

    return saturationMax;
}

inline void ColorCorrector::SetSaturation(float saturation)
{
    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_SetSaturation(
            m_backendHandle, saturation);
    });
}

inline bool ColorCorrector::IsPixelFormatSupported(PixelFormatName pixelFormatName) const
{
    PEAK_IPL_BOOL8 isPixelFormatSupported = 0;

    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_GetIsPixelFormatSupported(m_backendHandle,
            static_cast<PEAK_IPL_PIXEL_FORMAT>(pixelFormatName),
            reinterpret_cast<PEAK_IPL_BOOL8*>(&isPixelFormatSupported));
    });

    return isPixelFormatSupported > 0;
}

inline void ColorCorrector::ProcessInPlace(Image& image) const
{
    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_ProcessInPlace(
            m_backendHandle, ImageBackendAccessor::BackendHandle(image));
    });
}

inline Image ColorCorrector::Process(const Image& inputImage) const
{
    PEAK_IPL_IMAGE_HANDLE outputImageHandle = nullptr;
    ExecuteAndMapReturnCodes([&] {
        return PEAK_IPL_C_ABI_PREFIX PEAK_IPL_ColorCorrector_Process(
            m_backendHandle, ImageBackendAccessor::BackendHandle(inputImage), &outputImageHandle);
    });

    return ImageBackendAccessor::CreateImage(outputImageHandle);
}

inline void ColorCorrector::ApplyChromaticAdaption(const ChromaticAdapter& chromaticAdapter, uint32_t colorTemperature)
{
    const auto value = ColorCorrectionFactors();
    const auto calculatedMatrix = chromaticAdapter.CalculateColorCorrectionMatrix(colorTemperature, value);
    SetColorCorrectionFactors(calculatedMatrix);
}

} /* namespace ipl */
} /* namespace peak */
