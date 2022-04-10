#include "ExpressionParser.h"
#include <sstream>
#include <regex>

Result ExpressionParser::Parse(const std::string& exprString, Expression& resExpr)
{
	std::optional<ExprType> expressionType;
	
	size_t commandSpaceDelimPos = exprString.find(' ');

	std::string exprTypeStr = exprString.substr(0, commandSpaceDelimPos);
	for (const auto& [str, exprType] : m_exprTypeString)
	{
		if (exprTypeStr == str)
		{
			expressionType = exprType;
			break;
		}
	}

	if (!expressionType.has_value())
	{
		return { ResultStatus::Error, "Unknown command type." };
	}

	std::string restExprString = exprString.substr(commandSpaceDelimPos + 1);

	std::string identifier;
	switch (*expressionType)
	{
	case ExprType::Var:
	case ExprType::Print:
		resExpr = { *expressionType, { restExprString } };
		break;
	case ExprType::Let:
		return ParseLet(restExprString, resExpr);
	case ExprType::Fn:
		return ParseFn(restExprString, resExpr);
	case ExprType::Printvars:
	case ExprType::Printfns:
		resExpr = { *expressionType };
	default:
		break;
	}

	return { ResultStatus::OK };
}

Result ExpressionParser::ParseLet(const std::string& exprString, Expression& resExpr)
{
	size_t equalityCharPos = exprString.find('=');

	if (equalityCharPos == std::string::npos)
	{
		return { ResultStatus::Error, "Failed to parse assignment '" + exprString + "'." };
	}

	std::string destIdentifier = exprString.substr(0, equalityCharPos);

	std::string rightPart = exprString.substr(equalityCharPos + 1);

	if (IsValidIdentifier(rightPart))
	{
		resExpr = { ExprType::Let, { destIdentifier, rightPart } };
	}
	else if (IsValidFloat(rightPart))
	{
		double value = std::stod(rightPart);
		resExpr = { ExprType::Let, { destIdentifier }, { value } };
	}
	else
	{
		return { ResultStatus::Error, "Failed to parse '" + rightPart + "' expression." };
	}

	return { ResultStatus::OK };
}

Result ExpressionParser::ParseFn(const std::string& exprString, Expression& resExpr)
{
	size_t equalityCharPos = exprString.find('=');
	if (equalityCharPos == std::string::npos)
	{
		return { ResultStatus::Error, "Failed to parse expression '" + exprString + "' no assignment found." };
	}

	std::string fnIdentifier = exprString.substr(0, equalityCharPos);
	std::string rightPart = exprString.substr(equalityCharPos + 1);

	size_t opChPos;
	std::string firstOperandId, secondOperandId;
	for (char opCh : { '+', '-', '*', '/' })
	{
		if ((opChPos = exprString.find(opCh)) != std::string::npos)
		{
			firstOperandId = exprString.substr(0, opChPos);
			secondOperandId = exprString.substr(opChPos + 1);
			if (!IsValidIdentifier(firstOperandId))
			{
				return { ResultStatus::Error, "Parsing error: Invalid identifier '" + firstOperandId + "'." };
			}

			if (!IsValidIdentifier(secondOperandId))
			{
				return { ResultStatus::Error, "Parsing error: Invalid identifier '" + secondOperandId + "'." };
			}

			resExpr = { ExprType::Fn, { fnIdentifier, firstOperandId, secondOperandId }, {}, opCh };

			return { ResultStatus::OK };
		}
	}

	if (!IsValidIdentifier(rightPart))
	{
		return { ResultStatus::Error, "Parsing error: Invalid identifier '" + rightPart + "'." };
	}

	resExpr = { ExprType::Fn, { fnIdentifier } };

	return { ResultStatus::OK };
}



bool ExpressionParser::IsValidIdentifier(const std::string& identifier)
{
	std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");

	return std::regex_match(identifier, identifierRegex);
}

bool ExpressionParser::IsValidFloat(const std::string& str)
{
	std::regex floatRegex("[+-]?([0-9]*[.])?[0-9]+");

	return std::regex_match(str, floatRegex);
}
