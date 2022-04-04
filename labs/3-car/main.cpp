#include <iostream>

#include "Car.h"
#include "CommandInterpreter.h"

int main()
{
	Car car;
	CommandInterpreter interpreter(car, std::cin, std::cout);
	CommandInterpreter::Result result;

	while ((result = interpreter.Interpret()).status != CommandInterpreter::Status::Exit)
	{
		if (result.status != CommandInterpreter::Status::OK)
		{
			if (result.reportMessage.has_value())
			{
				std::cout << *(result.reportMessage) << std::endl;
			}
			else
			{
				switch (result.status)
				{
				case CommandInterpreter::Status::ParsingError:
					std::cout << "Parsing error was occured." << std::endl;
					break;
				case CommandInterpreter::Status::ExecutionError:
					std::cout << "Execution error was occured." << std::endl;
					break;
				default:
					break;
				}
			}
		}
	}

	std::cout << "Exiting..." << std::endl;

	return 0;
}
