#pragma once
#include <optional>
#include <vector>
#include <map>
#include "Result.h"

class VariablesContainer
{
public:

	bool ContainsIdentifier(const std::string& identifier);

	Result SetValue(const std::string& identifier, double value);

	Result DeclareNew(const std::string& identifier);

	Result GetValue(const std::string& identifier, std::optional<double>& value);

	std::vector<std::pair<std::string, std::optional<double>>> GetAllVariablesValues();

private:

	std::map<std::string, std::optional<double>> m_variables;
};
