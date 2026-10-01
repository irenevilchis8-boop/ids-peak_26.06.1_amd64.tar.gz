/*!
 * \file    peak_common_node_enums.hpp
 *
 * \author  IDS Imaging Development Systems GmbH
 * \date    2019-05-01
 * \since   1.0
 *
 * Copyright (c) 2019 - 2026, IDS Imaging Development Systems GmbH. All rights reserved.
 */

#pragma once


namespace peak
{
namespace core
{
namespace nodes
{

/*!
 * \ingroup ids_peak_node_enums
 * \brief Defines how node value access should interact with the internal cache.
 *
 * See \ref node_caching_polling_concepts "Node Caching and Polling Concepts".
 *
 * This policy is used by read accessors such as
 * \ref peak::core::nodes::FloatNode::Value "FloatNode::Value",
 * \ref peak::core::nodes::IntegerNode::Value "IntegerNode::Value",
 * \ref peak::core::nodes::StringNode::Value "StringNode::Value",
 * \ref peak::core::nodes::EnumerationNode::CurrentEntry "EnumerationNode::CurrentEntry",
 * and \ref peak::core::nodes::RegisterNode::Read "RegisterNode::Read".
 * It does not change whether a node is generally cacheable; it only controls
 * how one specific read operation is executed.
 */
enum class NodeCacheUsePolicy
{
    /*! Use cache according to cache and invalidation rules. */
    UseCache,
    /*! Ignore cache for this read and request fresh data from the device. */
    IgnoreCache
};

/*!
 * \ingroup ids_peak_node_enums
 * Possible node increment types for number nodes (float, integer).
 */
enum class NodeIncrementType
{
    NoIncrement,
    FixedIncrement,
    ListIncrement
};

/*!
 * \ingroup ids_peak_node_enums
 * Possible node representations for number nodes (float, integer).
 */
enum class NodeRepresentation
{
    Linear,
    Logarithmic,
    Boolean,
    PureNumber,
    HexNumber,
    IP4Address,
    MACAddress
};

inline std::string ToString(NodeCacheUsePolicy entry)
{
    std::string entryString;

    if (entry == NodeCacheUsePolicy::UseCache)
    {
        entryString = "UseCache";
    }
    else if (entry == NodeCacheUsePolicy::IgnoreCache)
    {
        entryString = "IgnoreCache";
    }

    return entryString;
}

inline std::string ToString(NodeIncrementType entry)
{
    std::string entryString;

    if (entry == NodeIncrementType::NoIncrement)
    {
        entryString = "NoIncrement";
    }
    else if (entry == NodeIncrementType::FixedIncrement)
    {
        entryString = "FixedIncrement";
    }
    else if (entry == NodeIncrementType::ListIncrement)
    {
        entryString = "ListIncrement";
    }

    return entryString;
}

inline std::string ToString(NodeRepresentation entry)
{
    std::string entryString;

    if (entry == NodeRepresentation::Linear)
    {
        entryString = "Linear";
    }
    else if (entry == NodeRepresentation::Logarithmic)
    {
        entryString = "Logarithmic";
    }
    else if (entry == NodeRepresentation::PureNumber)
    {
        entryString = "PureNumber";
    }
    else if (entry == NodeRepresentation::HexNumber)
    {
        entryString = "HexNumber";
    }
    else if (entry == NodeRepresentation::IP4Address)
    {
        entryString = "IP4Address";
    }
    else if (entry == NodeRepresentation::MACAddress)
    {
        entryString = "MACAddress";
    }

    return entryString;
}

} /* namespace nodes */
} /* namespace core */
} /* namespace peak */
