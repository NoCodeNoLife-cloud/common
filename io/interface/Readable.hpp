// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef READABLE_HPP
#define READABLE_HPP

namespace common::interface
{
/// \brief Abstract class for objects that can be read from.
/// \details This class provides an interface for objects that can be read from.
/// It declares a single method, `read()`, which must be implemented by any derived class.
class Readable abstract
{
public:
	virtual ~Readable() = default;
	virtual int read() = 0;
};
} // namespace common::interface
#endif // READABLE_HPP
