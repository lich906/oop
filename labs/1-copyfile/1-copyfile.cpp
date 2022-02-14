#include <fstream>
#include <iostream>
#include <optional>

constexpr auto ARGUMENTS_COUNT = 3;

struct Args
{
	std::string inputFilePath;
	std::string outputFilePath;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		return std::nullopt;
	}

	Args parsedArgs = { argv[1], argv[2] };

	return parsedArgs;
}

int ValidateStreams(std::ifstream& inStream, std::ofstream& outStream)
{
	if (!inStream.is_open())
	{
		std::cout << "Error was occured while opening input file.\n";
		return 1;
	}

	if (!outStream.is_open())
	{
		std::cout << "Error was occured while opening output file.\n";
		return 1;
	}

	return 0;
}

int CopyFile(std::ifstream& inStream, std::ofstream& outStream)
{
	char ch;
	while (inStream.get(ch))
	{
		if (!outStream.put(ch))
		{
			break;
		}
	}

	if (inStream.bad())
	{
		std::cout << "Failed to read data from file\n";
		return 1;
	}

	if (!outStream.flush())
	{
		std::cout << "Failed to write data into file\n";
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);

	if (!args.has_value())
	{
		std::cout << "Invalid arguments count. Usage: 1-copyfile.exe <input file path> <output file path>\n";
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(args->inputFilePath);
	std::ofstream outputFile;
	outputFile.open(args->outputFilePath);

	if (ValidateStreams(inputFile, outputFile))
	{
		return 1;
	}

	return CopyFile(inputFile, outputFile);
}
