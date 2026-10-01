/*!
 * \file    peak_icv_processing_policy.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/peak_icv_exception.hpp>

#include <string>

namespace peak
{
namespace pipeline
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_types
 * \brief Specifies the processing policy
 *
 * Defines how the image processing pipeline handles the bit depth conversions during processing,
 * balancing performance and image quality.
 *
 * \warning Changing the processing policy during active processing may cause inconsistent results.
 *          Set the policy before starting image processing operations.
 *
 * \see \ref DefaultPipeline::SetProcessingPolicy(), \ref DefaultPipeline::GetProcessingPolicy()
 *
 * \since ids_peak_icv 1.0
 */
enum class ProcessingPolicy
{
    /*! \brief Prefer speed.
     *
     * Reduces the bit depth of the input image at the earliest suitable stage if the target bit depth is lower.
     * Prioritizes performance over image quality.
     */
    Fast,

    /*! \brief Balance speed and quality.
     *
     * Retains the original bit depth throughout processing until the final pixel format conversion.
     * Provides a trade-off between performance and quality.
     */
    Balanced,

    /*! \brief Prefer quality.
     *
     * Increases the bit depth of the input image for all processing steps, if the target bit depth is higher.
     * Prioritizes improved image quality over performance.
     */
    Enhanced
};

/*!
 * \brief Converts a ProcessingPolicy enum value to its string representation.
 *
 * \param policy The processing policy value to convert.
 * \return A string representation of the processing policy value.
 * \throws NotSupportedException If the policy value is unknown.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(ProcessingPolicy policy)
{
    switch (policy)
    {
    case ProcessingPolicy::Fast:
        return "Fast";
    case ProcessingPolicy::Balanced:
        return "Balanced";
    case ProcessingPolicy::Enhanced:
        return "Enhanced";
    }

    const auto policyStr = std::to_string(static_cast<int>(policy));
    throw peak::icv::NotSupportedException("The given processing policy " + policyStr + " is unknown!");
}

/*!
 * \brief Stream output operator for ProcessingPolicy enum.
 *
 * \param os The output stream.
 * \param policy The processing policy value to output.
 * \return Reference to the output stream.
 * \since ids_peak_icv 1.0
 */
inline std::ostream& operator<<(std::ostream& os, ProcessingPolicy policy)
{
    return os << ToString(policy);
}

namespace detail
{
/*!
 * \brief Converts a string representation to a ProcessingPolicy enum value.
 *
 * \param policy The string representation of the processing policy value.
 * \return The corresponding ProcessingPolicy enum value.
 * \throws NotSupportedException If the string does not match any known policy value.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline ProcessingPolicy ToProcessingPolicy(const std::string& policy)
{
    if (policy == "Fast")
    {
        return ProcessingPolicy::Fast;
    }
    if (policy == "Balanced")
    {
        return ProcessingPolicy::Balanced;
    }
    if (policy == "Enhanced")
    {
        return ProcessingPolicy::Enhanced;
    }
    throw peak::icv::NotSupportedException("The given processing policy " + policy + " is unknown! ");
}
} // namespace detail

} // namespace pipeline 
} // namespace peak
