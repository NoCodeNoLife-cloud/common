// Created by author ethereal on 2024/12/2.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "Error.hpp"

namespace common::exception
{
	Error::Error(std::string message): Exception(std::move(message)) {}
	Error::Error(std::string message, const std::string& cause): Exception(std::move(message), cause) {}
	/// \brief The destructor of the Error class.
	/// \details This function is declared as virtual to make the Error class polymorphic.
	/// It is called when an Error object is destroyed.
	Error::~Error()
	{
		exit(EXIT_FAILURE);
	}

	/// \brief Converts the object to a string.
	/// \returns A string that represents the object.
	auto Error::toString() const -> std::string
	{
		return std::format("{}", *this);
	}
}
