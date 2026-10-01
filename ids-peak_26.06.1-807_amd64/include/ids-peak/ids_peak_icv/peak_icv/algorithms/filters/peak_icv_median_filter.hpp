/*!
 * \file    peak_icv_median_filter.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-09-24
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/filters/peak_icv_median_filter.h>
#include <utility>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_filters
 *
 * \brief
 *     Class for applying a median filter to an image.
 *
 * The median filter is a non-linear, spatial filter
 * used to reduce impulsive noise in images.
 * It replaces each pixel
 * with the median value
 * of the pixels in its local neighborhood,
 * defined by the specified kernel size.
 * The kernel size corresponds to a square neighborhood
 * (size x size grid) around each pixel,
 * where the median is calculated.
 *
 * This process preserves edges better than linear smoothing filters
 * while effectively removing salt-and-pepper noise
 * and small image artifacts.
 * A larger kernel removes more noise
 * but also reduces image detail.
 *
 * \since ids_peak_icv 1.1
 */
class MedianFilter
{
public:
    /*!
     * \brief
     *     Constructs a MedianFilter
     *     with a default kernel size of 3 (3 × 3 neighborhood).
     *
     * \since ids_peak_icv 1.1
     */
    MedianFilter() = default;

    /*!
     * \details
     *
     * The size of the kernel
     * must be an odd number
     * greater than 1
     * and smaller than the image dimensions.
     * The kernel size defines the size of the neighborhood
     * (in a size × size grid)
     * used to calculate the median for each pixel.
     *
     * A larger kernel removes more noise
     * but also reduces image detail.
     *
     * \param[in] kernelSize
     *     Size of the kernel used for the median filter.
     *
     * \since ids_peak_icv 1.1
     */
    void SetKernelSize(size_t kernelSize);

    /*!
     * \return
     *     The current kernel size used for the median filter.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD size_t GetKernelSize() const;

    /*!
     * \brief
     *     Applies the median filter to the specified image.
     *
     * \supportedPixelformats{MedianFilter}
     *
     * \note
     *     Processes the entire image,
     *     ignoring any specified image region.
     *
     * \param[in] image
     *     The image to process.
     *
     * \return
     *     The filtered image.
     *
     * \throws NotSupportedException
     *     The pixel format is unsupported.
     * \throws NotPossibleException
     *     The kernel size must be an odd number greater than 1.
     * \throws OutOfRangeException
     *     The kernel size exceeds the image dimensions.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Image Process(const Image& image) const;

private:
    size_t m_kernelSize = 3;
};

inline void MedianFilter::SetKernelSize(size_t kernelSize)
{
    m_kernelSize = kernelSize;
}

inline size_t MedianFilter::GetKernelSize() const
{
    return m_kernelSize;
}

inline Image MedianFilter::Process(const Image& image) const
{
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(image);

    Image outputImage = peak::common::detail::BackendAccessor<Image>::CreateInstance(image.GetPixelFormat(), image.GetSize(), false);
    auto* const outputImageHandle = peak::common::detail::BackendAccessor<Image>::BackendHandle(outputImage);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Filter_Image_Median(inputImageHandle, m_kernelSize, outputImageHandle);
    });

    return outputImage;
}

} /* namespace icv */
} /* namespace peak */
