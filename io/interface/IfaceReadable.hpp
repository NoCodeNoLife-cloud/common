// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
namespace common::interface
{
/// \brief Abstract class for objects that can be read from.
/// \details This class provides an interface for objects that can be read from.
/// It declares a single method, `read()`, which must be implemented by any derived class.
class IfaceReadable abstract
{
public:
	virtual ~IfaceReadable() = default;
	virtual auto read() -> int = 0;
};
}
