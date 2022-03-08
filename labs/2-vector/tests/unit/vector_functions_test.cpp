#include <catch2/catch.hpp>
#include <lib/vector_functions.h>
#include <sstream>

TEST_CASE("ReadVectorOfNumbers() must read numbers from istream and arrange elements in ascending order")
{
	std::vector<float> v;
	std::stringstream ss;
	
	SECTION("read one number")
	{
		ss << "5";
		REQUIRE_THAT(ReadVectorOfNumbers(ss).value(), Catch::Matchers::Equals(std::vector<float>{ 5 }));
	}

	SECTION("read some numbers, expect ascending order")
	{
		ss << "5 3 1.2 -5.4";
		REQUIRE_THAT(ReadVectorOfNumbers(ss).value(), Catch::Matchers::Equals(std::vector<float>{ -5.4, 1.2, 3, 5 }));
	}

	SECTION("expect nullopt when input stream is empty")
	{
		REQUIRE(!ReadVectorOfNumbers(ss).has_value());
	}

	SECTION("expect nullopt when input stream contains no numbers")
	{
		ss << "jgt #)(F kiof";
		REQUIRE(!ReadVectorOfNumbers(ss).has_value());
	}
}

TEST_CASE("ProcessVect() must multiply by max element and divide by min element for each element in vector")
{
	SECTION("only positive numbers")
	{
		std::vector<float> v{ 1, 1.2, 3, 5 };
		REQUIRE_THAT(ProcessVect(v).value(), Catch::Matchers::Equals(std::vector<float>{ 5, 6, 15, 25 }));
	}

	SECTION("with negative numbers")
	{
		std::vector<float> v{ -1, 1.2, 3, 5 };
		REQUIRE_THAT(ProcessVect(v).value(), Catch::Matchers::Equals(std::vector<float>{ -25, -15, -6, 5 }));
	}

	SECTION("with negative numbers")
	{
		std::vector<float> v{ -5, -1, 3, 5 };
		REQUIRE_THAT(ProcessVect(v).value(), Catch::Matchers::Equals(std::vector<float>{ -5, -3, 1, 5 }));
	}

	SECTION("expect nullopt when min element equals zero")
	{
		std::vector<float> v{ 0, 1.2, 3, 5 };
		REQUIRE(!ProcessVect(v).has_value());
	}

	SECTION("expect unchanged vector when all elements are equal")
	{
		std::vector<float> v{ 3, 3, 3, 3, 3, 3 };
		REQUIRE_THAT(ProcessVect(v).value(), Catch::Matchers::Equals(v));
	}
}
