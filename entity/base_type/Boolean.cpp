// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Boolean.hpp"

namespace common::entity::base_type
{
Boolean::Boolean(const bool value) : value_(value) {}

Boolean::~Boolean() = default;

/// \brief Conversion operator to bool.
/// \return The underlying boolean value of the Boolean object.
/// \details This operator allows an Boolean object to be used in a boolean context.
/// It returns the raw boolean value stored in the Boolean object.
Boolean::operator bool() const {
	return value_;
}

/// \brief Returns a string representation of the object.
/// \return A string representing the object's type name.
/// \details This function uses `typeid` to retrieve the name of the object's type.
std::string Boolean::toString() const {
	return std::format("{}", *this);
}

/// \brief Get the boolean value of the object.
/// \return The boolean value of the object
auto Boolean::boolValue() const -> bool {
	return value_;
}

/// \brief Compare this Boolean object with another.
/// \param other The Boolean object to compare with.
/// \return An integer less than, equal to, or greater than zero if this object
/// is considered to be respectively less than, equal to, or greater than the specified object.
/// \details This function compares the underlying boolean values directly.
auto Boolean::compareTo(const Boolean& other) const -> int {
	return value_ - other.value_;
}

/// \brief Parse a boolean value from a string.
/// \param str The string to parse.
/// \return A Boolean object representing the parsed value.
/// \throws std::invalid_argument If the string is not "true" or "false".
auto Boolean::parseBoolean(const std::string& str) -> Boolean {
	if (str == "true" || str == "TRUE") {
		return Boolean(true);
	}
	if (str == "false" || str == "FALSE") {
		return Boolean(false);
	}
	throw std::invalid_argument("Invalid input string for Boolean conversion");
}

/// \brief Get the boolean value of the object.
/// \return The underlying boolean value of the Boolean object.
/// \details This function returns the raw boolean value stored in the Boolean object.
auto Boolean::booleanValue() const -> bool {
	return value_;
}

/// \brief Check if the object is equal to another object
/// \param other The other object
/// \return True if the objects are equal
/// \details This function checks if the object is equal to another object. The
/// function first checks if the objects are of the same type, and if so, it
/// compares the underlying boolean values directly. Otherwise, it returns false.
bool Boolean::equals(const Boolean& other) const {
	return value_ == other.value_;
}

/// \brief Check if the object is equal to another object
/// \param other The other object
/// \return True if the objects are equal
/// \details This function checks if the object is equal to another object by
/// comparing the underlying boolean values directly.
auto Boolean::operator==(const Boolean& other) const -> bool {
	return equals(other);
}

/// \brief Check if the Boolean object is not equal to another Boolean object
/// \param other The other Boolean object
/// \return True if the Boolean objects are not equal
/// \details This function compares the underlying boolean values directly.
auto Boolean::operator!=(const Boolean& other) const -> bool {
	return !equals(other);
}
}
