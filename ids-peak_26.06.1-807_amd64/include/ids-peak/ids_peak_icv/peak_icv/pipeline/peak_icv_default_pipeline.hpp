/*!
 * \file    peak_icv_default_pipeline.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/peak_common_pipeline_base.hpp>
#include <peak_common/pipeline/modules/peak_common_iautofeature_module.hpp>
#include <peak_common/types/peak_common_pixel_format.hpp>
#include <peak_icv/pipeline/detail/peak_icv_color_matrix_transformation_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_debayer_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_downsampling_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_gain_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_hotpixel_correction_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_mono_conversion_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_pixel_format_conversion_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_sharpening_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_tone_curve_correction_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_transformation_module.hpp>
#include <peak_icv/pipeline/detail/peak_icv_unpack_module.hpp>
#include <peak_icv/pipeline/features/peak_icv_binning_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_chromatic_adaption_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_color_correction_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_decimation_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_digital_black_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_gain_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_gamma_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_hotpixel_correction_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_mirror_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_rotation_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_saturation_feature.hpp>
#include <peak_icv/pipeline/features/peak_icv_sharpening_feature.hpp>
#include <peak_icv/pipeline/types/peak_icv_processing_policy.hpp>
#include <peak_icv/serialization/peak_icv_archive.hpp>
#include <peak_icv/serialization/peak_icv_deserializer.hpp>
#include <peak_icv/serialization/peak_icv_serializer.hpp>

#include <unordered_map>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace peak
{
namespace pipeline
{
/*!
 * \ingroup ids_peak_icv_cpp_pipeline
 *
 * \brief Image processing pipeline for sequential transformation of raw image frames.
 *
 * The `Pipeline` class performs a series of configurable image processing steps on
 * raw or pre-processed image data. It is designed to support a complete transformation
 * workflow, from raw sensor input to final output format, with each stage modular
 * and optionally enabled or configured.
 *
 * ### Processing Steps:
 *
 * 1.  \ref peak::pipeline::detail::UnpackModule "Unpack" *(Always Active)* –
 *     Automatically unpacks packed sensor data formats.
 *     This stage is internal and cannot be configured.
 * 2.  \ref peak::pipeline::features::HotpixelCorrectionFeature "Hot Pixel Correction" –
 *     Identifies and corrects defective pixels (hot pixels).
 * 3.  \ref peak::pipeline::features::BinningFeature "Binning" –
 *     Reduces resolution and improves signal-to-noise ratio by combining adjacent pixels.
 * 4.  \ref peak::pipeline::features::DecimationFeature "Decimation" –
 *     Downscales the image by skipping pixels in a defined pattern.
 * 5.  \ref peak::pipeline::features::MirrorFeature "Mirror" –
 *     Optionally mirrors the image left-right and/or up-down.
 * 6.  \ref peak::pipeline::features::RotationFeature "Rotation" –
 *     Rotates the image by 90, 180, or 270 degrees.
 * 7.  \ref peak::pipeline::features::GainFeature "Gain" –
 *     Applies digital master gain to control image brightness,
 *     or digital color gains to adjust white balance.
 * 8.  \ref peak::pipeline::detail::DebayerModule "Debayer" *(Configured Internally)*:
 *     Converts Bayer pattern raw data to RGB format and
 *     expands monochrome images to RGB when a color output format is requested.
 *     This behavior is automatically determined based on the input and output pixel formats.
 * 9.  \ref peak::pipeline::features::ColorCorrectionFeature "Color Correction" –
 *     Applies a color correction matrix.
 * 10. Auto Features –
 *     Analyzes the image for the following dynamic adjustments:
 *     - Auto Brightness
 *     - Auto White Balance
 *     - Auto Focus (if supported by the device)
 *
 *     To enable Auto Features, an external module must be provided via:
 *     \code
 *     auto autoFeatureModule = std::make_shared<peak::pipeline::modules::AutoFeatureModule>(remoteDeviceNodeMap);
 *     pipeline.SetAutoFeatureModule(autoFeatureModule);
 *     \endcode
 *     This module is part of the **Auto Feature Library (AFL)**.
 *
 * 11. \ref peak::pipeline::detail::MonoConversionModule "Mono Conversion" *(Configured Internally)* –
 *     Converts RGB images to monochrome when a monochrome output format is requested.
 * 12. \ref peak::pipeline::features::SharpeningFeature "Sharpening" –
 *     Enhances image detail using edge-based sharpening filters.
 * 13. \ref peak::pipeline::features::GammaFeature "Gamma" –
 *     Applies gamma correction to adjust brightness and contrast.
 * 14. \ref peak::pipeline::detail::PixelFormatConversionModule "Pixel Format Conversion" *(Configured Internally)* –
 *     Converts the processed image to the desired output pixel format.
 *
 * ### Smart Pixel Format Configuration Inference:
 *
 * The pipeline includes built-in logic to automatically configure certain internal stages
 * based on the input and output formats. For example:
 * - If a Bayer image is provided and the output format is RGB, \ref peak::pipeline::detail::DebayerModule "debayering"
 *   is automatically applied.
 * - If a monochrome image is input and the output format is RGB, the \ref peak::pipeline::detail::DebayerModule "DebayerModule"
 *   takes over the mono-to-RGB expansion.
 * - If the output format is monochrome, \ref peak::pipeline::detail::MonoConversionModule "mono conversion" is enabled.
 * - If a Bayer pixel format is set as output format, the following features or modules are not processing
 *      - \ref peak::pipeline::detail::DebayerModule "DebayerModule",
 *      - \ref peak::pipeline::detail::MonoConversionModule "MonoConversionModule",
 *      - \ref peak::pipeline::features::SharpeningFeature "SharpeningFeature", and
 *      - \ref peak::pipeline::features::GammaFeature "GammaFeature".
 * - The \ref peak::pipeline::detail::PixelFormatConversionModule "PixelFormatConversionModule" is responsible
 *   for converting to the specified output format.
 *   If necessary, the bit depth is reduced during this step.
 *
 * Use the following method to set the desired final pixel format:
 * \code
 * pipeline.SetOutputPixelFormat(PixelFormat::RGB8);
 * \endcode
 *
 * \note There might be cases where some modules, even though they are enabled,
 * do not apply their configuration, if the pixel format is not supported.
 * Further information can be found in the documentation of the individual
 * "Process" methods for each module.
 *
 * ### Configuration:
 *
 * The pipeline can be configured in two ways:
 *
 * - **Module Access**: Each configurable processing module can be accessed directly,
 *   allowing individual configuration:
 *   \code
 *   pipeline.Gain().SetMaster(1.2f);
 *   pipeline.Gamma().SetValue(2.2f);
 *   \endcode
 *
 * - **Settings File**: Load or save all configuration settings:
 *   \code
 *   pipeline.ImportSettingsFromFile("config.json");
 *   pipeline.ExportSettingsToFile("config.json");
 *   \endcode
 *
 * This modular and extensible design enables flexible integration into a variety
 * of image processing applications, from camera pipelines to offline image editing.
 *
 * \since ids_peak_icv 1.0
 */
class DefaultPipeline : public PipelineBase
{
public:
    /*!
     * \brief Creates a DefaultPipeline with default module settings.
     *
     * Initializes all internal modules to their default configuration.
     *
     * \since ids_peak_icv 1.0
     */
    DefaultPipeline();

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.0
     */
    ~DefaultPipeline() override;

    /*!
     * \brief Converts the current pipeline settings into a string format.
     *
     * Serializes all relevant configuration parameters of the pipeline into
     * a single string, which can be stored or transferred for later use.
     *
     * The export includes:
     *   - Pipeline version
     *   - Pipeline type
     *   - Creation timestamp (ISO UTC)
     *   - All module settings (type + serialized data)
     *
     * \return A string representation of the pipeline's current configuration state.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::string ExportSettingsToString() const override;

    /*!
     * \brief Restores pipeline settings from a previously serialized string.
     *
     * Parses the provided string and applies the contained configuration values
     * to update the internal state of the pipeline accordingly.
     *
     * This includes:
     *   - Validation of version (must be >= 1).
     *   - Validation of pipeline type (must match this pipeline).
     *   - Restoring each module's settings by invoking its `deserialize` method.
     *
     * \param settings A string containing the serialized pipeline configuration.
     *
     * \throws peak::icv::CorruptedException  If the version or type is invalid.
     * \throws peak::icv::IOException         If required module settings are missing.
     *
     * \since ids_peak_icv 1.0
     */
    void ImportSettingsFromString(const std::string& settings) override;

    /*!
     * \brief Resets all modules in the pipeline to their default state.
     * Also resets their enabled state.
     * In addition, this also resets the pipelines internal properties to default:
     *      - ProcessingPolicy to peak::pipeline::ProcessingPolicy::Fast
     *
     * \since ids_peak_icv 1.0
     */
    void ResetToDefault() override;

    /*!
     * \returns The pipeline type identifier as a string, primarily used for serialization.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD const char* GetType() const override;

    /*!
     * \anchor pipeline_process_image
     *
     * \brief Applies the pipeline to the given image and returns the result as a new image.
     *
     * The returned image is always a new instance.
     * If no processing is applied, it will be a deep copy of the input.
     *
     * \warning The input image may be modified during execution due to in-place operations.
     *          If you need to preserve the original image,
     *          create a copy before calling this function.
     *
     * \note This operation disregards any specified image regions
     *       and processes the entire image.
     *
     * \param image Input image to be processed.
     *
     * \return A new image containing the processed input or a deep copy of the input.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::icv::Image& image) const;

    /*!
     * \anchor pipeline_process_image_view
     *
     * \brief Applies the pipeline to an image view and returns the result as a new image.
     *
     * Internally, the image view is converted into an Image before processing.
     *
     * The returned image is always a new instance.
     * If no processing is applied, it will contain a deep copy of the input buffer.
     *
     * \note This operation disregards any specified image regions and processes the entire image.
     *
     * \param imageView Input image view to be processed.
     *
     * \return A new image containing the processed input or a deep copy of the input.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image Process(const peak::common::IImageView& imageView) const;

    /*!
     * \brief Convenience operator for processing input using the pipeline.
     *
     * Equivalent to calling \ref pipeline_process_image "Process".
     *
     * \param image The image to be processed.
     *
     * \return A new image containing the processed input or a deep copy of the input.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image operator<<(const peak::icv::Image& image) const;

    /*!
     * \brief Convenience operator for processing input using the pipeline.
     *
     * Equivalent to calling \ref pipeline_process_image_view "Process".
     *
     * \param imageView The image view to be processed.
     *
     * \return A new image containing the processed input or a deep copy of the input.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::icv::Image operator<<(const peak::common::IImageView& imageView) const;

    /*!
     * \brief Frees unused internal buffers.
     *
     * Conversion modules use pre-allocated internal buffers to accelerate conversions.
     * When the image size or pixel format changes, new buffers are allocated, which may cause
     * the internal buffer pool to grow over time. This function can be used to release
     * unused buffers and reduce memory usage.
     *
     * \warning Avoid calling this function too frequently (e.g., after every resize or format change),
     * as it introduces some overhead and may negatively impact performance.
     *
     * \since ids_peak_icv 1.0
     */
    void ReleaseBuffers() const;

    /*!
     * \brief Provides access to the mirror feature for image mirroring operations.
     *
     * The mirror feature allows horizontal (left-right) and vertical (up-down) mirroring
     * of images during pipeline processing.
     *
     * \return A reference to the \ref features::MirrorFeature "mirror feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::MirrorFeature& Mirror() const;

    /*!
     * \brief Provides access to the rotation feature for image rotation operations.
     *
     * The rotation feature allows rotating images in 90-degree increments (0°, 90°, 180°, 270°)
     * during pipeline processing.
     *
     * \return A reference to the \ref features::RotationFeature "rotation feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::RotationFeature& Rotation() const;

    /*!
     * \brief Provides access to the gain feature for brightness and white balance adjustments.
     *
     * The gain feature allows adjustment of master gain (overall brightness) and individual
     * color channel gains (red, green, blue) for white balance correction.
     *
     * \return A reference to the \ref features::GainFeature "gain feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::GainFeature& Gain() const;

    /*!
     * \brief Provides access to the color correction feature for color space transformations.
     *
     * The color correction feature applies a 3x3 transformation matrix to perform color
     * balancing.
     *
     * \return A reference to the \ref features::ColorCorrectionFeature "color correction feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::ColorCorrectionFeature& ColorCorrection() const;

    /*!
     * \brief Provides access to the saturation feature for color intensity adjustments.
     *
     * The saturation feature allows adjustment of color saturation levels, making colors
     * more vivid (higher saturation) or more muted (lower saturation).
     *
     * \return A reference to the \ref features::SaturationFeature "saturation feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::SaturationFeature& Saturation() const;

    /*!
     * \brief Provides access to the gamma feature for brightness and contrast adjustments.
     *
     * The gamma feature applies inverse gamma correction to adjust image luminance,
     * preparing images for linear domain processing or display.
     *
     * \return A reference to the \ref features::GammaFeature "gamma feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::GammaFeature& Gamma() const;

    /*!
     * \brief Provides access to the digital black feature for sensor offset correction.
     *
     * The digital black feature compensates for sensor digital black offsets by subtracting
     * a configurable black level and normalizing the result.
     *
     * \return A reference to the \ref features::DigitalBlackFeature "digital black feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::DigitalBlackFeature& DigitalBlack() const;

    /*!
     * \brief Provides access to the sharpening feature for image detail enhancement.
     *
     * The sharpening feature applies edge-based sharpening filters to enhance image detail
     * and improve perceived image sharpness.
     *
     * \return A reference to the \ref features::SharpeningFeature "sharpening feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::SharpeningFeature& Sharpening() const;

    /*!
     * \brief Provides access to the hot pixel correction feature for defective pixel repair.
     *
     * The hot pixel correction feature identifies and corrects defective pixels (hot pixels)
     * in camera images by replacing them with interpolated values from neighboring pixels.
     *
     * \return A reference to the \ref features::HotpixelCorrectionFeature "hotpixel correction feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::HotpixelCorrectionFeature& HotpixelCorrection() const;

    /*!
     * \brief Provides access to the binning feature for resolution reduction and noise improvement.
     *
     * The binning feature reduces image resolution by combining adjacent pixels through
     * averaging or summation, improving signal-to-noise ratio at the cost of resolution.
     *
     * \return A reference to the \ref features::BinningFeature "binning feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::BinningFeature& Binning() const;

    /*!
     * \brief Provides access to the decimation feature for resolution reduction by pixel skipping.
     *
     * The decimation feature reduces image resolution by skipping pixels in a defined pattern,
     * providing a faster alternative to binning for resolution reduction.
     *
     * \return A reference to the \ref features::DecimationFeature "decimation feature".
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD features::DecimationFeature& Decimation() const;

    /*!
     * \brief Provides access to the chromatic adaption feature for adjusting to lighting conditions.
     *
     * The chromatic adaption feature adjusts the image's colors based on the known or estimated
     * correlated color temperature of the light source, maintaining consistent color perception.
     *
     * \return A reference to the \ref features::ChromaticAdaptionFeature "chromatic adaption feature".
     *
     * \since ids_peak_icv 1.3
     */
    PEAK_COMMON_NO_DISCARD features::ChromaticAdaptionFeature& ChromaticAdaption() const;

    /*!
     * \brief Defines the desired pixel format for processed images.
     *
     * The pipeline will convert images to this format during processing.
     *
     * \warning
     * When set to a Bayer format,
     * the \ref ColorCorrection, \ref Gamma and \ref Sharpening features
     * will not process the image because they do not support Bayer formats.
     * This may result in unexpected image quality if these features are enabled.
     *
     * \param format The new pixel format as a `PixelFormat` enum.
     *
     * \see GetOutputPixelFormat(), \ref features::ColorCorrectionFeature, \ref features::GammaFeature, \ref features::SharpeningFeature
     *
     * \since ids_peak_icv 1.0
     */
    void SetOutputPixelFormat(peak::common::PixelFormat format);

    /*!
     * \return The current output pixel format as a `PixelFormat` enum.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD peak::common::PixelFormat GetOutputPixelFormat() const;

    /*!
     * \brief Sets the processing policy for the image processing pipeline.
     *
     * This policy determines the trade-off between processing speed and
     * image quality throughout the entire pipeline.
     *
     * - \b Fast: Prioritizes processing speed, which may reduce image quality.
     * - \b Balanced: Balances processing speed and image quality for typical use cases.
     * - \b Enhanced: Prioritizes improved image quality at the cost of reduced processing speed.
     *
     * \param policy The desired processing policy.
     *
     * \since ids_peak_icv 1.0
     */
    void SetProcessingPolicy(ProcessingPolicy policy);

    /*!
     * \return The currently used processing policy.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD ProcessingPolicy GetProcessingPolicy() const
    {
        return m_processingPolicy;
    }

    /*!
     * \brief Sets an auto feature module for automatic image adjustments.
     *
     * These adjustments can include features such as
     * image brightness, white balance, and focus,
     * depending on the capabilities of the provided module.
     *
     * \note
     * If there is no auto feature module specified,
     * this step will be skipped during processing.
     *
     * \param autoFeatureModule The auto feature module.
     *
     * \since ids_peak_icv 1.0
     */
    void SetAutoFeatureModule(const std::shared_ptr<modules::IAutoFeature>& autoFeatureModule);

protected:
    PEAK_COMMON_NO_DISCARD std::vector<std::shared_ptr<modules::IModule>> GetModules() const override;

    PEAK_COMMON_NO_DISCARD virtual std::vector<std::shared_ptr<features::IFeature>> GetFeatures() const;

    PEAK_COMMON_NO_DISCARD virtual std::shared_ptr<detail::MonoConversionModule> MonoConversionModule() const;

    PEAK_COMMON_NO_DISCARD virtual std::shared_ptr<detail::PixelFormatConversionModule> FinalConversionModule() const;

private:
    static std::string GetCurrentIsoUtcTime();

    PEAK_COMMON_NO_DISCARD inline peak::common::Any Process(const peak::common::Any& input) const override;

    peak::common::Any operator<<(const peak::common::Any& input) override
    {
        return Process(input);
    }

    ProcessingPolicy m_processingPolicy{ ProcessingPolicy::Fast };

    std::shared_ptr<detail::UnpackModule> m_unpack{ std::make_shared<detail::UnpackModule>() };
    std::shared_ptr<detail::HotpixelCorrectionModule> m_hotpixel{ std::make_shared<detail::HotpixelCorrectionModule>() };
    std::shared_ptr<detail::DownsamplingModule> m_binning{ std::make_shared<detail::DownsamplingModule>(
        detail::DownsamplingMode::BinningAverage, "Binning") };
    std::shared_ptr<detail::DownsamplingModule> m_decimation{ std::make_shared<detail::DownsamplingModule>(
        detail::DownsamplingMode::Decimation, "Decimation") };
    std::shared_ptr<detail::TransformationModule> m_transformation{ std::make_shared<detail::TransformationModule>() };
    std::shared_ptr<detail::GainModule> m_gain{ std::make_shared<detail::GainModule>() };
    std::shared_ptr<detail::DebayerModule> m_debayer{ std::make_shared<detail::DebayerModule>() };
    std::shared_ptr<detail::ColorMatrixTransformationModule> m_colorCorrection{
        std::make_shared<detail::ColorMatrixTransformationModule>()
    };
    std::shared_ptr<detail::MonoConversionModule> m_monoConversion{ std::make_shared<detail::MonoConversionModule>() };
    std::shared_ptr<detail::SharpeningModule> m_sharpening{ std::make_shared<detail::SharpeningModule>() };
    std::shared_ptr<detail::ToneCurveCorrectionModule> m_toneCurveCorrection{ std::make_shared<detail::ToneCurveCorrectionModule>() };
    std::shared_ptr<detail::PixelFormatConversionModule> m_finalConversion{ std::make_shared<detail::PixelFormatConversionModule>() };

    std::shared_ptr<features::HotpixelCorrectionFeature> m_hotpixelFeature{ new features::HotpixelCorrectionFeature{ *m_hotpixel } };
    std::shared_ptr<features::BinningFeature> m_binningFeature{ new features::BinningFeature{ *m_binning } };
    std::shared_ptr<features::DecimationFeature> m_decimationFeature{ new features::DecimationFeature{ *m_decimation } };
    std::shared_ptr<features::MirrorFeature> m_mirrorFeature{ new features::MirrorFeature{ *m_transformation } };
    std::shared_ptr<features::RotationFeature> m_rotationFeature{ new features::RotationFeature{ *m_transformation } };
    std::shared_ptr<features::GainFeature> m_gainFeature{ new features::GainFeature{ *m_gain } };
    std::shared_ptr<features::ColorCorrectionFeature> m_colorCorrectionFeature{ new features::ColorCorrectionFeature{
        *m_colorCorrection } };
    std::shared_ptr<features::SaturationFeature> m_saturationFeature{ new features::SaturationFeature{ *m_colorCorrection } };
    std::shared_ptr<features::SharpeningFeature> m_sharpeningFeature{ new features::SharpeningFeature{ *m_sharpening } };
    std::shared_ptr<features::GammaFeature> m_gammaFeature{ new features::GammaFeature{ *m_toneCurveCorrection } };
    std::shared_ptr<features::DigitalBlackFeature> m_digitalBlackFeature{ new features::DigitalBlackFeature{ *m_toneCurveCorrection } };
    std::shared_ptr<features::ChromaticAdaptionFeature> m_chromaticAdaptionFeature{ new features::ChromaticAdaptionFeature{
        *m_colorCorrection } };

    std::shared_ptr<modules::IAutoFeature> m_autoFeatureModule;

    constexpr static int pipelineVersion{ 1 };
};

inline DefaultPipeline::DefaultPipeline()
{
    m_monoConversion->SetEnabled(false);

    const auto format = m_finalConversion->GetOutputPixelFormat();

    const auto bitDepth = peak::common::PixelFormatInfo(format).GetStorageBitsPerChannel();
    m_unpack->SetProcessingPolicy(m_processingPolicy);
    m_unpack->SetTargetBitDepth(bitDepth);
    m_debayer->SetProcessingPolicy(m_processingPolicy);
    m_debayer->SetTargetBitDepth(bitDepth);
}

inline DefaultPipeline::~DefaultPipeline()
{
    if (m_autoFeatureModule)
    {
        m_autoFeatureModule->SetGainModule(nullptr);
    }
}

inline std::string DefaultPipeline::ExportSettingsToString() const
{
    const auto archive = std::make_shared<peak::icv::Archive>();

    const auto moduleList = GetModules();
    std::vector<std::shared_ptr<peak::common::serialization::IArchive>> modules;
    modules.reserve(moduleList.size());

    for (const auto& module : moduleList)
    {
        if (module == nullptr)
        {
            continue;
        }
        auto moduleArchive = archive->CreateArchive();
        moduleArchive->SetString("Type", module->GetType());

        auto moduleDataArchive = moduleArchive->CreateArchive();
        module->Serialize(*moduleDataArchive);
        moduleArchive->SetArchive("Data", moduleDataArchive);
        modules.push_back(moduleArchive);
    }
    archive->SetArchiveArray("Modules", modules);
    archive->SetInt("Version", pipelineVersion);
    archive->SetString("Type", GetType());
    archive->SetString("Creation", GetCurrentIsoUtcTime());

    peak::icv::Serializer serializer;

    std::stringstream ss;
    serializer.Write(*archive, ss);
    return ss.str();
}

inline void DefaultPipeline::ImportSettingsFromString(const std::string& settings)
{
    peak::icv::Deserializer deserializer;

    std::stringstream ss;
    ss << settings;
    const auto archive = deserializer.Read(ss);

    const auto version = archive->GetInt("Version");

    if (version < 1)
    {
        throw peak::icv::CorruptedException(
            "The 'Version' entry " + std::to_string(version) + " in the settings string is invalid! Must be at least 1.");
    }

    const auto pipelineType = archive->GetString("Type");
    if (pipelineType != GetType())
    {
        throw peak::icv::CorruptedException(
            "The settings for " + pipelineType + " are not compatible with this pipeline (" + GetType() + ").");
    }

    const auto modules = GetModules();

    std::unordered_map<std::string, std::shared_ptr<peak::common::serialization::IArchive>> archiveMap;
    auto moduleArchives = archive->GetArchiveArray("Modules");

    for (const auto& moduleArchive : moduleArchives)
    {
        const auto moduleType = moduleArchive->GetString("Type");
        const auto data = moduleArchive->GetArchive("Data");
        archiveMap.emplace(moduleType, data);
    }

    for (const auto& module : modules)
    {
        const auto found = archiveMap.find(module->GetType());
        if (found == archiveMap.end())
        {
            throw peak::icv::IOException(std::string("The settings for module ") + module->GetType() + " are missing!");
        }

        module->Deserialize(*found->second);
    }
}

inline void DefaultPipeline::ResetToDefault()
{
    for (const auto& module : GetModules())
    {
        module->ResetToDefault();
        module->SetEnabled(true);
    }
    /*
     * Not every feature calls reset to default of its underlying module. Therefor, every feature's reset to default
     * can have its own logic and must be resetted separately.
     */
    for (const auto& feature : GetFeatures())
    {
        feature->ResetToDefault();
        feature->SetEnabled(true);
    }
    MonoConversionModule()->SetEnabled(false);
    m_processingPolicy = ProcessingPolicy::Fast;
}

inline const char* DefaultPipeline::GetType() const
{
    return "DefaultPipeline";
}

inline void DefaultPipeline::ReleaseBuffers() const
{
    m_unpack->ReleaseBuffers();
    m_debayer->ReleaseBuffers();
    MonoConversionModule()->ReleaseBuffers();
    FinalConversionModule()->ReleaseBuffers();
}

inline features::MirrorFeature& DefaultPipeline::Mirror() const
{
    return *m_mirrorFeature;
}

inline features::RotationFeature& DefaultPipeline::Rotation() const
{
    return *m_rotationFeature;
}

inline features::GainFeature& DefaultPipeline::Gain() const
{
    return *m_gainFeature;
}

inline features::ColorCorrectionFeature& DefaultPipeline::ColorCorrection() const
{
    return *m_colorCorrectionFeature;
}

inline features::SaturationFeature& DefaultPipeline::Saturation() const
{
    return *m_saturationFeature;
}

inline features::GammaFeature& DefaultPipeline::Gamma() const
{
    return *m_gammaFeature;
}

inline features::DigitalBlackFeature& DefaultPipeline::DigitalBlack() const
{
    return *m_digitalBlackFeature;
}

inline features::SharpeningFeature& DefaultPipeline::Sharpening() const
{
    return *m_sharpeningFeature;
}

inline features::HotpixelCorrectionFeature& DefaultPipeline::HotpixelCorrection() const
{
    return *m_hotpixelFeature;
}

inline features::BinningFeature& DefaultPipeline::Binning() const
{
    return *m_binningFeature;
}

inline features::DecimationFeature& DefaultPipeline::Decimation() const
{
    return *m_decimationFeature;
}

inline features::ChromaticAdaptionFeature& DefaultPipeline::ChromaticAdaption() const
{
    return *m_chromaticAdaptionFeature;
}

inline peak::common::Any DefaultPipeline::Process(const peak::common::Any& input) const
{
    auto data = input;

    for (const auto& mod : GetModules())
    {
        if (!mod)
        {
            continue;
        }

        try
        {
            data = mod->Process(data);
        }
        catch (const peak::icv::Exception& e)
        {
            const auto errorCode = e.GetStatus();
            const auto* const what = e.what();
            const auto* const moduleType = mod->GetType();

            const auto errorText = std::string{ "[" } + moduleType + "] " + what;
            switch (errorCode)
            {
            case PEAK_ICV_STATUS_LIBRARY_NOT_INITIALIZED:
            case PEAK_ICV_STATUS_DYNAMIC_DEPENDENCY_MISSING:
                throw peak::icv::InvalidConfigurationException(errorText, errorCode);
            case PEAK_ICV_STATUS_INVALID_HANDLE:
            case PEAK_ICV_STATUS_INVALID_BUFFER_SIZE:
            case PEAK_ICV_STATUS_MISMATCH:
            case PEAK_ICV_STATUS_NULL_POINTER:
            case PEAK_ICV_STATUS_NOT_SUPPORTED:
            case PEAK_ICV_STATUS_NOT_POSSIBLE:
                throw peak::icv::NotSupportedException(errorText);
            case PEAK_ICV_STATUS_CORRUPTED:
                throw peak::icv::CorruptedException(errorText);
            case PEAK_ICV_STATUS_OUT_OF_RANGE:
                throw peak::icv::OutOfRangeException(errorText);
            case PEAK_ICV_STATUS_INTERNAL_ERROR:
                throw peak::icv::Exception(errorText, errorCode);
            default:
                throw peak::icv::Exception("Generic Error!", errorCode);
            }
        }
    }

    if (input.AnyCast<peak::icv::Image>().GetData() == data.AnyCast<peak::icv::Image>().GetData())
    {
        return peak::common::Any(data.AnyCast<peak::icv::Image>().Copy());
    }
    return data;
}

inline peak::icv::Image DefaultPipeline::Process(const peak::icv::Image& image) const
{
    return Process(peak::common::Any(image)).AnyCast<peak::icv::Image>();
}

inline peak::icv::Image DefaultPipeline::Process(const peak::common::IImageView& imageView) const
{
    return Process(peak::icv::Image(imageView));
}

inline peak::icv::Image DefaultPipeline::operator<<(const peak::icv::Image& image) const
{
    return Process(image);
}

inline peak::icv::Image DefaultPipeline::operator<<(const peak::common::IImageView& imageView) const
{
    return Process(imageView);
}

inline peak::common::PixelFormat DefaultPipeline::GetOutputPixelFormat() const
{
    return FinalConversionModule()->GetOutputPixelFormat();
}

inline void DefaultPipeline::SetOutputPixelFormat(peak::common::PixelFormat format)
{
    const peak::common::PixelFormatInfo info(format);

    const bool isBayerFormat = info.IsSingleChannel() && info.HasChannel(peak::common::Channel::Bayer);
    const bool isMonoFormat = info.IsSingleChannel() && info.HasIntensityChannel();

    if (isBayerFormat)
    {
        m_debayer->SetConversionPolicy(detail::DebayerConversionPolicy::Bypass);
    }
    else if (isMonoFormat)
    {
        m_debayer->SetConversionPolicy(detail::DebayerConversionPolicy::BayerOnly);
        m_debayer->SetChannelLayout(DebayerChannelLayout::RGB);
    }
    else
    {
        m_debayer->SetConversionPolicy(detail::DebayerConversionPolicy::BayerAndMono);

        if (info.HasChannel(peak::common::Channel::Red) && info.HasChannel(peak::common::Channel::Green)
            && info.HasChannel(peak::common::Channel::Blue))
        {
            m_debayer->SetConversionPolicy(detail::DebayerConversionPolicy::BayerAndMono);
            switch (format)
            {
            case peak::common::PixelFormat::RGB8:
            case peak::common::PixelFormat::RGB10:
            case peak::common::PixelFormat::RGB12:
                m_debayer->SetChannelLayout(DebayerChannelLayout::RGB);
                break;
            case peak::common::PixelFormat::RGBa8:
            case peak::common::PixelFormat::RGBa10:
            case peak::common::PixelFormat::RGBa12:
                m_debayer->SetChannelLayout(DebayerChannelLayout::RGBA);
                break;
            case peak::common::PixelFormat::BGR8:
            case peak::common::PixelFormat::BGR10:
            case peak::common::PixelFormat::BGR12:
                m_debayer->SetChannelLayout(DebayerChannelLayout::BGR);
                break;
            case peak::common::PixelFormat::BGRa8:
            case peak::common::PixelFormat::BGRa10:
            case peak::common::PixelFormat::BGRa12:
                m_debayer->SetChannelLayout(DebayerChannelLayout::BGRA);
                break;
            default:
                break;
            }
        }
    }

    MonoConversionModule()->SetEnabled(isMonoFormat);

    FinalConversionModule()->SetOutputPixelFormat(format);

    const auto bitDepth = info.GetStorageBitsPerChannel();
    m_unpack->SetTargetBitDepth(bitDepth);
    m_debayer->SetTargetBitDepth(bitDepth);
}

inline void DefaultPipeline::SetProcessingPolicy(ProcessingPolicy policy)
{
    m_processingPolicy = policy;

    m_unpack->SetProcessingPolicy(m_processingPolicy);
    m_debayer->SetProcessingPolicy(m_processingPolicy);
}

inline void DefaultPipeline::SetAutoFeatureModule(const std::shared_ptr<modules::IAutoFeature>& autoFeatureModule)
{
    if (m_autoFeatureModule != nullptr)
    {
        m_autoFeatureModule->SetGainModule(nullptr);
    }

    m_autoFeatureModule = autoFeatureModule;

    m_colorCorrection->SetAutoFeatureModule(m_autoFeatureModule);

    if (m_autoFeatureModule != nullptr)
    {
        m_autoFeatureModule->SetGainModule(m_gain);
    }
}

inline std::string DefaultPipeline::GetCurrentIsoUtcTime()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t nowC = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};

#if defined(_WIN32) || defined(_WIN64)
    gmtime_s(&tm, &nowC);
#else
    gmtime_r(&nowC, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}

inline std::vector<std::shared_ptr<modules::IModule>> DefaultPipeline::GetModules() const
{
    if (m_autoFeatureModule == nullptr)
    {
        return { m_unpack, m_hotpixel, m_binning, m_decimation, m_transformation, m_gain, m_debayer, m_colorCorrection,
            MonoConversionModule(), m_sharpening, m_toneCurveCorrection, FinalConversionModule() };
    }

    return { m_unpack, m_hotpixel, m_binning, m_decimation, m_transformation, m_gain, m_debayer, m_colorCorrection, m_autoFeatureModule,
        MonoConversionModule(), m_sharpening, m_toneCurveCorrection, FinalConversionModule() };
}

inline std::vector<std::shared_ptr<features::IFeature>> DefaultPipeline::GetFeatures() const
{
    return { m_hotpixelFeature, m_binningFeature, m_decimationFeature, m_mirrorFeature, m_rotationFeature, m_gainFeature,
        m_colorCorrectionFeature, m_chromaticAdaptionFeature, m_saturationFeature, m_sharpeningFeature, m_gammaFeature,
        m_digitalBlackFeature };
}

inline std::shared_ptr<detail::MonoConversionModule> DefaultPipeline::MonoConversionModule() const
{
    return m_monoConversion;
}

inline std::shared_ptr<detail::PixelFormatConversionModule> DefaultPipeline::FinalConversionModule() const
{
    return m_finalConversion;
}
} // namespace pipeline 
} // namespace peak
