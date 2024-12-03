// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef STRINGWRITER_HPP
#define STRINGWRITER_HPP
#include <sstream>
#include "interface/Appendable.hpp"
#include "interface/Closeable.hpp"
#include "interface/Flushable.hpp"

namespace common::io
{
/// \brief A final class for writing characters to a string buffer.
/// \details The StringWriter class provides methods to write data to an internal string buffer.
/// It implements the Closeable, Flushable, and Appendable interfaces.
/// The class allows appending characters and strings, as well as flushing and closing operations.
/// It is useful for accumulating strings into a single string buffer and then retrieving the full content.
class StringWriter final : public interface::Closeable,
                           public interface::Flushable,
                           public interface::Appendable<StringWriter>
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
	[[nodiscard]] auto toString() const -> std::string;
	auto write(const char* cBuf, size_t off, size_t len) -> void;
	auto write(char c) -> void;
	auto write(const std::string& str) -> void;
	auto write(const std::string& str, size_t off, size_t len) -> void;

private:
	std::ostringstream buffer_;
};
} // namespace common::io
#endif // STRINGWRITER_HPP
