// Created by author ethereal on 2024/11/21.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef COMPARABLE_HPP
#define COMPARABLE_HPP

namespace common::interface
{
/// \class IfaceComparable
/// \brief Abstract interface for comparable objects.
template <typename T> class IfaceComparable abstract
{
public:
	virtual ~IfaceComparable() = default;
	[[nodiscard]] virtual auto compareTo(const T& other) const -> int = 0;
	[[nodiscard]] virtual auto equals(const T& other) const -> bool = 0;
};
} // namespace common::interface
#endif // COMPARABLE_HPP
