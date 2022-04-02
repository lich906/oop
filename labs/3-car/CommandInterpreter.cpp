#include "CommandInterpreter.h"

CommandInterpreter::Status CommandInterpreter::Interpret()
{
	std::string buf;
	std::getline(m_input, buf);

	Status status;
	if ((status = Parse(buf)) != Status::OK)
	{
		return status;
	}

	if ((status = Execute()) != Status::OK)
	{
		return status;
	}

	return (m_input.eof() || !m_input) ? Status::Exit : Status::OK;
}

CommandInterpreter::Status CommandInterpreter::Parse(const std::string& rawExpression)
{
	if (rawExpression.empty())
	{
		m_commandType = CommandType::NoCommand;
		return Status::OK;
	}

	size_t spacePos = rawExpression.find(' ');
	std::string commandString = rawExpression.substr(0, rawExpression.find(' '));

	if (!m_mapStringToCommandType.contains(commandString))
	{
		return Status::ParsingError;
	}

	CommandType type = m_mapStringToCommandType.at(commandString);

	if (type == CommandType::SetGear || type == CommandType::SetSpeed)
	{
		int value;
		try
		{
			value = std::stoi(rawExpression.substr(spacePos + 1));
		}
		catch (...)
		{
			return Status::ParsingError;
		}

		m_arg = value;
	}

	m_commandType = type;

	return Status::OK;
}

CommandInterpreter::Status CommandInterpreter::Execute()
{
	switch (m_commandType)
	{
	case CommandType::NoCommand:
		return Status::OK;

	case CommandType::Info:
		PrintCarInfo();
		return Status::OK;

	case CommandType::Exit:
		return Status::Exit;

	case CommandType::EngineOn:
		return m_car.TurnOnEngine() ? Status::OK : Status::ExecutionError;

	case CommandType::EngineOff:
		return m_car.TurnOffEngine() ? Status::OK : Status::ExecutionError;

	case CommandType::SetGear:
		return m_car.SetGear(*m_arg) ? Status::OK : Status::ExecutionError;

	case CommandType::SetSpeed:
		return m_car.SetSpeed(*m_arg) ? Status::OK : Status::ExecutionError;

	default:
		return Status::ExecutionError;
	}
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
