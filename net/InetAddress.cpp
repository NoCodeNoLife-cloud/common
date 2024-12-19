// Created by author ethereal on 2024/12/17.
// Copyright (c) 2024 ethereal. All rights reserved.
#include "InetAddress.hpp"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#define ICMP_ECHO_REQUEST 8

namespace common::io
{
std::vector<std::string> InetAddress::getLocalIpAddresses() {
	WSADATA wsaData;
	char hostname[256];
	addrinfo hints{}, *res;
	std::vector<std::string> ipAddresses;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed." << std::endl;
		return ipAddresses;
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
		std::cerr << "gethostname failed." << std::endl;
		WSACleanup();
		return ipAddresses;
	}
	if (getaddrinfo(hostname, nullptr, &hints, &res) != 0) {
		std::cerr << "getaddrinfo failed." << std::endl;
		WSACleanup();
		return ipAddresses;
	}
	for (struct addrinfo* p = res; p != nullptr; p = p->ai_next) {
		if (p->ai_family == AF_INET) {
			const void* addrPtr = &reinterpret_cast<struct sockaddr_in*>(p->ai_addr)->sin_addr;
			char ipStr[INET_ADDRSTRLEN];
			inet_ntop(p->ai_family, addrPtr, ipStr, sizeof(ipStr));
			ipAddresses.emplace_back(ipStr);
		}
		else if (p->ai_family == AF_INET6) {
			const void* addrPtr = &reinterpret_cast<struct sockaddr_in6*>(p->ai_addr)->sin6_addr;
			char ipStr[INET6_ADDRSTRLEN];
			inet_ntop(p->ai_family, addrPtr, ipStr, sizeof(ipStr));
			ipAddresses.emplace_back(ipStr);
		}
	}
	freeaddrinfo(res);
	WSACleanup();
	return ipAddresses;
}

bool InetAddress::testReachability(const std::string& ipAddress, int port) {
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		std::cerr << "WSAStartup failed with error: " << result << std::endl;
		return false;
	}
	const SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}
	sockaddr_in serverAddr{};
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr);
	result = connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
	if (result == SOCKET_ERROR) {
		const int wsaError = WSAGetLastError();
		closesocket(sock);
		WSACleanup();
		if (wsaError == WSAECONNREFUSED || wsaError == WSAETIMEDOUT) {
			return false;
		}
	}
	closesocket(sock);
	WSACleanup();
	return result == 0;
}
}
