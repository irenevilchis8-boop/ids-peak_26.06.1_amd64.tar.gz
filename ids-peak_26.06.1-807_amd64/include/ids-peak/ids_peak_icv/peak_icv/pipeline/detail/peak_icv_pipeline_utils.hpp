/*!
 * \file    peak_icv_pipeline_utils.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/peak_icv_exception.hpp>

namespace peak
{
namespace pipeline
{
namespace detail
{

inline void ValidateVersion(int64_t version, const std::string& moduleName)
{
    if (version < 1)
    {
        throw peak::icv::NotSupportedException("The 'Version' entry " + std::to_string(version) + " in the archive for module "
            + moduleName + " is invalid! Must be at least 1.");
    }
}
} // namespace detail
} // namespace pipeline 
} // namespace peak
