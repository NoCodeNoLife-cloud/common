// Created by author ethereal on 2024/11/24.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <format>

namespace common::math
{
/// \class MathUtil
/// \brief Provides a collection of mathematical functions and constants.
/// \details This abstract class offers a variety of static methods for performing mathematical operations such as
/// trigonometric, logarithmic, and exponential calculations. It also includes utility functions for rounding, finding
/// absolute values, and generating random numbers. The Math class is designed to be a comprehensive library for
/// mathematical computations.
class MathUtil abstract
{
public:
	static double abs(double a);
	static float abs(float a);
	static int abs(int a);
	static long abs(long a);
	static double acos(double a);
	static double asin(double a);
	static double atan(double a);
	static double atan2(double y, double x);
	static double cbrt(double a);
	static double sqrt(double a);
	static double ceil(double a);
	static double floor(double a);
	static double rint(double a);
	static long round(double a);
	static int round(float a);
	static double exp(double a);
	static double log(double a);
	static double log10(double a);
	static double pow(double a, double b);
	static double random();
	static double sin(double a);
	static double cos(double a);
	static double tan(double a);
	static double sinh(double x);
	static double cosh(double x);
	static double tanh(double x);
	template <typename T> static T max(T a, T b);
	template <typename T> static T min(T a, T b);
	static double toDegrees(double radians);
	static double toRadians(double degrees);
	static double ulp(double d);
	static float ulp(float f);
	static double signum(double d);
	static float signum(float f);
	static double hypot(double x, double y);
	static double copySign(double magnitude, double sign);
};

/// \brief Returns the maximum value of two values.
/// \details This function returns the maximum value of the two arguments.
/// \param[in] a The first value to compare.
/// \param[in] b The second value to compare.
/// \return The maximum value of the two arguments.
template <typename T> T MathUtil::max(T a, T b) {
	return a > b ? a : b;
}

/// \brief Returns the minimum value of two values.
/// \details This function returns the minimum value of the two arguments.
/// \param[in] a The first value to compare.
/// \param[in] b The second value to compare.
/// \return The minimum value of the two arguments.
template <typename T> T MathUtil::min(T a, T b) {
	return a < b ? a : b;
}
}
