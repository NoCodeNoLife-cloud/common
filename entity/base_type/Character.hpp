// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief A class representing a Character object.
/// \details This class is a part of the common library and represents a Character object.
/// It provides various methods for manipulating and comparing the Character object.
/// It is a final class and cannot be inherited.
class Character final : public Object, public interface::IfaceComparable<Character>
{
public:
	explicit Character(char value = '\0');
	~Character() override;
	explicit operator char() const;
	[[nodiscard]] auto toString() const -> std::string override;
	[[nodiscard]] auto equals(const Character& other) const -> bool override;
	[[nodiscard]] auto compareTo(const Character& other) const -> int override;
	[[nodiscard]] auto characterValue() const -> char;
	static auto isLetter(char c) -> bool;
	static auto isDigit(char c) -> bool;
	static auto isLetterOrDigit(char c) -> bool;
	static auto isUpperCase(char c) -> bool;
	static auto isLowerCase(char c) -> bool;
	static auto toUpperCase(char c) -> int;
	static auto toLowerCase(char c) -> int;
	auto operator==(const Character& other) const -> bool;
	auto operator!=(const Character& other) const -> bool;
	auto operator<(const Character& other) const -> bool;
	auto operator>(const Character& other) const -> bool;
	auto operator<=(const Character& other) const -> bool;
	auto operator>=(const Character& other) const -> bool;

private:
	friend std::formatter<Character>;
	char value_{0};
};
}

template <> struct std::formatter<common::entity::base_type::Character>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Character& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Character class.
 *
 * This function parses the format specifiers for the Character class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::Character>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Character object into a string.
 *
 * This function formats the Character object using the provided format context.
 * It generates a string representation of the Character object.
 *
 * \param content The Character object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::Character>::format(const common::entity::base_type::Character& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "{}", content.value_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Character& content) -> std::ostream& {
	return os << std::format("{}", content);
}
