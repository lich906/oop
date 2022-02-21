#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <sstream>

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

//bool 
bool ValidateStreams(std::ifstream& inStream, std::ofstream& outStream)
{
	if (!inStream.is_open())
	{
		std::cout << "Error was occured while opening input file.\n";
		return false;
	}

	if (!outStream.is_open())
	{
		std::cout << "Error was occured while opening output file.\n";
		return false;
	}

	return true;
}

void LogError(const std::string& msg)
{
	std::cout << msg;
}

std::string ReplaceString(const std::string& src, const std::string& searchStr, const std::string& replaceStr)
{
	std::string res("");
	if (searchStr.empty())
	{
		return src;
	}

	size_t pos, foundPos;
	pos = 0;
	while ((foundPos = src.find(searchStr, pos)) != std::string::npos)
	{
		res += src.substr(pos, foundPos - pos) + replaceStr;
		pos = foundPos + searchStr.length();
	}
	res += src.substr(pos) + '\n';

	return res;
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

//return bool
//istream, ostream&
//добавить обработку пустого searchString
bool Replace(std::istream& inStream, std::ostream& outStream, const std::string& searchStr, const std::string& replaceStr)
{
	std::string curStr;
	while (std::getline(inStream, curStr))
	{
		if (!(outStream << ReplaceString(curStr, searchStr, replaceStr)))
		{
			LogError("Failed to write data into file.\n");
			return false;
		}
	}

	return CheckStreams(inStream, outStream);
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

	if (!ValidateStreams(in, out))
	{
		return 1;
	}

	if(!Replace(in, out, args->searchString, args->replaceString))
	{
		return 1;
	}

	return 0;
}
