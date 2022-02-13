#include <iostream>
#include <optional>
#include <string>

#define ARGUMENTS_COUNT 2

bool isNumber(std::string str)
{
	for (unsigned char ch : str)
	{
		if (!std::isdigit(ch))
		{
			return false;
		}
	}

	return true;
}

std::optional<unsigned char> StringToByte(std::string str)
{
	int num = std::stoi(str);

	if (num > 0xff || num < 0)
	{
		std::cout << "Error: Argument value " << num << " is out of range. (0 - 255)\n";
		return std::nullopt;
	}
	else
	{
		return static_cast<unsigned char>(num);
	}
}

std::optional<unsigned char> ParseArg(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		std::cout << "Error: Invalid arguments count. Usage: 1-flipbyte.exe <byte integer representation>\n";
		return std::nullopt;
	}

	std::string arg = argv[1];

	if (!isNumber(arg))
	{
		std::cout << "Error: Argument is not a number.\n";
		return std::nullopt;
	}

	std::optional<unsigned char> parsedByte = StringToByte(arg);
	if (!parsedByte.has_value())
	{
		return std::nullopt;
	}

	return parsedByte.value();
}

int main(int argc, char* argv[])
{
	std::optional<unsigned char> byte = ParseArg(argc, argv);

	if (byte.has_value())
	{
		std::cout << +byte.value() << "\n";
		return 0;
	}

	return 1;
}
