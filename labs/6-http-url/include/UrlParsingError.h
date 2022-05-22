#pragma once
#include <stdexcept>

class UrlParsingError : public std::invalid_argument
{
public:
	UrlParsingError(const std::string& msg);

	UrlParsingError(const char* msg);
};
