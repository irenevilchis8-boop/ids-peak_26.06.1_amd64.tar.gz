/*!
 * \file    peak_icv_painter.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_icv/exceptions/detail/peak_icv_exception_helpers.hpp>
#include <peak_icv/painting/peak_icv_color.hpp>
#include <peak_icv/painting/peak_icv_drawable.hpp>
#include <peak_icv/painting/peak_icv_drawing_options.hpp>
#include <peak_icv_c/painting/peak_icv_painter.h>

namespace peak
{
namespace icv
{

/*!
 * \ingroup ids_peak_icv_cpp_painting
 *
 * \brief Provides functionality for painting drawable objects on images.
 *
 * The Painter enables rendering of objects
 * derived from IDrawable onto images.
 * Supported image formats are RGB8, BGR8, RGBa8, and BGRa8.
 *
 * You can configure drawing properties
 * such as color and opacity
 * using SetColor() and SetOpacity().
 * If not explicitly configured,
 * default values from \ref detail::DrawingOptions are applied.
 *
 * \snippet{trimleft} painting.cpp painting_set_and_draw_cpp
 *
 * \since ids_peak_icv 1.1
 */
class Painter
{
public:
    /*!
     * \brief Constructs a Painter with the target image.
     *
     * \param image The image all painting operations are performed on.
     *
     * \since ids_peak_icv 1.1
     */
    explicit Painter(Image& image);

    /*!
     * \brief Sets the color for painting.
     *
     * Refer to Color for more information on color configuration.
     *
     * \param color The color to be set.
     *
     * \since ids_peak_icv 1.1
     */
    void SetColor(const Color& color);

    /*!
     * \brief Sets the opacity for painting.
     *
     * Refer to Opacity for more information on opacity configuration.
     *
     * \param opacity  The opacity to be set.
     *
     * \since ids_peak_icv 1.1
     */
    void SetOpacity(const Opacity& opacity);

    /*!
     * \return The color for painting.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Color GetColor() const;

    /*!
     * \return The opacity for painting.
     *
     * \since ids_peak_icv 1.1
     */
    PEAK_COMMON_NO_DISCARD Opacity GetOpacity() const;

    /*!
     * \brief Draws the specified drawable object onto the image.
     *
     * The following objects can be drawn:
     * - \ref Region_painting "Region"
     *
     * Refer to the documentation of the specific drawable for more details.
     *
     * \param drawable The object to be drawn.
     *
     * \since ids_peak_icv 1.1
     */
    void Draw(const IDrawable& drawable) const;

private:
    detail::DrawingOptions m_drawingOptions;
    Image& m_image;
};

inline void Painter::SetColor(const Color& color)
{
    m_drawingOptions.SetColor(color);
}

inline void Painter::SetOpacity(const Opacity& opacity)
{
    m_drawingOptions.SetOpacity(opacity);
}

inline Color Painter::GetColor() const
{
    return m_drawingOptions.GetColor();
}

inline Opacity Painter::GetOpacity() const
{
    return m_drawingOptions.GetOpacity();
}

inline Painter::Painter(Image& image)
    : m_image(image)
{}

inline void Painter::Draw(const IDrawable& drawable) const
{
    drawable.Draw(m_image, m_drawingOptions);
}

} /* namespace icv */
} /* namespace peak */
