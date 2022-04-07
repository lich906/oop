#pragma once
#include <fstream>
#include "Result.h"
#include "FunctionsContainer.h"
#include "VariablesContainer.h"

class Calculator
{
public:

	Result ProcessExpression();

private:

	enum class ExprType
	{
		Var,
		Let,
		Fn,
		Print,
		Printvars,
		Printfns
	};

	struct Expression
	{
		ExprType type;
		std::vector<std::string> identifiers;
		std::optional<double> value;
		std::optional<FunctionsContainer::Operation> operation;
	};

	Expression ParseExpression(const std::string& exprString);

	VariablesContainer m_varsContainer;
	FunctionsContainer m_fnsContainer;
	std::istream m_input;
	std::ostream m_output;
};
