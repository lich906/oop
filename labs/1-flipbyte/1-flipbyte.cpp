#include <iostream>
#include <optional>
#include <string>
#include <charconv>

constexpr auto ARGUMENTS_COUNT = 2;

int DigitToInt(unsigned char digit)
{
	return digit - '0';
}

void LogError(const std::string& msg)
{
	std::cout << msg;
}

/// <summary>
/// ”простить либо std::stoi либо std::from_chars
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
std::optional<unsigned char> ParseByte(const std::string& str)
{
	using namespace std;

	unsigned char byte = 0;
	from_chars_result res = from_chars(str.data(), str.data() + str.size(), byte);

	if (res.ec == errc::invalid_argument || !string(res.ptr).empty())
	{
		LogError("Error: Argument is not a valid number. (0 - 255)\n");
		return nullopt;
	}

	if (res.ec == errc::result_out_of_range)
	{
		LogError("Error: Argument value is out of range. (0 - 255)\n");
		return nullopt;
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

	std::optional<unsigned char> parsedByte = ParseByte(argv[1]);
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
	std::cout << static_cast<int>(byte) << '\n';
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
