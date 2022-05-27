#include <catch2/catch.hpp>
#include "StringList.h"

TEST_CASE("Initializing string list")
{
	SECTION("Initialize empty list")
	{
		StringList list;
		REQUIRE(list.IsEmpty());
	}
}