#include <iostream>
#include <optional>
#include <fstream>
#include <string>

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

int Replace(std::ifstream& inStream, std::ofstream& outStream, std::string& searchStr, std::string& replaceStr)
{
	std::string buf;
	size_t pos, foundPos;
	while (std::getline(inStream, buf))
	{
		pos = 0;
		while ((foundPos = buf.find(searchStr, pos)) != std::string::npos)
		{
			if (!(outStream << buf.substr(pos, foundPos - pos) << replaceStr))
			{
				std::cout << "Failed to write data into output file.\n";
				return 1;
			}
			pos = foundPos + searchStr.length();
		}
		if (!(outStream << buf.substr(pos) << '\n'))
		{
			std::cout << "Failed to write data into output file.\n";
			return 1;
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
		std::cout << "Invalid arguments count. Usage: 1-replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	std::ifstream in(args->inputFilePath);
	std::ofstream out(args->outputFilePath);

	if (int err = ValidateStreams(in, out))
	{
		return err;
	}

	if (args->searchString.empty())
	{
		std::cout << "Search string is empty. File was copied without change.\n";
		return CopyFile(in, out);
	}

	return Replace(in, out, args->searchString, args->replaceString);
}
