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

	Protocol ParseProtocol(const std::string& url) const;
	std::string ParseDomain(const std::string& url) const;
	unsigned short ParsePort(const std::string& url) const;
	std::string ParseDocument(const std::string& url) const;

	unsigned short GetDefaultPort(Protocol protocol) const;

	bool IsValidDomain(const std::string& domain) const;
	
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};
