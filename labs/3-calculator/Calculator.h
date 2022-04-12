#pragma once
#include "ExpressionParser.h"
#include "Store.h"
#include <fstream>

class Calculator
{
public:
	void Interpret(std::istream& input, std::ostream& output);

private:
	const std::string nanPrintValue = "NaN";
	const char promptChar = '>';

	Result DelegateCommandExecution(const ExpressionParser::CommandData& expr);

	Result ExecutePrintCommand(const ExpressionParser::CommandData& commandData);

	Result ExecutePrintAllCommand(const Store::IdentifierValueVector& identifierValues);

	Result ExecuteFunctionDeclaration(const ExpressionParser::CommandData& commandData);

	ExpressionParser m_parser;

	Store m_store;
};
