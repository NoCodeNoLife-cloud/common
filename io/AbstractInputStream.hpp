// Created by author ethereal on 2024/12/4.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <fstream>
#include <vector>
#include "interface/IfaceCloseable.hpp"

namespace common::io
{
/// \brief Abstract class for input streams.
/// \details This abstract class provides a general interface for input streams.
/// It declares methods for reading from the stream, marking the stream, and resetting the stream.
/// The available method returns the number of bytes that can be read from the stream without blocking.
class AbstractInputStream abstract : public interface::IfaceCloseable
{
public:
	~AbstractInputStream() override;
	[[nodiscard]] virtual auto available() -> size_t = 0;
	virtual auto mark(int readLimit) -> void;
	[[nodiscard]] virtual auto markSupported() const -> bool;
	virtual auto read() -> std::byte = 0;
	virtual auto read(std::vector<std::byte>& buffer) -> size_t;
	virtual auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t;
	virtual auto reset() -> void;
	virtual auto skip(size_t n) -> size_t;
};
}
