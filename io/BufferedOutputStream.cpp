// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "BufferedOutputStream.hpp"

namespace common::io
{
BufferedOutputStream::BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out): BufferedOutputStream(std::move(out), DEFAULT_BUFFER_SIZE) {}

BufferedOutputStream::BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out, const size_t size): FilterOutputStream(std::move(out)), bufferSize_(size), buffer_(size), bufferPosition_(0) {
	if (!&outputStream_) {
		throw std::invalid_argument("Output stream cannot be null");
	}
	if (size == 0) {
		throw std::invalid_argument("Buffer size must be greater than 0");
	}
}

BufferedOutputStream::~BufferedOutputStream() {
	try {
		BufferedOutputStream::flush();
	}
	catch (...) {
		// Suppress exceptions in destructors
	}
}

/// \brief Writes a byte to the stream.
/// \details This function writes a byte to the output stream. If the buffer is full, it is flushed first.
/// \param b The byte to be written.
auto BufferedOutputStream::write(const std::byte b) -> void {
	if (bufferPosition_ >= bufferSize_) {
		flushBuffer();
	}
	buffer_[bufferPosition_++] = b;
}

/// \brief Writes a portion of a byte array to the stream.
/// \details This function writes a portion of a byte array to the output stream. If the buffer is full, it is flushed first.
/// \param data The byte array to be written.
/// \param offset The starting offset in the byte array.
/// \param len The number of bytes to write.
auto BufferedOutputStream::write(const std::vector<std::byte>& data, const size_t offset, const size_t len) -> void {
	if (offset + len > data.size()) {
		throw std::out_of_range("Data offset/length out of range");
	}
	size_t bytesWritten = 0;
	while (bytesWritten < len) {
		if (bufferPosition_ == bufferSize_) {
			flushBuffer();
		}
		const size_t bytesToCopy = std::min(len - bytesWritten, bufferSize_ - bufferPosition_);
		std::memcpy(&buffer_[bufferPosition_], &data[offset + bytesWritten], bytesToCopy);
		bufferPosition_ += bytesToCopy;
		bytesWritten += bytesToCopy;
	}
}

/// \brief Flushes the internal buffer.
/// \details This function flushes the internal buffer of the output stream. It is a no-op if the buffer is empty.
auto BufferedOutputStream::flush() -> void {
	flushBuffer();
	outputStream_->flush();
}

/// \brief Closes the output stream and releases its resources.
/// \details This function closes the underlying output stream and releases its resources.
auto BufferedOutputStream::close() -> void {
	outputStream_->close();
}

/// \brief Flushes the internal buffer.
/// \details This function flushes the internal buffer of the output stream to the underlying stream.
/// It is a no-op if the buffer is empty.
auto BufferedOutputStream::flushBuffer() -> void {
	if (bufferPosition_ > 0) {
		outputStream_->write(buffer_, 0, bufferPosition_);
		bufferPosition_ = 0;
	}
}
}
