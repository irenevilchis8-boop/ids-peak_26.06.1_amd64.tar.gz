/*!
 * \file    peak_icv_archive.ipp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-19
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/serialization/peak_icv_archive.hpp>
#include <peak_icv_c/serialization/peak_icv_archive.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace peak
{
namespace icv
{
namespace detail
{

inline Archive::ValueType MapApiValueType(peak_icv_archive_value_type_t type)
{
    switch (type)
    {
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_BOOL:
        return peak::common::serialization::IArchive::ValueType::Bool;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_BOOL_ARRAY:
        return peak::common::serialization::IArchive::ValueType::BoolArray;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_INT:
        return peak::common::serialization::IArchive::ValueType::Int;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_INT_ARRAY:
        return peak::common::serialization::IArchive::ValueType::IntArray;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_DOUBLE:
        return peak::common::serialization::IArchive::ValueType::Double;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_DOUBLE_ARRAY:
        return peak::common::serialization::IArchive::ValueType::DoubleArray;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_STRING:
        return peak::common::serialization::IArchive::ValueType::String;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_STRING_ARRAY:
        return peak::common::serialization::IArchive::ValueType::StringArray;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_ARCHIVE:
        return peak::common::serialization::IArchive::ValueType::Archive;
    case PEAK_ICV_ARCHIVE_VALUE_TYPE_ARCHIVE_ARRAY:
        return peak::common::serialization::IArchive::ValueType::ArchiveArray;
    default:
        throw NotSupportedException("The given archive type is not supported.");
    }
}
} /* namespace detail */

inline Archive::Archive()
{
    detail::ExecuteAndMapReturnCodes([this] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_Create(&m_handle);
    });
}

inline Archive::Archive(peak_icv_archive_handle handle)
    : m_handle(handle)
{}

inline Archive::~Archive()
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_Destroy(m_handle);
    }
}

inline Archive::Archive(Archive&& other) noexcept
{
    m_handle = std::exchange(other.m_handle, nullptr);
}

inline Archive& Archive::operator=(Archive&& other) noexcept
{
    if (m_handle != nullptr)
    {
        std::ignore = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_Destroy(m_handle);
    }
    m_handle = std::exchange(other.m_handle, nullptr);
    return *this;
}

inline Archive::ValueType Archive::GetValueType(const std::string& key) const
{
    peak_icv_archive_value_type_t recordType{};
    detail::ExecuteAndMapReturnCodes([this, &key, &recordType] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetValueType(m_handle, key.c_str(), &recordType);
    });

    return detail::MapApiValueType(recordType);
}

inline std::vector<std::string> Archive::GetKeys() const
{
    size_t count{};

    detail::ExecuteAndMapReturnCodes([this, &count] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetKeys_GetCount(m_handle, &count);
    });

    std::vector<std::string> keys;
    keys.reserve(count);

    detail::ExecuteAndMapReturnCodes([this, &keys, &count] {
        for (size_t i = 0; i < count; i++)
        {
            size_t size{};
            auto status = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetKeysElement_GetSizeInBytes(m_handle, i, &size);
            if (status != PEAK_ICV_STATUS_SUCCESS)
            {
                return status;
            }

            std::vector<char> buffer(size);
            status = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetKeysElement(m_handle, i, buffer.data(), size);
            if (status != PEAK_ICV_STATUS_SUCCESS)
            {
                return status;
            }

            keys.emplace_back(buffer.data(), buffer.size() - 1);
        }

        return PEAK_ICV_STATUS_SUCCESS;
    });

    return keys;
}

inline size_t Archive::GetArrayCount(const std::string& key) const
{
    size_t arrayCount{};
    detail::ExecuteAndMapReturnCodes([this, &key, &arrayCount] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetArray_GetCount(m_handle, key.c_str(), &arrayCount);
    });
    return arrayCount;
}

inline std::shared_ptr<peak::common::serialization::IArchive> Archive::CreateArchive() const
{
    peak_icv_archive_handle handle{};
    detail::ExecuteAndMapReturnCodes([&handle] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_Create(&handle);
    });
    return std::make_shared<Archive>(peak::common::detail::BackendAccessor<Archive>::CreateInstance(handle));
}

inline bool Archive::HasKey(const std::string& key) const
{
    bool hasKey{};
    detail::ExecuteAndMapReturnCodes([this, &key, &hasKey] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_HasKey(m_handle, key.c_str(), &hasKey);
    });

    return hasKey != 0;
}

inline void Archive::SetBool(const std::string& key, bool value)
{
    detail::ExecuteAndMapReturnCodes([this, &key, &value] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetBool(m_handle, key.c_str(), value);
    });
}

inline void Archive::SetInt(const std::string& key, int64_t value)
{
    detail::ExecuteAndMapReturnCodes([this, &key, &value] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetInt(m_handle, key.c_str(), value);
    });
}

inline void Archive::SetDouble(const std::string& key, double value)
{
    detail::ExecuteAndMapReturnCodes([this, &key, &value] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetDouble(m_handle, key.c_str(), value);
    });
}

inline void Archive::SetString(const std::string& key, const std::string& value)
{
    detail::ExecuteAndMapReturnCodes([this, &key, &value] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetString(m_handle, key.c_str(), value.c_str());
    });
}

inline void Archive::SetArchive(const std::string& key, const std::shared_ptr<IArchive>& value)
{
    auto archive = std::dynamic_pointer_cast<Archive>(value);
    if (archive == nullptr)
    {
        throw NullPointerException("Given archive or archive type is invalid.");
    }
    detail::ExecuteAndMapReturnCodes([this, &key, &archive] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetArchive(m_handle, key.c_str(), archive->m_handle);
    });
}

inline void Archive::SetBoolArray(const std::string& key, const std::vector<bool>& value)
{
    detail::ExecuteAndMapReturnCodes([this, &value, &key] {
        const std::size_t size = value.size();
        std::vector<uint8_t> list;
        list.resize(size);

        std::transform(value.begin(), value.end(), list.data(), [](const auto& item) {
            return item;
        });

        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetBoolArray(m_handle, key.c_str(), reinterpret_cast<bool*>(list.data()), size);
    });
}

inline void Archive::SetIntArray(const std::string& key, const std::vector<int64_t>& value)
{
    detail::ExecuteAndMapReturnCodes([this, &key, &value] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetIntArray(m_handle, key.c_str(), value.data(), value.size());
    });
}

inline void Archive::SetDoubleArray(const std::string& key, const std::vector<double>& value)
{
    detail::ExecuteAndMapReturnCodes([this, &key, &value] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetDoubleArray(m_handle, key.c_str(), value.data(), value.size());
    });
}

inline void Archive::SetStringArray(const std::string& key, const std::vector<std::string>& value)
{
    detail::ExecuteAndMapReturnCodes([this, &value, &key] {
        std::vector<const char*> stringList;
        stringList.reserve(value.size());

        std::transform(value.cbegin(), value.cend(), std::back_inserter(stringList), [](const auto& item) {
            return item.c_str();
        });
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetStringArray(m_handle, key.c_str(), stringList.data(), stringList.size());
    });
}

inline void Archive::SetArchiveArray(const std::string& key, const std::vector<std::shared_ptr<IArchive>>& value)
{
    detail::ExecuteAndMapReturnCodes([this, &value, &key] {
        std::vector<peak_icv_archive_handle> handles;
        handles.reserve(value.size());
        std::transform(std::cbegin(value), std::cend(value), std::back_inserter(handles), [](const auto& item) {
            const auto archive = std::dynamic_pointer_cast<Archive>(item);
            if (archive == nullptr)
            {
                throw NullPointerException("One or multiple of the given archives or archive types are invalid.");
            }
            return archive->m_handle;
        });

        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_SetArchiveArray(m_handle, key.c_str(), handles.data(), handles.size());
    });
}

inline bool Archive::GetBool(const std::string& key) const
{
    bool value{};

    detail::ExecuteAndMapReturnCodes([this, &key, &value]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetBool(m_handle, key.c_str(), &value);
    });

    return value;
}

inline int64_t Archive::GetInt(const std::string& key) const
{
    int64_t value{};

    detail::ExecuteAndMapReturnCodes([this, &key, &value]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetInt(m_handle, key.c_str(), &value);
    });

    return value;
}

inline double Archive::GetDouble(const std::string& key) const
{
    double value{};

    detail::ExecuteAndMapReturnCodes([this, &key, &value]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetDouble(m_handle, key.c_str(), &value);
    });

    return value;
}

inline std::string Archive::GetString(const std::string& key) const
{
    std::string value;

    detail::ExecuteAndMapReturnCodes([this, &key, &value]() {
        size_t size{};
        auto status = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetString_GetSizeInBytes(m_handle, key.c_str(), &size);
        if (status != PEAK_ICV_STATUS_SUCCESS)
        {
            return status;
        }

        std::vector<char> buffer;
        buffer.resize(size);
        status = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetString(m_handle, key.c_str(), buffer.data(), size);
        if (status != PEAK_ICV_STATUS_SUCCESS)
        {
            return status;
        }

        buffer.resize(size - 1);
        value.assign(buffer.data(), buffer.size());

        return PEAK_ICV_STATUS_SUCCESS;
    });

    return value;
}

inline std::shared_ptr<peak::common::serialization::IArchive> Archive::GetArchive(const std::string& key) const
{
    peak_icv_archive_handle handle{};

    detail::ExecuteAndMapReturnCodes([this, &key, &handle]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetArchive(m_handle, key.c_str(), &handle);
    });

    return std::make_shared<Archive>(peak::common::detail::BackendAccessor<Archive>::CreateInstance(handle));
}

inline std::vector<bool> Archive::GetBoolArray(const std::string& key) const
{
    std::vector<bool> values;

    size_t count{};
    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetArray_GetCount(m_handle, key.c_str(), &count);
    });

    if (count == 0)
    {
        return {};
    }

    std::vector<uint8_t> buffer(count);
    detail::ExecuteAndMapReturnCodes([&]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetBoolArray(m_handle, key.c_str(), reinterpret_cast<bool*>(buffer.data()), count);
    });

    values.resize(count);
    std::transform(buffer.begin(), buffer.end(), values.begin(), [](uint8_t b) {
        return static_cast<bool>(b);
    });

    return values;
}

inline std::vector<int64_t> Archive::GetIntArray(const std::string& key) const
{
    size_t count{};
    detail::ExecuteAndMapReturnCodes([this, &key, &count]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetArray_GetCount(m_handle, key.c_str(), &count);
    });
    if (count == 0)
    {
        return {};
    }

    std::vector<int64_t> list(count);

    detail::ExecuteAndMapReturnCodes([this, &key, &list, &count]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetIntArray(m_handle, key.c_str(), list.data(), count);
    });

    return list;
}

inline std::vector<double> Archive::GetDoubleArray(const std::string& key) const
{
    size_t count{};

    detail::ExecuteAndMapReturnCodes([this, &key, &count]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetArray_GetCount(m_handle, key.c_str(), &count);
    });

    if (count == 0)
    {
        return {};
    }

    std::vector<double> list(count);

    detail::ExecuteAndMapReturnCodes([this, &key, &list, &count]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetDoubleArray(m_handle, key.c_str(), list.data(), count);
    });

    return list;
}

inline std::vector<std::string> Archive::GetStringArray(const std::string& key) const
{
    size_t count{};

    detail::ExecuteAndMapReturnCodes([this, &key, &count]() {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetArray_GetCount(m_handle, key.c_str(), &count);
    });

    if (count == 0)
    {
        return {};
    }

    std::vector<std::string> list;
    list.reserve(count);

    detail::ExecuteAndMapReturnCodes([this, &key, &list, &count]() {
        for (size_t i = 0; i < count; i++)
        {
            size_t size{};
            auto status = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetStringArrayElement_GetSizeInBytes(m_handle, key.c_str(), i, &size);
            if (status != PEAK_ICV_STATUS_SUCCESS)
            {
                return status;
            }

            std::vector<char> buffer(size);

            status = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetStringArrayElement(m_handle, key.c_str(), i, buffer.data(), size);
            if (status != PEAK_ICV_STATUS_SUCCESS)
            {
                return status;
            }

            buffer.resize(size - 1);
            list.emplace_back(buffer.data(), buffer.size());
        }

        return PEAK_ICV_STATUS_SUCCESS;
    });

    return list;
}

inline std::vector<std::shared_ptr<peak::common::serialization::IArchive>> Archive::GetArchiveArray(const std::string& key) const
{
    std::vector<std::shared_ptr<IArchive>> archiveList;

    size_t count{};
    detail::ExecuteAndMapReturnCodes([this, &key, &count, &archiveList]() {
        auto status = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetArray_GetCount(m_handle, key.c_str(), &count);
        if (status != PEAK_ICV_STATUS_SUCCESS || count == 0)
        {
            return status;
        }

        std::vector<peak_icv_archive_handle> archiveHandleList{ count };
        archiveList.reserve(count);
        status = PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_GetArchiveArray(m_handle, key.c_str(), archiveHandleList.data(), count);
        std::transform(archiveHandleList.begin(), archiveHandleList.end(), std::back_inserter(archiveList), [](const auto& element) {
            return std::make_shared<Archive>(peak::common::detail::BackendAccessor<Archive>::CreateInstance(element));
        });

        return status;
    });

    return archiveList;
}
} /* namespace icv */
} /* namespace peak */
