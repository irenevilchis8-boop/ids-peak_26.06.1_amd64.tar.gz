/*!
 * \file    peak_icv_metadata_handle_guard.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-06-10
 * \since   1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv_c/backend/peak_icv_dll_defines.h>
#include <peak_icv_c/types/peak_icv_metadata.h>
#include <tuple>

namespace peak
{
namespace icv
{
namespace detail
{
class MetadataHandleGuard
{
public:
    MetadataHandleGuard()
    {
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_Create(&m_handle);
        });
    }

    MetadataHandleGuard(const MetadataHandleGuard& other) = delete;

    MetadataHandleGuard(MetadataHandleGuard&& other) noexcept
    {
        if (m_handle != other.m_handle)
        {
            m_handle = other.m_handle;
            other.m_handle = nullptr;
        }
    }

    MetadataHandleGuard& operator=(const MetadataHandleGuard& other) = delete;

    MetadataHandleGuard& operator=(MetadataHandleGuard&& other) noexcept
    {
        if (m_handle != other.m_handle)
        {
            if (m_handle)
            {
                detail::ExecuteAndMapReturnCodes([&] {
                    return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_Destroy(m_handle);
                });
            }

            m_handle = other.m_handle;
            other.m_handle = nullptr;
        }

        return *this;
    }

    ~MetadataHandleGuard()
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_Destroy(m_handle);
    }

    PEAK_COMMON_NO_DISCARD peak_icv_metadata_handle GetHandle() const
    {
        return m_handle;
    }

    peak_icv_metadata_handle* GetHandleAddress()
    {
        return &m_handle;
    }

private:
    peak_icv_metadata_handle m_handle{};
};

} // namespace detail
} // namespace icv 
} // namespace peak
