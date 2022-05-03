#include <catch2/catch.hpp>
#include "MyString.h"

TEST_CASE("Initializing string")
{
	SECTION("Initialize empty string")
	{
		MyString str;

		REQUIRE(strcmp(str.GetStringData(),"") == 0);
	}
}