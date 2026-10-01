/*!
 * \file    peak.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2019-05-01
 * \since   1.0
 *
 * Copyright (c) 2019 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once

/*!
 * \defgroup ids_peak IDS peak genericAPI
 *
 * \brief The IDS peak genericAPI library provides a unified interface for GenTL and
 *        GenApi, while also adding additional convenience features.
 */

/*!
 * \defgroup ids_peak_cpp C++
 * \ingroup ids_peak
 *
 * \brief The C++ interface for the IDS peak genericAPI library.
 */

/*!
 * \defgroup ids_peak_library Library
 * \ingroup ids_peak_cpp
 *
 * \brief Library level functions and types.
 */

/*!
 * \defgroup ids_peak_exceptions Exceptions
 * \ingroup ids_peak_cpp
 *
 * \brief Library exception types and functions.
 */

/*!
 * \defgroup ids_peak_device_discovery Device Discovery
 * \ingroup ids_peak_cpp
 *
 * \brief Provides classes and functions to discover and enumerate devices,
 *        interfaces, and GenTL producer libraries, allowing users to query
 *        available hardware and system modules.
 */

/*!
 * \defgroup ids_peak_device_control Device Control
 * \ingroup ids_peak_cpp
 *
 * \brief Provides classes and utilities for controlling and interacting with
 *        devices. Offers access to device features, mechanisms
 *        for handling events, and methods to access or manipulate
 *        files stored in a device’s persistent memory.
 */

/*!
 * \defgroup ids_peak_acquisition Acquisition
 * \ingroup ids_peak_cpp
 *
 * \brief Provides classes and utilities for acquiring, managing,
 *        and interpreting image and data buffers from devices. This includes
 *        access to data streams, buffer handling, and convenient conversions
 *        of raw or structured buffer contents into usable image
 *        representations.
 */

/*!
 * \defgroup ids_peak_device Device
 * \ingroup ids_peak_cpp
 *
 * \brief Provides classes and utilities for interacting with
 *        GenICam-compliant devices. This includes access to device proxies,
 *        the underlying remote hardware, enabling controlled and standardized
 *        communication with connected devices.
 */

/*!
 * \defgroup ids_peak_firmware_update Firmware Update
 * \ingroup ids_peak_cpp
 *
 * \brief Provides functionality for updating the firmware of
 *        GenICam-compliant devices, including access to update information,
 *        progress monitoring, and control over update behavior.
 */

/*!
 * \defgroup ids_peak_types Types
 * \ingroup ids_peak_cpp
 *
 * \brief General-purpose types and interfaces used throughout the library.
 */

/*!
 * \defgroup ids_peak_node Node
 * \ingroup ids_peak_device_control
 *
 * \brief Provides the concrete node types used to access and manipulate
 *        the features of a GenICam-compliant device via a
 *        [NodeMap](\ref peak::core::NodeMap).
 *
 * \details
 * Node and node map behavior follows the GenICam feature model as exposed by this API.
 *
 * \anchor node_caching_polling_concepts
 * \par Node Caching and Polling Concepts
 *
 * Caching exists to reduce control-channel traffic and access latency for frequently queried feature values.
 * By reusing values that are still valid according to cache and invalidation rules, applications can read dynamic
 * feature state more efficiently while preserving correctness.
 *
 * Nodes can be cacheable, depending on their XML metadata and runtime state.
 * Use \ref peak::core::nodes::Node::IsCacheable "Node::IsCacheable" and
 * \ref peak::core::nodes::Node::CachingMode "Node::CachingMode" to inspect this behavior.
 *
 * The caching mode is represented by
 * \ref peak::core::nodes::NodeCachingMode "NodeCachingMode".
 *
 * Various access states are represented by
 * \ref peak::core::nodes::NodeAccessStatus "NodeAccessStatus"; refer to that enum for concrete values.
 * Access status can also be cacheable. Use
 * \ref peak::core::nodes::Node::IsAccessStatusCacheable "Node::IsAccessStatusCacheable" to check this.
 *
 * Invalidation dependencies still apply: when one node changes, dependent nodes can be invalidated and may
 * require re-evaluation on next access. Use
 * \ref peak::core::nodes::Node::InvalidatedNodes "Node::InvalidatedNodes" to inspect which nodes become
 * invalid when the current node changes (directly and indirectly connected dependent nodes), and
 * \ref peak::core::nodes::Node::InvalidatingNodes "Node::InvalidatingNodes" to inspect which upstream
 * nodes can invalidate the current node (directly connected nodes only).
 *
 * Typical usage is to update a controlling node, then re-read affected dependent nodes (optionally with
 * \ref peak::core::nodes::NodeCacheUsePolicy "NodeCacheUsePolicy" configured to ignore cache when strict
 * freshness is required).
 *
 * \par Polling Time and NodeMap Polling
 * Some nodes provide a polling hint via
 * \ref peak::core::nodes::Node::PollingTime "Node::PollingTime".
 * Polling is executed on node map level by
 * \ref peak::core::NodeMap::PollNodes(int64_t) "NodeMap::PollNodes", which updates nodes that require
 * polling.
 *
 * The parameter of \ref peak::core::NodeMap::PollNodes(int64_t) "NodeMap::PollNodes" is elapsed time since
 * the previous call
 * in milliseconds. This API does not run an internal polling thread; applications must call it explicitly.
 *
 * \par NodeMap Polling Best Practice
 * Use one periodic loop per active node map and pass real elapsed milliseconds to
 * \ref peak::core::NodeMap::PollNodes(int64_t) "NodeMap::PollNodes".
 *
 * Practical guidance:
 * - Keep polling active while your application displays or depends on dynamic feature state.
 * - Choose an interval at or below the shortest relevant node polling time, but avoid over-polling.
 * - For deterministic behavior, compute elapsed time from a monotonic clock instead of a fixed constant.
 *
 * \par Cache Use Policy in Value and Read Calls
 * Most value accessors expose \ref peak::core::nodes::NodeCacheUsePolicy "NodeCacheUsePolicy",
 * for example:
 * - \ref peak::core::nodes::FloatNode::Value "FloatNode::Value"
 * - \ref peak::core::nodes::IntegerNode::Value "IntegerNode::Value"
 * - \ref peak::core::nodes::StringNode::Value "StringNode::Value"
 * - \ref peak::core::nodes::EnumerationNode::CurrentEntry "EnumerationNode::CurrentEntry"
 * - \ref peak::core::nodes::RegisterNode::Read "RegisterNode::Read"
 *
 * These accessors use \ref peak::core::nodes::NodeCacheUsePolicy "NodeCacheUsePolicy" to choose whether a
 * single read operation should use cached data or request fresh data from the device.
 */

/*!
 * \defgroup ids_peak_node_enums Node Enums
 * \ingroup ids_peak_device_control
 *
 * \brief Provides general enumerations for describing the behavior,
 *        properties, and metadata of nodes within a
 *        [NodeMap](\ref peak::core::NodeMap).
 */

#include <peak/buffer/peak_buffer.hpp>
#include <peak/buffer/peak_buffer_chunk.hpp>
#include <peak/buffer/peak_buffer_part.hpp>

#include <peak/data_stream/peak_data_stream.hpp>
#include <peak/data_stream/peak_data_stream_descriptor.hpp>

#include <peak/device/peak_device.hpp>
#include <peak/device/peak_device_descriptor.hpp>
#include <peak/device/peak_firmware_update_information.hpp>
#include <peak/device/peak_firmware_update_progress_observer.hpp>
#include <peak/device/peak_firmware_updater.hpp>

#include <peak/environment/peak_environment_inspector.hpp>

#include <peak/file/peak_fileadapter.hpp>

#include <peak/interface/peak_interface.hpp>
#include <peak/interface/peak_interface_descriptor.hpp>

#include <peak/library/peak_library.hpp>

#include <peak/node_map/peak_boolean_node.hpp>
#include <peak/node_map/peak_category_node.hpp>
#include <peak/node_map/peak_command_node.hpp>
#include <peak/node_map/peak_enumeration_entry_node.hpp>
#include <peak/node_map/peak_enumeration_node.hpp>
#include <peak/node_map/peak_float_node.hpp>
#include <peak/node_map/peak_integer_node.hpp>
#include <peak/node_map/peak_node.hpp>
#include <peak/node_map/peak_node_map.hpp>
#include <peak/node_map/peak_register_node.hpp>
#include <peak/node_map/peak_string_node.hpp>

#include <peak/port/peak_port.hpp>
#include <peak/port/peak_port_url.hpp>

#include <peak/producer_library/peak_producer_library.hpp>

#include <peak/reconnect/reconnect_information.hpp>

#include <peak/system/peak_system.hpp>
#include <peak/system/peak_system_descriptor.hpp>

#include <peak/version/peak_version.hpp>

#include <peak/image_view/peak_image_view.hpp>
#include <peak/peak_buffer_converter.hpp>
#include <peak/peak_device_manager.hpp>

#include <peak/image_view/peak_image_view_impl.hpp>
