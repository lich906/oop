#include <catch2/catch.hpp>
#include "primes_generator.h"
#include <sstream>

TEST_CASE("Generating set of prime numbers")
{
	std::set<int> result;

	SECTION("If upper bound is negative throws exception")
	{
		REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(-3), std::runtime_error);
	}

	SECTION("If upper bound between 0 and 1 generates empty set")
	{
		REQUIRE(GeneratePrimeNumbersSet(0).empty());
		REQUIRE(GeneratePrimeNumbersSet(1).empty());
	}

	SECTION("If upper bound is 2 generates only one prime number -- 2")
	{
		result = GeneratePrimeNumbersSet(2);

		REQUIRE(result.size() == 1);
		REQUIRE(result.find(2) != result.end());
	}

	SECTION("There is 5761455 prime numbers within 1 and 100000000")
	{
		result = GeneratePrimeNumbersSet(100000000);

		REQUIRE(result.size() == 5761455);
	}
}

TEST_CASE("Test set printing")
{
	std::ostringstream oss;

	SECTION("With empty set")
	{
		PrintSet(oss, std::set<int>{});

		REQUIRE(oss.str() == "");
	}

	SECTION("With one element in set")
	{
		PrintSet(oss, std::set<int>{46});

		REQUIRE(oss.str() == "46");
	}

	SECTION("With many elements in set")
	{
		PrintSet(oss, std::set<int>{ 46, 23, 13, 12, 1, 15 });

		REQUIRE(oss.str() == "1, 12, 13, 15, 23, 46");
	}

	SECTION("Specify another delimiter")
	{
		PrintSet(oss, std::set<int>{ 46, 23, 13, 12, 1, 15 }, " : ");

		REQUIRE(oss.str() == "1 : 12 : 13 : 15 : 23 : 46");
	}
}