// Created by author ethereal on 2024/12/9.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "AbstractReader.hpp"

namespace common::io
{
/// \brief A final class for reading characters from a character array.
/// \details The CharArrayReader class provides methods to read characters from a character array.
/// It is a concrete implementation of the AbstractReader interface.
/// This class supports marking and resetting, allowing the user to mark a position in the input and reset the stream to that position.
/// It also provides methods to check if the reader is ready to be read, skip characters, and close the reader.
class CharArrayReader final : public AbstractReader
{
public:
	explicit CharArrayReader(const std::vector<char>& buffer);
	CharArrayReader(const std::vector<char>& buffer, size_t offset, size_t length);
	~CharArrayReader() override;
	auto read() -> int override;
	auto read(std::vector<char>& b, size_t off, size_t len) -> size_t override;
	auto skip(size_t n) -> size_t override;
	[[nodiscard]] auto ready() const -> bool override;
	[[nodiscard]] auto markSupported() const -> bool override;
	auto mark(size_t readAheadLimit) -> void override;
	auto reset() -> void override;
	auto close() -> void override;

private:
	std::vector<char> buf_;
	size_t pos_{0};
	size_t markedPos_{0};
	size_t count_;
};
}
