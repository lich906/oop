#include <iostream>
#include <optional>
#include <string>

constexpr auto ARGUMENTS_COUNT = 2;

bool isNumber(const std::string& str)
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

void LogError(const std::string& msg)
{
	std::cout << msg;
}

std::optional<unsigned char> StringToByte(const std::string& str)
{
	unsigned char byte = 0;

	for (unsigned char ch : str)
	{
		if ((byte * 10 + DigitToInt(ch)) > 0xff)
		{
			LogError("Error: Argument value is out of range. (0 - 255)\n");
			return std::nullopt;
		}
		byte = byte * 10 + DigitToInt(ch);
	}

	return byte;
}

std::optional<unsigned char> ParseArg(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		LogError("Error: Invalid arguments count. Usage: 1-flipbyte.exe <byte integer representation>\n");
		return std::nullopt;
	}

	std::string arg = argv[1];

	if (!isNumber(arg))
	{
		LogError("Error: Argument is not a valid number. (0 - 255)\n");
		return std::nullopt;
	}

	std::optional<unsigned char> parsedByte = StringToByte(arg);
	if (!parsedByte.has_value())
	{
		return std::nullopt;
	}

	return parsedByte.value();
}

unsigned char FlipByte(unsigned char byte)
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

void PrintByte(unsigned char byte)
{
	std::cout << +byte << '\n';
}

int main(int argc, char* argv[])
{
	std::optional<unsigned char> arg = ParseArg(argc, argv);

	if (!arg.has_value())
	{
		return 1;
	}

	unsigned char byte = arg.value();
	PrintByte(FlipByte(byte));

	return 0;
}
