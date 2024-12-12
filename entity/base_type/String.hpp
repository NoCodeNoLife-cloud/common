// Created by author ethereal on 2024/11/29.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include <regex>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief A final class representing an immutable sequence of characters.
/// \details The String class provides a variety of methods for manipulating
/// and inspecting strings. It is a final class that cannot be inherited from.
/// The class inherits from Object and implements the Comparable interface
/// for comparing two String objects.
class String final : public Object, interface::IfaceComparable<String>
{
public:
	String();
	explicit String(const char* str);
	explicit String(std::string str);
	[[nodiscard]] auto toString() const -> std::string override;
	[[nodiscard]] auto charAt(int index) const -> char;
	[[nodiscard]] auto length() const -> size_t;
	[[nodiscard]] auto substring(int beginIndex, int endIndex) const -> String;
	[[nodiscard]] auto concat(const String& str) const -> String;
	[[nodiscard]] auto compareTo(const String& anotherString) const -> int override;
	[[nodiscard]] auto compareToIgnoreCase(const String& anotherString) const -> int;
	[[nodiscard]] auto isEmpty() const -> bool;
	[[nodiscard]] auto contains(const String& str) const -> bool;
	[[nodiscard]] auto replace(char oldChar, char newChar) const -> String;
	[[nodiscard]] auto toLowerCase() const -> String;
	[[nodiscard]] auto toUpperCase() const -> String;
	[[nodiscard]] auto trim() const -> String;
	[[nodiscard]] auto toStdString() const -> std::string;
	[[nodiscard]] auto equals(const String& other) const -> bool override;
	[[nodiscard]] auto codePointAt(int index) const -> int;
	[[nodiscard]] auto codePointBefore(int index) const -> int;
	[[nodiscard]] auto codePointCount(int beginIndex, int endIndex) const -> int;
	[[nodiscard]] auto indexOf(char ch) const -> int;
	[[nodiscard]] auto indexOf(char ch, int fromIndex) const -> int;
	[[nodiscard]] auto indexOf(const String& str) const -> int;
	[[nodiscard]] auto indexOf(const String& str, int fromIndex) const -> int;
	[[nodiscard]] auto lastIndexOf(char ch) const -> int;
	[[nodiscard]] auto lastIndexOf(char ch, int fromIndex) const -> int;
	[[nodiscard]] auto lastIndexOf(const String& str) const -> int;
	[[nodiscard]] auto lastIndexOf(const String& str, int fromIndex) const -> int;
	[[nodiscard]] auto matches(const std::string& regex) const -> bool;
	[[nodiscard]] auto replaceAll(const std::string& regex, const std::string& replacement) const -> String;
	[[nodiscard]] auto replaceFirst(const std::string& regex, const std::string& replacement) const -> String;
	[[nodiscard]] auto split(const std::string& regex) const -> std::vector<String>;
	[[nodiscard]] auto split(const std::string& regex, int limit) const -> std::vector<String>;
	static auto valueOf(bool b) -> String;
	static auto valueOf(char c) -> String;
	static auto valueOf(const char* data) -> String;
	static auto valueOf(int i) -> String;
	static auto valueOf(long l) -> String;
	static auto valueOf(float f) -> String;
	static auto valueOf(double d) -> String;
	static auto valueOf(const String& str) -> String;
	[[nodiscard]] auto regionMatches(int tOffset, const String& other, int oOffset, int len) const -> bool;
	[[nodiscard]] auto regionMatches(bool ignoreCase, int tOffset, const String& other, int oOffset, int len) const -> bool;
	auto operator==(const String& str) const -> bool;
	auto operator!=(const String& str) const -> bool;
	auto operator+(const String& str) const -> String;

private:
	friend std::formatter<String>;
	std::string data_{};
};
}

template <> struct std::formatter<common::entity::base_type::String>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::String& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the String class.
 *
 * This function parses the format specifiers for the String class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::String>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the String object into a string.
 *
 * This function formats the String object using the provided format context.
 * It generates a string representation of the String object.
 *
 * \param content The String object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::String>::format(const common::entity::base_type::String& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "String{{data: {}}}", content.data_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::String& content) -> std::ostream& {
	return os << std::format("{}", content);
}
