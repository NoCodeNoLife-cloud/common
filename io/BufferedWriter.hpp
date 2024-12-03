// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef BUFFEREDWRITER_HPP
#define BUFFEREDWRITER_HPP
#include <vector>
#include <glog/logging.h>
#include "AbstractWriter.hpp"
#include "interface/IfaceAppendable.hpp"

namespace commom::io
{
/**
 * \brief A class that writes text to a character-output stream, buffering characters so as to provide for the efficient writing of single characters, arrays, and strings.
 * \details The buffer size may be specified, or the default size may be used. The default is large enough for most purposes.
 * \note A newLine() method is provided, which uses the platform's own notion of line separator as defined by the system property line.separator.
 * \note The writer is not thread safe.
 */
class BufferedWriter final : public common::io::AbstractWriter,
                             public common::interface::IfaceAppendable<BufferedWriter>
{
public:
	explicit BufferedWriter(std::ofstream& os, size_t size);
	~BufferedWriter() override;
	auto write(const std::string& str) -> void override;
	auto write(std::vector<char>& cBuf, size_t off, size_t len) -> void override;
	auto newLine() -> BufferedWriter&;
	auto flush() -> void override;
	auto close() -> void override;
	auto append(char c) -> BufferedWriter& override;
	auto append(const std::string& str) -> BufferedWriter& override;
	auto append(const std::string& str, size_t start, size_t end) -> BufferedWriter& override;

private:
	static constexpr size_t DEFAULT_BUFFER_SIZE = 1024;
	std::ofstream& outStream_;
	std::vector<char> buffer_;
	size_t bufferSize_;
};
} // namespace commom::io
#endif //BUFFEREDWRITER_HPP
