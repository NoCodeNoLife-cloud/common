// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <sstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "io/interface/IfaceBoostSerializable.hpp"

namespace common::io::serialize
{
template <typename T>concept DerivedFromBoostSerializable = std::is_base_of_v<interface::IfaceBoostSerializable<T>, T>;

/// \brief Abstract class for serializing and deserializing objects using Boost Serialization.
/// This class provides static methods to serialize and deserialize objects
/// of types derived from `BoostSerializable`. It uses Boost Serialization
/// to perform the conversion of objects to/from strings.
/// \tparam T The object type, which must be derived from `BoostSerializable`.
class BoostSerializer abstract
{
public:
	template <DerivedFromBoostSerializable T> static auto serializeObject(const T& obj) -> std::string;
	template <DerivedFromBoostSerializable T> static auto deserializeObject(const std::string& data) -> T;
};

/// \brief Serialize an object into a string using Boost Serialization.
/// This function takes an object and serializes it into a string using
/// Boost Serialization. The object type `T` must support Boost
/// Serialization.
/// \param obj The object to serialize.
/// \return The serialized string.
template <DerivedFromBoostSerializable T> auto BoostSerializer::serializeObject(const T& obj) -> std::string {
	std::ostringstream ostringstream;
	boost::archive::binary_oarchive binaryOarchive(ostringstream);
	binaryOarchive << obj;
	return ostringstream.str();
}

/// \brief Deserialize an object from a string using Boost Serialization.
/// This function takes a serialized string and deserializes it into an object
/// of type `T` using Boost Serialization. The object type `T` must support
/// Boost Serialization.
/// \param data The serialized string data.
/// \return The deserialized object of type `T`.
template <DerivedFromBoostSerializable T> auto BoostSerializer::deserializeObject(const std::string& data) -> T {
	T t = T();
	std::istringstream istringstream(data);
	boost::archive::binary_iarchive binaryIarchive(istringstream);
	binaryIarchive >> t;
	return t;
}
}
