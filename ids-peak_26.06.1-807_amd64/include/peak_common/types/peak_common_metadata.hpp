/*!
 * \file    peak_common_metadata.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-08-08
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_metadata_traits.hpp>
#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common/types/peak_common_any.hpp>
#include <peak_common/types/peak_common_metadata_key.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <vector>

namespace peak
{
namespace common
{
namespace detail
{
struct MetadataAccessor;
}

/*!
 * \ingroup ids_peak_common_types
 * \brief Type-safe container for image acquisition metadata.
 *
 * The Metadata class is a flexible container for storing key-value pairs.
 *
 * It supports both:
 * - Arbitrary runtime keys using string identifiers (`*ByName` functions).
 * - Strongly typed compile-time keys via metadata traits (`*ByKey` functions).
 *
 * Values are stored using a type-erased mechanism (\ref peak::common::Any) and
 * can be retrieved either by casting or by trait-based access.
 *
 * \since ids_peak_common 1.0
 */
class Metadata
{
public:
    using allowedTypes = std::tuple<int64_t, std::vector<int64_t>, double, std::vector<double>, std::string, std::vector<std::string>, bool,
        std::vector<bool>>;

    /*!
     * \brief Stores a value using a string-based name.
     *
     * \tparam T Type of the value to store.
     * \param name A runtime string identifier.
     * \param value The value to store.
     *
     * \since ids_peak_common 1.0
     */
    template <typename T>
    void SetValueByName(const std::string& name, T&& value)
    {
        Dispatch(name, std::forward<T>(value), std::is_lvalue_reference<T>{});
    }

    /*!
     * \brief Removes the entry using a string-based name.
     *
     * If the key does not exist, nothing happens.
     *
     * \param name A runtime string identifier.
     *
     * \since ids_peak_common 2.0
     */
    void RemoveEntryByName(const std::string& name)
    {
        m_data.erase(name);
    }

    /*!
     * \brief Stores a value using a strongly typed metadata key.
     *
     * Ensures compile-time type safety using known metadata traits.
     *
     * Known metadata keys are defined in the enum \ref peak::common::MetadataKey.
     *
     * \tparam metadataKey A known metadata key (e.g. MetadataKey::DeviceTimestamp).
     * \tparam T Type of the value. Must match \c detail::MetadataKeyTraits<metadataKey>::type.
     * \param value The value to store.
     *
     * \since ids_peak_common 1.0
     */
    template <MetadataKey metadataKey, typename T>
    void SetValueByKey(T value)
    {
        static_assert(
            std::is_convertible<T, typename detail::MetadataKeyTraits<metadataKey>::type>::value, "Incorrect value type for metadata key");
        constexpr auto key = detail::MetadataKeyTraits<metadataKey>::Name();
        m_data[key] = Any(static_cast<typename detail::MetadataKeyTraits<metadataKey>::type>(std::forward<T>(value)));
    }

    /*!
     * \brief Checks if a given string key is stored in the metadata.
     *
     * \param name The key to check for.
     * \return True if the key exists, false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD bool HasEntryByName(const std::string& name) const
    {
        return m_data.find(name) != m_data.end(); // NOLINT
    }

    /*!
     * \brief Checks if a known key is stored in the metadata.
     *
     * Verifies that the key exists and that the stored type matches the expected trait type.
     *
     * \tparam metadataKey The strongly typed metadata key.
     * \return True if the key exists and the type matches, false otherwise.
     *
     * \since ids_peak_common 1.0
     */
    template <MetadataKey metadataKey>
    PEAK_COMMON_NO_DISCARD bool HasEntryByKey() const
    {
        using trait = detail::MetadataKeyTraits<metadataKey>;
        const auto hasKey = HasEntryByName(trait::Name());

        if (hasKey)
        {
            const auto hasCorrectType = TryGetValueByName(trait::Name()).GetType() == typeid(typename trait::type);
            return hasCorrectType;
        }

        return false;
    }

    /*!
     * \brief Retrieves a value by string name as a type-erased object.
     *
     * \param name The name of the metadata entry.
     * \return A \ref peak::common::Any object containing the value, or empty if not found.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD Any TryGetValueByName(const std::string& name) const
    {
        if (!HasEntryByName(name))
        {
            return {};
        }

        return m_data.at(name);
    }

    /*!
     * \brief Retrieves and casts the value associated with a string name.
     *
     * \tparam T The expected type of the stored value.
     * \param name The name of the metadata entry.
     *
     * \throws peak::common::InvalidCastException if the stored type does not match \c T.
     * \throws peak::common::OutOfRangeException if the name does not exist.
     *
     * \return The value cast to the requested type.
     *
     * \since ids_peak_common 1.0
     */
    template <typename T>
    PEAK_COMMON_NO_DISCARD T GetValueByName(const std::string& name) const
    {
        static_assert(detail::is_in_tuple<std::decay_t<T>, allowedTypes>::value, "T must be one of the allowedTypes!");

        if (!HasEntryByName(name))
        {
            throw OutOfRangeException("There is no value named " + name);
        }

        return TryGetValueByName(name).AnyCast<T>();
    }

    /*!
     * \brief Retrieves the value of a strongly typed metadata key.
     *
     * Provides type-safe access to known metadata keys, defined in
     * \ref peak::common::MetadataKey.
     *
     * \tparam metadataKey The strongly typed metadata key.
     *
     * \throws peak::common::InvalidCastException if the stored type does not match the trait definition.
     * \throws peak::common::OutOfRangeException if the key is not found.
     *
     * \return The stored value of type \c MetadataKeyTraits<metadataKey>::type.
     *
     * \since ids_peak_common 1.0
     */
    template <MetadataKey metadataKey>
    PEAK_COMMON_NO_DISCARD typename detail::MetadataKeyTraits<metadataKey>::type GetValueByKey() const
    {
        using trait = detail::MetadataKeyTraits<metadataKey>;
        if (!HasEntryByName(trait::Name()))
        {
            const std::string keyName = trait::Name();
            throw OutOfRangeException("There is no value named " + keyName);
        }

        return TryGetValueByName(trait::Name()).template AnyCast<typename trait::type>();
    }

    /*!
     * \brief Outputs the metadata keys in human-readable form.
     *
     * Values are not printed since their types are unknown at runtime.
     *
     * \param os The output stream.
     * \param metadata The metadata to print.
     * \return Reference to the stream.
     *
     * \since ids_peak_common 1.0
     */
    friend std::ostream& operator<<(std::ostream& os, const Metadata& metadata)
    {
        bool first = true;
        os << "{";
        for (const auto& pair : metadata.m_data)
        {
            if (!first)
            {
                os << ',';
            }

            // NOTE: Cannot output value, as we don't know the type...
            os << " \"" << pair.first << "\"";

            first = false;
        }
        os << " }";

        return os;
    }

    /*!
     * \brief Returns a string representation of the metadata.
     *
     * Equivalent to writing the object to a stream with \c operator<<.
     *
     * \return A formatted string listing the metadata keys.
     *
     * \since ids_peak_common 1.0
     */
    PEAK_COMMON_NO_DISCARD std::string ToString() const
    {
        std::ostringstream ss;
        ss << *this;
        return ss.str();
    }

    /*!
     * \brief Returns a vector of key names.
     *
     * \return A vector of key names
     *
     * \since ids_peak_common 1.1
     */
    PEAK_COMMON_NO_DISCARD std::vector<std::string> GetKeyNames() const
    {
        std::vector<std::string> names;
        names.reserve(m_data.size());
        std::transform(m_data.cbegin(), m_data.cend(), std::back_inserter(names), [](const auto& pair) {
            return pair.first;
        });

        return names;
    }

private:
    template <typename T>
    void Dispatch(const std::string& key, T&& value, std::true_type)
    {
        using Decayed = typename std::decay<T>::type;

        static_assert(detail::is_in_tuple<Decayed, allowedTypes>::value, "Lvalue type must be exactly one of the 'allowedTypes'!");

        m_data[key] = Any(value);
    }

    template <typename T>
    void Dispatch(const std::string& key, T&& value, std::false_type)
    {
        using Normalized = detail::normalize_t<T>;

        static_assert(detail::is_in_tuple<Normalized, allowedTypes>::value,
            "Rvalue type must be one of the 'allowedTypes' or be able to be widened into one of the 'allowedTypes'!");

        m_data[key] = Any(Cast(std::forward<T>(value)));
    }

    template <typename T>
    void SetValueByNameInternal(const std::string& name, T&& value)
    {
        m_data[name] = Any(std::forward<T>(value));
    }

    template <typename T>
    static detail::normalize_t<T> Cast(T&& v)
    {
        return static_cast<detail::normalize_t<T>>(v);
    }

    template <typename T>
    static std::vector<T> Cast(std::vector<T>&& v)
    {
        return std::move(v);
    }

    std::unordered_map<std::string, Any> m_data;

    friend struct detail::MetadataAccessor;
};

namespace detail
{
struct MetadataAccessor
{
    template <typename T>
    static void SetValueByName(Metadata& metadata, const std::string& key, T&& value)
    {
        metadata.SetValueByNameInternal(key, std::forward<T>(value));
    }
};
} // namespace detail

} // namespace common 
} // namespace peak
