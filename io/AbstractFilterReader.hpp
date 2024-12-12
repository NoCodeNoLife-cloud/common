// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "AbstractReader.hpp"

namespace common::io
{
/// \brief A class that provides a filter for an AbstractReader object.
/// \details This class provides a filter for an AbstractReader object.
/// It is used to filter the input of an AbstractReader object.
/// It is a concrete implementation of the AbstractReader interface.
class AbstractFilterReader final : public AbstractReader
{
public:
	explicit AbstractFilterReader(std::unique_ptr<AbstractReader> inputReader);
	~AbstractFilterReader() override;
	auto read() -> int override;
	auto read(std::vector<char>& cBuf, size_t off, size_t len) -> size_t override;
	auto skip(size_t n) -> size_t override;
	[[nodiscard]] auto ready() const -> bool override;
	[[nodiscard]] auto markSupported() const -> bool override;
	auto mark(size_t readAheadLimit) -> void override;
	auto reset() -> void override;
	auto close() -> void override;

protected:
	std::unique_ptr<AbstractReader> reader_; ///< The underlying character input stream.
};
}
