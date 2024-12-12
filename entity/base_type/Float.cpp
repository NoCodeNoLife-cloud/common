// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Float.hpp"
#include <string>

namespace common::entity::base_type
{
Float::Float(const float value) : value_(value) {}

Float::~Float() = default;

/// \brief Convert this Float object to a float.
/// \return The underlying float value of the object.
/// \details This function directly returns the underlying float value of the object.
/// It is useful for when you need to use the Float object as a float in a function call
/// or expression, but be careful not to use it when you mean to compare the objects
/// themselves.
Float::operator float() const {
	return value_;
}

/// \brief Returns a string representation of the object.
/// \return A string representing the object's type name.
/// \details This function uses `typeid` to retrieve the name of the object's type.
std::string Float::toString() const {
	return std::format("{}", *this);
}

/// \brief Check if the object is equal to another object
/// \param other The other object to compare with
/// \return True if the objects are of the same type and have equal float values, false otherwise
/// \details This function checks if the object is equal to another object. It first verifies
/// that the objects are of the same type using `typeid`, and then it compares their underlying
/// float values directly using `dynamic_cast`.
bool Float::equals(const Float& other) const {
	return value_ == other.value_;
}

/// \brief Compare this Float object with another.
/// \param other The Float object to compare with.
/// \return An integer less than, equal to, or greater than zero if this object
/// is considered to be respectively less than, equal to, or greater than the specified object.
/// \details This function compares the underlying float values directly.
auto Float::compareTo(const Float& other) const -> int {
	return (value_ > other.value_) - (value_ < other.value_);
}

/// \brief Returns the underlying float value.
/// \return The float value of the object
/// \details This function simply returns the underlying float value of the object.
auto Float::floatValue() const -> float {
	return value_;
}

/// \brief Parse a float value from a string.
/// \param str The string to parse.
/// \return A Float object representing the parsed value.
/// \throws std::invalid_argument If the string is not a valid float.
/// \throws std::out_of_range If the parsed value is out of range for a float.
auto Float::parseFloat(const std::string& str) -> Float {
	try {
		const float result = std::stof(str);
		return Float(result);
	}
	catch (const std::invalid_argument&) {
		throw std::invalid_argument("Invalid input string for Float conversion");
	} catch (const std::out_of_range&) {
		throw std::out_of_range("Value out of range for Float");
	}
}

/// \brief Check if this Float object is equal to another.
/// \param other The Float object to compare with.
/// \return True if the objects are equal, false otherwise.
/// \details This function checks if the underlying float values are equal.
auto Float::operator==(const Float& other) const -> bool {
	return value_ == other.value_;
}

/// \brief Check if this Float object is not equal to another.
/// \param other The Float object to compare with.
/// \return True if the objects are not equal, false otherwise.
/// \details This function checks if the underlying float values are not equal.
auto Float::operator!=(const Float& other) const -> bool {
	return value_ != other.value_;
}

/// \brief Check if this Float object is less than another.
/// \param other The Float object to compare with.
/// \return True if the objects are in order, false otherwise.
/// \details This function checks if the underlying float values are in order.
auto Float::operator<(const Float& other) const -> bool {
	return value_ < other.value_;
}

/// \brief Check if this Float object is greater than another.
/// \param other The Float object to compare with.
/// \return True if the objects are in order, false otherwise.
/// \details This function checks if the underlying float values are in order.
auto Float::operator>(const Float& other) const -> bool {
	return value_ > other.value_;
}

/// \brief Check if this Float object is less than or equal to another.
/// \param other The Float object to compare with.
/// \return True if the objects are in order, false otherwise.
/// \details This function checks if the underlying float values are in order.
auto Float::operator<=(const Float& other) const -> bool {
	return value_ <= other.value_;
}

/// \brief Check if this Float object is greater than or equal to another.
/// \param other The Float object to compare with.
/// \return True if the objects are in order, false otherwise.
/// \details This function checks if the underlying float values are in order.
auto Float::operator>=(const Float& other) const -> bool {
	return value_ >= other.value_;
}

/// \brief Add two Float objects together.
/// \param other The other Float object to add to this object.
/// \return The result of adding the two Float objects.
/// \details This function adds the underlying float values of the two objects together.
auto Float::operator+(const Float& other) const -> Float {
	return Float(this->value_ + other.value_);
}

/// \brief Subtract another Float object from this one.
/// \param other The other Float object to subtract from this object.
/// \return The result of subtracting the two Float objects.
/// \details This function subtracts the underlying float values of the two objects.
auto Float::operator-(const Float& other) const -> Float {
	return Float(this->value_ - other.value_);
}

/// \brief Multiply this Float object by another Float object.
/// \param other The other Float object to multiply with this object.
/// \return The result of multiplying the two Float objects.
/// \details This function multiplies the underlying float values of the two objects together.
auto Float::operator*(const Float& other) const -> Float {
	return Float(this->value_ * other.value_);
}

/// \brief Divide this Float object by another Float object.
/// \param other The other Float object to divide this object by.
/// \return The result of dividing the two Float objects.
/// \details This function divides the underlying float values of the two objects.
/// \throws std::overflow_error If the divisor is zero.
auto Float::operator/(const Float& other) const -> Float {
	if (other.value_ == 0.0f) {
		throw std::overflow_error("Division by zero");
	}
	return Float(this->value_ / other.value_);
}
}
