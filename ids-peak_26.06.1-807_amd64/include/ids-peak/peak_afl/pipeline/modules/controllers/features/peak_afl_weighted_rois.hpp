/*!
 * \file    peak_afl_weighted_rois.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-22
 * \since   1.8
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_afl/peak_afl.hpp>
#include <peak_afl/pipeline/modules/controllers/features/peak_afl_ifeature.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common/types/geometry/peak_common_rectangle.hpp>

#include <memory>

namespace peak
{
namespace pipeline
{
namespace modules
{
namespace autofeature
{
/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Weight enumeration for weighted regions of interest
 *
 * Defines the importance levels that can be assigned to regions of interest
 * in automatic control algorithms. Different weights influence how much
 * priority the algorithms give to each region.
 *
 * \since 1.8
 */
enum class Weight
{
    /*! \brief Low importance - minimal influence on auto algorithms */
    Weak,
    /*! \brief Normal importance - standard influence on auto algorithms */
    Medium,
    /*! \brief High importance - strong influence on auto algorithms */
    Strong
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Preset enumeration for the Region of interest
 *
 * ROI configurations that can be applied without manually specifying coordinates.
 * These presets automatically adapt to the current image size.
 *
 * \since 2.0
 */
enum class RoiPreset
{
    /*! \brief Sets a centered ROI that is one-third of the image dimensions. */
    Center = PEAK_AFL_CONTROLLER_ROI_PRESET_CENTER,
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Weighted region of interest structure
 *
 * Combines a rectangular region with an importance weight for use in
 * automatic control algorithms. This allows different areas of the image
 * to have different levels of influence on auto focus.
 *
 * \since 1.8
 */
struct WeightedROI
{
    /*! \brief The rectangular region of interest */
    peak::common::Rectangle rect;

    /*! \brief The importance weight for this region */
    Weight weight;
};

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Converts Weight enumeration to string representation
 *
 * \param[in] weight The weight value to convert
 * \return String representation of the weight
 * \throws peak::afl::error::InternalErrorException if weight is invalid
 *
 * \see Weight
 *
 * \since 1.8
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(Weight weight)
{
    switch (weight)
    {
    case Weight::Weak:
        return "Weak";
    case Weight::Medium:
        return "Medium";
    case Weight::Strong:
        return "Strong";
    }

    throw peak::afl::error::InternalErrorException("Invalid weight!", PEAK_AFL_STATUS_ERROR);
}

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Stream insertion operator for Weight enumeration
 *
 * Enables direct output of Weight values to output streams using
 * their string representation.
 *
 * \param[in,out] os The output stream to write to
 * \param[in] weight The Weight value to output
 * \return Reference to the output stream for chaining
 *
 * \note Uses ToString() function for string conversion
 *
 * \see ToString(Weight)
 * \see Weight
 *
 * \since 1.8
 */
inline std::ostream& operator<<(std::ostream& os, Weight weight)
{
    return os << ToString(weight);
}

namespace features
{
namespace detail
{
PEAK_COMMON_NO_DISCARD inline Weight ToWeight(const std::string& name)
{
    if (name == "Weak")
    {
        return Weight::Weak;
    }
    if (name == "Medium")
    {
        return Weight::Medium;
    }
    if (name == "Strong")
    {
        return Weight::Strong;
    }
    throw peak::afl::error::InternalErrorException("Invalid weight!", PEAK_AFL_STATUS_ERROR);
}

PEAK_COMMON_NO_DISCARD inline peak_afl_roi_weight ToCType(Weight weight)
{
    switch (weight)
    {
    case Weight::Weak:
        return PEAK_AFL_CONTROLLER_ROI_WEIGHT_WEAK;
    case Weight::Medium:
        return PEAK_AFL_CONTROLLER_ROI_WEIGHT_MEDIUM;
    case Weight::Strong:
        return PEAK_AFL_CONTROLLER_ROI_WEIGHT_STRONG;
    }

    throw peak::afl::error::InternalErrorException("Invalid weight!", PEAK_AFL_STATUS_ERROR);
}

PEAK_COMMON_NO_DISCARD inline Weight ToWeight(peak_afl_roi_weight weight)
{
    switch (weight)
    {
    case PEAK_AFL_CONTROLLER_ROI_WEIGHT_WEAK:
        return Weight::Weak;
    case PEAK_AFL_CONTROLLER_ROI_WEIGHT_MEDIUM:
        return Weight::Medium;
    case PEAK_AFL_CONTROLLER_ROI_WEIGHT_STRONG:
        return Weight::Strong;
    }

    throw peak::afl::error::InternalErrorException("Invalid weight!", PEAK_AFL_STATUS_ERROR);
}

PEAK_COMMON_NO_DISCARD inline peak_afl_weighted_rectangle ToCType(WeightedROI roi)
{
    peak_afl_weighted_rectangle result;
    result.roi.x = static_cast<uint32_t>(roi.rect.GetX());
    result.roi.y = static_cast<uint32_t>(roi.rect.GetY());
    result.roi.width = roi.rect.GetWidth();
    result.roi.height = roi.rect.GetHeight();
    result.weight = ToCType(roi.weight);
    return result;
}

PEAK_COMMON_NO_DISCARD inline WeightedROI ToWeightedROI(peak_afl_weighted_rectangle roi)
{
    const peak::common::Rectangle rect{ { static_cast<int32_t>(roi.roi.x), static_cast<int32_t>(roi.roi.y) },
        { roi.roi.width, roi.roi.height } };
    const auto weight = ToWeight(roi.weight);
    return { rect, weight };
}
} // namespace detail

/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Weighted regions of interest feature implementation for auto controllers
 *
 * The WeightedRois class provides a feature interface for managing multiple
 * weighted regions of interest for auto controllers. This feature allows
 * defining multiple rectangular areas within the image, each with different
 * importance weights that influence automatic algorithms.
 *
 * Weighted ROIs are useful for:
 * - Prioritizing important subjects in the scene
 * - De-emphasizing background areas
 * - Creating complex focus/exposure patterns
 * - Fine-tuning automatic behavior for specific applications
 *
 * Each weighted ROI consists of a rectangular region and a weight (Weak, Medium, Strong)
 * that determines how much influence that region has on the automatic calculations.
 *
 * This class inherits from IFeature<std::vector<WeightedROI>> and provides
 * serialization support for configuration persistence.
 *
 * \note The maximum number of supported weighted ROIs may vary based on the
 *       underlying controller implementation.
 *
 * \see IFeature
 * \see WeightedROI
 * \see Weight
 * \see peak::afl::Controller::SetWeightedROIs()
 * \see peak::afl::Controller::GetWeightedROIs()
 *
 * \since 1.8
 */
class WeightedRois : public IFeature<std::vector<WeightedROI>>
{
public:
    /*!
     * \brief Constructs a WeightedRois feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                       to manage the weighted ROIs parameter. The controller must
     *                       support weighted ROI operations.
     *
     * \pre controller must not be null
     * \pre controller must support weighted ROI functionality
     *
     * \since 1.8
     */
    explicit WeightedRois(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets a single weighted region of interest
     *
     * Sets a single weighted ROI for the controller. This is a convenience
     * method for setting just one weighted region.
     *
     * \param[in] value The weighted ROI to set, containing both the rectangular
     *                 region and its importance weight.
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the ROI is invalid or if the controller is in an invalid state.
     *
     * \see Set(const std::vector<WeightedROI>&)
     * \see Get()
     *
     * \since 1.8
     */
    void Set(const WeightedROI& value)
    {
        m_controller->SetWeightedROI(detail::ToCType(value));
    }

    /*!
     * \brief Sets multiple weighted regions of interest
     *
     * Sets a collection of weighted ROIs for the controller. Each ROI in the
     * vector will influence the automatic algorithms according to its weight.
     *
     * \param[in] value Vector of weighted ROIs to set. Each element contains
     *                  a rectangular region and its importance weight.
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if any ROI is invalid, if too many ROIs are provided, or if the
     *         controller is in an invalid state.
     *
     * \see Set(const WeightedROI&)
     * \see Get()
     *
     * \since 1.8
     */
    void Set(const std::vector<WeightedROI>& value) override
    {
        std::vector<peak_afl_weighted_rectangle> cRois;
        cRois.reserve(value.size());
        std::transform(value.cbegin(), value.cend(), std::back_inserter(cRois), [](const auto& roi) { return detail::ToCType(roi); });
        m_controller->SetWeightedROIs(cRois);
    }

    /*!
     * \brief Sets a predefined region of interest (ROI)
     *
     * \param[in] preset The preset to set.
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \since 2.0
     */
    void SetPreset(RoiPreset preset)
    {
        m_controller->SetROIPreset(static_cast<peak_afl_roi_preset>(preset));
    }

    /*!
     * \brief Gets the current weighted regions of interest
     *
     * Retrieves all currently configured weighted ROIs from the controller.
     *
     * \return Vector of weighted ROIs, each containing a rectangular region
     *         and its importance weight
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD std::vector<WeightedROI> Get() const override
    {
        const auto cRois = m_controller->GetWeightedROIs();

        std::vector<WeightedROI> rois;
        rois.reserve(cRois.size());
        std::transform(
            cRois.cbegin(), cRois.cend(), std::back_inserter(rois), [](const auto& cRoi) { return detail::ToWeightedROI(cRoi); });
        return rois;
    }

    /*!
     * \brief Serializes the current weighted ROIs to an archive
     *
     * Stores all current weighted ROIs in the provided archive for configuration
     * persistence. Each ROI is stored as a sub-archive containing X, Y, Width,
     * Height, and Weight values.
     *
     * \param[in,out] archive The archive to write the weighted ROIs to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        std::vector<std::shared_ptr<peak::common::serialization::IArchive>> archives;
        const auto weightedRois = Get();
        for (const auto& roi : weightedRois)
        {
            auto subArchives = archive.CreateArchive();
            subArchives->SetInt("X", roi.rect.GetX());
            subArchives->SetInt("Y", roi.rect.GetY());
            subArchives->SetInt("Width", roi.rect.GetWidth());
            subArchives->SetInt("Height", roi.rect.GetHeight());
            subArchives->SetString("Weight", ToString(roi.weight));

            archives.push_back(subArchives);
        }

        archive.SetArchiveArray("WeightedRois", archives);
    }

    /*!
     * \brief Deserializes weighted ROIs from an archive
     *
     * Loads weighted ROIs from the provided archive and applies them to the
     * controller. Each ROI is expected to be stored as a sub-archive containing
     * X, Y, Width, Height, and Weight values.
     *
     * \param[in] archive The archive to read the weighted ROIs from
     *
     * \throws May throw serialization exceptions if the archive operation fails
     * \throws May throw controller exceptions if any deserialized ROI is invalid
     *
     * \see Serialize()
     *
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        std::vector<WeightedROI> rois;
        const auto archives = archive.GetArchiveArray("WeightedRois");
        for (const auto& subArchive : archives)
        {
            peak_afl_weighted_rectangle roi;
            roi.roi.x = static_cast<uint32_t>(subArchive->GetInt("X"));
            roi.roi.y = static_cast<uint32_t>(subArchive->GetInt("Y"));
            roi.roi.width = static_cast<uint32_t>(subArchive->GetInt("Width"));
            roi.roi.height = static_cast<uint32_t>(subArchive->GetInt("Height"));
            roi.weight = detail::ToCType(detail::ToWeight(subArchive->GetString("Weight")));
            rois.emplace_back(detail::ToWeightedROI(roi));
        }

        Set(rois);
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual weighted ROI functionality.
     * This controller must support weighted ROI operations and remain valid for
     * the lifetime of this WeightedRois feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
