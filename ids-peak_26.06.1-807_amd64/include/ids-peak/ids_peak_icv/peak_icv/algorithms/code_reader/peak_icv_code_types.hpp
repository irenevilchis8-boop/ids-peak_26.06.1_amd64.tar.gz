/*!
 * \file    peak_icv_code_types.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-12-22
 * \since   1.2
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once
#include <peak_icv_c/algorithms/code_reader/peak_icv_code_reader.h>

namespace peak
{
namespace icv
{
namespace experimental
{

/*!
 * \ingroup ids_peak_icv_cpp_code_reader
 *
 * \brief Enum that holds the possible code types for detection and identification.
 *
 * \since ids_peak_icv 1.2
 * \warning This function is still in development and not released.
 */
enum class CodeType
{
    /*!
     * \brief A Data Matrix code is a two-dimensional code, that may store numeric data or characters.
     *
     * \since ids_peak_icv 1.2
     * \warning This function is still in development and not released.
     */
    DataMatrix = peak_icv_code_type::DataMatrix
};

} // namespace experimental
} // namespace icv 
} // namespace peak
