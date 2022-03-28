#include <iostream>

#include "command_parsing.h"

int main()
{
	std::string userInput;

	while (std::getline(std::cin, userInput))
	{
		if(!ParseCommand(userInput).has_value())
		{
			std::cout << "Parsing error" << std::endl;
		}
		else
		{
			std::cout << "OK" << std::endl;
		}
	}
}
