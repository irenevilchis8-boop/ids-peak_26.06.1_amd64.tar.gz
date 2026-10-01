/*!
 * \file    peak_icv_drago_tone_mapping.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-05-26
 * \since   ids_peak_icv 1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/hdr/tone_mapping/peak_icv_drago_tone_mapping.h>

namespace peak
{
namespace icv
{

/*!
 * \brief Compresses the dynamic range of HDR images
 * using a logarithmic curve adapted to human visual perception.
 *
 * It is based on Adaptive Logarithmic Mapping For Displaying High Contrast Scenes Paper
 * from F. Drago, K. Myszkowski, T. Annen and N. Chiba from the year 2003.
 *
 * See paper: [External link](https://resources.mpi-inf.mpg.de/tmo/logmap/logmap.pdf)
 *
 * \ingroup ids_peak_icv_cpp_tone_mapping
 * \since ids_peak_icv 1.4
 */
class DragoToneMapping : detail::IBackendAccessible<DragoToneMapping>
{
public:
    explicit DragoToneMapping();

    ~DragoToneMapping() override;

    /*!
     * \brief Converts an HDR image into a displayable LDR image.
     *
     * \supportedPixelformats{ToneMapping}
     *
     * \return The tone-mapped image in the corresponding 8-bit format
     * (e.g., Mono32f becomes Mono8).
     *
     * \since ids_peak_icv 1.4
     */
    PEAK_COMMON_NO_DISCARD Image Process(const Image& hdrImage) const;

private:
    friend peak::common::detail::BackendAccessor<DragoToneMapping>;

    PEAK_COMMON_NO_DISCARD detail::handle_of_t<DragoToneMapping> GetHandle() const override;

    peak_icv_tone_mapping_drago_handle m_handle{};
};

inline DragoToneMapping::DragoToneMapping()
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Drago_Create(&m_handle);
    });
}

inline DragoToneMapping::~DragoToneMapping()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Drago_Destroy(m_handle);
    }
}

inline detail::handle_of_t<DragoToneMapping> DragoToneMapping::GetHandle() const
{
    return m_handle;
}

inline Image DragoToneMapping::Process(const Image& hdrImage) const
{
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(hdrImage);
    peak_common_pixel_format outputPixelFormat;

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Drago_GetOutputPixelFormat(
            m_handle, peak::common::detail::CppPixelFormatToCPixelFormat(hdrImage.GetPixelFormat()), &outputPixelFormat);
    });

    Image outputImage = peak::common::detail::BackendAccessor<Image>::CreateInstance(
        peak::common::detail::CPixelFormatToCppPixelFormat(outputPixelFormat), hdrImage.GetSize(), false);
    auto* const outputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(outputImage);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_ToneMapping_Drago_Process(m_handle, inputImageHandle, outputImageHandle);
    });

    return outputImage;
}

} // namespace icv 
} // namespace peak
