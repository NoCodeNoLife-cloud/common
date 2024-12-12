// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "BufferedWriter.hpp"
#include <fstream>
#include <stdexcept>

namespace common::io
{
BufferedWriter::BufferedWriter(std::unique_ptr<std::ofstream> os, const size_t size = DEFAULT_BUFFER_SIZE): outputStream_(std::move(os)), bufferSize_(size) {
	if (!outputStream_->is_open()) {
		throw std::runtime_error("Output stream is not open.");
	}
	buffer_.reserve(size);
}

BufferedWriter::~BufferedWriter() {
	BufferedWriter::close();
}

/// \brief Writes a string to the writer.
/// \details This function writes a string to the writer. If the size of the string
/// is greater than the buffer size, the buffer is flushed and the string is written
/// directly to the output stream. Otherwise, the string is written to the buffer.
/// If the buffer is full after writing the string, the buffer is flushed.
auto BufferedWriter::write(const std::string& str) -> void {
	if (str.size() > bufferSize_) {
		flush();
		*outputStream_ << str;
	}
	else {
		for (const char c : str) {
			buffer_.push_back(static_cast<char>(c));
		}
		if (buffer_.size() >= bufferSize_) {
			flush();
		}
	}
}

/// \brief Writes a portion of a byte array to the writer.
/// \details This function writes a portion of a byte array to the writer. If the size of the portion
/// is greater than the buffer size, the buffer is flushed and the portion is written directly to the
/// output stream. Otherwise, the portion is written to the buffer. If the buffer is full after writing
/// the portion, the buffer is flushed.
auto BufferedWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
	if (off + len > cBuf.size()) {
		throw std::out_of_range("Offset and length are out of the bounds of the buffer.");
	}
	if (len > bufferSize_) {
		flush();
		outputStream_->write(cBuf.data() + off, static_cast<std::streamsize>(len));
	}
	else {
		for (size_t i = 0; i < len; ++i) {
			buffer_.push_back(cBuf[off + i]);
			if (buffer_.size() >= bufferSize_) {
				flush();
			}
		}
	}
}

/// \brief Writes a line separator to the writer and returns the writer.
/// \details This function is a convenience method to write a line separator to the writer.
/// It writes a "\n" to the writer and returns the writer itself.
auto BufferedWriter::newLine() -> BufferedWriter& {
	write("\n");
	return *this;
}

/// \brief Flushes the buffer.
/// \details This function flushes the buffer to the output stream. If the buffer is empty,
/// this function does nothing.
auto BufferedWriter::flush() -> void {
	if (!buffer_.empty()) {
		outputStream_->write(buffer_.data(), static_cast<std::streamsize>(buffer_.size()));
		buffer_.clear();
	}
}

/// \brief Closes the writer.
/// \details This function flushes the buffer and closes the output stream.
auto BufferedWriter::close() -> void {
	flush();
	outputStream_->close();
}

/// \brief Appends a character to the writer.
/// \details This function appends a character to the writer. If the buffer is full after appending the character,
/// the buffer is flushed.
auto BufferedWriter::append(const char c) -> BufferedWriter& {
	buffer_.push_back(static_cast<char>(c));
	if (buffer_.size() >= bufferSize_) {
		flush();
	}
	return *this;
}

/// \brief Appends a string to the writer.
/// \details This function appends a string to the writer. If the buffer is full after appending the string,
/// the buffer is flushed.
auto BufferedWriter::append(const std::string& str) -> BufferedWriter& {
	for (const char c : str) {
		buffer_.push_back(static_cast<char>(c));
		if (buffer_.size() >= bufferSize_) {
			flush();
		}
	}
	return *this;
}

/// \brief Appends a substring to the writer.
/// \details This function appends a substring of the given string to the writer.
/// The substring is defined by the range [start, end).
/// If the start or end indexes are out of bounds, or if start is greater than end,
/// the function does nothing. If the buffer is full after appending the substring,
/// the buffer is flushed.
/// \param str The string from which a substring will be appended.
/// \param start The starting index (inclusive) of the substring to append.
/// \param end The ending index (exclusive) of the substring to append.
/// \return A reference to the BufferedWriter object.
auto BufferedWriter::append(const std::string& str, const size_t start, const size_t end) -> BufferedWriter& {
	if (start < str.length() && end <= str.length() && start < end) {
		for (size_t i = start; i < end; ++i) {
			buffer_.push_back(static_cast<char>(str[i]));
			if (buffer_.size() >= bufferSize_) {
				flush();
			}
		}
	}
	return *this;
}

/// \brief Converts the buffer to a string.
/// \details This function returns a string representation of the current contents of the buffer.
/// It is useful for retrieving the buffered data without flushing it to the output stream.
/// \return A string containing the buffered data.
auto BufferedWriter::toString() const -> std::string {
	std::string str;
	for (const char c : buffer_) {
		str.push_back(c);
	}
	return str;
}
}
