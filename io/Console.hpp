// Created by author ethereal on 2024/12/3.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <iostream>
#include <string>
#include "interface/IfaceFlushable.hpp"

namespace common::io
{
/// \brief A final class representing a console.
/// \details The Console class provides static methods for printing
/// to the standard output and reading from the standard input.
/// It is a final class that cannot be inherited from.
class Console final : public interface::IfaceFlushable
{
public:
	auto flush() -> void override;
	template <typename... Args> static auto format(const std::string& fmt, Args... args) -> void;
	template <typename... Args> static auto printf(const std::string& fmt, Args... args) -> void;
	static auto readLine() -> std::string;
	template <typename... Args> static auto readLine(const std::string& fmt, Args... args) -> std::string;
	static auto writer() -> std::ostream&;
	static auto reader() -> std::istream&;
};

/**
 * \brief Formats and outputs a string to the console.
 *
 * This function uses the provided format string and arguments to
 * generate a formatted output, which is then printed to the standard output.
 * It utilizes std::vformat to handle the formatting.
 *
 * \param fmt The format string.
 * \param args The arguments to be formatted according to the format string.
 */
template <typename... Args> auto Console::format(const std::string& fmt, Args... args) -> void {
	std::cout << std::vformat(fmt, std::make_format_args(args...));
}

/**
 * \brief Prints a formatted string to the console.
 *
 * This function is a convenience wrapper for format(). It formats the
 * provided arguments according to the format string and prints the result
 * to the standard output.
 *
 * \param fmt The format string.
 * \param args The arguments to be formatted according to the format string.
 */
template <typename... Args> auto Console::printf(const std::string& fmt, Args... args) -> void {
	format(fmt, args...);
}

/**
 * \brief Prints a formatted string to the console and reads a line of input.
 *
 * This function formats the provided arguments according to the format string
 * and prints the result to the standard output. Then, it reads a line of input
 * from the standard input and returns it.
 *
 * \param fmt The format string.
 * \param args The arguments to be formatted according to the format string.
 * \return The line of input that was read from the standard input.
 */
template <typename... Args> auto Console::readLine(const std::string& fmt, Args... args) -> std::string {
	format(fmt, args...);
	return readLine();
}
}
