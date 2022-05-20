#include "primes_generator.h"
#include <string>

constexpr int ARGUMENTS_COUNT = 2;

int ParseArg(int argc, char* argv[]);

int main(int argc, char** argv)
{
	try
	{
		int upperBound = ParseArg(argc, argv);
		std::set<int> primesSet = GeneratePrimeNumbersSet(upperBound);
		PrintSet(std::cout, primesSet);
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}

int ParseArg(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		throw std::runtime_error("Invalid arguments count. Usage: 2-primes-generator <upper bound>");
	}

	try
	{
		int arg = std::stoi(std::string(argv[1]));
		return arg;
	}
	catch (const std::invalid_argument& e)
	{
		throw std::invalid_argument("Upper bound argument is not a valid number");
	}
	catch (const std::out_of_range& e)
	{
		throw std::out_of_range("Upper bound value is out of range");
	}
}
