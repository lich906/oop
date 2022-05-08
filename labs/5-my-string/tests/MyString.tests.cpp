#include <catch2/catch.hpp>
#include "MyString.h"

TEST_CASE("Initializing string")
{
	SECTION("Initialize empty MyString")
	{
		MyString str;

		REQUIRE(strcmp(str.GetStringData(), "") == 0);
	}

	SECTION("Initialize MyString with null-terminated string")
	{
		char str[] = "Wizard";
		MyString myStr(str), myStr2("That's fine"), myStr3 = "Convert constructor should be invoked";

		REQUIRE(strcmp(myStr.GetStringData(), str) == 0);
		REQUIRE(strcmp(myStr2.GetStringData(), "That's fine") == 0);
		REQUIRE(strcmp(myStr3.GetStringData(), "Convert constructor should be invoked") == 0);
	}

	SECTION("Ensure that MyString was copied rather than pointed to existing char array")
	{
		char str[] = "Wizard";
		MyString myStr(str);

		str[0] = 'L';

		REQUIRE(strcmp(str, "Lizard") == 0);
		REQUIRE(strcmp(myStr.GetStringData(), "Wizard") == 0);
	}

	SECTION("Initialize MyString with null-terminated string containing null chars in the middle")
	{
		char str[] = "Come\0My\0Fanatics";
		MyString myStr(str, sizeof str);

		REQUIRE(strcmp(myStr.GetStringData(), str) == 0);
	}

	SECTION("Initialize MyString with not null terminated string")
	{
		char str[]{ 'T', 'h', 'a', 't', '\0', 'l', 'o', 'o', 'k', 's', '\0', 'w', 'e', 'i', 'r', 'd' };
		MyString myStr(str, sizeof str);

		REQUIRE(strcmp(myStr.GetStringData(), "That\0looks\0weird") == 0);
	}

	SECTION("Length passed to constructor is less than actual size")
	{
		char str[] = "Directed By Robert B. Weide";
		MyString myStr(str, 11);

		REQUIRE(strcmp(myStr.GetStringData(), "Directed By") == 0);
	}

	SECTION("Initialize MyString with std::string instance")
	{
		MyString myStr(std::string("Stl string"));
		MyString myStr2 = std::string("Convert constructor should be invoked");

		REQUIRE(strcmp(myStr.GetStringData(), "Stl string") == 0);
		REQUIRE(strcmp(myStr2.GetStringData(), "Convert constructor should be invoked") == 0);
	}
}

TEST_CASE("Test copy constructor and copy assignment operator")
{
	SECTION("Explicit constructor call")
	{
		MyString src("I went to netherlands");
		REQUIRE(strcmp(src.GetStringData(), "I went to netherlands") == 0);

		MyString dest(src);
		REQUIRE(strcmp(dest.GetStringData(), "I went to netherlands") == 0);
	}

	SECTION("Test copy assignment operator")
	{
		MyString src("Our legion grows"), dest;

		dest = src;
		REQUIRE(strcmp(dest.GetStringData(), "Our legion grows") == 0);
	}

	SECTION("Ensure that data was copied rather than pointed to data of other string")
	{
		MyString src("Some cool phrase"), dest;
		REQUIRE(strcmp(src.GetStringData(), "Some cool phrase") == 0);

		dest = src;
		REQUIRE(strcmp(dest.GetStringData(), "Some cool phrase") == 0);

		src = "That phrase is cooller";

		REQUIRE(strcmp(src.GetStringData(), "That phrase is cooller") == 0);
		REQUIRE(strcmp(dest.GetStringData(), "Some cool phrase") == 0);
	}

	SECTION("Test self-assignment")
	{
		MyString src("What will you do");
		REQUIRE(strcmp(src.GetStringData(), "What will you do") == 0);
		const char* ptrBefore = src.GetStringData();

		src = src;

		const char* ptrAfter = src.GetStringData();
		REQUIRE(ptrAfter == ptrBefore);
		REQUIRE(strcmp(src.GetStringData(), "What will you do") == 0);
	}
}

TEST_CASE("Test move constructor and move assignment operator")
{
	SECTION("Explicit constructor call")
	{
		MyString str(std::move(MyString("Data is moved")));
		REQUIRE(strcmp(str.GetStringData(), "Data is moved") == 0);

		MyString str2(MyString("That data is moved too"));
		REQUIRE(strcmp(str2.GetStringData(), "That data is moved too") == 0);
	}

	SECTION("Test move assignment operator")
	{
		MyString str;

		str = MyString("Back to the future");

		REQUIRE(strcmp(str.GetStringData(), "Back to the future") == 0);
	}
}
