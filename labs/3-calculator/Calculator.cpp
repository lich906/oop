#include "Calculator.h"

#include <sstream>

void Calculator::Interpret(std::istream& input, std::ostream& output)
{
	output << promptChar;

	std::string exprString;
	std::getline(input, exprString);

	if (exprString.empty())
	{
		return;
	}

	Result result;
	ExpressionParser::CommandData expression;
	if ((result = m_parser.Parse(exprString, expression)).status != ResultStatus::OK)
	{
		output << result.reportMessage << std::endl;
		return;
	}

	result = DelegateCommandExecution(expression);

	if (!result.reportMessage.empty())
	{
		output << result.reportMessage << std::endl;
	}
}

Result Calculator::DelegateCommandExecution(const ExpressionParser::CommandData& commandData)
{
	Result execResult;
	std::optional<double> value;
	std::ostringstream reportString;
	Store::IdentifierValueVector allValues;
	switch (commandData.type)
	{
	case ExpressionParser::CommandType::PrintValue:
		return ExecutePrintCommand(commandData);

	case ExpressionParser::CommandType::PrintAllVariables:
		allValues = m_store.GetAllVariablesValues();
		return ExecutePrintAllCommand(allValues);

	case ExpressionParser::CommandType::PrintAllFunctions:
		allValues = m_store.GetAllFunctionsValues();
		return ExecutePrintAllCommand(allValues);

	case ExpressionParser::CommandType::DeclareVariable:
		return m_store.DeclareVariable(commandData.identifiers[0]);

	case ExpressionParser::CommandType::AssignVariable:
		if (commandData.value.has_value())
		{
			return m_store.AssignValueToVariable(commandData.identifiers[0], *commandData.value);
		}
		else
		{
			return m_store.AssignValueToVariable(commandData.identifiers[0], commandData.identifiers[1]);
		}

	case ExpressionParser::CommandType::DeclareFunction:
		return ExecuteFunctionDeclaration(commandData);

	default:
		return { ResultStatus::Error, "Internal error: unknown command type recieved." };
	}
}

Result Calculator::ExecutePrintCommand(const ExpressionParser::CommandData& commandData)
{
	Result result;
	std::ostringstream outputStream;
	double value;

	if ((result = m_store.GetValue(commandData.identifiers[0], value)).status != ResultStatus::OK)
	{
		return result;
	}

	if (!isnan(value))
	{
		outputStream << value;
	}
	else
	{
		outputStream << nanPrintValue;
	}

	return { ResultStatus::OK, outputStream.str() };
}

Result Calculator::ExecutePrintAllCommand(const Store::IdentifierValueVector& identifierValues)
{
	std::ostringstream outputStream;
	if (identifierValues.empty())
	{
		outputStream << "There is nothing to print.";
	}
	else
	{
		for (const auto& [identifier, value] : identifierValues)
		{
			outputStream << identifier << " : ";
			if (!isnan(value))
			{
				outputStream << value;
			}
			else
			{
				outputStream << nanPrintValue;
			}
			outputStream << std::endl;
		}
	}

	return { ResultStatus::OK, outputStream.str() };
}

Result Calculator::ExecuteFunctionDeclaration(const ExpressionParser::CommandData& commandData)
{
	if (commandData.operation.has_value())
	{
		Function::Operation operation;
		switch (*commandData.operation)
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
		return m_store.DeclareFunction(commandData.identifiers[0], commandData.identifiers[1], operation, commandData.identifiers[2]);
	}
	else
	{
		return m_store.DeclareFunction(commandData.identifiers[0], commandData.identifiers[1]);
	}
}
