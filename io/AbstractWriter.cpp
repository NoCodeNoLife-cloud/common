// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "AbstractWriter.hpp"
#include <stdexcept>

namespace common::io
{
AbstractWriter::AbstractWriter() = default;
AbstractWriter::~AbstractWriter() = default;

/// \brief Appends a character to the Writer.
/// \details This method writes a single character to the writer object and returns a reference to the Writer.
/// \param c The character to append.
/// \return A reference to the Writer object.
auto AbstractWriter::append(const char c) -> AbstractWriter& {
	write(c);
	return *this;
}

/// \brief Appends a string to the Writer.
/// \details This method writes the entire content of the given string to the writer object and returns a reference to the Writer.
/// \param csq The string to append.
/// \return A reference to the Writer object.
auto AbstractWriter::append(const std::string& csq) -> AbstractWriter& {
	write(csq);
	return *this;
}

/// \brief Appends a substring to the Writer.
/// \details This method writes a substring of the given string to the writer object and returns a reference to the Writer.
/// The substring is defined by the range [start, end).
/// If the start or end indexes are out of bounds, or if start is greater than end,
/// the function does nothing.
/// \param csq The string from which a substring will be appended.
/// \param start The starting index (inclusive) of the substring to append.
/// \param end The ending index (exclusive) of the substring to append.
/// \return A reference to the Writer object.
auto AbstractWriter::append(const std::string& csq, const size_t start, const size_t end) -> AbstractWriter& {
	write(csq, start, end);
	return *this;
}

/// \brief Writes a single character to the Writer.
/// \details This method writes a single character to the writer object.
/// It utilizes the overloaded write method to specify the starting position and length, writing a single character.
/// \param c The character to write.
auto AbstractWriter::write(const char c) -> void {
	const std::vector buf(1, c);
	write(buf, 0, 1);
}

/// \brief Writes a vector of characters to the Writer.
/// \details This method writes the entire content of the given vector of characters to the writer object.
/// It utilizes the overloaded write method to specify the starting position and length, writing from the start to the end of the vector.
/// \param cBuf The vector of characters to write.
auto AbstractWriter::write(const std::vector<char>& cBuf) -> void {
	write(cBuf, 0, cBuf.size());
}

/// \brief Writes a string to the Writer.
/// \details This method writes the entire content of the given string to the writer object.
/// It utilizes the overloaded write method to specify the starting position and length, writing from the start to the end of the string.
/// \param str The string to write.
auto AbstractWriter::write(const std::string& str) -> void {
	write(str, 0, str.size());
}

/// \brief Writes a substring of the given string to the Writer.
/// \details This method writes a substring of the given string to the writer object.
/// The substring is defined by the range [start, end).
/// If the start or end indexes are out of bounds, or if start is greater than end,
/// the function does nothing.
/// \param str The string from which a substring will be written.
/// \param off The starting index (inclusive) of the substring to write.
/// \param len The length of the substring to write.
auto AbstractWriter::write(const std::string& str, const size_t off, const size_t len) -> void {
	if (off < str.size()) {
		const size_t end = off + len < str.size() ? off + len : str.size();
		const std::vector buf(str.begin() + static_cast<std::string::difference_type>(off), str.begin() + static_cast<std::string::difference_type>(end));
		write(buf, 0, buf.size());
	}
}
}
