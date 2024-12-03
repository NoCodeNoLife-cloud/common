// Created by author ethereal on 2024/12/4.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP
#include <fstream>
#include <vector>
#include "interface/Closeable.hpp"

namespace common::io
{
/// \brief Abstract class for input streams.
/// \details This abstract class provides a general interface for input streams.
/// It declares methods for reading from the stream, marking the stream, and resetting the stream.
/// The available method returns the number of bytes that can be read from the stream without blocking.
class InputStream abstract : public interface::Closeable
{
public:
	~InputStream() override;
	[[nodiscard]] virtual auto available() const -> size_t = 0;
	virtual auto mark(int readLimit) -> void;
	[[nodiscard]] virtual auto markSupported() const -> bool;
	virtual auto read() -> int = 0;
	virtual auto read(std::vector<unsigned char>& buffer) -> int;
	virtual auto read(std::vector<unsigned char>& buffer, int offset, int len) -> int;
	virtual auto reset() -> void;
	virtual auto skip(int64_t n) -> int64_t;
};
} // namespace common::io
#endif // INPUTSTREAM_HPP
