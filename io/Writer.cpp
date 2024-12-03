// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Writer.hpp"
#include <stdexcept>

namespace common::io
{
Writer::Writer() = default;
Writer::~Writer() = default;

/// \brief Appends a single character to the writer.
/// \details This function appends a single character to the writer. It is
/// equivalent to calling `write(c)`.
/// \param c the character to append.
/// \return the writer.
auto Writer::append(const char c) -> Writer& {
	write(c);
	return *this;
}

/// \brief Appends a string to the writer.
/// \details This function appends a string to the writer. It is
/// equivalent to calling `write(csq)`.
/// \param csq the string to append.
/// \return the writer.
auto Writer::append(const std::string& csq) -> Writer& {
	write(csq);
	return *this;
}

/// \brief Appends a substring of the given string to the writer.
/// \details This function appends a substring of the given string to the writer.
/// The substring is defined by the range [start, end).
/// If the start or end indexes are out of bounds, or if start is greater than end,
/// an std::out_of_range exception is thrown.
/// \param csq the string from which a substring will be appended.
/// \param start the starting index (inclusive) of the substring to append.
/// \param end the ending index (exclusive) of the substring to append.
/// \return the writer.
auto Writer::append(const std::string& csq, const size_t start, const size_t end) -> Writer& {
	if (end > static_cast<int>(csq.size()) || start > end) { throw std::out_of_range("Invalid start or end position"); }
	write(csq.substr(start, end - start));
	return *this;
}

/// \brief Writes a null-terminated character array to the writer.
/// \details This function writes the contents of a null-terminated character array to the writer.
/// If the provided character buffer is null, an std::invalid_argument exception is thrown.
/// \param cBuf The null-terminated character array to be written.
auto Writer::write(const char cBuf[]) -> void {
	if (cBuf == nullptr) { throw std::invalid_argument("Buffer cannot be null"); }
	int len = 0;
	while (cBuf[len] != '\0') { ++len; }
	write(cBuf, 0, len);
}

/// \brief Writes a single character to the writer.
/// \details This function writes a single character to the writer.
/// It is equivalent to calling `write(&c, 0, 1)`.
/// \param c the character to write.
auto Writer::write(const char c) -> void { write(&c, 0, 1); }

/// \brief Writes the contents of a std::string to the writer.
/// \details This function writes the contents of a std::string to the writer.
/// It is equivalent to calling `write(str.c_str(), 0, str.size())`.
/// \param str the std::string to write.
auto Writer::write(const std::string& str) -> void { write(str.c_str(), 0, str.size()); }

/// \brief Writes a substring of a std::string to the writer.
/// \details This function writes a substring defined by offset and length from a std::string to the writer.
/// If the provided offset or length is out of range, an std::out_of_range exception is thrown.
/// \param str The std::string from which the substring will be written.
/// \param off The starting index (inclusive) of the substring.
/// \param len The length of the substring to write.
auto Writer::write(const std::string& str, const size_t off, const size_t len) -> void {
	if (off + len > static_cast<int>(str.size())) { throw std::out_of_range("Invalid offset or length"); }
	write(str.c_str() + off, 0, len);
}
} // namespace common::io
