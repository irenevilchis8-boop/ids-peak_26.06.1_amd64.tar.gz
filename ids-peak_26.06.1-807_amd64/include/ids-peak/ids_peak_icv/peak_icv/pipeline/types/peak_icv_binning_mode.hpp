/*!
 * \file    peak_icv_binning_mode.hpp
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
 * \brief Mode parameter for the binning algorithm.
 *
 * The enum holding the possible modes.
 *
 * \since ids_peak_icv 1.0
 */
enum class BinningMode
{
    //! The averaged pixel values of neighboring rows and/or columns are computed during binning.
    Average = 0,

    //! The pixel values of neighboring rows and/or columns are summed during binning.
    Sum = 1
};

/*!
 * \brief Converts a BinningMode enum value to its string representation.
 *
 * \param mode The binning mode value to convert.
 * \return A string representation of the binning mode value.
 * \throws NotSupportedException If the mode value is unknown.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(BinningMode mode)
{
    if (mode == BinningMode::Average)
    {
        return "Average";
    }
    if (mode == BinningMode::Sum)
    {
        return "Sum";
    }
    const auto modeStr = std::to_string(static_cast<int>(mode));
    throw peak::icv::NotSupportedException("The given binning mode " + modeStr + " is unknown!");
}

/*!
 * \brief Stream output operator for BinningMode enum.
 *
 * \param os The output stream.
 * \param mode The binning mode value to output.
 * \return Reference to the output stream.
 * \since ids_peak_icv 1.0
 */
inline std::ostream& operator<<(std::ostream& os, BinningMode mode)
{
    return os << ToString(mode);
}

namespace detail
{
/*!
 * \brief Converts a string representation to a BinningMode enum value.
 *
 * \param mode The string representation of the binning mode value.
 * \return The corresponding BinningMode enum value.
 * \throws NotSupportedException If the string does not match any known mode value.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline BinningMode ToBinningMode(const std::string& mode)
{
    if (mode == "Average")
    {
        return BinningMode::Average;
    }
    if (mode == "Sum")
    {
        return BinningMode::Sum;
    }
    throw peak::icv::NotSupportedException("The given binning mode " + mode + " is unknown! ");
}
} // namespace detail

} // namespace pipeline 
} // namespace peak
