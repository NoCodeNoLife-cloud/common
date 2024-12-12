// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <vector>
#include <glog/logging.h>
#include "AbstractWriter.hpp"
#include "interface/IfaceAppendable.hpp"

namespace common::io
{
/// \brief A class that writes characters to a stream with buffering.
/// \details It writes characters to a stream with buffering. The write and append methods are supported.
/// The available and markSupported methods are also supported.
/// \remark The buffer size can be specified in the constructor.
class BufferedWriter final : public common::io::AbstractWriter, public common::interface::IfaceAppendable<BufferedWriter>
{
public:
	explicit BufferedWriter(std::unique_ptr<std::ofstream> os, size_t size);
	~BufferedWriter() override;
	auto write(const std::string& str) -> void override;
	auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
	auto newLine() -> BufferedWriter&;
	auto flush() -> void override;
	auto close() -> void override;
	auto append(char c) -> BufferedWriter& override;
	auto append(const std::string& str) -> BufferedWriter& override;
	auto append(const std::string& str, size_t start, size_t end) -> BufferedWriter& override;
	[[nodiscard]] auto toString() const -> std::string override;

private:
	static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
	std::unique_ptr<std::ofstream> outputStream_;
	std::vector<char> buffer_;
	size_t bufferSize_;
};
}
