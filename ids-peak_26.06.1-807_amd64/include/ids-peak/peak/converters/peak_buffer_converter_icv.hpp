/*!
 * \file    peak_buffer_converter_icv.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-06-06
 * \since   1.12
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once


#include <peak_icv/peak_icv.hpp>
#include <peak/image_view/peak_image_view.hpp>
#include <peak/image_view/peak_image_view_impl.hpp>


namespace peak
{

/*!
 *\ingroup ids_peak_acquisition
 * \brief Converts a core::Buffer into a peak::icv::Image.
 *
 * This creates a peak::icv::Image as a shallow copy of the buffer (i.e. using the same memory).
 *
 * \param[in] buffer The buffer to convert
 * \returns The buffer converted to an Image.
 * \remark Remember that the buffer's memory is only under your control until you re-queue the buffer.
 *
 * \since 1.12
 *
 * \note To use this method, this file needs to be included explicitly:
 * \code
 * #include <peak/converters/peak_buffer_converter_icv.hpp>
 * \endcode
 *
 */
template <>
inline peak::icv::Image BufferTo<peak::icv::Image>(const std::shared_ptr<peak::core::Buffer>& buffer)
{
    // Using constructor rather than buffer.ToImageView() to include the nullptr check.
    return peak::icv::Image(core::ImageView(buffer));
}

} /* namespace peak */
