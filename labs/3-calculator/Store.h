#pragma once
#include "Result.h"
#include "Function.h"
#include <map>

class Store
{
public:
	using IdentifierValueVector = std::vector<std::pair<std::string, double>>;

	bool ContainsIdentifier(const std::string& identifier) const;

	Result DeclareFunction(const std::string& identifier, const std::string& assigningIdentifier);

	Result DeclareFunction(const std::string& identifier, const std::string& firstOperand, Function::Operation operation, const std::string& secondOperand);

	Result DeclareVariable(const std::string& identifier);

	Result AssignValueToVariable(const std::string& identifier, const std::string& assigningVariable);

	Result AssignValueToVariable(const std::string& identifier, double value);

	Result GetValue(const std::string& identifier, double& value) const;

	IdentifierValueVector GetAllFunctionsValues() const;

	IdentifierValueVector GetAllVariablesValues() const;

private:
	bool IsVariable(const std::string& identifier) const;

	bool IsFunction(const std::string& identifier) const;

	std::map<std::string, std::unique_ptr<Variable>> m_variablesContainer;

	std::map<std::string, std::unique_ptr<Function>> m_functionsContainer;
};
