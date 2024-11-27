// Created by author ethereal on 2024/12/2.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "InvalidArgument.hpp"

namespace common::exception
{
	InvalidArgument::InvalidArgument(const std::string& invalidArgumentName): Exception(invalidArgumentName) {}
	InvalidArgument::InvalidArgument(std::string message, std::string cause): Exception(std::move(message), std::move(cause)) {}
	InvalidArgument::~InvalidArgument() = default;
	/// \brief Converts the object to a string.
	/// \returns A string that represents the object.
	auto InvalidArgument::toString() const -> std::string
	{
		return std::format("{}", *this);
	}
}
