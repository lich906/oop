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

	SECTION("Test decrementing of the iterator")
	{
		const MyString palindrome("redivider");
		MyString::const_iterator beg = palindrome.begin();
		MyString::const_iterator end = palindrome.end();

		REQUIRE(*beg == 'r');

		--end;
		REQUIRE(*end == 'r');

		++beg;
		REQUIRE(*beg == 'e');

		++++++beg;
		REQUIRE(*beg == 'v');

		--end;
		REQUIRE(*end == 'e');
		REQUIRE(beg != end);

		------end;
		REQUIRE(*beg == *end);
		REQUIRE(beg == end);
	}

	SECTION("Add up iterator and integer")
	{
		// 01234567890123456789012345678
		// Walking through the string :]
		MyString::const_iterator it = str.begin();

		it += 3;
		REQUIRE(*it == 'k');
		REQUIRE(*(it + 6) == 'h');
		REQUIRE(*(it + 7) == 'r');

		it += -2;
		REQUIRE(*it == 'a');
		REQUIRE(*(it + 6) == ' ');
		REQUIRE(*(it + 7) == 't');
	}

	SECTION("Add up integer and iterator")
	{
		MyString::const_iterator it = str.begin();

		REQUIRE(*(2 + it) == 'l');
		REQUIRE(*((str.GetLength() - 1) + it) == ']');
		REQUIRE(*(0 + it) == *it);
		REQUIRE((0 + it) == it);
	}

	SECTION("Subtract integer from iterator")
	{
		// 09876543109876543210987654321
		// Walking through the string :]
		MyString::const_iterator it = str.end();

		it -= 1;
		REQUIRE(*it == ']');

		it -= 3;
		REQUIRE(*it == 'g');

		REQUIRE(*(it - 2) == 'i');
		REQUIRE(*(it - 5) == 's');
	}

	SECTION("Get difference of two iterators")
	{
		MyString::const_iterator beg = str.begin();
		MyString::const_iterator end = str.end();

		REQUIRE((end - beg) == str.GetLength());
		REQUIRE((beg - end) == -static_cast<int>(str.GetLength()));

		MyString::const_iterator beg2 = beg;
		REQUIRE((beg2 - beg) == 0);

		++beg2;
		REQUIRE((beg2 - beg) == 1);

		beg2 += 3;
		REQUIRE((beg2 - beg) == 4);

		beg += 4;
		REQUIRE(beg2 - beg == 0);
	}

	SECTION("Compare iterators")
	{
		MyString::const_iterator beg = str.begin();
		MyString::const_iterator end = str.end();

		REQUIRE(end > beg);
		REQUIRE(beg < end);

		MyString::const_iterator beg2 = str.begin();
		
		++beg2;
		REQUIRE(beg2 > beg);
		
		++beg;
		REQUIRE(beg2 >= beg);
		REQUIRE(beg2 <= beg);
	}

	SECTION("Access element at offset relatively of the iterator")
	{
		MyString::const_iterator beg = str.begin();
		MyString::const_iterator end = str.end();

		REQUIRE(beg[0] == 'W');
		REQUIRE(beg[2] == 'l');
		REQUIRE(*(beg + 5) == beg[5]);

		
		REQUIRE(end[-6] == 'i');
		REQUIRE(end[-8] == 't');
		REQUIRE(*(end - 7) == end[-7]);
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

	SECTION("Decrement the iterator and mutate string")
	{
		MyString::iterator it = str.end();
		MyString::const_iterator cIt = str.end();

		--it;
		--cIt;
		REQUIRE(*it == ')');
		REQUIRE(*cIt == ')');
		------it;
		REQUIRE(*it == 'g');
		*it = 'e';
		--it;
		*it = 'g';
		*--it = 'n';
		--it;
		*it-- = 'o';
		*it-- = 'p';

		REQUIRE(*it == 's');

		REQUIRE(str == "Looking at the sponge :)");
	}

	SECTION("Add up iterator and integer")
	{
		// 012345678901234567890123
		// Looking at the string :)
		MyString::iterator it = str.begin();

		it += 3;
		REQUIRE(*it == 'k');
		REQUIRE(*(it + 6) == 't');
		REQUIRE(*(it + 7) == ' ');

		it += -2;
		REQUIRE(*it == 'o');
		REQUIRE(*(it + 6) == ' ');
		REQUIRE(*(it + 7) == 'a');
	}

	SECTION("Add up integer and iterator")
	{
		MyString::iterator it = str.begin();

		REQUIRE(*(2 + it) == 'o');
		REQUIRE(*((str.GetLength() - 1) + it) == ')');
		REQUIRE(*(0 + it) == *it);
		REQUIRE((0 + it) == it);
	}

	SECTION("Subtract integer from iterator")
	{
		// 012345678901234567890123
		// Looking at the string :)
		MyString::iterator it = str.end();

		it -= 1;
		REQUIRE(*it == ')');

		it -= 3;
		REQUIRE(*it == 'g');

		REQUIRE(*(it - 2) == 'i');
		REQUIRE(*(it - 5) == 's');
	}

	SECTION("Get difference of two iterators")
	{
		MyString::iterator beg = str.begin();
		MyString::iterator end = str.end();

		REQUIRE((end - beg) == str.GetLength());
		REQUIRE((beg - end) == -static_cast<int>(str.GetLength()));

		MyString::const_iterator beg2 = beg;
		REQUIRE((beg2 - beg) == 0);

		++beg2;
		REQUIRE((beg2 - beg) == 1);

		beg2 += 3;
		REQUIRE((beg2 - beg) == 4);

		beg += 4;
		REQUIRE(beg2 - beg == 0);
	}

	SECTION("Compare iterators")
	{
		MyString::iterator beg = str.begin();
		MyString::iterator end = str.end();

		REQUIRE(end > beg);
		REQUIRE(beg < end);

		MyString::iterator beg2 = str.begin();

		++beg2;
		REQUIRE(beg2 > beg);

		++beg;
		REQUIRE(beg2 >= beg);
		REQUIRE(beg2 <= beg);
	}

	SECTION("Access element at offset relatively of the iterator and mutate it")
	{
		// Looking at the string :)
		MyString::iterator beg = str.begin();
		MyString::iterator end = str.end();

		beg[0] = 'D';
		beg[3] = 'm';
		end[-8] = 'p';
		end[-7] = 'o';

		--end;
		end[-5] = 'n';
		end[-4] = 'g';
		end[-3] = 'e';

		REQUIRE(str == "Dooming at the sponge :)");
	}
}

TEST_CASE("Test range-based for loop compatibility")
{
	MyString str("Iterating through the string");

	SECTION("Copy content of string to accumulator and fill str with '#' char")
	{
		std::string copy;

		for (char& ch : str)
		{
			copy.push_back(ch);
			ch = '#';
		}

		REQUIRE(copy == "Iterating through the string");
		REQUIRE(str == "############################");
	}
}

TEST_CASE("Test reverse iterators functionality")
{
	MyString str("Dancing with the string");

	SECTION("Reverse the string with reverse iterator and range-based for")
	{
		MyString::const_reverse_iterator rend = str.rend();
		std::string reversedStr;

		for (auto rbeg = str.rbegin(); rbeg != rend; ++rbeg)
		{
			reversedStr.push_back(*rbeg);
		}

		REQUIRE(reversedStr == "gnirts eht htiw gnicnaD");
	}

	SECTION("Reverse the string and take only odd chars")
	{
		MyString::const_reverse_iterator rend = str.rend();
		std::string reversedStr;

		for (auto rbeg = str.rbegin(); rbeg < rend; rbeg += 2)
		{
			reversedStr.push_back(*rbeg);
		}

		REQUIRE(reversedStr == "git h twginD");
	}

	SECTION("Replace each even char with '@'")
	{
		for (auto rbeg = str.rbegin(); rbeg < str.rend(); rbeg += 2)
		{
			*rbeg = '@';
		}

		REQUIRE(str == "@a@c@n@ @i@h@t@e@s@r@n@");
	}

	SECTION("Move two iterators towards each other and mutate string")
	{
		for (auto rbeg = str.rbegin(), rend = str.rend() - 1; rbeg < rend; rbeg +=2, rend -=2)
		{
			*rbeg = '@';
			*rend = '#';
		}

		REQUIRE(str == "#a#c#n# #i#h@t@e@s@r@n@");
	}
}
