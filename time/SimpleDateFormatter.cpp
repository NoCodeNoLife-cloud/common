// Created by author ethereal on 2024/11/30.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "SimpleDateFormatter.hpp"
#include <iomanip>
#include <sstream>

namespace common::util::time
{
/// \brief Constructs a SimpleDateFormatter with the specified pattern.
/// \param pattern The date-time pattern string used for formatting and parsing.
/// \throws std::invalid_argument If the provided pattern is empty.
/// \details This constructor initializes the SimpleDateFormatter with the given pattern,
/// validating it to ensure it's not empty. The pattern is used in format and parse operations
/// to specify the desired date-time format.
SimpleDateFormatter::SimpleDateFormatter(const std::string& pattern) {
	validatePattern(pattern);
	this->pattern = pattern;
}

/// \brief Applies the specified pattern to the date-time formatter.
/// \param newPattern The new date-time pattern string to use for formatting and parsing.
/// \throws std::invalid_argument If the provided pattern is empty.
/// \details This function applies the specified pattern to the formatter, validating it to ensure it's not empty.
/// This will change the format and parser used by the SimpleDateFormatter to the new pattern.
auto SimpleDateFormatter::applyPattern(const std::string& newPattern) -> void {
	validatePattern(newPattern);
	this->pattern = newPattern;
}

/// \brief Returns the current date-time pattern used by the formatter.
/// \return The current date-time pattern used by the formatter.
/// \details This function returns the current date-time pattern used by the formatter.
/// This is the pattern that is used in both the format and parse operations.
auto SimpleDateFormatter::toPattern() const -> std::string {
	return this->pattern;
}

/// \brief Formats a date according to the current pattern.
/// \param date The date to format, represented as a std::tm structure.
/// \return A string representing the formatted date.
/// \throws std::runtime_error If there is an error during formatting.
/// \details This function formats the given date using the current date-time pattern.
/// It uses the std::put_time function to format the date into a string. If formatting
/// fails, a std::runtime_error is thrown with a descriptive error message.
auto SimpleDateFormatter::format(const std::tm& date) const -> std::string {
	std::ostringstream oss;
	try {
		oss << std::put_time(&date, pattern.c_str());
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Error formatting date: " + std::string(e.what()));
	}
	return oss.str();
}

/// \brief Parses a date-time string into a std::tm structure using the current pattern.
/// \param dateStr The date-time string to parse.
/// \return A std::tm structure representing the parsed date.
/// \throws std::runtime_error If there is an error during parsing.
/// \details This function parses the given date-time string using the current date-time pattern.
/// It uses the std::get_time function to parse the string into a std::tm structure. If parsing
/// fails, a std::runtime_error is thrown with a descriptive error message.
auto SimpleDateFormatter::parse(const std::string& dateStr) const -> std::tm {
	std::istringstream iss(dateStr);
	std::tm date = {};
	try {
		iss >> std::get_time(&date, pattern.c_str());
		if (iss.fail()) {
			throw std::runtime_error("Failed to parse date: " + dateStr);
		}
	}
	catch (const std::exception& e) {
		throw std::runtime_error("Error parsing date: " + std::string(e.what()));
	}
	return date;
}

/// \brief Compares this formatter with another formatter for equality.
/// \param other The formatter to compare with.
/// \return true if the formatters are equal, false otherwise.
/// \details This function compares the current formatter with another formatter for equality.
/// Two formatters are considered equal if their patterns are equal.
auto SimpleDateFormatter::equals(const SimpleDateFormatter& other) const -> bool {
	return this->pattern == other.pattern;
}

/// \brief Returns the hash code of this formatter.
/// \return The hash code of this formatter.
/// \details This function returns the hash code of this formatter. The hash code is
/// based on the pattern string used by the formatter.
auto SimpleDateFormatter::hashCode() const -> size_t {
	// A simple hash function for demonstration purposes.
	return std::hash<std::string>{}(this->pattern);
}

/// \brief Validates the provided date-time pattern.
/// \param pat The date-time pattern string to validate.
/// \throws std::invalid_argument If the provided pattern is empty.
/// \details This function validates the provided date-time pattern to ensure it is not empty.
/// If the pattern is empty, it throws an std::invalid_argument exception. In a complete implementation,
/// additional checks should be included to verify the pattern's correctness according to date-time formatting rules.
auto SimpleDateFormatter::validatePattern(const std::string& pat) -> void {
	// Only a simple validation for illustration. In a full implementation,
	// more thorough checks are necessary to ensure pattern correctness.
	if (pat.empty()) {
		throw std::invalid_argument("Pattern cannot be empty.");
	}
}
}
