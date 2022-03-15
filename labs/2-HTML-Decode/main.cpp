#include <iostream>
#include "lib/html_decode.h"

int main()
{
	std::string inputStr;

	while (std::getline(std::cin, inputStr))
	{
		std::cout << HtmlDecode(inputStr) << '\n';
	}

	return 0;
}
