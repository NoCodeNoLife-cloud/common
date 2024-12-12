// Created by author ethereal on 2024/12/15.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "FilterReader.hpp"

namespace common::io
{
class PushbackReader final : public FilterReader
{
public:
	explicit PushbackReader(std::shared_ptr<AbstractReader> reader) : PushbackReader(std::move(reader), DEFAULT_BUFFER_SIZE) {}

	PushbackReader(std::shared_ptr<AbstractReader> reader, size_t size) : FilterReader(std::move(reader)), buffer_(size) {
		if (size == 0) {
			throw std::invalid_argument("Buffer size must be greater than zero.");
		}
	}

	/// \brief Closes the PushbackReader and clears its buffer.
	/// \details This function overrides the close method of the FilterReader to perform additional
	/// operations specific to PushbackReader. It ensures that the underlying reader is closed
	/// and the pushback buffer is cleared, releasing any resources associated with it.
	auto close() -> void override {
		FilterReader::close();
		buffer_.clear();
	}

	/// \brief Marks the current position in the input stream.
	/// \details This method is overridden to indicate that marking is not supported
	/// in PushbackReader. Calling this method will result in a runtime error.
	/// \param readAheadLimit The maximum limit of bytes that can be read before the mark position becomes invalid. This parameter is unused.
	auto mark(size_t readAheadLimit) -> void override {
		throw std::runtime_error("mark() not supported.");
	}

	/// \brief Indicates whether the PushbackReader supports marking.
	/// \details This method is overridden to indicate that marking is not supported
	/// in PushbackReader. Calling this method will result in a runtime error.
	[[nodiscard]] auto markSupported() const -> bool override {
		return false;
	}

	/// \brief Reads a single character from the PushbackReader.
	/// \details This method attempts to read a single character from the pushback buffer.
	/// If the pushback buffer is exhausted, it reads from the underlying FilterReader.
	/// \return The character read as an integer, or -1 if the end of the stream has been reached.
	auto read() -> int override {
		if (bufferPos_ < buffer_.size()) {
			return buffer_[bufferPos_++];
		}
		return FilterReader::read();
	}

	/// \brief Reads characters from the PushbackReader into a buffer.
	/// \details This method attempts to read up to a specified number of characters into a buffer,
	/// starting at a given offset. It first reads from the pushback buffer, and if the requested
	/// number of characters is not fulfilled, it continues to read from the underlying FilterReader.
	/// An exception is thrown if the offset and length exceed the buffer's capacity.
	/// \param cBuf The buffer into which the characters are read.
	/// \param off The starting offset in the buffer.
	/// \param len The maximum number of characters to read.
	/// \return The total number of characters read into the buffer.
	/// \throws std::out_of_range if the offset and length exceed the buffer's capacity.
	auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override {
		if (off + len > cBuf.size()) {
			throw std::out_of_range("Buffer overflow.");
		}
		size_t bytesRead = 0;
		while (bufferPos_ < buffer_.size() && bytesRead < len) {
			cBuf[off++] = buffer_[bufferPos_++];
			bytesRead++;
		}
		if (bytesRead < len) {
			bytesRead += FilterReader::read(cBuf, off, len - bytesRead);
		}
		return bytesRead;
	}

	/// \brief Indicates whether the PushbackReader is ready to be read.
	/// \details This method returns true if the PushbackReader is ready to be read,
	/// i.e., if the pushback buffer is not empty or the underlying FilterReader is ready.
	[[nodiscard]] auto ready() const -> bool override {
		return bufferPos_ < buffer_.size() || FilterReader::ready();
	}

	/// \brief Resets the PushbackReader to its original state.
	/// \details This method resets the PushbackReader to its original state,
	/// i.e., it clears the pushback buffer and resets the underlying FilterReader.
	/// \throws std::runtime_error if reset() is not supported.
	auto reset() -> void override {
		throw std::runtime_error("reset() not supported.");
	}

	/// \brief Skips over characters in the PushbackReader.
	/// \details This method skips over up to a specified number of characters in the PushbackReader.
	/// It first discards characters from the pushback buffer, and if the requested
	/// number of characters is not fulfilled, it continues to skip characters from the underlying FilterReader.
	/// \param n The maximum number of characters to skip.
	/// \return The total number of characters skipped.
	auto skip(size_t n) -> size_t override {
		size_t skipped = 0;
		if (bufferPos_ < buffer_.size()) {
			const size_t bufferRemaining = buffer_.size() - bufferPos_;
			skipped = std::min(n, bufferRemaining);
			bufferPos_ += skipped;
			n -= skipped;
		}
		if (n > 0) {
			skipped += FilterReader::skip(n);
		}
		return skipped;
	}

	/// \brief Unreads characters in the PushbackReader.
	/// \details This method unread characters in the PushbackReader,
	/// i.e., it pushes the characters back into the pushback buffer.
	/// The characters are inserted into the front of the pushback buffer.
	auto unread(const std::vector<char>& cBuf) -> void {
		unread(cBuf, 0, cBuf.size());
	}

	/// \brief Unreads characters in the PushbackReader.
	/// \details This method unread characters in the PushbackReader,
	/// i.e., it pushes the characters back into the pushback buffer.
	/// The characters are inserted into the front of the pushback buffer.
	auto unread(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
		if (len > bufferPos_) {
			throw std::overflow_error("Pushback buffer overflow.");
		}
		for (size_t i = 0; i < len; ++i) {
			buffer_[--bufferPos_] = cBuf[off + len - 1 - i];
		}
	}

	/// \brief Unreads a single character in the PushbackReader.
	/// \details This method pushes a single character back into the pushback buffer.
	/// It allows the character to be read again in subsequent read operations.
	/// \param c The character to be unread.
	/// \throws std::overflow_error if the pushback buffer is full.
	auto unread(const int c) -> void {
		if (bufferPos_ == 0) {
			throw std::overflow_error("Pushback buffer overflow.");
		}
		buffer_[--bufferPos_] = static_cast<char>(c);
	}

private:
	static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
	std::vector<char> buffer_;
	size_t bufferPos_{DEFAULT_BUFFER_SIZE};
};
}
