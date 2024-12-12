// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <iostream>
#include "AbstractReader.hpp"

namespace common::io
{
/// \brief A final class that provides buffering for a Reader object.
/// \details This class provides buffering for a Reader object. Buffering can greatly improve performance by reducing the number
/// of calls to the underlying Reader object. The buffering is optional and can be disabled by calling the constructor with
/// a buffer size of 0.
class BufferedReader final : public AbstractReader
{
public:
	explicit BufferedReader(std::unique_ptr<AbstractReader> reader, int size);
	~BufferedReader() override;
	auto close() -> void override;
	auto mark(size_t readAheadLimit) -> void override;
	[[nodiscard]] auto markSupported() const -> bool override;
	auto reset() -> void override;
	auto read() -> int override;
	auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
	auto readLine() -> std::string;
	[[nodiscard]] auto ready() const -> bool override;
	auto skip(long n) -> long;

private:
	static constexpr size_t DEFAULT_BUFFER_SIZE = 8192;
	std::vector<char> buffer_;
	std::unique_ptr<AbstractReader> reader_;
	size_t bufferSize_{0};
	size_t pos_{0};
	size_t count_{0};
	size_t markLimit_{0};
	bool fillBuffer();
};
}
