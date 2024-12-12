// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include "AbstractOutputStream.hpp"

namespace common::io
{
/// \brief A ByteArrayOutputStream provides a stream for writing data to a byte array.
/// \details This class is inspired by Java's ByteArrayOutputStream and allows writing
/// to a dynamically growing byte buffer.
class ByteArrayOutputStream final : public AbstractOutputStream
{
public:
	ByteArrayOutputStream();
	explicit ByteArrayOutputStream(size_t size);
	auto write(std::byte b) -> void override;
	auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;
	auto writeTo(AbstractOutputStream& out) const -> void;
	auto reset() -> void;
	[[nodiscard]] auto toByteArray() const -> std::vector<std::byte>;
	[[nodiscard]] auto size() const -> size_t;
	[[nodiscard]] auto toString() const -> std::string;
	auto close() -> void override;
	auto flush() -> void override;

protected:
	std::vector<std::byte> buf_;
	size_t count_{0};
};
}
