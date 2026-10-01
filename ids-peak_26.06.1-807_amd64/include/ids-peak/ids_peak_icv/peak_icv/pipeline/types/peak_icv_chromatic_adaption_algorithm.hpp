/*!
 * \file    peak_icv_chromatic_adaption_algorithm.hpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-02-13
 * \since ids_peak_icv 1.3
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/peak_icv_exception.hpp>
#include <peak_icv_c/algorithms/preprocessing/peak_icv_color_matrix_transformation.h>

#include <ostream>
#include <string>

namespace peak
{
namespace pipeline
{
/*!
 * \ingroup ids_peak_icv_cpp_pipeline_types
 * \brief Algorithm used for chromatic adaption.
 *
 * \since ids_peak_icv 1.3
 */
enum class ChromaticAdaptionAlgorithm
{
    //! Legacy adaption algorithm.
    Legacy = PEAK_ICV_CHROMATIC_ADAPTION_ALGORITHM_LEGACY,

    //! Bradford adaption algorithm (Default).
    Bradford = PEAK_ICV_CHROMATIC_ADAPTION_ALGORITHM_BRADFORD
};

/*!
 * \brief Converts an ChromaticAdaptionAlgorithm enum value to its string representation.
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(ChromaticAdaptionAlgorithm algorithm)
{
    if (algorithm == ChromaticAdaptionAlgorithm::Legacy)
    {
        return "Legacy";
    }
    if (algorithm == ChromaticAdaptionAlgorithm::Bradford)
    {
        return "Bradford";
    }
    const auto algStr = std::to_string(static_cast<int>(algorithm));
    throw peak::icv::NotSupportedException("The given adaption algorithm " + algStr + " is unknown!");
}

inline std::ostream& operator<<(std::ostream& os, ChromaticAdaptionAlgorithm algorithm)
{
    return os << ToString(algorithm);
}

namespace detail
{
PEAK_COMMON_NO_DISCARD inline ChromaticAdaptionAlgorithm ToChromaticAdaptionAlgorithm(const std::string& algorithm)
{
    if (algorithm == "Legacy")
    {
        return ChromaticAdaptionAlgorithm::Legacy;
    }
    if (algorithm == "Bradford")
    {
        return ChromaticAdaptionAlgorithm::Bradford;
    }
    throw peak::icv::NotSupportedException("The given adaption algorithm " + algorithm + " is unknown!");
}
} // namespace detail
} // namespace pipeline 
} // namespace peak
