#include <catch2/catch.hpp>
#include "StringList.h"

TEST_CASE("Initializing string list")
{
	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE(list.GetLength() == 0);
}

TEST_CASE("Try get element from back and front of empty list")
{
	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE(list.GetLength() == 0);

	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
	REQUIRE_THROWS_WITH(list.GetFront(), "List is empty");

	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_WITH(list.GetBack(), "List is empty");
}

TEST_CASE("Pushing elements to back")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1);
	REQUIRE(list.GetBack() == str1);
	REQUIRE(list.GetLength() == 1);
	REQUIRE(!list.IsEmpty());

	list.PushBack(str2);
	REQUIRE(list.GetBack() == str2);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(!list.IsEmpty());

	list.PushBack(str3).PushBack(str4);
	REQUIRE(list.GetBack() == str4);
	REQUIRE(list.GetLength() == 4);
	REQUIRE(!list.IsEmpty());
}

TEST_CASE("Push elements to front and back")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1);
	REQUIRE(list.GetBack() == str1);
	REQUIRE(list.GetFront() == str1);
	REQUIRE(list.GetLength() == 1);
	REQUIRE(!list.IsEmpty());

	list.PushFront(str2);
	REQUIRE(list.GetBack() == str1);
	REQUIRE(list.GetFront() == str2);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(!list.IsEmpty());

	list.PushBack(str3).PushFront(str4);
	REQUIRE(list.GetBack() == str3);
	REQUIRE(list.GetFront() == str4);
	REQUIRE(list.GetLength() == 4);
	REQUIRE(!list.IsEmpty());
}

TEST_CASE("Test Clear method")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushBack(str2).PushBack(str3).PushBack(str4);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.GetLength() == 4);

	list.Clear();
	REQUIRE(list.IsEmpty());
	REQUIRE(list.GetLength() == 0);
}

TEST_CASE("Test bool cast operator")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE(!list);

	list.PushBack(str1);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list);
}

TEST_CASE("Test PopBack method")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushBack(str1).PushFront(str2);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == str1);

	list.PopBack();
	REQUIRE(list.GetLength() == 1);
	REQUIRE(list.GetBack() == str2);

	list.PushBack(str3);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == str3);

	list.PopBack().PopBack();
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
}

TEST_CASE("Test PopFront method")
{
	std::string str1("Provide"), str2("Strong"), str3("Exception"), str4("Safety");

	StringList list;
	REQUIRE(list.IsEmpty());

	list.PushFront(str1).PushBack(str2);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == str2);
	REQUIRE(list.GetFront() == str1);

	list.PopFront();
	REQUIRE(list.GetLength() == 1);
	REQUIRE(list.GetBack() == str2);
	REQUIRE(list.GetFront() == str2);

	list.PushFront(str3);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetFront() == str3);

	list.PopFront().PopFront();
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
}
