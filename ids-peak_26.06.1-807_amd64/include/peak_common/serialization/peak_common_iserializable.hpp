/*!
 * \file    peak_common_iserializable.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-27
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/serialization/peak_common_iarchive.hpp>

namespace peak
{
namespace common
{
namespace serialization
{
/*!
 * \ingroup ids_peak_common_serialization
 * \brief Interface for objects that can be serialized to and deserialized from an archive.
 *
 * Classes implementing this interface provide mechanisms to convert their internal state
 * into a portable form using an \ref peak::common::serialization::IArchive, and restore it later from the same archive.
 *
 * \since ids_peak_common 1.0
 */
class ISerializable
{
public:
    virtual ~ISerializable() = default;

    /*!
     * \brief Serializes the current object into the provided archive.
     *
     * This method writes the internal state of the object into the given
     * \ref peak::common::serialization::IArchive so that it can later be reconstructed using Deserialize().
     *
     * \param archive The archive to which the object's data will be written.
     */
    virtual void Serialize(IArchive& archive) const = 0;

    /*!
     * \brief Deserializes the object's state from the provided archive.
     *
     * This method reads data from the given \ref peak::common::serialization::IArchive and reconstructs
     * the internal state of the object.
     *
     * \param archive The archive from which to read the object's data.
     */
    virtual void Deserialize(const IArchive& archive) = 0;
};

} // namespace serialization
} // namespace common 
} // namespace peak
