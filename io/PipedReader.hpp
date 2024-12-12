// Created by author ethereal on 2024/12/14.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <mutex>
#include "AbstractReader.hpp"
#include "PipedWriter.hpp"

namespace common::io
{
class PipedWriter;

/// \brief A class that reads characters from a stream with pipe.
/// \details It reads characters from a stream with pipe. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The pipe size can be specified in the constructor.
class PipedReader final : public AbstractReader
{
public:
	PipedReader();
	explicit PipedReader(int pipeSize);
	explicit PipedReader(const std::shared_ptr<PipedWriter>& src);
	PipedReader(std::shared_ptr<PipedWriter> src, int pipeSize);
	~PipedReader() override;
	auto close() -> void override;
	auto read() -> int override;
	auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
	[[nodiscard]] auto ready() const -> bool override;
	auto connect(std::shared_ptr<PipedWriter> src) -> void;
	auto mark(size_t readAheadLimit) -> void override;
	auto reset() -> void override;
	[[nodiscard]] auto markSupported() const -> bool override;
	auto writeToBuffer(char c) -> void;

private:
	static constexpr int DEFAULT_PIPE_SIZE = 1024;
	std::shared_ptr<PipedWriter> src_;
	std::vector<char> buffer_;
	size_t bufferSize_{0};
	size_t readPos_{0};
	size_t writePos_{0};
	std::mutex readMutex_;
};
}
