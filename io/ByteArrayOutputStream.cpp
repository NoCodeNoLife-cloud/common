// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "ByteArrayOutputStream.hpp"

namespace common::io
{
ByteArrayOutputStream::ByteArrayOutputStream(): buf_(32) {}

/// \brief Constructor with initial capacity.
/// \param size Initial capacity of the buffer.
/// \throws std::invalid_argument if size is negative.
ByteArrayOutputStream::ByteArrayOutputStream(const size_t size) {
	buf_.resize(size);
}

/// \brief Writes a single byte to the buffer.
/// \param b Byte to write.
/// \details The method will increase the buffer size if the buffer is full.
auto ByteArrayOutputStream::write(const std::byte b) -> void {
	if (count_ == buf_.size()) {
		buf_.resize(buf_.size() * 2);
	}
	buf_[count_++] = b;
}

/// \brief Writes a portion of a byte array to the buffer.
/// \param buffer Data array to be written.
/// \param offset Offset from which to start writing in the buffer.
/// \param len Number of bytes to write from the buffer.
/// \details This method writes \p len bytes from the specified \p buffer starting at \p offset to the internal byte buffer.
/// If the internal buffer is full, it is resized to accommodate the new data. Throws an exception if the offset and length
/// exceed the size of the input buffer.
auto ByteArrayOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void {
	if (offset + len > buffer.size()) {
		throw std::out_of_range("Buffer offset/length out of range");
	}
	if (count_ + len > buf_.size()) {
		buf_.resize(std::max(buf_.size() * 2, count_ + len));
	}
	std::copy_n(buffer.begin() + static_cast<std::vector<char>::difference_type>(offset), len, buf_.begin() + static_cast<std::vector<char>::difference_type>(count_));
	count_ += len;
}

/// \brief Writes the entire content of the internal buffer to the given OutputStream.
/// \param out Stream to write to.
/// \details This method writes the entire content of the internal buffer to the given OutputStream.
auto ByteArrayOutputStream::writeTo(AbstractOutputStream& out) const -> void {
	out.write(buf_, 0, count_);
}

/// \brief Resets the buffer to an empty state.
/// \details This method resets the internal counter to zero, effectively discarding any data written to the stream.
auto ByteArrayOutputStream::reset() -> void {
	count_ = 0;
}

/// \brief Creates a copy of the current buffer as a byte array.
/// \return A vector containing the valid bytes in the buffer.
/// \details This method returns a vector containing the valid bytes in the buffer.
/// The returned vector is a copy of the valid bytes in the internal buffer.
/// The method does not modify the internal state of the ByteArrayOutputStream.
auto ByteArrayOutputStream::toByteArray() const -> std::vector<std::byte> {
	return {buf_.begin(), buf_.begin() + static_cast<std::vector<char>::difference_type>(count_)};
}

/// \brief Returns the current size of the buffer.
/// \return The number of valid bytes in the buffer.
/// \details This method returns the current size of the buffer, which is the number of valid bytes in the internal buffer.
auto ByteArrayOutputStream::size() const -> size_t {
	return count_;
}

/// \brief Converts the buffer to a string using the platform's default character set.
/// \return A string representation of the buffer.
/// \details This method converts the buffer to a string using the platform's default character set.
/// The returned string is a copy of the valid bytes in the internal buffer.
/// The method does not modify the internal state of the ByteArrayOutputStream.
auto ByteArrayOutputStream::toString() const -> std::string {
	return {reinterpret_cast<const char*>(buf_.data()), count_};
}

/// \brief Closes the stream and releases any system resources associated with it.
/// \details This method is a no-op for ByteArrayOutputStream.
auto ByteArrayOutputStream::close() -> void {}

/// \brief Flushes the stream.
/// \details This method is a no-op for ByteArrayOutputStream, as the stream is not connected to a physical device.
auto ByteArrayOutputStream::flush() -> void {
	// No operation for ByteArrayOutputStream.
}
}
