#include <iostream>
#include "Calculator.h"

int main()
{
	Calculator calc;
	while (!std::cin.eof())
	{
		calc.Interpret(std::cin, std::cout);
	}

	return 0;
}
