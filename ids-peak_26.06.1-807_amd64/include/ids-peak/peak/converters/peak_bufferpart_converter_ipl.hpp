/*!
* \file    peak_bufferpart_converter_ipl.hpp
*
* \author  IDS Imaging Development Systems GmbH
* \date    2024-04-08
* \since   1.8.0
*
* Copyright (c) 2024 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
*/

#pragma once


#include <peak_ipl/peak_ipl.hpp>
#include <peak/data_stream/peak_data_stream.hpp>
#include <peak/device/peak_device.hpp>
#include <peak/peak_buffer_converter.hpp>
#include <peak/image_view/peak_image_view.hpp>
#include <peak/image_view/peak_image_view_impl.hpp>

#include <cassert>


namespace peak
{

/*!
 *\ingroup ids_peak_acquisition
* \brief Converts a core::BufferPart into a peak::ipl::Image.
*
* This creates a peak::ipl::Image as a shallow copy of the buffer (i.e. using the same memory).
*
* \param[in] part The buffer part to convert
* \returns The buffer part converted to an Image.
* \remark Remember that the buffer part's memory is only under your control until you re-queue the buffer.
*
* \since 1.8
*
* \note To use this method, this file needs to be included explicitly:
* \code
* #include <peak/converters/peak_bufferpart_converter_ipl.hpp>
* \endcode
*/
template <>
inline peak::ipl::Image BufferPartTo(const std::shared_ptr<peak::core::BufferPart>& part)
{
    // Using constructor rather than buffer.ToImageView() to include the nullptr check.
    auto imageView = core::ImageView(part);

    return peak::ipl::Image(imageView);
}

} /* namespace peak */
