// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include <string>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief A wrapper class for primitive type int.
/// \details This class provides a way to treat int as a generic object.
/// It is used to represent an immutable signed 32-bit integer.
class Integer final : public Object, public interface::IfaceComparable<Integer>
{
public:
	static constexpr int MIN_VALUE = std::numeric_limits<int>::min();
	static constexpr int MAX_VALUE = std::numeric_limits<int>::max();
	explicit Integer(int value = 0);
	~Integer() override;
	explicit operator int() const;
	[[nodiscard]] auto toString() const -> std::string override;
	[[nodiscard]] auto intValue() const -> int;
	static auto parseInt(const std::string& str) -> Integer;
	[[nodiscard]] auto compareTo(const Integer& other) const -> int override;
	[[nodiscard]] auto equals(const Integer& other) const -> bool override;
	auto operator==(const Integer& other) const -> bool;
	auto operator!=(const Integer& other) const -> bool;
	auto operator<(const Integer& other) const -> bool;
	auto operator>(const Integer& other) const -> bool;
	auto operator<=(const Integer& other) const -> bool;
	auto operator>=(const Integer& other) const -> bool;
	auto operator+(const Integer& other) const -> Integer;
	auto operator-(const Integer& other) const -> Integer;
	auto operator*(const Integer& other) const -> Integer;
	auto operator/(const Integer& other) const -> Integer;

private:
	friend std::formatter<Integer>;
	int value_{0};
};
}

template <> struct std::formatter<common::entity::base_type::Integer>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Integer& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Integer class.
 *
 * This function parses the format specifiers for the Integer class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::Integer>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Integer object into a string.
 *
 * This function formats the Integer object using the provided format context.
 * It generates a string representation of the Integer object.
 *
 * \param content The Integer object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::Integer>::format(const common::entity::base_type::Integer& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "{}", content.value_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Integer& content) -> std::ostream& {
	return os << std::format("{}", content);
}
