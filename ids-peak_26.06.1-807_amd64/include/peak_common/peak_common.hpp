/*!
 * \file    peak_common.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2025-05-09
 * \since   ids_peak_common 1.0
 *
 * Copyright (c) 2025 - 2026, IDS Imaging Development Systems GmbH. All rights
 * reserved.
 */

/*!
 * \defgroup ids_peak_common IDS peak common
 *
 * \brief Fundamental types, constants, and interfaces shared across multiple libraries.
 *
 * This module contains reusable types, enumerations, utility classes, and interface definitions
 * that provide the foundation for other libraries and modules.
 *
 * It includes:
 * - Basic type definitions and aliases
 * - Core enums and flags
 * - Abstract interfaces and base classes
 * - Utility structures and helpers for consistent API design
 *
 * The components in this group are intended to be lightweight and dependency-free,
 * making them suitable for use across various projects and libraries.
 *
 * \since ids_peak_common 1.0
 */

/*!
\defgroup ids_peak_common_cpp C++
\ingroup ids_peak_common

\brief
  The C++ interface for the IDS peak common library.

# Prerequisites

The library requires the use of at least C++14 for the client application.

# How to use

In order to use \htmlonly IDS peak common \endhtmlonly you need to include the interface header file
`peak_common/peak_common.hpp`

\since ids_peak_common 1.0
 */

/*!
 * \defgroup ids_peak_common_pipeline Image Pipeline
 * \ingroup ids_peak_common_cpp
 *
 * \brief Interfaces and types for defining and controlling data processing pipelines.
 *
 * This group contains the core interfaces for creating and managing pipelines,
 * which process input data through a sequence of configurable modules to produce output.
 * It provides the foundational classes and utilities for pipeline configuration,
 * execution, and lifecycle management.
 *
 * \since ids_peak_common 1.0
 */

/*!
 * \defgroup ids_peak_common_pipeline_modules Pipeline Modules
 * \ingroup ids_peak_common_pipeline
 *
 * \brief Interface definitions for individual module types used within a pipeline.
 *
 * This module defines the interfaces for pipeline modules, which represent individual
 * processing steps within a pipeline. Modules can be chained together to form flexible
 * and reusable data processing flows, each module focusing on a specific transformation
 * or operation.
 *
 * \since ids_peak_common 1.0
 */

/*!
 * \defgroup ids_peak_common_serialization Serialization
 * \ingroup ids_peak_common_cpp
 *
 * \brief Interfaces for defining serialization and deserialization behavior.
 *
 * It focuses on the contract layer without providing concrete serialization logic
 * or implementations.
 *
 * These interfaces are intended to be implemented by other components
 * or libraries to support specific serialization formats (e.g., binary,
 * text-based formats, or custom protocols).
 *
 * The goal of this module is to ensure a consistent and extensible
 * approach to serialization throughout the library ecosystem.
 *
 * \since ids_peak_common 1.0
 */

/*!
 * \defgroup ids_peak_common_types Types
 * \ingroup ids_peak_common_cpp
 *
 * \brief General-purpose types and interfaces used throughout the library.
 *
 * This module contains a collection of core types that are widely used across
 * different components of the library. These types among others include utility types
 * such as ranges, intervals, type-erased containers (e.g., Any), pixel formats,
 * image view interfaces, and other foundational constructs.
 *
 * The types in this group are intended to provide reusable, versatile building blocks
 * for applications and other libraries built on top of this component.
 *
 * \since ids_peak_common 1.0
 */

/*!
 * \defgroup ids_peak_common_types_geometry Geometry
 * \ingroup ids_peak_common_types
 *
 * \brief Types representing geometric concepts such as points, sizes, rectangles, and vectors.
 *
 * This subgroup focuses on types commonly used to represent and manipulate geometric data.
 * It includes templates and type aliases for points, rectangles, sizes, and vectors,
 * which are useful in image processing, spatial computations, and graphical applications.
 *
 * \since ids_peak_common 1.0
 */

/*!
 * \defgroup ids_peak_common_detail Internal Detail Types
 * \ingroup ids_peak_common_cpp
 *
 * \brief Internal types and implementation details with limited public exposure.
 *
 * This module contains internal types, helper classes, and low-level implementation details
 * that are primarily intended for internal use within the library. These types are located
 * in the `detail` namespace and are not part of the stable public API.
 *
 * **Direct use of types from the `detail` namespace is discouraged**, as their structure
 * and behavior may change without notice between versions.
 *
 * When needed, stable access to certain internal types is provided through public `using`
 * declarations or type aliases. These public aliases form part of the supported API surface
 * and are safe to use. Only these publicly exposed aliases should be relied upon in user code.
 *
 * \since ids_peak_common 1.0
 */

/*!
 * \defgroup ids_peak_common_c_types C Language Compatible Types
 * \ingroup ids_peak_common_cpp
 *
 * \brief C-compatible types for interoperability with C codebases.
 *
 * This group contains a selection of type definitions and structures
 * designed for use in pure C environments. While the majority of the
 * library is written in C++ and leverages modern C++ features, these
 * types provide limited interoperability for scenarios where integration
 * with C code is required.
 *
 * Only a subset of types are exposed in this group, focused on
 * facilitating basic data exchange and interoperability.
 * Full functionality of the library is not available in C.
 *
 * \since ids_peak_common 1.0
 */

/*!
 * \namespace peak::common
 * \ingroup ids_peak_common_cpp
 *
 * \brief Root namespace for common types and interfaces shared across multiple libraries.
 *
 * The `peak::common` namespace contains all publicly available types, constants,
 * enumerations, and interfaces that form the foundation for other libraries and modules.
 *
 * This namespace is part of the \ref ids_peak_common "Common Types and Interfaces" module
 * and is intended to provide stable, reusable components for general use.
 *
 * It includes:
 * - Core data types and structures
 * - Publicly exposed aliases for internal types
 * - Interfaces and helper utilities for consistent API design
 *
 * All components within this namespace are suitable for use in production code and are
 * maintained with a stable API guarantee.
 *
 * \since ids_peak_common 1.0
 */

#pragma once

namespace peak
{
namespace common
{
/*!
 * \ingroup ids_peak_common_detail
 *
 * \brief Namespace for internal implementation details and low-level types.
 *
 * The `detail` namespace contains internal types, helper classes, and low-level
 * implementation components that support the functionality of the public API.
 *
 * This namespace belongs to the \ref ids_peak_common_detail "Internal Detail Types" module
 * and is **not intended for direct use in user code**. Types and functions in this namespace
 * are considered implementation details and may change without notice.
 *
 * When necessary, safe access to internal types is provided via public aliases
 * in the `peak::common` namespace. **User code should rely on these public
 * aliases for forward compatibility** and avoid direct dependencies on `detail` components.
 *
 * \since ids_peak_common 1.0
 */
namespace detail
{} // namespace detail
} // namespace common 
} // namespace peak

#include <peak_common/detail/peak_common_backend_accessor.hpp>
#include <peak_common/detail/peak_common_math.hpp>
#include <peak_common/detail/peak_common_metadata_traits.hpp>
#include <peak_common/detail/peak_common_type_traits.hpp>
#include <peak_common/exceptions/peak_common_exceptions.hpp>
#include <peak_common/pipeline/peak_common_ipipeline.hpp>
#include <peak_common/pipeline/peak_common_pipeline_base.hpp>
#include <peak_common/pipeline/modules/peak_common_iautofeature_module.hpp>
#include <peak_common/pipeline/modules/peak_common_igain_module.hpp>
#include <peak_common/pipeline/modules/peak_common_imodule.hpp>
#include <peak_common/serialization/peak_common_iarchive.hpp>
#include <peak_common/serialization/peak_common_ideserializer.hpp>
#include <peak_common/serialization/peak_common_iserializable.hpp>
#include <peak_common/serialization/peak_common_iserializer.hpp>
#include <peak_common/types/geometry/peak_common_point.hpp>
#include <peak_common/types/geometry/peak_common_rectangle.hpp>
#include <peak_common/types/geometry/peak_common_size.hpp>
#include <peak_common/types/geometry/peak_common_vector.hpp>
#include <peak_common/types/peak_common_any.hpp>
#include <peak_common/types/peak_common_channel.hpp>
#include <peak_common/types/peak_common_iimageview.hpp>
#include <peak_common/types/peak_common_interval.hpp>
#include <peak_common/types/peak_common_metadata.hpp>
#include <peak_common/types/peak_common_metadata_key.hpp>
#include <peak_common/types/peak_common_pixel_format.hpp>
#include <peak_common/types/peak_common_range.hpp>
#include <peak_common/types/peak_common_version.hpp>
#include <peak_common_c/detail/peak_common_defines.h>
#include <peak_common_c/types/peak_common_simple_types.h>
