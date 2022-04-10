#pragma once
#include "Result.h"
#include "Variable.h"
#include "Function.h"
#include <map>

class Store
{
public:
	bool ContainsIdentifier(const std::string& identifier);

	Result DeclareFunction(const std::string& identifier, const std::string& varIdentifier);

	Result DeclareFunction(const std::string& identifier, const std::string& firstOperand, Function::Operation operation, const std::string& secondOperand);

	Result DeclareVariable(const std::string& identifier);

	Result AssignValueToVariable(const std::string& identifier, const std::string& assigningVariable);

	Result AssignValueToVariable(const std::string& identifier, double value);

	Result GetValue(const std::string& identifier, std::optional<double>& value);

	std::vector<std::pair<std::string, std::optional<double>>> GetAllFunctionsValues();

	std::vector<std::pair<std::string, std::optional<double>>> GetAllVariablesValues();

private:
	bool IsVariable(const std::string& identifier);

	bool IsFunction(const std::string& identifier);

	std::map<std::string, std::shared_ptr<Variable>> m_variablesContainer;

	std::map<std::string, std::shared_ptr<Function>> m_functionsContainer;
};
