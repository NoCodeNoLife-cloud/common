// Created by author ethereal on 2024/11/24.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "JsonSerializer.hpp"

namespace common::io::serialize
{
/// \brief Get a string value from a JSON object with a default value.
/// \param json the JSON object to retrieve the value from.
/// \param key the key to retrieve the value for.
/// \param defaultValue the default value to return if the key doesn't exist or is not a string.
/// \return the retrieved string value, or the default value if the key doesn't exist or is not a string.
auto JsonSerializer::getStringOrDefault(const rapidjson::Value& json, const char* key, const std::string& defaultValue) -> std::string {
	if (json.HasMember(key) && json[key].IsString()) {
		return json[key].GetString();
	}
	return defaultValue;
}

/// \brief Get an integer value from a JSON object with a default value.
/// \param json the JSON object to retrieve the value from.
/// \param key the key to retrieve the value for.
/// \param defaultValue the default value to return if the key doesn't exist or is not an integer.
/// \return the retrieved integer value, or the default value if the key doesn't exist or is not an integer.
auto JsonSerializer::getIntOrDefault(const rapidjson::Value& json, const char* key, const int defaultValue) -> int {
	if (json.HasMember(key) && json[key].IsInt()) {
		return json[key].GetInt();
	}
	return defaultValue;
}

/// \brief Get a double value from a JSON object with a default value.
/// \param json the JSON object to retrieve the value from.
/// \param key the key to retrieve the value for.
/// \param defaultValue the default value to return if the key doesn't exist or is not a double.
/// \return the retrieved double value, or the default value if the key doesn't exist or is not a double.
auto JsonSerializer::getDoubleOrDefault(const rapidjson::Value& json, const char* key, const double defaultValue) -> double {
	if (json.HasMember(key) && json[key].IsDouble()) {
		return json[key].GetDouble();
	}
	return defaultValue;
}

/// \brief Get a boolean value from a JSON object with a default value.
/// \param json the JSON object to retrieve the value from.
/// \param key the key to retrieve the value for.
/// \param defaultValue the default value to return if the key doesn't exist or is not a boolean.
/// \return the retrieved boolean value, or the default value if the key doesn't exist or is not a boolean.
auto JsonSerializer::getBoolOrDefault(const rapidjson::Value& json, const char* key, const bool defaultValue) -> bool {
	if (json.HasMember(key) && json[key].IsBool()) {
		return json[key].GetBool();
	}
	return defaultValue;
}

/// \brief Serialize a field into a JSON object.
/// \param writer the JSON writer to use.
/// \param key the key of the field.
/// \param value the value of the field.
auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void {
	writer.Key(key);
	writer.String(value.c_str());
}

/// \brief Serialize a field into a JSON object.
/// \param writer the JSON writer to use.
/// \param key the key of the field.
/// \param value the value of the field.
/// \details This function serializes a field into a JSON object. It takes a JSON writer and a key-value pair as
/// parameter. The key is the name of the field in the JSON object and the value is the value of that field. The JSON
/// writer is used to write the key-value pair into the JSON object.
auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const int value) -> void {
	writer.Key(key);
	writer.Int(value);
}

/// \brief Serialize a field into a JSON object.
/// \param writer the JSON writer to use.
/// \param key the key of the field.
/// \param value the value of the field.
/// \details This function serializes a field into a JSON object. It takes a JSON writer and a key-value pair as
/// parameter. The key is the name of the field in the JSON object and the value is the value of that field. The JSON
/// writer is used to write the key-value pair into the JSON object.
auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const double value) -> void {
	writer.Key(key);
	writer.Double(value);
}

/// \brief Serialize a field into a JSON object.
/// \param writer the JSON writer to use.
/// \param key the key of the field.
/// \param value the value of the field.
/// \details This function serializes a field into a JSON object. It takes a JSON writer and a key-value pair as
/// parameter. The key is the name of the field in the JSON object and the value is the value of that field. The JSON
/// writer is used to write the key-value pair into the JSON object.
auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const bool value) -> void {
	writer.Key(key);
	writer.Bool(value);
}
}
