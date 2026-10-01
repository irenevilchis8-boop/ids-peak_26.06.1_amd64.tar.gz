/*!
 * \file    peak_icv_opacity.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/exceptions/peak_icv_exception.hpp>
#include <peak_icv/utils/peak_icv_printable.hpp>

#include <type_traits>
#include <cstdint>
#include <string>

namespace peak
{
namespace icv
{
/*!
 * \ingroup ids_peak_icv_cpp_painting
 *
 * \brief Holds an opacity value
 *        representing the transparency level of an object or pixel.
 *
 * Opacity ranges from 0 to 100,
 * where 0 indicates complete transparency
 * and 100 indicates complete opacity.
 * Intermediate values represent varying levels of transparency.
 *
 * \since ids_peak_icv 1.1
 */
class Opacity : public detail::IPrintable<Opacity>
{
public:
    /*!
     * \brief Constructs an Opacity object with full opacity (100).
     *
     * \since ids_peak_icv 1.1
     */
    constexpr explicit Opacity()
        : Opacity(maximum)
    {}

    /*!
     * \brief Constructs an Opacity object with the specified value.
     *
     * \param value Opacity value in the range [0, 100]
     *
     * \throws OutOfRangeException if \p value is greater than 100
     *
     * \since ids_peak_icv 1.1
     */
    constexpr explicit Opacity(uint32_t value)
        : m_value(value)
    {
        if (value > maximum)
        {
            throw OutOfRangeException(
                "Opacity value has to be within the range of " + std::to_string(minimum) + " to " + std::to_string(maximum) + ".");
        }
    }

    /*!
     * \return The opacity value.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD constexpr uint32_t GetValue() const
    {
        return m_value;
    }

    /*!
     * \return The minimum allowed opacity value.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD static constexpr uint32_t GetMinimum()
    {
        return minimum;
    }

    /*!
     * \return The maximum allowed opacity value.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD static constexpr uint32_t GetMaximum()
    {
        return maximum;
    }

    /*!
     * \brief
     *
     * \since ids_peak_icv 1.1
     */
    template <typename Opacity
        /// @cond HIDE_FROM_DOXYGEN
        ,
        std::enable_if_t<std::is_integral<Opacity>::value, bool> = true
        /// @endcond
        >
    auto operator==(const Opacity& value) const
    {
        return static_cast<uint32_t>(value) == m_value;
    }

protected:
    void Print(detail::CommaSeperatedStream& stream) const override
    {
        stream << GetValue();
    }

private:
    static constexpr uint32_t minimum = 0;
    static constexpr uint32_t maximum = 100;
    uint32_t m_value{ maximum };
};

} /* namespace icv */
} /* namespace peak */
