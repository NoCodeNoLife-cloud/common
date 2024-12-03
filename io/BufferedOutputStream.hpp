// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef BUFFEREDOUTPUTSTREAM_HPP
#define BUFFEREDOUTPUTSTREAM_HPP
#include <vector>
#include "OutputStream.hpp"

namespace common::io
{
/// \brief A buffered output stream.
/// \details This class provides a buffered output stream. It is thread-safe and allows to write single bytes or a range of bytes to the underlying stream.
/// The constructor takes a reference to an output stream and the size of the internal buffer.
/// The write method writes a single byte to the internal buffer.
/// The write method writes a range of bytes to the internal buffer.
/// The flush method flushes the internal buffer to the underlying stream.
/// The close method closes the underlying stream.
class BufferedOutputStream final : public interface::Flushable,
                                   public interface::Closeable
{
public:
	explicit BufferedOutputStream(OutputStream& out);
	BufferedOutputStream(OutputStream& out, size_t size);
	~BufferedOutputStream() override;
	auto write(int b) -> void;
	auto write(const std::vector<unsigned char>& data, size_t offset, size_t len) -> void;
	auto flush() -> void override;
	auto close() -> void override;

private:
	static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
	OutputStream& outputStream_;
	size_t bufferSize_;
	std::vector<unsigned char> buffer_;
	size_t bufferPosition_;
	void flushBuffer();
};
} // namespace common::io
#endif //BUFFEREDOUTPUTSTREAM_HPP
