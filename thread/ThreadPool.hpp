// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

namespace common::thread
{
/// \brief A thread pool for executing tasks concurrently
/// A thread pool is a software design pattern for achieving concurrency of
/// tasks. It uses a group of worker threads that are maintained by the pool in
/// such a way that the tasks can be executed concurrently without the need for
/// explicit thread management by the application.
/// The thread pool pattern allows for the efficient execution of tasks that
/// involve waiting for events to occur, by reusing threads rather than
/// creating and destroying them. The pool of threads is typically maintained
/// by a manager that assigns tasks to the threads as they become available.
class ThreadPool
{
public:
	ThreadPool(size_t core_threads, size_t max_threads, size_t queue_size, std::chrono::milliseconds idle_time);
	~ThreadPool();
	template <class F, class... Args> auto Submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;
	auto Shutdown() -> void;
	auto ShutdownNow() -> void;

private:
	auto Worker() -> void;
	auto AddWorker() -> bool;
	std::vector<std::thread> workers_;
	std::queue<std::function<void()>> task_queue_;
	std::condition_variable condition_;
	std::mutex queueMutex_;
	std::atomic<bool> stop_;
	std::atomic<size_t> coreThreadCount_;
	std::atomic<size_t> activeThreadCount_;
	size_t maxThreadCount_;
	size_t maxQueueSize_;
	std::chrono::milliseconds threadIdleTime_;
};
}
