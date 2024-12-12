// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <vector>
#include "AbstractOutputStream.hpp"
#include "FilterOutputStream.hpp"

namespace common::io
{
/// \brief A buffered output stream.
/// \details This class provides a buffered output stream. It is thread-safe and allows to write single bytes or a range of bytes to the underlying stream.
/// The constructor takes a reference to an output stream and the size of the internal buffer.
/// The write method writes a single byte to the internal buffer.
/// The write method writes a range of bytes to the internal buffer.
/// The flush method flushes the internal buffer to the underlying stream.
/// The close method closes the underlying stream.
class BufferedOutputStream final : public FilterOutputStream
{
public:
	explicit BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out);
	BufferedOutputStream(std::unique_ptr<AbstractOutputStream> out, size_t size);
	~BufferedOutputStream() override;
	auto write(std::byte b) -> void override;
	auto write(const std::vector<std::byte>& data, size_t offset, size_t len) -> void override;
	auto flush() -> void override;
	auto close() -> void override;

protected:
	static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
	size_t bufferSize_;
	std::vector<std::byte> buffer_;
	size_t bufferPosition_;
	void flushBuffer();
};
}
