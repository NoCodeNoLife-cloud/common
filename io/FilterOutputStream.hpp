// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "AbstractOutputStream.hpp"

namespace common::io
{
/// \brief A concrete class that filters an output stream.
/// \details The `FilterOutputStream` class provides a base implementation for filtering
/// operations on an underlying output stream. Subclasses can extend this to provide
/// specific filtering behaviors.
class FilterOutputStream : public AbstractOutputStream
{
public:
	explicit FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream);
	~FilterOutputStream() override;
	auto write(std::byte b) -> void override;
	auto write(const std::vector<std::byte>& buffer) -> void override;
	auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;
	auto flush() -> void override;
	auto close() -> void override;

protected:
	std::shared_ptr<AbstractOutputStream> outputStream_;
};
}
