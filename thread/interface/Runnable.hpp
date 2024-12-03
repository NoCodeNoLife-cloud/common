// Created by author ethereal on 2024/11/28.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

namespace common::interface
{
/// \brief Interface for objects that can be run.
/// \details This interface is designed for objects that can be run in a separate thread.
template <typename ReturnType, typename... Args> class Runnable abstract
{
public:
	virtual ~Runnable() = default;
	virtual auto Run(Args... args) -> ReturnType = 0;
};
} // namespace common::interface
#endif // RUNNABLE_HPP
