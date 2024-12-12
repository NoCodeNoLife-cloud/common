// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <memory>
#include "AbstractWriter.hpp"

namespace common::io
{
/// \brief Abstract class for writing filtered character streams.
/// \details The FilterWriter class is an abstract class for writing filtered character streams.
/// It provides methods to write characters, strings, and character arrays to a stream.
/// The class is designed for subclassing by users who want to write filtered character streams.
class AbstractFilterWriter abstract : public AbstractWriter
{
public:
	explicit AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter);
	~AbstractFilterWriter() override;
	auto write(char c) -> void override;
	auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void override;
	auto write(const std::vector<char>& cBuf) -> void override;
	auto write(const std::string& str, size_t off, size_t len) -> void override;
	auto write(const std::string& str) -> void override;
	auto flush() -> void override;
	auto close() -> void override;

protected:
	std::unique_ptr<AbstractWriter> outputWriter_;
};
}
