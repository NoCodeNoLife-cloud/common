// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef BUFFEREDWRITER_HPP
#define BUFFEREDWRITER_HPP
#include <vector>
#include <glog/logging.h>
#include "interface/Appendable.hpp"
#include "interface/Closeable.hpp"
#include "interface/Flushable.hpp"

namespace commom::io
{
/**
 * \brief A class that writes text to a character-output stream, buffering characters so as to provide for the efficient writing of single characters, arrays, and strings.
 * \details The buffer size may be specified, or the default size may be used. The default is large enough for most purposes.
 * \note A newLine() method is provided, which uses the platform's own notion of line separator as defined by the system property line.separator.
 * \note The writer is not thread safe.
 */
class BufferedWriter final : public common::interface::Closeable,
                             public common::interface::Flushable,
                             public common::interface::Appendable<BufferedWriter>
{
public:
	explicit BufferedWriter(std::ofstream& os, size_t size = 1024);
	~BufferedWriter() override;
	void write(const std::string& str);
	Appendable& newLine();
	void flush() override;
	void close() override;
	BufferedWriter& append(char c) override;
	BufferedWriter& append(const std::string& str) override;
	BufferedWriter& append(const std::string& str, size_t start, size_t end) override;

private:
	std::ofstream& outStream_;
	std::vector<unsigned char> buffer_;
	size_t bufferSize_;
};
} // namespace commom::io
#endif //BUFFEREDWRITER_HPP
