#include <iostream>
#include <map>
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

int DigitToInt(unsigned char digit)
{
	std::map<unsigned char, int> castMap = {
		{ '0', 0 },
		{ '1', 1 },
		{ '2', 2 },
		{ '3', 3 },
		{ '4', 4 },
		{ '5', 5 },
		{ '6', 6 },
		{ '7', 7 },
		{ '8', 8 },
		{ '9', 9 },
	};

	return castMap[digit];
}

std::optional<unsigned char> StringToByte(std::string str)
{
	unsigned char byte = 0;

	for (unsigned char ch : str)
	{
		if ((byte * 10 + DigitToInt(ch)) > 0xff)
		{
			std::cout << "Error: Argument value is out of range. (0 - 255)\n";
			return std::nullopt;
		}
		else
		{
			byte = byte * 10 + DigitToInt(ch);
		}
	}

	return byte;
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
		std::cout << "Error: Argument is not a valid number. (0 - 255)\n";
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
	std::optional<unsigned char> arg = ParseArg(argc, argv);

	if (!arg.has_value())
	{
		return 1;
	}

	unsigned char byte = arg.value();
	unsigned char invertedByte = 0;

	for (int i = 0; i < 8; ++i)
	{
		invertedByte <<= 1;
		invertedByte += byte & 1;
		byte >>= 1;
	}

	std::cout << +invertedByte << "\n";

	return 0;
}
