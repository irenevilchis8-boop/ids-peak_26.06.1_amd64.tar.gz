/*!
 * \file    peak_common_ipipeline.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_common/types/peak_common_any.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

#include <memory>
#include <string>
#include <vector>

/*!
 * \namespace peak::pipeline
 * \ingroup ids_peak_common_pipeline
 *
 * \brief Interfaces and implementations for defining and controlling data processing pipelines.
 *
 * This namespace contains the core interfaces, types, and their implementations
 * for creating and managing pipelines that process input data through a sequence
 * of configurable modules to produce output. It provides foundational building blocks
 * for pipeline configuration, execution, and lifecycle management.
 *
 * All pipeline-related implementations and interface definitions reside in this namespace.
 *
 * \since ids_peak_common 1.0
 */

namespace peak
{
namespace pipeline
{

/*!
 * \ingroup ids_peak_common_pipeline
 *
 * \brief Interface defining the structure and behavior of a processing pipeline.
 *
 * A pipeline is composed of multiple modules chained together in a defined order.
 * When an input is processed, each module's `Process` function is called sequentially,
 * and the final result is returned.
 *
 * \since ids_peak_common 1.0
 */
class IPipeline
{
public:
    virtual ~IPipeline() = default;

    /*!
     * \brief Saves the current settings of the pipeline and its modules to a file.
     *
     * \param filePath Path to the file where the settings should be saved.
     *
     * \since ids_peak_common 1.0
     */
    virtual void ExportSettingsToFile(const std::string& filePath) const = 0;

    /*!
     * \brief Loads the settings of the pipeline and its modules from a file.
     *
     * \param filePath Path to the file from which settings should be loaded.
     *
     * \since ids_peak_common 1.0
     */
    virtual void ImportSettingsFromFile(const std::string& filePath) = 0;

    /*!
     * \brief Returns the current settings of the pipeline and its modules as a string.
     *
     * \return A string representation of the pipeline settings.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual std::string ExportSettingsToString() const = 0;

    /*!
     * \brief Loads settings for the pipeline and its modules from a string.
     *
     * \param settings String containing serialized pipeline settings.
     *
     * \since ids_peak_common 1.0
     */
    virtual void ImportSettingsFromString(const std::string& settings) = 0;

    /*!
     * \brief Resets the pipeline and its modules to their default state.
     *
     * \since ids_peak_common 1.0
     */
    virtual void ResetToDefault() = 0;

    /*!
     * \brief Processes the input through all pipeline modules and returns the result.
     *
     * The input is passed through each module in sequence.
     *
     * \param input The input to process.
     *
     * \return The processed input.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual peak::common::Any Process(const peak::common::Any& input) const = 0;

    /*!
     * \brief Convenience operator for processing input using the pipeline.
     *
     * Equivalent to calling Process(input).
     *
     * \param input The input to process.
     *
     * \return The processed input.
     *
     * \since ids_peak_common 1.0
     */
    virtual peak::common::Any operator<<(const peak::common::Any& input) = 0;

    /*!
     * \brief Returns the type identifier of the pipeline.
     *
     * This is a unique string used to identify the specific pipeline implementation.
     *
     * \return A null-terminated string representing the pipeline type.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual const char* GetType() const = 0;

protected:
    /*!
     * \brief Retrieves the list of all modules in the pipeline, in execution order.
     *
     * \return A vector of shared pointers to the modules.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD virtual std::vector<std::shared_ptr<modules::IModule>> GetModules() const = 0;
};

} // namespace pipeline 
} // namespace peak
