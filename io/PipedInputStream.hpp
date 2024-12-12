// Created by author ethereal on 2024/12/14.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <mutex>
#include <vector>
#include "AbstractInputStream.hpp"
#include "PipedOutputStream.hpp"

namespace common::io
{
class PipedOutputStream;

/// \brief A class that reads bytes from a stream with pipe.
/// \details It reads bytes from a stream with pipe. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The pipe size can be specified in the constructor.
class PipedInputStream final : public AbstractInputStream
{
public:
	PipedInputStream();
	explicit PipedInputStream(size_t pipeSize);
	explicit PipedInputStream(const std::shared_ptr<PipedOutputStream>& src);
	explicit PipedInputStream(const std::shared_ptr<PipedOutputStream>& src, size_t pipeSize);
	~PipedInputStream() override;
	auto close() -> void override;
	[[nodiscard]] auto available() -> size_t override;
	auto read() -> std::byte override;
	auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
	auto connect(std::shared_ptr<PipedOutputStream> src) -> void;
	auto receive(std::byte b) -> void;

protected:
	std::vector<std::byte> buffer_{};
	size_t in_{0};
	size_t out_{0};
	static constexpr size_t PIPE_SIZE = 1024;
	std::mutex mutex_;
	std::shared_ptr<PipedOutputStream> src_;
};
}
