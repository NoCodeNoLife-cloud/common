// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>
#include <vector>
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceReadable.hpp"

namespace common::io
{
/// \brief Abstract class for reading character streams.
/// \details The Reader class provides an interface for reading character streams. It is an abstract class that implements
/// the Closeable and Readable interfaces, requiring derived classes to implement methods for reading characters into
/// buffers, marking, and resetting the stream. The class also provides methods to check if marking is supported,
/// determine if the stream is ready to be read, and skip characters.
class AbstractReader abstract : public interface::IfaceCloseable, public interface::IfaceReadable
{
public:
	~AbstractReader() override;
	auto read() -> int override;
	virtual auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t = 0;
	virtual auto read(std::vector<char>& cBuf) -> size_t;
	[[nodiscard]] virtual auto markSupported() const -> bool;
	virtual auto mark(size_t readAheadLimit) -> void =0;
	virtual auto reset() -> void =0;
	[[nodiscard]] virtual auto ready() const -> bool;
	virtual auto skip(size_t n) -> size_t;
};
}
