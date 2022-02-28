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

void LogError(const std::string& msg)
{
	std::cout << msg;
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

std::string ReplaceString(const std::string& src, const std::string& searchStr, const std::string& replaceStr)
{
	if (searchStr.empty())
	{
		return src;
	}

	std::string res;
	size_t pos, foundPos;
	pos = 0;
	while ((foundPos = src.find(searchStr, pos)) != std::string::npos)
	{
		//std::string::append
		res.append(src, pos, foundPos - pos).append(replaceStr);
		pos = foundPos + searchStr.length();
	}
	res.append(src, pos);

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

bool Replace(std::istream& inStream, std::ostream& outStream, const std::string& searchStr, const std::string& replaceStr)
{
	std::string curStr;
	while (std::getline(inStream, curStr))
	{
		if (!(outStream << ReplaceString(curStr, searchStr, replaceStr) << '\n'))
		{
			LogError("Failed to write data into file.\n");
			return false;
		}
	}

	return CheckStreams(inStream, outStream);
}

bool ReplaceSubstringsInFile(const Args& args)
{
	std::ifstream in(args.inputFilePath);
	std::ofstream out(args.outputFilePath);

	if (!ValidateStreams(in, out))
	{
		return false;
	}

	if (!Replace(in, out, args.searchString, args.replaceString))
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
		std::cout << "Invalid arguments count. Usage: 1-replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	if (!ReplaceSubstringsInFile(args.value()))
	{
		return 1;
	}

	return 0;
}
