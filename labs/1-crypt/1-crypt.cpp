#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <array>

typedef std::array<int, 8> BitmapArray;

constexpr auto ARGUMENTS_COUNT = 5;
constexpr BitmapArray CRYPT_MAP = { 2, 3, 4, 6, 7, 0, 1, 5 };
constexpr BitmapArray DECRYPT_MAP = { 5, 6, 0, 1, 2, 7, 3, 4 };

enum class Operation
{
	Crypt,
	Decrypt
};

struct Args
{
	Operation operation;
	std::string inputFilePath;
	std::string outputFilePath;
	unsigned char cryptKey;
};

int DigitToInt(unsigned char digit)
{
	return digit - '0';
}

void LogError(const std::string& msg)
{
	std::cout << msg;
}

std::optional<unsigned char> ParseCryptKey(const std::string& keyString)
{
	if (keyString.empty())
	{
		return std::nullopt;
	}

	unsigned char key = 0;

	for (unsigned char ch : keyString)
	{
		if (!std::isdigit(ch))
		{
			return std::nullopt;
		}

		if ((key * 10 + DigitToInt(ch)) > 0xff)
		{
			return std::nullopt;
		}

		key = key * 10 + DigitToInt(ch);
	}

	return key;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		LogError("Error: Invalid arguments count. Usage: 1-crypt.exe <operation (\"crypt\"/\"decrypt\")> <file to crypt/decrypt> <output file> <byte key>\n");
		return std::nullopt;
	}

	std::string opStr(argv[1]);
	if (!(opStr == "crypt" || opStr == "decrypt"))
	{
		LogError("Error: Unknow operation \"" + opStr + "\". Available options: \"crypt\" or \"decrypt\".\n");
		return std::nullopt;
	}

	std::optional<unsigned char> cryptKey = ParseCryptKey(argv[4]);
	if (!cryptKey.has_value())
	{
		LogError("Error: Invalid crypt key.\n");
		return std::nullopt;
	}

	if (std::string(argv[2]) == std::string(argv[3]))
	{
		LogError("Error: Input and output files should not match.\n");
		return std::nullopt;
	}

	Args parsedArgs{};
	parsedArgs.operation = (opStr == "crypt") ? Operation::Crypt : Operation::Decrypt;
	parsedArgs.inputFilePath = argv[2];
	parsedArgs.outputFilePath = argv[3];
	parsedArgs.cryptKey = cryptKey.value();

	return parsedArgs;
}

void MoveBit(unsigned char srcByte, unsigned char& destByte, int srcPos, int destPos)
{
	destByte |= (((srcByte >> srcPos) & 1) << destPos);
}

unsigned char ShuffleByte(unsigned char byte, const BitmapArray& shufflingMap)
{
	unsigned char shuffledByte = 0;
	for (int i = 0; i < 8; ++i)
	{
		MoveBit(byte, shuffledByte, i, shufflingMap[i]);
	}
	return shuffledByte;
}

unsigned char ProcessByte(unsigned char byte, unsigned char key, Operation operation)
{
	if (operation == Operation::Crypt)
	{
		return ShuffleByte(byte ^ key, CRYPT_MAP);
	}
	else
	{
		return ShuffleByte(byte, DECRYPT_MAP) ^ key;
	}
}

bool CheckStreams(std::istream& inStream, std::ostream& outStream)
{
	if (inStream.bad())
	{
		LogError("Failed to read data from file.\n");
		return false;
	}

	if (!outStream.flush())
	{
		LogError("Failed to write data into file.\n");
		return false;
	}

	return true;
}

bool ProcessEncryption(std::istream& in, std::ostream& out, unsigned char key, Operation operation)
{
	char byte;
	while (in.get(byte))
	{
		if (!out.put(ProcessByte(byte, key, operation)))
		{
			break;
		}
	}

	return CheckStreams(in, out);
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

bool EncryptFile(const Args& args)
{
	std::ifstream inputFile(args.inputFilePath, std::ios::binary);
	std::ofstream outputFile(args.outputFilePath, std::ios::binary);

	if (!ValidateStreams(inputFile, outputFile))
	{
		return false;
	}

	if (!ProcessEncryption(inputFile, outputFile, args.cryptKey, args.operation))
	{
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);
	if (!args.has_value())
	{
		return 1;
	}

	if (!EncryptFile(args.value()))
	{
		return 1;
	}

	return 0;
}
