/*!
 * \file    peak_icv_region_selector.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv_c/types/peak_icv_region.h>
#include <functional>

namespace peak
{
namespace icv
{

namespace detail
{
template <typename T>
using select_by_function_t = std::function<peak_icv_status(peak_icv_region_handle*, size_t, T, peak_icv_region_handle*, size_t)>;

template <typename T>
using select_by_get_count_function_t = std::function<peak_icv_status(peak_icv_region_handle*, size_t, T, size_t*)>;

} // namespace detail
} /* namespace icv */
} /* namespace peak */
