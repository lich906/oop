#include <fstream>
#include <iostream>
#include <optional>

#define ARGUMENTS_COUNT 3

struct Args
{
	char* inputFile;
	char* outputFile;
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

std::optional<std::ifstream> OpenInputStream(char* fileName)
{
	std::ifstream stream;
	stream.open(fileName);

	if (!stream.is_open())
	{
		return std::nullopt;
	}

	return stream;
}

std::optional<std::ofstream> OpenOutputStream(char* fileName)
{
	std::ofstream stream;
	stream.open(fileName);

	if (!stream.is_open())
	{
		return std::nullopt;
	}

	return stream;
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
		std::cout << "Invalid arguments count. Usage 1-copyfile <input file path> <output file path>\n";
		return 1;
	}

	std::optional<std::ifstream> inputFile = OpenInputStream(args->inputFile);

	if (!inputFile.has_value())
	{
		std::cout << "Error was occured while opening \"" << args->inputFile << "\" input file.\n";
		return 1;
	}

	std::optional<std::ofstream> outputFile = OpenOutputStream(args->outputFile);

	if (!outputFile.has_value())
	{
		std::cout << "Error was occured while opening \"" << args->outputFile << "\" output file.\n";
		return 1;
	}

	return CopyFile(inputFile.value(), outputFile.value());
}
