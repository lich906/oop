#pragma once
#include <string>

enum class ResultStatus
{
	OK,
	Error
};

struct Result
{
	ResultStatus status;
	std::string reportMessage;
};