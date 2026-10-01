/*!
 * \file    peak_icv_backend_accessor.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-01-30
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/utils/peak_icv_type_traits.hpp>
#include <algorithm>
#include <iterator>
#include <vector>

namespace peak
{
namespace icv
{

namespace detail
{
template <typename Type>
class IBackendAccessible
{
public:
    virtual ~IBackendAccessible() = default;

protected:
    PEAK_COMMON_NO_DISCARD virtual handle_of_t<Type> GetHandle() const = 0;

private:
    friend Type;

    IBackendAccessible() = default;
};

template <typename Type>
class IBackendExchangeable
{
public:
    virtual ~IBackendExchangeable() = default;

protected:
    PEAK_COMMON_NO_DISCARD virtual handle_of_t<Type>* GetHandleAddress() = 0;

private:
    friend Type;

    IBackendExchangeable() = default;
};

} // namespace detail
} /* namespace icv */
} /* namespace peak */
