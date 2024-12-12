// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Object.hpp"

namespace common::entity::base_type
{
Object::Object() = default;
Object::~Object() = default;

/// \brief Clone the object
/// \return A clone of the object
auto Object::clone() const -> std::unique_ptr<Object> {
	return std::make_unique<Object>(Object(*this));
}

/// \brief Get the class type of the object
/// \return The class type
auto Object::getClass() const -> const std::type_info& {
	return typeid(*this);
}

/// \brief Check if the object is equal to another object
/// \param other The other object
/// \return True if the objects are equal
auto Object::equals(const Object& other) const -> bool {
	if (typeid(*this) != typeid(other)) {
		return false;
	}
	return this == &other;
}

/// \brief Get the hash code of the object
/// \return The hash code
auto Object::hashCode() const -> size_t {
	return std::hash<const void*>{}(this);
}

/// \brief Get the string representation of the object
/// \return The string representation
auto Object::toString() const -> std::string {
	return std::format("{}", *this);
}
}
