/*!
 * \file    peak_icv_downsampling_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_common/types/peak_common_any.hpp>
#include <peak_common/types/peak_common_interval.hpp>
#include <peak_icv/exceptions/peak_icv_exception.hpp>
#include <peak_icv/pipeline/detail/peak_icv_pipeline_utils.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_downsampling.h>

namespace peak
{
namespace pipeline
{

namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Mode parameter for the downsampling algorithm.
 *
 * The enum holding the possible modes.
 *
 * \since ids_peak_icv 1.0
 */
enum class DownsamplingMode
{
    //! The averaged pixel values of neighboring rows and/or columns are computed during binning.
    BinningAverage = 0,

    //! The pixel values of neighboring rows and/or columns are summed during binning.
    BinningSum = 1,

    //! The additional pixel values of neighboring rows and/or columns are skipped during decimation.
    Decimation = 2,
};

PEAK_COMMON_NO_DISCARD inline std::string ToString(DownsamplingMode mode)
{
    if (mode == DownsamplingMode::BinningAverage)
    {
        return "BinningAverage";
    }
    if (mode == DownsamplingMode::BinningSum)
    {
        return "BinningSum";
    }
    if (mode == DownsamplingMode::Decimation)
    {
        return "Decimation";
    }
    const auto modeStr = std::to_string(static_cast<int>(mode));
    throw peak::icv::NotSupportedException("The given downsampling mode " + modeStr + " is unknown!");
}

PEAK_COMMON_NO_DISCARD inline DownsamplingMode ToMode(const std::string& mode)
{
    if (mode == "BinningAverage")
    {
        return DownsamplingMode::BinningAverage;
    }
    if (mode == "BinningSum")
    {
        return DownsamplingMode::BinningSum;
    }
    if (mode == "Decimation")
    {
        return DownsamplingMode::Decimation;
    }
    throw peak::icv::NotSupportedException("The given downsampling mode " + mode + " is unknown!");
}

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_modules
 *
 * \brief Downsampling is used to decrease the image size.
 *
 * This module provides comprehensive functionality for image downsampling,
 * which is the process of reducing image resolution and dimensions.
 * It supports multiple algorithms optimized for various use cases.
 *
 * There are two basic techniques for downsampling:
 *
 * - _Binning_
 *   This method reduces resolution by summarizing or averaging groups of pixels
 *   in the horizontal (x) and/or vertical (y) directions.
 *   It helps preserve image quality by minimizing aliasing artifacts.
 *
 * - _Decimation_
 *   This method reduces resolution by selecting (i.e., skipping) pixels at regular intervals
 *   along columns (x), rows (y) or both.
 *   It is computationally efficient but may introduce aliasing.
 *
 * The reduction factors are specified separately for the x (columns) and y (rows) directions.
 *
 * \since ids_peak_icv 1.0
 */
class DownsamplingModule : public modules::IModule
{
public:
    /*!
     * \brief Creates a DownsamplingModule with \ref defaults_feature_binning "default values".
     *
     * \since ids_peak_icv 1.0
     */
    explicit DownsamplingModule();

    /*!
     * \brief Creates a DownsamplingModule with factors x = 1, y = 1
     *        and the given downsampling mode and name.
     *
     * \since ids_peak_icv 1.0
     */
    explicit DownsamplingModule(DownsamplingMode defaultMode, std::string customName);

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~DownsamplingModule() override;

    /*!
     * \brief Copy constructor for class DownsamplingModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    DownsamplingModule(const DownsamplingModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    DownsamplingModule(DownsamplingModule&& other) noexcept;

    /*!
     * \brief Copy assignment for class DownsamplingModule is deleted.
     *
     * \note If you need to copy a module, you can create a new one and copy the parameters via Serialize() and Deserialize().
     *
     * \since ids_peak_icv 1.0
     */
    DownsamplingModule& operator=(const DownsamplingModule& other) = delete;

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    DownsamplingModule& operator=(DownsamplingModule&& other) noexcept;

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
     * \brief Serializes the object's internal state into the provided archive.
     *
     * This function populates the given \p archive with all parameters required to fully represent the current state of the object.
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
     * \throws CorruptedException If the archive is malformed, misses keys or the values are invalid
     * \throws NotSupportedException If the 'Version' entry indicates an unsupported version.
     *
     * \note This function requires that the archive contains all expected fields as produced by a corresponding Serialize() call.
     *
     * \since ids_peak_icv 1.0
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override;

    /*!
     * \brief Applies the downsampling factors and mode to the input image and returns a downsampled copy based on current settings.
     *
     * \supportedPixelformats{Downsampling}
     *
     * \note Processes the entire image, ignoring any specified image region.
     * The alpha channel of the input image (if present) is also ignored.
     * This is because the alpha channel can have different interpretations
     * — such as transparency, segmentation labels, or masks —
     * each of which would require different handling during binning.
     * Consequently, the alpha channel of the output image is always set to the maximum possible pixel value.
     *
     * \param input The input image to be processed.
     *
     * \returns A new image object that is the transformed result of the input.
     *
     * \throws NotSupportedException  If \p image has any other than the supported pixel formats.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& input) const;

    /*!
     * \brief Applies the downsampling factors and mode to the input image and returns a downsampled copy based on current settings.
     *
     * \supportedPixelformats{Downsampling}
     *
     * \note Processes the entire image, ignoring any specified image region.
     * The alpha channel of the input image (if present) is also ignored.
     * This is because the alpha channel can have different interpretations
     * — such as transparency, segmentation labels, or masks —
     * each of which would require different handling during binning.
     * Consequently, the alpha channel of the output image is always set to the maximum possible pixel value.
     *
     * \param input The input image to be processed.
     *
     * \returns A new image object that is the transformed result of the input.
     *
     * \throws peak::common::InvalidCastException If the input cast to \ref peak::icv::Image failed.
     * \throws NotSupportedException  If \p image has any other than the supported pixel formats.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;

    /*!
     * \brief Returns the type of the module for serialization purposes or the custom type, if defined.
     *
     * \returns A string representing the module's type.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD const char* GetType() const override;

    /*!
     * \brief Sets the custom type of the module for serialization purposes.
     *
     * \param type A string representing the module's type.
     *
     * \since ids_peak_icv 1.0
     */
    void SetCustomType(const std::string& type);

    /*!
     * \brief Resets all settings to their default values defined at initialization,
     * i.e. x = 1, y = 1, and the initial downsampling mode.
     *
     * \note The enabled state and CustomType do not change when calling this function.
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \brief Sets the number of columns to downsample.
     *
     * \param x The number of columns to downsample.
     *
     * \since ids_peak_icv 1.0
     */
    void SetX(uint32_t x);

    /*!
     * \brief Sets the number of rows to downsample.
     *
     * \param y The number of rows to downsample.
     *
     * \since ids_peak_icv 1.0
     */
    void SetY(uint32_t y);

    /*!
     * \brief Returns the current number of columns used for downsampling.
     *
     * \returns The current number of columns to downsample.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetX() const;

    /*!
     * \brief Returns the current number of rows used for downsampling.
     *
     * \returns The current number of rows to downsample.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetY() const;

    /*!
     * \brief Returns the valid range for downsampling factors x and y.
     *
     * \returns The valid range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::IntervalU GetRange() const;

    /*!
     * \brief Sets the \ref DownsamplingMode.
     *
     * \param mode The \ref DownsamplingMode to set.
     *
     * \since ids_peak_icv 1.0
     */
    void SetMode(const DownsamplingMode& mode);

    /*!
     * \brief Returns the current \ref DownsamplingMode.
     *
     * \returns The current \ref DownsamplingMode.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD DownsamplingMode GetMode() const;

private:
    static constexpr auto modeKey{ "Mode" };
    static constexpr auto xKey = "X";
    static constexpr auto yKey = "Y";
    static constexpr auto defaultModeKey = "DefaultMode";

    static constexpr int moduleVersion = 1;

    DownsamplingMode m_defaultMode{ DownsamplingMode::BinningAverage };

    peak_icv_downsampling_handle m_handle{};
    bool m_enabled{ true };

    std::string m_customType;
};

inline DownsamplingModule::DownsamplingModule()
    : DownsamplingModule(DownsamplingMode::BinningAverage, {})
{}

inline DownsamplingModule::DownsamplingModule(DownsamplingMode defaultMode, std::string customName)
    : m_defaultMode{ defaultMode }
    , m_customType{ std::move(customName) }
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_Create(
            &m_handle, peak_icv_downsampling_factor{ 1, 1 }, static_cast<peak_icv_downsampling_mode>(m_defaultMode));
    });
}

inline DownsamplingModule::~DownsamplingModule()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_Destroy(m_handle);
    }
}

inline DownsamplingModule::DownsamplingModule(DownsamplingModule&& other) noexcept
    : m_defaultMode{ std::exchange(other.m_defaultMode, DownsamplingMode::BinningAverage) }
    , m_handle{ std::exchange(other.m_handle, nullptr) }
    , m_enabled{ std::exchange(other.m_enabled, false) }
{}

inline DownsamplingModule& DownsamplingModule::operator=(DownsamplingModule&& other) noexcept
{
    if (this != &other)
    {
        if (m_handle != nullptr)
        {
            peak::icv::detail::ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_Destroy(m_handle);
            });
        }

        m_handle = std::exchange(other.m_handle, nullptr);
        m_enabled = std::exchange(other.m_enabled, false);
        m_defaultMode = std::exchange(other.m_defaultMode, DownsamplingMode::BinningAverage);
    }

    return *this;
}

inline void DownsamplingModule::SetEnabled(const bool enabled)
{
    m_enabled = enabled;
}

inline bool DownsamplingModule::IsEnabled() const
{
    return m_enabled;
}

inline void DownsamplingModule::Serialize(peak::common::serialization::IArchive& archive) const
{
    archive.SetInt("Version", moduleVersion);
    archive.SetBool("Enabled", IsEnabled());

    archive.SetInt(xKey, GetX());
    archive.SetInt(yKey, GetY());

    const auto& mode = GetMode();
    archive.SetString(modeKey, ToString(mode));

    archive.SetString(defaultModeKey, ToString(m_defaultMode));
}

inline void DownsamplingModule::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto version = archive.GetInt("Version");
    detail::ValidateVersion(version, GetType());

    SetEnabled(archive.GetBool("Enabled"));

    SetX(static_cast<uint32_t>(archive.GetInt(xKey)));
    SetY(static_cast<uint32_t>(archive.GetInt(yKey)));

    SetMode(ToMode(archive.GetString(modeKey)));
    m_defaultMode = ToMode(archive.GetString(defaultModeKey));
}

inline peak::icv::Image DownsamplingModule::Process(const peak::icv::Image& input) const
{
    return Process(peak::common::Any(input)).AnyCast<peak::icv::Image>();
}

inline peak::common::Any DownsamplingModule::Process(const peak::common::Any& input) const
{
    auto needsProcessing = [&] {
        bool value{};
        peak::icv::detail::ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_NeedsProcessing(m_handle, &value);
        });
        return value;
    };

    if (!IsEnabled() || !needsProcessing())
    {
        return input;
    }

    const auto& inputImage = input.AnyCast<peak::icv::Image>();
    auto* const inputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(inputImage);

    peak_common_size outputImageSize{};
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_GetOutputImageSize(m_handle, inputImageHandle, &outputImageSize);
    });

    peak::icv::Image outputImage = peak::common::detail::BackendAccessor<peak::icv::Image>::CreateInstance(
        inputImage.GetPixelFormat(), peak::common::Size{ outputImageSize.width, outputImageSize.height }, false);
    auto* const outputImageHandle = peak::common::detail::BackendAccessor<peak::icv::Image>::BackendHandle(outputImage);

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_Process(m_handle, inputImageHandle, outputImageHandle);
    });

    return peak::common::Any{ outputImage };
}

inline const char* DownsamplingModule::GetType() const
{
    if (!m_customType.empty())
    {
        return m_customType.c_str();
    }
    return "Downsampling";
}

inline void DownsamplingModule::ResetToDefault()
{
    SetX(1);
    SetY(1);
    SetMode(m_defaultMode);
}

inline void DownsamplingModule::SetX(uint32_t x)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_SetFactor(m_handle, peak_icv_downsampling_factor{ x, GetY() });
    });
}

inline void DownsamplingModule::SetY(uint32_t y)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_SetFactor(m_handle, peak_icv_downsampling_factor{ GetX(), y });
    });
}

inline uint32_t DownsamplingModule::GetX() const
{
    peak_icv_downsampling_factor factor{};

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_GetFactor(m_handle, &factor);
    });

    return factor.x;
}

inline uint32_t DownsamplingModule::GetY() const
{
    peak_icv_downsampling_factor factor{};

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_GetFactor(m_handle, &factor);
    });

    return factor.y;
}

inline peak::common::IntervalU DownsamplingModule::GetRange() const
{
    peak_common_interval_u cRange{};

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_GetRange(m_handle, &cRange);
    });

    return { cRange.minimum, cRange.maximum };
}

inline void DownsamplingModule::SetMode(const DownsamplingMode& mode)
{
    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_SetMode(
            m_handle, static_cast<peak_icv_downsampling_mode>(mode));
    });
}

inline DownsamplingMode DownsamplingModule::GetMode() const
{
    peak_icv_downsampling_mode mode{};

    peak::icv::detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Preprocessing_Downsampling_GetMode(m_handle, &mode);
    });

    return static_cast<DownsamplingMode>(mode);
}

} // namespace detail
} // namespace pipeline 
} // namespace peak
