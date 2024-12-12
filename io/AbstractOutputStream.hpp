// Created by author ethereal on 2024/12/4.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef OUTPUTSTREAM_HPP
#define OUTPUTSTREAM_HPP
#include <format>
#include <vector>
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceFlushable.hpp"

namespace common::io
{
/// \brief Abstract class for objects that can be written to.
/// \details This class provides an interface for objects that can be written to.
/// It is a base class for classes that implement output streams.
/// It is an abstract class that cannot be instantiated.
class AbstractOutputStream abstract : public interface::IfaceCloseable,
                                      public interface::IfaceFlushable
{
public:
	~AbstractOutputStream() override = default;
	virtual auto write(int b) -> void = 0;
	virtual auto write(const std::vector<char>& buffer) -> void;
	virtual auto write(const std::vector<char>& buffer, size_t offset, size_t len) -> void;
};
} // namespace common::io
#endif // OUTPUTSTREAM_HPP
