// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef STRINGREADER_HPP
#define STRINGREADER_HPP
#include <stdexcept>
#include <string>
#include "AbstractReader.hpp"

namespace common::io
{
/// \brief A class that reads characters from a string.
/// \details It is a concrete implementation of the interface::Readable interface.
/// It is used to read characters from a string. The mark and reset methods are supported.
class StringReader final : public AbstractReader
{
public:
	explicit StringReader(std::string s);
	~StringReader() override;
	auto close() -> void override;
	auto mark(int readAheadLimit) -> void override;
	[[nodiscard]] auto markSupported() -> bool override;
	auto read() -> int override;
	auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
	[[nodiscard]] auto ready() const -> bool override;
	auto reset() -> void override;
	auto skip(long ns) -> long;

private:
	std::string source_;
	size_t position_;
	size_t markPosition_;
	bool markSet_;
};
} // namespace common::io
#endif // STRINGREADER_HPP
