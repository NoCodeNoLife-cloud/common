// Created by author ethereal on 2024/12/14.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "PipedReader.hpp"
#include <utility>

namespace common::io
{
PipedReader::PipedReader(): PipedReader(DEFAULT_PIPE_SIZE) {}

PipedReader::PipedReader(int pipeSize) : buffer_(pipeSize), bufferSize_(pipeSize) {}

PipedReader::PipedReader(const std::shared_ptr<PipedWriter>& src) : PipedReader(src, DEFAULT_PIPE_SIZE) {}

PipedReader::PipedReader(std::shared_ptr<PipedWriter> src, const int pipeSize) : src_(std::move(src)), buffer_(pipeSize), bufferSize_(pipeSize) {}

PipedReader::~PipedReader() {
	close();
}

/// \brief Closes the PipedReader.
/// \details This method closes the PipedReader, resetting the associated PipedWriter,
auto PipedReader::close() -> void {
	src_.reset();
	buffer_.clear();
	readPos_ = writePos_ = 0;
}

/// \brief Reads the next byte of data from this input stream.
/// \details The value byte is returned as an \c int in the range \c 0 to
/// \c 255. If no byte is available because the end of the stream has been
/// reached, the value \c -1 is returned. This method blocks until input data
/// is available, the end of the stream is detected, or an exception is thrown.
/// \return the next byte of data, or \c -1 if the end of the stream is reached.
auto PipedReader::read() -> int {
	std::lock_guard lock(readMutex_);
	if (!ready()) {
		return -1;
	}
	return buffer_[readPos_++ % bufferSize_];
}

/// \brief Reads characters into a portion of an array.
/// \details This method blocks until some input is available, the end of the
/// stream is detected, or an exception is thrown.
/// \param cBuf destination buffer. If the length of the destination buffer is
/// less than the number of bytes requested to be read, then the returned value
/// is the number of bytes actually read and the buffer is filled.
/// \param off the start offset of the data
/// \param len the maximum number of bytes to read
/// \return The number of bytes actually read, or -1 if the end of the stream has
/// been reached
auto PipedReader::read(std::vector<char>& cBuf, const size_t off, const size_t len) -> size_t {
	std::lock_guard lock(readMutex_);
	if (off + len > cBuf.size()) {
		throw std::out_of_range("index out of range");
	}
	size_t bytesRead = 0;
	while (bytesRead < len && ready()) {
		cBuf[off + bytesRead] = buffer_[readPos_++ % bufferSize_];
		++bytesRead;
	}
	return bytesRead;
}

/// \brief Tests if this reader is ready to be read.
/// \details Whether this reader is ready to be read. A reader is ready if the next read operation
/// will not block. This reader is ready if there is data available in the pipe.
/// \return true if this reader is ready to be read, false otherwise.
auto PipedReader::ready() const -> bool {
	return readPos_ != writePos_;
}

/// \brief Connects the piped reader to the given piped writer.
/// \details Connects the piped reader to the given piped writer.
/// \param[in] src The piped writer to connect to.
/// \throw std::runtime_error If the piped reader is already connected.
auto PipedReader::connect(std::shared_ptr<PipedWriter> src) -> void {
	if (src_) {
		throw std::runtime_error("already connected");
	}
	src_ = std::move(src);
}

auto PipedReader::mark(size_t readAheadLimit) -> void {
	// no-op
}

auto PipedReader::reset() -> void {
	// no-op
}

/// \brief Tests if this reader supports the mark and reset methods.
/// \details Whether this reader supports the mark and reset methods.
/// \return false if this reader supports the mark and reset methods, true otherwise.
bool PipedReader::markSupported() const {
	return false;
}

auto PipedReader::writeToBuffer(char c) -> void {
	if (bufferSize_ == 0) {
		throw std::runtime_error("Buffer not initialized or closed.");
	}
	const size_t nextWritePos = (writePos_ + 1) % bufferSize_;
	if (nextWritePos == readPos_) {
		throw std::runtime_error("Pipe buffer overflow: Reader has not consumed data.");
	}
	buffer_[writePos_] = c;
	writePos_ = nextWritePos;
}
}
