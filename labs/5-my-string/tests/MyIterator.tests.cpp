#include <catch2/catch.hpp>
#include "MyString.h"

TEST_CASE("Test functionality of const iterator")
{
	const MyString str("Walking throught the string :]");

	SECTION("Get begin() const iterator from const MyString instance")
	{
		MyString::const_iterator cIt1 = str.begin();
		MyString::const_iterator cIt2 = str.cbegin();
		const char* first = str.GetStringData();

		REQUIRE(*first == 'W');
		REQUIRE(cIt1.data() == first);
		REQUIRE(cIt2.data() == first);
	}

	SECTION("Get end() const iterator from const MyString instance")
	{
		MyString::const_iterator cIt1 = str.end();
		MyString::const_iterator cIt2 = str.cend();
		const char* last = str.GetStringData() + (str.GetLength() - 1);

		REQUIRE(*last == ']');
		REQUIRE(cIt1.data() == (last + 1));
		REQUIRE(cIt2.data() == (last + 1));
	}

	SECTION("Dereferencing of const iterator")
	{
		MyString::const_iterator cIt = str.begin();
		REQUIRE(*cIt == 'W');
	}

	SECTION("Pre-increment of const iterator")
	{
		MyString::const_iterator cIt = str.begin();
		REQUIRE(*cIt == 'W');
		REQUIRE(*++cIt == 'a');
		REQUIRE(*++cIt == 'l');
		REQUIRE(*++cIt == 'k');
	}

	SECTION("Post-increment of const iterator")
	{
		MyString::const_iterator cIt = str.begin();
		REQUIRE(*cIt++ == 'W');
		REQUIRE(*cIt == 'a');
		REQUIRE(*cIt++ == 'a');
		REQUIRE(*cIt++ == 'l');
		REQUIRE(*cIt == 'k');
	}

	SECTION("Test equation check for iterators")
	{
		MyString::const_iterator cIt1 = str.begin();
		MyString::const_iterator cIt2 = str.begin();

		REQUIRE(cIt1 == cIt2);

		REQUIRE(cIt1++ == cIt2);
		REQUIRE(cIt1 != cIt2);

		++cIt2;
		REQUIRE(cIt1 == cIt2);

		REQUIRE(++cIt1 == ++cIt2);
	}
}

TEST_CASE("Test functionality of non const iterator")
{
	MyString str("Looking at the string :)");

	SECTION("Get begin() iterator, iterator points at the first element")
	{
		MyString::iterator it = str.begin();
		const char* first = str.GetStringData();

		REQUIRE(*first == 'L');
		REQUIRE(it.data() == first);
	}

	SECTION("Get end() iterator, iterator points at the past-the-end element")
	{
		const char* last = str.GetStringData() + (str.GetLength() - 1);
		REQUIRE(*last == ')');

		MyString::iterator it = str.end();
		REQUIRE(it.data() == (last + 1));
	}

	SECTION("Dereference the iterator and mutate data")
	{
		MyString::iterator it = str.begin();
		REQUIRE(*it == 'L');
	
		*it = 'B';
		REQUIRE(str == "Booking at the string :)");
	}

	SECTION("Increment the iterator and mutate string")
	{
		MyString::iterator it = str.begin();
		REQUIRE(*it == 'L');
		*it = 'B';
		REQUIRE(str == "Booking at the string :)");

		REQUIRE(*++it == 'o');
		*it = 'a';
		REQUIRE(str == "Baoking at the string :)");

		REQUIRE(*++it == 'o');
		*it = 'r';
		REQUIRE(str == "Barking at the string :)");

		REQUIRE(*++it == 'k');
	}

	SECTION("Post-increment of const iterator")
	{
		MyString::iterator it = str.begin();
		REQUIRE(*it++ == 'L');
		*it = 'i';
		REQUIRE(str == "Lioking at the string :)");

		REQUIRE(*it++ == 'i');
		*it = 'c';
		REQUIRE(str == "Licking at the string :)");

		REQUIRE(*it++ == 'c');
		*it = 'r';
		REQUIRE(str == "Licring at the string :)");

		REQUIRE(*it == 'r');
	}
}