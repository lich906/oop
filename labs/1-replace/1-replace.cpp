#include <iostream>
#include <optional>
#include <fstream>

constexpr auto ARGUMENTS_COUNT = 5;

struct Args
{
	std::string inputFilePath;
	std::string outputFilePath;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		return std::nullopt;
	}

	Args parsedArgs = { argv[1], argv[2], argv[3], argv[4] };

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

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);

	if (!args.has_value())
	{
		std::cout << "Invalid arguments count. Usage: 1-replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	std::ifstream in(args->inputFilePath, std::ios::in);
	std::ofstream out(args->outputFilePath, std::ios::out);

	if (int err = ValidateStreams(in, out))
	{
		return err;
	}

	if (args->searchString.empty())
	{

	}
}
