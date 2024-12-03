// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef BUFFEREDINPUTSTREAM_HPP
#define BUFFEREDINPUTSTREAM_HPP
#include <vector>
#include "InputStream.hpp"

namespace common::io
{
/// \brief A class that reads characters from a stream with buffering.
/// \details It reads characters from a stream with buffering. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The buffer size can be specified in the constructor.
class BufferedInputStream final : public interface::Closeable
{
public:
	explicit BufferedInputStream(InputStream& in);
	BufferedInputStream(InputStream& in, int size);
	[[nodiscard]] auto available() const -> size_t;
	auto close() -> void override;
	auto mark(int readLimit) -> void;
	[[nodiscard]] static auto markSupported() -> bool;
	auto read() -> int;
	auto read(std::vector<unsigned char>& buffer, size_t offset, size_t len) -> size_t;
	auto reset() -> void;
	auto skip(int64_t n) -> int64_t;

private:
	std::vector<unsigned char> buf_;
	size_t count_{0};
	size_t markLimit_{0};
	size_t markPos_{0};
	size_t pos_{0};
	InputStream& inputStream_;
	auto fillBuffer() -> void;
};
} // namespace common::io
#endif //BUFFEREDINPUTSTREAM_HPP
