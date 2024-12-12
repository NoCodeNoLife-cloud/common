// Created by author ethereal on 2024/11/28.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
namespace common::interface
{
/// \brief Interface for objects that can be run.
/// \details This interface is designed for objects that can be run in a separate thread.
template <typename ReturnType, typename... Args> class IfaceRunnable abstract
{
public:
	virtual ~IfaceRunnable() = default;
	virtual auto Run(Args... args) -> ReturnType = 0;
};
}
