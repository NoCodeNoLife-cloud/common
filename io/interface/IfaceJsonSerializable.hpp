// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace common::interface
{
/// \brief Abstract class for JSON serialization and deserialization.
/// \details This class provides an interface for objects that can be serialized to and deserialized from JSON format.
/// Derived classes must implement the serialize and deserialize methods to provide the specific serialization logic.
/// The serialize method writes the object state to a JSON writer, while the deserialize method reads the object state
/// from a JSON value.
class IfaceJsonSerializable abstract
{
public:
	virtual ~IfaceJsonSerializable() = default;
	virtual auto serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer) const -> void = 0;
	virtual auto deserialize(const rapidjson::Value& json) -> void = 0;
};
}
