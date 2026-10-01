/*!
 * \file    peak_common_igain_module.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

namespace peak
{
namespace pipeline
{

namespace modules
{
/*!
 * \ingroup ids_peak_common_pipeline_modules
 * \brief Interface for modules that provide gain control functionality.
 *
 * A gain module consists of a master gain value applied to all channels,
 * along with individual gain values for the red, green, and blue channels.
 */
class IGain : public IModule
{
public:
    /*!
     * \brief Sets the master gain value.
     *
     * This value is applied uniformly to all color channels.
     *
     * \param value The master gain value to apply.
     *
     * \since ids_peak_common 1.0
     */
    virtual void SetMaster(float value) = 0;

    /*!
     * \brief Retrieves the current master gain value.
     *
     * \return The master gain value.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual float GetMaster() const = 0;

    /*!
     * \brief Sets the gain value for the red channel.
     *
     * \param value The gain value for the red channel.
     *
     * \since ids_peak_common 1.0
     */
    virtual void SetRed(float value) = 0;

    /*!
     * \brief Retrieves the gain value for the red channel.
     *
     * \return The red channel gain value.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual float GetRed() const = 0;

    /*!
     * \brief Sets the gain value for the green channel.
     *
     * \param value The gain value for the green channel.
     *
     * \since ids_peak_common 1.0
     */
    virtual void SetGreen(float value) = 0;

    /*!
     * \brief Retrieves the gain value for the green channel.
     *
     * \return The green channel gain value.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual float GetGreen() const = 0;

    /*!
     * \brief Sets the gain value for the blue channel.
     *
     * \param value The gain value for the blue channel.
     *
     * \since ids_peak_common 1.0
     */
    virtual void SetBlue(float value) = 0;

    /*!
     * \brief Retrieves the gain value for the blue channel.
     *
     * \return The blue channel gain value.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual float GetBlue() const = 0;
};
} // namespace modules

} // namespace pipeline 
} // namespace peak
