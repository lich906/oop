#include "html_decode.h"

#include <map>
#include <vector>

constexpr auto FRAME_SIZE = 7;
constexpr auto NULL_CHAR = '\0';
typedef std::vector<char> Frame;
typedef std::map<std::string, char> EntityDecodeMap;

Frame ReplaceEntityWithSymbol(const Frame& frame, const EntityDecodeMap& decodeMap)
{
	size_t i;
	bool match;
	for (auto const& [htmlCode, encodedCh] : decodeMap)
	{
		i = 0;
		match = true;
		for (const char ch : htmlCode)
		{
			if (ch != frame[i])
			{
				match = false;
				break;
			}
			++i;
		}

		if (match)
		{
			Frame res = { encodedCh };
			for (; i < frame.size(); ++i)
			{
				res.push_back(frame[i]);
			}
			return res;
		}
	}

	return frame;
}

char GetCharToAppend(Frame& frame, const EntityDecodeMap& decodeMap)
{
	if (frame.size() < FRAME_SIZE)
	{
		return NULL_CHAR;
	}

	frame = ReplaceEntityWithSymbol(frame, decodeMap);

	return frame.front();
}

std::string HtmlDecode(const std::string& html)
{
	const EntityDecodeMap decodeMap = {
		{ "&lt;", '<' },
		{ "&gt;", '>' },
		{ "&amp;", '&' },
		{ "&apos;", '\'' },
		{ "&quot;", '"' }
	};

	std::string decodedStr;
	char chToAppend;
	Frame frame;
	std::string::const_iterator htmlIt = html.begin();

	do
	{
		frame.push_back((htmlIt != html.end()) ? *htmlIt : NULL_CHAR);

		chToAppend = GetCharToAppend(frame, decodeMap);

		if (chToAppend != NULL_CHAR)
		{
			decodedStr.push_back(chToAppend);
			frame.erase(frame.begin());
		}

		if (htmlIt != html.end())
			++htmlIt;
	} while (frame[0] != NULL_CHAR);

	return decodedStr;
}