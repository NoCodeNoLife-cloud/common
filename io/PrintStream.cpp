// Created by author ethereal on 2024/12/15.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "PrintStream.hpp"

namespace common::io
{
PrintStream::PrintStream(std::shared_ptr<AbstractOutputStream> outStream, const bool autoFlush, const std::locale& loc): FilterOutputStream(std::move(outStream)), autoFlush_(autoFlush), locale_(loc) {}

PrintStream::~PrintStream() = default;

/// \brief Appends a character to the stream.
/// \details Writes the character to the stream and flushes if needed.
/// \param c The character to append.
auto PrintStream::append(char c) -> PrintStream& {
	write(static_cast<std::byte>(c));
	flushIfNeeded();
	return *this;
}

/// \brief Appends a string to the stream.
/// \details Writes the string to the stream and flushes if needed.
/// \param str The string to append.
auto PrintStream::append(const std::string& str) -> PrintStream& {
	for (char c : str) {
		write(static_cast<std::byte>(c));
	}
	flushIfNeeded();
	return *this;
}

/// \brief Appends a substring to the stream.
/// \details Writes the substring to the stream and flushes if needed.
/// \param str The string to append.
/// \param start The start of the substring.
/// \param end The end of the substring.
auto PrintStream::append(const std::string& str, size_t start, size_t end) -> PrintStream& {
	for (size_t i = start; i < end; i++) {
		write(static_cast<std::byte>(str[i]));
	}
	flushIfNeeded();
	return *this;
}

/// \brief Prints a boolean value to the stream.
/// \details Writes the boolean value to the stream and flushes if needed.
/// \param b The boolean value to print.
auto PrintStream::print(const bool b) const -> void {
	if (outputStream_) {
		outputStream_->write(static_cast<std::byte>(b ? 1 : 0));
	}
	flushIfNeeded();
}

/// \brief Prints a character to the stream.
/// \details Writes the character to the stream and flushes if needed.
/// \param c The character to print.
auto PrintStream::print(char c) const -> void {
	if (outputStream_) {
		outputStream_->write(static_cast<std::byte>(c));
		flushIfNeeded();
	}
}

/// \brief Prints an integer value to the stream.
/// \details Writes the integer value to the stream and flushes if needed.
/// \param i The integer value to print.
auto PrintStream::print(const int i) const -> void {
	if (outputStream_) {
		for (const auto buffer = std::to_string(i); char c : buffer) {
			outputStream_->write(static_cast<std::byte>(c));
		}
		flushIfNeeded();
	}
}

/// \brief Prints a long value to the stream.
/// \details Writes the long value to the stream and flushes if needed.
/// \param l The long value to print.
auto PrintStream::print(const long l) const -> void {
	if (outputStream_) {
		for (const auto buffer = std::to_string(l); char c : buffer) {
			outputStream_->write(static_cast<std::byte>(c));
		}
		flushIfNeeded();
	}
}

/// \brief Prints a float value to the stream.
/// \details Writes the float value to the stream and flushes if needed.
/// \param f The float value to print.
auto PrintStream::print(const float f) const -> void {
	if (outputStream_) {
		for (const auto buffer = std::to_string(f); char c : buffer) {
			outputStream_->write(static_cast<std::byte>(c));
		}
		flushIfNeeded();
	}
}

/// \brief Prints a double value to the stream.
/// \details Writes the double value to the stream and flushes if needed.
/// \param d The double value to print.
auto PrintStream::print(const double d) const -> void {
	if (outputStream_) {
		for (const auto buffer = std::to_string(d); char c : buffer) {
			outputStream_->write(static_cast<std::byte>(c));
		}
		flushIfNeeded();
	}
}

/// \brief Prints a string to the stream.
/// \details Writes the string to the stream and flushes if needed.
/// \param s The string to print.
auto PrintStream::print(const char* s) const -> void {
	if (outputStream_ && s) {
		while (*s) {
			outputStream_->write(static_cast<std::byte>(*s++));
		}
		flushIfNeeded();
	}
}

/// \brief Prints a string to the stream.
/// \details Writes the string to the stream and flushes if needed.
/// \param s The string to print.
auto PrintStream::print(const std::string& s) const -> void {
	if (outputStream_) {
		for (char c : s) {
			outputStream_->write(static_cast<std::byte>(c));
		}
		flushIfNeeded();
	}
}

/// \brief Prints a vector of characters to the stream.
/// \details Writes the vector of characters to the stream and flushes if needed.
/// \param v The vector of characters to print.
auto PrintStream::print(const std::vector<char>& v) const -> void {
	if (outputStream_) {
		for (char c : v) {
			outputStream_->write(static_cast<std::byte>(c));
		}
		flushIfNeeded();
	}
}

/// \brief Prints a boolean value to the stream.
/// \details Writes the boolean value to the stream and flushes if needed.
/// \param b The boolean value to print.
void PrintStream::println(const bool b) const {
	print(b);
	print('\n');
}

/// \brief Prints a character to the stream.
/// \details Writes the character to the stream and flushes if needed.
/// \param c The character to print.
void PrintStream::println(const char c) const {
	print(c);
	print('\n');
}

/// \brief Prints an integer value to the stream.
/// \details Writes the integer value to the stream and flushes if needed.
/// \param i The integer value to print.
void PrintStream::println(const int i) const {
	print(i);
	print('\n');
}

/// \brief Prints a long value to the stream.
/// \details Writes the long value to the stream and flushes if needed.
/// \param l The long value to print.
void PrintStream::println(long l) const {
	print(l);
	print('\n');
}

/// \brief Prints a float value followed by a newline to the stream.
/// \details Writes the float value to the stream, appends a newline character, and flushes if needed.
/// \param f The float value to print.
void PrintStream::println(float f) const {
	print(f);
	print('\n');
}

/// \brief Prints a double value followed by a newline to the stream.
/// \details Writes the double value to the stream, appends a newline character, and flushes if needed.
/// \param d The double value to print.
void PrintStream::println(double d) const {
	print(d);
	print('\n');
}

/// \brief Prints a string followed by a newline to the stream.
/// \details Writes the string to the stream, appends a newline character, and flushes if needed.
/// \param s The string to print.
void PrintStream::println(const char* s) const {
	print(s);
	print('\n');
}

/// \brief Prints a string followed by a newline to the stream.
/// \details Writes the string to the stream, appends a newline character, and flushes if needed.
/// \param s The string to print.
void PrintStream::println(const std::string& s) const {
	print(s);
	print('\n');
}

/// \brief Prints a vector of characters followed by a newline to the stream.
/// \details Writes the vector of characters to the stream, appends a newline character, and flushes if needed.
/// \param v The vector of characters to print.
void PrintStream::println(const std::vector<char>& v) const {
	print(v);
	print('\n');
}

/// \brief Flushes the stream.
/// \details Flushes the internal buffer of the output stream.
auto PrintStream::flush() -> void {
	if (outputStream_) {
		outputStream_->flush();
	}
}

/// \brief Closes the stream and its underlying stream.
/// \details Closes the stream by closing the underlying output stream.
auto PrintStream::close() -> void {
	if (outputStream_) {
		outputStream_->close();
	}
}

/// \brief Flushes the stream if autoFlush is enabled.
/// \details Flushes the internal buffer of the output stream if autoFlush is enabled.
auto PrintStream::flushIfNeeded() const -> void {
	if (autoFlush_ && outputStream_) {
		outputStream_->flush();
	}
}
}
