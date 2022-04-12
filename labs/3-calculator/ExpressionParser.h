#pragma once
#include "Result.h"
#include <vector>
#include <optional>
#include <string>
#include <map>

class ExpressionParser
{
public:
	enum class CommandType
	{
		DeclareVariable,
		AssignVariable,
		DeclareFunction,
		PrintValue,
		PrintAllVariables,
		PrintAllFunctions
	};

	struct CommandData
	{
		CommandType type;
		std::vector<std::string> identifiers;
		std::optional<double> value;
		std::optional<char> operation;
	};

	Result Parse(const std::string& rawString, CommandData& parsedData) const;

private:
	const std::map<std::string, CommandType> m_commandTypeString = {
		{ "var", CommandType::DeclareVariable },
		{ "let", CommandType::AssignVariable },
		{ "fn", CommandType::DeclareFunction },
		{ "print", CommandType::PrintValue },
		{ "printvars", CommandType::PrintAllVariables },
		{ "printfns", CommandType::PrintAllFunctions }
	};

	Result ParseVariableAssignment(const std::string& rawString, CommandData& parsedData) const;

	Result ParseFunctionDeclaration(const std::string& rawString, CommandData& parsedData) const;

	bool IsValidIdentifier(const std::string& identifier) const;

	bool IsValidFloat(const std::string& str) const;
};
