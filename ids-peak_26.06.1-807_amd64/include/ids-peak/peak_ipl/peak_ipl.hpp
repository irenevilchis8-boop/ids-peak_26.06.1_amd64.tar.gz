/*!
 * \file    peak_ipl.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2019-05-01
 * \since   1.0
 *
 * Copyright (c) 2019 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

/*!
 * \defgroup ids_peak_ipl IDS peak IPL
 *
 * \brief IDS peak IPL (Image Processing Library) is an object-oriented
 *        C++ library that provides special functionality for processing image data.
 */

/*!
 * \defgroup ids_peak_ipl_cpp C++
 * \ingroup ids_peak_ipl
 *
 * \brief The C++ interface for the IDS peak IPL library.
 */

/*!
 * \defgroup ids_peak_ipl_library Library
 * \ingroup ids_peak_ipl_cpp
 *
 * \brief Library level functions and types.
 */

/*!
 * \defgroup ids_peak_ipl_exceptions Exceptions
 * \ingroup ids_peak_ipl_cpp
 *
 * \brief Custom exceptions used throughout the library.
 */

/*!
 * \defgroup ids_peak_ipl_image Image
 * \ingroup ids_peak_ipl_cpp
 *
 * \brief Core classes for handling images and pixel data.
 *
 * Provides functionality for representing images, defining pixel formats, 
 * accessing pixel lines, and storing histogram information.
 */

/*!
 * \defgroup ids_peak_ipl_io IO
 * \ingroup ids_peak_ipl_cpp
 *
 * \brief Classes for reading, writing, and encoding images and videos.
 *
 * Includes tools for file-based image I/O, video creation, and media encoding
 * and container management.
 */

/*!
 * \defgroup ids_peak_ipl_algorithm Algorithms
 * \ingroup ids_peak_ipl_cpp
 *
 * \brief Image processing and analysis algorithms.
 *
 * Provides a variety of algorithms for image correction, enhancement,
 * transformation, and analysis, including color adjustment, sharpening,
 * geometric operations, and pixel-level processing.
 */

/*!
 * \defgroup ids_peak_ipl_types Types
 * \ingroup ids_peak_ipl_cpp
 *
 * \brief General-purpose types and interfaces used throughout the library.
 */

#include <peak_ipl/types/peak_ipl_image.hpp>
#include <peak_ipl/types/peak_ipl_pixel_format.hpp>
#include <peak_ipl/types/peak_ipl_pixel_line.hpp>
#include <peak_ipl/types/peak_ipl_simple_types.hpp>
#include <peak_ipl/library/peak_ipl_library.hpp>

#include <peak_ipl/algorithm/peak_ipl_binning.hpp>
#include <peak_ipl/algorithm/peak_ipl_color_corrector.hpp>
#include <peak_ipl/algorithm/peak_ipl_decimation.hpp>
#include <peak_ipl/algorithm/peak_ipl_gain.hpp>
#include <peak_ipl/algorithm/peak_ipl_gamma_corrector.hpp>
#include <peak_ipl/algorithm/peak_ipl_histogram.hpp>
#include <peak_ipl/algorithm/peak_ipl_hotpixel_correction.hpp>
#include <peak_ipl/algorithm/peak_ipl_image_converter.hpp>
#include <peak_ipl/algorithm/peak_ipl_lut.hpp>
#include <peak_ipl/algorithm/peak_ipl_image_transformer.hpp>
#include <peak_ipl/algorithm/peak_ipl_sharpness.hpp>
#include <peak_ipl/algorithm/peak_ipl_edge_enhancement.hpp>
#include <peak_ipl/algorithm/peak_ipl_chromatic_adaption.hpp>

#include <peak_ipl/io/peak_ipl_image_reader.hpp>
#include <peak_ipl/io/peak_ipl_image_writer.hpp>
#include <peak_ipl/io/peak_ipl_video_writer.hpp>
