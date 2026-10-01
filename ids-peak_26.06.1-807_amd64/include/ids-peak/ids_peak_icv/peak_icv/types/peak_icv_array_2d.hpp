/*!
 * \file    peak_icv_array_2d.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/utils/peak_icv_printable.hpp>
#include <array>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_types
 *
 * \brief A class template for a two-dimensional array.
 *
 * This class allows for the storage and manipulation of a 2D array of a specified type, number of rows, and columns.
 *
 * \tparam Type The type of the elements stored in the array.
 * \tparam rows The number of rows in the array.
 * \tparam columns The number of columns in the array.
 *
 * \since ids_peak_icv 1.0
 */
template <typename Type, std::size_t rows, std::size_t columns>
class Array2D : public detail::IPrintable<Array2D<Type, rows, columns>>
{
public:
    /*!
     * \brief Default constructor that initializes the array with default values.
     *
     * \since ids_peak_icv 1.0
     */
    constexpr Array2D()
        : m_data{}
    {}

    /*!
     * \brief Constructor that initializes the array with a given 2D initializer list.
     *
     * \param initList A 2D array to initialize the Array2D object.
     *
     * \since ids_peak_icv 1.0
     */
    constexpr Array2D(const Type (&initList)[rows][columns]) // NOLINT
    {
        for (std::size_t row = 0; row < rows; ++row)
        {
            for (std::size_t col = 0; col < columns; ++col)
            {
                m_data[row * columns + col] = initList[row][col];
            }
        }
    }

    /*!
     * \brief Constructor that initializes the array with a given 1D data array.
     *
     * \param data A 1D array to initialize the Array2D object.
     *
     * \since ids_peak_icv 1.0
     */
    explicit constexpr Array2D(std::array<Type, rows * columns> data)
        : m_data(std::move(data))
    {}

    /*!
     * \brief Returns a pointer to the underlying data of the array.
     *
     * \return A pointer to the array data.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr const Type* GetData() const
    {
        return m_data.data();
    }

    /*!
     * \brief Accesses the element at the specified row and column.
     *
     * This method throws an exception if the indices are out of range.
     *
     * \param row The row index of the element to access.
     * \param col The column index of the element to access.
     *
     * \return A reference to the element at the specified indices.
     *
     * \throws OutOfRangeException If the row or column index is out of range.
     *
     * \since ids_peak_icv 1.0
     */
    constexpr Type& At(std::size_t row, std::size_t col)
    {
        if (row >= rows || col >= columns)
        {
            throw OutOfRangeException("The given row or column index is out of range. Please check the array dimensions.");
        }
        return m_data[row * columns + col];
    }

    /*!
     * \brief Accesses the element at the specified row and column (const version).
     *
     * This method throws an exception if the indices are out of range.
     *
     * \param row The row index of the element to access.
     * \param col The column index of the element to access.
     *
     * \return A const reference to the element at the specified indices.
     *
     * \throws OutOfRangeException If the row or column index is out of range.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr const Type& At(std::size_t row, std::size_t col) const
    {
        if (row >= rows || col >= columns)
        {
            throw OutOfRangeException("The given row or column index is out of range. Please check the array dimensions.");
        }
        return m_data[row * columns + col];
    }

    /*!
     * \brief Gets the number of rows in the array.
     *
     * \return The number of rows in the array.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr std::size_t GetNumberOfRows() const
    {
        return rows;
    }

    /*!
     * \brief Gets the number of columns in the array.
     *
     * \return The number of columns in the array.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD constexpr std::size_t GetNumberOfColumns() const
    {
        return columns;
    }

    /*!
     * \brief Returns an iterator to the beginning of the array.
     *
     * \return An iterator pointing to the first element of the array.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD auto begin();

    /*!
     * \brief Returns a const iterator to the beginning of the array.
     *
     * \return An iterator pointing to the first element of the array.
     */
    PEAK_COMMON_NO_DISCARD auto cbegin() const;

    /*!
     * \brief Returns an iterator to the end of the array.
     *
     * \return An iterator pointing to one past the last element of the array.
     *
     * \since ids_peak_icv 1.0
     */
    PEAK_COMMON_NO_DISCARD auto end();

    /*!
     * \brief Returns a const iterator to the end of the array.
     *
     * \return An iterator pointing to one past the last element of the array.
     */
    PEAK_COMMON_NO_DISCARD auto cend() const;

protected:
    void Print(detail::CommaSeperatedStream& stream) const override
    {
        for (std::size_t row = 0; row < rows; ++row)
        {
            for (std::size_t col = 0; col < columns; ++col)
            {
                stream << this->At(row, col);
            }
            if (row < rows - 1)
            {
                stream << std::endl;
            }
        }
    }

private:
    std::array<Type, rows * columns> m_data;
};

template <typename Type, std::size_t rows, std::size_t columns>
auto Array2D<Type, rows, columns>::begin()
{
    return m_data.begin();
}

template <typename T, std::size_t rows, std::size_t columns>
auto Array2D<T, rows, columns>::cbegin() const
{
    return m_data.cbegin();
}

template <typename Type, std::size_t rows, std::size_t columns>
auto Array2D<Type, rows, columns>::end()
{
    return m_data.end();
}

template <typename T, std::size_t rows, std::size_t columns>
auto Array2D<T, rows, columns>::cend() const
{
    return m_data.cend();
}

} /* namespace icv */
} /* namespace peak */
