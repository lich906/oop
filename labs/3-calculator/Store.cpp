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
		m_functionsContainer[identifier] = make_shared<Function>(m_variablesContainer[assigningIdentifier].get());
	}
	else if (IsFunction(assigningIdentifier))
	{
		m_functionsContainer[identifier] = make_shared<Function>(m_functionsContainer[assigningIdentifier].get());
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
		firstOperandPtr = m_variablesContainer[firstIdentifier].get();
	}
	else if (IsFunction(firstIdentifier))
	{
		firstOperandPtr = m_functionsContainer[firstIdentifier].get();
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + firstIdentifier + "'." };
	}

	Operand* secondOperandPtr;
	if (IsVariable(secondIdentifier))
	{
		secondOperandPtr = m_variablesContainer[secondIdentifier].get();
	}
	else if (IsFunction(secondIdentifier))
	{
		secondOperandPtr = m_functionsContainer[secondIdentifier].get();
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + secondIdentifier + "'." };
	}

	m_functionsContainer[identifier] = make_shared<Function>(firstOperandPtr, operation, secondOperandPtr);

	return { ResultStatus::OK };
}

Result Store::DeclareVariable(const string& identifier)
{
	if (ContainsIdentifier(identifier))
	{
		return { ResultStatus::Error, "Identifier \'" + identifier + "\' has been already declared." };
	}

	m_variablesContainer[identifier] = make_shared<Variable>();

	return { ResultStatus::OK };
}

Result Store::AssignValueToVariable(const string& identifier, const string& assigningIdentifier)
{
	if (IsFunction(identifier))
	{
		return { ResultStatus::Error, "'" + assigningIdentifier + "' is a function." };
	}

	optional<double> assigningValue;
	if (IsVariable(assigningIdentifier))
	{
		assigningValue = m_variablesContainer[assigningIdentifier]->GetValue();
	}
	else if (IsFunction(assigningIdentifier))
	{
		assigningValue = m_functionsContainer[assigningIdentifier]->GetValue();
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + assigningIdentifier + "'." };
	}

	if (!IsVariable(identifier))
	{
		m_variablesContainer[identifier] = make_shared<Variable>(assigningValue);
	}
	else
	{
		m_variablesContainer[identifier]->SetValue(assigningValue);
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
		m_variablesContainer[identifier]->SetValue(optional<double>(value));
	}
	else
	{
		m_variablesContainer[identifier] = make_shared<Variable>(optional<double>(value));
	}

	return { ResultStatus::OK };
}

Result Store::GetValue(const string& identifier, optional<double>& value)
{
	if (IsFunction(identifier))
	{
		value = m_functionsContainer[identifier]->GetValue();
	}
	else if (IsVariable(identifier))
	{
		value = m_variablesContainer[identifier]->GetValue();
	}
	else
	{
		return { ResultStatus::Error, "Unknown identifier '" + identifier + "'." };
	}

	return { ResultStatus::OK };
}

Store::IdentifierValueVector Store::GetAllFunctionsValues()
{
	vector<pair<string, optional<double>>> allFunctionsValues;

	for (const auto& [identifier, functionPtr] : m_functionsContainer)
	{
		allFunctionsValues.push_back({ identifier, functionPtr->GetValue() });
	}

	return allFunctionsValues;
}

Store::IdentifierValueVector Store::GetAllVariablesValues()
{
	vector<pair<string, optional<double>>> allVariablesValues;

	for (const auto& [identifier, variablePtr] : m_variablesContainer)
	{
		allVariablesValues.push_back({ identifier, variablePtr->GetValue() });
	}

	return allVariablesValues;
}
