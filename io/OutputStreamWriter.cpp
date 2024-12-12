// Created by author ethereal on 2024/12/12.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "OutputStreamWriter.hpp"

namespace common::io
{
OutputStreamWriter::OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream, const std::string& charsetName): outputWriter_(std::move(outputStream)), charset_(charsetName), closed_(false) {
	if (charsetName != "UTF-8") {
		throw std::invalid_argument("Unsupported encoding: " + charsetName);
	}
}

OutputStreamWriter::OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream): OutputStreamWriter(std::move(outputStream), "UTF-8") {}

OutputStreamWriter::~OutputStreamWriter() = default;

/// \brief Returns the name of the encoding being used.
/// \details This method returns the name of the encoding being used.
/// If the stream is closed, an empty string is returned.
/// \return The name of the encoding being used.
auto OutputStreamWriter::getEncoding() const -> std::string {
	return closed_ ? "" : charset_;
}

/// \brief Writes a single character to the stream.
/// \details This method writes a single character to the stream.
/// If the stream is closed, an exception is thrown.
/// \param c The character to write.
void OutputStreamWriter::write(const char c) {
	write(std::string(1, c));
}

/// \brief Writes a portion of a character buffer to the stream.
/// \details This method writes up to \p len characters from the specified buffer \p cBuf starting at \p off to the stream.
/// If the stream is closed or the offset and length exceed the buffer size, an exception is thrown.
/// \param cBuf The character buffer to be written.
/// \param off The starting position in the buffer to write from.
/// \param len The maximum number of characters to write from the buffer.
/// \throws std::ios_base::failure If the stream is closed or if writing fails.
/// \throws std::out_of_range If the offset and length exceed the buffer size.
auto OutputStreamWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
	if (closed_) {
		throw std::ios_base::failure("Stream is closed");
	}
	if (off + len > cBuf.size()) {
		throw std::out_of_range("Offset and length exceed buffer size");
	}
	outputWriter_->write(cBuf, off, len);
	if (!outputWriter_) {
		throw std::ios_base::failure("Failed to write to stream");
	}
}

/// \brief Writes the entire content of a character buffer to the stream.
/// \details This method writes the entire content of the specified buffer \p cBuf to the stream.
/// If the stream is closed or if writing fails, an exception is thrown.
/// \param cBuf The character buffer to be written.
/// \throws std::ios_base::failure If the stream is closed or if writing fails.
void OutputStreamWriter::write(const std::vector<char>& cBuf) {
	write(cBuf, 0, cBuf.size());
}

/// \brief Writes the entire content of a string to the stream.
/// \details This method converts the given string \p str to a character buffer and writes it to the stream.
/// If the stream is closed or if writing fails, an exception is thrown.
/// \param str The string to be written.
/// \throws std::ios_base::failure If the stream is closed or if writing fails.
void OutputStreamWriter::write(const std::string& str) {
	write(std::vector<char>(str.begin(), str.end()));
}

/// \brief Writes a portion of a string to the stream.
/// \details This method writes up to \p len characters from the specified string \p str starting at \p off to the stream.
/// If the stream is closed or if the offset and length exceed the string size, an exception is thrown.
/// \param str The string to be written.
/// \param off The starting position in the string to write from.
/// \param len The maximum number of characters to write from the string.
/// \throws std::ios_base::failure If the stream is closed or if writing fails.
/// \throws std::out_of_range If the offset and length exceed the string size.
void OutputStreamWriter::write(const std::string& str, const size_t off, const size_t len) {
	if (off + len > str.size()) {
		throw std::out_of_range("Offset and length exceed string size");
	}
	write(std::vector(str.begin() + static_cast<std::string::difference_type>(off), str.begin() + static_cast<std::string::difference_type>(off + len)));
}

/// \brief Flushes the stream.
/// \details This method flushes the stream. If the stream is closed or if flushing fails, an exception is thrown.
/// \throws std::ios_base::failure If the stream is closed or if flushing fails.
auto OutputStreamWriter::flush() -> void {
	if (closed_) {
		throw std::ios_base::failure("Stream is closed");
	}
	outputWriter_->flush();
	if (!outputWriter_) {
		throw std::ios_base::failure("Failed to flush stream");
	}
}

/// \brief Closes the stream.
/// \details This method closes the stream. If the stream is already closed, the method does nothing.
/// \throws std::ios_base::failure If the stream is closed or if closing fails.
auto OutputStreamWriter::close() -> void {
	if (closed_) {
		return;
	}
	flush();
	closed_ = true;
}

/// \brief Appends a character to the writer.
/// \details This method appends a single character to the stream by writing it to the underlying output stream.
/// It facilitates method chaining by returning a reference to the current OutputStreamWriter object, allowing for
/// multiple append calls to be chained together.
/// \param c The character to append to the writer.
/// \return A reference to the current OutputStreamWriter object.
AbstractWriter& OutputStreamWriter::append(const char c) {
	write(c);
	return *this;
}

/// \brief Appends a string to the writer.
/// \details This method appends the specified string \p csq to the stream by writing it to the underlying output stream.
/// It facilitates method chaining by returning a reference to the current OutputStreamWriter object, allowing for
/// multiple append calls to be chained together.
/// \param csq The string to append to the writer.
/// \return A reference to the current OutputStreamWriter object.
AbstractWriter& OutputStreamWriter::append(const std::string& csq) {
	write(csq);
	return *this;
}

/// \brief Appends a substring to the writer.
/// \details This method appends the specified substring \p csq to the stream by writing it to the underlying output stream.
/// The substring is defined by the range [start, end).
/// If the start or end indexes are out of bounds, or if start is greater than end,
/// the function does nothing.
/// It facilitates method chaining by returning a reference to the current OutputStreamWriter object, allowing for
/// multiple append calls to be chained together.
/// \param csq The string to append to the writer.
/// \param start The starting index (inclusive) of the substring to append.
/// \param end The ending index (exclusive) of the substring to append.
/// \return A reference to the current OutputStreamWriter object.
AbstractWriter& OutputStreamWriter::append(const std::string& csq, const size_t start, const size_t end) {
	write(csq, start, end - start);
	return *this;
}

/// \brief Gets the string representation of the writer.
/// \details This method returns the string representation of the writer by calling the toString method of the
/// underlying output stream. If the stream is closed, it throws an exception.
/// \return The string representation of the writer.
auto OutputStreamWriter::toString() const -> std::string {
	if (closed_) {
		throw std::ios_base::failure("Stream is closed");
	}
	return outputWriter_->toString();
}
}
