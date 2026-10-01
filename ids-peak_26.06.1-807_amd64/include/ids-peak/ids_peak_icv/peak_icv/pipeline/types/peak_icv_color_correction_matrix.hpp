/*!
 * \file    peak_icv_color_correction_matrix.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-07-09
 * \since   1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_math.hpp>
#include <peak_common/serialization/peak_common_iserializable.hpp>
#include <peak_icv/types/peak_icv_matrix.hpp>

namespace peak
{
namespace pipeline
{

/*!
 * \ingroup ids_peak_icv_cpp_pipeline_types
 * \brief Color correction matrix.
 *
 * A color correction matrix is a 3×3 transformation matrix used to adjust RGB color values.
 * It is typically used to convert colors from a camera sensor’s native RGB space to a standard color space,
 * or to perform color balancing and correction.
 *
 * The color correction matrix is represented as a 3×3 float array:
 *
 * |        |        |        |
 * |--------|--------|--------|
 * | m_00   | m_01   | m_02   |
 * | m_10   | m_11   | m_12   |
 * | m_20   | m_21   | m_22   |
 *
 * \see \ref features::ColorCorrectionFeature for more information.
 *
 * \since ids_peak_icv 1.0
 */
class ColorCorrectionMatrix
    : public peak::icv::Matrix<float, 3, 3>
    , public peak::common::serialization::ISerializable
{
public:
    using peak::icv::Matrix<float, 3, 3>::Matrix;

    /*!
     * \brief Creates an instance of class ColorCorrectionMatrix.
     *
     * \since ids_peak_icv 1.0
     */
    ColorCorrectionMatrix() = default;

    /*!
     * \brief Creates an instance of class ColorCorrectionMatrix with \p data.
     *
     * \param data The initial data for the color correction matrix.
     *
     * \since ids_peak_icv 1.0
     */
    explicit ColorCorrectionMatrix(const float (&data)[3][3]) // NOLINT
        : Matrix(data)
    {}

    /*!
     * \brief Creates an instance of class ColorCorrectionMatrix with \p data.
     *
     * \param matrix The initial matrix for the color correction matrix.
     *
     * \since ids_peak_icv 1.0
     */
    ColorCorrectionMatrix(Matrix<float, 3, 3> matrix) // NOLINT
        : Matrix(std::move(matrix))
    {}

    /*!
     * \brief Creates an instance of class ColorCorrectionMatrix.
     *
     * \param name The name of the color correction matrix, used for serialization.
     * \param data The initial data for the color correction matrix.
     *
     * \since ids_peak_icv 1.0
     */
    ColorCorrectionMatrix(std::string name, const float (&data)[3][3]) // NOLINT
        : Matrix(data)
        , m_name{ std::move(name) }
    {}

    /*!
     * \brief Creates an instance of class ColorCorrectionMatrix.
     *
     * \param name The name of the color correction matrix, used for serialization.
     * \param matrix The initial matrix for the color correction matrix.
     *
     * \since ids_peak_icv 1.0
     */
    ColorCorrectionMatrix(std::string name, Matrix<float, 3, 3> matrix) // NOLINT
        : Matrix(std::move(matrix))
        , m_name{ std::move(name) }
    {}

    /*!
     * \brief Serializes the object's internal state into the provided archive.
     *
     * This function populates the given \p archive with all parameters required to  fully represent the current state of the object.
     * It ensures that the object can be reconstructed or transmitted accurately by saving all relevant data members
     * in a consistent and structured format.
     *
     * \param archive The target archive that will store the serialized parameters.
     *
     * \since ids_peak_icv 1.0
     */
    void Serialize(peak::common::serialization::IArchive& archive) const override;


    /*!
     * \brief Restores the object's state from the provided archive.
     *
     * This function reads and applies all necessary parameters from the given \p archive to reconstruct the internal state of the object.
     * It ensures that the object is restored to a valid and consistent state.
     *
     * \param archive The source archive containing the serialized parameters.
     *
     * \since ids_peak_icv 1.0
     */
    void Deserialize(const peak::common::serialization::IArchive& archive) override;

    bool operator==(const ColorCorrectionMatrix& other) const;

private:
    std::string m_name;
};

inline void ColorCorrectionMatrix::Serialize(peak::common::serialization::IArchive& archive) const
{
    std::vector<double> doubleValues(9);
    std::transform(cbegin(), cend(), doubleValues.begin(), [&](const float v) {
        return static_cast<double>(v);
    });
    archive.SetDoubleArray(m_name, doubleValues);
}

inline void ColorCorrectionMatrix::Deserialize(const peak::common::serialization::IArchive& archive)
{
    const auto doubleValues = archive.GetDoubleArray(m_name);
    std::transform(doubleValues.cbegin(), doubleValues.cend(), begin(), [&](const double v) {
        return static_cast<float>(v);
    });
}

inline bool ColorCorrectionMatrix::operator==(const ColorCorrectionMatrix& other) const
{
    return std::equal(cbegin(), cend(), other.cbegin(), [](float a, float b) {
        return peak::common::detail::AreAlmostEqual(a, b, 6);
    });
}

/*!
 * \brief Converts a ColorCorrectionMatrix to its string representation.
 *
 * \param matrix The color correction matrix to convert.
 * \return A string representation of the matrix.
 * \since ids_peak_icv 1.0
 */
PEAK_COMMON_NO_DISCARD inline std::string ToString(const ColorCorrectionMatrix& matrix)
{
    std::stringstream ss;
    ss << matrix;
    return ss.str();
}

} // namespace pipeline 
} // namespace peak
