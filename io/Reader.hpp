// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef READER_HPP
#define READER_HPP
#include <format>
#include <vector>
#include "interface/Closeable.hpp"
#include "interface/Readable.hpp"

namespace common::io
{
/// \brief Abstract class for reading character streams.
/// \details The Reader class provides an interface for reading character streams. It is an abstract class that implements
/// the Closeable and Readable interfaces, requiring derived classes to implement methods for reading characters into
/// buffers, marking, and resetting the stream. The class also provides methods to check if marking is supported,
/// determine if the stream is ready to be read, and skip characters.
class Reader abstract : public interface::Closeable,
                        public interface::Readable
{
public:
	~Reader() override;
	virtual auto read(char* cBuf, size_t off, size_t len) -> int = 0;
	auto read() -> int override;
	virtual auto read(std::vector<char>& cBuf) -> int;
	[[nodiscard]] virtual auto markSupported() const -> bool;
	virtual auto mark(int /*readAheadLimit*/) -> void =0;
	virtual auto reset() -> void =0;
	[[nodiscard]] virtual auto ready() const -> bool;
	virtual auto skip(long n) -> long;
};
} // namespace common::io
#endif // READER_HPP
