// Created by author ethereal on 2024/12/2.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "OutOfRange.hpp"

namespace common::exception
{
	OutOfRange::OutOfRange(const size_t index, const size_t size): Exception("range_check: __n (which is " + std::to_string(index) + ") >= this->size() (which is " + std::to_string(size) + ")") {}
	OutOfRange::OutOfRange(const size_t index, const size_t size, std::string cause): Exception("range_check: __n (which is " + std::to_string(index) + ") >= this->size() (which is " + std::to_string(size) + ")", std::move(cause)) {}
	OutOfRange::OutOfRange(std::string message, std::string cause): Exception(std::move(message), std::move(cause)) {}
	OutOfRange::~OutOfRange() = default;
	/// \brief Converts the object to a string.
	/// \returns A string that represents the object.
	auto OutOfRange::toString() const -> std::string
	{
		return std::format("{}", *this);
	}
}
