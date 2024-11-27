// Created by author ethereal on 2024/12/2.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Exception.hpp"

namespace common::exception
{
	Exception::Exception(std::string message): message_(std::move(message)) {}
	Exception::Exception(std::string message, std::string cause): message_(std::move(message)), cause_(std::make_unique<std::exception>(cause.data())) {}
	Exception::~Exception() = default;
	/// \brief Converts the object to a string.
	/// \returns A string that represents the object.
	auto Exception::toString() const -> std::string
	{
		return std::format("{}", *this);
	}
}
