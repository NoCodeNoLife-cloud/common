// Created by author ethereal on 2024/11/29.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "String.hpp"
#include <algorithm>
#include <utility>

namespace common::entity::base_type
{
String::String() = default;

String::String(const char* str) : data_(str) {}

String::String(std::string str) : data_(std::move(str)) {}

/// \brief Get the character at the specified index.
/// \param index The index of the character to retrieve.
/// \return The character at the specified index.
/// \throws std::out_of_range If the index is out of bounds.
auto String::charAt(const int index) const -> char {
	if (index < 0 || index >= data_.size()) throw std::out_of_range("Index out of bounds");
	return data_[index];
}

/// \brief Get the length of the string.
/// \return The number of characters in the string.
auto String::length() const -> size_t {
	return data_.size();
}

/// \brief Retrieve a substring from the String object.
/// \param beginIndex The starting index, inclusive, of the substring.
/// \param endIndex The ending index, exclusive, of the substring.
/// \return A new String object containing the specified substring.
/// \throws std::out_of_range If the beginIndex or endIndex is out of bounds or if beginIndex is greater than endIndex.
auto String::substring(const int beginIndex, const int endIndex) const -> String {
	if (beginIndex < 0 || endIndex > data_.size() || beginIndex > endIndex) throw std::out_of_range("Invalid range");
	return String(data_.substr(beginIndex, endIndex - beginIndex));
}

/// \brief Concatenate the specified string to the end of this String object.
/// \param str The string to be concatenated.
/// \return A new String object that is the result of the concatenation.
auto String::concat(const String& str) const -> String {
	return String(data_ + str.data_);
}

/// \brief Compare this String object with the specified String object.
/// \param anotherString The String object to be compared with.
/// \return An integer indicating the result of the comparison.
/// \details The result is negative if this String object is lexicographically less than the specified String object,
/// zero if the strings are equal, and positive if this String object is lexicographically greater than the specified
/// String object.
auto String::compareTo(const String& anotherString) const -> int {
	return data_.compare(anotherString.data_);
}

/// \brief Compare this String object with the specified String object, ignoring the case of the strings.
/// \param anotherString The String object to be compared with.
/// \return An integer indicating the result of the comparison.
/// \details The result is negative if this String object is lexicographically less than the specified String object,
/// zero if the strings are equal, and positive if this String object is lexicographically greater than the specified
/// String object.
/// \details The comparison is done in a case-insensitive manner.
auto String::compareToIgnoreCase(const String& anotherString) const -> int {
	std::string lower1 = data_, lower2 = anotherString.data_;
	std::ranges::transform(lower1, lower1.begin(), tolower);
	std::ranges::transform(lower2, lower2.begin(), tolower);
	return lower1.compare(lower2);
}

/// \brief Check if the string is empty.
/// \return True if the string has no characters, false otherwise.
auto String::isEmpty() const -> bool {
	return data_.empty();
}

/// \brief Check if the string contains the specified string.
/// \param str The string to be searched for.
/// \return True if the string contains the specified string, false otherwise.
auto String::contains(const String& str) const -> bool {
	return data_.find(str.data_) != std::string::npos;
}

/// \brief Replace all occurrences of the specified character with the specified replacement character.
/// \param oldChar The character to be replaced.
/// \param newChar The character to replace with.
/// \return A new String object with all occurrences of the specified character replaced with the specified replacement
/// character.
auto String::replace(const char oldChar, const char newChar) const -> String {
	std::string result = data_;
	std::ranges::replace(result, oldChar, newChar);
	return String(result);
}

/// \brief Convert the string to lowercase.
/// \return A new String object containing the lowercase of the string.
auto String::toLowerCase() const -> String {
	std::string lower = data_;
	std::ranges::transform(lower, lower.begin(), tolower);
	return String(lower);
}

/// \brief Convert the string to uppercase.
/// \return A new String object containing the uppercase of the string.
auto String::toUpperCase() const -> String {
	std::string upper = data_;
	std::ranges::transform(upper, upper.begin(), toupper);
	return String(upper);
}

/// \brief Remove leading and trailing whitespace from the string.
/// \return A new String object with all leading and trailing whitespace removed.
auto String::trim() const -> String {
	const size_t start = data_.find_first_not_of(" \t\n\r");
	const size_t end = data_.find_last_not_of(" \t\n\r");
	if (start == std::string::npos) return String("");
	return String(data_.substr(start, end - start + 1));
}

/// \brief Get the underlying std::string of the String object.
/// \return The underlying std::string of the String object.
auto String::toStdString() const -> std::string {
	return data_;
}

/// \brief Compare this String object with the specified String object.
/// \param other The String object to compare with.
/// \return True if the strings are equal, false otherwise.
auto String::equals(const String& other) const -> bool {
	return data_ == other.data_;
}

/// \brief Get the Unicode code point at the specified index.
/// \param index The index of the code point to retrieve.
/// \return The Unicode code point at the specified index.
/// \throws std::out_of_range If the index is out of bounds.
auto String::codePointAt(const int index) const -> int {
	if (index < 0 || index >= data_.size()) throw std::out_of_range("Index out of bounds");
	return data_[index];
}

/// \brief Get the Unicode code point before the specified index.
/// \param index The index of the code point to retrieve.
/// \return The Unicode code point before the specified index.
/// \throws std::out_of_range If the index is out of bounds.
auto String::codePointBefore(const int index) const -> int {
	if (index <= 0 || index > data_.size()) throw std::out_of_range("Index out of bounds");
	return data_[index - 1];
}

/// \brief Get the number of Unicode code points in the given range.
/// \param beginIndex The starting index, inclusive, of the range.
/// \param endIndex The ending index, exclusive, of the range.
/// \return The number of Unicode code points in the given range.
/// \throws std::out_of_range If the range is invalid (i.e. beginIndex < 0, endIndex > data.size(), or beginIndex >
/// endIndex).
auto String::codePointCount(const int beginIndex, const int endIndex) const -> int {
	if (beginIndex < 0 || endIndex > data_.size() || beginIndex > endIndex) throw std::out_of_range("Invalid range");
	return endIndex - beginIndex;
}

/// \brief Find the index of the first occurrence of the specified character.
/// \param ch The character to search for.
/// \return The index of the first occurrence of the specified character, or -1 if not found.
auto String::indexOf(const char ch) const -> int {
	const auto pos = data_.find(ch);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

/// \brief Find the index of the first occurrence of the specified character, starting from the specified index.
/// \param ch The character to search for.
/// \param fromIndex The starting index, inclusive, of the search.
/// \return The index of the first occurrence of the specified character, or -1 if not found.
auto String::indexOf(const char ch, const int fromIndex) const -> int {
	if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
	const auto pos = data_.find(ch, fromIndex);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

/// \brief Find the index of the first occurrence of the specified string.
/// \param str The string to search for.
/// \return The index of the first occurrence of the specified string, or -1 if not found.
auto String::indexOf(const String& str) const -> int {
	const auto pos = data_.find(str.data_);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

/// \brief Find the index of the first occurrence of the specified string, starting from the specified index.
/// \param str The string to search for.
/// \param fromIndex The starting index, inclusive, of the search.
/// \return The index of the first occurrence of the specified string, or -1 if not found.
auto String::indexOf(const String& str, const int fromIndex) const -> int {
	if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
	const auto pos = data_.find(str.data_, fromIndex);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

/// \brief Find the index of the last occurrence of the specified character.
/// \param ch The character to search for.
/// \return The index of the last occurrence of the specified character, or -1 if not found.
auto String::lastIndexOf(const char ch) const -> int {
	const auto pos = data_.rfind(ch);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

/// \brief Find the index of the last occurrence of the specified character, starting from the specified index.
/// \param ch The character to search for.
/// \param fromIndex The starting index, inclusive, of the search.
/// \return The index of the last occurrence of the specified character, or -1 if not found.
auto String::lastIndexOf(const char ch, const int fromIndex) const -> int {
	if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
	const auto pos = data_.rfind(ch, fromIndex);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

/// \brief Find the index of the last occurrence of the specified string.
/// \param str The string to search for.
/// \return The index of the last occurrence of the specified string, or -1 if not found.
auto String::lastIndexOf(const String& str) const -> int {
	const auto pos = data_.rfind(str.data_);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

/// \brief Find the index of the last occurrence of the specified string, starting from the specified index.
/// \param str The string to search for.
/// \param fromIndex The starting index, inclusive, of the search.
/// \return The index of the last occurrence of the specified string, or -1 if not found.
/// \throws std::out_of_range If the fromIndex is out of bounds.
auto String::lastIndexOf(const String& str, const int fromIndex) const -> int {
	if (fromIndex < 0 || fromIndex >= data_.size()) throw std::out_of_range("Index out of bounds");
	const auto pos = data_.rfind(str.data_, fromIndex);
	return pos == std::string::npos ? -1 : static_cast<int>(pos);
}

/// \brief Test if the string matches the specified regular expression.
/// \param regex The regular expression to match against.
/// \return True if the string matches the regular expression, false otherwise.
auto String::matches(const std::string& regex) const -> bool {
	return std::regex_match(data_, std::regex(regex));
}

/// \brief Replace all occurrences of the specified regular expression with the specified replacement string.
/// \param regex The regular expression to match against.
/// \param replacement The string to replace with.
/// \return A new String object with all occurrences of the regular expression replaced with the specified replacement
/// string.
auto String::replaceAll(const std::string& regex, const std::string& replacement) const -> String {
	return String(std::regex_replace(data_, std::regex(regex), replacement));
}

/// \brief Replace the first occurrence of the specified regular expression with the specified replacement string.
/// \param regex The regular expression to match against.
/// \param replacement The string to replace with.
/// \return A new String object with the first occurrence of the regular expression replaced with the specified
/// replacement string.
auto String::replaceFirst(const std::string& regex, const std::string& replacement) const -> String {
	const std::regex re(regex);
	std::string result = data_;
	if (std::smatch match; std::regex_search(result, match, re)) {
		result.replace(match.position(0), match.length(0), replacement);
	}
	return String(result);
}

/// \brief Split the string into a vector of strings using the specified regular expression.
/// \param regex The regular expression to split against.
/// \return A vector of strings, split by the regular expression.
auto String::split(const std::string& regex) const -> std::vector<String> {
	const std::regex re(regex);
	std::sregex_token_iterator it(data_.begin(), data_.end(), re, -1);
	const std::sregex_token_iterator end;
	std::vector<String> result;
	while (it != end) {
		result.emplace_back(*it++);
	}
	return result;
}

/// \brief Split the string into a vector of strings using the specified regular expression.
/// \param regex The regular expression to split against.
/// \param limit The maximum number of strings to split into. If 0 or negative, splits into all possible strings.
/// \return A vector of strings, split by the regular expression.
auto String::split(const std::string& regex, const int limit) const -> std::vector<String> {
	const std::regex re(regex);
	std::sregex_token_iterator it(data_.begin(), data_.end(), re, -1);
	const std::sregex_token_iterator end;
	std::vector<String> result;
	while (it != end && (limit <= 0 || result.size() < static_cast<size_t>(limit - 1))) {
		result.emplace_back(*it++);
	}
	if (limit > 0 && it != end) {
		result.emplace_back(std::string(it->first, data_.end()));
	}
	return result;
}

/// \brief Returns a String object representing the specified boolean.
/// \param b The boolean to create a String object for.
/// \return A String object representing the specified boolean.
auto String::valueOf(const bool b) -> String {
	return String(b ? "true" : "false");
}

/// \brief Returns a String object representing the specified character.
/// \param c The character to create a String object for.
/// \return A String object representing the specified character.
auto String::valueOf(const char c) -> String {
	return String(std::string(1, c));
}

/// \brief Returns a String object representing the specified character array.
/// \param data The character array to create a String object for.
/// \return A String object representing the specified character array.
auto String::valueOf(const char* data) -> String {
	return String(data);
}

/// \brief Returns a String object representing the specified integer.
/// \param i The integer to create a String object for.
/// \return A String object representing the specified integer.
auto String::valueOf(const int i) -> String {
	return String(std::to_string(i));
}

/// \brief Returns a String object representing the specified long integer.
/// \param l The long integer to create a String object for.
/// \return A String object representing the specified long integer.
auto String::valueOf(const long l) -> String {
	return String(std::to_string(l));
}

/// \brief Returns a String object representing the specified float.
/// \param f The float to create a String object for.
/// \return A String object representing the specified float.
auto String::valueOf(const float f) -> String {
	return String(std::to_string(f));
}

/// \brief Returns a String object representing the specified double.
/// \param d The double to create a String object for.
/// \return A String object representing the specified double.
auto String::valueOf(const double d) -> String {
	return String(std::to_string(d));
}

/// \brief Returns a String object representing the specified String object.
/// \param str The String object to create a String object for.
/// \return A String object representing the specified String object.
auto String::valueOf(const String& str) -> String {
	return str;
}

/// \brief Tests if two string regions are equal.
/// \param tOffset The starting offset of the subregion in this string.
/// \param other The string to be compared with.
/// \param oOffset The starting offset of the subregion in the given string.
/// \param len The number of characters to compare.
/// \return True if the specified subregion of this string is equal to the specified subregion of the given string,
/// false otherwise.
auto String::regionMatches(const int tOffset, const String& other, const int oOffset, const int len) const -> bool {
	if (tOffset < 0 || oOffset < 0 || tOffset + len > data_.size() || oOffset + len > other.data_.size()) {
		return false;
	}
	return data_.compare(tOffset, len, other.data_, oOffset, len) == 0;
}

/// \brief Tests if two string regions are equal.
/// \param ignoreCase True if the case should be ignored, false otherwise.
/// \param tOffset The starting offset of the subregion in this string.
/// \param other The string to be compared with.
/// \param oOffset The starting offset of the subregion in the given string.
/// \param len The number of characters to compare.
/// \return True if the specified subregion of this string is equal to the specified subregion of the given string,
/// false otherwise.
auto String::regionMatches(const bool ignoreCase, const int tOffset, const String& other, const int oOffset, const int len) const -> bool {
	if (!ignoreCase) return regionMatches(tOffset, other, oOffset, len);
	std::string thisRegion = data_.substr(tOffset, len);
	std::string otherRegion = other.data_.substr(oOffset, len);
	std::ranges::transform(thisRegion, thisRegion.begin(), tolower);
	std::ranges::transform(otherRegion, otherRegion.begin(), tolower);
	return thisRegion == otherRegion;
}

/// \brief Check if this String object is equal to the specified String object.
/// \param str The String object to compare with.
/// \return True if the strings are equal, false otherwise.
auto String::operator==(const String& str) const -> bool {
	return equals(str);
}

/// \brief Check if this String object is not equal to the specified String object.
/// \param str The String object to compare with.
/// \return True if the strings are not equal, false otherwise.
auto String::operator!=(const String& str) const -> bool {
	return !equals(str);
}

/// \brief Concatenate this String object with another String object.
/// \param str The String object to be added.
/// \return A new String object that is the result of the concatenation.
auto String::operator+(const String& str) const -> String {
	return this->concat(str);
}

/// \brief Get the string representation of the String object.
/// \return The string representation of the String object.
auto String::toString() const -> std::string {
	return std::format("{}", *this);
}
}
