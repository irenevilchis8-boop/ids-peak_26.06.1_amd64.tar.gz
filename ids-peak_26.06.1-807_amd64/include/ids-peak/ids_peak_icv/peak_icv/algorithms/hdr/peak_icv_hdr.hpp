/*!
 * \file    peak_icv_hdr.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-01-20
 * \since   1.2
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/algorithms/hdr/peak_icv_response_curve.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/hdr/peak_icv_hdr.h>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_hdr
 *
 * \brief Specifies the HDR reconstruction algorithm.
 *
 * Defines the algorithm used to reconstruct a High Dynamic Range (HDR) image
 * from multiple input images captured with different exposure settings.
 *
 * \note
 *     Currently, only the Debevec HDR reconstruction algorithm is supported.
 *     Additional algorithms may be introduced in future releases.
 *
 * \since ids_peak_icv 1.2
 */
enum class HDRAlgorithm
{
    /*!
     * \brief Debevec HDR reconstruction algorithm.
     *
     * Uses the method proposed by Debevec and Malik to estimate the camera
     * response curve (CRC) and combine multiple exposures into an HDR image.
     *
     * \since ids_peak_icv 1.2
     */
    Debevec = 0,
};

/*!
 * \ingroup ids_peak_icv_cpp_hdr
 *
 * \brief Performs High Dynamic Range (HDR) image reconstruction.
 *
 * This class provides functionality to generate a High Dynamic Range (HDR)
 * image from a set of input images captured with different exposure settings.
 * The input images are expected to depict the same scene while varying exactly
 * one parameter: either the exposure time OR the gain.
 *
 * Internally, the HDR reconstruction is performed using the Debevec algorithm.
 * A key part of this process is determining the *Camera Response Curve* (CRC),
 * which maps digital pixel values to relative radiance.
 *
 * ### Typical usage
 * - Create an `HDR` object
 * - Optionally calculating the response curve using \ref EstimateResponseCurve
 * - Generate the HDR image using \ref Process
 *
 * \note
 *     All input images must have
 *     the **same resolution**,
 *     the **same pixel format**
 *     and being captured from an **identical viewpoint of the same scene**
 *     without any change in camera position or scene content.
 *     Any mismatch may lead to invalid HDR reconstruction results.
 *
 * ### Limitations
 * - All input images must be compatible (same resolution, pixel format, and scene)
 * - At least tow input images must be provided
 * - Only the Debevec HDR algorithm is currently supported
 *
 * \since ids_peak_icv 1.2
 */
class HDR : detail::IBackendAccessible<HDR>
{
public:
    /*!
     * \brief Constructs an HDR processing object.
     *
     * Creates and initializes an HDR object using the default HDR reconstruction
     * algorithm (Debevec).
     *
     * \since ids_peak_icv 1.2
     */
    explicit HDR();

    ~HDR() override;

    /*!
     * \brief Returns the HDR algorithm used by this object.
     *
     * The algorithm is defined at construction time and determines how
     * the input images are combined during HDR reconstruction.
     *
     * \return The HDR algorithm identifier.
     *
     * \since ids_peak_icv 1.2
     */
    PEAK_COMMON_NO_DISCARD HDRAlgorithm GetAlgorithm() const;

    /*!
     * \brief Estimates the *Camera Response Curve* (CRC) from a set of input images.
     *
     * This method calculates the response characteristics of the camera sensor.
     * The CRC defines the relationship between
     * scene radiance and the measured pixel values.
     *
     * All input images must meet the following conditions:
     *      - Represent the same scene.
     *      - Be compatible in size and pixel format.
     *      - Contain valid metadata for either exposure time or gain,
     *        and the values for the chosen parameter must vary across the given images
     *        (e.g., \ref peak::common::MetadataKey::DeviceExposureTime or
     *        \ref peak::common::MetadataKey::DeviceGain).
     *
     * Performing this estimation step explicitly can significantly reduce the processing
     * time of subsequent calls to `Process()`, as the curve does not need to be
     * re-calculated.
     *
     * If this method is not called, the response curve is estimated automatically
     * during the first call to `Process()`.
     *
     * \supportedPixelformats{HDR}
     *
     * \param[in] images
     *      Images of the same scene with different exposure time or gain metadata.
     *      Must not be empty.
     *
     * \since ids_peak_icv 1.3
     */
    void EstimateResponseCurve(const std::vector<Image>& images) const;

    /*!
     * \brief Generates an HDR image from the specified input images.
     *
     * Processes the provided images and combines them into a single HDR image.
     *
     * If a pixel is under- or overexposed across all input images
     * this pixel is clamped to the HDR image's global minimum or maximum values, respectively.
     * All clamped pixels are excluded from the image region.
     *
     * All input images must meet the following conditions:
     *      - Represent the same scene.
     *      - Be compatible in size and pixel format.
     *      - Contain valid metadata for either exposure time or gain,
     *        and the values for the chosen parameter must vary across the given images
     *        (e.g., \ref peak::common::MetadataKey::DeviceExposureTime or
     *        \ref peak::common::MetadataKey::DeviceGain).
     *
     * If the camera response curve has not been explicitly estimated
     * using \ref EstimateResponseCurve,
     * an internal estimation step is performed automatically
     * when it is first called.
     * This may increase the overall processing time for the first call.
     *
     * \supportedPixelformats{HDR}
     *
     * \param[in] images
     *      Images of the same scene with different exposure time or gain metadata.
     *      Must not be empty.
     *
     * \return The resulting HDR image with pixel format Mono32f resp. RGB32f.
     *
     * \since ids_peak_icv 1.2
     */
    PEAK_COMMON_NO_DISCARD Image Process(const std::vector<Image>& images) const;

    /*!
     * \throws NotPossibleException
     *     No response curve is currently set.
     *     Use HDR::SetResponseCurve()
     *     or HDR::EstimateResponseCurve()
     *     to set a response curve first.
     *
     * \since ids_peak_icv 1.4
     */
    PEAK_COMMON_NO_DISCARD ResponseCurve GetResponseCurve() const;

    /*!
     * \since ids_peak_icv 1.4
     */
    void SetResponseCurve(const ResponseCurve& responseCurve);

private:
    friend peak::common::detail::BackendAccessor<HDR>;

    PEAK_COMMON_NO_DISCARD detail::handle_of_t<HDR> GetHandle() const override;

    peak_icv_hdr_handle m_handle{};
};

inline HDR::HDR()
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_Create(&m_handle);
    });
}

inline HDR::~HDR()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_Destroy(m_handle);
    }
}

inline HDRAlgorithm HDR::GetAlgorithm() const
{
    peak_icv_hdr_algorithm algorithm;

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_GetAlgorithm(m_handle, &algorithm);
    });

    return static_cast<HDRAlgorithm>(algorithm);
}

inline detail::handle_of_t<HDR> HDR::GetHandle() const
{
    return m_handle;
}

inline void HDR::EstimateResponseCurve(const std::vector<Image>& images) const
{
    if (images.size() == 0)
    {
        throw NotPossibleException("Number of input images has to be greater than 0.");
    }

    std::vector<peak_icv_image_handle> imageHandles;
    imageHandles.reserve(images.size());
    std::transform(images.begin(), images.end(), std::back_inserter(imageHandles), [](const auto& image) {
        return peak::common::detail::BackendAccessor<Image>::BackendHandle(image);
    });

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_EstimateResponseCurve(m_handle, imageHandles.data(), imageHandles.size());
    });
}

inline Image HDR::Process(const std::vector<Image>& images) const
{
    if (images.empty())
    {
        throw NotPossibleException("Input image vector cannot be empty.");
    }

    std::vector<peak_icv_image_handle> imageHandles;
    imageHandles.reserve(images.size());
    std::transform(images.begin(), images.end(), std::back_inserter(imageHandles), [](const peak::icv::Image& image) {
        return peak::common::detail::BackendAccessor<Image>::BackendHandle(image);
    });

    peak_common_pixel_format outputPixelFormat;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_Process_GetOutputPixelFormat(
            m_handle, peak::common::detail::CppPixelFormatToCPixelFormat(images.at(0).GetPixelFormat()), &outputPixelFormat);
    });

    Image outputImage = peak::common::detail::BackendAccessor<Image>::CreateInstance(
        peak::common::detail::CPixelFormatToCppPixelFormat(outputPixelFormat), images.at(0).GetSize(), false);
    auto* const outputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(outputImage);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_Process(m_handle, imageHandles.data(), imageHandles.size(), outputImageHandle);
    });

    return outputImage;
}

inline ResponseCurve HDR::GetResponseCurve() const
{
    auto responseCurve = peak::common::detail::BackendAccessor<ResponseCurve>::CreateInstance();
    auto responseCurveHandle = peak::common::detail::BackendAccessor<ResponseCurve>::BackendHandleAddress(responseCurve);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_GetResponseCurve(m_handle, responseCurveHandle);
    });

    return responseCurve;
}

inline void HDR::SetResponseCurve(const ResponseCurve& responseCurve)
{
    const auto responseCurveHandle = peak::common::detail::BackendAccessor<ResponseCurve>::BackendHandle(responseCurve);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_HDR_SetResponseCurve(m_handle, responseCurveHandle);
    });
}

} // namespace icv 
} // namespace peak
