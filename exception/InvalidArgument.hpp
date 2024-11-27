// Created by author ethereal on 2024/12/2.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef INVALIDARGUMENT_HPP
#define INVALIDARGUMENT_HPP
#include <format>
#include <iostream>
#include "Exception.hpp"

namespace common::exception
{
	class InvalidArgument final : public Exception
	{
	public:
		explicit InvalidArgument(const std::string& invalidArgumentName);
		InvalidArgument(std::string message, std::string cause);
		~InvalidArgument() override;
		[[nodiscard]] auto toString() const -> std::string override;

	private:
		friend std::formatter<InvalidArgument>;
	};
}

template <>
struct std::formatter<common::exception::InvalidArgument>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::exception::InvalidArgument& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the InvalidArgument class.
 *
 * This function parses the format specifiers for the InvalidArgument class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::exception::InvalidArgument>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator
{
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}')
	{
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the InvalidArgument object into a string.
 *
 * This function formats the InvalidArgument object using the provided format context.
 * It generates a string representation of the InvalidArgument object.
 *
 * \param content The InvalidArgument object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::exception::InvalidArgument>::format(const common::exception::InvalidArgument& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
{
	if (content.cause_)
	{
		return std::format_to(ctx.out(), "invalid argument: {}, cause: {}", content.message_, content.cause_->what());
	}
	return std::format_to(ctx.out(), "invalid argument: {}", content.message_);
}

inline auto operator<<(std::ostream& os, const common::exception::InvalidArgument& content) -> std::ostream&
{
	return os << std::format("{}", content);
}
#endif //INVALIDARGUMENT_HPP
