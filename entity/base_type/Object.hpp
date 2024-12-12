// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>

namespace common::entity::base_type
{
/// \class Object
/// \brief The base class for all objects.
class Object
{
public:
	explicit Object();
	virtual ~Object();
	[[nodiscard]] virtual auto clone() const -> std::unique_ptr<Object>;
	[[nodiscard]] virtual auto getClass() const -> const std::type_info&;
	[[nodiscard]] virtual auto equals(const Object& other) const -> bool;
	[[nodiscard]] virtual auto hashCode() const -> size_t;
	[[nodiscard]] virtual auto toString() const -> std::string;

private:
	friend std::formatter<Object>;
};
}

template <> struct std::formatter<common::entity::base_type::Object>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Object& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * Parse the format string context to determine the format of the output. This currently doesn't do anything
 * but is required by the std::formatter interface.
 *
 * @param ctx The format string context to parse.
 * @return The iterator pointing to the end of the parsed format string.
 */
constexpr auto std::formatter<common::entity::base_type::Object>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * Format the given Object using its std::string representation.
 *
 * @param content The Object to format.
 * @param ctx The format context.
 * @return The iterator pointing to the end of the formatted output.
 */
inline auto std::formatter<common::entity::base_type::Object>::format([[maybe_unused]] const common::entity::base_type::Object& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "Object{{}}", "");
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Object& object) -> std::ostream& {
	return os << std::format("{}", object);
}
