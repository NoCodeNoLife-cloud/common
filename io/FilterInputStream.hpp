// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "AbstractInputStream.hpp"

namespace common::io
{
/// \brief A class that reads bytes from a stream with filtering.
/// \details It reads bytes from a stream with filtering. The read and skip methods are supported.
/// The available and markSupported methods are also supported.
class FilterInputStream : public AbstractInputStream
{
public:
	explicit FilterInputStream(std::unique_ptr<AbstractInputStream> inputStream);
	~FilterInputStream() override;
	[[nodiscard]] auto available() -> size_t override;
	auto mark(int readLimit) -> void override;
	[[nodiscard]] auto markSupported() const -> bool override;
	auto read() -> std::byte override;
	auto read(std::vector<std::byte>& buffer) -> size_t override;
	auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
	auto reset() -> void override;
	auto skip(size_t n) -> size_t override;
	auto close() -> void override;

protected:
	std::unique_ptr<AbstractInputStream> inputStream_;
};
}
