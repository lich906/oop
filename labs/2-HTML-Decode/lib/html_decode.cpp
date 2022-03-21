#include "html_decode.h"

#include <map>

typedef std::map<std::string, char> EntityDecodeMap;

const EntityDecodeMap decodeMap = {
	{ "&lt", '<' },
	{ "&gt", '>' },
	{ "&amp", '&' },
	{ "&apos", '\'' },
	{ "&quot", '"' }
};

bool CompareWithEntity(const std::string::const_iterator& first, const std::string::const_iterator& end, std::string entityCode)
{
	char i = 0;
	for (const char ch : entityCode)
	{
		if ((first + i) == end || ch != *(first + i))
		{
			return false;
		}
		++i;
	}

	return true;
}

char GetCharToAppend(std::string::const_iterator& first, const std::string::const_iterator& end)
{
	for (auto const& [entityCode, ch] : decodeMap)
	{
		if (CompareWithEntity(first, end, entityCode))
		{
			char codeLen = entityCode.length();
			std::advance(first, codeLen - (((first + codeLen) != end && *(first + codeLen) == ';') ? 0 : 1));
			return ch;
		}
	}

	return *first;
}

std::string HtmlDecode(const std::string& html)
{
	std::string decodedStr;
	std::string::const_iterator iterator = html.begin();

	while (iterator != html.end())
	{
		decodedStr.push_back(GetCharToAppend(iterator, html.end()));
		++iterator;
	}

	return decodedStr;
}