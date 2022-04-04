#pragma once
#include "Car.h"
#include <optional>
#include <fstream>
#include <map>

class CommandInterpreter
{
public:
	CommandInterpreter(Car& car, std::istream& in, std::ostream& out)
		: m_car(car)
		, m_input(in)
		, m_output(out)
	{
	}

	enum class Status
	{
		OK,
		ParsingError,
		ExecutionError,
		Exit
	};

	struct Result
	{
		Status status;
		std::optional<std::string> reportMessage;
	};

	Result Interpret();

private:
	enum class CommandType
	{
		Info,
		EngineOn,
		EngineOff,
		SetGear,
		SetSpeed,
		Exit,
		NoCommand
	};

	const std::map<std::string, CommandType> m_mapStringToCommandType = {
		{ "Info", CommandType::Info },
		{ "EngineOn", CommandType::EngineOn },
		{ "EngineOff", CommandType::EngineOff },
		{ "SetGear", CommandType::SetGear },
		{ "SetSpeed", CommandType::SetSpeed },
		{ "Exit", CommandType::Exit }
	};

	struct Command
	{
		CommandType type;
		std::optional<int> arg;
	};

	struct ParseResult
	{
		Status status;
		std::optional<Command> command;
		std::optional<std::string> reportMessage;
	};

	ParseResult Parse(const std::string& rawExpression);

	Result Execute(std::optional<Command> command);

	void PrintCarInfo();

	std::istream& m_input;
	std::ostream& m_output;
	Car& m_car;
};
