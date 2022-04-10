#pragma once
#include "ExpressionParser.h"
#include "Store.h"
#include <fstream>

class Calculator
{
public:
	void Interpret(std::istream& input, std::ostream& output);

private:
	Result Execute(const ExpressionParser::Expression& expr);

	ExpressionParser m_parser;

	Store m_store;
};
