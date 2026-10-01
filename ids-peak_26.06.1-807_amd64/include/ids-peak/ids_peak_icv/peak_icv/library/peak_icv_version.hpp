/*!
 * \file    peak_icv_version.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/types/peak_common_version.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>

#include <cstdint>
#include <string>

namespace peak
{
namespace icv
{
namespace library
{

/*!
 * \ingroup ids_peak_icv_cpp_library
 *
 * \brief Returns the version of the library.
 *
 * This function provides version information as a structured object
 * containing the major, minor, subminor, and patch version numbers.
 * It can be used to programmatically verify compatibility or display
 * the library version at runtime.
 *
 * \return A peak::common::Version object representing the library's version.
 */
inline peak::common::Version Version()
{
    uint32_t major{};
    uint32_t minor{};
    uint32_t subminor{};
    uint32_t patch{};

    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_GetVersion(&major, &minor, &subminor, &patch);
    });

    return { major, minor, subminor, patch };
}

} // namespace library
} /* namespace icv */
} /* namespace peak */
