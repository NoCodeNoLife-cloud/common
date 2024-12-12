// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include "entity/base_type/Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief A class representing a boolean value.
/// \details This class is a boolean value in an object form. It is a subclass of
/// the Object class and implements the Comparable interface. It provides a way
/// to perform boolean operations between two Boolean objects.
class Boolean final : public Object, public interface::IfaceComparable<Boolean>
{
public:
	static const Boolean TRUE;
	static const Boolean FALSE;
	explicit Boolean(bool value = false);
	~Boolean() override;
	explicit operator bool() const;
	[[nodiscard]] auto toString() const -> std::string override;
	[[nodiscard]] auto boolValue() const -> bool;
	[[nodiscard]] auto compareTo(const Boolean& other) const -> int override;
	static auto parseBoolean(const std::string& str) -> Boolean;
	[[nodiscard]] auto booleanValue() const -> bool;
	[[nodiscard]] auto equals(const Boolean& other) const -> bool override;
	auto operator==(const Boolean& other) const -> bool;
	auto operator!=(const Boolean& other) const -> bool;

private:
	friend std::formatter<Boolean>;
	bool value_{false};
};

inline const Boolean Boolean::TRUE{true};
inline const Boolean Boolean::FALSE{false};
}

template <> struct std::formatter<common::entity::base_type::Boolean>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Boolean& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Boolean class.
 *
 * This function parses the format specifiers for the Boolean class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::Boolean>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Boolean object into a string.
 *
 * This function formats the Boolean object using the provided format context.
 * It generates a string representation of the Boolean object.
 *
 * \param content The Boolean object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::Boolean>::format(const common::entity::base_type::Boolean& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "{}", content.value_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Boolean& content) -> std::ostream& {
	return os << std::format("{}", content);
}
