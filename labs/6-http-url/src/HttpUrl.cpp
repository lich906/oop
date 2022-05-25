#include "HttpUrl.h"

const std::string protocolRegex(R"(^([hH][tT]{2}[pP][sS]?):\/\/.*)");

const std::string dnsDomainRegex(R"(((?:[\w-]{2,63}\.)*[\w-]{2,63}\.[a-zA-Z-]{2,63}))");
const std::string ipAddressRegex(R"(((?:\d{1,3}\.){3}\d{1,3}))");
const std::string detailIpAddressRegex(R"((\d+)\.(\d+)\.(\d+)\.(\d+))");
const std::string simpleNameRegex(R"(([\w-]+))");

const std::string portRegex(R"(.*:([\w]*)?(\/.*|$))");
const std::string documentRegex(R"(.*:\/\/[\w:.-]*\/?([\w.\/\?&=%-]*)$)");

HttpUrl::HttpUrl(const std::string& url)
	: m_protocol(ParseProtocol(url))
	, m_domain(ParseDomain(url))
	, m_port(ParsePort(url))
	, m_document(ParseDocument(url))
{
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
	: HttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

HttpUrl::HttpUrl(
	const std::string& domain,
	const std::string& document,
	Protocol protocol,
	unsigned short port)
{
	if (!IsValidDomain(domain))
	{
		throw UrlParsingError("Invalid domain");
	}

	m_domain = domain;
	m_document = (document.size() && document[0] != '/') ? "/" + document : document;
	m_protocol = protocol;
	m_port = port;
}

std::string HttpUrl::GetURL() const
{
	std::string urlStr;

	switch (m_protocol)
	{
	case Protocol::HTTP:
		urlStr.append("http://");
		break;
	case Protocol::HTTPS:
		urlStr.append("https://");
		break;
	default:
		throw std::invalid_argument("Invalid protocol");
	}

	urlStr.append(m_domain);

	if (GetDefaultPort(m_protocol) != m_port)
	{
		urlStr.push_back(':');
		urlStr.append(std::to_string(m_port));
	}

	return urlStr.append(m_document);
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

HttpUrl::Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short HttpUrl::GetPort() const
{
	return m_port;
}

unsigned short HttpUrl::GetDefaultPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return defaultHttpPort;
	case Protocol::HTTPS:
		return defaultHttpsPort;
	default:
		throw std::invalid_argument("Default port for protocol not found");
	}
}

bool HttpUrl::IsValidDomain(const std::string& domain)
{
	return 
		std::regex_match(domain, std::regex(dnsDomainRegex))
		|| IsValidIpAddress(domain)
		|| std::regex_match(domain, std::regex(simpleNameRegex));
}

bool HttpUrl::IsValidIpAddress(const std::string& ipAddress)
{
	if (!std::regex_match(ipAddress, std::regex(ipAddressRegex)))
	{
		return false;
	}

	std::smatch matches;
	std::regex_match(ipAddress, matches, std::regex(detailIpAddressRegex));
	for (size_t i = 1; i <= 4; ++i)
	{
		if (std::stoi(matches[i].str()) > 0xFF)
		{
			return false;
		}
	}

	return true;
}

HttpUrl::Protocol HttpUrl::ParseProtocol(const std::string& url)
{
	std::smatch matches;
	if (std::regex_match(url, matches, std::regex(protocolRegex)))
	{
		switch (matches[1].length())
		{
		case 5:
			return Protocol::HTTPS;
		case 4:
			return Protocol::HTTP;
		default:
			throw UrlParsingError("Invalid protocol");
		}
	}

	throw UrlParsingError("Invalid protocol");
}

std::string HttpUrl::ParseDomain(const std::string& url)
{
	// обрабатывать 127.0.0.1, localhost
	std::smatch matches;
	if (std::regex_match(url, matches, std::regex(R"(.*:\/\/)" + dnsDomainRegex + R"((:|\/|$).*)"))
		|| (std::regex_match(url, matches, std::regex(R"(.*:\/\/)" + ipAddressRegex + R"((:|\/|$).*)"))
			&& IsValidIpAddress(matches[1].str()))
		|| std::regex_match(url, matches, std::regex(R"(.*:\/\/)" + simpleNameRegex + R"((:|\/|$).*)"))
	)
	{
		return matches[1].str();
	}

	throw UrlParsingError("Invalid domain");
}

unsigned short HttpUrl::ParsePort(const std::string& url) const
{
	// 0 порт не валиден
	std::smatch matches;
	if (std::regex_match(url, matches, std::regex(portRegex)))
	{
		if (!matches[1].str().empty())
		{
			try
			{
				int port = std::stoi(matches[1].str());
				if (port > 0xFFFF || port <= 0)
				{
					throw UrlParsingError("Invalid port");
				}
				return port;
			}
			catch(...)
			{
				throw UrlParsingError("Invalid port");
			}
		}
		else
		{
			return GetDefaultPort(m_protocol);
		}
	}

	throw UrlParsingError("Invalid port");
}

std::string HttpUrl::ParseDocument(const std::string& url)
{
	std::smatch matches;
	if (std::regex_match(url, matches, std::regex(documentRegex)))
	{
		return "/" + matches[1].str();
	}

	throw UrlParsingError("Invalid document path");
}
