// Created by author ethereal on 2024/12/2.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP
#include <format>
#include <iostream>
#include "entity/base_type/Object.hpp"

namespace common::exception
{
	class Exception : public entity::base_type::Object, public std::exception
	{
	public:
		explicit Exception(std::string message);
		Exception(std::string message, std::string cause);
		~Exception() override;
		[[nodiscard]] auto toString() const -> std::string override;

	protected:
		std::string message_;
		std::unique_ptr<std::exception> cause_;

	private:
		friend std::formatter<Exception>;
	};
}

template <>
struct std::formatter<common::exception::Exception>
{
	constexpr static auto parse(format_parse_context& ctx) -> format_parse_context::const_iterator;
	static auto format(const common::exception::Exception& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>;
};

/**
 * \brief Parse the format specifiers for the Exception class.
 *
 * This function parses the format specifiers for the Exception class.
 * The format specifiers are as follows:
 *
 * \param ctx The format parse context.
 * \return The parsed format specifiers.
 */
constexpr auto std::formatter<common::exception::Exception>::parse(format_parse_context& ctx) -> format_parse_context::const_iterator
{
	const auto begin = ctx.begin();
	if (const auto end = ctx.end(); begin != end && *begin != '}')
	{
		throw std::format_error("invalid format");
	}
	return begin;
}

/**
 * \brief Format the Exception object into a string.
 *
 * This function formats the Exception object using the provided format context.
 * It generates a string representation of the Exception object.
 *
 * \param content The Exception object to format.
 * \param ctx The format context to use for formatting.
 * \return An iterator to the end of the inserted sequence.
 */
inline auto std::formatter<common::exception::Exception>::format(const common::exception::Exception& content, format_context& ctx) -> back_insert_iterator<_Fmt_buffer<char>>
{
	if (content.cause_)
	{
		return std::format_to(ctx.out(), "exception: {}, cause: {}", content.message_, content.cause_->what());
	}
	return std::format_to(ctx.out(), "exception: {}", content.message_);
}

inline auto operator<<(std::ostream& os, const common::exception::Exception& content) -> std::ostream&
{
	return os << std::format("{}", content);
}
#endif //EXCEPTION_HPP
