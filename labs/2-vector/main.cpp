#include "lib\vector_functions.h"
#include "lib\misc.h"

int main()
{
	auto vect = ReadVectorOfNumbers(std::cin);

	if (!vect.has_value())
	{
		LogError("Failed to read data.\n");
		return 1;
	}

	auto res = ProcessVect(vect.value());

	if (!res.has_value())
	{
		LogError("Dividing by min element equals zero");
		return 1;
	}

	if (!PrintVector(std::cout, res.value()))
	{
		LogError("Failed to print out data.\n");
		return 1;
	}

	return 0;
}
