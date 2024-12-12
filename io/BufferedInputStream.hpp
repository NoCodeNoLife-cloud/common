// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <vector>
#include "FilterInputStream.hpp"

namespace common::io
{
/// \brief A class that reads characters from a stream with buffering.
/// \details It reads characters from a stream with buffering. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The buffer size can be specified in the constructor.
class BufferedInputStream final : public FilterInputStream
{
public:
	explicit BufferedInputStream(std::unique_ptr<AbstractInputStream> in);
	BufferedInputStream(std::unique_ptr<AbstractInputStream> in, int size);
	[[nodiscard]] auto available() const -> size_t;
	auto close() -> void override;
	auto mark(int readLimit) -> void override;
	[[nodiscard]] auto markSupported() const -> bool override;
	auto read() -> std::byte override;
	auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
	auto reset() -> void override;
	auto skip(size_t n) -> size_t override;

protected:
	static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
	std::vector<std::byte> buf_;
	size_t count_{0};
	size_t markLimit_{0};
	size_t markPos_{0};
	size_t pos_{0};
	auto fillBuffer() -> void;
};
}
