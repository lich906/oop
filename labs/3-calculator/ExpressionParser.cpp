#include "ExpressionParser.h"
#include <sstream>
#include <regex>

Result ExpressionParser::Parse(const std::string& exprString, Expression& resExpr) const
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
		return { ResultStatus::Error, "Unknown command type '" + exprTypeStr + "'." };
	}

	std::string restExprString =
		(commandSpaceDelimPos != std::string::npos) ?
		exprString.substr(commandSpaceDelimPos + 1) :
		"";

	switch (*expressionType)
	{
	case ExprType::Var:
	case ExprType::Print:
		if (!IsValidIdentifier(restExprString))
		{
			return { ResultStatus::Error, "Parsing error: Invalid identifier '" + restExprString + "'." };
		}
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

Result ExpressionParser::ParseLet(const std::string& exprString, Expression& resExpr) const
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
		resExpr = { ExprType::Let, { destIdentifier, rightPart } };
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
		resExpr = { ExprType::Let, { destIdentifier }, { value } };
	}
	else
	{
		return { ResultStatus::Error, "Failed to parse '" + rightPart + "' expression." };
	}

	return { ResultStatus::OK };
}

Result ExpressionParser::ParseFn(const std::string& exprString, Expression& resExpr) const
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
	std::string firstOperandId, secondOperandId;
	for (char opCh : { '+', '-', '*', '/' })
	{
		if ((opChPos = rightPart.find(opCh)) != std::string::npos)
		{
			firstOperandId = rightPart.substr(0, opChPos);
			secondOperandId = rightPart.substr(opChPos + 1);
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

	resExpr = { ExprType::Fn, { fnIdentifier, rightPart } };

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
