/*!
 * \file    peak_afl_roi.hpp
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
namespace features
{
/*!
 * \ingroup ids_peak_afl_pipeline_features
 * \brief Region of Interest (ROI) feature implementation for auto controllers
 *
 * The Roi class provides a feature interface for managing the region of interest
 * parameter of auto controllers. This feature defines the rectangular area within
 * the image that the automatic algorithms should analyze for exposure, focus,
 * white balance, and other automatic adjustments.
 *
 * By setting an ROI, users can focus the automatic algorithms on specific parts
 * of the image, such as:
 * - A subject in portrait photography
 * - A specific area in industrial inspection
 * - The center region to avoid edge effects
 * - Any custom rectangular region of importance
 *
 * This class inherits from IFeature<peak::common::Rectangle> and provides
 * serialization support for configuration persistence.
 *
 * \note The ROI coordinates must be within the image boundaries and cannot
 *       have negative x or y values.
 *
 * \see IFeature
 * \see peak::common::Rectangle
 * \see peak::afl::Controller::SetROI()
 * \see peak::afl::Controller::GetROI()
 *
 * \since 1.8
 */
class Roi : public IFeature<peak::common::Rectangle>
{
public:
    /*!
     * \brief Constructs a Roi feature with the specified controller
     *
     * \param[in] controller Shared pointer to the auto controller that will be used
     *                       to manage the ROI parameter. The controller must support
     *                       ROI operations.
     *
     * \pre controller must not be null
     * \pre controller must support ROI functionality
     *
     * \since 1.8
     */
    explicit Roi(std::shared_ptr<peak::afl::Controller> controller)
        : m_controller{ std::move(controller) }
    {}

    /*!
     * \brief Sets the region of interest rectangle
     *
     * Sets the rectangular area within the image that the automatic algorithms
     * should analyze. The ROI defines the focus area for automatic exposure,
     * focus, white balance, and other adjustments.
     *
     * \param[in] value The rectangle defining the ROI. Must have non-negative
     *                 x and y coordinates and must fit within the image boundaries.
     *
     * \throws peak::afl::error::InvalidParameterException if x or y coordinates are negative
     * \throws May throw additional exceptions based on the underlying controller
     *         implementation if the ROI is outside image boundaries or invalid.
     *
     * \see Get()
     * \see peak::common::Rectangle
     *
     * \since 1.8
     */
    void Set(const peak::common::Rectangle& value) override
    {
        if (value.GetX() < 0 || value.GetY() < 0)
        {
            throw peak::afl::error::InvalidParameterException(
                "Negative x or y is not supported!", PEAK_AFL_STATUS_INVALID_PARAMETER);
        }

        m_controller->SetROI(
            { static_cast<uint32_t>(value.GetX()), static_cast<uint32_t>(value.GetY()), value.GetWidth(), value.GetHeight() });
    }

    /*!
     * \brief Gets the current region of interest rectangle
     *
     * Retrieves the currently configured rectangular area that the automatic
     * algorithms are analyzing within the image.
     *
     * \return The current ROI as a Rectangle object
     *
     * \throws May throw exceptions based on the underlying controller implementation
     *         if the controller is in an invalid state.
     *
     * \see Set()
     * \see peak::common::Rectangle
     *
     * \since 1.8
     */
    PEAK_COMMON_NO_DISCARD peak::common::Rectangle Get() const override
    {
        const auto result = m_controller->GetROI();
        return { static_cast<int32_t>(result.x), static_cast<int32_t>(result.y), result.width, result.height };
    }

    /*!
     * \brief Serializes the current ROI to an archive
     *
     * Stores the current region of interest rectangle in the provided archive for
     * configuration persistence. The ROI is stored as a sub-archive with the key "Roi"
     * containing X, Y, Width, and Height values.
     *
     * \param[in,out] archive The archive to write the ROI to
     *
     * \throws May throw serialization exceptions if the archive operation fails
     *
     * \see Deserialize()
     *
     * \since 1.8
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override
    {
        auto subArchive = archive.CreateArchive();

        const auto roi = Get();
        subArchive->SetInt("X", roi.GetX());
        subArchive->SetInt("Y", roi.GetY());
        subArchive->SetInt("Width", roi.GetWidth());
        subArchive->SetInt("Height", roi.GetHeight());

        archive.SetArchive("Roi", subArchive);
    }

    /*!
     * \brief Deserializes the ROI from an archive
     *
     * Loads the region of interest rectangle from the provided archive and applies it
     * to the controller. The ROI is expected to be stored as a sub-archive with the
     * key "Roi" containing X, Y, Width, and Height values.
     *
     * \param[in] archive The archive to read the ROI from
     *
     * \throws May throw serialization exceptions if the archive operation fails
     * \throws May throw controller exceptions if the deserialized ROI is invalid
     *
     * \see Serialize()
     *
     * \since 1.8
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override
    {
        const auto subArchive = archive.GetArchive("Roi");

        const auto x = static_cast<int32_t>(subArchive->GetInt("X"));
        const auto y = static_cast<int32_t>(subArchive->GetInt("Y"));
        const auto width = static_cast<uint32_t>(subArchive->GetInt("Width"));
        const auto height = static_cast<uint32_t>(subArchive->GetInt("Height"));

        Set({ x, y, width, height });
    }

private:
    /*!
     * \brief Shared pointer to the auto controller
     *
     * The controller instance that provides the actual ROI functionality.
     * This controller must support ROI operations and remain valid for the
     * lifetime of this Roi feature instance.
     */
    std::shared_ptr<peak::afl::Controller> m_controller;
};
} // namespace features
} // namespace autofeature
} // namespace modules
} // namespace pipeline 
} // namespace peak
