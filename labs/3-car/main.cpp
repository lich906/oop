#include <iostream>

#include "Car.h"
#include "CommandInterpreter.h"

int main()
{
	Car car;
	CommandInterpreter interpreter(car, std::cin, std::cout);
	CommandInterpreter::Status status;

	while ((status = interpreter.Interpret()) != CommandInterpreter::Status::Exit)
	{
		if (status == CommandInterpreter::Status::ParsingError)
		{
			std::cout << "Command parsing error" << std::endl;
		}

		if (status == CommandInterpreter::Status::ExecutionError)
		{
			std::cout << "Failed to perform action" << std::endl;
		}
	}

	return 0;
}
