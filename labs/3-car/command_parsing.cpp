#include "command_parsing.h"
#include <map>

std::map<std::string, CommandType> mapStringToCommandType = {
	{ "Info", CommandType::Info },
	{ "EngineOn", CommandType::EngineOn },
	{ "EngineOff", CommandType::EngineOff },
	{ "SetGear", CommandType::SetGear },
	{ "SetSpeed", CommandType::SetSpeed }
};

std::optional<Command> ParseCommand(const std::string& rawExpression)
{
	size_t spacePos = rawExpression.find(' ');
	std::string commandString = rawExpression.substr(0, rawExpression.find(' '));

	if (!mapStringToCommandType.contains(commandString))
	{
		return std::nullopt;
	}

	CommandType type = mapStringToCommandType[commandString];

	if (type == CommandType::SetGear || type == CommandType::SetSpeed)
	{
		int value;
		try
		{
			value = std::stoi(rawExpression.substr(spacePos + 1));
		}
		catch (...)
		{
			return std::nullopt;
		}

		return Command{ type, value };
	}

	return Command{ type };
}