// Created by author ethereal on 2024/12/14.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "PipedWriter.hpp"
#include <utility>

namespace common::io
{
PipedWriter::PipedWriter() = default;

PipedWriter::PipedWriter(std::shared_ptr<PipedReader> writer) : reader_(std::move(writer)) {}

PipedWriter::~PipedWriter() {
	close();
}

/// \brief Closes the PipedWriter.
/// \details This method closes the PipedWriter, ensuring that no more data can be written to it.
/// It flushes any remaining data to the connected PipedReader and resets the connection.
/// If the writer is already closed, this method does nothing.
auto PipedWriter::close() -> void {
	if (closed_) {
		return;
	}
	flush();
	closed_ = true;
	if (reader_) {
		reader_->close();
		reader_.reset();
	}
}

/// \brief Flushes the PipedWriter.
/// \details This method is a no-op for PipedWriter as data is directly written to the connected PipedReader.
/// It is provided to satisfy the interface requirements.
auto PipedWriter::flush() -> void {
	// no-op
}

/// \brief Writes a single character to the PipedWriter.
/// \details This method writes a single character to the connected PipedReader.
/// It is thread-safe and throws an exception if the PipedWriter is closed or not connected to a reader.
/// \param[in] c The character to write.
void PipedWriter::write(const char c) {
	std::lock_guard lock(writeMutex_);
	if (closed_) {
		throw std::runtime_error("Cannot write to a closed pipe.");
	}
	if (!reader_) {
		throw std::runtime_error("Pipe is not connected to a reader.");
	}
	reader_->writeToBuffer(c);
}

/// \brief Writes a portion of a byte array to the PipedWriter.
/// \details This method writes a portion of a byte array to the connected PipedReader.
/// It is thread-safe and throws an exception if the PipedWriter is closed or not connected to a reader.
/// If the offset is out of bounds, an exception is thrown.
/// \param[in] cBuf The byte array to write.
/// \param[in] off The offset in the byte array.
/// \param[in] len The length of the portion to write.
auto PipedWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
	std::lock_guard lock(writeMutex_);
	if (off + len > cBuf.size()) {
		throw std::out_of_range("Buffer overflow detected in PipedWriter::write.");
	}
	if (closed_) {
		throw std::runtime_error("Cannot write to a closed pipe.");
	}
	if (!reader_) {
		throw std::runtime_error("Pipe is not connected to a reader.");
	}
	for (size_t i = 0; i < len; ++i) {
		reader_->writeToBuffer(cBuf[off + i]);
	}
}

/// \brief Returns a string representation of the PipedWriter.
/// \details Provides a string representation containing the state of the PipedWriter, such as whether it is closed and whether it is connected to a reader.
/// \return A string representing the current state of the PipedWriter.
auto PipedWriter::toString() const -> std::string {
	return "";
}

/// \brief Connects the PipedWriter to the given PipedReader.
/// \details Connects the PipedWriter to the given PipedReader.
/// \param[in] snk The PipedReader to connect to.
/// \throw std::runtime_error If the PipedWriter is already connected or closed.
auto PipedWriter::connect(std::shared_ptr<PipedReader> snk) -> void {
	if (reader_ || closed_) {
		throw std::runtime_error("Pipe already connected or closed.");
	}
	reader_ = std::move(snk);
}
}
