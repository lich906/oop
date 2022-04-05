#pragma once
#include <string>

enum class ResultStatus
{
	Success,
	Error
};

struct Result
{
	ResultStatus status;
	std::string reportMessage;
};