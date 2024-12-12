// Created by author ethereal on 2024/11/29.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "UuidGenerator.hpp"
#include <iomanip>
#include <sstream>

namespace common::entity::util
{
UuidGenerator::UuidGenerator() = default;

UuidGenerator::UuidGenerator(const uint64_t mostSigBits, const uint64_t leastSigBits) : mostSignificantBits(mostSigBits), leastSignificantBits(leastSigBits) {}

UuidGenerator::~UuidGenerator() = default;

/// \brief Generates a random UUID.
/// \return a random UUID.
auto UuidGenerator::randomUUID() -> UuidGenerator {
	return {generateRandom64Bits(), generateRandom64Bits()};
}

/// \brief Converts a string to a UUID.
/// \param name The string to be converted.
/// \return The UUID represented by the string.
/// \details The string must be in the format of 8-4-4-4-12, otherwise, an exception will be thrown.
auto UuidGenerator::fromString(const std::string& name) -> UuidGenerator {
	uint64_t msb = 0;
	uint64_t lsb = 0;
	size_t idx = 0;
	for (const char c : name) {
		if (c == '-') continue;
		const uint64_t hexValue = c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
		if (idx < 16) {
			msb = msb << 4 | hexValue;
		}
		else {
			lsb = lsb << 4 | hexValue;
		}
		++idx;
	}
	return {msb, lsb};
}

/// \brief Returns the most significant bits of the UUID.
/// \return The most significant 64 bits of the UUID.
auto UuidGenerator::getMostSignificantBits() const -> uint64_t {
	return mostSignificantBits;
}

/// \brief Returns the least significant bits of the UUID.
/// \return The least significant 64 bits of the UUID.
auto UuidGenerator::getLeastSignificantBits() const -> uint64_t {
	return leastSignificantBits;
}

/// \brief Converts the UUID to a string.
/// \return The string representation of the UUID, in the format of 8-4-4-4-12.
auto UuidGenerator::toString() const -> std::string {
	std::ostringstream oss;
	oss << std::hex << std::setfill('0') << std::setw(8) << (mostSignificantBits >> 32) << '-' << std::setw(4) << (mostSignificantBits >> 16 & 0xFFFF) << '-' << std::setw(4) << (mostSignificantBits & 0xFFFF) << '-' << std::setw(4) << (leastSignificantBits >> 48) << '-' << std::setw(12) << (leastSignificantBits & 0xFFFFFFFFFFFFULL);
	return oss.str();
}

/// \brief Checks if the UUID is equal to another UUID.
/// \param other The UUID to compare with.
/// \return True if the UUIDs are equal.
auto UuidGenerator::equals(const UuidGenerator& other) const -> bool {
	return mostSignificantBits == other.mostSignificantBits && leastSignificantBits == other.leastSignificantBits;
}

/// \brief Compares the UUID with another UUID.
/// \param other The UUID to compare with.
/// \return A negative integer, zero, or a positive integer as the UUID is less than, equal to, or greater than the
/// other UUID.
auto UuidGenerator::compareTo(const UuidGenerator& other) const -> int {
	if (mostSignificantBits < other.mostSignificantBits) return -1;
	if (mostSignificantBits > other.mostSignificantBits) return 1;
	if (leastSignificantBits < other.leastSignificantBits) return -1;
	if (leastSignificantBits > other.leastSignificantBits) return 1;
	return 0;
}

/// \brief Returns a hash code for the UUID.
/// \return A hash code for the UUID.
auto UuidGenerator::hashCode() const -> int {
	return static_cast<int>(mostSignificantBits >> 32 ^ mostSignificantBits ^ leastSignificantBits >> 32 ^ leastSignificantBits);
}

/// \brief Converts a byte array to a UUID.
/// \param name The byte array to be converted.
/// \return The UUID represented by the byte array.
/// \details The byte array is hashed using the std::hash function and the 128-bit hash value is used to create a UUID.
auto UuidGenerator::nameUUIDFromBytes(const std::vector<unsigned char>& name) -> UuidGenerator {
	constexpr std::hash<std::string> hashFn;
	const std::string data(name.begin(), name.end());
	const size_t hashValue = hashFn(data);
	return {static_cast<uint64_t>(hashValue), (hashValue >> 32)};
}

/// \brief Generates a random 64-bit value.
/// \return A random 64-bit value.
auto UuidGenerator::generateRandom64Bits() -> uint64_t {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<uint64_t> dis;
	return dis(gen);
}
}
