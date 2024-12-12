// Created by author ethereal on 2024/12/14.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <memory>
#include <mutex>
#include "AbstractWriter.hpp"
#include "PipedReader.hpp"

namespace common::io
{
class PipedReader;

/// \brief A final class for writing characters to a pipe.
/// \details The PipedWriter class provides methods to write characters to a pipe.
/// It is a concrete implementation of the AbstractWriter interface.
/// The class supports writing single characters and character arrays, with the option to specify offsets and lengths.
/// The class also supports flushing and closing the stream, as well as appending characters and strings.
/// It is useful for writing text data to a stream with a specified character encoding.
/// \remark Instances of this class are not thread-safe. Synchronization is needed for concurrent access.
class PipedWriter final : public AbstractWriter
{
public:
	PipedWriter();
	explicit PipedWriter(std::shared_ptr<PipedReader> writer);
	~PipedWriter() override;
	auto close() -> void override;
	auto flush() -> void override;
	auto write(char c) -> void override;
	auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
	[[nodiscard]] auto toString() const -> std::string override;
	auto connect(std::shared_ptr<PipedReader> snk) -> void;

private:
	std::shared_ptr<PipedReader> reader_;
	bool closed_{false};
	std::mutex writeMutex_;
};
}
