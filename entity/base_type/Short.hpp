// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief Class Short is a type of Object that represents a signed short value.
/// \details Class Short is a type of Object that represents a signed short value.
/// It is a final class that cannot be inherited from.
class Short final : public Object, public interface::IfaceComparable<Short>
{
public:
	static constexpr int16_t MAX_VALUE = std::numeric_limits<int16_t>::max();
	static constexpr int16_t MIN_VALUE = std::numeric_limits<int16_t>::min();
	explicit Short(int16_t value = 0);
	~Short() override;
	explicit operator short() const;
	[[nodiscard]] auto toString() const -> std::string override;
	[[nodiscard]] auto shortValue() const -> int16_t;
	[[nodiscard]] auto equals(const Short& other) const -> bool override;
	[[nodiscard]] auto compareTo(const Short& other) const -> int override;
	static auto parseShort(const std::string& str) -> Short;
	auto operator==(const Short& other) const -> bool;
	auto operator!=(const Short& other) const -> bool;
	auto operator<(const Short& other) const -> bool;
	auto operator>(const Short& other) const -> bool;
	auto operator<=(const Short& other) const -> bool;
	auto operator>=(const Short& other) const -> bool;
	auto operator+(const Short& other) const -> Short;
	auto operator-(const Short& other) const -> Short;
	auto operator*(const Short& other) const -> Short;
	auto operator/(const Short& other) const -> Short;
	auto operator%(const Short& other) const -> Short;

private:
	friend std::formatter<Short>;
	int16_t value_{0};
};
}

template <> struct std::formatter<common::entity::base_type::Short>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Short& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Short class.
 *
 * This function parses the format specifiers for the Short class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::Short>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Short object into a string.
 *
 * This function formats the Short object using the provided format context.
 * It generates a string representation of the Short object.
 *
 * \param content The Short object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::Short>::format(const common::entity::base_type::Short& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "{}", content.value_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Short& content) -> std::ostream& {
	return os << std::format("{}", content);
}
