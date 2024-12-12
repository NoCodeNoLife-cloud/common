// Created by author ethereal on 2024/12/16.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

namespace common::io
{
class Date
{
public:
	~Date();
	Date();
	Date(int year, int month, int day);
	Date(int year, int month, int day, int hours, int minutes, int seconds);
	explicit Date(long long timestamp);
	Date clone() const;
	auto equals(const Date& other) const -> bool;
	auto after(const Date& other) const -> bool;
	auto before(const Date& other) const -> bool;
	auto getTime() const -> long long;
	auto getYear() const -> int;
	auto getMonth() const -> int;
	auto getDay() const -> int;
	auto toString() const -> std::string;
	auto hashCode() const -> size_t;

private:
	std::tm toTm() const;
	std::chrono::system_clock::time_point time_point_;
};
}
