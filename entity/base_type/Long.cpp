// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Long.hpp"
#include <string>

namespace common::entity::base_type
{
Long::Long(const int64_t value) : value_(value) {}

Long::~Long() = default;

/// \brief Get the long value of the object.
/// \return The underlying int64_t value of the Long object.
/// \details This function returns the raw long value stored in the Long object.
Long::operator long() const {
	return static_cast<long>(value_);
}

/// \brief Returns a string representation of the object.
/// \return A string representing the object's type name.
/// \details This function uses `typeid` to retrieve the name of the object's type.
std::string Long::toString() const {
	return std::format("{}", *this);
}

/// \brief Get the long value of the object.
/// \return The underlying int64_t value of the Long object.
/// \details This function returns the raw long value stored in the Long object.
auto Long::longValue() const -> int64_t {
	return value_;
}

/// \brief Check if the object is equal to another object
/// \param other The other object
/// \return True if the objects are equal
/// \details This function checks if the object is equal to another object. The
/// function first checks if the objects are of the same type, and if so, it
/// compares the underlying int64_t values directly. Otherwise, it returns false.
bool Long::equals(const Long& other) const {
	return value_ == other.value_;
}

/// \brief Compare this Long object with another.
/// \param other The Long object to compare with.
/// \return An integer less than, equal to, or greater than zero if this object
/// is considered to be respectively less than, equal to, or greater than the specified object.
/// \details This function compares the underlying int64_t values directly.
auto Long::compareTo(const Long& other) const -> int {
	return (value_ > other.value_) - (value_ < other.value_);
}

/// \brief Parse a long value from a string.
/// \param str The string to parse.
/// \return A Long object representing the parsed value.
/// \throws std::invalid_argument If the string is not a valid long.
/// \throws std::out_of_range If the parsed value is out of range for the Long object.
/// \details This function parses the string using `std::stoll`.
auto Long::parseLong(const std::string& str) -> Long {
	try {
		const int64_t result = std::stoll(str);
		return Long(result);
	}
	catch (const std::invalid_argument&) {
		throw std::invalid_argument("Invalid input string for Long conversion");
	} catch (const std::out_of_range&) {
		throw std::out_of_range("Value out of range for Long");
	}
}

/// \brief Check if this Long object is equal to another.
/// \param other The Long object to compare with.
/// \return True if the two objects are equal, false otherwise.
/// \details This function checks if the two objects are equal by comparing their underlying int64_t values directly.
auto Long::operator==(const Long& other) const -> bool {
	return equals(other);
}

/// \brief Check if this Long object is not equal to another.
/// \param other The Long object to compare with.
/// \return True if the two objects are not equal, false otherwise.
/// \details This function checks if the two objects are not equal by comparing their underlying int64_t values
/// directly.
auto Long::operator!=(const Long& other) const -> bool {
	return !equals(other);
}

/// \brief Check if this Long object is less than another.
/// \param other The Long object to compare with.
/// \return True if this object is less than the other object, false otherwise.
/// \details This function checks if the underlying int64_t values are in order.
auto Long::operator<(const Long& other) const -> bool {
	return value_ < other.value_;
}

/// \brief Check if this Long object is greater than another.
/// \param other The Long object to compare with.
/// \return True if this object is greater than the other object, false otherwise.
/// \details This function checks if the underlying int64_t values are in order.
auto Long::operator>(const Long& other) const -> bool {
	return value_ > other.value_;
}

/// \brief Check if this Long object is less than or equal to another.
/// \param other The Long object to compare with.
/// \return True if this object is less than or equal to the other object, false otherwise.
/// \details This function checks if the underlying int64_t values are in order.
auto Long::operator<=(const Long& other) const -> bool {
	return value_ <= other.value_;
}

/// \brief Check if this Long object is greater than or equal to another.
/// \param other The Long object to compare with.
/// \return True if this object is greater than or equal to the other object, false otherwise.
/// \details This function checks if the underlying int64_t values are in order.
auto Long::operator>=(const Long& other) const -> bool {
	return value_ >= other.value_;
}

/// \brief Add another Long object to this Long object.
/// \param other The Long object to add.
/// \return A new Long object with the result of the addition.
/// \details This function adds the underlying int64_t values directly.
auto Long::operator+(const Long& other) const -> Long {
	return Long(this->value_ + other.value_);
}

/// \brief Subtract another Long object from this Long object.
/// \param other The Long object to subtract.
/// \return A new Long object with the result of the subtraction.
/// \details This function subtracts the underlying int64_t values directly.
auto Long::operator-(const Long& other) const -> Long {
	return Long(this->value_ - other.value_);
}

/// \brief Multiply another Long object with this Long object.
/// \param other The Long object to multiply with.
/// \return A new Long object with the result of the multiplication.
/// \details This function multiplies the underlying int64_t values directly.
auto Long::operator*(const Long& other) const -> Long {
	return Long(this->value_ * other.value_);
}

/// \brief Divide this Long object by another Long object.
/// \param other The Long object to divide by.
/// \return A new Long object with the result of the division.
/// \details This function divides the underlying int64_t values directly.
/// \throws std::overflow_error If the divisor is zero.
auto Long::operator/(const Long& other) const -> Long {
	if (other.value_ == 0) {
		throw std::overflow_error("Division by zero");
	}
	return Long(this->value_ / other.value_);
}

/// \brief Compute the remainder of this Long object divided by another Long object.
/// \param other The Long object to compute the remainder with.
/// \return A new Long object with the result of the modulo operation.
/// \details This function computes the remainder of the underlying int64_t values directly.
/// \throws std::overflow_error If the divisor is zero.
auto Long::operator%(const Long& other) const -> Long {
	if (other.value_ == 0) {
		throw std::overflow_error("Modulo by zero");
	}
	return Long(this->value_ % other.value_);
}
}
