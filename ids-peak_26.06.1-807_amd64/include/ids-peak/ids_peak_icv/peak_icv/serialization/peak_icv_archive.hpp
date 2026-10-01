/*!
 * \file    peak_icv_archive.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-19
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <peak_common/detail/peak_common_backend_accessor.hpp>
#include <peak_common/serialization/peak_common_iarchive.hpp>
#include <peak_common_c/detail/peak_common_defines.h>

#include <peak_icv/utils/peak_icv_backend_accessor.hpp>
#include <peak_icv_c/serialization/peak_icv_archive.h>

namespace peak
{
namespace icv
{
/*!
 * \ingroup ids_peak_icv_cpp_serialization
 *
 * \brief
 *   A key-value store that implements the `IArchive` interface.
 *
 * The `Archive` class provides a concrete implementation
 * of a serialization archive
 * that stores data as key-value pairs.
 * It supports various data types including
 * primitives (bool, int64_t, double),
 * strings,
 * nested archives,
 * and arrays of these types.
 *
 * **Example**
 *
 * \code{.cpp}
 * peak::icv::Archive archive{};
 *
 * archive.SetInt("A", 1);
 * archive.SetString("B", "Text");
 * archive.SetIntArray("C", std::vector<int64_t>({ 1, 2, 3 }));
 *
 * auto subArchive = std::make_shared<peak::icv::Archive>();
 * subArchive->SetDouble("a", 1.2);
 * subArchive->SetBool("b", true);
 * archive.SetArchive("D", subArchive);
 * \endcode
 *
 * This class inherits from peak::common::serialization::IArchive.
 *
 * \note
 *   This class is non-copyable but supports move semantics.
 *
 * \see peak::common::serialization::IArchive
 *
 * \since ids_peak_icv 1.0
 */
class Archive
    : public peak::common::serialization::IArchive
    , public detail::IBackendAccessible<Archive>
{
public:
    /*!
     * \brief Constructs an empty `Archive` instance.
     *
     * \throws InvalidConfigurationException The library is not initialized.
     *
     * \since ids_peak_icv 1.0
     */
    Archive();

    /*!
     * \brief Virtual destructor.
     *
     * Ensures proper cleanup of resources when the archive is destroyed.
     *
     * \since ids_peak_icv 1.0
     */
    ~Archive() override;

    /*!
     * \brief Archive instances cannot be copied.
     *
     * \since ids_peak_icv 1.0
     */
    Archive(const Archive&) = delete;

    /*!
     * \brief Archive instances cannot be copy-assigned.
     *
     * \since ids_peak_icv 1.0
     */
    Archive& operator=(const Archive&) = delete;

    /*!
     * \brief Constructs an `Archive` by moving from another instance.
     *
     * \param other The Archive instance to move from.
     *
     * \since ids_peak_icv 1.0
     */
    Archive(Archive&& other) noexcept;

    /*!
     * \brief Assigns this archive by moving from another instance.
     *
     * \param other The Archive instance to move from.
     *
     * \return A Reference to this Archive.
     *
     * \since ids_peak_icv 1.0
     */
    Archive& operator=(Archive&& other) noexcept;

    /*!
     * \brief Creates a new archive instance.
     *
     * Factory method that creates a new archive
     * wrapped in a `shared_ptr`.
     *
     * \return A shared pointer to a new `IArchive` instance.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::shared_ptr<IArchive> CreateArchive() const override;

    /*!
     * \brief Checks whether a key exists in the archive.
     *
     * \param key The key to check.
     *
     * \return `true` if the key exists, `false` otherwise.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD bool HasKey(const std::string& key) const override;

    /*!
     * \brief Returns the type of value stored under a key.
     *
     * \param key The key to get query.
     *
     * \return The `ValueType` representing the stored type.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD ValueType GetValueType(const std::string& key) const override;

    /*!
     * \brief Returns all keys stored in the archive.
     *
     * \return A vector containing all keys currently stored.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<std::string> GetKeys() const override;

    /*!
     * \brief Retruns the number of elements in an array value.
     *
     * \param key The key of the array.
     *
     * \return The number of elements in the array,
     *         or `0` if key doesn't exist
     *         or is not an array.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD size_t GetArrayCount(const std::string& key) const override;

    /*!
     * \brief Sets a boolean value.
     *
     * \param key   The key under which to store the value.
     * \param value The boolean value to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetBool(const std::string& key, bool value) override;

    /*!
     * \brief Sets an integer value.
     *
     * \param key   The key under which to store the value.
     * \param value The 64-bit integer value to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetInt(const std::string& key, int64_t value) override;

    /*!
     * \brief Sets a double precision floating point value.
     *
     * \param key   The key under which to store the value.
     * \param value The double value to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetDouble(const std::string& key, double value) override;

    /*!
     * \brief Sets a string value.
     *
     * \param key   The key under which to store the value.
     * \param value The string value to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetString(const std::string& key, const std::string& value) override;

    /*!
     * \brief Sets a nested archive.
     *
     * \param key   The key under which to store the archive.
     * \param value A shared pointer to the `IArchive` instance to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetArchive(const std::string& key, const std::shared_ptr<IArchive>& value) override;

    /*!
     * \brief Sets an array of boolean values.
     *
     * \param key   The key under which to store the array.
     * \param value The vector of boolean values to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetBoolArray(const std::string& key, const std::vector<bool>& value) override;

    /*!
     * \brief Sets an array of integer values.
     *
     * \param key   The key under which to store the array.
     * \param value The vector of 64-bit integer values to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetIntArray(const std::string& key, const std::vector<int64_t>& value) override;

    /*!
     * \brief Sets an array of double precision floating point values.
     *
     * \param key   The key under which to store the array.
     * \param value The vector of double values to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetDoubleArray(const std::string& key, const std::vector<double>& value) override;

    /*!
     * \brief Sets an array of string values.
     *
     * \param key   The key under which to store the array.
     * \param value The vector of string values to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetStringArray(const std::string& key, const std::vector<std::string>& value) override;

    /*!
     * \brief Sets an array of nested archives.
     *
     * \param key   The key under which to store the array.
     * \param value The vector of shared pointers to `IArchive` instances to store.
     *
     * \since ids_peak_icv 1.0
     */
    void SetArchiveArray(const std::string& key, const std::vector<std::shared_ptr<IArchive>>& value) override;

    // Getter methods for single values

    /*!
     * \brief Returns the boolean value.
     *
     * \param key The key of the value to retrieve.
     *
     * \return The boolean value stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD bool GetBool(const std::string& key) const override;

    /*!
     * \brief Returns the integer value.
     *
     * \param key The key of the value to retrieve.
     *
     * \return The integer value stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD int64_t GetInt(const std::string& key) const override;

    /*!
     * \brief Returns the double precision floating point value.
     *
     * \param key The key of the value to retrieve.
     *
     * \return The double value stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD double GetDouble(const std::string& key) const override;

    /*!
     * \brief Returns the string value.
     *
     * \param key The key of the value to retrieve.
     *
     * \return The string value stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::string GetString(const std::string& key) const override;

    /*!
     * \brief Returns the nested archive.
     *
     * \param key The key of the archive to retrieve.
     *
     * \return A shared pointer to the `IArchive` instance stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::shared_ptr<IArchive> GetArchive(const std::string& key) const override;

    /*!
     * \brief Returns the array of boolean values.
     *
     * \param key The key of the array to retrieve.
     *
     * \return The vector of boolean values stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<bool> GetBoolArray(const std::string& key) const override;

    /*!
     * \brief Returns the array of integer values.
     *
     * \param key The key of the array to retrieve.
     *
     * \return The vector of integer values stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<int64_t> GetIntArray(const std::string& key) const override;

    /*!
     * \brief Returns the array of double precision floating point values.
     *
     * \param key The key of the array to retrieve.
     *
     * \return The vector of double values stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<double> GetDoubleArray(const std::string& key) const override;

    /*!
     * \brief Returns the array of string values.
     *
     * \param key The key of the array to retrieve.
     *
     * \return The vector of string values stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<std::string> GetStringArray(const std::string& key) const override;

    /*!
     * \brief Returns the array of nested archives.
     *
     * \param key The key of the array to retrieve.
     *
     * \return The vector of shared pointers to `IArchive` instances stored under the specified key.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::vector<std::shared_ptr<IArchive>> GetArchiveArray(const std::string& key) const override;

private:
    friend peak::common::detail::BackendAccessor<Archive>;

    explicit Archive(peak_icv_archive_handle handle);

    PEAK_COMMON_NO_DISCARD peak_icv_archive_handle GetHandle() const override
    {
        return m_handle;
    }

    peak_icv_archive_handle m_handle{};
};
} /* namespace icv */
} /* namespace peak */

#include <peak_icv/serialization/detail/peak_icv_archive.ipp>
