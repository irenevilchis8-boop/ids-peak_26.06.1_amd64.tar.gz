/*!
 * \file    peak_common_iautofeature_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_imodule.hpp>

#include <array>
#include <memory>

namespace peak
{
namespace pipeline
{

namespace modules
{
class IGain;

/*!
 * \ingroup ids_peak_common_pipeline_modules
 * \brief Interface for modules that provide auto feature functionality.
 *
 * Defines the necessary functions that any auto feature module must implement.
 *
 * \since ids_peak_common 1.0
 */
class IAutoFeature : public IModule
{
public:
    /*!
     * \brief Called by the pipeline to set the gain module for the auto feature module.
     *
     * This function provides the gain module that the auto feature module can use
     * to apply gain adjustments as needed.
     *
     * \param gainModule The gain module to be controlled by the auto feature module.
     *
     * \since ids_peak_common 1.0
     */
    virtual void SetGainModule(std::shared_ptr<IGain> gainModule) = 0;

    /*!
     * \brief Notifies the auto feature module of the currently used color correction matrix.
     *
     * Allows the auto feature module to adjust its algorithms and gain values based on
     * the provided color correction matrix.
     *
     * \param matrix The 3x3 color correction matrix in row-major order that is
     *               currently in use.
     */
    virtual void SetColorCorrectionMatrix(const std::array<float, 9>& matrix) = 0;
};
} // namespace modules

} // namespace pipeline 
} // namespace peak
