/*!
 * \file    peak_icv_rotation.hpp
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
 *
 * \brief Angle parameter for the rotation algorithm.
 *
 * \since ids_peak_icv 1.0
 */
enum class Rotation
{
    /*!
     * \brief No rotation applied to the image.
     * \since ids_peak_icv 1.0
     */
    None = 0,

    /*!
     * \brief Rotate the image 90 degrees counterclockwise.
     * \since ids_peak_icv 1.0
     */
    Degree90Counterclockwise = 90,

    /*!
     * \brief Rotate the image 180 degrees (upside down).
     * \since ids_peak_icv 1.0
     */
    Degree180 = 180,

    /*!
     * \brief Rotate the image 90 degrees clockwise.
     * \since ids_peak_icv 1.0
     */
    Degree90Clockwise = 270
};

/*!
 * \brief Converts a Rotation enum value to its string representation.
 *
 * \param rotation The rotation value to convert.
 * \return A string representation of the rotation value.
 * \throws NotSupportedException If the rotation value is unknown.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(Rotation rotation)
{
    switch (rotation)
    {
    case Rotation::None:
        return "None";
    case Rotation::Degree90Counterclockwise:
        return "Degree90Counterclockwise";
    case Rotation::Degree180:
        return "Degree180";
    case Rotation::Degree90Clockwise:
        return "Degree90Clockwise";
    }

    const auto rotationStr = std::to_string(static_cast<int>(rotation));
    throw peak::icv::NotSupportedException("The given rotation " + rotationStr + " is unknown!");
}

/*!
 * \brief Stream output operator for Rotation enum.
 *
 * \param os The output stream.
 * \param rotation The rotation value to output.
 * \return Reference to the output stream.
 * \since ids_peak_icv 1.0
 */
inline std::ostream& operator<<(std::ostream& os, Rotation rotation)
{
    return os << ToString(rotation);
}

namespace detail
{
/*!
 * \brief Converts a string representation to a Rotation enum value.
 *
 * \param rotation The string representation of the rotation value.
 * \return The corresponding Rotation enum value.
 * \throws NotSupportedException If the string does not match any known rotation value.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline Rotation ToRotation(const std::string& rotation)
{
    if (rotation == "None")
    {
        return Rotation::None;
    }
    if (rotation == "Degree90Counterclockwise")
    {
        return Rotation::Degree90Counterclockwise;
    }
    if (rotation == "Degree180")
    {
        return Rotation::Degree180;
    }
    if (rotation == "Degree90Clockwise")
    {
        return Rotation::Degree90Clockwise;
    }
    throw peak::icv::NotSupportedException("The given rotation " + rotation + " is unknown! ");
}
} // namespace detail

} // namespace pipeline 
} // namespace peak
