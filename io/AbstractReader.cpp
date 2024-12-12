// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "AbstractReader.hpp"

namespace common::io
{
AbstractReader::~AbstractReader() = default;

/// \brief Reads a single character.
/// \details Reads a single character from the reader and returns it. If the end of the stream has been reached, -1 is
/// returned.
/// \return The character read, or -1 if the end of the stream has been reached.
auto AbstractReader::read() -> int {
	std::vector<char> buffer(1);
	if (const size_t bytesRead = read(buffer, 0, 1); bytesRead == -1) {
		return -1;
	}
	return buffer[0];
}

/// \brief Reads characters into a buffer.
/// \details Reads characters into the specified buffer, starting at the beginning of the buffer.
/// \param cBuf The buffer into which the data is read.
/// \return The total number of characters read into the buffer, or -1 if the end of the stream has been reached.
auto AbstractReader::read(std::vector<char>& cBuf) -> size_t {
	return read(cBuf, 0, static_cast<int>(cBuf.size()));
}

/// \brief Tests if this reader supports the mark and reset methods.
/// \details Whether this reader supports the mark and reset methods.
/// \return true if this reader supports the mark and reset methods, false otherwise.
auto AbstractReader::markSupported() const -> bool {
	return false;
}

/// \brief Tests if this reader is ready to be read.
/// \details Whether this reader is ready to be read.
/// \return true if this reader is ready to be read, false otherwise.
auto AbstractReader::ready() const -> bool {
	return true;
}

/// \brief Skips over and discards n characters of data from this reader.
/// \details The skip method may, for a variety of reasons, end before skipping n characters.
/// \param n The number of characters to skip.
/// \return The number of characters actually skipped.
/// \throws std::invalid_argument If the skip value is negative.
auto AbstractReader::skip(const size_t n) -> size_t {
	size_t skipped = 0;
	while (skipped < n) {
		std::vector<char> buffer(1024);
		const size_t toRead = std::min(n - skipped, buffer.size());
		const size_t readCount = read(buffer, 0, static_cast<int>(toRead));
		if (readCount == -1) break;
		skipped += readCount;
	}
	return skipped;
}
}
