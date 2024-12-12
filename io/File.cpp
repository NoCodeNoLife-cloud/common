// Created by author ethereal on 2024/12/3.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "File.hpp"
#include <fstream>
#include <windows.h>

namespace common::io
{
File::File(const std::string& path) : filePath_(path) {}

File::File(std::filesystem::path path) : filePath_(std::move(path)) {}

File::File(const char* path) : filePath_(path) {}

File::~File() = default;

/// \brief Compares this File object with the specified File object.
/// \param other the File object to compare with.
/// \return a negative integer, zero, or a positive integer as this File object is less than, equal to, or greater than
/// the specified File object.
/// \details This function compares the two File objects by comparing the absolute paths of the two files.
auto File::compareTo(const File& other) const -> int {
	return filePath_.string().compare(other.filePath_.string());
}

/// \brief Compares this File object with the specified File object for equality.
/// \param other the File object to compare with.
/// \return true if this File object is equal to the specified File object, false otherwise.
/// \details This function compares the two File objects by checking if they represent the same file.
auto File::equals(const File& other) const -> bool {
	return equivalent(filePath_, other.filePath_);
}

/// \brief Checks if the file can be executed.
/// \return true if the file can be executed, false otherwise.
auto File::canExecute() const -> bool {
	const DWORD attributes = GetFileAttributesW(filePath_.c_str());
	return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

/// \brief Checks if the file can be read.
/// \return true if the file can be read, false otherwise.
auto File::canRead() const -> bool {
	const std::ifstream file(filePath_);
	return file.good();
}

/// \brief Checks if the file can be written.
/// \return true if the file can be written, false otherwise.
auto File::canWrite() const -> bool {
	const std::ofstream file(filePath_, std::ios::app);
	return file.good();
}

/// \brief Creates a new file with the specified path.
/// \return true if the file was created, false otherwise.
auto File::createNewFile() const -> bool {
	if (std::filesystem::exists(filePath_)) {
		return false;
	}
	const std::ofstream file(filePath_);
	return file.good();
}

/// \brief Creates a temporary file with the specified prefix and suffix in the specified directory.
/// \param prefix The prefix of the temporary file.
/// \param suffix The suffix of the temporary file.
/// \param directory The directory in which the temporary file should be created.
/// \return A File object pointing to the newly created temporary file.
auto File::createTempFile(const std::string& prefix, const std::string& suffix, const std::string& directory) -> File {
	char tempPath[MAX_PATH];
	if (directory.empty()) {
		GetTempPath(MAX_PATH, tempPath);
	}
	else {
		strncpy_s(tempPath, directory.c_str(), MAX_PATH);
	}
	char tempFileName[MAX_PATH];
	GetTempFileName(tempPath, prefix.c_str(), 0, tempFileName);
	const std::string tempFilePath = std::string(tempFileName) + suffix;
	return File(tempFilePath);
}

/// \brief Deletes the file.
/// \return true if the file was deleted, false otherwise.
auto File::deleteFile() const -> bool {
	return std::filesystem::remove(filePath_);
}

/// \brief Checks if the file exists.
/// \return true if the file exists, false otherwise.
auto File::exists() const -> bool {
	return std::filesystem::exists(filePath_);
}

/// \brief Returns the absolute path of the file.
/// \return The absolute path of the file.
auto File::getAbsolutePath() const -> std::string {
	return absolute(filePath_).string();
}

/// \brief Returns the absolute path of the file as a File object.
/// \return A File object pointing to the absolute path of the file.
auto File::getAbsoluteFile() const -> File {
	return File(absolute(filePath_).string());
}

/// \brief Returns the name of the file.
/// \return The name of the file.
auto File::getName() const -> std::string {
	return filePath_.filename().string();
}

/// \brief Returns the parent directory of the file.
/// \return The parent directory of the file.
auto File::getParent() const -> std::string {
	return filePath_.parent_path().string();
}

/// \brief Returns the canonical path of the file as a File object.
/// \return A File object pointing to the canonical path of the file.
auto File::getCanonicalFile() const -> File {
	return File(canonical(filePath_));
}

/// \brief Returns the parent directory of the file as a File object.
/// \return A File object pointing to the parent directory of the file.
auto File::getParentFile() const -> File {
	return filePath_.has_parent_path() ? File(filePath_.parent_path()) : File(std::string(""));
}

/// \brief Returns the path of the file as a string.
/// \return The path of the file as a string.
/// \details This function returns the path represented by the File object in string format.
auto File::getPath() const -> std::string {
	return filePath_.string();
}

/// \brief Returns the total size of the file system in bytes.
/// \return The total size of the file system in bytes.
/// \details This function returns the total size of the file system in bytes, which is the sum of the number of bytes
/// available to the caller after successful execution of this method; i.e., where the file denoted by this abstract
/// pathname exists. The total size of the partition <i>NR</i> bytes is <code>(long) (new
/// File("/volume/partition/NR").getTotalSpace())</code>.
auto File::getTotalSpace() const -> long {
	const auto spaceInfo = space(filePath_);
	return static_cast<long>(spaceInfo.capacity);
}

/// \brief Returns the number of unallocated bytes in the partition.
/// \return The number of unallocated bytes in the partition.
/// \details This function returns the number of unallocated bytes in the partition <i>NR</i> denoted by this abstract
/// path name. The number of unallocated bytes is defined as <code>getTotalSpace() - getUsableSpace()</code>. On systems
/// where this information is not available, this method will throw an IOException rather than returning an incorrect
/// result.
auto File::getUsableSpace() const -> long {
	const auto spaceInfo = space(filePath_);
	return static_cast<long>(spaceInfo.free);
}

/// \brief Returns a hash code value for this File object.
/// \return A hash code value for this File object.
/// \details This function returns a hash code value for this File object. The hash code is generated using the
/// std::hash function applied to the absolute path of the file.
auto File::hashCode() const -> size_t {
	return std::hash<std::string>()(filePath_.string());
}

/// \brief Checks if the file path is absolute.
/// \return true if the file path is absolute, false otherwise.
/// \details This function checks if the file path is absolute by calling the std::filesystem::path::is_absolute()
/// function.
auto File::isAbsolute() const -> bool {
	return filePath_.is_absolute();
}

/// \brief Creates the directory named by this abstract pathname.
/// \return true if and only if the directory was created; false otherwise.
/// \details This function creates the directory named by this abstract pathname.
/// If the specified directory does not already exist, and the parent directory exists, then this method will create a
/// new directory. Otherwise, this method will return false.
auto File::mkdir() const -> bool {
	return create_directory(filePath_);
}

/// \brief Renames the file to the specified destination.
/// \param dest The File object representing the destination path.
/// \return true if the file was successfully renamed, false otherwise.
/// \details This function attempts to rename the file to the specified destination path.
/// If the operation is successful, it returns true. If a filesystem error occurs,
/// such as if the destination path is invalid or the file cannot be accessed,
/// the function catches the exception and returns false.
auto File::renameTo(const File& dest) const -> bool {
	try {
		std::filesystem::rename(filePath_, dest.filePath_);
		return true;
	}
	catch (const std::filesystem::filesystem_error&) {
		return false;
	}
}

/// \brief Checks if the file is a directory.
/// \return true if the file is a directory, false otherwise.
auto File::isDirectory() const -> bool {
	return is_directory(filePath_);
}

/// \brief Checks if the file is a regular file.
/// \return true if the file is a regular file, false otherwise.
auto File::isFile() const -> bool {
	return is_regular_file(filePath_);
}

/// \brief Checks if the file is hidden.
/// \return true if the file is hidden, false otherwise.
auto File::isHidden() const -> bool {
	const DWORD attributes = GetFileAttributesW(filePath_.c_str());
	return attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_HIDDEN;
}

/// \brief Returns the size of the file in bytes.
/// \return The size of the file in bytes if it exists and is a regular file, 0 otherwise.
/// \details This function checks if the file exists and is a regular file, then returns its size in bytes.
auto File::length() const -> long long {
	if (std::filesystem::exists(filePath_) && is_regular_file(filePath_)) {
		return static_cast<long long>(file_size(filePath_));
	}
	return 0;
}

/// \brief Returns the last modified time of the file in seconds since the Unix epoch.
/// \return The last modified time of the file in seconds since the Unix epoch if it exists, 0 otherwise.
/// \details This function checks if the file exists, then returns its last modified time in seconds since the Unix
/// epoch.
auto File::lastModified() const -> long long {
	const auto lastWriteTime = last_write_time(filePath_);
	const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
	return std::chrono::system_clock::to_time_t(sctp);
}

/// \brief Lists the entries in the directory.
/// \return A vector of strings containing the names of the entries in the directory.
/// \details If the file is a directory, this function returns the names of all entries within it.
/// It returns an empty vector if the file is not a directory.
auto File::list() const -> std::vector<std::string> {
	std::vector<std::string> entries;
	if (isDirectory()) {
		for (const auto& entry : std::filesystem::directory_iterator(filePath_)) {
			entries.push_back(entry.path().filename().string());
		}
	}
	return entries;
}

/// \brief Converts the File object to a string.
/// \return The string representation of the File object.
/// \details This function converts the File object to a string using the std::format function.
auto File::toString() const -> std::string {
	return std::format("{}", *this);
}

/// \brief Converts the File object to a URI.
/// \return The URI representation of the File object.
/// \details This function converts the File object to a URI using the std::format function.
auto File::toURI() const -> std::string {
	return "file://" + filePath_.string();
}
}
