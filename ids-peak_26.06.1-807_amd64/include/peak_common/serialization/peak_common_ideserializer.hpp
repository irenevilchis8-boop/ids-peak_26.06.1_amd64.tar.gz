/*!
 * \file    peak_common_ideserializer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-27
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/serialization/peak_common_iarchive.hpp>

#include <istream>
#include <memory>

namespace peak
{
namespace common
{
namespace serialization
{

/*!
 * \ingroup ids_peak_common_serialization
 * \brief Interface for deserializing structured data from an input stream into an archive.
 *
 * \since ids_peak_common 1.0
 */
class IDeserializer
{
public:
    virtual ~IDeserializer() = default;

    /*!
     * \brief Deserializes data from the specified input stream into an archive.
     *
     * This function reads raw data from the provided `std::istream` and converts it
     * into a structured `IArchive` object. The stream must be open, valid, and ready
     * for reading before this function is called.
     *
     * \param stream The input stream to read from.
     *               It should point to the beginning of a valid archive format.
     *
     * \return A shared pointer to the deserialized IArchive.
     */
    PEAK_COMMON_NO_DISCARD virtual std::shared_ptr<IArchive> Read(std::istream& stream) = 0;
};

} // namespace serialization
} // namespace common 
} // namespace peak
