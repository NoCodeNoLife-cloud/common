// Created by author ethereal on 2024/12/6.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <vector>
#include "interface/IfaceAppendable.hpp"
#include "interface/IfaceCloseable.hpp"
#include "interface/IfaceFlushable.hpp"

namespace common::io
{
/// \brief Abstract class for objects that can be written to.
/// \details This class provides a basic interface for objects that can be written to.
/// It is used by the Writer class to provide a basic interface for writing to an output stream.
class AbstractWriter : public interface::IfaceCloseable, public interface::IfaceFlushable, interface::IfaceAppendable<AbstractWriter>
{
public:
	AbstractWriter();
	~AbstractWriter() override;
	auto append(char c) -> AbstractWriter& override;
	auto append(const std::string& csq) -> AbstractWriter& override;
	auto append(const std::string& csq, size_t start, size_t end) -> AbstractWriter& override;
	virtual auto write(char c) -> void;
	virtual auto write(const std::vector<char>& cBuf) -> void;
	virtual auto write(const std::vector<char>& cBuf, size_t off, size_t len) -> void = 0;
	virtual auto write(const std::string& str) -> void;
	virtual auto write(const std::string& str, size_t off, size_t len) -> void;
	[[nodiscard]] virtual auto toString() const -> std::string = 0;
};
}
