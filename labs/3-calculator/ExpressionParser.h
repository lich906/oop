#pragma once
#include "Result.h"
#include <vector>
#include <optional>
#include <string>
#include <map>

class ExpressionParser
{
public:
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
		std::optional<char> operation;
	};

	Result Parse(const std::string& exprString, Expression& resExpr);

private:
	const std::map<std::string, ExprType> m_exprTypeString = {
		{ "var", ExprType::Var },
		{ "let", ExprType::Let },
		{ "fn", ExprType::Fn },
		{ "print", ExprType::Print },
		{ "printvars", ExprType::Printvars },
		{ "printfns", ExprType::Printfns }
	};

	Result ParseLet(const std::string& exprString, Expression& resExpr);

	Result ParseFn(const std::string& exprString, Expression& resExpr);

	bool IsValidIdentifier(const std::string& identifier);

	bool IsValidFloat(const std::string& str);
};
