/*!
* \file    peak_ipl_color_correction_factors.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-03-20
 * \since   1.16
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_ipl/backend/peak_ipl_attribute_defines.h>
#include <peak_ipl/exception/peak_ipl_exception.hpp>

#include <array>
#include <type_traits>
#include <limits>
#include <cmath>

/*!
 * \namespace peak::ipl
 * \brief The "peak::ipl" namespace contains the whole image processing library.
 */

namespace peak
{
namespace ipl
{
/*!
 * \ingroup ids_peak_ipl_types
 * \brief The Factors of the Color Correction Matrix.
 */
struct ColorCorrectionFactors
{
    /*! \brief Constructor for a new ColorCorrectionFactors instance
     *
     * Creates a new ColorCorrectionFactors instance.
     *
     * The matrix is row-wise sorted:
     *
     * |    |    |    |
     * | -- | -- | -- |
     * | RR | GR | BR |
     * | RG | GG | BG |
     * | RB | GB | BB |
     *
     * \param[in] facRR Red-Red Factor.
     * \param[in] facGR Green-Red Factor.
     * \param[in] facBR Blue-Red Factor.
     * \param[in] facRG Red-Green Factor.
     * \param[in] facGG Green-Green Factor.
     * \param[in] facBG Blue-Green Factor.
     * \param[in] facRB Red-Blue Factor.
     * \param[in] facGB Green-Blue Factor.
     * \param[in] facBB Blue-Blue Factor.
     *
     * \since 1.0
     */
    constexpr ColorCorrectionFactors(float facRR, float facGR, float facBR, float facRG, float facGG, float facBG,
        float facRB, float facGB, float facBB)
        : factorRR(facRR)
        , factorGR(facGR)
        , factorBR(facBR)
        , factorRG(facRG)
        , factorGG(facGG)
        , factorBG(facBG)
        , factorRB(facRB)
        , factorGB(facGB)
        , factorBB(facBB)
    {}

    /*! \brief Constructor for a new ColorCorrectionFactors instance
     *
     * Creates a new ColorCorrectionFactors instance with an array.
     * The values are expected left to right and top to bottom.
     *
     * The matrix is row-wise sorted:
     *
     * |        |        |        |
     * | ------ | ------ | ------ |
     * | RR (0) | GR (1) | BR (2) |
     * | RG (3) | GG (4) | BG (5) |
     * | RB (6) | GB (7) | BB (8) |
     *
     * \param[in] factors The factors.
     *
     * \since 1.16
     */
    constexpr explicit ColorCorrectionFactors(const std::array<float, 9>& factors)
        : factorRR(factors[0])
        , factorGR(factors[1])
        , factorBR(factors[2])
        , factorRG(factors[3])
        , factorGG(factors[4])
        , factorBG(factors[5])
        , factorRB(factors[6])
        , factorGB(factors[7])
        , factorBB(factors[8])
    {}

    /*! \brief Constructor for a new ColorCorrectionFactors instance
     *
     * Creates a new ColorCorrectionFactors instance. The Factors are initialized to zero.
     *
     * \since 1.0
     */
    constexpr ColorCorrectionFactors() = default;

    /*! \brief Destructor for the ColorCorrectionFactors instance
     *
     * Destroys a ColorCorrectionFactors instance.
     *
     * \since 1.0
     */
    ~ColorCorrectionFactors() = default;

    /*! \brief Copy Constructor for a new ColorCorrectionFactors instance
     *
     * Creates a new ColorCorrectionFactors instance. The Factors are copied from \p other
     *
     * \param[in] o The other instance to copy the factors from.
     *
     * \since 1.0
     */
    ColorCorrectionFactors(ColorCorrectionFactors&& o) = default;

    /*! \brief Move constructor for ColorCorrectionFactors instance
     *
     * Moves the instance from \p other to this. Afterward \p other is invalid.
     *
     * \param[in] o The other instance to move the factors from.
     *
     * \since 1.0
     */
    ColorCorrectionFactors(const ColorCorrectionFactors& o) = default;

    /*! \brief Copy assigment for ColorCorrectionFactors instance
     *
     * Copies the Factors from \p other to this instance.
     *
     * \param[in] o The other instance to copy the factors from.
     *
     * \since 1.0
     */
    ColorCorrectionFactors& operator=(const ColorCorrectionFactors& o) = default;

    /*! \brief Move assignment for ColorCorrectionFactors instance
     *
     * Moves the factors from \p other to this.
     *
     * \param[in] o The other instance to move the factors from.
     *
     * \since 1.0
     */
    ColorCorrectionFactors& operator=(ColorCorrectionFactors&& o) = default;

    /*! \brief Compare ColorCorrectionFactors
     *
     * Compares the factors from \p other to this instance
     *
     * \param[in] other The other instance to compare.
     *
     * \returns True if equal, false otherwise.
     *
     * \since 1.0
     */
    PEAK_IPL_NO_DISCARD constexpr bool operator==(const ColorCorrectionFactors& other) const
    {
        return (isEqual(factorRR, other.factorRR) && isEqual(factorGR, other.factorGR)
            && isEqual(factorBR, other.factorBR) && isEqual(factorRG, other.factorRG)
            && isEqual(factorGG, other.factorGG) && isEqual(factorBG, other.factorBG)
            && isEqual(factorRB, other.factorRB) && isEqual(factorGB, other.factorGB)
            && isEqual(factorBB, other.factorBB));
    }

    /*! \brief Create an identity matrix
     *
     * This will return a ColorCorrectionFactors matrix with diagonal all 1 and all other 0.
     *
     * \returns The identity matrix.
     *
     * \since 1.16
     */
    PEAK_IPL_NO_DISCARD static constexpr ColorCorrectionFactors Identity()
    {
        return { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    }

    /*! \brief Returns the ColorCorrectionFactors as an array
     *
     * \returns The factors as a std::array.
     *
     * \since 1.16
     */
    PEAK_IPL_NO_DISCARD constexpr std::array<float,9> AsArray() const
    {
        return { factorRR, factorGR, factorBR, factorRG, factorGG, factorBG, factorRB, factorGB, factorBB };
    }

    float factorRR{}; //!< Red-Red Factor.
    float factorGR{}; //!< Green-Red Factor.
    float factorBR{}; //!< Blue-Red Factor.
    float factorRG{}; //!< Red-Green Factor.
    float factorGG{}; //!< Green-Green Factor.
    float factorBG{}; //!< Blue-Green Factor.
    float factorRB{}; //!< Red-Blue Factor.
    float factorGB{}; //!< Green-Blue Factor.
    float factorBB{}; //!< Blue-Blue Factor.

private:
    template <class T>
    static constexpr T Absolute(const T& x) noexcept
    {
        return x < 0 ? -x : x;
    }

    template <class T>
    static constexpr typename std::enable_if<std::numeric_limits<T>::is_iec559, bool>::type isEqual(T x, T y)
    {
        return Absolute(x - y) <= std::numeric_limits<T>::epsilon();
    }

    template <class T>
    static constexpr typename std::enable_if<std::is_integral<T>::value, bool>::type isEqual(T x, T y)
    {
        return x == y;
    }
};

} /* namespace ipl */
} /* namespace peak */
