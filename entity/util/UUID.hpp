// Created by author ethereal on 2024/11/28.
// Copyright (c) 2024 ethereal. All rights reserved.
#ifndef UUID_HPP
#define UUID_HPP
#include <string>
#include <random>
#include <vector>
#include <cstdint>
#include "entity/interface/Comparable.hpp"

namespace common::entity::util
{
	/// \brief A class that represents a universally unique identifier (UUID).
	/// \details  A UUID is a 128-bit value that is used to identify information in computer systems.
	/// It is usually represented as a 32-character hexadecimal string, with 8 characters
	/// for the most significant 60 bits, a hyphen, 4 characters for the next 16 bits,
	/// a hyphen, 4 characters for the next 12 bits, a hyphen, and finally 12 characters
	/// for the least significant 48 bits.
	class UUID final : public interface::Comparable<UUID>
	{
	public:
		UUID();

		UUID(uint64_t mostSigBits, uint64_t leastSigBits);

		~UUID() override;

		static UUID randomUUID();

		static UUID fromString(const std::string& name);

		[[nodiscard]] auto getMostSignificantBits() const -> uint64_t;

		[[nodiscard]] auto getLeastSignificantBits() const -> uint64_t;

		[[nodiscard]] auto toString() const -> std::string;

		[[nodiscard]] auto equals(const UUID& other) const -> bool override;

		[[nodiscard]] auto compareTo(const UUID& other) const -> int override;

		[[nodiscard]] auto hashCode() const -> int;

		static auto nameUUIDFromBytes(const std::vector<uint8_t>& name) -> UUID;

	private:
		uint64_t mostSignificantBits{};
		uint64_t leastSignificantBits{};

		static auto generateRandom64Bits() -> uint64_t;
	};
}
#endif //UUID_HPP
