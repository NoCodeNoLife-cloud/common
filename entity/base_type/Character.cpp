// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Character.hpp"

namespace common::entity::base_type
{
Character::Character(const char value) : value_(value) {}

Character::~Character() = default;

/// \brief Converts the Character object to a char.
/// \return The underlying char value of this Character object.
/// \details This function provides a convenient way to access the underlying
/// char value of the Character object. It is useful when you need to convert
/// a Character object to a char for use in a char-specific context.
Character::operator char() const {
	return value_;
}

/// \brief Returns a string representation of the object.
/// \return A string representing the object's type name.
/// \details This function uses `typeid` to retrieve the name of the object's type.
std::string Character::toString() const {
	return std::format("{}", *this);
}

/// \brief Check if the object is equal to another object
/// \param other The other object
/// \return True if the objects are equal
/// \details This function checks if the object is equal to another object.
/// The function first checks if the objects are of the same type, and if so,
/// it compares the underlying char values directly. Otherwise, it returns
/// false.
bool Character::equals(const Character& other) const {
	return value_ == other.value_;
}

/// \brief Compare this Character object with another.
/// \param other The Character object to compare with.
/// \return An integer less than, equal to, or greater than zero if this object
/// is considered to be respectively less than, equal to, or greater than the
/// specified object.
/// \details This function compares the underlying char values directly.
auto Character::compareTo(const Character& other) const -> int {
	return value_ - other.value_;
}

/// \brief Check if a character is a letter
/// \param c The character to check
/// \return True if the character is a letter, false otherwise
/// \details This function uses the standard library function `std::isalpha`
/// to determine if the given character is a letter.
auto Character::isLetter(const char c) -> bool {
	return std::isalpha(c);
}

/// \brief Check if a character is a digit
/// \param c The character to check
/// \return True if the character is a digit, false otherwise
/// \details This function uses the standard library function `std::isdigit`
/// to determine if the given character is a digit.
auto Character::isDigit(const char c) -> bool {
	return std::isdigit(c);
}

/// \brief Check if a character is a letter or a digit
/// \param c The character to check
/// \return True if the character is a letter or a digit, false otherwise
/// \details This function uses the standard library function `std::isalnum`
/// to determine if the given character is a letter or a digit.
auto Character::isLetterOrDigit(const char c) -> bool {
	return std::isalnum(c);
}

/// \brief Check if a character is uppercase
/// \param c The character to check
/// \return True if the character is uppercase, false otherwise
/// \details This function uses the standard library function `std::isupper`
/// to determine if the given character is uppercase.
auto Character::isUpperCase(const char c) -> bool {
	return std::isupper(c);
}

/// \brief Check if a character is lowercase
/// \param c The character to check
/// \return True if the character is lowercase, false otherwise
/// \details This function uses the standard library function `std::islower`
/// to determine if the given character is lowercase.
auto Character::isLowerCase(const char c) -> bool {
	return std::islower(c);
}

/// \brief Convert a character to uppercase
/// \param c The character to convert
/// \return The uppercase equivalent of the character
/// \details This function uses the standard library function `std::toupper`
/// to convert the given character to its uppercase form.
auto Character::toUpperCase(const char c) -> int {
	return std::toupper(c);
}

/// \brief Convert a character to lowercase
/// \param c The character to convert
/// \return The lowercase equivalent of the character
/// \details This function uses the standard library function `std::tolower`
/// to convert the given character to its lowercase form.
auto Character::toLowerCase(const char c) -> int {
	return std::tolower(c);
}

/// \brief Get the underlying character value
/// \return The underlying character value
/// \details This function returns the underlying character value of this
/// Character object.
auto Character::characterValue() const -> char {
	return value_;
}

/// \brief Check if this Character object is equal to another Character object.
/// \param other The other Character object to compare with.
/// \return True if the objects are equal, false otherwise.
/// \details This function compares the underlying char values directly.
auto Character::operator==(const Character& other) const -> bool {
	return equals(other);
}

/// \brief Check if this Character object is not equal to another Character object.
/// \param other The other Character object to compare with.
/// \return True if the objects are not equal, false otherwise.
/// \details This function compares the underlying char values directly and returns true if they are different.
auto Character::operator!=(const Character& other) const -> bool {
	return !equals(other);
}

/// \brief Check if this Character object is less than another Character object.
/// \param other The other Character object to compare with.
/// \return True if this Character object is less than the other Character object, false otherwise.
/// \details This function compares the underlying char values directly.
auto Character::operator<(const Character& other) const -> bool {
	return value_ < other.value_;
}

/// \brief Check if this Character object is greater than another Character object.
/// \param other The other Character object to compare with.
/// \return True if this Character object is greater than the other Character object, false otherwise.
/// \details This function compares the underlying char values directly.
auto Character::operator>(const Character& other) const -> bool {
	return value_ > other.value_;
}

/// \brief Check if this Character object is less than or equal to another Character object.
/// \param other The other Character object to compare with.
/// \return True if this Character object is less than or equal to the other Character object, false otherwise.
/// \details This function compares the underlying char values directly.
auto Character::operator<=(const Character& other) const -> bool {
	return value_ <= other.value_;
}

/// \brief Check if this Character object is greater than or equal to another Character object.
/// \param other The other Character object to compare with.
/// \return True if this Character object is greater than or equal to the other Character object, false otherwise.
/// \details This function compares the underlying char values directly.
auto Character::operator>=(const Character& other) const -> bool {
	return value_ >= other.value_;
}
}
