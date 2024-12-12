// Created by author ethereal on 2024/12/14.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "PipedOutputStream.hpp"

namespace common::io
{
PipedOutputStream::PipedOutputStream(const std::shared_ptr<PipedInputStream>& snk) {
	if (!snk) {
		throw std::invalid_argument("PipedInputStream cannot be null");
	}
	snk_ = snk;
	connected_ = true;
	closed_ = false;
}

PipedOutputStream::~PipedOutputStream() {
	close();
}

/// \brief Closes the piped output stream.
/// \details If the stream is already closed, this method does nothing.
/// Otherwise, it flushes the stream and sets the closed flag.
/// If the stream is connected, it also closes the connected input stream.
auto PipedOutputStream::close() -> void {
	if (closed_) {
		return;
	}
	flush();
	connected_ = false;
	closed_ = true;
	if (snk_) {
		snk_->close();
	}
}

/// \brief Flushes the piped output stream.
/// \details This method does not actually flush any data, as the data is directly written to the connected input stream.
/// The method is provided to satisfy the interface requirements of the OutputStream interface.
/// If the stream is not connected or if the stream is closed, the method throws an exception.
auto PipedOutputStream::flush() -> void {
	if (closed_ || !connected_ || !snk_) {
		throw std::runtime_error("PipedOutputStream is not connected");
	}
	// no-op
}

/// \brief Writes a single byte to the piped output stream.
/// \details If the stream is not connected or if the stream is closed, the method throws an exception.
/// Otherwise, it writes the byte to the connected input stream.
auto PipedOutputStream::write(const std::byte b) -> void {
	if (closed_ || !connected_ || !snk_) {
		throw std::runtime_error("PipedOutputStream is not connected");
	}
	snk_->receive(b);
}

/// \brief Writes a portion of a byte array to the piped output stream.
/// \details If the stream is not connected or if the stream is closed, the method throws an exception.
/// Otherwise, it writes the specified portion of the byte array to the connected input stream.
void PipedOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
	if (closed_ || !connected_ || !snk_) {
		throw std::runtime_error("PipedOutputStream is not connected");
	}
	if (offset + len > buffer.size()) {
		throw std::out_of_range("Buffer overflow");
	}
	for (size_t i = 0; i < len; ++i) {
		snk_->receive(buffer[offset + i]);
	}
}
}
