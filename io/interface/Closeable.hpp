// Created by author ethereal on 2024/12/3.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef CLOSEABLE_HPP
#define CLOSEABLE_HPP

namespace common::interface
{
	/// \brief Abstract interface for objects that can be closed.
	/// \details This class declares a method to close the object. Any class that implements
	/// this interface must provide a concrete implementation of the close method.
	/// The close method is a way to signal to the object that it should release its resources
	/// and make any necessary cleanup. The object should be in a valid state before
	/// being closed.
	class Closeable abstract
	{
	public:
		virtual ~Closeable() = default;

		virtual auto close() -> void = 0;
	};
}
#endif //CLOSEABLE_HPP
