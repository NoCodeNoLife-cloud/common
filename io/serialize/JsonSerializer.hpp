// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <fstream>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include "io/interface/IfaceJsonSerializable.hpp"

namespace common::io::serialize
{
template <typename T>concept DerivedFromJsonSerializable = std::is_base_of_v<interface::IfaceJsonSerializable, T>;

/// \brief Class JsonSerializer abstract
/// \details This class is an abstract class which provides static methods to serialize and deserialize objects to and
/// from JSON files. It is used by the Student class to save and load student objects to and from JSON files.
class JsonSerializer abstract
{
public:
	JsonSerializer() = delete;
	template <DerivedFromJsonSerializable T> static auto saveStudentToJsonFile(const T& entity, const std::string& filename) -> void;
	template <DerivedFromJsonSerializable T> static auto loadStudentFromJsonFile(const std::string& filename) -> T;
	static auto getStringOrDefault(const rapidjson::Value& json, const char* key, const std::string& defaultValue) -> std::string;
	static auto getIntOrDefault(const rapidjson::Value& json, const char* key, int defaultValue) -> int;
	static auto getDoubleOrDefault(const rapidjson::Value& json, const char* key, double defaultValue) -> double;
	static auto getBoolOrDefault(const rapidjson::Value& json, const char* key, bool defaultValue) -> bool;
	static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void;
	static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, int value) -> void;
	static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, double value) -> void;
	static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, bool value) -> void;
};

/// \brief Saves a student object to a JSON file.
/// \tparam T type of the student object, must be derived from JsonSerializable.
/// \param entity the student object to be saved.
/// \param filename the name of the file to save.
template <DerivedFromJsonSerializable T> auto JsonSerializer::saveStudentToJsonFile(const T& entity, const std::string& filename) -> void {
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter writer(buffer);
	entity.serialize(writer);
	std::ofstream ofs(filename);
	if (!ofs) {
		throw std::runtime_error("Failed to open file for writing: " + filename);
	}
	ofs << buffer.GetString();
	ofs.close();
}

/// \brief Loads a student object from a JSON file.
/// \tparam T type of the student object, must be derived from JsonSerializable.
/// \param filename the name of the file to load.
/// \return the loaded student object.
template <DerivedFromJsonSerializable T> auto JsonSerializer::loadStudentFromJsonFile(const std::string& filename) -> T {
	T entity{};
	std::ifstream ifs(filename);
	if (!ifs) {
		throw std::runtime_error("Failed to open file for reading: " + filename);
	}
	const std::string jsonStr{std::istreambuf_iterator(ifs), std::istreambuf_iterator<char>()};
	ifs.close();
	rapidjson::Document document;
	if (document.Parse(jsonStr.c_str()).HasParseError()) {
		throw std::runtime_error("JSON parse error!");
	}
	if (document.IsObject()) {
		entity.deserialize(document);
	}
	return entity;
}
}
