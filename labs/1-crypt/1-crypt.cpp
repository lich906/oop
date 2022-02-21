#include <iostream>
#include <optional>
#include <string>
#include <fstream>

constexpr auto ARGUMENTS_COUNT = 4;

enum class Operation
{
	crypt,
	decrypt
};

struct Args
{
	Operation operation;
	std::string inputFilePath;
	std::string outputFilePath;
	unsigned char cryptKey;
};

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
			return std::nullopt;
		}
		else
		{
			byte = byte * 10 + DigitToInt(ch);
		}
	}

	return byte;
}

std::optional<unsigned char> ParseCryptKey(const std::string& key)
{
	if (!isNumber(key))
	{
		return std::nullopt;
	}

	return StringToByte(key);
}

std::optional<Args> ParseArg(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		LogError("Error: Invalid arguments count. Usage: 1-crypt.exe <operation (\"crypt\"/\"decrypt\")> <file to crypt/decrypt> <output file> <byte key>\n");
		return std::nullopt;
	}

	if (!(argv[1] == "crypt" || argv[1] == "decrypt"))
	{
		LogError("Error: Unknow operation. Available options: \"crypt\" or \"decrypt\".\n");
		return std::nullopt;
	}

	std::optional<unsigned char> cryptKey = ParseCryptKey(argv[4]);
	if (!cryptKey.has_value())
	{
		LogError("Error: Invalid crypt key.\n");
		return std::nullopt;
	}

	Args parsedArgs = {};
	parsedArgs.operation = (argv[1] == "crypt") ? Operation::crypt : Operation::decrypt;
	parsedArgs.inputFilePath = argv[2];
	parsedArgs.outputFilePath = argv[3];
	parsedArgs.cryptKey = cryptKey.value();

	return parsedArgs;
}

bool ValidateStreams(std::ifstream& inStream, std::ofstream& outStream)
{
	if (!inStream.is_open())
	{
		LogError("Error was occured while opening input file.\n");
		return false;
	}

	if (!outStream.is_open())
	{
		LogError("Error was occured while opening output file.\n");
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArg(argc, argv);
	if (!args.has_value())
	{
		return 1;
	}

	std::ifstream inputFile(args->inputFilePath, std::ios::binary);
	std::ofstream outputFile(args->outputFilePath, std::ios::binary);

	if (!ValidateStreams(inputFile, outputFile))
	{
		return 1;
	}
}
