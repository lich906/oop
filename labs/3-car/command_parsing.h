#pragma once
#include <string>
#include <optional>

enum class CommandType
{
	Info,
	EngineOn,
	EngineOff,
	SetGear,
	SetSpeed,
	Exit
};

struct Command
{
	CommandType type;
	int arg;
};

std::optional<Command> ParseCommand(const std::string& rawExpression);
