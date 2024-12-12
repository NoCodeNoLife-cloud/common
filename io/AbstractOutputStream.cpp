// Created by author ethereal on 2024/12/4.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "AbstractOutputStream.hpp"

namespace common::io
{
/// \brief Writes the entire buffer to the output stream.
/// \param buffer The buffer to be written.
/// \details This function writes the entire buffer to the output stream.
auto AbstractOutputStream::write(const std::vector<std::byte>& buffer) -> void {
	write(buffer, 0, static_cast<int>(buffer.size()));
}

/// \brief Writes a portion of the buffer to the output stream.
/// \param buffer The buffer to be written.
/// \param offset The starting offset in the buffer.
/// \param len The number of bytes to be written.
/// \details This function writes \p len bytes from the buffer starting at \p offset to the output stream.
auto AbstractOutputStream::write(const std::vector<std::byte>& buffer, const size_t offset, const size_t len) -> void {
	if (offset + len > buffer.size()) {
		throw std::out_of_range("Buffer offset/length out of range");
	}
	for (int i = 0; i < len; ++i) {
		write(buffer[offset + i]);
	}
}
}
