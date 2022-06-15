#include <iostream>
#include "parse_url.h"

int main()
{
	Protocol protocol;
	int port;
	std::string host, document;
	std::string url;

	std::cout << "> ";
	while (std::getline(std::cin, url))
	{
		if (url.empty())
			continue;

		if (ParseURL(url, protocol, port, host, document))
		{
			std::cout
				<< url << std::endl
				<< "HOST: " << host << std::endl
				<< "PORT: " << port << std::endl
				<< "DOC: " << document << std::endl;
		}
		else
		{
			std::cout << "Invalid url." << std::endl;
		}

		std::cout << "> ";
	}

	return 0;
}