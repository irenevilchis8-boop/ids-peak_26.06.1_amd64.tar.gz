/*!
 * \file    peak_icv_hotpixel_correction_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_common/types/geometry/peak_common_point.hpp>
#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/pipeline/detail/peak_icv_pipeline_utils.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_hotpixel_correction.h>

namespace peak
{
namespace pipeline
{

namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Hotpixel correction is an image pipeline module for detecting and correcting hot pixels in camera images.
 *
 * \details \copydetails features::HotpixelCorrectionFeature
 */
class HotpixelCorrectionModule : public modules::IModule
{
public:
    /*!
     * \brief Creates a HotpixelCorrectionModule module with default settings (no correction).
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelCorrectionModule();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~HotpixelCorrectionModule() override;

    /*!
     * \brief Copy constructor for class HotpixelCorrectionModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelCorrectionModule(const HotpixelCorrectionModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelCorrectionModule(HotpixelCorrectionModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class HotpixelCorrectionModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelCorrectionModule& operator=(const HotpixelCorrectionModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    HotpixelCorrectionModule& operator=(HotpixelCorrectionModule&& other) noexcept;

    /*!
     * \brief Enables or disables the module.
     *
     * \param enabled Set to \c true to enable, or \c false to disable.
     *
     * \since ids_peak_icv 1.0
     */
    void SetEnabled(bool enabled) override;

    /*!
     * \brief Gets whether this module is currently enabled.
     *
     * \return \c true if enabled; otherwise \c false.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD bool IsEnabled() const override;

    /*!
     * \brief Returns the type of the module for serialization purposes.
     *
     * \returns A string representing the module's type.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD const char* GetType() const override;

    /*!
     * \brief Applies hot pixel correction to the input image in place and returns a reference to the modified image.
     *
     * The correction is performed based on the current configuration of the module. The operation modifies the
     * input image directly and does not create a copy.
     *
     * \note Supported pixel formats: BayerGR8, BayerGR10, BayerGR12, BayerRG8, BayerRG10, BayerRG12,
     *       BayerGB8, BayerGB10, BayerGB12, BayerBG8, BayerBG10, BayerBG12, Mono8, Mono10, Mono12.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed and corrected.
     *
     * \returns A reference to the input image after in-place hot pixel correction.
     *
     * \throws NotSupportedException  If \p image has any other than the supported pixel formats.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Applies hot pixel correction to the input image in place and returns a reference to the modified image.
     *
     * The correction is performed based on the current configuration of the module. The operation modifies the
     * input image directly and does not create a copy.
     *
     * \note Supported pixel formats: BayerGR8, BayerGR10, BayerGR12, BayerRG8, BayerRG10, BayerRG12,
     *       BayerGB8, BayerGB10, BayerGB12, BayerBG8, BayerBG10, BayerBG12, Mono8, Mono10, Mono12.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param input The input image to be processed and corrected.
     *
     * \returns A reference to the input image after in-place hot pixel correction.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     * \throws NotSupportedException  If \p image has any other than the supported pixel formats.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

    /*!
     * \brief Serializes the object's internal state into the provided archive.
     *
     * This function populates the given \p archive with all parameters required to  fully represent the current state of the object.
     * It ensures that the object can be reconstructed or transmitted accurately by saving all relevant data members
     * in a consistent and structured format.
     *
     * \param archive The target archive that will store the serialized parameters.
     *
     * \since ids_peak_icv 1.0
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override;


    /*!
     * \brief Restores the object's state from the provided archive.
     *
     * This function reads and applies all necessary parameters from the given \p archive to reconstruct the internal state of the object.
     * It ensures that the object is restored to a valid and consistent state.
     *
     * \param archive The source archive containing the serialized parameters.
     *
     * \throws CorruptedException If Archive is malformed, misses keys or the values are invalid
     * \throws NotSupportedException If the 'Version' entry indicates an unsupported version.
     *
     * \note This function requires that the archive contains all expected fields as produced by a corresponding Serialize() call.
     *
     * \since ids_peak_icv 1.0
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override;

    /*!
     * \brief Sets the list of known hot pixels.
     *
     * \param hotpixels A vector of hot pixel positions to use.
     *
     * \since ids_peak_icv 1.0
     */
    void SetList(const std::vector<peak::common::Point>& hotpixels);

    /*!
     * \brief Retrieves the current list of known hot pixels.
     *
     * \return A vector containing the positions of all configured hot pixels.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<peak::common::Point> GetList() const;

    /*!
     * \brief Returns the valid range of sensitivities.
     *
     * \return  An IntervalU containing the minimum and maximum allowed sensitivity values.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalU GetSensitivityRange() const;

    /*!
     * \brief Performs immediate hot pixel detection on the given image.
     *
     * This method analyzes the provided image and detects hot pixels based on the current
     * sensitivity setting. The results are stored internally and can be accessed using GetList().
     *
     * \note Supported pixel formats: BayerGR8, BayerGR10, BayerGR12, BayerRG8, BayerRG10, BayerRG12, BayerGB8, BayerGB10, BayerGB12,
     *                                BayerBG8, BayerBG10, BayerBG12, Mono8, Mono10, Mono12
     *
     * \param image        The input image to analyze for hot pixel detection.
     * \param sensitivity  Sensitivity for hot pixel detection. A higher sensitivity may result in detecting more hot pixels,
     *                     including possible false positives.
     *                     Valid values are within the range returned by \ref GetSensitivityRange.
     * \param gainFactor   Gain factor applied to the image (typically 1.0 or higher). Used to account for increased noise levels when detecting hot pixels.
     *                     Higher gain factors may require higher sensitivity values for effective detection.
     *
     * \throws OutOfRangeException  If \p sensitivity value is outside the valid range.
     * \throws NotSupportedException  If \p image has any other than the supported pixel formats.
     *
     * \warning Calling this function will overwrite any existing hot pixel list previously set via SetList().
     *          All previously configured hot pixel positions will be lost.
     *
     * \see SetList(), GetList(), GetSensitivityRange()
     *
     * \since ids_peak_icv 1.0
     */
    void Detect(const peak::icv::Image& image, uint32_t sensitivity = 3, float gainFactor = 1.0F);

    /*!
     * \brief Clears the hot pixel list.
     *
     * \note The enabled state does not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

private:
    static constexpr int moduleVersion = 1;

    peak_icv_hotpixel_correction_handle m_handle{};
    bool m_enabled{ true };
};

inline const char* HotpixelCorrectionModule::GetType() const
{
    return "HotpixelCorrection";
}

inline HotpixelCorrectionModule::HotpixelCorrectionModule()
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Create(&m_handle);
    });
}

inline HotpixelCorrectionModule::~HotpixelCorrectionModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Destroy(m_handle);
    }
}

inline HotpixelCorrectionModule::HotpixelCorrectionModule(HotpixelCorrectionModule&& other) noexcept
{
    m_handle = std::exchange(other.m_handle, nullptr);
    m_enabled = other.m_enabled;
}

inline HotpixelCorrectionModule& HotpixelCorrectionModule::operator=(HotpixelCorrectionModule&& other) noexcept
{
    if (this != &other)
    {
        if (m_handle != nullptr)
        {
            peak::icv::detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Destroy(m_handle);
            });
        }

        m_handle = std::exchange(other.m_handle, nullptr);
        m_enabled = other.m_enabled;
    }

    return *this;
}

inline void HotpixelCorrectionModule::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

inline bool HotpixelCorrectionModule::IsEnabled() const
{
    return m_enabled;
}

inline void HotpixelCorrectionModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    const auto hotpixels = GetList();
    std::vector<std::shared_ptr<peak::common::serialization::IArchive>> archivePoints;
    archivePoints.reserve(hotpixels.size());

    std::transform(std::cbegin(hotpixels), std::cend(hotpixels), std::back_inserter(archivePoints), [&archive](const auto& point) {
        auto archivePoint = archive.CreateArchive();
        archivePoint->SetInt("X", point.GetX());
        archivePoint->SetInt("Y", point.GetY());
        return archivePoint;
    });
    archive.SetArchiveArray("HotpixelList", archivePoints);

    archive.SetInt("Version", moduleVersion);
    archive.SetBool("Enabled", IsEnabled());
}

inline void HotpixelCorrectionModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");
    detail::ValidateVersion(version, GetType());

    SetEnabled(archive.GetBool("Enabled"));

    const auto archivePoints = archive.GetArchiveArray("HotpixelList");
    std::vector<peak::common::Point> list;
    list.reserve(archivePoints.size());
    std::transform(std::cbegin(archivePoints), std::cend(archivePoints), std::back_inserter(list), [](const auto& archive) {
        return peak::common::Point{ static_cast<int32_t>(archive->GetInt("X")), static_cast<int32_t>(archive->GetInt("Y")) };
    });

    SetList(list);
}

inline void HotpixelCorrectionModule::SetList(const std::vector<peak::common::Point>& hotpixels)
{
    if (hotpixels.empty())
    {
        peak::icv::detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_ResetList(m_handle);
        });
    }
    std::vector<peak_common_point> cPoints;
    cPoints.reserve(hotpixels.size());
    std::transform(hotpixels.cbegin(), hotpixels.cend(), std::back_inserter(cPoints), [](const peak::common::Point& cppPoint) {
        return peak_common_point{ cppPoint.GetX(), cppPoint.GetY() };
    });

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_SetList(m_handle, cPoints.data(), cPoints.size());
    });
}

inline std::vector<peak::common::Point> HotpixelCorrectionModule::GetList() const
{
    size_t count = 0;
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount(m_handle, &count);
    });
    if (count == 0)
    {
        return {};
    }

    std::vector<peak_common_point> cList(count);
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_GetList(m_handle, cList.data(), count);
    });

    std::vector<peak::common::Point> cppList{};
    cppList.reserve(count);
    std::transform(cList.begin(), cList.end(), std::back_inserter(cppList), [](const peak_common_point& cPoint) {
        return peak::common::Point{ cPoint.x, cPoint.y };
    });

    return cppList;
}

inline void HotpixelCorrectionModule::Detect(const peak::icv::Image& image, uint32_t sensitivity, float gainFactor)
{
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(image);

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_Detect(m_handle, inputImageHandle, sensitivity, gainFactor);
    });
}

inline void HotpixelCorrectionModule::ResetToDefault()
{
    SetList({});
}

inline peak::icv::Image HotpixelCorrectionModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any HotpixelCorrectionModule::Process(const peak::common::Any& input) const
{
    auto needsProcessing = [&] {
        size_t count{};
        peak::icv::detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_GetList_GetCount(m_handle, &count);
        });
        return count > 0;
    };

    if (!IsEnabled() || !needsProcessing())
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(inputImage);

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_ProcessInplace(m_handle, inputImageHandle);
    });

    return peak::common::Any{ inputImage };
}

inline peak::common::IntervalU HotpixelCorrectionModule::GetSensitivityRange() const
{
    peak_common_interval_u cRange{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_HotpixelCorrection_GetSensitivityRange(m_handle, &cRange);
    });

    return peak::common::detail::BackendAccessor<peak::common::IntervalU>::CreateInstance(cRange);
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
