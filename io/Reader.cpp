// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Reader.hpp"

namespace common::io
{
Reader::~Reader() = default;

/// \brief Reads a single character.
/// \details Reads a single character from the reader and returns it. If the end of the stream has been reached, -1 is
/// returned.
/// \return The character read, or -1 if the end of the stream has been reached.
auto Reader::read() -> int {
	char c;
	const int result = read(&c, 0, 1);
	return result == -1 ? -1 : c;
}

/// \brief Reads characters into a buffer.
/// \details Reads characters into the specified buffer, starting at the beginning of the buffer.
/// \param cBuf The buffer into which the data is read.
/// \return The total number of characters read into the buffer, or -1 if the end of the stream has been reached.
auto Reader::read(std::vector<char>& cBuf) -> int { return read(cBuf.data(), 0, static_cast<int>(cBuf.size())); }

/// \brief Tests if this reader supports the mark and reset methods.
/// \details Whether this reader supports the mark and reset methods.
/// \return true if this reader supports the mark and reset methods, false otherwise.
auto Reader::markSupported() const -> bool { return false; }

/// \brief Tests if this reader is ready to be read.
/// \details Whether this reader is ready to be read.
/// \return true if this reader is ready to be read, false otherwise.
auto Reader::ready() const -> bool { return true; }

/// \brief Skips over and discards n characters of data from this reader.
/// \details The skip method may, for a variety of reasons, end before skipping n characters.
/// \param n The number of characters to skip.
/// \return The number of characters actually skipped.
/// \throws std::invalid_argument If the skip value is negative.
auto Reader::skip(const long n) -> long {
	if (n < 0) { throw std::invalid_argument("Skip value must be non-negative"); }
	long skipped = 0;
	while (skipped < n) {
		char buffer[1024];
		const long toRead = std::min(n - skipped, static_cast<long>(sizeof(buffer)));
		const int readCount = read(buffer, 0, static_cast<int>(toRead));
		if (readCount == -1) break;
		skipped += readCount;
	}
	return skipped;
}
} // namespace common::io
