// Created by author ethereal on 2024/12/11.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "AbstractFilterWriter.hpp"
#include <stdexcept>

namespace common::io
{
AbstractFilterWriter::AbstractFilterWriter(std::unique_ptr<AbstractWriter> outputWriter) : outputWriter_(std::move(outputWriter)) {
	if (!outputWriter_) {
		throw std::invalid_argument("Output writer cannot be null");
	}
}

AbstractFilterWriter::~AbstractFilterWriter() = default;

/// \brief Writes a single character to the output stream.
/// \param c The character to be written.
/// \throws std::runtime_error if the output stream is not available.
auto AbstractFilterWriter::write(const char c) -> void {
	if (!outputWriter_) {
		throw std::runtime_error("Output stream is not available");
	}
	outputWriter_->write(c);
}

/// \brief Writes a portion of a character buffer to the output stream.
/// \param cBuf The buffer containing characters to write.
/// \param off The offset in the buffer from which to start writing.
/// \param len The number of characters to write.
/// \throws std::runtime_error if the output stream is not available.
/// \throws std::out_of_range if the buffer overflows.
auto AbstractFilterWriter::write(const std::vector<char>& cBuf, const size_t off, const size_t len) -> void {
	if (!outputWriter_) {
		throw std::runtime_error("Output stream is not available");
	}
	if (off + len > cBuf.size()) {
		throw std::out_of_range("Buffer overflow");
	}
	outputWriter_->write(cBuf, off, len);
}

/// \brief Writes a character buffer to the output stream.
/// \param cBuf The buffer containing characters to write.
/// \throws std::runtime_error if the output stream is not available.
auto AbstractFilterWriter::write(const std::vector<char>& cBuf) -> void {
	if (!outputWriter_) {
		throw std::runtime_error("Output stream is not available");
	}
	outputWriter_->write(cBuf);
}

/// \brief Writes a portion of a string to the output stream.
/// \param str The string containing characters to write.
/// \param off The offset in the string from which to start writing.
/// \param len The number of characters to write.
/// \throws std::runtime_error if the output stream is not available.
/// \throws std::out_of_range if the string overflows.
auto AbstractFilterWriter::write(const std::string& str, const size_t off, const size_t len) -> void {
	if (!outputWriter_) {
		throw std::runtime_error("Output stream is not available");
	}
	if (off + len > str.size()) {
		throw std::out_of_range("String overflow");
	}
	outputWriter_->write(str, off, len);
}

/// \brief Writes a string to the output stream.
/// \param str The string containing characters to write.
/// \throws std::runtime_error if the output stream is not available.
auto AbstractFilterWriter::write(const std::string& str) -> void {
	if (!outputWriter_) {
		throw std::runtime_error("Output stream is not available");
	}
	outputWriter_->write(str);
}

/// \brief Flushes the output stream.
/// \throws std::runtime_error if the output stream is not available.
auto AbstractFilterWriter::flush() -> void {
	if (!outputWriter_) {
		throw std::runtime_error("Output stream is not available");
	}
	outputWriter_->flush();
}

/// \brief Closes the output stream.
/// \throws std::runtime_error if the output stream is not available.
auto AbstractFilterWriter::close() -> void {
	if (!outputWriter_) {
		throw std::runtime_error("Output stream is not available");
	}
	flush();
	outputWriter_->close();
}
}
