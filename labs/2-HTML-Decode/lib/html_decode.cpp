#include "html_decode.h"

#include <optional>

enum class HtmlEntityCode
{
	Lt,
	Gt,
	Apos,
	Quot,
	Amp
};

void AppendDecodedHtmlEntity(std::string& str, std::optional<HtmlEntityCode> htmlEntityCode)
{
	if (!htmlEntityCode.has_value())
	{
		return;
	}

	switch (htmlEntityCode.value())
	{
	case HtmlEntityCode::Lt:
		str.push_back('<');
		break;
	case HtmlEntityCode::Gt:
		str.push_back('>');
		break;
	case HtmlEntityCode::Apos:
		str.push_back('\'');
		break;
	case HtmlEntityCode::Quot:
		str.push_back('"');
		break;
	case HtmlEntityCode::Amp:
		str.push_back('&');
		break;
	default:
		break;
	}
}

std::optional<HtmlEntityCode> ParseHtmlEntityCode(const std::string& html, size_t& pos, size_t codeStartPos)
{
	size_t codeEndPos = html.find(';', codeStartPos);
	pos = codeEndPos + 1;

	std::string codeStr = html.substr(codeStartPos + 1, codeEndPos - codeStartPos - 1);

	if (codeStr == "lt")
	{
		return HtmlEntityCode::Lt;
	}
	if (codeStr == "gt")
	{
		return HtmlEntityCode::Gt;
	}
	if (codeStr == "apos")
	{
		return HtmlEntityCode::Apos;
	}
	if (codeStr == "quot")
	{
		return HtmlEntityCode::Quot;
	}
	if (codeStr == "amp")
	{
		return HtmlEntityCode::Amp;
	}

	return std::nullopt;
}

std::string HtmlDecode(const std::string& html)
{
	std::string decodedStr;
	std::optional<HtmlEntityCode> htmlEntityCode;
	size_t pos = 0, foundPos;

	do
	{
		foundPos = html.find('&', pos);
		decodedStr.append(html, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			htmlEntityCode = ParseHtmlEntityCode(html, pos, foundPos);
			AppendDecodedHtmlEntity(decodedStr, htmlEntityCode);
		}
	} while (foundPos != std::string::npos);

	return decodedStr;
}