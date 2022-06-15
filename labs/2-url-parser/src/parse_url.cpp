#include "parse_url.h"

Protocol MapHttpUrlProtocol(HttpUrl::Protocol httpUrlProtocol);

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	try
	{
		HttpUrl httpUrl(url);
		protocol = MapHttpUrlProtocol(httpUrl.GetProtocol());
		port = httpUrl.GetPort();
		host = httpUrl.GetDomain();
		document = httpUrl.GetDocument();

		return true;
	}
	catch (const UrlParsingError& e)
	{
		return false;
	}
}

Protocol MapHttpUrlProtocol(HttpUrl::Protocol httpUrlProtocol)
{
	switch (httpUrlProtocol)
	{
	case HttpUrl::Protocol::HTTP:
		return Protocol::HTTP;
	case HttpUrl::Protocol::HTTPS:
		return Protocol::HTTPS;
	case HttpUrl::Protocol::FTP:
		return Protocol::FTP;
	default:
		throw std::logic_error("Invalid http url protocol");
	}
}
