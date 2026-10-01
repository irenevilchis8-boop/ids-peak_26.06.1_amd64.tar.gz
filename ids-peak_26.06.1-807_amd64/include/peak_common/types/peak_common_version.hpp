/*!
 * \file    peak_common_version.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-12
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_backend_accessor.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common_c/types/peak_common_simple_types.h>
#include <cstdint>
#include <sstream>
#include <string>
#include <tuple>

namespace peak
{
namespace common
{

/*!
 * \ingroup ids_peak_common_types
 * \brief Represents a structured version identifier with four components: major, minor, subminor, and patch.
 *
 * The version format follows the common scheme: <b>major.minor.subminor.patch</b>,
 * where each component represents a different level of change or compatibility.
 * This class provides utilities for comparing versions and converting them to string format.
 *
 * \since ids_peak_common 1.0
 */
class Version
{

public:
    Version(uint32_t major, uint32_t minor, uint32_t subminor, uint32_t patch);

    /*!
     * \brief Retrieves the major version component.
     *
     * This is the first part of the version string: <b>major</b>.minor.subminor.patch.
     *
     * \return The major version number.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetMajor() const;

    /*!
     * \brief Retrieves the minor version component.
     *
     * This is the second part of the version string: major.<b>minor</b>.subminor.patch.
     *
     * \return The minor version number.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetMinor() const;

    /*!
     * \brief Retrieves the subminor version component.
     *
     * This is the third part of the version string: major.minor.<b>subminor</b>.patch.
     *
     * \return The subminor version number.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetSubminor() const;

    /*!
     * \brief Retrieves the patch version component.
     *
     * This is the fourth part of the version string: major.minor.subminor.<b>patch</b>.
     *
     * \return The patch version number.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD uint32_t GetPatch() const;

    /*!
     * \brief Checks if two versions are equal.
     *
     * \param other The version to compare with.
     * \return True if all components are equal; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool operator==(const Version& other) const
    {
        return std::tie(other.m_major, other.m_minor, other.m_subminor, other.m_patch)
            == std::tie(this->m_major, this->m_minor, this->m_subminor, this->m_patch);
    }

    /*!
     * \brief Checks if two versions are not equal.
     *
     * \param other The version to compare with.
     * \return True if any of the components are not equal; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool operator!=(const Version& other) const
    {
        return !(*this == other);
    }

    /*!
     * \brief Checks if this version is less than another version.
     *
     * Comparison is performed lexicographically based on version components.
     *
     * \param other The version to compare with.
     * \return True if this version is less than \p other; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool operator<(const Version& other) const
    {
        return std::tie(this->m_major, this->m_minor, this->m_subminor, this->m_patch)
            < std::tie(other.m_major, other.m_minor, other.m_subminor, other.m_patch);
    }

    /*!
     * \brief Checks if this version is greater than another version.
     *
     * \param other The version to compare with.
     * \return True if this version is greater than \p other; false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool operator>(const Version& other) const
    {
        return other < *this;
    }

    /*!
     * \brief Outputs the version in dot-separated string format (e.g., "1.2.3.4").
     *
     * \param os Output stream.
     * \param version The version to write.
     * \return Reference to the output stream.
     *
     * \since ids_peak_common 1.0
     */
    friend std::ostream& operator<<(std::ostream& os, Version version)
    {
        return os << version.m_major << '.' << version.m_minor << '.' << version.m_subminor << '.' << version.m_patch;
    }

    /*!
     * \brief Converts the version to its string representation (e.g., "1.2.3.4").
     *
     * \return A string containing the formatted version.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD std::string ToString() const
    {
        std::ostringstream ss;
        ss << *this;
        return ss.str();
    }

private:
    friend detail::BackendAccessor<Version>;

    explicit Version(const detail::c_type_of_t<Version>& version)
        : Version(version.major, version.minor, version.subminor, version.patch)
    {}

    explicit operator detail::c_type_of_t<Version>() const
    {
        return { this->GetMajor(), this->GetMinor(), this->GetSubminor(), this->GetPatch() };
    }

    std::uint32_t m_major{};
    std::uint32_t m_minor{};
    std::uint32_t m_subminor{};
    std::uint32_t m_patch{};
};

inline Version::Version(uint32_t major, uint32_t minor, uint32_t subminor, uint32_t patch)
    : m_major{ major }
    , m_minor{ minor }
    , m_subminor{ subminor }
    , m_patch{ patch }
{}

inline uint32_t Version::GetMajor() const
{
    return m_major;
}

inline uint32_t Version::GetMinor() const
{
    return m_minor;
}

inline uint32_t Version::GetSubminor() const
{
    return m_subminor;
}

inline uint32_t Version::GetPatch() const
{
    return m_patch;
}

} // namespace common 
} // namespace peak
