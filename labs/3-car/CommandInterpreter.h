#pragma once
#include "Car.h"
#include <optional>
#include <string>
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

	Status Interpret();

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

	Status Parse(const std::string& rawExpression);

	Status Execute();

	void PrintCarInfo();

	std::istream& m_input;
	std::ostream& m_output;
	Car& m_car;
	CommandType m_commandType = CommandType::NoCommand;
	std::optional<int> m_arg;
};
