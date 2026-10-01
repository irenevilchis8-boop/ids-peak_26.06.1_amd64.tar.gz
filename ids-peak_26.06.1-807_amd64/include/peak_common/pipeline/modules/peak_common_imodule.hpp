/*!
 * \file    peak_common_imodule.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/serialization/peak_common_iserializable.hpp>
#include <peak_common/types/peak_common_any.hpp>

namespace peak
{
namespace pipeline
{
/*!
 * \ingroup ids_peak_common_pipeline_modules
 * \brief Interface definitions and implementations for individual module types used within a pipeline.
 *
 * This namespace defines interfaces, base types, and their implementations for pipeline modules,
 * which represent discrete processing steps within a pipeline. Modules can be composed
 * and chained to form flexible, reusable data processing workflows.
 *
 * All module-related implementations and interface definitions reside in this namespace.
 *
 * \since ids_peak_common 1.0
 */
namespace modules
{
/*!
 * \ingroup ids_peak_common_pipeline_modules
 * \brief Interface for a module used within a pipeline.
 *
 * Defines the required functions that must be implemented by any module
 * participating in the pipeline. Modules must support enabling/disabling,
 * processing input, and serialization.
 *
 * \since ids_peak_common 1.0
 */
class IModule : public peak::common::serialization::ISerializable
{
public:
    ~IModule() override = default;

    /*!
     * \brief Sets the enabled state of the module.
     *
     * \param enabled True to enable the module, false to disable it.
     *
     * \since ids_peak_common 1.0
     */
    virtual void SetEnabled(bool enabled) = 0;

    /*!
     * \brief Checks whether the module is currently enabled.
     *
     * \return True if the module is enabled, false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual bool IsEnabled() const = 0;

    /*!
     * \brief Returns the type identifier of the module.
     *
     * This should be a unique string identifying the specific implementation
     * of the module.
     *
     * \return A null-terminated string identifying the module type.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual const char* GetType() const = 0;

    /*!
     * \brief Processes input data and returns the result.
     *
     * This function is called by the pipeline to process a unit of data.
     *
     * \param input The input data to be processed.
     *
     * \return The processed input.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual peak::common::Any Process(const peak::common::Any& input) const = 0;

    /*!
     * \brief Resets the module to its default state. The enabled state is not reset.
     *
     * \since ids_peak_common 1.0
     */
    virtual void ResetToDefault() = 0;
};
} // namespace modules
} // namespace pipeline 
} // namespace peak
