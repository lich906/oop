#include "Calculator.h"

#include <sstream>

void Calculator::Interpret(std::istream& input, std::ostream& output)
{
	std::string exprString;
	std::getline(input, exprString);

	Result result;
	ExpressionParser::Expression expression;
	if ((result = m_parser.Parse(exprString, expression)).status != ResultStatus::OK)
	{
		output << result.reportMessage << std::endl;
		return;
	}

	result = Execute(expression);

	if (!result.reportMessage.empty())
	{
		output << result.reportMessage << std::endl;
	}
}

Result Calculator::Execute(const ExpressionParser::Expression& expression)
{
	Result execResult;
	std::optional<double> value;
	std::ostringstream reportString;
	std::vector<std::pair<std::string, std::optional<double>>> allValues;
	switch (expression.type)
	{
	case ExpressionParser::ExprType::Print:
		if ((execResult = m_store.GetValue(expression.identifiers[0], value)).status != ResultStatus::OK)
		{
			return execResult;
		}
		if (value.has_value())
		{
			reportString << *value;
		}
		else
		{
			reportString << "NaN";
		}
		return { ResultStatus::OK, reportString.str() };

	case ExpressionParser::ExprType::Printvars:
		allValues = m_store.GetAllVariablesValues();
		if (allValues.empty())
		{
			reportString << "There is no variables.";
		}
		else
		{
			for (const auto& [identifier, value] : allValues)
			{
				reportString << identifier << " : ";
				if (value.has_value())
				{
					reportString << *value;
				}
				else
				{
					reportString << "NaN";
				}
				reportString << std::endl;
			}
		}
		return { ResultStatus::OK, reportString.str() };

	case ExpressionParser::ExprType::Printfns:
		allValues = m_store.GetAllFunctionsValues();
		if (allValues.empty())
		{
			reportString << "There is no functions.";
		}
		else
		{
			for (const auto& [identifier, value] : allValues)
			{
				reportString << identifier << " : ";
				if (value.has_value())
				{
					reportString << *value;
				}
				else
				{
					reportString << "NaN";
				}
				reportString << std::endl;
			}
		}
		return { ResultStatus::OK, reportString.str() };

	case ExpressionParser::ExprType::Var:
		return m_store.DeclareVariable(expression.identifiers[0]);

	case ExpressionParser::ExprType::Let:
		if (expression.value.has_value())
		{
			return m_store.AssignValueToVariable(expression.identifiers[0], *expression.value);
		}
		else
		{
			return m_store.AssignValueToVariable(expression.identifiers[0], expression.identifiers[1]);
		}

	case ExpressionParser::ExprType::Fn:
		if (expression.operation.has_value())
		{
			Function::Operation operation;
			switch (*expression.operation)
			{
				case '+':
					operation = Function::Operation::Add;
					break;
				case '-':
					operation = Function::Operation::Sub;
					break;
				case '*':
					operation = Function::Operation::Mul;
					break;
				case '/':
					operation = Function::Operation::Div;
					break;
				default:
					return { ResultStatus::Error, "Internal error: unknown function operation recieved." };
			}
			return m_store.DeclareFunction(expression.identifiers[0], expression.identifiers[1], operation, expression.identifiers[2]);
		}
		else
		{
			return m_store.DeclareFunction(expression.identifiers[0], expression.identifiers[1]);
		}

	default:
		return { ResultStatus::Error, "Internal error: unknown command type recieved." };
	}
}
