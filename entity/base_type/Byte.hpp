// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include <entity/base_type/Object.hpp>
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief A Byte object wraps a value of primitive type byte in an object.
/// \details An object of type Byte contains a single field whose type is byte.
/// The Byte class provides several methods for performing operations on a byte by a Byte object, including methods for
/// adding, subtracting, multiplying, and dividing two Byte objects. There are also methods for determining the absolute
/// value, as well as methods for comparing two Byte objects.
class Byte final : public Object, public interface::IfaceComparable<Byte>
{
public:
	static constexpr int8_t MIN_VALUE = std::numeric_limits<int8_t>::min();
	static constexpr int8_t MAX_VALUE = std::numeric_limits<int8_t>::max();
	explicit Byte(int8_t value = 0);
	~Byte() override;
	explicit operator int8_t() const;
	[[nodiscard]] auto equals(const Byte& other) const -> bool override;
	[[nodiscard]] auto compareTo(const Byte& other) const -> int override;
	[[nodiscard]] auto toString() const -> std::string override;
	static auto parseByte(const std::string& str) -> Byte;
	[[nodiscard]] auto byteValue() const -> int8_t;
	auto operator==(const Byte& other) const -> bool;
	auto operator!=(const Byte& other) const -> bool;
	auto operator<(const Byte& other) const -> bool;
	auto operator>(const Byte& other) const -> bool;
	auto operator<=(const Byte& other) const -> bool;
	auto operator>=(const Byte& other) const -> bool;
	auto operator+(const Byte& other) const -> Byte;
	auto operator-(const Byte& other) const -> Byte;

private:
	friend std::formatter<Byte>;
	int8_t value_{0};
};
}

template <> struct std::formatter<common::entity::base_type::Byte>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Byte& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Byte class.
 *
 * This function parses the format specifiers for the Byte class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::Byte>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Byte object into a string.
 *
 * This function formats the Byte object using the provided format context.
 * It generates a string representation of the Byte object.
 *
 * \param content The Byte object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::Byte>::format(const common::entity::base_type::Byte& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "{}", content.value_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Byte& content) -> std::ostream& {
	return os << std::format("{}", content);
}
