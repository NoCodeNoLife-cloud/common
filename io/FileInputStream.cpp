// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "FileInputStream.hpp"

namespace common::io
{
FileInputStream::FileInputStream(const std::string& name) {
	if (!std::filesystem::exists(name)) {
		throw std::ios_base::failure("FileNotFoundException: File does not exist.");
	}
	if (std::filesystem::is_directory(name)) {
		throw std::ios_base::failure("FileNotFoundException: Path is a directory.");
	}
	fileStream_.open(name, std::ios::binary);
	if (!fileStream_.is_open()) {
		throw std::ios_base::failure("FileNotFoundException: Unable to open file.");
	}
	fileName_ = name;
}

FileInputStream::FileInputStream(const char* name) : FileInputStream(std::string(name)) {}

FileInputStream::FileInputStream(const std::filesystem::path& file) : FileInputStream(file.string()) {}

FileInputStream::~FileInputStream() {
	FileInputStream::close();
}

/// \brief Reads the next byte of data from this input stream.
/// \details The value byte is returned as an int in the range 0 to 255.
/// If no byte is available because the end of the stream has been reached, the value -1 is returned.
/// This method blocks until input data is available, the end of the stream is detected, or an exception is thrown.
/// \return the next byte of data, or -1 if the end of the stream is reached.
auto FileInputStream::read() -> std::byte {
	std::byte byte;
	if (fileStream_.read(reinterpret_cast<char*>(&byte), 1)) {
		return byte;
	}
	return static_cast<std::byte>(-1);
}

/// \brief Reads bytes from this input stream into the specified byte array.
/// \details This method reads up to b.length bytes from this input stream into the byte array b.
/// The bytes are read into the byte array starting at offset 0.
/// If no byte is available because the end of the stream has been reached, the number of bytes read is returned.
/// Otherwise, the number of bytes actually read is returned.
/// This method blocks until input data is available, the end of the stream is detected, or an exception is thrown.
/// \param buffer the buffer into which the data is read.
/// \return the total number of bytes read into the buffer, or -1 if there is no more data because the end of the stream has been reached.
auto FileInputStream::read(std::vector<std::byte>& buffer) -> size_t {
	return read(buffer, 0, buffer.size());
}

/// \brief Reads up to len bytes of data from this input stream into an array of bytes.
/// \details This method reads up to len bytes from this input stream into the byte array b.
/// The bytes are read into the byte array starting at offset.
/// If no byte is available because the end of the stream has been reached, the number of bytes read is returned.
/// Otherwise, the number of bytes actually read is returned.
/// This method blocks until input data is available, the end of the stream is detected, or an exception is thrown.
/// \param buffer the buffer into which the data is read.
/// \param offset the starting offset in the buffer.
/// \param len the maximum number of bytes to read.
/// \return the total number of bytes read into the buffer, or -1 if there is no more data because the end of the stream has been reached.
auto FileInputStream::read(std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> size_t {
	if (offset + len > buffer.size()) {
		throw std::invalid_argument("Invalid buffer, offset, or length.");
	}
	fileStream_.read(reinterpret_cast<char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
	return fileStream_.gcount();
}

/// \brief Skips over and discards n bytes of data from this input stream.
/// \details The skip method may, for a variety of reasons, end before skipping n bytes.
/// \param n The number of bytes to skip.
/// \return The number of bytes actually skipped.
auto FileInputStream::skip(const size_t n) -> size_t {
	fileStream_.seekg(static_cast<std::streamoff>(n), std::ios::cur);
	return fileStream_.good() ? static_cast<std::streamoff>(n) : 0;
}

/// \brief Returns the number of bytes that can be read (or skipped over) from this input stream without blocking by the next caller of a method for this input stream.
/// \details The available method for class FileInputStream returns the number of bytes that can be read from this file input stream without blocking.
/// \return The number of available bytes.
auto FileInputStream::available() -> size_t {
	const auto current = fileStream_.tellg();
	fileStream_.seekg(0, std::ios::end);
	const auto end = fileStream_.tellg();
	fileStream_.seekg(current, std::ios::beg);
	return end - current;
}

/// \brief Closes this input stream and releases any system resources associated with the stream.
/// \details The close method of FileInputStream calls the close method of its underlying input stream.
auto FileInputStream::close() -> void {
	if (fileStream_.is_open()) {
		fileStream_.close();
	}
}

/// \brief Tests if this input stream supports the mark and reset methods.
/// \details This method returns false indicating that the FileInputStream does not support
/// the mark and reset methods, meaning the current position in the stream cannot be saved
/// and reverted to later.
/// \return false since this FileInputStream does not support the mark and reset methods.
[[nodiscard]] auto FileInputStream::markSupported() const -> bool {
	return false;
}
}
