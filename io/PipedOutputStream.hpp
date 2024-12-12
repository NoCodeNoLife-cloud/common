// Created by author ethereal on 2024/12/14.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "AbstractOutputStream.hpp"
#include "PipedInputStream.hpp"

namespace common::io
{
class PipedInputStream;

/// \brief A final class for writing bytes to a pipe.
/// \details The PipedOutputStream class provides methods to write bytes to a pipe.
/// It is a concrete implementation of the AbstractOutputStream interface.
/// The class supports writing single bytes and byte arrays, with the option to specify offsets and lengths.
/// The class also supports flushing and closing the stream, as well as checking if the stream is closed.
/// \remark The class is designed to handle pipe output operations, with options for connecting to a PipedInputStream.
class PipedOutputStream final : public AbstractOutputStream
{
public:
	PipedOutputStream() = delete;
	explicit PipedOutputStream(const std::shared_ptr<PipedInputStream>& snk);
	~PipedOutputStream() override;
	auto close() -> void override;
	auto flush() -> void override;
	auto write(std::byte b) -> void override;
	auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;

protected:
	std::shared_ptr<PipedInputStream> snk_;
	bool closed_{true};
	bool connected_{false};
};
}
