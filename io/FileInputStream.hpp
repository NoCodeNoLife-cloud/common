// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include "AbstractInputStream.hpp"

namespace common::io
{
/// \brief A class that reads bytes from a file.
/// \details This class provides an interface for reading bytes from a file.
/// It is a concrete implementation of the interface::InputStreamable interface.
/// The constructor takes a string or a C-style string pointer as a parameter, which is the name of the file to read from.
/// The constructor takes a std::filesystem::path object as a parameter, which is the path to the file to read from.
/// The class provides methods to read single bytes, blocks of bytes, and to skip over bytes.
/// The class also provides methods to check the number of bytes available to read and to close the file.
class FileInputStream final : public AbstractInputStream
{
public:
	explicit FileInputStream(const std::string& name);
	explicit FileInputStream(const char* name);
	explicit FileInputStream(const std::filesystem::path& file);
	~FileInputStream() override;
	auto read() -> std::byte override;
	auto read(std::vector<std::byte>& buffer) -> size_t override;
	auto read(std::vector<std::byte>& buffer, size_t offset, size_t len) -> size_t override;
	auto skip(size_t n) -> size_t override;
	auto available() -> size_t override;
	auto close() -> void override;
	[[nodiscard]] auto markSupported() const -> bool override;

private:
	std::ifstream fileStream_;
	std::string fileName_;
};
}
