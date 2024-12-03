// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef BUFFEREDREADER_HPP
#define BUFFEREDREADER_HPP
#include <iostream>
#include "Reader.hpp"

namespace common::io
{
/// \brief A final class that provides buffering for a Reader object.
/// \details This class provides buffering for a Reader object. Buffering can greatly improve performance by reducing the number
/// of calls to the underlying Reader object. The buffering is optional and can be disabled by calling the constructor with
/// a buffer size of 0.
class BufferedReader final : public interface::Closeable,
                             public interface::Readable
{
public:
	explicit BufferedReader(Reader& reader, int size);
	~BufferedReader() override;
	auto close() -> void override;
	auto mark(int readAheadLimit) -> void;
	[[nodiscard]] static auto markSupported() -> bool;
	auto reset() -> void;
	auto read() -> int override;
	auto read(char* cBuf, size_t off, size_t len) -> size_t;
	auto readLine() -> std::string;
	[[nodiscard]] auto ready() const -> bool;
	auto skip(long n) -> long;

private:
	static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
	std::vector<char> buffer_;
	Reader& reader_;
	size_t bufferSize_{0};
	size_t pos_{0};
	size_t count_{0};
	size_t markLimit_{0};
	bool fillBuffer();
};
} // namespace common::io
#endif //BUFFEREDREADER_HPP
