// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "ByteArrayInputStream.hpp"
#include <stdexcept>

namespace common::io
{
ByteArrayInputStream::ByteArrayInputStream(const std::vector<std::byte>& buf): buffer_(buf) {}

/// \brief Reads the next byte of data from this input stream.
/// \details The value byte is returned as an int in the range 0 to 255.
/// If no byte is available because the end of the stream has been reached, the value -1 is returned.
/// This method blocks until input data is available, the end of the stream is detected, or an exception is thrown.
/// \return The next byte of data, or -1 if the end of the stream has been reached.
auto ByteArrayInputStream::read() -> std::byte {
	if (pos_ >= buffer_.size()) {
		return static_cast<std::byte>(-1);
	}
	return buffer_[pos_++];
}

/// \brief Skips over and discards n bytes of data from this input stream.
/// \details The skip method increases the position by the number of bytes skipped, up to n,
/// or until the end of the buffer is reached. If the end of the buffer is reached before
/// n bytes are skipped, it returns the actual number of bytes skipped.
/// \param n The number of bytes to skip.
/// \return The number of bytes actually skipped.
auto ByteArrayInputStream::skip(const size_t n) -> size_t {
	const size_t available = buffer_.size() - pos_;
	const size_t bytesToSkip = std::min(n, available);
	pos_ += bytesToSkip;
	return bytesToSkip;
}

/// \brief Reads bytes from the input stream into a specified buffer.
/// \details This method reads up to len bytes from the input stream into the provided buffer vector, starting at the specified offset.
/// It copies bytes from the internal buffer to the given buffer. If the end of the stream is reached before reading the requested number of bytes,
/// it returns the actual number of bytes read. If the offset and length exceed the size of the buffer, an exception is thrown.
/// \param cBuf The buffer into which the data is read.
/// \param off The starting position in the buffer to write the data.
/// \param len The maximum number of bytes to read into the buffer.
/// \return The total number of bytes read into the buffer, or 0 if the end of the stream has been reached.
/// \throws std::out_of_range If the offset and length exceed the size of the buffer.
auto ByteArrayInputStream::read(std::vector<std::byte>& cBuf, const size_t off, size_t len) -> size_t {
	if (off + len > cBuf.size()) {
		throw std::out_of_range("Offset and length exceed the size of the buffer");
	}
	if (const size_t remaining = buffer_.size() - pos_; len > remaining) {
		len = remaining;
	}
	if (pos_ >= buffer_.size()) {
		return 0;
	}
	std::copy_n(buffer_.begin() + static_cast<std::ptrdiff_t>(pos_), len, cBuf.begin() + static_cast<std::ptrdiff_t>(off));
	pos_ += len;
	return len;
}

/// \brief Returns an estimate of the number of bytes that can be read (or skipped over) from this input stream without blocking.
/// \details The available method for a ByteArrayInputStream returns the number of remaining bytes that can be read from the source buffer.
/// \return An estimate of the number of bytes that can be read (or skipped over) from this input stream without blocking.
size_t ByteArrayInputStream::available() {
	return buffer_.size() - pos_;
}

/// \brief Resets the position of the input stream to the last marked position.
/// \details The reset method resets the position of the input stream to the last marked position.
/// If no mark has been set, the position is reset to the beginning of the stream (position 0).
void ByteArrayInputStream::reset() {
	pos_ = markPosition_;
}

/// \brief Sets the current marked position in the stream.
/// \details The markPosition method sets the current marked position in the stream.
/// The marked position is the position up to which data can be read from the source buffer.
/// If an I/O error occurs, the marked position is not changed.
/// \param readAheadLimit The maximum number of bytes that can be read from the source buffer.
void ByteArrayInputStream::mark(const size_t readAheadLimit) {
	markPosition_ = std::min(readAheadLimit, buffer_.size());
}

/// \brief Tests if this input stream supports the mark and reset methods.
/// \details This method returns true indicating that the ByteArrayInputStream supports
/// the mark and reset methods, allowing the current position in the stream to be saved
/// and reverted to later.
/// \return true since this ByteArrayInputStream supports the mark and reset methods.
auto ByteArrayInputStream::markSupported() const -> bool {
	return true;
}

/// \brief Closes this input stream and releases any system resources associated with the stream.
/// \details The close method of ByteArrayInputStream does nothing.
auto ByteArrayInputStream::close() -> void {
	// do nothing
}
}
