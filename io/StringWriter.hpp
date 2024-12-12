// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <sstream>
#include <vector>
#include "AbstractWriter.hpp"
#include "interface/IfaceAppendable.hpp"

namespace common::io
{
/// \brief A final class for writing characters to a string buffer.
/// \details The StringWriter class provides methods to write data to an internal string buffer.
/// It implements the Closeable, Flushable, and Appendable interfaces.
/// The class allows appending characters and strings, as well as flushing and closing operations.
/// It is useful for accumulating strings into a single string buffer and then retrieving the full content.
class StringWriter final : public AbstractWriter, public interface::IfaceAppendable<StringWriter>
{
public:
	explicit StringWriter(size_t initialSize);
	~StringWriter() override;
	auto append(char c) -> StringWriter& override;
	auto append(const std::string& csq) -> StringWriter& override;
	auto append(const std::string& csq, size_t start, size_t end) -> StringWriter& override;
	auto close() -> void override;
	auto flush() -> void override;
	[[nodiscard]] auto getBuffer() const -> std::string;
	[[nodiscard]] auto toString() const -> std::string override;
	auto write(char c) -> void override;
	auto write(const std::string& str) -> void override;
	auto write(const std::string& str, size_t off, size_t len) -> void override;
	void write(const std::vector<char>& cBuf, size_t off, size_t len) override;

private:
	std::ostringstream buffer_;
};
}
