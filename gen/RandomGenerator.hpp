// Created by author ethereal on 2024/11/20.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <random>

namespace common::gen
{
/// \class RandomGenerator
/// \brief Abstract class for generating random values.
class RandomGenerator abstract
{
public:
	RandomGenerator();
	explicit RandomGenerator(long seed);
	auto nextBoolean() -> bool;
	auto nextBytes(std::vector<unsigned char>& bytes) -> void;
	auto nextDouble() -> double;
	auto nextFloat() -> float;
	auto nextGaussian() -> double;
	auto nextInt() -> int;
	auto nextInt(int n) -> int;
	auto nextLong() -> long;
	auto setSeed(long seed) -> void;

protected:
	std::mt19937 generator;
	std::uniform_real_distribution<> realDist;
	std::normal_distribution<> normalDist;
	int next(int bits);
};

inline RandomGenerator::RandomGenerator(): generator(std::random_device{}()), realDist(0.0, 1.0), normalDist(0.0, 1.0) {}

inline RandomGenerator::RandomGenerator(const long seed): generator(seed), realDist(0.0, 1.0), normalDist(0.0, 1.0) {}

/// \brief Generates a random boolean value.
/// \details The function utilizes a Bernoulli distribution with a probability of 0.5
/// to generate a random boolean value, returning either true or false with equal likelihood.
/// \return A boolean value, either true or false.
inline bool RandomGenerator::nextBoolean() {
	std::bernoulli_distribution dist(0.5);
	return dist(generator);
}

/// \brief Generates random bytes and places them in a user-supplied byte array.
/// \details The number of random bytes produced is equal to the length of the
/// user-supplied byte array.
/// \param[in] bytes The byte array to be filled with random bytes.
inline auto RandomGenerator::nextBytes(std::vector<unsigned char>& bytes) -> void {
	std::uniform_int_distribution<unsigned int> dist(0, 255);
	std::generate(bytes.begin(), bytes.end(), [&]() {
		return static_cast<unsigned char>(dist(generator));
	});
}

/// \brief Generates a random double value.
/// \details The function utilizes a uniform real distribution to generate a
/// random double value in the range [0.0, 1.0).
/// \return A double value in the range [0.0, 1.0).
inline auto RandomGenerator::nextDouble() -> double {
	return realDist(generator);
}

/// \brief Generates a random float value.
/// \details The function utilizes a uniform real distribution to generate a
/// random float value in the range [0.0, 1.0).
/// \return A float value in the range [0.0, 1.0).
inline auto RandomGenerator::nextFloat() -> float {
	return static_cast<float>(realDist(generator));
}

/// \brief Generates a random float value.
/// \details The function utilizes a uniform real distribution to generate a
/// random float value in the range [0.0, 1.0).
/// \return A float value in the range [0.0, 1.0).
inline auto RandomGenerator::nextGaussian() -> double {
	return normalDist(generator);
}

/// \brief Generates a random int value.
/// \details The function utilizes a uniform integer distribution to generate a
/// random int value in the range [Integer.MIN_VALUE, Integer.MAX_VALUE].
/// \return An int value in the range [Integer.MIN_VALUE, Integer.MAX_VALUE].
inline auto RandomGenerator::nextInt() -> int {
	return next(32);
}

/// \brief Generates a random int value in the range [0, n).
/// \details The function utilizes a uniform integer distribution to generate a
/// random int value between 0 (inclusive) and n (exclusive).
/// \param n The exclusive upper bound of the range.
/// \return An int value in the range [0, n).
/// \throws std::invalid_argument if n is less than or equal to 0.
inline auto RandomGenerator::nextInt(int n) -> int {
	if (n <= 0) {
		throw std::invalid_argument("n must be greater than 0");
	}
	std::uniform_int_distribution<int> dist(0, n - 1);
	return dist(generator);
}

/// \brief Generates a random long value in the range [Long.MIN_VALUE, Long.MAX_VALUE].
/// \details The function utilizes a uniform integer distribution to generate a
/// random long value in the range [Long.MIN_VALUE, Long.MAX_VALUE].
/// \return A long value in the range [Long.MIN_VALUE, Long.MAX_VALUE].
inline auto RandomGenerator::nextLong() -> long {
	std::uniform_int_distribution<long> dist(0, LONG_MAX);
	return dist(generator);
}

/// \brief Sets the seed of the random number generator using a single long seed.
/// \details The seed is used to initialize the internal state of the random number generator.
/// \param seed The seed value.
inline auto RandomGenerator::setSeed(long seed) -> void {
	generator.seed(seed);
}

/// \brief Generates a random int value.
/// \details The function utilizes a uniform integer distribution to generate a
/// random int value in the range [0, 2^bits - 1].
/// \param bits The number of bits used to represent the generated integer.
/// \return An int value in the range [0, 2^bits - 1].
inline auto RandomGenerator::next(int bits) -> int {
	std::uniform_int_distribution<int> dist(0, (1 << bits) - 1);
	return dist(generator);
}
}
