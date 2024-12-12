// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Integer.hpp"

namespace common::entity::base_type
{
Integer::Integer(const int value) : value_(value) {}

Integer::~Integer() = default;

/// \brief Convert the Integer object to a raw int value.
/// \return The underlying int value of the Integer object.
/// \details This operator allows the Integer object to be implicitly converted to an int type.
Integer::operator int() const {
	return value_;
}

/// \brief Returns a string representation of the object.
/// \return A string representing the object's type name.
/// \details This function uses `typeid` to retrieve the name of the object's type.
std::string Integer::toString() const {
	return std::format("{}", *this);
}

/// \brief Get the int value of the object.
/// \return The underlying int value of the Integer object.
/// \details This function returns the raw int value stored in the Integer object.
auto Integer::intValue() const -> int {
	return value_;
}

/// \brief Parse an integer value from a string.
/// \param str The string to parse.
/// \return An Integer object representing the parsed value.
/// \throws std::invalid_argument If the string is not a valid integer.
/// \throws std::out_of_range If the parsed value is out of range for the Integer object.
auto Integer::parseInt(const std::string& str) -> Integer {
	try {
		size_t idx;
		const int result = std::stoi(str, &idx);
		if (idx != str.size()) {
			throw std::invalid_argument("Invalid input string");
		}
		return Integer(result);
	}
	catch (const std::out_of_range&) {
		throw std::out_of_range("Value out of range");
	}
}

/// \brief Compare this Integer object with another.
/// \param other The Integer object to compare with.
/// \return An integer less than, equal to, or greater than zero if this object
/// is considered to be respectively less than, equal to, or greater than the specified object.
/// \details This function compares the underlying int values directly.
auto Integer::compareTo(const Integer& other) const -> int {
	return value_ - other.value_;
}

/// \brief Check if the object is equal to another object
/// \param other The other object
/// \return True if the objects are equal
/// \details This function checks if the object is equal to another object. The
/// function first checks if the objects are of the same type, and if so, it
/// compares the underlying int values directly. Otherwise, it returns false.
bool Integer::equals(const Integer& other) const {
	return value_ == other.value_;
}

/// \brief Check if this Integer object is equal to another Integer object.
/// \param other The other Integer object to compare with.
/// \return True if the objects are equal, false otherwise.
/// \details This function compares the underlying int values directly.
auto Integer::operator==(const Integer& other) const -> bool {
	return equals(other);
}

/// \brief Check if this Integer object is not equal to another Integer object.
/// \param other The other Integer object to compare with.
/// \return True if the objects are not equal, false otherwise.
/// \details This function compares the underlying int values directly.
auto Integer::operator!=(const Integer& other) const -> bool {
	return !equals(other);
}

/// \brief Check if this Integer object is less than another Integer object.
/// \param other The other Integer object to compare with.
/// \return True if this Integer object is less than the other Integer object, false otherwise.
/// \details This function compares the underlying int values directly.
auto Integer::operator<(const Integer& other) const -> bool {
	return value_ < other.value_;
}

/// \brief Check if this Integer object is greater than another Integer object.
/// \param other The other Integer object to compare with.
/// \return True if this Integer object is greater than the other Integer object, false otherwise.
/// \details This function compares the underlying int values directly.
auto Integer::operator>(const Integer& other) const -> bool {
	return value_ > other.value_;
}

/// \brief Check if this Integer object is less than or equal to another Integer object.
/// \param other The other Integer object to compare with.
/// \return True if this Integer object is less than or equal to the other Integer object, false otherwise.
/// \details This function compares the underlying int values directly.
auto Integer::operator<=(const Integer& other) const -> bool {
	return value_ <= other.value_;
}

/// \brief Check if this Integer object is greater than or equal to another Integer object.
/// \param other The other Integer object to compare with.
/// \return True if this Integer object is greater than or equal to the other Integer object, false otherwise.
/// \details This function compares the underlying int values directly.
auto Integer::operator>=(const Integer& other) const -> bool {
	return value_ >= other.value_;
}

/// \brief Add two Integer objects.
/// \param other The other Integer object.
/// \return A new Integer object representing the sum of this object and the other.
auto Integer::operator+(const Integer& other) const -> Integer {
	return Integer(this->value_ + other.value_);
}

/// \brief Subtract an Integer object from this object.
/// \param other The other Integer object.
/// \return A new Integer object representing the difference between this object and the other.
auto Integer::operator-(const Integer& other) const -> Integer {
	return Integer(this->value_ - other.value_);
}

/// \brief Multiply this object by another Integer object.
/// \param other The other Integer object.
/// \return A new Integer object representing the product of this object and the other.
auto Integer::operator*(const Integer& other) const -> Integer {
	return Integer(this->value_ * other.value_);
}

/// \brief Divide this object by another Integer object.
/// \param other The other Integer object.
/// \return A new Integer object representing the quotient of this object divided by the other.
/// \throws std::invalid_argument If division by zero is attempted.
auto Integer::operator/(const Integer& other) const -> Integer {
	if (other.value_ == 0) {
		throw std::invalid_argument("Division by zero is not allowed.");
	}
	return Integer(this->value_ / other.value_);
}
}
