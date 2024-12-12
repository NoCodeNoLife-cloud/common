// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "ThreadPool.hpp"

namespace common::thread
{
///\brief A thread pool for executing tasks concurrently
/// A thread pool is a software design pattern for achieving concurrency of
/// tasks. It uses a group of worker threads that are maintained by the pool in
/// such a way that the tasks can be executed concurrently without the need for
/// explicit thread management by the application.
/// The thread pool pattern allows for the efficient execution of tasks that
/// involve waiting for events to occur, by reusing threads rather than
/// creating and destroying them. The pool of threads is typically maintained
/// by a manager that assigns tasks to the threads as they become available.
ThreadPool::ThreadPool(const size_t core_threads, const size_t max_threads, const size_t queue_size, const std::chrono::milliseconds idle_time) : stop_(false), coreThreadCount_(core_threads), maxThreadCount_(max_threads), maxQueueSize_(queue_size), threadIdleTime_(idle_time) {
	for (size_t i = 0; i < coreThreadCount_; ++i) {
		AddWorker();
	}
}

///\brief Destroys the thread pool.
///\details Shuts down all the threads and clears the task queue.
ThreadPool::~ThreadPool() {
	Shutdown();
}

/// \brief Submit a task to the thread pool for execution.
/// \tparam F The type of the function to be executed.
/// \tparam Args The types of the arguments to be passed to the function.
/// \param f The function to be executed.
/// \param args The arguments to be passed to the function.
/// \return A future object that will hold the result of the function execution.
/// \throws std::runtime_error if the task queue is full.
/// \details This function creates a packaged task from the function and arguments
/// and adds it to the task queue. If the queue is full, it throws an exception.
/// A worker thread will eventually execute the task, and the result can be
/// retrieved from the returned future object.
template <class F, class... Args> auto ThreadPool::Submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
	using return_type = std::invoke_result_t<F, Args...>;
	auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	std::future<return_type> res = task->get_future();
	{
		std::unique_lock lock(queueMutex_);
		if (task_queue_.size() >= maxQueueSize_) {
			throw std::runtime_error("Task queue is full");
		}
		task_queue_.emplace([task] {
			(*task)();
		});
	}
	condition_.notify_one();
	return res;
}

/// \brief Shuts down all the threads in the pool.
/// \details This function notifies all the worker threads to finish their
/// tasks and exit. It then waits for all the threads to finish and clears
/// the task queue.
auto ThreadPool::Shutdown() -> void {
	{
		std::unique_lock lock(queueMutex_);
		stop_ = true;
	}
	condition_.notify_all();
	for (std::thread& worker : workers_) {
		if (worker.joinable()) worker.join();
	}
}

/// \brief Immediately shuts down the thread pool.
/// \details This function sets the stop flag to true and clears the task queue.
/// It notifies all worker threads to finish their current tasks and exit as soon as possible.
/// This is a more abrupt shutdown compared to the regular Shutdown, as it discards all pending tasks.
auto ThreadPool::ShutdownNow() -> void {
	{
		std::unique_lock lock(queueMutex_);
		stop_ = true;
		while (!task_queue_.empty()) {
			task_queue_.pop();
		}
	}
	condition_.notify_all();
	for (std::thread& worker : workers_) {
		if (worker.joinable()) worker.join();
	}
}

/// \brief Executes tasks from the task queue.
/// \details This function runs in a loop, waiting for tasks to be available in the task queue.
/// It picks up tasks and executes them. If the thread pool is in the process of shutting down
/// and there are no tasks left in the queue, the function exits.
auto ThreadPool::Worker() -> void {
	while (true) {
		std::function<void()> task;
		{
			std::unique_lock lock(queueMutex_);
			condition_.wait_for(lock, threadIdleTime_, [this] {
				return stop_ || !task_queue_.empty();
			});
			if (stop_ && task_queue_.empty()) return;
			if (task_queue_.empty() && activeThreadCount_ > coreThreadCount_) {
				--activeThreadCount_;
				return;
			}
			if (!task_queue_.empty()) {
				task = std::move(task_queue_.front());
				task_queue_.pop();
			}
		}
		if (task) {
			task();
		}
	}
}

/// \brief Adds a new worker thread to the pool.
/// \details This function creates a new worker thread and adds it to the pool.
/// The new thread will execute tasks from the task queue.
/// \return true if the thread was added successfully, false otherwise.
/// \details The function returns false if the current number of active threads
/// is already at the maximum allowed number.
auto ThreadPool::AddWorker() -> bool {
	if (activeThreadCount_ >= maxThreadCount_) {
		return false;
	}
	++activeThreadCount_;
	workers_.emplace_back([this] {
		Worker();
	});
	return true;
}
}
