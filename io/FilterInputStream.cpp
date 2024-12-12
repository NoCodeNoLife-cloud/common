// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "FilterInputStream.hpp"

namespace common::io
{
FilterInputStream::FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream): inputStream_(std::move(inputStream)) {}

FilterInputStream::~FilterInputStream() = default;

/// \brief Returns the number of bytes that can be read without blocking.
/// \return The number of available bytes.
auto FilterInputStream::available() -> size_t {
	if (!inputStream_) {
		throw std::runtime_error("Input stream is not available");
	}
	return inputStream_->available();
}

/// \brief Marks the current position in the stream.
/// \param readLimit The maximum bytes to read before the mark becomes invalid.
void FilterInputStream::mark(const int readLimit) {
	if (!inputStream_) {
		throw std::runtime_error("Input stream is not available");
	}
	inputStream_->mark(readLimit);
}

/// \brief Checks if marking is supported by the stream.
/// \return `true` if marking is supported; otherwise, `false`.
bool FilterInputStream::markSupported() const {
	if (!inputStream_) {
		return false;
	}
	return inputStream_->markSupported();
}

/// \brief Reads the next byte from the stream.
/// \return The next byte as an `int`, or `-1` if end of stream is reached.
auto FilterInputStream::read() -> std::byte {
	if (!inputStream_) {
		throw std::runtime_error("Input stream is not available");
	}
	return inputStream_->read();
}

/// \brief Reads bytes into the provided buffer.
/// \param buffer The buffer to fill with bytes.
/// \return The number of bytes read.
size_t FilterInputStream::read(std::vector<std::byte>& buffer) {
	if (!inputStream_) {
		throw std::runtime_error("Input stream is not available");
	}
	return inputStream_->read(buffer);
}

/// \brief Reads bytes into the provided buffer starting at the given offset.
/// \param buffer The buffer to fill with bytes.
/// \param offset The start position in the buffer to write to.
/// \param len The maximum number of bytes to read.
/// \return The number of bytes read.
size_t FilterInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
	if (!inputStream_) {
		throw std::runtime_error("Input stream is not available");
	}
	return inputStream_->read(buffer, offset, len);
}

/// \brief Resets the stream to the most recent mark.
void FilterInputStream::reset() {
	if (!inputStream_) {
		throw std::runtime_error("Input stream is not available");
	}
	inputStream_->reset();
}

/// \brief Skips over the specified number of bytes in the stream.
/// \param n The number of bytes to skip.
/// \return The actual number of bytes skipped.
size_t FilterInputStream::skip(const size_t n) {
	if (!inputStream_) {
		throw std::runtime_error("Input stream is not available");
	}
	return inputStream_->skip(n);
}

/// \brief Closes the input stream and releases any system resources associated with the stream.
/// \details Closes the underlying input stream and releases any system resources associated with it.
auto FilterInputStream::close() -> void {
	inputStream_->close();
}
}
