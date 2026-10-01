/*!
 * \file    peak_common_backend_accessor.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-28
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once


#include <peak_common/detail/peak_common_type_traits.hpp>

#include <algorithm>
#include <iterator>
#include <vector>

/// @cond HIDE_FROM_DOXYGEN
namespace peak
{
namespace common
{

namespace detail
{

template <typename T>
class BackendAccessor
{
public:
    static handle_of_t<T> BackendHandle(const T& instance);
    static handle_of_t<T>* BackendHandleAddress(T& instance);
    template <typename... Args>
    static T CreateInstance(Args&&... args);
    static peak::common::detail::c_type_of_t<T> CreateCType(const T& instance);
    static std::vector<T> CreateInstances(std::vector<handle_of_t<T>> handles);
};

template <typename T>
handle_of_t<T> BackendAccessor<T>::BackendHandle(const T& instance)
{
    return instance.GetHandle();
}

template <typename T>
handle_of_t<T>* BackendAccessor<T>::BackendHandleAddress(T& instance)
{
    return instance.GetHandleAddress();
}

template <typename T>
template <typename... Args>
T BackendAccessor<T>::CreateInstance(Args&&... args)
{
    return T{ std::forward<Args>(args)... };
}

template <typename T>
peak::common::detail::c_type_of_t<T> BackendAccessor<T>::CreateCType(const T& instance)
{
    return { static_cast<peak::common::detail::c_type_of_t<T>>(instance) };
}

template <typename T>
std::vector<T> BackendAccessor<T>::CreateInstances(std::vector<handle_of_t<T>> handles)
{
    std::vector<T> instances;
    instances.reserve(handles.size());
    std::transform(handles.begin(), handles.end(), std::back_inserter(instances), [](const auto& handle) {
        return CreateInstance(handle);
    });

    return instances;
}

} // namespace detail
} // namespace common 
} // namespace peak

/// @endcond
