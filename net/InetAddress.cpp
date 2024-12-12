// Created by author ethereal on 2024/12/17.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "InetAddress.hpp"
#include <stdexcept>

namespace common::io
{
/// \brief Default constructor.
/// Initialize the object with an empty hostname and an empty IP address.
InetAddress::InetAddress() {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		throw std::runtime_error("WSAStartup failed!");
	}
};

/// \brief Constructor from a string.
/// \details Initialize the object with the given address which can be a hostname or an IP address.
/// If the address is a hostname, the hostname and IP address fields will be set to the hostname and its resolved IP address.
/// If the address is an IP address, the hostname and IP address fields will be set to the IP address and its resolved hostname.
InetAddress::InetAddress(const std::string& address): InetAddress() {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		throw std::runtime_error("WSAStartup failed!");
	}
	if (isIPAddress(address)) {
		ipAddress = address;
		hostname = resolveHostnameFromIP(address);
	}
	else {
		hostname = address;
		ipAddress = resolveIPFromHostname(address);
	}
}

/// \brief Destructor.
/// \details Release any resources allocated by the InetAddress object.
InetAddress::~InetAddress() {
	WSACleanup();
};

/// \brief Get the local host name.
/// \details Get the host name of the current machine.
/// \return The local host name.
auto InetAddress::getLocalHostName() -> std::string {
	char buffer[256];
	if (gethostname(buffer, sizeof(buffer)) != 0) {
		throw std::runtime_error("Failed to get local host name");
	}
	return {buffer};
}

/// \brief Get the local host addresses.
/// \details Get the IP addresses of the current machine.
/// \return The local host addresses.
auto InetAddress::getLocalHostAddresses() -> std::vector<std::string> {
	std::vector<std::string> addresses;
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) != 0) {
		throw std::runtime_error("Failed to get local host name");
	}
	addrinfo hints = {}, *info;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(hostname, nullptr, &hints, &info) != 0) {
		throw std::runtime_error("Failed to get local host addresses");
	}
	for (const addrinfo* p = info; p != nullptr; p = p->ai_next) {
		char ipStr[INET6_ADDRSTRLEN];
		void* addr;
		if (p->ai_family == AF_INET) {
			addr = &reinterpret_cast<sockaddr_in*>(p->ai_addr)->sin_addr;
		}
		else if (p->ai_family == AF_INET6) {
			addr = &reinterpret_cast<sockaddr_in6*>(p->ai_addr)->sin6_addr;
		}
		else {
			continue;
		}
		inet_ntop(p->ai_family, addr, ipStr, sizeof(ipStr));
		addresses.emplace_back(ipStr);
	}
	freeaddrinfo(info);
	return addresses;
}

/// \brief Get the host name associated with this InetAddress instance.
/// \return A reference to the host name string.
auto InetAddress::getHostName() const -> const std::string& {
	return hostname;
}

/// \brief Get the IP address associated with this InetAddress instance.
/// \return A reference to the IP address string.
auto InetAddress::getIPAddress() const -> const std::string& {
	return ipAddress;
}

/// \brief Check if the provided address is a valid IP address.
/// \param address The address to check.
/// \return True if the address is a valid IP address, false otherwise.
auto InetAddress::isIPAddress(const std::string& address) -> bool {
	sockaddr_in sa{};
	return inet_pton(AF_INET, address.c_str(), &(sa.sin_addr)) == 1 || inet_pton(AF_INET6, address.c_str(), &(sa.sin_addr)) == 1;
}

/// \brief Resolve the IP address from the given hostname.
/// \details Resolve the IP address from the given hostname.
/// \param host The hostname to resolve.
/// \return The resolved IP address.
auto InetAddress::resolveIPFromHostname(const std::string& host) -> std::string {
	addrinfo hints = {}, *info;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(host.c_str(), nullptr, &hints, &info) != 0) {
		throw std::runtime_error("Failed to resolve IP address from hostname: " + host);
	}
	char ipStr[INET6_ADDRSTRLEN];
	void* addr;
	if (info->ai_family == AF_INET) {
		addr = &reinterpret_cast<sockaddr_in*>(info->ai_addr)->sin_addr;
	}
	else {
		addr = &reinterpret_cast<sockaddr_in6*>(info->ai_addr)->sin6_addr;
	}
	inet_ntop(info->ai_family, addr, ipStr, sizeof(ipStr));
	freeaddrinfo(info);
	return {ipStr};
}

/// \brief Resolve the hostname from the given IP address.
/// \details Resolve the hostname from the given IP address.
/// \param ip The IP address to resolve.
/// \return The resolved hostname.
auto InetAddress::resolveHostnameFromIP(const std::string& ip) -> std::string {
	sockaddr_storage addr{};
	socklen_t addrLen;
	if (inet_pton(AF_INET, ip.c_str(), &reinterpret_cast<sockaddr_in*>(&addr)->sin_addr) == 1) {
		addr.ss_family = AF_INET;
		addrLen = sizeof(sockaddr_in);
	}
	else if (inet_pton(AF_INET6, ip.c_str(), &reinterpret_cast<sockaddr_in6*>(&addr)->sin6_addr) == 1) {
		addr.ss_family = AF_INET6;
		addrLen = sizeof(sockaddr_in6);
	}
	else {
		throw std::runtime_error("Invalid IP address format: " + ip);
	}
	char hostname[NI_MAXHOST];
	if (getnameinfo(reinterpret_cast<sockaddr*>(&addr), addrLen, hostname, sizeof(hostname), nullptr, 0, 0) != 0) {
		throw std::runtime_error("Failed to resolve hostname from IP: " + ip);
	}
	return {hostname};
}
}
