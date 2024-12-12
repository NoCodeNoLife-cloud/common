// Created by author ethereal on 2024/12/3.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Console.hpp"

namespace common::io
{
/// \brief Flushes the output buffer.
/// \details This function is a wrapper for std::cout.flush(). It is used to flush the output buffer of the console.
auto Console::flush() -> void {
	std::cout.flush();
}

/// \brief Reads a line of text from the console.
/// \details This function reads a line of text from the console and returns it as a string.
/// The line is read until the end of line is reached or a maximum number of characters is read.
auto Console::readLine() -> std::string {
	std::string input;
	std::getline(std::cin, input);
	return input;
}

/// \brief Gets the output stream used by the console.
/// \details This function returns a reference to the output stream used by the console.
/// The output stream is used to write to the console.
auto Console::writer() -> std::ostream& {
	return std::cout;
}

/// \brief Gets the input stream used by the console.
/// \details This function returns a reference to the input stream used by the console.
/// The input stream is used to read from the console.
auto Console::reader() -> std::istream& {
	return std::cin;
}
}
