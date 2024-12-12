// Created by author ethereal on 2024/12/3.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
namespace common::interface
{
/// \brief Abstract class for objects that can be flushed.
/// \details This abstract class provides the flush method which can be used to flush the content of the object.
class IfaceFlushable abstract
{
public:
	virtual ~IfaceFlushable() = default;
	virtual auto flush() -> void = 0;
};
}
