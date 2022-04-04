#include "CommandInterpreter.h"

//TODO: переместить сюда m_mapStringToCommandType
CommandInterpreter::Result CommandInterpreter::Interpret()
{
	std::string buf;
	std::getline(m_input, buf);

	ParseResult parseResult;
	if ((parseResult = Parse(buf)).status != Status::OK)
	{
		return { parseResult.status, parseResult.reportMessage };
	}

	Result execResult;
	if ((execResult = Execute(parseResult.command)).status != Status::OK)
	{
		return { execResult.status, execResult.reportMessage };
	}

	return (m_input.eof() || !m_input) ?
		Result{ Status::Exit } : Result{ Status::OK };
}

//TODO: возвращать структуру комманды Command + структуру ParseResult или слить их вместе
CommandInterpreter::ParseResult CommandInterpreter::Parse(const std::string& rawExpression)
{
	if (rawExpression.empty())
	{
		return { Status::OK };
	}

	size_t spacePos = rawExpression.find(' ');
	std::string commandString = rawExpression.substr(0, rawExpression.find(' '));

	if (!m_mapStringToCommandType.contains(commandString))
	{
		return {
			Status::ParsingError,
			std::nullopt,
			"Parsing error: unknown command"
		};
	}

	CommandType type = m_mapStringToCommandType.at(commandString);
	std::optional<int> arg;

	if (type == CommandType::SetGear || type == CommandType::SetSpeed)
	{
		try
		{
			arg = std::stoi(rawExpression.substr(spacePos + 1));
		}
		catch (...)
		{
			return {
				Status::ParsingError,
				std::nullopt,
				"Parsing error: invalid command argument"
			};
		}
	}

	return {
		Status::OK,
		Command{
			type,
			arg
		}
	};
}

CommandInterpreter::Result CommandInterpreter::Execute(std::optional<Command> command)
{
	if (!command.has_value())
	{
		return { Status::OK };
	}

	bool noError;
	switch (command->type)
	{
	case CommandType::NoCommand:
		return { Status::OK };

	case CommandType::Info:
		PrintCarInfo();
		return { Status::OK };

	case CommandType::Exit:
		return { Status::Exit };

	case CommandType::EngineOn:
		noError = m_car.TurnOnEngine();
		break;

	case CommandType::EngineOff:
		noError = m_car.TurnOffEngine();
		break;

	case CommandType::SetGear:
		noError = m_car.SetGear(*(command->arg));
		break;

	case CommandType::SetSpeed:
		noError = m_car.SetSpeed(*(command->arg));
		break;

	default:
		return {
			Status::ExecutionError,
			"Internal error: Executing command with invalid command type."
		};
	}

	if (noError)
	{
		return { Status::OK };
	}

	return {
		Status::ExecutionError,
		m_car.GetLastErrorMessage()
	};
}

void CommandInterpreter::PrintCarInfo()
{
	int direction = m_car.GetDirection();
	int gear = m_car.GetGear();

	m_output
		<< "Engine: " << (m_car.IsTurnedOn() ? "On" : "Off") << std::endl
		<< "Direction: " << (direction >= 0 ? direction == 0 ? "Immobile" : "Forward" : "Backwards") << std::endl
		<< "Speed: " << m_car.GetSpeed() << std::endl
		<< "Gear: " << (gear < 0 ? "R" : gear == 0 ? "N" : std::to_string(gear)) << std::endl;
}
