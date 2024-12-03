// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef WRITER_HPP
#define WRITER_HPP
#include "interface/Appendable.hpp"
#include "interface/Closeable.hpp"
#include "interface/Flushable.hpp"

namespace common::io
{
/// \brief Abstract class for objects that can be written to.
/// \details This class provides a basic interface for objects that can be written to.
/// It is used by the Writer class to provide a basic interface for writing to an output stream.
class Writer : public interface::Closeable,
               public interface::Flushable,
               interface::Appendable<Writer>
{
public:
	Writer();
	~Writer() override;
	auto append(char c) -> Writer& override;
	auto append(const std::string& csq) -> Writer& override;
	auto append(const std::string& csq, size_t start, size_t end) -> Writer& override;
	virtual void write(const char cBuf[], size_t off, size_t len) = 0;
	virtual auto write(const char cBuf[]) -> void;
	virtual auto write(char c) -> void;
	virtual auto write(const std::string& str) -> void;
	virtual auto write(const std::string& str, size_t off, size_t len) -> void;
};
} // namespace common::io
#endif // WRITER_HPP
