#pragma once
#include <string>
#include <map>
#include <stdexcept>
#include <regex>
#include "UrlParsingError.h"

class HttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	HttpUrl(const std::string& url);

	HttpUrl(
		const std::string& domain,
		const std::string& document,
		Protocol protocol = Protocol::HTTP);

	HttpUrl(
		const std::string& domain,
		const std::string& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL() const;

	std::string GetDomain() const;

	std::string GetDocument() const;

	Protocol GetProtocol() const;

	unsigned short GetPort() const;

private:
	static constexpr unsigned short defaultHttpPort = 80;
	static constexpr unsigned short defaultHttpsPort = 443;

	// сделать static или внешними функциями в безымянном пространстве имен
	static Protocol ParseProtocol(const std::string& url);
	static std::string ParseDomain(const std::string& url);
	unsigned short ParsePort(const std::string& url) const;
	static std::string ParseDocument(const std::string& url);

	static unsigned short GetDefaultPort(Protocol protocol);

	static bool IsValidDomain(const std::string& domain);
	static bool IsValidIpAddress(const std::string& ipAddress);
	
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};
