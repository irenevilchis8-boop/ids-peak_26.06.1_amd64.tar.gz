/*!
 * \file    peak_icv_serializer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-19
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/serialization/peak_common_iarchive.hpp>
#include <peak_common/serialization/peak_common_iserializer.hpp>

#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/exceptions/peak_icv_exception.hpp>
#include <peak_icv/serialization/detail/peak_icv_serialization_helper.hpp>
#include <peak_icv/serialization/peak_icv_archive.hpp>
#include <peak_icv/serialization/peak_icv_serialization_types.hpp>
#include <peak_icv/serialization/peak_icv_serializer.hpp>
#include <peak_icv/utils/peak_icv_backend_accessor.hpp>

namespace peak
{
namespace icv
{
/*!
 * \ingroup ids_peak_icv_cpp_serialization
 *
 * \brief
 *   Serializer for writing `IArchive` objects to an output stream.
 *
 * This class converts an `IArchive` object
 * into a specific serialization format
 * and writes the result to a stream.
 *
 * **Example**
 *
 * \code{.cpp}
 * peak::icv::Archive archive{};
 * archive.SetInt("id", 42);
 * archive.SetString("name", "example");
 *
 * std::ofstream file("archive.json");
 * peak::icv::Serializer serializer{ peak::icv::SerializationType::Json };
 * serializer.Write(archive, file);
 * file.close();
 * \endcode
 *
 * \since ids_peak_icv 1.0
 */
class Serializer : public peak::common::serialization::ISerializer
{
public:
    /*!
     * \brief
     *   Constructs a `Serializer` with the specified serialization type.
     *
     * The chosen format determines how the archive is written
     * when `Write()` is called.
     * If no type is provided,
     * JSON is used by default.
     *
     * \param type The serialization format to use
     *             (defaults to `SerializationType::Json`).
     *
     * \since ids_peak_icv 1.0
     */
    explicit Serializer(SerializationType type = SerializationType::Json);

    /*!
     * \brief
     *   Serializes an archive and writes it to a stream.
     *
     * Converts the given `IArchive` object
     * into the configured format
     * and writes the serialized data to the provided stream.
     *
     * \param archive The archive to serialize.
     * \param stream  The stream that receives the serialized data.
     *
     * \throws NotSupportedException The serialization type is not supported.
     *
     * \since ids_peak_icv 1.0
     */
    void Write(const peak::common::serialization::IArchive& archive, std::ostream& stream) override;

private:
    SerializationType m_type;
};

inline Serializer::Serializer(peak::icv::SerializationType type)
    : m_type{ type }
{}

inline void Serializer::Write(const peak::common::serialization::IArchive& archive, std::ostream& stream)
{
    std::vector<char> buffer;

    auto* archiveHandle = [&archive]() {
        try
        {
            const auto& realArchive = dynamic_cast<const Archive&>(archive);
            return peak::common::detail::BackendAccessor<Archive>::BackendHandle(realArchive);
        }
        catch (std::bad_cast&)
        {
            throw InternalErrorException("The given archive is invalid. This should not happen.", PEAK_ICV_STATUS_INTERNAL_ERROR);
        }
    }();

    size_t size{};
    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_ToString_GetSizeInBytes(
            archiveHandle, helper::MapSerializationTypeToApi(m_type), &size);
    });

    buffer.resize(size);

    detail::ExecuteAndMapReturnCodes([&] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_ToString(
            archiveHandle, helper::MapSerializationTypeToApi(m_type), buffer.data(), &size);
    });

    stream.write(buffer.data(), static_cast<std::streamsize>(buffer.size() - 1));
}

} /* namespace icv */
} /* namespace peak */
