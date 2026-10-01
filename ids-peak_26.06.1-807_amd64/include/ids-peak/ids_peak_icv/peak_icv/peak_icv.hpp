/*!
 * \file    peak_icv.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2023-04-04
 * \since   1.0
 *
 * Copyright (c) 2023 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

/*!
 * \defgroup ids_peak_icv_library IDS peak ICV
 *
 * \since ids_peak_icv 1.0
 */

/*!
 * \defgroup ids_peak_icv_cpp C++
 * \ingroup ids_peak_icv_library
 *
 * \brief
 *  The C++ interface for the IDS peak ICV library.
 *
 * # Prerequisites
 *
 * The library requires the use of at least C++14 for the client application.
 *
 * You also need to have the \htmlonly IDS peak IPL \endhtmlonly libraries and their headers.
 *
 * # How to use
 *
 * In order to use \htmlonly IDS peak ICV \endhtmlonly you need to include the interface header file
 * `peak_icv/peak_icv.hpp`
 * and link your application with the `ids_peak_icv` and the `ids_peak_ipl` library.
 *
 * In order to run an application, the shared libraries must be found by the system. \n
 *
 * - _Windows_: copy the deployed shared libraries (dll) into the folder with the applications executable.\n
 * - _Linux_: add the path to the deployed shared libraries (so) to `LD_LIBRARY_PATH`.
 *
 */

/*!
 * \defgroup ids_peak_icv_cpp_algorithms Algorithms
 * \ingroup ids_peak_icv_cpp
 *
 * \brief Image processing algorithms.
 */

/*!
 * \defgroup ids_peak_icv_cpp_calibration Calibration
 * \ingroup ids_peak_icv_cpp_algorithms
 *
 * \brief Geometric camera calibration.
 *
 * Provides tools to determine camera parameters, correct lens distortion, and map image pixels to physical real-world coordinates.
 */

/*!
 * \defgroup ids_peak_icv_cpp_filters Filters
 * \ingroup ids_peak_icv_cpp_algorithms
 * \brief Image filtering.
 */

/*!
 * \defgroup ids_peak_icv_cpp_thresholds Thresholds
 * \ingroup ids_peak_icv_cpp_algorithms
 * \brief Group of functions for thresholding images.
 */

/*!
 * \defgroup ids_peak_icv_cpp_transformations Transformations
 * \ingroup ids_peak_icv_cpp_algorithms
 *
 * \brief Geometric image transformations.
 */

/*!
 * \defgroup ids_peak_icv_cpp_exceptions Exceptions
 * \ingroup ids_peak_icv_cpp
 *
 * \brief Custom exceptions thrown by the library.
 */

/*!
 * \defgroup ids_peak_icv_cpp_experimental Experimental
 * \ingroup ids_peak_icv_cpp
 *
 * \brief Preliminary features under development.
 *
 * Next to its released functions
 * the IDS peak ICV library contains preliminary functions
 * that are being prepared by our software development team but are still in development.
 * These preliminary functions are marked with a warning in the documentation.
 * Preliminary functions are located within an experimental namespace.
 * While these function are functional and can be used for experimenting with new concepts and features, they should be
 * avoided in production environments, as they might be subject to (breaking) changes.
 */

/*!
 * \defgroup ids_peak_icv_cpp_code_reader Code Reader
 * \ingroup ids_peak_icv_cpp_experimental
 *
 * \brief Code detection and decoding.
 */

/*!
 * \defgroup ids_peak_icv_cpp_hdr HDR
 * \ingroup ids_peak_icv_cpp
 * \brief High Dynamic Range (HDR) processing.
 */

/*!
 * \defgroup ids_peak_icv_cpp_tone_mapping Tone mapping
 * \ingroup ids_peak_icv_cpp_hdr
 * \brief Maps High Dynamic Range (HDR) images to displayable Low Dynamic Range (LDR) formats.
 */

/*!
 * \defgroup ids_peak_icv_cpp_io IO
 * \ingroup ids_peak_icv_cpp
 * \brief File input and output.
 *
 * Provides readers and writers
 * for saving and loading library data
 * such as images, point clouds, and calibration results.
 */

/*!
 * \defgroup ids_peak_icv_cpp_pipeline Image Pipeline
 * \ingroup ids_peak_icv_cpp
 *
 * \brief Comprehensive image processing pipeline system for real-time image transformation and enhancement.
 *
 * The Image Pipeline provides a complete, modular framework for processing raw or pre-processed image data
 * through a series of configurable transformation stages. It supports a wide range of image processing
 * operations from basic format conversions to advanced enhancement algorithms.
 *
 * ## Architecture Overview
 *
 * The pipeline follows a modular design with two main component types:
 * - **Modules**: Core processing units that perform specific image transformations
 * - **Features**: High-level interfaces that provide user-friendly access to module functionality
 *
 * ## Processing Flow
 *
 * The pipeline processes images through sequential stages:
 *
 * - **Data Unpacking** - Converts packed sensor formats to standard representations
 * - **Defect Correction** - Removes hot pixels and other sensor artifacts
 * - **Geometric Transformations** - Handles binning, decimation, rotation, and mirroring
 * - **Gain Control** - Applies brightness and white balance adjustments
 * - **Color Processing** - Performs debayering, chromatic adaption, and color space transformations
 * - **Enhancement** - Applies sharpening, gamma correction, and tone mapping
 * - **Format Conversion** - Converts to the desired output pixel format
 *
 * For more information refer to the \ref guide_pipeline Guide.
 */

/*!
 * \defgroup ids_peak_icv_cpp_pipeline_modules Pipeline Modules
 * \ingroup ids_peak_icv_cpp_pipeline
 *
 * \brief Core processing modules that perform specific image transformation operations.
 *
 * Pipeline modules are the fundamental building blocks of the image processing pipeline.
 * Each module encapsulates a specific image processing algorithm and can be configured
 * independently. Modules are typically not accessed directly by users; instead, they
 * are controlled through the higher-level Feature interfaces.
 *
 * ## Module Categories
 *
 * ### Format Conversion Modules
 * - **UnpackModule**: Converts packed sensor data to standard formats
 * - **DebayerModule**: Converts Bayer pattern data to RGB
 * - **MonoConversionModule**: Converts color images to monochrome
 * - **PixelFormatConversionModule**: Final format conversion and bit depth adjustment
 *
 * ### Enhancement Modules
 * - **GainModule**: Applies digital gain for brightness and white balance
 * - **SharpeningModule**: Enhances image detail using edge-based filters
 * - **ToneCurveCorrectionModule**: Applies gamma correction and tone mapping
 * - **ColorMatrixTransformationModule**: Performs color space transformations
 *
 * ### Geometric Transformation Modules
 * - **TransformationModule**: Handles rotation and mirroring operations
 * - **DownsamplingModule**: Performs binning and decimation operations
 *
 * ### Correction Modules
 * - **HotpixelCorrectionModule**: Identifies and corrects defective pixels
 *
 * \note Modules are typically accessed through Feature interfaces rather than directly.
 *       Direct module access is primarily for advanced use cases and internal pipeline logic.
 */

/*!
 * \defgroup ids_peak_icv_cpp_pipeline_features Pipeline Features
 * \ingroup ids_peak_icv_cpp_pipeline
 *
 * \brief High-level user interfaces for configuring and controlling pipeline processing stages.
 *
 * Pipeline features provide intuitive, user-friendly interfaces for configuring the various
 * image processing operations in the pipeline. Each feature corresponds to one or more
 * underlying modules and abstracts away the low-level implementation details.
 *
 * ## Feature Categories
 *
 * ### Geometric Features
 * - **BinningFeature**: Combines adjacent pixels to reduce resolution and improve SNR
 * - **DecimationFeature**: Reduces resolution by skipping pixels in a pattern
 * - **MirrorFeature**: Flips images horizontally and/or vertically
 * - **RotationFeature**: Rotates images in 90-degree increments
 *
 * ### Color and Brightness Features
 * - **GainFeature**: Controls overall brightness and individual color channel gains
 * - **ChromaticAdaptionFeature**: Adjusts to changes in lighting conditions to maintain consistent color perception
 * - **ColorCorrectionFeature**: Applies color correction matrices for color space conversion
 * - **SaturationFeature**: Adjusts color saturation levels
 * - **GammaFeature**: Applies gamma correction for brightness and contrast adjustment
 * - **DigitalBlackFeature**: Compensates for sensor digital black offsets
 *
 * ### Enhancement Features
 * - **SharpeningFeature**: Enhances image detail and perceived sharpness
 * - **HotpixelCorrectionFeature**: Removes defective pixels from sensor data
 *
 * ## Common Feature Interface
 *
 * All features inherit from `IFeature` and provide:
 * - **SetEnabled(bool)**: Enable or disable the feature
 * - **IsEnabled()**: Check if the feature is currently enabled
 * - **ResetToDefault()**: Restore feature to default settings
 */

/*!
 * \defgroup ids_peak_icv_cpp_pipeline_types Special Pipeline Types
 * \ingroup ids_peak_icv_cpp_pipeline
 *
 * \brief Supporting data structures, enumerations, and type definitions for pipeline configuration.
 *
 * This group contains the specialized types used throughout the pipeline system for
 * configuration, control, and data representation. These types provide type-safe
 * interfaces for pipeline parameters and ensure consistent behavior across the system.
 */

/*!
 * \defgroup ids_peak_icv_cpp_library Library
 * \ingroup ids_peak_icv_cpp
 *
 * \brief Library runtime management.
 *
 * Provides global control and initialization functions.
 */

/*!
 * \defgroup ids_peak_icv_cpp_painting Painting
 * \ingroup ids_peak_icv_cpp
 * \brief Image painting.
 *
 * Provides tools and styling options to draw shapes and overlays onto images.
 */

/*!
 * \defgroup ids_peak_icv_cpp_selectors Selectors
 * \ingroup ids_peak_icv_cpp
 *
 * \brief Object filtering.
 *
 * A Selector encapsulates a filtering operation
 * applied to a given set of objects.
 * Instead of modifying the original set,
 * each selection function returns a new Selector object
 * that represents the filtered subset.
 *
 * This design enables the chaining of multiple selection criteria.
 *
 * To access the currently selected objects,
 * use the respective accessor functions,
 * such as \ref peak::icv::RegionSelector::GetRegions.
 */

/*!
 * \defgroup ids_peak_icv_cpp_serialization Serialization
 * \ingroup ids_peak_icv_cpp
 *
 * \brief Object serialization.
 *
 * Serialization refers to the process of transforming
 * an object’s state or a data structure
 * into a format suitable for storage or transmission
 * (e.g., files, databases, or network streams).
 * This allows data to be persisted
 * and later reconstructed through deserialization,
 * restoring the original structure and values.
 *
 * Typical use cases include:
 * - Saving application state to disk
 * - Transferring data between processes or systems
 */

/*!
 * \defgroup ids_peak_icv_cpp_types Types
 * \ingroup ids_peak_icv_cpp
 *
 * \brief Fundamental data types.
 */

/*!
 * \defgroup ids_peak_icv_cpp_geometry Geometry
 * \ingroup ids_peak_icv_cpp_types
 * \brief Geometric data types.
 */

#include <peak_icv/algorithms/calibration/peak_icv_calibration_parameters.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_plate.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_result.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_calibration_view.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_camera_calibration.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_distortion_coefficients.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_extrinsic_parameters.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_intrinsic_parameters.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_reprojection_error.hpp>
#include <peak_icv/algorithms/calibration/peak_icv_workspace_calibration.hpp>

#include <peak_icv/algorithms/code_reader/peak_icv_code_reader.hpp>
#include <peak_icv/algorithms/code_reader/peak_icv_code_reader_result.hpp>
#include <peak_icv/algorithms/code_reader/peak_icv_code_types.hpp>

#include <peak_icv/algorithms/hdr/tone_mapping/peak_icv_drago_tone_mapping.hpp>

#include <peak_icv/algorithms/filters/peak_icv_median_filter.hpp>

#include <peak_icv/algorithms/hdr/peak_icv_hdr.hpp>
#include <peak_icv/algorithms/hdr/peak_icv_response_curve.hpp>
#include <peak_icv/algorithms/hdr/tone_mapping/peak_icv_drago_tone_mapping.hpp>

#include <peak_icv/algorithms/thresholds/peak_icv_threshold.hpp>

#include <peak_icv/algorithms/transformations/peak_icv_interpolation.hpp>
#include <peak_icv/algorithms/transformations/peak_icv_undistortion.hpp>

#include <peak_icv/exceptions/peak_icv_exception.hpp>

#include <peak_icv/io/peak_icv_calibration_parameters_writer.hpp>
#include <peak_icv/io/peak_icv_calibration_result_writer.hpp>
#include <peak_icv/io/peak_icv_image_writer.hpp>
#include <peak_icv/io/peak_icv_point_cloud_writer.hpp>
#include <peak_icv/io/peak_icv_response_curve_writer.hpp>

#include <peak_icv/library/peak_icv_library.hpp>
#include <peak_icv/library/peak_icv_version.hpp>

#include <peak_icv/painting/peak_icv_color.hpp>
#include <peak_icv/painting/peak_icv_drawing_options.hpp>
#include <peak_icv/painting/peak_icv_opacity.hpp>
#include <peak_icv/painting/peak_icv_painter.hpp>

#include <peak_icv/pipeline/peak_icv_default_pipeline.hpp>

#include <peak_icv/selectors/peak_icv_region_selector.hpp>

#include <peak_icv/serialization/peak_icv_archive.hpp>
#include <peak_icv/serialization/peak_icv_deserializer.hpp>
#include <peak_icv/serialization/peak_icv_serialization_types.hpp>
#include <peak_icv/serialization/peak_icv_serializer.hpp>

#include <peak_icv/types/geometry/peak_icv_coordinate_system.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyz.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyzi.hpp>
#include <peak_icv/types/geometry/peak_icv_point_xyzrgb.hpp>
#include <peak_icv/types/geometry/peak_icv_polygon.hpp>

#include <peak_icv/types/peak_icv_array_2d.hpp>
#include <peak_icv/types/peak_icv_image.hpp>
#include <peak_icv/types/peak_icv_point_cloud_xyz.hpp>
#include <peak_icv/types/peak_icv_point_cloud_xyzi.hpp>
#include <peak_icv/types/peak_icv_point_cloud_xyzrgb.hpp>
#include <peak_icv/types/peak_icv_region.hpp>
#include <peak_icv/types/peak_icv_transformation_matrix_3d.hpp>
#include <peak_icv/types/peak_icv_undistorted_image.hpp>
#include <peak_icv/types/peak_icv_xyz_image.hpp>
