#include "UrlParsingError.h"

UrlParsingError::UrlParsingError(const std::string& msg)
	: std::invalid_argument(msg)
{
}

UrlParsingError::UrlParsingError(const char* msg)
	: std::invalid_argument(msg)
{
}
