// Created by author ethereal on 2024/12/15.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "File.hpp"
#include "FilterOutputStream.hpp"
#include "interface/IfaceAppendable.hpp"

namespace common::io
{
/// \brief A class that provides methods to print data to an output stream.
/// \details The PrintStream class provides methods to print data to an output stream.
/// It is a concrete implementation of the FilterOutputStream and IfaceAppendable interfaces.
/// It supports printing of various types of data, including boolean, character, integer, long, float, double,
/// string, and vector of characters. It also supports flushing and closing the stream.
class PrintStream final : public FilterOutputStream, public interface::IfaceAppendable<PrintStream>
{
public:
	explicit PrintStream(std::shared_ptr<AbstractOutputStream> outStream, bool autoFlush = true, const std::locale& loc = std::locale());
	~PrintStream() override;
	auto append(char c) -> PrintStream& override;
	auto append(const std::string& str) -> PrintStream& override;
	auto append(const std::string& str, size_t start, size_t end) -> PrintStream& override;
	auto flush() -> void override;
	auto close() -> void override;
	void print(bool b) const;
	void print(char c) const;
	void print(int i) const;
	void print(long l) const;
	void print(float f) const;
	void print(double d) const;
	void print(const char* s) const;
	void print(const std::string& s) const;
	void print(const std::vector<char>& v) const;
	void println(bool b) const;
	void println(char c) const;
	void println(int i) const;
	void println(long l) const;
	void println(float f) const;
	void println(double d) const;
	void println(const char* s) const;
	void println(const std::string& s) const;
	void println(const std::vector<char>& v) const;

protected:
	void flushIfNeeded() const;
	bool autoFlush_{false};
	bool errorState_{false};
	std::locale locale_;
};
}
