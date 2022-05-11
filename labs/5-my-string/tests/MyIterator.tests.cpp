#include <catch2/catch.hpp>
#include "MyString.h"

TEST_CASE("Get begin and end iterator's data")
{
	SECTION("Get begin() iterator, iterator points at the first element")
	{
		MyString str("Walking through the string");

		const char* first = str.GetStringData();
		REQUIRE(*first == 'W');

		MyIterator it = str.begin();
		REQUIRE(it.data() == first);
	}

	SECTION("Get end() iterator, iterator points at the past-the-end element")
	{
		MyString str("Looking at the string :)");

		const char* end = str.GetStringData() + (str.GetLength() - 1);
		REQUIRE(*end == ')');

		MyIterator it = str.end();
		REQUIRE(it.data() == (end + 1));
	}
}
