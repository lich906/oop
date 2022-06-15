#pragma once
#include "HttpUrl.h"

enum class Protocol
{
	HTTPS,
	HTTP,
	FTP
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document);