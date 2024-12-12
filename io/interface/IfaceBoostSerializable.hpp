// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <boost/serialization/serialization.hpp>

namespace common::interface
{
/// \brief Abstract base class for Boost serializable objects.
/// This class provides an interface for objects that can be serialized
/// using Boost.Serialization. Deriving classes must implement the
/// `serializeImpl` method to define the actual serialization logic.
/// \tparam T The type of the derived class.
template <typename T> class IfaceBoostSerializable abstract
{
public:
	virtual ~IfaceBoostSerializable() = default;

private:
	friend class boost::serialization::access;
	template <class Archive> void serialize(Archive& archive, unsigned int version);
};

/// \brief Serialize the object using Boost.Serialization
/// This function is called by Boost.Serialization to serialize or
/// deserialize an object of type T. It delegates the actual
/// serialization logic to the serializeImpl function of the derived class.
/// \tparam Archive The type of archive to serialize the data to/from
/// \param archive The archive object used for serialization
/// \param version The version of the serialized data
template <typename T> template <class Archive> void IfaceBoostSerializable<T>::serialize(Archive& archive, const unsigned int version) {
	static_cast<T*>(this)->serializeImpl(archive, version);
}
}
