#include "lib\vector_functions.h"
#include "lib\misc.h"

int main()
{
	auto vect = ReadVectorOfNumbers(std::cin);

	if (!vect.has_value())
	{
		return 1;
	}

	if (!PrintVector(std::cout, ProcessVect(vect.value())))
	{
		return 1;
	}

	return 0;
}
