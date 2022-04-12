#include "ExpressionParser.h"
#include <sstream>
#include <regex>

Result ExpressionParser::Parse(const std::string& rawString, CommandData& parsedData) const
{
	std::optional<CommandType> commandType;
	
	size_t commandSpaceDelimPos = rawString.find(' ');

	std::string commandTypeStr = rawString.substr(0, commandSpaceDelimPos);
	for (const auto& [cmdStr, cmdType] : m_commandTypeString)
	{
		if (commandTypeStr == cmdStr)
		{
			commandType = cmdType;
			break;
		}
	}

	if (!commandType.has_value())
	{
		return { ResultStatus::Error, "Unknown command type '" + commandTypeStr + "'." };
	}

	std::string restExprString =
		(commandSpaceDelimPos != std::string::npos) ?
		rawString.substr(commandSpaceDelimPos + 1) :
		"";

	switch (*commandType)
	{
	case CommandType::DeclareVariable:
	case CommandType::PrintValue:
		if (!IsValidIdentifier(restExprString))
		{
			return { ResultStatus::Error, "Parsing error: Invalid identifier '" + restExprString + "'." };
		}
		parsedData = { *commandType, { restExprString } };
		break;

	case CommandType::AssignVariable:
		return ParseVariableAssignment(restExprString, parsedData);

	case CommandType::DeclareFunction:
		return ParseFunctionDeclaration(restExprString, parsedData);

	case CommandType::PrintAllVariables:
	case CommandType::PrintAllFunctions:
		parsedData = { *commandType };

	default:
		break;
	}

	return { ResultStatus::OK };
}

Result ExpressionParser::ParseVariableAssignment(const std::string& exprString, CommandData& parsedData) const
{
	size_t equalityCharPos = exprString.find('=');

	if (equalityCharPos == std::string::npos)
	{
		return { ResultStatus::Error, "Failed to parse assignment '" + exprString + "'." };
	}

	std::string destIdentifier = exprString.substr(0, equalityCharPos);

	if (!IsValidIdentifier(destIdentifier))
	{
		return { ResultStatus::Error, "Parsing error: Invalid identifier '" + destIdentifier + "'." };
	}

	std::string rightPart = exprString.substr(equalityCharPos + 1);

	if (IsValidIdentifier(rightPart))
	{
		parsedData = { CommandType::AssignVariable, { destIdentifier, rightPart } };
	}
	else if (IsValidFloat(rightPart))
	{
		double value;
		try
		{
			value = std::stod(rightPart);
		}
		catch (std::out_of_range&)
		{
			return { ResultStatus::Error, "Error: Assigning value is too big" };
		}
		parsedData = { CommandType::AssignVariable, { destIdentifier }, { value } };
	}
	else
	{
		return { ResultStatus::Error, "Failed to parse '" + rightPart + "' expression." };
	}

	return { ResultStatus::OK };
}

Result ExpressionParser::ParseFunctionDeclaration(const std::string& exprString, CommandData& parsedData) const
{
	size_t equalityCharPos = exprString.find('=');
	if (equalityCharPos == std::string::npos)
	{
		return { ResultStatus::Error, "Failed to parse expression '" + exprString + "' no assignment found." };
	}

	std::string fnIdentifier = exprString.substr(0, equalityCharPos);

	if (!IsValidIdentifier(fnIdentifier))
	{
		return { ResultStatus::Error, "Parsing error: Invalid identifier '" + fnIdentifier + "'." };
	}

	std::string rightPart = exprString.substr(equalityCharPos + 1);

	size_t opChPos;
	for (char opCh : { '+', '-', '*', '/' })
	{
		if ((opChPos = rightPart.find(opCh)) != std::string::npos)
		{
			std::string firstOperandId = rightPart.substr(0, opChPos);
			std::string secondOperandId = rightPart.substr(opChPos + 1);
			if (!IsValidIdentifier(firstOperandId))
			{
				return { ResultStatus::Error, "Parsing error: Invalid identifier '" + firstOperandId + "'." };
			}

			if (!IsValidIdentifier(secondOperandId))
			{
				return { ResultStatus::Error, "Parsing error: Invalid identifier '" + secondOperandId + "'." };
			}

			parsedData = { CommandType::DeclareFunction, { fnIdentifier, firstOperandId, secondOperandId }, {}, opCh };

			return { ResultStatus::OK };
		}
	}

	if (!IsValidIdentifier(rightPart))
	{
		return { ResultStatus::Error, "Parsing error: Invalid identifier '" + rightPart + "'." };
	}

	parsedData = { CommandType::DeclareFunction, { fnIdentifier, rightPart } };

	return { ResultStatus::OK };
}



bool ExpressionParser::IsValidIdentifier(const std::string& identifier) const
{
	std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");

	return std::regex_match(identifier, identifierRegex);
}

bool ExpressionParser::IsValidFloat(const std::string& str) const
{
	std::regex floatRegex("[+-]?([0-9]*[.])?[0-9]+");

	return std::regex_match(str, floatRegex);
}
