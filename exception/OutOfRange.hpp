// Created by author ethereal on 2024/12/2.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef OUTOFRANGE_HPP
#define OUTOFRANGE_HPP
#include <format>
#include <iostream>
#include <string>
#include "Exception.hpp"

namespace common::exception
{
	class OutOfRange final : public Exception
	{
	public:
		OutOfRange(size_t index, size_t size);

		OutOfRange(size_t index, size_t size, std::string cause);

		OutOfRange(std::string message, std::string cause);

		~OutOfRange() override;

		[[nodiscard]] auto toString() const -> std::string override;

	private:
		friend std::formatter<OutOfRange>;
	};
}

template <>
struct std::formatter<common::exception::OutOfRange>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;

	static auto format(const common::exception::OutOfRange& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the OutOfRange class.
 *
 * This function parses the format specifiers for the OutOfRange class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::exception::OutOfRange>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator
{
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}')
	{
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the OutOfRange object into a string.
 *
 * This function formats the OutOfRange object using the provided format context.
 * It generates a string representation of the OutOfRange object.
 *
 * \param content The OutOfRange object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::exception::OutOfRange>::format(const common::exception::OutOfRange& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
{
	if (content.cause_)
	{
		return std::format_to(ctx.out(), "out of range: {}, cause: {}", content.message_, content.cause_->what());
	}
	return std::format_to(ctx.out(), "out of range: {}", content.message_);
}

inline auto operator<<(std::ostream& os, const common::exception::OutOfRange& content) -> std::ostream&
{
	return os << std::format("{}", content);
}
#endif //OUTOFRANGE_HPP
