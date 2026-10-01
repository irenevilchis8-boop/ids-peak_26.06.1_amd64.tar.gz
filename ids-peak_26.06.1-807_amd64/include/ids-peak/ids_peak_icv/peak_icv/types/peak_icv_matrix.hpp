/*!
 * \file    peak_icv_matrix.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/types/peak_icv_array_2d.hpp>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_types
 *
 * \brief A class template for a two-dimensional matrix.
 *
 * This class allows for the storage and manipulation of a 2D matrix of a specified type, number of rows, and columns.
 *
 * \tparam Type The type of the elements stored in the matrix.
 * \tparam rows The number of rows in the matrix.
 * \tparam columns The number of columns in the matrix.
 *
 * \since ids_peak_icv 1.0
 */
template <typename Type, std::size_t rows, std::size_t columns>
class Matrix : public Array2D<Type, rows, columns>
{
public:
    using Array2D<Type, rows, columns>::Array2D; // NOLINT

    /*!
     * \brief Creates and returns an identity matrix.
     *
     * \since ids_peak_icv 1.0
     */
    static Matrix Identity()
    {
        return Matrix::Diagonal(static_cast<Type>(1));
    }

    /*!
     * \brief Constructs a uniform diagonal matrix.
     *
     * \param value The scalar value to be placed along the diagonal.
     *
     * \returns A \c Matrix with \p value on the diagonal and zeros elsewhere.
     *
     * \since ids_peak_icv 1.0
     */
    static Matrix Diagonal(const Type& value)
    {
        static_assert(rows == columns, "Matrix must be symmetrical!");

        Matrix result;

        for (size_t i = 0; i < rows; ++i)
        {
            result.At(i, i) = static_cast<Type>(value);
        }

        return result;
    }
};

} /* namespace icv */
} /* namespace peak */
