// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "BufferedWriter.hpp"
#include <fstream>
#include <stdexcept>

namespace commom::io
{
BufferedWriter::BufferedWriter(std::ofstream& os, size_t size): outStream_(os),
                                                                bufferSize_(size) {
	if (!os.is_open()) { throw std::runtime_error("Output stream is not open."); }
	buffer_.reserve(size);
}

BufferedWriter::~BufferedWriter() { BufferedWriter::close(); }

/// \brief Writes a string to the writer.
/// \details This function writes a string to the writer. If the size of the string
/// is greater than the buffer size, the buffer is flushed and the string is written
/// directly to the output stream. Otherwise, the string is written to the buffer.
/// If the buffer is full after writing the string, the buffer is flushed.
void BufferedWriter::write(const std::string& str) {
	if (str.size() > bufferSize_) {
		flush();
		outStream_ << str;
	}
	else {
		for (const char c : str) { buffer_.push_back(static_cast<unsigned char>(c)); }
		if (buffer_.size() >= bufferSize_) { flush(); }
	}
}

/// \brief Writes a line separator to the writer and returns the writer.
/// \details This function is a convenience method to write a line separator to the writer.
/// It writes a "\n" to the writer and returns the writer itself.
common::interface::Appendable<BufferedWriter>& BufferedWriter::newLine() {
	write("\n");
	return *this;
}

/// \brief Flushes the buffer.
/// \details This function flushes the buffer to the output stream. If the buffer is empty,
/// this function does nothing.
void BufferedWriter::flush() {
	if (!buffer_.empty()) {
		outStream_.write(reinterpret_cast<const char*>(buffer_.data()), static_cast<std::streamsize>(buffer_.size()));
		buffer_.clear();
	}
}

/// \brief Closes the writer.
/// \details This function flushes the buffer and closes the output stream.
void BufferedWriter::close() {
	flush();
	outStream_.close();
}

/// \brief Appends a character to the writer.
/// \details This function appends a character to the writer. If the buffer is full after appending the character,
/// the buffer is flushed.
BufferedWriter& BufferedWriter::append(char c) {
	buffer_.push_back(static_cast<unsigned char>(c));
	if (buffer_.size() >= bufferSize_) { flush(); }
	return *this;
}

/// \brief Appends a string to the writer.
/// \details This function appends a string to the writer. If the buffer is full after appending the string,
/// the buffer is flushed.
BufferedWriter& BufferedWriter::append(const std::string& str) {
	for (const char c : str) {
		buffer_.push_back(static_cast<unsigned char>(c));
		if (buffer_.size() >= bufferSize_) { flush(); }
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
BufferedWriter& BufferedWriter::append(const std::string& str, size_t start, size_t end) {
	if (start < str.length() && end <= str.length() && start < end) {
		for (size_t i = start; i < end; ++i) {
			buffer_.push_back(static_cast<unsigned char>(str[i]));
			if (buffer_.size() >= bufferSize_) { flush(); }
		}
	}
	return *this;
}
} // namespace commom::io
