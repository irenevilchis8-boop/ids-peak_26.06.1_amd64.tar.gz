/*!
 * \file    peak_common_iserializer.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-27
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <ostream>

#include <peak_common/serialization/peak_common_iarchive.hpp>

namespace peak
{
namespace common
{
namespace serialization
{

/*!
 * \ingroup ids_peak_common_serialization
 * \brief Interface for serializing data to an output stream.
 *
 * This interface defines a contract for writing structured or binary data
 * into an output stream.
 *
 * Implementations of this interface are responsible for formatting and
 * writing the contents of one or more archives to a given output destination.
 *
 * \since ids_peak_common 1.0
 */
class ISerializer
{
public:
    virtual ~ISerializer() = default;

    /*!
     * \brief Serializes data and writes it to the specified output stream.
     *
     * \param archive The archive which will be written to file.
     * \param stream The output stream to which serialized data will be written.
     */
    virtual void Write(const IArchive& archive, std::ostream& stream) = 0;
};

} // namespace serialization
} // namespace common 
} // namespace peak
