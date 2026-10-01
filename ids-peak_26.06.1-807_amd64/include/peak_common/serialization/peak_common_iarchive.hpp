/*!
 * \file    peak_common_iarchive.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-27
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>

#include <memory>
#include <string>
#include <vector>

namespace peak
{
namespace common
{

/*!
 * \ingroup ids_peak_common_serialization
 *
 * \brief Interfaces for defining serialization and deserialization behavior.
 *
 * This namespace contains interface definitions that specify the contract
 * for serialization and deserialization operations without providing concrete
 * implementations or logic.
 *
 * These interfaces are intended to be implemented by other components or
 * libraries to support specific serialization formats such as binary,
 * text-based, or custom protocols.
 *
 * The goal of this namespace is to establish a consistent and extensible
 * serialization framework across the library ecosystem.
 *
 * All serialization-related interfaces are defined within this namespace.
 *
 * \since ids_peak_common 1.0
 */
namespace serialization
{

/*!
 * \ingroup ids_peak_common_serialization
 * \brief Interface for a hierarchical key-value archive system.
 *
 * Provides methods for storing and retrieving structured data of various types,
 * including primitive values, arrays, and nested archives.
 *
 * This interface is suitable for serialization and deserialization purposes.
 *
 * \since ids_peak_common 1.0
 */
class IArchive
{
public:
    /*!
     * \brief Enumerates supported value types that can be stored or queried in the archive.
     */
    enum class ValueType
    {
        Bool,        //!< Single boolean value
        BoolArray,   //!< Array of booleans

        Int,         //!< 64-bit signed integer
        IntArray,    //!< Array of integers

        Double,      //!< Double-precision floating point
        DoubleArray, //!< Array of doubles

        String,      //!< UTF-8 encoded string
        StringArray, //!< Array of strings

        Archive,     //!< Nested archive object
        ArchiveArray //!< Array of nested archives
    };

    virtual ~IArchive() = default;

    /*!
     * \brief Creates a new, empty archive instance.
     */
    PEAK_COMMON_NO_DISCARD virtual std::shared_ptr<IArchive> CreateArchive() const = 0;

    /*!
     * \brief Checks whether a given key exists in the archive.
     * \param key The key to look for.
     * \return true if the key exists, false otherwise.
     */
    PEAK_COMMON_NO_DISCARD virtual bool HasKey(const std::string& key) const = 0;

    /*!
     * \brief Retrieves the value type associated with a key.
     * \param key The key whose value type to retrieve.
     * \return The ValueType of the stored data.
     */
    PEAK_COMMON_NO_DISCARD virtual ValueType GetValueType(const std::string& key) const = 0;

    /*!
     * \brief Returns a list of all keys currently stored in the archive.
     * \return Vector containing all stored keys.
     */
    PEAK_COMMON_NO_DISCARD virtual std::vector<std::string> GetKeys() const = 0;

    /*!
     * \brief Gets the number of elements in an array stored under the given key.
     * \param key The key referencing the array.
     * \return Element count of the array.
     */
    PEAK_COMMON_NO_DISCARD virtual size_t GetArrayCount(const std::string& key) const = 0;

    // --------------------- Setters ---------------------

    /*! \brief Stores a boolean value. */
    virtual void SetBool(const std::string& key, bool value) = 0;

    /*! \brief Stores a 64-bit signed integer. */
    virtual void SetInt(const std::string& key, int64_t value) = 0;

    /*! \brief Stores a double-precision floating point number. */
    virtual void SetDouble(const std::string& key, double value) = 0;

    /*! \brief Stores a UTF-8 string. */
    virtual void SetString(const std::string& key, const std::string& value) = 0;

    /*! \brief Stores a nested archive object. */
    virtual void SetArchive(const std::string& key, const std::shared_ptr<IArchive>& value) = 0;

    /*! \brief Stores an array of boolean values. */
    virtual void SetBoolArray(const std::string& key, const std::vector<bool>& value) = 0;

    /*! \brief Stores an array of 64-bit integers. */
    virtual void SetIntArray(const std::string& key, const std::vector<int64_t>& value) = 0;

    /*! \brief Stores an array of doubles. */
    virtual void SetDoubleArray(const std::string& key, const std::vector<double>& value) = 0;

    /*! \brief Stores an array of strings. */
    virtual void SetStringArray(const std::string& key, const std::vector<std::string>& value) = 0;

    /*! \brief Stores an array of nested archives. */
    virtual void SetArchiveArray(const std::string& key, const std::vector<std::shared_ptr<IArchive>>& value) = 0;

    // --------------------- Getters ---------------------

    /*! \brief Retrieves a boolean value by key. */
    PEAK_COMMON_NO_DISCARD virtual bool GetBool(const std::string& key) const = 0;

    /*! \brief Retrieves a 64-bit signed integer by key. */
    PEAK_COMMON_NO_DISCARD virtual int64_t GetInt(const std::string& key) const = 0;

    /*! \brief Retrieves a double-precision number by key. */
    PEAK_COMMON_NO_DISCARD virtual double GetDouble(const std::string& key) const = 0;

    /*! \brief Retrieves a string value by key. */
    PEAK_COMMON_NO_DISCARD virtual std::string GetString(const std::string& key) const = 0;

    /*! \brief Retrieves a nested archive by key. */
    PEAK_COMMON_NO_DISCARD virtual std::shared_ptr<IArchive> GetArchive(const std::string& key) const = 0;

    /*! \brief Retrieves an array of booleans by key. */
    PEAK_COMMON_NO_DISCARD virtual std::vector<bool> GetBoolArray(const std::string& key) const = 0;

    /*! \brief Retrieves an array of integers by key. */
    PEAK_COMMON_NO_DISCARD virtual std::vector<int64_t> GetIntArray(const std::string& key) const = 0;

    /*! \brief Retrieves an array of doubles by key. */
    PEAK_COMMON_NO_DISCARD virtual std::vector<double> GetDoubleArray(const std::string& key) const = 0;

    /*! \brief Retrieves an array of strings by key. */
    PEAK_COMMON_NO_DISCARD virtual std::vector<std::string> GetStringArray(const std::string& key) const = 0;

    /*! \brief Retrieves an array of nested archives by key. */
    PEAK_COMMON_NO_DISCARD virtual std::vector<std::shared_ptr<IArchive>> GetArchiveArray(const std::string& key) const = 0;
};

} // namespace serialization
} // namespace common 
} // namespace peak
