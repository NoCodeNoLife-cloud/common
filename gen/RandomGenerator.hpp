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
	template <typename T> static auto getUniformIntDistributionValue(T min, T max) -> T;
	template <typename T> static auto getUniformRealDistributionValue(T min, T max) -> T;
	template <typename T> static auto getNormalDistribution(T mean, T stddev) -> T;
	template <typename T> static auto getPoissonDistribution(T mean) -> T;
	template <typename T> static auto getDiscreteDistribution(T min, T max) -> T;
	template <typename T> static auto getExponentialDistribution(T lambda) -> T;

private:
	static inline auto gen_ = std::mt19937_64(std::random_device()());
};

///\brief Get a uniform integer distribution value
///\param min The minimum value
///\param max The maximum value
///\return The uniform integer distribution value
template <typename T> auto RandomGenerator::getUniformIntDistributionValue(T min, T max) -> T {
	std::uniform_int_distribution<T> dist(min, max);
	return dist(gen_);
}

/// \brief Get a uniform real distribution value
/// \param min The minimum value
/// \param max The maximum value
/// \return The uniform real distribution value
template <typename T> auto RandomGenerator::getUniformRealDistributionValue(T min, T max) -> T {
	std::uniform_real_distribution<T> dist(min, max);
	return dist(gen_);
}

/// \brief Get a normal distribution value
/// \param mean The mean of the normal distribution
/// \param stddev The standard deviation of the normal distribution
/// \return The normal distribution value
template <typename T> auto RandomGenerator::getNormalDistribution(T mean, T stddev) -> T {
	std::normal_distribution<T> dist(mean, stddev);
	return dist(gen_);
}

/// \brief Get a Poisson distribution value
/// \param mean The mean of the Poisson distribution
/// \return The Poisson distribution value
template <typename T> auto RandomGenerator::getPoissonDistribution(T mean) -> T {
	std::poisson_distribution<T> dist(mean);
	return dist(gen_);
}

/// \brief Get a discrete distribution value
/// \param min The minimum value
/// \param max The maximum value
/// \return The discrete distribution value
template <typename T> auto RandomGenerator::getDiscreteDistribution(T min, T max) -> T {
	std::uniform_int_distribution<T> dist(min, max);
	return dist(gen_);
}

/// \brief Get an exponential distribution value
/// \param lambda The lambda of the exponential distribution
/// \return The exponential distribution value
template <typename T> auto RandomGenerator::getExponentialDistribution(T lambda) -> T {
	std::exponential_distribution<T> dist(lambda);
	return dist(gen_);
}
}
