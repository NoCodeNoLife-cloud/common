// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Byte.hpp"
#include <string>

namespace common::entity::base_type
{
Byte::Byte(const int8_t value) : value_(value) {}

Byte::~Byte() = default;

/// \brief Convert the Byte object to a signed char.
/// \return The underlying int8_t value of the Byte object as a signed char.
/// \details This operator function allows the Byte object to be implicitly
///          converted to a signed char, providing a convenient way to access
///          the raw byte value.
Byte::operator signed char() const {
	return value_;
}

/// \brief Check if this Byte object is equal to another object.
/// \param other The other object to compare with.
/// \return True if the objects are equal, false otherwise.
/// \details This function compares the underlying byte values.
/// If the other object is not of type Byte, it returns false.
bool Byte::equals(const Byte& other) const {
	return value_ == other.value_;
}

/// \brief Compare this Byte object with another.
/// \param other The Byte object to compare with.
/// \return An integer less than, equal to, or greater than zero if this object
/// is considered to be respectively less than, equal to, or greater than the specified object.
/// \details This function compares the underlying byte values directly.
auto Byte::compareTo(const Byte& other) const -> int {
	return (value_ > other.value_) - (value_ < other.value_);
}

/// \brief Returns a string representation of the object.
/// \return A string representing the object's type name.
/// \details This function uses `typeid` to retrieve the name of the object's type.
std::string Byte::toString() const {
	return std::format("{}", *this);
}

/// \brief Get the byte value of the object.
/// \return The underlying int8_t value of the Byte object.
/// \details This function returns the raw byte value stored in the Byte object.
auto Byte::parseByte(const std::string& str) -> Byte {
	try {
		const int result = std::stoi(str);
		if (result < MIN_VALUE || result > MAX_VALUE) {
			throw std::out_of_range("Value out of range for Byte");
		}
		return Byte(static_cast<int8_t>(result));
	}
	catch (const std::invalid_argument&) {
		throw std::invalid_argument("Invalid input string for Byte conversion");
	} catch (const std::out_of_range&) {
		throw std::out_of_range("Value out of range for Byte");
	}
}

/// \brief Get the byte value of the object.
/// \return The underlying int8_t value of the Byte object.
/// \details This function returns the raw byte value stored in the Byte object.
auto Byte::byteValue() const -> int8_t {
	return value_;
}

/// \brief Check if this Byte object is equal to another Byte object.
/// \param other The other Byte object to compare with.
/// \return True if the objects are equal, false otherwise.
/// \details This function compares the underlying byte values directly.
auto Byte::operator==(const Byte& other) const -> bool {
	return equals(other);
}

/// \brief Check if this Byte object is not equal to another Byte object.
/// \param other The other Byte object to compare with.
/// \return True if the objects are not equal, false otherwise.
/// \details This function compares the underlying byte values directly.
auto Byte::operator!=(const Byte& other) const -> bool {
	return !equals(other);
}

/// \brief Check if this Byte object is less than another Byte object.
/// \param other The other Byte object to compare with.
/// \return True if this Byte object is less than the other Byte object, false otherwise.
/// \details This function compares the underlying byte values directly.
auto Byte::operator<(const Byte& other) const -> bool {
	return value_ < other.value_;
}

/// \brief Check if this Byte object is greater than another Byte object.
/// \param other The other Byte object to compare with.
/// \return True if this Byte object is greater than the other Byte object, false otherwise.
/// \details This function compares the underlying byte values directly.
auto Byte::operator>(const Byte& other) const -> bool {
	return value_ > other.value_;
}

/// \brief Check if this Byte object is less than or equal to another Byte object.
/// \param other The other Byte object to compare with.
/// \return True if this Byte object is less than or equal to the other Byte object, false otherwise.
/// \details This function compares the underlying byte values directly.
auto Byte::operator<=(const Byte& other) const -> bool {
	return value_ <= other.value_;
}

/// \brief Check if this Byte object is greater than or equal to another Byte object.
/// \param other The other Byte object to compare with.
/// \return True if this Byte object is greater than or equal to the other Byte object, false otherwise.
/// \details This function compares the underlying byte values directly.
auto Byte::operator>=(const Byte& other) const -> bool {
	return value_ >= other.value_;
}

/// \brief Add another Byte object to this one.
/// \param other The other Byte object to add.
/// \return A new Byte object with the result of the addition.
/// \details This function adds the underlying byte values directly and checks for overflow.
auto Byte::operator+(const Byte& other) const -> Byte {
	const int result = this->value_ + other.value_;
	if (result < MIN_VALUE || result > MAX_VALUE) {
		throw std::overflow_error("Byte overflow in addition");
	}
	return Byte(static_cast<int8_t>(result));
}

/// \brief Subtract another Byte object from this one.
/// \param other The other Byte object to subtract.
/// \return A new Byte object with the result of the subtraction.
/// \details This function subtracts the underlying byte values directly and checks for underflow.
auto Byte::operator-(const Byte& other) const -> Byte {
	const int result = this->value_ - other.value_;
	if (result < MIN_VALUE || result > MAX_VALUE) {
		throw std::overflow_error("Byte overflow in subtraction");
	}
	return Byte(static_cast<int8_t>(result));
}
}
