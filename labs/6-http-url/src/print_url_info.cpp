#include "print_url_info.h"

void PrintUrlInfo(std::ostream& output, const HttpUrl& url)
{
	std::string protocol = (url.GetProtocol() == HttpUrl::Protocol::HTTPS) ? "HTTPS" : "HTTP";
	output
		<< "URL\t\t" << url.GetURL() << std::endl
		<< "Protocol\t" << protocol << std::endl
		<< "Domain\t\t" << url.GetDomain() << std::endl
		<< "Port\t\t" << url.GetPort() << std::endl
		<< "Document\t" << url.GetDocument() << std::endl;
}
