#include "Calculator.h"

Result Calculator::ProcessExpression()
{
	std::string exprString;
	std::getline(m_input, exprString);

	Calculator::Expression expr = ParseExpression(exprString);

	return Result();
}

Calculator::Expression Calculator::ParseExpression(const std::string& exprString)
{
	return Expression();
}
