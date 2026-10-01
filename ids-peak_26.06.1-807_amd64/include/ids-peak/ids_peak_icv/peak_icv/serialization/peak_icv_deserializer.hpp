/*!
 * \file    peak_icv_deserializer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-19
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <istream>

#include <peak_common/serialization/peak_common_ideserializer.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/serialization/detail/peak_icv_serialization_helper.hpp>
#include <peak_icv/serialization/peak_icv_archive.hpp>
#include <peak_icv/serialization/peak_icv_deserializer.hpp>
#include <peak_icv/serialization/peak_icv_serialization_types.hpp>

namespace peak
{
namespace icv
{
/*!
 * \ingroup ids_peak_icv_cpp_serialization
 *
 * \brief
 *   Deserializer for reading serialized data
 *   and converting it into an `IArchive` object.
 *
 * This class provides functionality to read data
 * from a supported serialization format
 * (currently, only JSON)
 * and reconstruct it as an `IArchive` object.
 *
 * **Example**
 *
 * \code{.cpp}
 * std::ifstream file("archive.json");
 * peak::icv::Deserializer deserializer{};
 * auto archive = deserializer.Read(file);
 *
 * auto id = archive->GetInt("id");
 * auto name = archive->GetString("name");
 * \endcode
 *
 * It inherits from `peak::common::serialization::IDeserializer`
 * and implements the deserialization operations.
 *
 * \note
 *   This class is non-copyable
 *   but supports move semantics.
 *
 * \see peak::common::serialization::IDeserializer
 * \see peak::common::serialization::IArchive
 * \see SerializationType
 *
 * \since ids_peak_icv 1.0
 */
class Deserializer : public peak::common::serialization::IDeserializer
{
public:
    /*!
     * \brief
     *   Reads serialized data from the specified stream
     *   and deserializes it into an archive.
     *
     * \param stream The stream to read serialized data from.
     *
     * \return A shared pointer to an `IArchive` object
     *         containing the deserialized data.
     *
     * \throws NotSupportedException The serialization type is not supported.
     * \throws CorruptedException    The stream contains invalid or corrupted data.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD std::shared_ptr<peak::common::serialization::IArchive> Read(std::istream& stream) override;
};

inline std::shared_ptr<peak::common::serialization::IArchive> Deserializer::Read(std::istream& stream)
{
    std::string buffer((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    peak_icv_archive_handle archiveHandle{};

    detail::ExecuteAndMapReturnCodes([&buffer, &archiveHandle] {
        return PEAK_ICV_C_ABI_PREFIX peak_icv_Archive_CreateFromString(
            &archiveHandle, peak_icv_serialization_type::PEAK_ICV_SERIALIZATION_TYPE_JSON, buffer.data());
    });

    return std::make_shared<Archive>(peak::common::detail::BackendAccessor<Archive>::CreateInstance(archiveHandle));
}

} /* namespace icv */
} /* namespace peak */
