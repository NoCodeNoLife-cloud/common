// Created by author ethereal on 2024/12/8.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef BYTEARRAYOUTPUTSTREAM_HPP
#define BYTEARRAYOUTPUTSTREAM_HPP
#include "AbstractOutputStream.hpp"

namespace common::io
{
/// \brief A ByteArrayOutputStream provides a stream for writing data to a byte array.
/// \details This class is inspired by Java's ByteArrayOutputStream and allows writing
/// to a dynamically growing byte buffer.
class ByteArrayOutputStream final : public AbstractOutputStream
{
protected:
	std::vector<char> buf;
	size_t count = 0;

public:
	ByteArrayOutputStream();
	explicit ByteArrayOutputStream(size_t size);
	auto write(int b) -> void override;
	auto write(const std::vector<char>& buffer, size_t offset, size_t len) -> void override;
	auto writeTo(AbstractOutputStream& out) const -> void;
	auto reset() -> void;
	[[nodiscard]] auto toByteArray() const -> std::vector<char>;
	[[nodiscard]] auto size() const -> size_t;
	[[nodiscard]] auto toString() const -> std::string;
	auto close() -> void override;
	auto flush() -> void override;
};
} // namespace common::io
#endif //BYTEARRAYOUTPUTSTREAM_HPP
