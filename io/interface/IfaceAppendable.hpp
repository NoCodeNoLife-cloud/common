// Created by author ethereal on 2024/12/7.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <string>

namespace common::interface
{
/// \brief Abstract class for objects that can be appended to.
/// \details This template class provides an interface for objects that support appending operations.
/// It declares three overloaded append methods, which allow for appending a character or a string to the object.
/// Derived classes must implement these methods to define specific appending behavior.
/// \tparam T The type of the derived class, enabling method chaining through the use of return type.
template <typename T> class IfaceAppendable abstract
{
public:
	virtual ~IfaceAppendable() = default;
	virtual auto append(char c) -> T& = 0;
	virtual auto append(const std::string& str) -> T& = 0;
	virtual auto append(const std::string& str, size_t start, size_t end) -> T& = 0;
};
}
