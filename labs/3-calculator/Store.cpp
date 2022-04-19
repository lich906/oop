#include "Store.h"
#include <variant>

using namespace std;

bool Store::ContainsIdentifier(const string& identifier) const
{
	return IsVariable(identifier) || IsFunction(identifier);
}

bool Store::IsVariable(const string& identifier) const
{
	return m_variablesContainer.contains(identifier);
}

bool Store::IsFunction(const string& identifier) const
{
	return m_functionsContainer.contains(identifier);
}

Result Store::DeclareFunction(const string& identifier, const string& assigningIdentifier)
{
	if (ContainsIdentifier(identifier))
	{
		return { ResultStatus::Error, "Identifier '" + identifier + "' has been already declared." };
	}

	if (IsVariable(assigningIdentifier))
	{
		m_functionsContainer[identifier] = make_unique<Function>(m_variablesContainer[assigningIdentifier].get());
	}
	else if (IsFunction(assigningIdentifier))
	{
		m_functionsContainer[identifier] = make_unique<Function>(m_functionsContainer[assigningIdentifier].get());
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + assigningIdentifier + "'." };
	}

	return { ResultStatus::OK };
}

Result Store::DeclareFunction(const string& identifier, const string& firstIdentifier, Function::Operation operation, const string& secondIdentifier)
{
	if (ContainsIdentifier(identifier))
	{
		return { ResultStatus::Error, "Identifier '" + identifier + "' has been already declared." };
	}

	Operand* firstOperandPtr;
	if (IsVariable(firstIdentifier))
	{
		firstOperandPtr = m_variablesContainer.at(firstIdentifier).get();
	}
	else if (IsFunction(firstIdentifier))
	{
		firstOperandPtr = m_functionsContainer.at(firstIdentifier).get();
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + firstIdentifier + "'." };
	}

	Operand* secondOperandPtr;
	if (IsVariable(secondIdentifier))
	{
		secondOperandPtr = m_variablesContainer.at(secondIdentifier).get();
	}
	else if (IsFunction(secondIdentifier))
	{
		secondOperandPtr = m_functionsContainer.at(secondIdentifier).get();
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + secondIdentifier + "'." };
	}

	m_functionsContainer[identifier] = make_unique<Function>(firstOperandPtr, operation, secondOperandPtr);

	return { ResultStatus::OK };
}

Result Store::DeclareVariable(const string& identifier)
{
	if (ContainsIdentifier(identifier))
	{
		return { ResultStatus::Error, "Identifier '" + identifier + "' has been already declared." };
	}

	m_variablesContainer[identifier] = make_unique<Variable>(nan(""));

	return { ResultStatus::OK };
}

Result Store::AssignValueToVariable(const string& identifier, const string& assigningIdentifier)
{
	if (IsFunction(identifier))
	{
		return { ResultStatus::Error, "'" + identifier + "' is a function." };
	}

	double assigningValue;
	if (IsVariable(assigningIdentifier))
	{
		assigningValue = m_variablesContainer.at(assigningIdentifier)->GetValue();
	}
	else if (IsFunction(assigningIdentifier))
	{
		assigningValue = m_functionsContainer.at(assigningIdentifier)->GetValue();
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + assigningIdentifier + "'." };
	}

	if (!IsVariable(identifier))
	{
		m_variablesContainer[identifier] = make_unique<Variable>(assigningValue);
	}
	else
	{
		m_variablesContainer.at(identifier)->SetValue(assigningValue);
	}

	return { ResultStatus::OK };
}

Result Store::AssignValueToVariable(const string& identifier, double value)
{
	if (IsFunction(identifier))
	{
		return { ResultStatus::Error, "'" + identifier + "' is a function." };
	}

	if (IsVariable(identifier))
	{
		m_variablesContainer.at(identifier)->SetValue(value);
	}
	else
	{
		m_variablesContainer[identifier] = make_unique<Variable>(value);
	}

	return { ResultStatus::OK };
}

Result Store::GetValue(const string& identifier, double& value) const
{
	if (IsFunction(identifier))
	{
		value = m_functionsContainer.at(identifier)->GetValue();
	}
	else if (IsVariable(identifier))
	{
		value = m_variablesContainer.at(identifier)->GetValue();
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + identifier + "'." };
	}

	return { ResultStatus::OK };
}

Store::IdentifierValueVector Store::GetAllFunctionsValues() const
{
	vector<pair<string, double>> allFunctionsValues;

	for (const auto& [identifier, functionPtr] : m_functionsContainer)
	{
		allFunctionsValues.push_back({ identifier, functionPtr->GetValue() });
	}

	return allFunctionsValues;
}

Store::IdentifierValueVector Store::GetAllVariablesValues() const
{
	vector<pair<string, double>> allVariablesValues;

	for (const auto& [identifier, variablePtr] : m_variablesContainer)
	{
		allVariablesValues.push_back({ identifier, variablePtr->GetValue() });
	}

	return allVariablesValues;
}
