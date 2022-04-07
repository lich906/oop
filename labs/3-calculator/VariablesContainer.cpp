#include "VariablesContainer.h"

bool VariablesContainer::ContainsIdentifier(const std::string& identifier)
{
	return m_variables.contains(identifier);
}

Result VariablesContainer::SetValue(const std::string& identifier, double value)
{
	return Result();
}

Result VariablesContainer::DeclareNew(const std::string& identifier)
{
	if (ContainsIdentifier(identifier))
	{
		return { ResultStatus::Error, "Variable \'" + identifier + "\' already declared." };
	}

	m_variables[identifier] = std::optional<double>{};

	return { ResultStatus::OK };
}

Result VariablesContainer::GetValue(const std::string& identifier, std::optional<double>& value)
{
	return Result();
}

std::vector<std::pair<std::string, std::optional<double>>> VariablesContainer::GetAllVariablesValues()
{
	return std::vector<std::pair<std::string, std::optional<double>>>();
}
