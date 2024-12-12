// Created by author ethereal on 2024/12/10.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "CharArrayWriter.hpp"
#include <stdexcept>

namespace common::io
{
CharArrayWriter::CharArrayWriter() = default;

CharArrayWriter::CharArrayWriter(const int initialSize) {
	if (initialSize < 0) {
		throw std::invalid_argument("initialSize must be non-negative");
	}
	buf_.reserve(initialSize);
}

CharArrayWriter::~CharArrayWriter() = default;

/// \brief Writes a single character to the writer.
/// \details This method writes a character to the internal buffer of the CharArrayWriter.
/// If the buffer is already full, it appends the character to the end of the buffer.
/// Otherwise, it replaces the character at the current position.
/// \param c The character to write.
void CharArrayWriter::write(const char c) {
	if (count_ == buf_.size()) {
		buf_.push_back(c);
	}
	else {
		buf_[count_] = c;
	}
	++count_;
}

/// \brief Writes a portion of a byte array to the writer.
/// \details This method writes up to len bytes from the specified cBuf starting at off to the internal buffer of the CharArrayWriter.
/// If the internal buffer is full, it is resized to accommodate the new data. If the offset and length exceed the size of the input buffer, an exception is thrown.
/// \param cBuf The buffer to be written.
/// \param off The starting position in the buffer to write the data.
/// \param len The maximum number of bytes to write from the buffer.
auto CharArrayWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
	if (off + len > static_cast<int>(cBuf.size())) {
		throw std::out_of_range("Invalid offset or length");
	}
	if (count_ + len > static_cast<int>(buf_.size())) {
		buf_.resize(count_ + len);
	}
	std::copy_n(cBuf.begin() + static_cast<std::ptrdiff_t>(off), len, buf_.begin() + static_cast<std::ptrdiff_t>(count_));
	count_ += len;
}

/// \brief Writes a portion of a string to the writer.
/// \details This method writes up to len characters from the specified str starting at off to the internal buffer of the CharArrayWriter.
/// If the internal buffer is full, it is resized to accommodate the new data. If the offset and length exceed the size of the input string, an exception is thrown.
/// \param str The string to be written.
/// \param off The starting position in the string to write the data.
/// \param len The maximum number of characters to write from the string.
void CharArrayWriter::write(const std::string& str, const size_t off, const size_t len) {
	if (off + len > static_cast<int>(str.size())) {
		throw std::out_of_range("Invalid offset or length");
	}
	if (count_ + len > static_cast<int>(buf_.size())) {
		buf_.resize(count_ + len);
	}
	std::copy_n(str.begin() + static_cast<std::ptrdiff_t>(off), len, buf_.begin() + static_cast<std::ptrdiff_t>(count_));
	count_ += len;
}

/// \brief Writes the contents of the writer to the specified AbstractWriter.
/// \details This method writes all the characters currently stored in the internal buffer of the CharArrayWriter to the specified AbstractWriter.
/// \param out The AbstractWriter to write the data to.
auto CharArrayWriter::writeTo(AbstractWriter& out) const -> void {
	out.write(buf_, 0, count_);
}

/// \brief Appends a string to the writer.
/// \details This method appends the characters of the given string to the internal buffer of the CharArrayWriter.
/// If the internal buffer is full, it is resized to accommodate the new data.
/// \param csq The string to be written.
/// \return A reference to the CharArrayWriter object.
CharArrayWriter& CharArrayWriter::append(const std::string& csq) {
	write(csq, 0, csq.size());
	return *this;
}

/// \brief Appends a substring to the writer.
/// \details This method appends the characters of the substring of the given string, starting at \p start and ending at \p end, to the internal buffer of the CharArrayWriter.
/// If the internal buffer is full, it is resized to accommodate the new data.
/// \param csq The string to be written.
/// \param start The starting index (inclusive) of the substring to append.
/// \param end The ending index (exclusive) of the substring to append.
/// \return A reference to the CharArrayWriter object.
CharArrayWriter& CharArrayWriter::append(const std::string& csq, const size_t start, const size_t end) {
	write(csq, start, end - start);
	return *this;
}

/// \brief Appends a single character to the writer.
/// \details This method appends the given character to the internal buffer of the CharArrayWriter.
/// If the internal buffer is full, it is resized to accommodate the new character.
/// \param c The character to append.
/// \return A reference to the CharArrayWriter object.
CharArrayWriter& CharArrayWriter::append(const char c) {
	write(c);
	return *this;
}

/// \brief Resets the writer to its initial state.
/// \details This method resets the writer to its initial state, effectively clearing the internal buffer.
auto CharArrayWriter::reset() -> void {
	count_ = 0;
}

/// \brief Returns the internal buffer of the CharArrayWriter as a vector of characters.
/// \details This method returns the internal buffer of the CharArrayWriter as a vector of characters.
/// The vector returned contains the characters written to the writer so far.
/// The size of the vector will be equal to the number of characters written to the writer.
/// \return The internal buffer of the CharArrayWriter as a vector of characters.
auto CharArrayWriter::toCharArray() const -> std::vector<char> {
	return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
}

/// \brief Returns the number of characters currently stored in the internal buffer of the CharArrayWriter.
/// \details This method returns the number of characters currently stored in the internal buffer of the CharArrayWriter.
/// This is the number of characters that have been written to the writer but not yet flushed or reset.
/// \return The number of characters currently stored in the internal buffer of the CharArrayWriter.
auto CharArrayWriter::size() const -> size_t {
	return count_;
}

/// \brief Converts the internal buffer of the CharArrayWriter to a string.
/// \details This method converts the internal buffer of the CharArrayWriter to a string.
/// The string returned contains the characters written to the writer so far.
/// The size of the string will be equal to the number of characters written to the writer.
/// \return The internal buffer of the CharArrayWriter as a string.
auto CharArrayWriter::toString() const -> std::string {
	return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
}

/// \brief Flushes the internal buffer.
/// \details This method flushes the internal buffer by clearing it.
/// This is a no-op for CharArrayWriter, as it does not require flushing.
auto CharArrayWriter::flush() -> void {
	buf_.clear();
	count_ = 0;
}

/// \brief Closes the writer and releases its resources.
/// \details This method closes the writer and releases its resources.
/// It is a no-op for CharArrayWriter, as it does not require closing.
auto CharArrayWriter::close() -> void {
	buf_.clear();
	count_ = 0;
}
}
