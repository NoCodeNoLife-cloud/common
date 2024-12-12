// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "BufferedInputStream.hpp"

namespace common::io
{
BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in): BufferedInputStream(std::move(in), DEFAULT_BUFFER_SIZE) {}

BufferedInputStream::BufferedInputStream(std::unique_ptr<AbstractInputStream> in, const int size): FilterInputStream(std::move(in)), buf_(size) {
	if (!&inputStream_) {
		throw std::invalid_argument("Input stream cannot be null");
	}
	if (size <= 0) {
		throw std::invalid_argument("Buffer size must be greater than zero");
	}
}

/// \brief Returns the number of bytes that can be read from the input stream without blocking.
/// \details This function calculates the available bytes in the buffer and adds it to the available bytes in the underlying input stream.
/// \return The total number of bytes available for reading without blocking.
auto BufferedInputStream::available() const -> size_t {
	return count_ - pos_ + inputStream_->available();
}

/// \brief Closes the input stream and releases its resources.
/// \details This function closes the underlying input stream, clears the buffer, and resets the position and mark position.
/// \note This function does not throw any exceptions.
auto BufferedInputStream::close() -> void {
	inputStream_->close();
	buf_.clear();
}

/// \brief Marks the current position in the stream.
/// \details This method sets a mark position in the stream that can be reset to later.
/// The `readLimit` parameter defines the maximum limit of bytes that can be read
/// before the mark position becomes invalid.
/// \param readLimit The limit of bytes that can be read before the mark position becomes invalid.
auto BufferedInputStream::mark(const int readLimit) -> void {
	markLimit_ = readLimit;
	inputStream_->mark(readLimit);
	markPos_ = pos_;
}

/// \brief Tests if this input stream supports the mark and reset methods.
/// \details Whether this input stream supports the mark and reset methods.
/// \return true if this input stream supports the mark and reset methods, false otherwise.
auto BufferedInputStream::markSupported() const -> bool {
	return true;
}

/// \brief Reads the next byte of data from the input stream.
/// \details This function reads the next byte of data from the input stream and returns it as an integer.
/// If the end of the stream is reached, it returns -1 to indicate EOF.
/// \return The byte read as an integer, or -1 if the end of the stream is reached.
auto BufferedInputStream::read() -> std::byte {
	if (pos_ >= count_) {
		fillBuffer();
		if (pos_ >= count_) {
			return static_cast<std::byte>(-1);
		}
	}
	return buf_[pos_++];
}

/// \brief Reads a portion of the stream into a byte array.
/// \details This function reads up to len bytes of data from the input stream into a byte array buffer.
/// The data is written to the buffer starting at offset, and the number of bytes read is returned.
/// If the end of the stream is reached before a byte could be read, or if an I/O error occurs, then -1 is returned.
/// \param buffer The buffer to write the data to.
/// \param offset The starting offset in the buffer.
/// \param len The maximum number of bytes to read.
/// \return The total number of bytes read into the buffer, or -1 if there is no more data because the end of the stream has been reached.
auto BufferedInputStream::read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t {
	if (offset + len > static_cast<int>(buffer.size())) {
		throw std::out_of_range("Buffer offset/length out of range");
	}
	size_t totalBytesRead = 0;
	while (len > 0) {
		size_t bytesAvailable = count_ - pos_;
		if (bytesAvailable <= 0) {
			fillBuffer();
			bytesAvailable = count_ - pos_;
			if (bytesAvailable <= 0) {
				break;
			}
		}
		const size_t bytesToRead = std::min(len, bytesAvailable);
		std::copy_n(buf_.begin() + static_cast<long long>(pos_), bytesToRead, buffer.begin() + static_cast<long long>(offset));
		pos_ += bytesToRead;
		offset += bytesToRead;
		len -= bytesToRead;
		totalBytesRead += bytesToRead;
	}
	return totalBytesRead > 0 ? totalBytesRead : -1;
}

/// \brief Resets the stream to the last marked position.
/// \details This method resets the position in the stream to the last marked position
/// by calling the mark() method. If a mark has not been set, this method does nothing.
/// \throws std::ios_base::failure If an error occurs while resetting the stream.
auto BufferedInputStream::reset() -> void {
	pos_ = markPos_;
	inputStream_->reset();
}

/// \brief Skips over and discards n bytes of data from this input stream.
/// \details The skip method may, for a variety of reasons, end before skipping n bytes.
/// \param n The number of bytes to skip.
/// \return The number of bytes actually skipped.
/// \throws std::invalid_argument If the skip value is negative.
auto BufferedInputStream::skip(size_t n) -> size_t {
	if (n <= 0) {
		return 0;
	}
	size_t skipped = 0;
	while (n > 0) {
		size_t bytesAvailable = count_ - pos_;
		if (bytesAvailable <= 0) {
			fillBuffer();
			bytesAvailable = count_ - pos_;
			if (bytesAvailable <= 0) {
				break;
			}
		}
		const auto bytesToSkip = std::min(bytesAvailable, n);
		pos_ += bytesToSkip;
		n -= bytesToSkip;
		skipped += bytesToSkip;
	}
	return skipped;
}

/// \brief Fills the internal buffer with data from the underlying input stream.
/// \details This method reads data from the underlying input stream into the internal buffer.
/// If a mark has been set, it will be cleared if the buffer is filled in such a way that the
/// mark position is no longer valid.
auto BufferedInputStream::fillBuffer() -> void {
	if (markPos_ < 0 || pos_ - markPos_ >= markLimit_) {
		markPos_ = -1;
	}
	if (const size_t bytesRead = inputStream_->read(buf_); bytesRead > 0) {
		pos_ = 0;
		count_ = bytesRead;
	}
	else {
		count_ = 0;
	}
}
}
