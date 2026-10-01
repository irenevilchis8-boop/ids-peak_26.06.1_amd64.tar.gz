/*!
 * \file    peak_common_pipeline_base.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common/pipeline/peak_common_ipipeline.hpp>

#include <fstream>
#include <sstream>
#include <string>

namespace peak
{
namespace pipeline
{

/*!
 * \ingroup ids_peak_common_pipeline
 * \brief Base class for implementing a custom pipeline.
 *
 * Provides a partial implementation of the IPipeline interface.
 * Can be used as a foundation for creating custom pipeline behavior.
 *
 * \since ids_peak_common 1.0
 */
class PipelineBase : public IPipeline
{
public:
    /*!
     * \copybrief IPipeline::ExportSettingsToFile
     *
     * This base implementation calls ExportSettingsToString() and writes the resulting
     * string to the specified file path.
     *
     * \copydetails IPipeline::ExportSettingsToFile
     */
    void ExportSettingsToFile(const std::string& filePath) const override;

    /*!
     * \copybrief IPipeline::ImportSettingsFromFile
     *
     * This base implementation reads the file contents and passes them to
     * ImportSettingsFromString() to restore the pipeline state.
     *
     * \copydetails IPipeline::ImportSettingsFromFile
     */
    void ImportSettingsFromFile(const std::string& filePath) override;

    /*!
     * \copybrief IPipeline::operator<<
     *
     * This base implementation simply redirects to the Process() method.
     *
     * \copydetails IPipeline::operator<<
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any operator<<(const peak::common::Any& input) override;

    /*!
     * \copybrief IPipeline::Process
     *
     * This base implementation iterates over all modules using GetModules(),
     * calling each module's Process() method in sequence and passing the result along.
     *
     * \copydetails IPipeline::Process
     */
    PEAK_COMMON_NO_DISCARD peak::common::Any Process(const peak::common::Any& input) const override;
};

inline void PipelineBase::ExportSettingsToFile(const std::string& filePath) const
{
    std::ofstream stream;
    stream.exceptions(std::ios::badbit | std::ios::failbit);

    try
    {
        stream.open(filePath);

        stream << ExportSettingsToString();
    }
    catch (const std::ios_base::failure& e)
    {
        throw peak::common::IOException("Saving settings to the file " + filePath + " failed: " + e.what());
    }
}

inline void PipelineBase::ImportSettingsFromFile(const std::string& filePath)
{
    std::ifstream stream;
    stream.exceptions(std::ios::badbit | std::ios::failbit);

    try
    {
        stream.open(filePath);

        std::stringstream ss;
        ss << stream.rdbuf();

        ImportSettingsFromString(ss.str());
    }
    catch (const std::ios_base::failure& e)
    {
        throw peak::common::IOException("Loading settings from the file " + filePath + " failed: " + e.what());
    }
}

inline peak::common::Any PipelineBase::operator<<(const peak::common::Any& input)
{
    return Process(input);
}

inline peak::common::Any PipelineBase::Process(const peak::common::Any& input) const
{
    auto data = input;

    for (const auto& module : GetModules())
    {
        data = module->Process(data);
    }

    return data;
}


} // namespace pipeline 
} // namespace peak
