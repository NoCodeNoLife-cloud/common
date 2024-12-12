// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "FileOutputStream.hpp"
#include <stdexcept>

namespace common::io
{
FileOutputStream::FileOutputStream(const std::string& name, const bool append) {
	if (std::filesystem::exists(name) && std::filesystem::is_directory(name)) {
		throw std::ios_base::failure("FileNotFoundException: Path is a directory.");
	}
	fileStream_.open(name, std::ios::binary | (append ? std::ios::app : std::ios::trunc));
	if (!fileStream_.is_open()) {
		throw std::ios_base::failure("FileNotFoundException: Unable to open or create file.");
	}
	fileName_ = name;
}

FileOutputStream::FileOutputStream(const char* name, const bool append) : FileOutputStream(std::string(name), append) {}

FileOutputStream::FileOutputStream(const std::filesystem::path& file, const bool append) : FileOutputStream(file.string(), append) {}

FileOutputStream::~FileOutputStream() {
	FileOutputStream::close();
}

/// \brief Writes a single byte to the file.
/// \details The byte to be written is the lowest eight bits of the specified int value.
/// \param b the byte to be written.
void FileOutputStream::write(std::byte b) {
	if (!fileStream_) {
		throw std::ios_base::failure("IOException: Stream is not writable.");
	}
	const char byte = static_cast<char>(b);
	fileStream_.write(&byte, 1);
}

/// \brief Writes a sequence of bytes from a buffer to the file.
/// \details The method writes data starting from the beginning of the buffer to the end of the buffer into the file stream.
/// \param buffer The buffer containing the bytes to be written.
void FileOutputStream::write(const std::vector<std::byte>& buffer) {
	write(buffer, 0, buffer.size());
}

/// \brief Writes a sequence of bytes from a buffer to the file.
/// \details The method writes data from the buffer starting at the specified \p offset and of the specified \p len into the file stream.
/// \param buffer The buffer containing the bytes to be written.
/// \param offset The starting offset in the buffer.
/// \param len The number of bytes to be written.
void FileOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) {
	if (offset > buffer.size() || len > buffer.size() - offset) {
		throw std::invalid_argument("Invalid buffer, offset, or length.");
	}
	if (!fileStream_) {
		throw std::ios_base::failure("IOException: Stream is not writable.");
	}
	fileStream_.write(reinterpret_cast<const char*>(buffer.data() + offset), static_cast<std::streamsize>(len));
}

/// \brief Closes the file stream and releases any system resources associated with it.
/// \details Once a closed stream is closed, further write(), flush(), or close() invocations will cause an IOException to be thrown.
/// Closing a previously closed stream has no effect.
void FileOutputStream::close() {
	if (fileStream_.is_open()) {
		fileStream_.close();
	}
}

/// \brief Flushes the file stream and forces any buffered output bytes to be written out to the file.
/// \details The flush method of FileOutputStream calls the flush() method of its underlying output stream object.
void FileOutputStream::flush() {
	if (!fileStream_) {
		throw std::ios_base::failure("IOException: Stream is not writable.");
	}
	fileStream_.flush();
}
}
