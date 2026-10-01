/*!
 * \file    peak_icv_metadata_adapter.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2026-06-10
 * \since   1.4
 *
 * Copyright (c) 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once
#include <peak_common/types/peak_common_metadata.hpp>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/utils/peak_icv_metadata_handle_guard.hpp>
#include <peak_icv_c/types/peak_icv_metadata.h>

namespace peak
{
namespace icv
{
namespace detail
{


class MetadataAdapter
{
public:
    static peak::common::Metadata createMetaDataFromHandle(peak_icv_metadata_handle handle);
    static MetadataHandleGuard createMetadataHandleGuardFromMetadata(const peak::common::Metadata& metadata);

private:
    static std::string GetMetadataKeyByIndex(peak_icv_metadata_handle handle, size_t index);

    template <typename T>
    static T GetMetadataValue(peak_icv_metadata_handle handle, const std::string& key)
    {
        (void)handle;
        (void)key;
        static_assert(sizeof(T) == 0, "Unsupported metadata type requested.");
        return T{};
    }

    static void GetMetadataValueFromBackendAndAppendIt(
        peak_icv_metadata_handle handle, const std::string& key, peak::common::Metadata& metadata);

    static void HandleSpecialCaseROIComplexType(peak_icv_metadata_handle handle, peak::common::Metadata& metadata);
    static bool HasKey(peak_icv_metadata_handle handle, const std::string& key);
};

template <>
inline bool MetadataAdapter::GetMetadataValue<bool>(peak_icv_metadata_handle handle, const std::string& key)
{
    bool value{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetBool(handle, key.c_str(), &value);
    });
    return value;
}

template <>
inline std::vector<bool> MetadataAdapter::GetMetadataValue<std::vector<bool>>(peak_icv_metadata_handle handle, const std::string& key)
{
    size_t count{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetArray_GetCount(handle, key.c_str(), &count);
    });
    if (count == 0)
    {
        return {};
    }

    std::vector<uint8_t> buffer(count);
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetBoolArray(
            handle, key.c_str(), reinterpret_cast<bool*>(buffer.data()), buffer.size());
    });

    std::vector<bool> value;
    value.reserve(count);
    std::transform(buffer.begin(), buffer.end(), std::back_inserter(value), [](const auto& val) {
        return static_cast<bool>(val);
    });
    return value;
}

template <>
inline int64_t MetadataAdapter::GetMetadataValue<int64_t>(peak_icv_metadata_handle handle, const std::string& key)
{
    int64_t value{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetInt(handle, key.c_str(), &value);
    });
    return value;
}

template <>
inline std::vector<int64_t> MetadataAdapter::GetMetadataValue<std::vector<int64_t>>(
    peak_icv_metadata_handle handle, const std::string& key)
{
    size_t count{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetArray_GetCount(handle, key.c_str(), &count);
    });
    if (count == 0)
    {
        return {};
    }

    std::vector<int64_t> value(count);
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetIntArray(handle, key.c_str(), value.data(), value.size());
    });
    return value;
}

template <>
inline double MetadataAdapter::GetMetadataValue<double>(peak_icv_metadata_handle handle, const std::string& key)
{
    double value{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetDouble(handle, key.c_str(), &value);
    });
    return value;
}

template <>
inline std::vector<double> MetadataAdapter::GetMetadataValue<std::vector<double>>(peak_icv_metadata_handle handle, const std::string& key)
{
    size_t count{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetArray_GetCount(handle, key.c_str(), &count);
    });
    if (count == 0)
    {
        return {};
    }

    std::vector<double> value(count);
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetDoubleArray(handle, key.c_str(), value.data(), value.size());
    });
    return value;
}

template <>
inline std::string MetadataAdapter::GetMetadataValue<std::string>(peak_icv_metadata_handle handle, const std::string& key)
{
    size_t valueSize{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetString_GetSizeInBytes(handle, key.c_str(), &valueSize);
    });

    // this may not be a string, as this would result in a const char* being passed to a char*
    std::vector<char> buffer(valueSize);
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetString(handle, key.c_str(), buffer.data(), buffer.size());
    });

    return { buffer.data(), buffer.size() - 1 };
}

template <>
inline std::vector<std::string> MetadataAdapter::GetMetadataValue<std::vector<std::string>>(
    peak_icv_metadata_handle handle, const std::string& key)
{
    size_t count{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetArray_GetCount(handle, key.c_str(), &count);
    });

    std::vector<std::string> value;
    value.reserve(count);

    for (size_t index = 0; index < count; ++index)
    {
        size_t valueSize{};
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetStringArrayElement_GetSizeInBytes(handle, key.c_str(), index, &valueSize);
        });

        // this may not be a string, as this would result in a const char* being passed to a char*
        std::vector<char> element(valueSize);
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetStringArrayElement(
                handle, key.c_str(), index, element.data(), element.size());
        });
        value.emplace_back(element.data(), element.size() - 1);
    }

    return value;
}

template <>
inline uint64_t MetadataAdapter::GetMetadataValue<uint64_t>(peak_icv_metadata_handle handle, const std::string& key)
{
    uint64_t value{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetUInt(handle, key.c_str(), &value);
    });
    return value;
}

template <>
inline std::vector<uint64_t> MetadataAdapter::GetMetadataValue<std::vector<uint64_t>>(
    peak_icv_metadata_handle handle, const std::string& key)
{
    size_t count{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetArray_GetCount(handle, key.c_str(), &count);
    });
    if (count == 0)
    {
        return {};
    }

    std::vector<uint64_t> value(count);
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetUIntArray(handle, key.c_str(), value.data(), value.size());
    });
    return value;
}

inline void MetadataAdapter::GetMetadataValueFromBackendAndAppendIt(
    peak_icv_metadata_handle handle, const std::string& key, peak::common::Metadata& metadata)
{
    peak_icv_metadata_value_type_t valueType{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetValueType(handle, key.c_str(), &valueType);
    });

    switch (valueType)
    {
    case PEAK_ICV_METADATA_VALUE_TYPE_BOOL: {
        auto value = GetMetadataValue<bool>(handle, key);
        metadata.SetValueByName(key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_BOOL_ARRAY: {
        auto value = GetMetadataValue<std::vector<bool>>(handle, key);
        metadata.SetValueByName(key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_INT: {
        auto value = GetMetadataValue<int64_t>(handle, key);
        metadata.SetValueByName(key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_INT_ARRAY: {
        auto value = GetMetadataValue<std::vector<int64_t>>(handle, key);
        metadata.SetValueByName(key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_DOUBLE: {
        auto value = GetMetadataValue<double>(handle, key);
        metadata.SetValueByName(key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_DOUBLE_ARRAY: {
        auto value = GetMetadataValue<std::vector<double>>(handle, key);
        metadata.SetValueByName(key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_STRING: {
        auto value = GetMetadataValue<std::string>(handle, key);
        metadata.SetValueByName(key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_STRING_ARRAY: {
        auto value = GetMetadataValue<std::vector<std::string>>(handle, key);
        metadata.SetValueByName(key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_UINT: {
        auto value = GetMetadataValue<uint64_t>(handle, key);
        peak::common::detail::MetadataAccessor::SetValueByName(metadata, key, value);
        break;
    }
    case PEAK_ICV_METADATA_VALUE_TYPE_UINT_ARRAY: {
        auto value = GetMetadataValue<std::vector<uint64_t>>(handle, key);
        peak::common::detail::MetadataAccessor::SetValueByName(metadata, key, value);
        break;
    }
    default:
        std::stringstream ss;
        ss << "The library provided an unknown metadata type: " << valueType << ". The binary library does not match the compiled headers.";
        throw MismatchException(ss.str());
    }
}

inline peak::common::Metadata MetadataAdapter::createMetaDataFromHandle(peak_icv_metadata_handle handle)
{
    peak::common::Metadata metadata;

    const auto numberOfKeys = [&]() {
        size_t count;
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetEntryCount(handle, &count);
        });
        return count;
    }();

    for (size_t keyIndex = 0; keyIndex < numberOfKeys; ++keyIndex)
    {
        const auto key = GetMetadataKeyByIndex(handle, keyIndex);
        GetMetadataValueFromBackendAndAppendIt(handle, key, metadata);
    }

    HandleSpecialCaseROIComplexType(handle, metadata);
    return metadata;
}

inline std::string MetadataAdapter::GetMetadataKeyByIndex(peak_icv_metadata_handle handle, const size_t index)
{
    size_t size{};
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetKey_GetSizeInBytes(handle, index, &size);
    });

    // this may not be a string, as this would result in a const char* being passed to a char*
    std::vector<char> key(size);
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetKey(handle, index, key.data(), key.size());
    });

    return { key.data(), key.size() - 1 };
}

inline bool MetadataAdapter::HasKey(peak_icv_metadata_handle handle, const std::string& key)
{
    bool hasKey;
    ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_HasKey(handle, key.c_str(), &hasKey);
    });
    return hasKey;
}

inline void MetadataAdapter::HandleSpecialCaseROIComplexType(peak_icv_metadata_handle handle, peak::common::Metadata& metadata)
{
    uint64_t x{};
    uint64_t y{};
    uint64_t width{};
    uint64_t height{};

    if (HasKey(handle, "ROIX"))
    {
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetUInt(handle, "ROIX", &x);
        });
    }

    if (HasKey(handle, "ROIY"))
    {
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetUInt(handle, "ROIY", &y);
        });
    }

    if (HasKey(handle, "ROIWidth"))
    {
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetUInt(handle, "ROIWidth", &width);
        });
    }

    if (HasKey(handle, "ROIHeight"))
    {
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_GetUInt(handle, "ROIHeight", &height);
        });
    }

    if (height != 0 && width != 0)
    {
        metadata.SetValueByKey<peak::common::MetadataKey::Roi>(peak::common::RectangleU{
            static_cast<uint32_t>(x), static_cast<uint32_t>(y), static_cast<uint32_t>(width), static_cast<uint32_t>(height) });
    }

    metadata.RemoveEntryByName("ROIX");
    metadata.RemoveEntryByName("ROIY");
    metadata.RemoveEntryByName("ROIWidth");
    metadata.RemoveEntryByName("ROIHeight");
}

inline MetadataHandleGuard MetadataAdapter::createMetadataHandleGuardFromMetadata(const peak::common::Metadata& metadata)
{
    MetadataHandleGuard metadataGuard;

    for (const auto& key : metadata.GetKeyNames())
    {
        const auto value = metadata.TryGetValueByName(key);
        const auto& valueType = value.GetType();

        if (valueType == typeid(bool))
        {
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetBool(metadataGuard.GetHandle(), key.c_str(), value.AnyCast<bool>());
            });
        }
        else if (valueType == typeid(std::vector<bool>))
        {
            const auto& vectorValue = value.template AnyCast<std::vector<bool>>();
            const std::size_t size = vectorValue.size();
            std::vector<uint8_t> list(size);

            std::transform(vectorValue.begin(), vectorValue.end(), list.data(), [](const auto& item) {
                return item;
            });
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetBoolArray(
                    metadataGuard.GetHandle(), key.c_str(), reinterpret_cast<bool*>(list.data()), vectorValue.size());
            });
        }
        else if (valueType == typeid(int64_t))
        {
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetInt(metadataGuard.GetHandle(), key.c_str(), value.AnyCast<int64_t>());
            });
        }
        else if (valueType == typeid(std::vector<int64_t>))
        {
            const auto& vectorValue = value.AnyCast<std::vector<int64_t>>();
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetIntArray(
                    metadataGuard.GetHandle(), key.c_str(), vectorValue.data(), vectorValue.size());
            });
        }
        else if (valueType == typeid(uint64_t))
        {
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetUInt(metadataGuard.GetHandle(), key.c_str(), value.AnyCast<uint64_t>());
            });
        }
        else if (valueType == typeid(std::vector<uint64_t>))
        {
            const auto& vectorValue = value.AnyCast<std::vector<uint64_t>>();
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetUIntArray(
                    metadataGuard.GetHandle(), key.c_str(), vectorValue.data(), vectorValue.size());
            });
        }
        else if (valueType == typeid(double))
        {
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetDouble(metadataGuard.GetHandle(), key.c_str(), value.AnyCast<double>());
            });
        }
        else if (valueType == typeid(std::vector<double>))
        {
            const auto& vectorValue = value.AnyCast<std::vector<double>>();
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetDoubleArray(
                    metadataGuard.GetHandle(), key.c_str(), vectorValue.data(), vectorValue.size());
            });
        }
        else if (valueType == typeid(std::string))
        {
            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetString(
                    metadataGuard.GetHandle(), key.c_str(), value.AnyCast<std::string>().c_str());
            });
        }
        else if (valueType == typeid(std::vector<std::string>))
        {
            const auto& vectorValue = value.AnyCast<std::vector<std::string>>();

            std::vector<const char*> cStrings(vectorValue.size());

            std::transform(vectorValue.begin(), vectorValue.end(), cStrings.begin(), [](const std::string& s) {
                return s.c_str();
            });

            ExecuteAndMapReturnCodes([&] {
                return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetStringArray(
                    metadataGuard.GetHandle(), key.c_str(), cStrings.data(), cStrings.size());
            });
        }
    }

    if (metadata.HasEntryByKey<peak::common::MetadataKey::Roi>())
    {
        const auto roi = metadata.GetValueByKey<peak::common::MetadataKey::Roi>();

        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetUInt(metadataGuard.GetHandle(), "ROIX", roi.GetX());
        });
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetUInt(metadataGuard.GetHandle(), "ROIY", roi.GetY());
        });
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetUInt(metadataGuard.GetHandle(), "ROIWidth", roi.GetWidth());
        });
        ExecuteAndMapReturnCodes([&] {
            return PEAK_ICV_C_ABI_PREFIX peak_icv_Metadata_SetUInt(metadataGuard.GetHandle(), "ROIHeight", roi.GetHeight());
        });
    }

    return metadataGuard;
}


} // namespace detail
} // namespace icv 
} // namespace peak
