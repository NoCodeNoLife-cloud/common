// Created by author ethereal on 2024/12/10.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "AbstractWriter.hpp"

namespace common::io
{
/// \brief A class that writes characters to a character array.
/// \details The CharArrayWriter class implements an output stream in which the data is written into a character array.
/// The buffer automatically grows as data is written to it.
/// The class is designed for use as a drop-in replacement for an FileWriter in situations where writing to a file is not possible.
class CharArrayWriter final : public AbstractWriter, interface::IfaceAppendable<CharArrayWriter>
{
public:
	CharArrayWriter();
	explicit CharArrayWriter(int initialSize);
	~CharArrayWriter() override;
	auto write(char c) -> void override;
	auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
	auto write(const std::string& str, size_t off, size_t len) -> void override;
	auto writeTo(AbstractWriter& out) const -> void;
	auto append(const std::string& csq) -> CharArrayWriter& override;
	auto append(const std::string& csq, size_t start, size_t end) -> CharArrayWriter& override;
	auto append(char c) -> CharArrayWriter& override;
	auto reset() -> void;
	[[nodiscard]] auto toCharArray() const -> std::vector<char>;
	[[nodiscard]] auto size() const -> size_t;
	[[nodiscard]] auto toString() const -> std::string override;
	auto flush() -> void override;
	auto close() -> void override;

private:
	std::vector<char> buf_;
	size_t count_{0};
};
}
