// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief A class representing a signed 64-bit integer.
/// \details This class contains a signed 64-bit integer.
/// It is a wrapper class for the built-in type int64_t.
class Long final : public Object, public interface::IfaceComparable<Long>
{
public:
	static constexpr int64_t MAX_VALUE = std::numeric_limits<int64_t>::max();
	static constexpr int64_t MIN_VALUE = std::numeric_limits<int64_t>::min();
	explicit Long(int64_t value = 0);
	~Long() override;
	explicit operator long() const;
	[[nodiscard]] auto toString() const -> std::string override;
	[[nodiscard]] auto longValue() const -> int64_t;
	[[nodiscard]] auto equals(const Long& other) const -> bool override;
	[[nodiscard]] auto compareTo(const Long& other) const -> int override;
	static auto parseLong(const std::string& str) -> Long;
	auto operator==(const Long& other) const -> bool;
	auto operator!=(const Long& other) const -> bool;
	auto operator<(const Long& other) const -> bool;
	auto operator>(const Long& other) const -> bool;
	auto operator<=(const Long& other) const -> bool;
	auto operator>=(const Long& other) const -> bool;
	auto operator+(const Long& other) const -> Long;
	auto operator-(const Long& other) const -> Long;
	auto operator*(const Long& other) const -> Long;
	auto operator/(const Long& other) const -> Long;
	auto operator%(const Long& other) const -> Long;

private:
	friend std::formatter<Long>;
	int64_t value_{0};
};
}

template <> struct std::formatter<common::entity::base_type::Long>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Long& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Long class.
 *
 * This function parses the format specifiers for the Long class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::Long>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Long object into a string.
 *
 * This function formats the Long object using the provided format context.
 * It generates a string representation of the Long object.
 *
 * \param content The Long object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::Long>::format(const common::entity::base_type::Long& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "{}", content.value_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Long& content) -> std::ostream& {
	return os << std::format("{}", content);
}
