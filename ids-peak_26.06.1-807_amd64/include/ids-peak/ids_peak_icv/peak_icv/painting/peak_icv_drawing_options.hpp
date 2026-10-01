/*!
 * \file    peak_icv_drawing_options.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common/detail/peak_common_backend_accessor.hpp>

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/painting/peak_icv_color.hpp>
#include <peak_icv/painting/peak_icv_opacity.hpp>
#include <peak_icv_c/painting/peak_icv_color.h>
#include <peak_icv_c/painting/peak_icv_painter.h>
#include <peak_icv_c/types/peak_icv_simple_types.h>

namespace peak
{
namespace icv
{
namespace detail
{

/*!
 * \ingroup ids_peak_icv_cpp_painting
 *
 * \brief
 *
 * \since ids_peak_icv 1.1
 */
class DrawingOptions
{
public:
    /*!
     * \brief Default Drawing options are red with 100% opacity.
     *
     * \since ids_peak_icv 1.1
     */
    DrawingOptions() = default;

    /*!
     * \brief Get the color for drawing.
     *
     * \return The color
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD constexpr Color GetColor() const;

    /*!
     * \brief Get the opacity for drawing.
     *
     * \return The opacity
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Opacity GetOpacity() const;

    /*!
     * \brief Set the color for drawing.
     *
     * \since ids_peak_icv 1.1
     */
    void SetColor(const Color& color);

    /*!
     * \brief Set the opacity for drawing.
     *
     * \since ids_peak_icv 1.1
     */
    void SetOpacity(const Opacity& opacity);

    bool operator==(const DrawingOptions& other) const;

private:
    friend peak::common::detail::BackendAccessor<DrawingOptions>;

    explicit operator peak_icv_drawing_options() const;

    Color m_color{ ColorConstant::Red };
    Opacity m_opacity{ 100 };
    size_t m_reserved{};
};

constexpr Color DrawingOptions::GetColor() const
{
    return m_color;
}

inline Opacity DrawingOptions::GetOpacity() const
{
    return m_opacity;
}

inline void DrawingOptions::SetColor(const Color& color)
{
    m_color = color;
}

inline void DrawingOptions::SetOpacity(const Opacity& opacity)
{
    m_opacity = opacity;
}

inline DrawingOptions::operator peak_icv_drawing_options() const // NOLINT
{
    return { m_color.GetRaw(), m_opacity.GetValue(), m_reserved };
}

inline bool DrawingOptions::operator==(const DrawingOptions& other) const
{
    return m_color == other.m_color && m_opacity.GetValue() == other.m_opacity.GetValue();
}

} // namespace detail
} /* namespace icv */
} /* namespace peak */
