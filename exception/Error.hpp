// Created by author ethereal on 2024/12/2.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef ERROR_HPP
#define ERROR_HPP
#include <format>
#include <iostream>
#include "Exception.hpp"

namespace common::exception
{
	class Error final : public Exception
	{
	public:
		explicit Error(std::string message);

		Error(std::string message, const std::string& cause);

		~Error() override;

		[[nodiscard]] auto toString() const -> std::string override;

	private:
		friend std::formatter<Error>;
	};
}

template <>
struct std::formatter<common::exception::Error>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;

	static auto format(const common::exception::Error& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Error class.
 *
 * This function parses the format specifiers for the Error class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::exception::Error>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator
{
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}')
	{
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Error object into a string.
 *
 * This function formats the Error object using the provided format context.
 * It generates a string representation of the Error object.
 *
 * \param content The Error object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::exception::Error>::format(const common::exception::Error& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
{
	if (content.cause_)
	{
		return std::format_to(ctx.out(), "error: {}, cause: {}", content.message_, content.cause_->what());
	}
	return std::format_to(ctx.out(), "error: {}, cause: {}", content.message_);
}

inline auto operator<<(std::ostream& os, const common::exception::Error& content) -> std::ostream&
{
	return os << std::format("{}", content);
}
#endif //ERROR_HPP
