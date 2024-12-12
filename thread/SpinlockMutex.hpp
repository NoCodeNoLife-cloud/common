// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <atomic>

namespace common::thread
{
/// \brief A simple spinlock mutex.
/// \details This class is a simple, lock-free spinlock mutex.
/// It is designed to be used in situations where a critical section of code is very short, such as when accessing a
/// shared resource. Because it is based on a spinlock, it will burn CPU cycles if it can't acquire the lock
/// immediately.
class SpinlockMutex
{
public:
	SpinlockMutex();
	auto lock() -> void;
	auto unlock() -> void;

private:
	std::atomic_flag flag_;
};
}
