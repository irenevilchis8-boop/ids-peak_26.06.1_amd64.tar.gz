/*!
 * \file    peak_icv_drawable.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-09-12
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

#include <peak_icv/painting/peak_icv_drawing_options.hpp>

namespace peak
{
namespace icv
{
class Image;

class Painter;

/*!
 * \ingroup ids_peak_icv_cpp_types
 * \brief Base class for all drawables.
 *
 * \since ids_peak_icv 1.1
 */
class IDrawable
{
protected:
    /*!
     * \brief Base class destructor
     *
     * \since ids_peak_icv 1.1
     */
    virtual ~IDrawable() = default;

    /*!
     * \brief Base class draw function
     *
     * \since ids_peak_icv 1.1
     */
    virtual void Draw(Image& image, const detail::DrawingOptions& options) const = 0;

private:
    friend Painter;
};

} /* namespace icv */
} /* namespace peak */
