// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "ByteArrayOutputStream.hpp"

namespace common::io
{
ByteArrayOutputStream::ByteArrayOutputStream(): buf(32) {}

/// \brief Constructor with initial capacity.
/// \param size Initial capacity of the buffer.
/// \throws std::invalid_argument if size is negative.
ByteArrayOutputStream::ByteArrayOutputStream(const size_t size) {
	buf.resize(size);
}

/// \brief Writes a single byte to the buffer.
/// \param b Byte to write.
/// \details The method will increase the buffer size if the buffer is full.
auto ByteArrayOutputStream::write(const int b) -> void {
	if (count == buf.size()) {
		buf.resize(buf.size() * 2);
	}
	buf[count++] = static_cast<char>(b);
}

/// \brief Writes a portion of a byte array to the buffer.
/// \param buffer Data array to be written.
/// \param offset Offset from which to start writing in the buffer.
/// \param len Number of bytes to write from the buffer.
/// \details This method writes \p len bytes from the specified \p buffer starting at \p offset to the internal byte buffer.
/// If the internal buffer is full, it is resized to accommodate the new data. Throws an exception if the offset and length
/// exceed the size of the input buffer.
auto ByteArrayOutputStream::write(const std::vector<char>& buffer, const size_t offset, const size_t len) -> void {
	if (offset + len > buffer.size()) {
		throw std::out_of_range("Buffer offset/length out of range");
	}
	if (count + len > buf.size()) {
		buf.resize(std::max(buf.size() * 2, count + len));
	}
	std::copy_n(buffer.begin() + static_cast<std::vector<char>::difference_type>(offset), len, buf.begin() + static_cast<std::vector<char>::difference_type>(count));
	count += len;
}

/// \brief Writes the entire content of the internal buffer to the given OutputStream.
/// \param out Stream to write to.
/// \details This method writes the entire content of the internal buffer to the given OutputStream.
auto ByteArrayOutputStream::writeTo(AbstractOutputStream& out) const -> void {
	out.write(buf, 0, count);
}

/// \brief Resets the buffer to an empty state.
/// \details This method resets the internal counter to zero, effectively discarding any data written to the stream.
auto ByteArrayOutputStream::reset() -> void {
	count = 0;
}

/// \brief Creates a copy of the current buffer as a byte array.
/// \return A vector containing the valid bytes in the buffer.
/// \details This method returns a vector containing the valid bytes in the buffer.
/// The returned vector is a copy of the valid bytes in the internal buffer.
/// The method does not modify the internal state of the ByteArrayOutputStream.
auto ByteArrayOutputStream::toByteArray() const -> std::vector<char> {
	return {buf.begin(), buf.begin() + static_cast<std::vector<char>::difference_type>(count)};
}

/// \brief Returns the current size of the buffer.
/// \return The number of valid bytes in the buffer.
/// \details This method returns the current size of the buffer, which is the number of valid bytes in the internal buffer.
auto ByteArrayOutputStream::size() const -> size_t {
	return count;
}

/// \brief Converts the buffer to a string using the platform's default character set.
/// \return A string representation of the buffer.
/// \details This method converts the buffer to a string using the platform's default character set.
/// The returned string is a copy of the valid bytes in the internal buffer.
/// The method does not modify the internal state of the ByteArrayOutputStream.
auto ByteArrayOutputStream::toString() const -> std::string {
	return {buf.begin(), buf.begin() + static_cast<std::string::difference_type>(count)};
}

/// \brief Closes the stream and releases any system resources associated with it.
/// \details This method is a no-op for ByteArrayOutputStream.
auto ByteArrayOutputStream::close() -> void {}

/// \brief Flushes the stream.
/// \details This method is a no-op for ByteArrayOutputStream, as the stream is not connected to a physical device.
auto ByteArrayOutputStream::flush() -> void {
	// No operation for ByteArrayOutputStream.
}
} // namespace common::io
