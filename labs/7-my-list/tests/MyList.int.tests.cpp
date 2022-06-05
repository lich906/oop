#include "catch2/catch.hpp"
#include "MyList.hpp"
#include <sstream>

TEST_CASE("Pushing integer elements to back")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(num1);
	REQUIRE(list.GetBack() == num1);
	REQUIRE(list.GetLength() == 1);
	REQUIRE(!list.IsEmpty());

	list.PushBack(num2);
	REQUIRE(list.GetBack() == num2);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(!list.IsEmpty());

	list.PushBack(num3).PushBack(num4);
	REQUIRE(list.GetBack() == num4);
	REQUIRE(list.GetLength() == 4);
	REQUIRE(!list.IsEmpty());
}

TEST_CASE("Push integer elements to front and back")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(num1);
	REQUIRE(list.GetBack() == num1);
	REQUIRE(list.GetFront() == num1);
	REQUIRE(list.GetLength() == 1);
	REQUIRE(!list.IsEmpty());

	list.PushFront(num2);
	REQUIRE(list.GetBack() == num1);
	REQUIRE(list.GetFront() == num2);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(!list.IsEmpty());

	list.PushBack(num3).PushFront(num4);
	REQUIRE(list.GetBack() == num3);
	REQUIRE(list.GetFront() == num4);
	REQUIRE(list.GetLength() == 4);
	REQUIRE(!list.IsEmpty());
}

TEST_CASE("Test PopBack method with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(num1).PushFront(num2);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == num1);

	list.PopBack();
	REQUIRE(list.GetLength() == 1);
	REQUIRE(list.GetBack() == num2);

	list.PushBack(num3);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == num3);

	list.PopBack().PopBack();
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
}

TEST_CASE("Test PopFront method with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushFront(num1).PushBack(num2);
	REQUIRE(!list.IsEmpty());
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetBack() == num2);
	REQUIRE(list.GetFront() == num1);

	list.PopFront();
	REQUIRE(list.GetLength() == 1);
	REQUIRE(list.GetBack() == num2);
	REQUIRE(list.GetFront() == num2);

	list.PushFront(num3);
	REQUIRE(list.GetLength() == 2);
	REQUIRE(list.GetFront() == num3);

	list.PopFront().PopFront();
	REQUIRE(list.IsEmpty());
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
}

TEST_CASE("Test iterator increment operator with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(num1).PushBack(num2).PushBack(num3).PushBack(num4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Increment begin() iterator once")
	{
		REQUIRE(list.GetFront() == *list.begin());

		int secondElement = *(++list.begin());
		list.PopFront();
		REQUIRE(list.GetFront() == secondElement);
		REQUIRE(list.GetFront() == *list.begin());
	}

	SECTION("Increment begin() iterator several times")
	{
		MyList<int>::ConstIterator iterator = list.begin();

		REQUIRE(*iterator++ == 23);
		REQUIRE(*iterator == 15);
		REQUIRE(*++iterator == -5);
		++iterator;
		REQUIRE(*iterator == 16);
	}

	SECTION("Try increment end() iterator")
	{
		MyList<int>::ConstIterator iterator = list.end();

		REQUIRE_THROWS_AS(++iterator, std::logic_error);
		REQUIRE_THROWS_AS(iterator++, std::logic_error);
	}

	SECTION("Try increment rend() iterator")
	{
		MyList<int>::ConstReverseIterator iterator = list.rend();

		CHECK_THROWS_AS(++++iterator, std::logic_error);
		CHECK_THROWS_AS(iterator++ ++, std::logic_error);
	}
}

TEST_CASE("Test iterator decrement operator with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(num1).PushBack(num2).PushBack(num3).PushBack(num4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Decrement end() iterator once")
	{
		REQUIRE(list.GetBack() == 16);
		REQUIRE(list.GetBack() == *(--list.end()));

		list.PopBack();
		REQUIRE(list.GetBack() == -5);
		REQUIRE(list.GetBack() == *(--list.end()));
	}

	SECTION("Decrement end() iterator several times")
	{
		MyList<int>::ConstIterator iterator = list.end();

		REQUIRE(*--iterator == 16);
		REQUIRE(*iterator-- == 16);
		REQUIRE(*iterator == -5);
		REQUIRE(*--iterator == 15);
		REQUIRE(*--iterator == 23);
	}

	SECTION("Try decrement begin() before iterator")
	{
		MyList<int>::ConstIterator iterator = list.begin();

		REQUIRE_THROWS_AS(----iterator, std::logic_error);
	}

	SECTION("Try decrement rbegin() before iterator")
	{
		MyList<int>::ConstReverseIterator iterator = list.rbegin();

		REQUIRE_THROWS_AS(----iterator, std::logic_error);
	}
}

TEST_CASE("Test iterator equality and non-equality operators with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());
	REQUIRE(list.begin() == list.end());

	list.PushBack(num1).PushBack(num2).PushBack(num3).PushBack(num4);
	REQUIRE(list.GetLength() == 4);

	REQUIRE(list.begin() != list.end());
	REQUIRE(++++list.begin() == ----list.end());

	REQUIRE(list.rbegin() != list.rend());
	REQUIRE(++++list.rbegin() == ----list.rend());

	list.PopBack().PopFront();

	REQUIRE(++list.begin() == --list.end());
	REQUIRE(++list.rbegin() == --list.rend());
}

TEST_CASE("Test regular const and non-const iterator with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;
	std::ostringstream oss;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(num1).PushBack(num2).PushBack(num3).PushBack(num4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Write integers to ostream using const iterator")
	{
		MyList<int>::ConstIterator iterator = list.begin();

		for (; iterator != list.end(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(oss.str() == "23 15 -5 16 ");
	}

	SECTION("Mutate integer list data using regular iterator")
	{
		MyList<int>::Iterator iterator = list.begin();

		for (; iterator != list.end(); ++iterator)
		{
			*iterator = 6;
		}

		for (iterator = list.begin(); iterator != list.end(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(list.GetFront() == 6);
		REQUIRE(list.GetBack() == 6);
		REQUIRE(oss.str() == "6 6 6 6 ");
	}
}

TEST_CASE("Test reverse const and non-const iterator with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;
	std::ostringstream oss;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(num1).PushBack(num2).PushBack(num3).PushBack(num4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Write strings to ostream using reverse const iterator")
	{
		MyList<int>::ConstReverseIterator iterator = list.rbegin();

		for (; iterator != list.rend(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(oss.str() == "16 -5 15 23 ");
	}

	SECTION("Mutate list data using reverse iterator")
	{
		MyList<int>::ReverseIterator iterator = list.rbegin();

		for (; iterator != list.rend(); ++iterator)
		{
			*iterator = 6;
		}

		for (iterator = list.rbegin(); iterator != list.rend(); ++iterator)
		{
			oss << *iterator << ' ';
		}

		REQUIRE(list.GetFront() == 6);
		REQUIRE(list.GetBack() == 6);
		REQUIRE(oss.str() == "6 6 6 6 ");
	}
}

TEST_CASE("Test Insert method with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	SECTION("Insert to begin pos")
	{
		list.Insert(list.begin(), num1);
		REQUIRE(list.GetLength() == 1);
		REQUIRE(list.GetFront() == num1);
		REQUIRE(list.GetBack() == num1);
	}

	SECTION("Insert to end pos")
	{
		list.Insert(list.cend(), num2);
		REQUIRE(list.GetLength() == 1);
		REQUIRE(list.GetFront() == num2);
		REQUIRE(list.GetBack() == num2);
	}

	SECTION("Insert to the middle")
	{
		list.Insert(list.cend(), num1);
		list.Insert(list.cend(), num2);
		REQUIRE(list.GetLength() == 2);
		REQUIRE(list.GetFront() == num1);
		REQUIRE(list.GetBack() == num2);

		list.Insert(++list.cbegin(), num3);
		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == num1);
		REQUIRE(list.GetBack() == num2);

		REQUIRE(list.PopFront().GetFront() == num3);

		list.Insert(--list.cend(), num4);
		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == num3);
		REQUIRE(list.GetBack() == num2);

		REQUIRE(list.PopBack().GetBack() == num4);
	}
}

TEST_CASE("Test Erase method with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> list;
	REQUIRE(list.IsEmpty());

	list.PushBack(num1).PushBack(num2).PushBack(num3).PushBack(num4);
	REQUIRE(list.GetLength() == 4);

	SECTION("Erase first element")
	{
		REQUIRE(list.GetFront() == num1);
		REQUIRE(list.GetLength() == 4);

		list.Erase(list.cbegin());

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == num2);
	}

	SECTION("Erase last element")
	{
		REQUIRE(list.GetBack() == num4);
		REQUIRE(list.GetLength() == 4);

		list.Erase(--list.cend());

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetBack() == num3);
	}

	SECTION("Erase element in the middle")
	{
		REQUIRE(list.GetFront() == num1);
		REQUIRE(list.GetLength() == 4);

		list.Erase(++++list.cbegin()); // erase num3

		REQUIRE(list.GetLength() == 3);
		REQUIRE(list.GetFront() == num1);
		REQUIRE(*(++++list.begin()) == num4);
		REQUIRE(*(----list.end()) == num2);
	}

	SECTION("Try erase past-the-last element")
	{
		REQUIRE_THROWS_AS(list.Erase(list.cend()), std::logic_error);
		REQUIRE_THROWS_AS(list.Erase(--list.crend().base()), std::logic_error);
	}
}

TEST_CASE("Test copy constructor with integers")
{
	int num1 = 23, num2 = 15, num3 = -5, num4 = 16;

	MyList<int> src;
	REQUIRE(src.IsEmpty());

	src.PushBack(num1).PushBack(num2).PushBack(num3).PushBack(num4);
	REQUIRE(src.GetLength() == 4);

	SECTION("Copy assignment operator")
	{
		MyList<int> dest(src);
		REQUIRE(dest);

		REQUIRE(dest.GetLength() == 4);
		REQUIRE(dest.GetFront() == num1);
		REQUIRE(dest.GetBack() == num4);
		dest.PopFront().PopBack();
		REQUIRE(dest.GetFront() == num2);
		REQUIRE(dest.GetBack() == num3);

		REQUIRE(src.GetLength() == 4);
		REQUIRE(src.GetFront() == num1);
		REQUIRE(src.GetBack() == num4);
	}

	SECTION("Copy assignment operator")
	{
		MyList<int> dest;
		REQUIRE(!dest);

		dest = src;
		REQUIRE(dest.GetLength() == 4);
		REQUIRE(dest.GetFront() == num1);
		REQUIRE(dest.GetBack() == num4);
		dest.PopFront().PopBack();
		REQUIRE(dest.GetFront() == num2);
		REQUIRE(dest.GetBack() == num3);

		REQUIRE(src.GetLength() == 4);
		REQUIRE(src.GetFront() == num1);
		REQUIRE(src.GetBack() == num4);
	}
}

TEST_CASE("Test default constructed iterator of integer list")
{
	MyList<int>::ConstIterator iterator;

	REQUIRE_THROWS_AS(*iterator, std::logic_error);
	REQUIRE_THROWS_AS(++iterator, std::logic_error);
	REQUIRE_THROWS_AS(iterator++, std::logic_error);
	REQUIRE_THROWS_AS(--iterator, std::logic_error);
	REQUIRE_THROWS_AS(iterator--, std::logic_error);
}
