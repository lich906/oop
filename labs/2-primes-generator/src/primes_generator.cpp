#include "primes_generator.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 0)
	{
		throw std::runtime_error("Upper bound value must be greater than zero");
	}
	else if (upperBound < 2)
	{
		return std::set<int>();
	}

	size_t sieveSize = upperBound + 1;
	std::vector<bool> sieve(sieveSize, true);
	sieve[0] = 0;
	sieve[1] = 0;

	size_t iterationsLimit = ceil(sqrt(sieveSize));
	for (size_t index = 2; index <= iterationsLimit; ++index)
	{
		if (sieve[index])
		{
			for (size_t i = index * 2; i < sieveSize; i += index)
			{
				sieve[i] = false;
			}
		}
	}

	std::set<int> primesSet;
	for (size_t i = 0; i < sieveSize; i++)
	{
		if (sieve[i])
		{
			primesSet.insert(primesSet.end(), i);
		}
	}

	return primesSet;
}

void PrintSet(std::ostream& out, const std::set<int>& set, const char* delimiter)
{
	if (set.empty())
		return;

	auto it = set.begin();

	out << *it++;
	
	while (it != set.end())
	{
		out << delimiter << *it++;
	}
}
