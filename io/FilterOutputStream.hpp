// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef FILTEROUTPUTSTREAM_HPP
#define FILTEROUTPUTSTREAM_HPP
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
	explicit FilterOutputStream(std::unique_ptr<AbstractOutputStream> outputStream);
	~FilterOutputStream() override;
	auto write(int b) -> void override;
	auto write(const std::vector<char>& buffer) -> void override;
	auto write(const std::vector<char>& buffer, size_t offset, size_t len) -> void override;
	auto flush() -> void override;
	auto close() -> void override;

protected:
	std::unique_ptr<AbstractOutputStream> outputStream_;
};
} // namespace common::io
#endif //FILTEROUTPUTSTREAM_HPP
