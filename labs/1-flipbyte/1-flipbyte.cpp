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
	return digit - '0';
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

unsigned char flipByte(unsigned char byte)
{
	unsigned char flippedByte = 0;
	for (int i = 0; i < 8; ++i)
	{
		flippedByte <<= 1;
		flippedByte += byte & 1;
		byte >>= 1;
	}

	return flippedByte;
}

int main(int argc, char* argv[])
{
	std::optional<unsigned char> arg = ParseArg(argc, argv);

	if (!arg.has_value())
	{
		return 1;
	}

	unsigned char byte = arg.value();
	std::cout << +flipByte(byte) << "\n";

	return 0;
}
