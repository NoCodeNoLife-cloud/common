// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "AbstractFilterReader.hpp"

namespace common::io
{
AbstractFilterReader::AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader): reader_(std::move(inputReader)) {
	if (!reader_) {
		throw std::invalid_argument("Input reader cannot be null");
	}
}

AbstractFilterReader::~AbstractFilterReader() = default;

/// \brief Reads the next character from this reader and returns it as an int.
/// \details This method returns the next character from this reader as an int.
/// It blocks until input data is available, the end of the stream is detected, or an exception is thrown.
/// \return The next character from this reader as an int, or -1 if the end of the stream has been reached.
auto AbstractFilterReader::read() -> int {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	return reader_->read();
}

/// \brief Reads a portion of the stream into a character array.
/// \details This method reads up to \c len characters of data from this reader into a character array buffer.
/// The data is written to the buffer starting at \c off, and the number of characters read is returned.
/// If the end of the stream is reached before any characters can be read, or if an error occurs, \c -1 is returned.
/// \param cBuf The buffer to write the data to.
/// \param off The starting offset in the buffer.
/// \param len The maximum number of characters to read.
/// \return The total number of characters read into the buffer, or \c -1 if the end of the stream has been reached.
auto AbstractFilterReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	if (off + len > cBuf.size()) {
		return -1;
	}
	return reader_->read(cBuf, off, len);
}

/// \brief Skips over and discards n characters of data from this reader.
/// \details The skip method forwards the skip request to the underlying input reader.
/// If the underlying reader is not available, an exception is thrown.
/// \param n The number of characters to skip.
/// \return The number of characters actually skipped.
auto AbstractFilterReader::skip(const size_t n) -> size_t {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	return reader_->skip(n);
}

/// \brief Tests if this reader is ready to be read.
/// \details Whether this reader is ready to be read. A reader is ready if the next read operation
/// will not block. This reader is ready if the underlying input reader is ready.
/// \return true if this reader is ready to be read, false otherwise.
auto AbstractFilterReader::ready() const -> bool {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	return reader_->ready();
}

/// \brief Tests if this reader supports the mark and reset methods.
/// \details Whether this reader supports the mark and reset methods.
/// This method simply forwards the request to the underlying input reader.
/// If the underlying reader is not available, an exception is thrown.
/// \return true if this reader supports the mark and reset methods, false otherwise.
auto AbstractFilterReader::markSupported() const -> bool {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	return reader_->markSupported();
}

/// \brief Sets the current marked position in the stream.
/// \details The mark method sets a mark position in the stream that can be reset to later.
/// The `readAheadLimit` parameter defines the maximum limit of characters that can be read
/// before the mark position becomes invalid.
/// If the underlying reader is not available, an exception is thrown.
/// \param readAheadLimit The limit of characters that can be read before the mark position becomes invalid.
auto AbstractFilterReader::mark(const size_t readAheadLimit) -> void {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	reader_->mark(readAheadLimit);
}

/// \brief Resets the FilterReader to the last marked position.
/// \details This method resets the position in the stream to the last marked position
/// by calling the reset method on the underlying input reader. If a mark has not been set,
auto AbstractFilterReader::reset() -> void {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	reader_->reset();
}

/// \brief Closes the FilterReader and releases its resources.
/// \details This method closes the underlying input reader and releases any system resources associated with it.
/// Once the stream has been closed, further read(), ready(), mark(), or reset() operations will throw.
/// Closing a previously closed stream has no effect.
auto AbstractFilterReader::close() -> void {
	if (!reader_) {
		throw std::runtime_error("Input stream is not available");
	}
	reader_->close();
}
}
