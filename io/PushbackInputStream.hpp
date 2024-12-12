// Created by author ethereal on 2024/12/15.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "FilterInputStream.hpp"

namespace common::io
{
/// \brief A class that reads bytes from a stream with pushback ability.
/// \details It reads bytes from a stream with pushback ability. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The pushback buffer size can be specified in the constructor.
class PushbackInputStream final : public FilterInputStream
{
public:
	explicit PushbackInputStream(std::unique_ptr<AbstractInputStream> inputStream, size_t bufferSize = 64);
	~PushbackInputStream() override;
	auto available() -> size_t override;
	auto read() -> std::byte override;
	auto read(std::vector<std::byte>& buffer) -> size_t override;
	auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
	void unread(const std::vector<std::byte>& buffer);
	void unread(const std::vector<std::byte>& buffer, size_t offset, size_t len);
	void unread(std::byte b);

private:
	std::vector<std::byte> pushbackBuffer_;
	size_t bufferPos_;
};
}
