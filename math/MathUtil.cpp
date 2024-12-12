// Created by author ethereal on 2024/11/24.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "MathUtil.hpp"
#include <cmath>
#include <limits>
#include <numbers>
#include <random>

namespace common::math
{
/// \brief Returns the absolute value of a double value.
/// \details If the argument is not negative, the result is the same as the argument. If the argument is negative, the
/// result is the negation of the argument.
/// \param[in] a The double value whose absolute value is to be determined.
/// \return The absolute value of the argument.
double MathUtil::abs(const double a) {
	return std::fabs(a);
}

/// \brief Returns the absolute value of a float value.
/// \details If the argument is not negative, the result is the same as the argument. If the argument is negative, the
/// result is the negation of the argument.
/// \param[in] a The float value whose absolute value is to be determined.
/// \return The absolute value of the argument.
float MathUtil::abs(const float a) {
	return std::fabs(a);
}

/// \brief Returns the absolute value of an int value.
/// \details If the argument is not negative, the result is the same as the argument. If the argument is negative, the
/// result is the negation of the argument.
/// \param[in] a The int value whose absolute value is to be determined.
/// \return The absolute value of the argument.
int MathUtil::abs(const int a) {
	return std::abs(a);
}

/// \brief Returns the absolute value of a long value.
/// \details If the argument is not negative, the result is the same as the argument. If the argument is negative, the
/// result is the negation of the argument.
/// \param[in] a The long value whose absolute value is to be determined.
/// \return The absolute value of the argument.
long MathUtil::abs(const long a) {
	return std::labs(a);
}

/// \brief Returns the arc cosine of a double value.
/// \details The arc cosine is the angle whose cosine is the specified number.
/// The returned angle is in the range [0.0, pi] radians.
/// \param[in] a The double value whose arc cosine is to be determined.
/// \return The arc cosine of the argument.
/// \throws std::domain_error If the argument is outside the range [-1.0, 1.0].
double MathUtil::acos(const double a) {
	return std::acos(a);
}

/// \brief Returns the arc sine of a double value.
/// \details The arc sine is the angle whose sine is the specified number.
/// The returned angle is in the range [-pi/2, pi/2] radians.
/// \param[in] a The double value whose arc sine is to be determined.
/// \return The arc sine of the argument.
/// \throws std::domain_error If the argument is outside the range [-1.0, 1.0].
double MathUtil::asin(const double a) {
	return std::asin(a);
}

/// \brief Returns the arc tangent of a double value.
/// \details The arc tangent is the angle whose tangent is the specified number.
/// The returned angle is in the range [-pi/2, pi/2] radians.
/// \param[in] a The double value whose arc tangent is to be determined.
/// \return The arc tangent of the argument.
double MathUtil::atan(const double a) {
	return std::atan(a);
}

/// \brief Returns the angle in radians from the x-axis to the point (y, x).
/// \details The angle is in the range [-pi, pi] radians.
/// \param[in] y The y-coordinate of the point.
/// \param[in] x The x-coordinate of the point.
/// \return The angle in radians from the x-axis to the point (y, x).
double MathUtil::atan2(const double y, const double x) {
	return std::atan2(y, x);
}

/// \brief Returns the cube root of a double value.
/// \details The cube root is the value which, when multiplied by itself three times, produces the argument.
/// \param[in] a The double value whose cube root is to be determined.
/// \return The cube root of the argument.
double MathUtil::cbrt(const double a) {
	return std::cbrt(a);
}

/// \brief Returns the square root of a double value.
/// \details The square root is the value which, when multiplied by itself, produces the argument.
/// \param[in] a The double value whose square root is to be determined.
/// \return The square root of the argument.
double MathUtil::sqrt(const double a) {
	return std::sqrt(a);
}

/// \brief Returns the smallest integer that is greater than or equal to the argument.
/// \details The ceiling of a double value is the smallest integer that is greater than or equal to the argument.
/// \param[in] a The double value whose ceiling is to be determined.
/// \return The smallest integer that is greater than or equal to the argument.
double MathUtil::ceil(const double a) {
	return std::ceil(a);
}

/// \brief Returns the largest integer that is less than or equal to the argument.
/// \details The floor of a double value is the largest integer that is less than or equal to the argument.
/// \param[in] a The double value whose floor is to be determined.
/// \return The largest integer that is less than or equal to the argument.
double MathUtil::floor(const double a) {
	return std::floor(a);
}

/// \brief Returns the double value that is closest in value to the argument and is equal to a mathematical integer.
/// \details If two double values that are mathematical integers are equally close to the value of the argument, the
/// result is the integer value that is even.
/// \param[in] a The double value whose integer value closest to the argument is to be determined.
/// \return The double value that is closest in value to the argument and is equal to a mathematical integer.
double MathUtil::rint(const double a) {
	return std::nearbyint(a);
}

/// \brief Returns the closest long to the argument, with ties rounding to positive infinity.
/// \details The value of the argument is rounded to the nearest long value.
/// If the argument is halfway between two long values, the result is the long value that is closer to positive
/// infinity.
/// \param[in] a The double value whose rounded value is to be determined.
/// \return The closest long to the argument, with ties rounding to positive infinity.
long MathUtil::round(const double a) {
	return static_cast<long>(std::round(a));
}

/// \brief Returns the closest int to the argument, with ties rounding to positive infinity.
/// \details The value of the argument is rounded to the nearest int value.
/// If the argument is halfway between two int values, the result is the int value that is closer to positive infinity.
/// \param[in] a The float value whose rounded value is to be determined.
/// \return The closest int to the argument, with ties rounding to positive infinity.
int MathUtil::round(const float a) {
	return static_cast<int>(std::round(a));
}

/// \brief Returns Euler's number e raised to the power of a double value.
/// \details This function returns Euler's number e raised to the power of the argument.
/// \param[in] a The double value whose exponential value is to be determined.
/// \return Euler's number e raised to the power of the argument.
double MathUtil::exp(const double a) {
	return std::exp(a);
}

/// \brief Returns the natural logarithm of a double value.
/// \details This function returns the natural logarithm of the argument.
/// \param[in] a The double value whose natural logarithm is to be determined.
/// \return The natural logarithm of the argument.
double MathUtil::log(const double a) {
	return std::log(a);
}

/// \brief Returns the base 10 logarithm of a double value.
/// \details This function returns the base 10 logarithm of the argument.
/// \param[in] a The double value whose base 10 logarithm is to be determined.
/// \return The base 10 logarithm of the argument.
double MathUtil::log10(const double a) {
	return std::log10(a);
}

/// \brief Raises a double value to the power of another double value.
/// \details This function computes the value of the first argument raised to the power of the second argument.
/// \param[in] a The base value to be raised to the power.
/// \param[in] b The exponent value.
/// \return The result of raising the base to the power of the exponent.
/// \throws std::domain_error If the base is zero and the exponent is less than or equal to zero.
double MathUtil::pow(const double a, const double b) {
	return std::pow(a, b);
}

/// \brief Returns a random double value between 0.0 and 1.0.
/// \details This function uses the Mersenne Twister engine to generate a random double value.
/// \return A random double value between 0.0 and 1.0.
double MathUtil::random() {
	std::random_device rd{};
	std::mt19937 gen{rd()};
	std::uniform_real_distribution dis{0.0, 1.0};
	return dis(gen);
}

/// \brief Returns the sine of a double value.
/// \details This function returns the sine of the argument.
/// \param[in] a The double value whose sine is to be determined.
/// \return The sine of the argument.
double MathUtil::sin(const double a) {
	return std::sin(a);
}

/// \brief Returns the cosine of a double value.
/// \details This function returns the cosine of the argument.
/// \param[in] a The double value whose cosine is to be determined.
/// \return The cosine of the argument.
double MathUtil::cos(const double a) {
	return std::cos(a);
}

/// \brief Returns the tangent of a double value.
/// \details This function returns the tangent of the argument.
/// \param[in] a The double value whose tangent is to be determined.
/// \return The tangent of the argument.
double MathUtil::tan(const double a) {
	return std::tan(a);
}

/// \brief Returns the hyperbolic sine of a double value.
/// \details This function returns the hyperbolic sine of the argument.
/// \param[in] x The double value whose hyperbolic sine is to be determined.
/// \return The hyperbolic sine of the argument.
double MathUtil::sinh(const double x) {
	return std::sinh(x);
}

/// \brief Returns the hyperbolic cosine of a double value.
/// \details This function returns the hyperbolic cosine of the argument.
/// \param[in] x The double value whose hyperbolic cosine is to be determined.
/// \return The hyperbolic cosine of the argument.
double MathUtil::cosh(const double x) {
	return std::cosh(x);
}

/// \brief Returns the hyperbolic tangent of a double value.
/// \details This function returns the hyperbolic tangent of the argument.
/// \param[in] x The double value whose hyperbolic tangent is to be determined.
/// \return The hyperbolic tangent of the argument.
double MathUtil::tanh(const double x) {
	return std::tanh(x);
}

/// \brief Converts radians to degrees.
/// \details This function converts a double value in radians to an equivalent double value in degrees.
/// \param[in] radians The double value in radians to be converted.
/// \return The equivalent double value in degrees.
double MathUtil::toDegrees(const double radians) {
	return radians * 180.0 / std::numbers::pi;
}

/// \brief Converts degrees to radians.
/// \details This function converts a double value in degrees to an equivalent double value in radians.
/// \param[in] degrees The double value in degrees to be converted.
/// \return The equivalent double value in radians.
double MathUtil::toRadians(const double degrees) {
	return degrees * std::numbers::pi / 180.0;
}

/// \brief Returns the unit in the last place (ULP) of a double value.
/// \details The ULP is the positive distance between the given double value and the next larger representable double
/// value.
/// \param[in] d The double value whose ULP is to be determined.
/// \return The ULP of the argument.
double MathUtil::ulp(const double d) {
	return std::nextafter(d, std::numeric_limits<double>::infinity()) - d;
}

/// \brief Returns the unit in the last place (ULP) of a float value.
/// \details The ULP is the positive distance between the given float value and the next larger representable float
/// value.
/// \param[in] f The float value whose ULP is to be determined.
/// \return The ULP of the argument.
float MathUtil::ulp(const float f) {
	return std::nextafterf(f, std::numeric_limits<float>::infinity()) - f;
}

/// \brief Returns the signum function of a double value.
/// \details The signum function returns -1 if the argument is less than zero, 0 if the argument is zero, and 1 if the
/// argument is greater than zero.
/// \param[in] d The double value whose signum is to be determined.
/// \return The signum of the argument.
double MathUtil::signum(const double d) {
	return (d > 0) - (d < 0);
}

/// \brief Returns the signum function of a float value.
/// \details The signum function returns -1.0f if the argument is less than zero, 0.0f if the argument is zero, and 1.0f
/// if the argument is greater than zero.
/// \param[in] f The float value whose signum is to be determined.
/// \return The signum of the argument.
float MathUtil::signum(const float f) {
	return static_cast<float>((f > 0) - (f < 0));
}

/// \brief Returns the square root of the sum of the squares of two double values.
/// \details This function returns the square root of the sum of the squares of the two arguments.
/// \param[in] x The first double value.
/// \param[in] y The second double value.
/// \return The square root of the sum of the squares of the two arguments.
double MathUtil::hypot(const double x, const double y) {
	return std::hypot(x, y);
}

/// \brief Returns the first floating-point argument with the sign of the second floating-point argument.
/// \details This function returns the value of the first argument with the sign of the second argument.
/// \param[in] magnitude The double value whose magnitude is used.
/// \param[in] sign The double value whose sign is used.
/// \return The first argument with the sign of the second argument.
double MathUtil::copySign(const double magnitude, const double sign) {
	return std::copysign(magnitude, sign);
}
}
