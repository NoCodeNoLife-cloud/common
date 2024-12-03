// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef BYTEARRAYINPUTSTREAM_HPP
#define BYTEARRAYINPUTSTREAM_HPP
#include <vector>
#include "AbstractInputStream.hpp"

namespace common::io
{
class ByteArrayInputStream final : public AbstractInputStream
{
public:
	explicit ByteArrayInputStream(const std::vector<char>& buf);
	auto read() -> int override;
	auto skip(std::size_t n) -> std::size_t;
	auto read(std::vector<char>& cBuf, std::size_t off, std::size_t len) -> std::size_t;
	[[nodiscard]] std::size_t available() const override;
	void reset() override;
	void mark(size_t readAheadLimit);
	[[nodiscard]] auto markSupported() const -> bool override;
	auto close() -> void override;

private:
	const std::vector<char> buffer_;
	std::size_t pos_{0};
	std::size_t markPosition_{0};
};
} // namespace common::io
#endif //BYTEARRAYINPUTSTREAM_HPP
