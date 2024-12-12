// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include "Object.hpp"
#include "entity/interface/IfaceComparable.hpp"

namespace common::entity::base_type
{
/// \brief A Double object represents an immutable double precision floating point value.
/// \details In addition to implementing the methods inherited from its parent class,
/// it also overrides the methods defined in the Comparable interface.
class Double final : public Object, public interface::IfaceComparable<Double>
{
public:
	static constexpr double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
	static constexpr double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
	static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
	static constexpr double MAX_VALUE = std::numeric_limits<double>::max();
	static constexpr double MIN_VALUE = std::numeric_limits<double>::min();
	explicit Double(double value = 0.0);
	~Double() override;
	explicit operator double() const;
	[[nodiscard]] auto toString() const -> std::string override;
	[[nodiscard]] auto equals(const Double& other) const -> bool override;
	[[nodiscard]] auto compareTo(const Double& other) const -> int override;
	[[nodiscard]] auto doubleValue() const -> double;
	static auto parseDouble(const std::string& str) -> Double;
	auto operator==(const Double& other) const -> bool;
	auto operator!=(const Double& other) const -> bool;
	auto operator<(const Double& other) const -> bool;
	auto operator>(const Double& other) const -> bool;
	auto operator<=(const Double& other) const -> bool;
	auto operator>=(const Double& other) const -> bool;
	auto operator+(const Double& other) const -> Double;
	auto operator-(const Double& other) const -> Double;
	auto operator*(const Double& other) const -> Double;
	auto operator/(const Double& other) const -> Double;

private:
	friend std::formatter<Double>;
	double value_{0.0};
};
}

template <> struct std::formatter<common::entity::base_type::Double>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::entity::base_type::Double& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Double class.
 *
 * This function parses the format specifiers for the Double class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::entity::base_type::Double>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator {
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}') {
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Double object into a string.
 *
 * This function formats the Double object using the provided format context.
 * It generates a string representation of the Double object.
 *
 * \param content The Double object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::entity::base_type::Double>::format(const common::entity::base_type::Double& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>> {
	return std::format_to(ctx.out(), "{}", content.value_);
}

inline auto operator<<(std::ostream& os, const common::entity::base_type::Double& content) -> std::ostream& {
	return os << std::format("{}", content);
}
