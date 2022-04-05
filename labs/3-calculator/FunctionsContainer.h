#pragma once
#include <optional>
#include <vector>
#include <map>
#include "Result.h"

class FunctionsContainer
{
public:

	enum class Operation
	{
		Add,
		Sub,
		Mul,
		Div
	};

	bool ContainsIdentifier(const std::string& identifier);

	Result DeclareNew(const std::string& identifier, const std::string& varIdentifier);

	Result DeclareNew(const std::string& identifier, const std::string& firstOperand, Operation operation, const std::string& secondOperand);

	Result CalcFunction(std::string identifier, std::optional<double>& result);

	std::vector<std::pair<std::string, std::optional<double>>> GetAllFunctionsValues();

private:
	
	struct FunctionBody
	{
		std::string firstOperandIdentifier;
		std::optional<Operation> operation;
		std::optional<std::string> secondOperandIdentifier;
	};

	std::map<std::string, FunctionBody> m_functions;
};
