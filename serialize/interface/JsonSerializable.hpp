// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef JSONSERIALIZABLE_HPP
#define JSONSERIALIZABLE_HPP
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace common::interface
{
	/// \brief Abstract class for JSON serialization and deserialization.
	/// \details This class provides an interface for objects that can be serialized to and deserialized from JSON format.
	/// Derived classes must implement the serialize and deserialize methods to provide the specific serialization logic.
	/// The serialize method writes the object state to a JSON writer, while the deserialize method reads the object state from a JSON value.
	class JsonSerializable abstract
	{
	public:
		virtual ~JsonSerializable() = default;
		virtual auto serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer) const -> void =0;
		virtual auto deserialize(const rapidjson::Value& json) -> void =0;
	};
}
#endif //JSONSERIALIZABLE_HPP
