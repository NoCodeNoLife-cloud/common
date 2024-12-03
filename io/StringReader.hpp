// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef STRINGREADER_HPP
#define STRINGREADER_HPP
#include <stdexcept>
#include <string>
#include "interface/Closeable.hpp"
#include "interface/Readable.hpp"

namespace common::io
{
/// \brief A class that reads characters from a string.
/// \details It is a concrete implementation of the interface::Readable interface.
/// It is used to read characters from a string. The mark and reset methods are supported.
class StringReader final : public interface::Closeable,
                           public interface::Readable
{
public:
	explicit StringReader(std::string s);
	~StringReader() override;
	auto close() -> void override;
	auto mark(int readAheadLimit) -> void;
	[[nodiscard]] static auto markSupported() -> bool;
	auto read() -> int override;
	auto read(char cBuf[], int off, int len) -> int;
	[[nodiscard]] auto ready() const -> bool;
	auto reset() -> void;
	auto skip(long ns) -> long;

private:
	std::string source_;
	size_t position_;
	size_t markPosition_;
	bool markSet_;
};
} // namespace common::io
#endif // STRINGREADER_HPP
