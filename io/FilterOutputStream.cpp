// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "FilterOutputStream.hpp"

namespace common::io
{
FilterOutputStream::FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream): outputStream_(std::move(outputStream)) {}

FilterOutputStream::~FilterOutputStream() = default;

/// \brief Writes a single byte to the stream.
/// \param b The byte to write.
/// \throw std::runtime_error If the underlying stream is unavailable.
auto FilterOutputStream::write(const std::byte b) -> void {
	if (!outputStream_) {
		throw std::runtime_error("Output stream is not available");
	}
	outputStream_->write(b);
}

/// \brief Writes the entire buffer to the stream.
/// \param buffer The buffer containing the data to write.
/// \throw std::runtime_error If the underlying stream is unavailable.
void FilterOutputStream::write(const std::vector<std::byte>& buffer) {
	if (!outputStream_) {
		throw std::runtime_error("Output stream is not available");
	}
	outputStream_->write(buffer);
}

/// \brief Writes a portion of the buffer to the stream.
/// \param buffer The buffer containing the data to write.
/// \param offset The offset in the buffer at which to start writing.
/// \param len The number of bytes to write.
/// \throw std::runtime_error If the underlying stream is unavailable or the buffer is invalid.
void FilterOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
	if (!outputStream_) {
		throw std::runtime_error("Output stream is not available");
	}
	if (offset + len > buffer.size()) {
		throw std::out_of_range("Buffer overflow");
	}
	outputStream_->write(buffer, offset, len);
}

/// \brief Flushes the stream, forcing any buffered output bytes to be written.
/// \throw std::runtime_error If the underlying stream is unavailable.
auto FilterOutputStream::flush() -> void {
	if (!outputStream_) {
		throw std::runtime_error("Output stream is not available");
	}
	outputStream_->flush();
}

/// \brief Closes the stream and releases any system resources associated with it.
/// \throw std::runtime_error If the underlying stream is unavailable.
auto FilterOutputStream::close() -> void {
	if (!outputStream_) {
		throw std::runtime_error("Output stream is not available");
	}
	flush();
	outputStream_->close();
}
}
