#include <catch2/catch.hpp>
#include <CommandInterpreter.h>
#include <Car.h>
#include <sstream>

TEST_CASE("CommandInterpreter parses commands from istream and executes it by calling car's methods")
{
	std::ostringstream oss;
	Car car;

	SECTION("Try parse unknown command")
	{
		std::istringstream iss("SomeCommand 123");
		CommandInterpreter interpreter(car, iss, oss);

		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::ParsingError);
	}

	SECTION("Try parse SetGear command with bad argument")
	{
		std::istringstream iss("SetGear gi390g");
		CommandInterpreter interpreter(car, iss, oss);

		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::ParsingError);
	}

	SECTION("Parse sequence of valid commands")
	{
		std::istringstream iss("EngineOn\nSetGear -1\nSetSpeed 20\nSetGear 0\nSetSpeed 10\nSetSpeed 15\nSetGear 1\nEngineOff\nSetSpeed 0\nEngineOff\n");
		CommandInterpreter interpreter(car, iss, oss);

		//turn on engine
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetDirection() == 0);

		//set rear gear
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.GetGear() == -1);
		REQUIRE(car.GetDirection() == 0);

		//accelerate to 20 moving backwards
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.GetGear() == -1);
		REQUIRE(car.GetSpeed() == 20);
		REQUIRE(car.GetDirection() == -1);

		//set neutral gear
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 20);
		REQUIRE(car.GetDirection() == -1);

		//brake to 10
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == -1);

		//trying to accelerate from 10 to 15 on neutral gear
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::ExecutionError);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == -1);

		//trying to set gear 1 while moving backwards on neutral gear
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::ExecutionError);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == -1);

		//trying turn off engine while moving backwards on neutral gear
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::ExecutionError);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 10);
		REQUIRE(car.GetDirection() == -1);

		//brake to 0
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);
		REQUIRE(car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == 0);

		//turn off engine
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == 0);
	}
}

TEST_CASE("Empty string ignoring and 'Exit' command behavior")
{
	std::ostringstream oss;
	Car car;

	SECTION("Empty string is valid meaning that there is nothing to execute")
	{
		std::istringstream iss("\n");
		CommandInterpreter interpreter(car, iss, oss);

		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == 0);

		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);

		//car state wasn't changed
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		REQUIRE(car.GetDirection() == 0);
	}

	SECTION("Exit command invokes 'Exit' status")
	{
		std::istringstream iss("Exit\n");
		CommandInterpreter interpreter(car, iss, oss);

		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::Exit);
	}
}

TEST_CASE("Testing 'Info' command correct behavior")
{
	std::ostringstream oss;
	Car car;

	SECTION("Info command prints info into ostream")
	{
		std::istringstream iss("Info\n");
		CommandInterpreter interpreter(car, iss, oss);

		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK);

		REQUIRE(oss.str() == "Engine: Off\nDirection: Immobile\nSpeed: 0\nGear: N\n");
	}

	SECTION("Print info after changing car's state")
	{
		std::istringstream iss("EngineOn\nSetGear 1\nSetSpeed 10\nInfo\n");
		CommandInterpreter interpreter(car, iss, oss);

		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK); // turn engine on
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK); // set gear 1
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK); // set speed 10 moving forward
		REQUIRE(interpreter.Interpret().status == CommandInterpreter::Status::OK); // print info

		REQUIRE(oss.str() == "Engine: On\nDirection: Forward\nSpeed: 10\nGear: 1\n");
	}
}