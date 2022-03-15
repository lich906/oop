#include "html_decode.h"

#include <map>
#include <vector>

constexpr auto FRAME_SIZE = 7;
constexpr auto NULL_CHAR = '\0';
typedef std::vector<char> Frame;

//×ÇÕÁ
Frame ReplaceEntityInFrame(const Frame& frame)
{
	if (frame[0] == '&' && frame[1] == 'a' && frame[2] == 'p' && frame[3] == 'o' && frame[4] == 's')
	{
		if (frame[5] == ';')
		{
			return { '\'', frame[6] };
		}

		return { '\'', frame[5], frame[6] };
	}

	if (frame[0] == '&' && frame[1] == 'q' && frame[2] == 'u' && frame[3] == 'o' && frame[4] == 't')
	{
		if (frame[5] == ';')
		{
			return { '"', frame[6] };
		}

		return { '"', frame[5], frame[6] };
	}

	if (frame[0] == '&' && frame[1] == 'a' && frame[2] == 'm' && frame[3] == 'p')
	{
		if (frame[4] == ';')
		{
			return { '&', frame[5], frame[6] };
		}

		return { '&', frame[4], frame[5], frame[6] };
	}

	if (frame[0] == '&' && frame[1] == 'l' && frame[2] == 't')
	{
		if (frame[3] == ';')
		{
			return { '<', frame[4], frame[5], frame[6] };
		}

		return { '<', frame[3], frame[4], frame[5], frame[6] };
	}

	if (frame[0] == '&' && frame[1] == 'g' && frame[2] == 't')
	{
		if (frame[3] == ';')
		{
			return { '>', frame[4], frame[5], frame[6] };
		}

		return { '>', frame[3], frame[4], frame[5], frame[6] };
	}

	return frame;
}

char GetResultChar(Frame& frame)
{
	if (frame.size() < FRAME_SIZE)
	{
		return NULL_CHAR;
	}

	frame = ReplaceEntityInFrame(frame);

	return frame.front();
}

std::string HtmlDecode(const std::string& html)
{
	const std::map<std::string, char> decodeMap = {
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

		chToAppend = GetResultChar(frame);

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