// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include "AbstractOutputStream.hpp"

namespace common::io
{
/// \brief A final class for writing data to a file output stream.
/// \details The FileOutputStream class provides methods to write data to a file.
/// It is a concrete implementation of the AbstractOutputStream interface.
/// The class supports writing single bytes, byte arrays, and byte arrays with specified offsets and lengths.
/// The class also provides methods to close the file output stream and to flush the output buffer.
/// \remark The class is designed to handle file output operations, with options for appending to existing files.
class FileOutputStream final : public AbstractOutputStream
{
public:
	explicit FileOutputStream(const std::string& name, bool append = false);
	explicit FileOutputStream(const char* name, bool append = false);
	explicit FileOutputStream(const std::filesystem::path& file, bool append = false);
	~FileOutputStream() override;
	void write(std::byte b) override;
	void write(const std::vector<std::byte>& buffer) override;
	void write(const std::vector<std::byte>& buffer, size_t offset, size_t len) override;
	void close() override;
	void flush() override;

private:
	std::ofstream fileStream_;
	std::string fileName_;
};
}
