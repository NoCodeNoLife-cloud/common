// Created by author ethereal on 2024/12/12.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>
#include "AbstractWriter.hpp"

namespace common::io
{
/// \brief A class that writes characters to an output stream using a specified charset.
/// \details The OutputStreamWriter class provides methods to write characters to an output stream.
/// It supports writing characters, strings, and character arrays, with the option to specify offsets and lengths.
/// The class also supports flushing and closing the stream, as well as appending characters and strings.
/// It uses a specified charset for encoding the characters into bytes.
/// The class is useful for writing text data to a stream with a specified character encoding.
/// \remark Instances of this class are not thread-safe. Synchronization is needed for concurrent access.
class OutputStreamWriter final : public AbstractWriter
{
public:
	OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream, const std::string& charsetName);
	explicit OutputStreamWriter(std::unique_ptr<AbstractWriter> outputStream);
	~OutputStreamWriter() override;
	[[nodiscard]] auto getEncoding() const -> std::string;
	auto write(char c) -> void override;
	auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
	auto write(const std::vector<char>& cBuf) -> void override;
	auto write(const std::string& str) -> void override;
	auto write(const std::string& str, size_t off, size_t len) -> void override;
	auto flush() -> void override;
	auto close() -> void override;
	auto append(char c) -> AbstractWriter& override;
	auto append(const std::string& csq) -> AbstractWriter& override;
	auto append(const std::string& csq, size_t start, size_t end) -> AbstractWriter& override;
	[[nodiscard]] auto toString() const -> std::string override;

private:
	std::unique_ptr<AbstractWriter> outputWriter_;
	std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter_;
	std::string charset_;
	bool closed_;
};
}
