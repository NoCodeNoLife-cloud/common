// Created by author ethereal on 2024/12/12.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>
#include "AbstractReader.hpp"

namespace common::io
{
/// \brief A class for converting byte input streams into character streams using a specified charset.
/// \details The InputStreamReader class reads bytes from an input stream and converts them to characters based on the specified charset.
/// It inherits from AbstractReader and implements the necessary methods for reading characters, marking, resetting, and closing the stream.
class InputStreamReader final : public AbstractReader
{
public:
	explicit InputStreamReader(std::shared_ptr<AbstractReader> input);
	explicit InputStreamReader(std::shared_ptr<AbstractReader> input, const std::string& charsetName);
	~InputStreamReader() override;
	auto read() -> int override;
	auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
	[[nodiscard]] auto ready() const -> bool override;
	auto close() -> void override;
	auto mark(size_t) -> void override;
	auto reset() -> void override;

private:
	std::shared_ptr<AbstractReader> reader_;
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter_;
};
}
