/*!
 * \file    peak_icv_linear_tone_mapping.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-05-26
 * \since   ids_peak_icv 1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/hdr/tone_mapping/peak_icv_linear_tone_mapping.h>

namespace peak
{
namespace icv
{
namespace experimental
{

/*!
 * \brief Maps a specific exposure window of an HDR image linearly to an LDR image.
 *
 * This class applies a linear tone mapping operator. It isolates a specific range
 * of exposure values and maps them linearly to the displayable Low Dynamic Range (LDR).
 * Exposure values outside of this targeted window are clipped.
 *
 * \ingroup ids_peak_icv_cpp_tone_mapping
 * \since ids_peak_icv 1.4
 */
class LinearToneMapping : detail::IBackendAccessible<LinearToneMapping>
{
public:
    explicit LinearToneMapping();

    ~LinearToneMapping() override;

    /*!
     * \brief Converts an HDR image into a displayable LDR image using linear mapping.
     *
     * The exposure window is defined by the `centerExposureValue` (in EV) and the total
     * dynamic range specified by `numberOfStops`. Pixels with an exposure falling within
     * the window `[centerExposureValue - (numberOfStops / 2), centerExposureValue + (numberOfStops / 2)]`
     * are mapped linearly to the full LDR range. Values outside this window are clipped
     * to the minimum or maximum LDR value.
     *
     * \supportedPixelformats{ToneMapping}
     *
     * \return The tone-mapped image in the corresponding 8-bit format
     * (e.g., Mono32f becomes Mono8).
     *
     * \since ids_peak_icv 1.4
     */
    PEAK_COMMON_NO_DISCARD Image Process(const Image& hdrImage, float centerExposureValue, float numberOfStops) const;
    /*!
     * \brief Computes the absolute minimum and maximum exposure values (EV) of the specified HDR image.
     *
     * \since ids_peak_icv 1.4
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalF GetExposureValueRange(const Image& hdrImage) const;

private:
    friend peak::common::detail::BackendAccessor<LinearToneMapping>;

    PEAK_COMMON_NO_DISCARD detail::handle_of_t<LinearToneMapping> GetHandle() const override;

    peak_icv_tone_mapping_linear_handle m_handle{};
};

inline LinearToneMapping::LinearToneMapping()
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Linear_Create(&m_handle);
    });
}

inline LinearToneMapping::~LinearToneMapping()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Linear_Destroy(m_handle);
    }
}

inline detail::handle_of_t<LinearToneMapping> LinearToneMapping::GetHandle() const
{
    return m_handle;
}

inline Image LinearToneMapping::Process(const Image& hdrImage, float centerExposureValue, float numberOfStops) const
{
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(hdrImage);
    peak_common_pixel_format outputPixelFormat;

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Linear_GetOutputPixelFormat(
            m_handle, peak::common::detail::CppPixelFormatToCPixelFormat(hdrImage.GetPixelFormat()), &outputPixelFormat);
    });

    Image outputImage = peak::common::detail::BackendAccessor<Image>::CreateInstance(
        peak::common::detail::CPixelFormatToCppPixelFormat(outputPixelFormat), hdrImage.GetSize(), false);
    auto* const outputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(outputImage);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Linear_Process(
            m_handle, inputImageHandle, centerExposureValue, numberOfStops, outputImageHandle);
    });

    return outputImage;
}

inline peak::common::IntervalF LinearToneMapping::GetExposureValueRange(const Image& hdrImage) const
{
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(hdrImage);
    peak_common_interval_f range{};

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Linear_GetExposureValueRange(m_handle, inputImageHandle, &range);
    });

    return peak::common::detail::BackendAccessor<peak::common::IntervalF>::CreateInstance(range);
}

} // namespace experimental
} // namespace icv 
} // namespace peak
