// Created by author ethereal on 2024/12/3.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "File.hpp"
#include <fstream>
#include <windows.h>

namespace common::io
{
	File::File(const std::string& path): filePath(path) {}

	/// \brief Checks if the file can be executed.
	/// \return true if the file can be executed, false otherwise.
	auto File::canExecute() const -> bool
	{
		const DWORD attributes = GetFileAttributesW(filePath.c_str());
		return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
	}

	/// \brief Checks if the file can be read.
	/// \return true if the file can be read, false otherwise.
	auto File::canRead() const -> bool
	{
		const std::ifstream file(filePath);
		return file.good();
	}

	/// \brief Checks if the file can be written.
	/// \return true if the file can be written, false otherwise.
	auto File::canWrite() const -> bool
	{
		const std::ofstream file(filePath, std::ios::app);
		return file.good();
	}

	/// \brief Creates a new file with the specified path.
	/// \return true if the file was created, false otherwise.
	auto File::createNewFile() const -> bool
	{
		if (std::filesystem::exists(filePath))
		{
			return false;
		}
		const std::ofstream file(filePath);
		return file.good();
	}

	/// \brief Creates a temporary file with the specified prefix and suffix in the specified directory.
	/// \param prefix The prefix of the temporary file.
	/// \param suffix The suffix of the temporary file.
	/// \param directory The directory in which the temporary file should be created.
	/// \return A File object pointing to the newly created temporary file.
	auto File::createTempFile(const std::string& prefix, const std::string& suffix, const std::string& directory) -> File
	{
		char tempPath[MAX_PATH];
		if (directory.empty())
		{
			GetTempPath(MAX_PATH, tempPath);
		}
		else
		{
			strncpy_s(tempPath, directory.c_str(), MAX_PATH);
		}
		char tempFileName[MAX_PATH];
		GetTempFileName(tempPath, prefix.c_str(), 0, tempFileName);
		const std::string tempFilePath = std::string(tempFileName) + suffix;
		return File(tempFilePath);
	}

	/// \brief Deletes the file.
	/// \return true if the file was deleted, false otherwise.
	auto File::deleteFile() const -> bool
	{
		return std::filesystem::remove(filePath);
	}

	/// \brief Checks if the file exists.
	/// \return true if the file exists, false otherwise.
	auto File::exists() const -> bool
	{
		return std::filesystem::exists(filePath);
	}

	/// \brief Returns the absolute path of the file.
	/// \return The absolute path of the file.
	auto File::getAbsolutePath() const -> std::string
	{
		return absolute(filePath).string();
	}

	/// \brief Returns the absolute path of the file as a File object.
	/// \return A File object pointing to the absolute path of the file.
	auto File::getAbsoluteFile() const -> File
	{
		return File(absolute(filePath).string());
	}

	/// \brief Returns the name of the file.
	/// \return The name of the file.
	auto File::getName() const -> std::string
	{
		return filePath.filename().string();
	}

	/// \brief Returns the parent directory of the file.
	/// \return The parent directory of the file.
	auto File::getParent() const -> std::string
	{
		return filePath.parent_path().string();
	}

	/// \brief Checks if the file is a directory.
	/// \return true if the file is a directory, false otherwise.
	auto File::isDirectory() const -> bool
	{
		return is_directory(filePath);
	}

	/// \brief Checks if the file is a regular file.
	/// \return true if the file is a regular file, false otherwise.
	auto File::isFile() const -> bool
	{
		return is_regular_file(filePath);
	}

	/// \brief Checks if the file is hidden.
	/// \return true if the file is hidden, false otherwise.
	auto File::isHidden() const -> bool
	{
		const DWORD attributes = GetFileAttributesW(filePath.c_str());
		return attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_HIDDEN;
	}

	/// \brief Returns the size of the file in bytes.
	/// \return The size of the file in bytes if it exists and is a regular file, 0 otherwise.
	/// \details This function checks if the file exists and is a regular file, then returns its size in bytes.
	auto File::length() const -> long long
	{
		if (std::filesystem::exists(filePath) && is_regular_file(filePath))
		{
			return static_cast<long long>(file_size(filePath));
		}
		return 0;
	}

	/// \brief Returns the last modified time of the file in seconds since the Unix epoch.
	/// \return The last modified time of the file in seconds since the Unix epoch if it exists, 0 otherwise.
	/// \details This function checks if the file exists, then returns its last modified time in seconds since the Unix epoch.
	auto File::lastModified() const -> long long
	{
		const auto lastWriteTime = last_write_time(filePath);
		const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
		return std::chrono::system_clock::to_time_t(sctp);
	}

	/// \brief Lists the entries in the directory.
	/// \return A vector of strings containing the names of the entries in the directory.
	/// \details If the file is a directory, this function returns the names of all entries within it.
	/// It returns an empty vector if the file is not a directory.
	auto File::list() const -> std::vector<std::string>
	{
		std::vector<std::string> entries;
		if (isDirectory())
		{
			for (const auto& entry : std::filesystem::directory_iterator(filePath))
			{
				entries.push_back(entry.path().filename().string());
			}
		}
		return entries;
	}

	/// \brief Converts the File object to a string.
	/// \return The string representation of the File object.
	/// \details This function converts the File object to a string using the std::format function.
	auto File::toString() const -> std::string
	{
		return std::format("{}", *this);
	}
}
