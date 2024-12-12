// Created by author ethereal on 2024/12/12.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "InputStreamReader.hpp"

namespace common::io
{
InputStreamReader::InputStreamReader(std::shared_ptr<AbstractReader> input) : reader_(std::move(input)) {
	if (!reader_) {
		throw std::invalid_argument("Input stream cannot be null");
	}
}

InputStreamReader::InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName) : reader_(std::move(input)) {
	if (!reader_) {
		throw std::invalid_argument("Input stream cannot be null");
	}
	if (charsetName != "UTF-8") {
		throw std::invalid_argument("Only UTF-8 charset is supported in this implementation");
	}
}

InputStreamReader::~InputStreamReader() = default;

/// \brief Reads a single character from the input stream.
/// \return The character read from the input stream, or -1 if the end of the stream is reached.
/// \throws std::runtime_error if the input stream is not available.
/// \throws std::runtime_error if failed to decode byte to character.
int InputStreamReader::read() {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	std::vector<char> byteBuffer(4, 0);
	if (const size_t bytesRead = reader_->read(byteBuffer, 0, 1); bytesRead == 0) {
		return -1;
	}
	try {
		const char32_t charValue = converter_.from_bytes(byteBuffer.data())[0];
		return static_cast<int>(charValue);
	}
	catch (const std::exception&) {
		throw std::runtime_error("Failed to decode byte to character");
	}
}

/// \brief Reads characters into a buffer from the input stream.
/// \param cBuf The buffer to fill with characters.
/// \param off The offset in the buffer at which to start filling.
/// \param len The number of characters to read.
/// \return The number of characters read, or -1 if the end of the stream is reached.
/// \throws std::runtime_error if the input stream is not available.
/// \throws std::out_of_range if the buffer overflows.
/// \throws std::runtime_error if failed to decode bytes to characters.
auto InputStreamReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	if (off + len > cBuf.size()) {
		throw std::out_of_range("Buffer overflow");
	}
	std::vector<char> byteBuffer(len, 0);
	const size_t bytesRead = reader_->read(byteBuffer, 0, len);
	if (bytesRead == 0) {
		return -1;
	}
	try {
		auto chars = converter_.from_bytes(byteBuffer.data(), byteBuffer.data() + bytesRead);
		const size_t charsToCopy = std::min(chars.size(), len);
		std::copy_n(chars.begin(), charsToCopy, cBuf.begin() + static_cast<std::vector<char>::difference_type>(off));
		return charsToCopy;
	}
	catch (const std::exception&) {
		throw std::runtime_error("Failed to decode bytes to characters");
	}
}

/// \brief Checks if the input stream is ready to be read.
/// \return true if the input stream is ready, false otherwise.
/// \throws std::runtime_error if the input stream is not available.
bool InputStreamReader::ready() const {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	return reader_->ready();
}

/// \brief Closes the input stream.
/// \throws std::runtime_error if the input stream is not available.
auto InputStreamReader::close() -> void {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	reader_->close();
}

/// \brief Marks the current position in the input stream (not supported).
/// \throws std::runtime_error as mark is not supported.
auto InputStreamReader::mark(size_t) -> void {
	throw std::runtime_error("Mark not supported");
}

/// \brief Resets the input stream to the marked position (not supported).
/// \throws std::runtime_error as reset is not supported.
auto InputStreamReader::reset() -> void {
	throw std::runtime_error("Reset not supported");
}
}
