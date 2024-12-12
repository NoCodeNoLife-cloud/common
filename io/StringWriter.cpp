// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "StringWriter.hpp"

namespace common::io
{
StringWriter::StringWriter(const size_t initialSize) {
	// Reserve an approximate initial size for the string buffer.
	buffer_.str(std::string(initialSize, '\0'));
	buffer_.seekp(0); // Reset the write position to the start.
}

StringWriter::~StringWriter() = default;

/// \brief Appends a single character to the writer.
/// \details This method appends the character to the internal string buffer.
/// \return The writer object, allowing method chaining.
auto StringWriter::append(const char c) -> StringWriter& {
	buffer_.put(c);
	return *this;
}

/// \brief Appends a string to the writer.
/// \details This method appends the entire string to the internal string buffer.
/// \return The writer object, allowing method chaining.
auto StringWriter::append(const std::string& csq) -> StringWriter& {
	buffer_ << csq;
	return *this;
}

/// \brief Appends a substring to the writer.
/// \details This method appends the characters of the substring of the given string,
/// starting at \p start and ending at \p end, to the internal string buffer.
/// If the start or end indexes are out of bounds, or if start is greater than end,
/// a std::out_of_range exception is thrown.
/// \param csq The string from which a substring will be appended.
/// \param start The starting index (inclusive) of the substring to append.
/// \param end The ending index (exclusive) of the substring to append.
/// \return A reference to the StringWriter object.
auto StringWriter::append(const std::string& csq, const size_t start, const size_t end) -> StringWriter& {
	if (start > end || end > csq.size()) {
		throw std::out_of_range("Invalid start or end position");
	}
	buffer_.write(csq.data() + start, static_cast<std::streamsize>(end - start));
	return *this;
}

/// \brief Closes the writer, releasing any system resources associated with it.
/// \details This method has no effect; it is a no-op.
auto StringWriter::close() -> void {
	// No operation; closing is a no-op.
}

/// \brief Flushes the internal buffer.
/// \details This method flushes the underlying string buffer,
/// ensuring that all buffered output is written out.
/// It is a no-op for std::ostringstream, as it does not require flushing.
auto StringWriter::flush() -> void {
	buffer_.flush();
}

/// \brief Retrieves the current contents of the buffer.
/// \details This function returns the current contents of the internal string buffer
/// as a std::string. It provides a snapshot of the data accumulated in the buffer.
auto StringWriter::getBuffer() const -> std::string {
	return buffer_.str();
}

/// \brief Converts the writer to a string.
/// \details This function returns a string representation of the writer.
/// It is equivalent to calling `getBuffer()`.
/// \return The string representation of the writer.
auto StringWriter::toString() const -> std::string {
	return buffer_.str();
}

/// \brief Writes a single character to the writer.
/// \details This function writes a single character to the internal string buffer.
/// \param c the character to write.
auto StringWriter::write(const char c) -> void {
	buffer_.put(c);
}

/// \brief Writes a string to the writer.
/// \details This function writes the contents of the provided string to the writer.
/// \param str the string to write.
auto StringWriter::write(const std::string& str) -> void {
	buffer_ << str;
}

/// \brief Writes a substring of the given string to the writer.
/// \details This function writes a substring of the given string to the writer.
/// The substring is defined by the range [start, end).
/// If the start or end indexes are out of bounds, or if start is greater than end,
/// a std::out_of_range exception is thrown.
/// \param str the string from which a substring will be written.
/// \param off the starting index (inclusive) of the substring to write.
/// \param len the length of the substring to write.
auto StringWriter::write(const std::string& str, const size_t off, const size_t len) -> void {
	if (off > str.size() || off + len > str.size()) {
		throw std::out_of_range("Invalid offset or length");
	}
	buffer_.write(str.data() + off, static_cast<std::streamsize>(len));
}

/// \brief Writes a portion of the byte array to the writer.
/// \details This function writes a portion of the given byte array to the writer.
/// The portion is defined by the range [off, off+len).
/// If the offset and length are out of bounds of the byte array,
/// a std::out_of_range exception is thrown.
/// \param cBuf the byte array to write.
/// \param off the starting index (inclusive) of the portion to write.
/// \param len the length of the portion to write.
void StringWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) {
	if (off > cBuf.size() || len > cBuf.size() - off) {
		throw std::out_of_range("Invalid offset or length");
	}
	buffer_.write(cBuf.data() + off, static_cast<std::streamsize>(len));
}
}
