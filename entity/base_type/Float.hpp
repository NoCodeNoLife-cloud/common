// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief A class representing a float value.
/// \details This class is a wrapper around a float value. It provides a way to compare
/// and manipulate float values in a type-safe manner. It also provides a way to convert
/// other types of numeric values to a float value.
class Float final : public Object, public interface::IfaceComparable<Float>
{
public:
	static constexpr float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
	static constexpr float NEGATIVE_INFINITY = -std::numeric_limits<float>::infinity();
	static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
	static constexpr float MAX_VALUE = std::numeric_limits<float>::max();
	static constexpr float MIN_VALUE = std::numeric_limits<float>::min();
	explicit Float(float value = 0.0f);
	~Float() override;
	explicit operator float() const;
	[[nodiscard]] auto toString() const -> std::string override;
	[[nodiscard]] auto equals(const Float& other) const -> bool override;
	[[nodiscard]] auto compareTo(const Float& other) const -> int override;
	[[nodiscard]] auto floatValue() const -> float;
	static auto parseFloat(const std::string& str) -> Float;
	auto operator==(const Float& other) const -> bool;
	auto operator!=(const Float& other) const -> bool;
	auto operator<(const Float& other) const -> bool;
	auto operator>(const Float& other) const -> bool;
	auto operator<=(const Float& other) const -> bool;
	auto operator>=(const Float& other) const -> bool;
	auto operator+(const Float& other) const -> Float;
	auto operator-(const Float& other) const -> Float;
	auto operator*(const Float& other) const -> Float;
	auto operator/(const Float& other) const -> Float;

private:
	friend std::formatter<Float>;
	float value_{0.0};
};
}

template <> struct std::formatter<common::entity::base_type::Float>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Float& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Float class.
 *
 * This function parses the format specifiers for the Float class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::Float>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Float object into a string.
 *
 * This function formats the Float object using the provided format context.
 * It generates a string representation of the Float object.
 *
 * \param content The Float object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::Float>::format(const common::entity::base_type::Float& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "{}", content.value_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Float& content) -> std::ostream& {
	return os << std::format("{}", content);
}
