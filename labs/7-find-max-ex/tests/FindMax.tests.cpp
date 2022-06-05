#include "catch2/catch.hpp"
#include "FindMax.hpp"
#include "Sportsmen.hpp"

TEST_CASE("Find sportsmen by max height")
{
	std::vector<Sportsmen> vect{
		Sportsmen("Vasiliy Pupkin", 160, 75),
		Sportsmen("Ivan Petrov", 185, 93),
		Sportsmen("Ivan Ivanov", 180, 95),
		Sportsmen("Oleg Olegov", 172, 79),
		Sportsmen("Olga Olgovna", 170, 77),
		Sportsmen("Vladimir Putin", 181, 86),
		Sportsmen("Vladimir Monomakh", 178, 72)
	};

	SECTION("Find max sportsmen by height")
	{
		Sportsmen maxSportsmen;

		REQUIRE(FindMax(vect, maxSportsmen, [](const Sportsmen& first, const Sportsmen& second) {
			return first.GetHeight() < second.GetHeight();
		}));

		REQUIRE(maxSportsmen.GetName() == "Ivan Petrov");
		REQUIRE(maxSportsmen.GetHeight() == 185);
		REQUIRE(maxSportsmen.GetWeight() == 93);
	}

	SECTION("Find max sportsmen by weight")
	{
		Sportsmen maxSportsmen;

		REQUIRE(FindMax(vect, maxSportsmen, [](const Sportsmen& first, const Sportsmen& second) {
			return first.GetWeight() < second.GetWeight();
		}));

		REQUIRE(maxSportsmen.GetName() == "Ivan Ivanov");
		REQUIRE(maxSportsmen.GetHeight() == 180);
		REQUIRE(maxSportsmen.GetWeight() == 95);
	}
}

TEST_CASE("Find max integer")
{
	std::vector<int> vect{ 13, 16, 6, 43, 143, 34 };

	int maxInt;

	REQUIRE(FindMax(vect, maxInt, [](int first, int second) {
		return first < second;
	}));

	REQUIRE(maxInt == 143);
}

TEST_CASE("Empty vector")
{
	std::vector<char> vect;

	char maxChar;

	REQUIRE(!FindMax(vect, maxChar, [](char first, char second) {
		return first < second;
	}));
}
