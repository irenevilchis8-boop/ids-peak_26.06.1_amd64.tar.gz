/*!
 * \file    peak_icv_hotpixel_detection.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-28
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/filters/peak_icv_median_filter.h>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_hotpixel_correction.h>
#include <utility>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_algorithms
 * \brief Detects hot pixels in images taken by a camera by identifying anomalies in the pixels intensities.
 *
 * The HotpixelDetection class performs analysis of images to identify hot pixels —
 * pixels that consistently report abnormal intensity values. The detection sensitivity
 * and gain factor can be configured to tune the detection accuracy.
 *
 * \note This class only performs hot pixel **detection**, not correction.
 *
 * \since ids_peak_icv 1.0
 */
class HotpixelDetection
{
public:
    /*!
     * \brief Constructs a new HotpixelDetection instance.
     *
     * Initializes internal resources for hot pixel detection.
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelDetection();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~HotpixelDetection();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelDetection(const HotpixelDetection& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelDetection(HotpixelDetection&& other) noexcept;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelDetection& operator=(const HotpixelDetection& other);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelDetection& operator=(HotpixelDetection&& other) noexcept;

    /*!
     * \brief Detects hot pixels in the provided image.
     *
     * Analyzes the input image to identify hot pixels using the configured
     * sensitivity and gain factor. The result is a list of points corresponding
     * to detected hot pixels.
     *
     * \param image The input image to analyze.
     * \return A vector of points representing detected hot pixels.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<peak::common::Point> Detect(const Image& image) const;

    /*!
     * \brief Sets the sensitivity used during hot pixel detection.
     *
     * \param sensitivity A value within the valid sensitivity range.
     *
     * \throws OutOfRangeException If the value is outside the valid range.
     *
     * \since ids_peak_icv 1.0
     */
    void SetSensitivity(uint32_t sensitivity);

    /*!
     * \brief Returns the currently configured detection sensitivity.
     *
     * \return Current sensitivity value.
     *
     * \since ids_peak_icv 1.0
     */
    uint32_t GetSensitivity() const;

    /*!
     * \brief Retrieves the valid range of sensitivity values.
     *
     * \return An IntervalU representing the allowed sensitivity range.
     *
     * \since ids_peak_icv 1.0
     */
    peak::common::IntervalU GetSensitivityRange();

    /*!
     * \brief Sets the gain factor used during detection.
     *
     * Higher gain values simulate conditions with more image noise, potentially
     * improving detection accuracy under specific scenarios.
     *
     * \param gainFactor The gain factor to apply (e.g., 1.0 for normal, >1.0 for higher gain).
     *
     * \since ids_peak_icv 1.0
     */
    void SetGainFactor(float gainFactor);

    /*!
     * \brief Gets the current gain factor.
     *
     * \return The configured gain factor value.
     *
     * \since ids_peak_icv 1.0
     */
    float GetGainFactor() const;

private:
    peak_icv_hotpixel_correction_handle m_handle{};
    uint32_t m_sensitivity = 3;
    float m_gainFactor = 1.0F;
};

inline std::vector<peak::common::Point> HotpixelDetection::Detect(const Image& image) const
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Detect(
            m_handle, peak::common::detail::BackendAccessor<Image>::BackendHandle(image), m_sensitivity, m_gainFactor);
    });

    size_t hotpixelCount{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount(m_handle, &hotpixelCount);
    });

    if (hotpixelCount == 0)
    {
        return {};
    }

    std::vector<peak_common_point> hotpixelsC(hotpixelCount);
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_GetList(m_handle, hotpixelsC.data(), hotpixelCount);
    });

    std::vector<peak::common::Point> hotpixelsCpp;
    hotpixelsCpp.reserve(hotpixelCount);
    std::transform(hotpixelsC.begin(), hotpixelsC.end(), std::back_inserter(hotpixelsCpp), [](peak_common_point pointC) {
        return peak::common::detail::BackendAccessor<peak::common::Point>::CreateInstance(pointC);
    });

    return hotpixelsCpp;
}

inline HotpixelDetection::HotpixelDetection()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Create(&m_handle);
    });
}

inline HotpixelDetection::HotpixelDetection(const HotpixelDetection& other)
{
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount(other.m_handle);
    });
    m_handle = other.m_handle;
    m_gainFactor = other.m_gainFactor;
    m_sensitivity = other.m_sensitivity;
}

inline HotpixelDetection::HotpixelDetection(HotpixelDetection&& other) noexcept
{
    m_handle = other.m_handle;
    other.m_handle = nullptr;

    m_sensitivity = std::move(other.m_sensitivity);
    m_gainFactor = std::move(other.m_gainFactor);
}

inline HotpixelDetection& HotpixelDetection::operator=(const HotpixelDetection& other)
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Destroy(m_handle);
            });
        }

        detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_IncreaseUseCount(other.m_handle);
        });
        m_handle = other.m_handle;
        m_gainFactor = other.m_gainFactor;
        m_sensitivity = other.m_sensitivity;
    }

    return *this;
}

inline HotpixelDetection& HotpixelDetection::operator=(HotpixelDetection&& other) noexcept
{
    if (m_handle != other.m_handle)
    {
        if (m_handle != nullptr)
        {
            detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Destroy(m_handle);
            });
        }

        m_handle = other.m_handle;
        other.m_handle = nullptr;
        m_sensitivity = std::move(other.m_sensitivity);
        m_gainFactor = std::move(other.m_gainFactor);
    }

    return *this;
}

inline HotpixelDetection::~HotpixelDetection()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Destroy(m_handle);
    }
}

inline void HotpixelDetection::SetSensitivity(uint32_t sensitivity)
{
    const auto range = GetSensitivityRange();

    if (sensitivity < range.GetMinimum() || sensitivity > range.GetMaximum())
    {
        throw OutOfRangeException("The given sensitivity is out of range. Check GetSensitivityRange() function for the valid range.");
    }

    m_sensitivity = sensitivity;
}

inline uint32_t HotpixelDetection::GetSensitivity() const
{
    return m_sensitivity;
}

inline peak::common::IntervalU HotpixelDetection::GetSensitivityRange()
{
    peak_common_interval_u sensitivityRange;
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange(m_handle, &sensitivityRange);
    });

    return peak::common::detail::BackendAccessor<peak::common::IntervalU>::CreateInstance(sensitivityRange);
}

inline void HotpixelDetection::SetGainFactor(float gainFactor)
{
    m_gainFactor = gainFactor;
}

inline float HotpixelDetection::GetGainFactor() const
{
    return m_gainFactor;
}

} /* namespace icv */
} /* namespace peak */
