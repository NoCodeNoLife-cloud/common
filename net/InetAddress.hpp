// Created by author ethereal on 2024/12/17.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <iostream>
#include <vector>

namespace common::io
{
class InetAddress
{
public:
	static std::vector<std::string> getLocalIpAddresses();
	static bool testReachability(const std::string& ipAddress, int port);
};
}
