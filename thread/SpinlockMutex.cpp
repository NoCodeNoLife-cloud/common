// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "SpinlockMutex.hpp"
#include <thread>

namespace common::thread
{
SpinlockMutex::SpinlockMutex() = default;

/// \brief Acquires the spinlock, blocking if necessary until it becomes
/// available.
/// \details Continuously attempts to set the atomic flag. If the flag is
/// already set, the thread yields to allow other thread to proceed.
auto SpinlockMutex::lock() -> void {
	while (flag_.test_and_set(std::memory_order_acquire)) {
		std::this_thread::yield();
	}
}

/// \brief Releases the spinlock.
/// \details If there are thread waiting for the spinlock to become available,
/// one of them will be unblocked.
auto SpinlockMutex::unlock() -> void {
	flag_.clear(std::memory_order_release);
}
}
