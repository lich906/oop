#include <iostream>
#include "print_url_info.h"

int main()
{
	std::string inputStr;
	while (!std::cin.eof())
	{
		std::cout << "> ";
		std::getline(std::cin, inputStr);

		if (inputStr.empty())
			continue;

		try
		{
			HttpUrl url(inputStr);
			PrintUrlInfo(std::cout, url);
		}
		catch(const UrlParsingError& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
		}
	}

	std::cout << "Goodbye" << std::endl;

	return 0;
}
