// Created by author ethereal on 2024/12/17.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <string>
#include <vector>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
namespace common::io
{
class InetAddress
{
public:
	InetAddress();
	explicit InetAddress(const std::string& address);
	~InetAddress();
	static auto getLocalHostName() -> std::string;
	static auto getLocalHostAddresses() -> std::vector<std::string>;
	[[nodiscard]] auto getHostName() const -> const std::string&;
	[[nodiscard]] auto getIPAddress() const -> const std::string&;
	static bool isIPAddress(const std::string& address);

private:
	static std::string resolveIPFromHostname(const std::string& host);
	static std::string resolveHostnameFromIP(const std::string& ip);
	std::string hostname;
	std::string ipAddress;
	WSADATA wsaData{};
};
}
