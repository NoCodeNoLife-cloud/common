// Created by author ethereal on 2024/11/30.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <ctime>
#include <string>

namespace common::util::time
{
/// \class SimpleDateFormatter
/// \brief A class for formatting dates into a string according to a given pattern.
///
/// This class is a simple implementation of a date formatter. It is a subclass of
/// the Object class and implements the Comparable interface. It provides a way
/// to format dates into strings with a given pattern. The pattern is specified
/// in the constructor and can be changed by calling the applyPattern() method.
///
/// The class provides two methods for formatting dates: the format() method takes
/// a tm object as a parameter and returns a string representing the date in the
/// given pattern. The parse() method takes a string parameter and returns a tm
/// object representing the date in the string.
class SimpleDateFormatter
{
public:
	explicit SimpleDateFormatter(const std::string& pattern);
	auto applyPattern(const std::string& newPattern) -> void;
	[[nodiscard]] auto toPattern() const -> std::string;
	[[nodiscard]] auto format(const std::tm& date) const -> std::string;
	[[nodiscard]] auto parse(const std::string& dateStr) const -> std::tm;
	[[nodiscard]] auto equals(const SimpleDateFormatter& other) const -> bool;
	[[nodiscard]] auto hashCode() const -> size_t;

private:
	std::string pattern;
	static void validatePattern(const std::string& pat);
};
}
