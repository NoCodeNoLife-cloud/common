// Created by author ethereal on 2024/12/4.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
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
class AbstractOutputStream abstract : public interface::IfaceCloseable, public interface::IfaceFlushable
{
public:
	~AbstractOutputStream() override = default;
	virtual auto write(std::byte b) -> void = 0;
	virtual auto write(const std::vector<std::byte>& buffer) -> void;
	virtual auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void;
};
}
