// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Double.hpp"
#include <string>

namespace common::entity::base_type
{
Double::Double(const double value) : value_(value) {}

Double::~Double() = default;

/// \brief Cast the object to a double.
/// \return The underlying double value.
/// \details This function simply returns the underlying double value.
Double::operator double() const {
	return value_;
}

/// \brief Returns a string representation of the object.
/// \return A string representing the object's type name.
/// \details This function uses `typeid` to retrieve the name of the object's type.
std::string Double::toString() const {
	return std::format("{}", *this);
}

/// \brief Check if the object is equal to another object
/// \param other The other object
/// \return True if the objects are equal
/// \details This function checks if the object is equal to another object.
/// The function first checks if the objects are of the same type, and if so,
/// it compares the underlying double values directly. Otherwise, it returns
/// false.
bool Double::equals(const Double& other) const {
	return value_ == other.value_;
}

/// \brief Compare this Double object with another.
/// \param other The Double object to compare with.
/// \return An integer less than, equal to, or greater than zero if this object
/// is considered to be respectively less than, equal to, or greater than the specified object.
/// \details This function compares the underlying double values directly.
auto Double::compareTo(const Double& other) const -> int {
	return (value_ > other.value_) - (value_ < other.value_);
}

/// \brief Returns the underlying double value.
/// \return The underlying double value.
/// \details This function simply returns the underlying double value.
auto Double::doubleValue() const -> double {
	return value_;
}

/// \brief Parse a double value from a string.
/// \param str The string to parse.
/// \return A Double object representing the parsed value.
/// \throws std::invalid_argument If the string is not a valid double.
/// \throws std::out_of_range If the parsed value is out of range for a double.
auto Double::parseDouble(const std::string& str) -> Double {
	try {
		const double result = std::stod(str);
		return Double(result);
	}
	catch (const std::invalid_argument&) {
		throw std::invalid_argument("Invalid input string for Double conversion");
	} catch (const std::out_of_range&) {
		throw std::out_of_range("Value out of range for Double");
	}
}

/// \brief Check if this Double object is equal to another Double object.
/// \param other The Double object to compare with.
/// \return True if the Double objects are equal, false otherwise.
/// \details This function checks if the underlying double values are equal
/// by utilizing the Equals method.
auto Double::operator==(const Double& other) const -> bool {
	return value_ == other.value_;
}

/// \brief Check if this Double object is not equal to another Double object.
/// \param other The Double object to compare with.
/// \return True if the Double objects are not equal, false otherwise.
/// \details This function checks if the underlying double values are not equal
/// by utilizing the Equals method.
auto Double::operator!=(const Double& other) const -> bool {
	return value_ != other.value_;
}

/// \brief Check if this Double object is less than another Double object.
/// \param other The Double object to compare with.
/// \return True if this object is less than the other object, false otherwise.
/// \details This function checks if the underlying double values are less than
/// by utilizing the CompareTo method.
auto Double::operator<(const Double& other) const -> bool {
	return value_ < other.value_;
}

/// \brief Check if this Double object is greater than another Double object.
/// \param other The Double object to compare with.
/// \return True if this object is greater than the other object, false otherwise.
/// \details This function checks if the underlying double value is greater than
/// the value of the other Double object.
auto Double::operator>(const Double& other) const -> bool {
	return value_ > other.value_;
}

/// \brief Check if this Double object is less than or equal to another Double object.
/// \param other The Double object to compare with.
/// \return True if this object is less than or equal to the other object, false otherwise.
/// \details This function checks if the underlying double values are less than or equal to
/// by utilizing the CompareTo method.
auto Double::operator<=(const Double& other) const -> bool {
	return value_ <= other.value_;
}

/// \brief Check if this Double object is greater than or equal to another Double object.
/// \param other The Double object to compare with.
/// \return True if this object is greater than or equal to the other object, false otherwise.
/// \details This function checks if the underlying double values are greater than or equal to
/// the value of the other Double object.
auto Double::operator>=(const Double& other) const -> bool {
	return value_ >= other.value_;
}

/// \brief Adds two Double objects.
/// \param other The Double object to add.
/// \return A Double object with the result of the addition.
/// \details This function adds the underlying double values of the two Double objects.
auto Double::operator+(const Double& other) const -> Double {
	return Double(this->value_ + other.value_);
}

/// \brief Subtracts two Double objects.
/// \param other The Double object to subtract.
/// \return A Double object with the result of the subtraction.
/// \details This function subtracts the underlying double values of the two Double objects.
auto Double::operator-(const Double& other) const -> Double {
	return Double(this->value_ - other.value_);
}

/// \brief Multiplies two Double objects.
/// \param other The Double object to multiply with.
/// \return A Double object with the result of the multiplication.
/// \details This function multiplies the underlying double values of the two Double objects.
auto Double::operator*(const Double& other) const -> Double {
	return Double(this->value_ * other.value_);
}

/// \brief Divides two Double objects.
/// \param other The Double object to divide with.
/// \return A Double object with the result of the division.
/// \details This function divides the underlying double values of the two Double objects.
/// \throws std::overflow_error If the divisor is zero.
auto Double::operator/(const Double& other) const -> Double {
	if (other.value_ == 0.0) {
		throw std::overflow_error("Division by zero");
	}
	return Double(this->value_ / other.value_);
}
}
