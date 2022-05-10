#include <catch2/catch.hpp>
#include "MyString.h"
#include <sstream>

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

TEST_CASE("SubString() returns the sub string at specified start and length")
{
	MyString subject("Let\0battle be\0joined", 20), result;

	SECTION("Start and length within the subject string size")
	{
		result = subject.SubString(4, 6);
		REQUIRE(result.GetLength() == 6);
		REQUIRE(strcmp(result.GetStringData(), "battle") == 0);
		REQUIRE(strcmp(subject.GetStringData(), "Let\0battle be\0joined") == 0);
	}

	SECTION("Length exceeds the subject string size")
	{
		result = subject.SubString(4, 123);
		REQUIRE(result.GetLength() == 16);
		REQUIRE(strcmp(result.GetStringData(), "battle be\0joined") == 0);
	}

	SECTION("Start exceeds the subject string size")
	{
		result = subject.SubString(123, 5);
		REQUIRE(result.GetLength() == 0);
		REQUIRE(strcmp(result.GetStringData(), "") == 0);
	}

	SECTION("Length parameter is zero")
	{
		result = subject.SubString(4, 0);
		REQUIRE(result.GetLength() == 0);
		REQUIRE(strcmp(result.GetStringData(), "") == 0);
	}
}

TEST_CASE("Clear() method deletes content of the string, string becomes empty")
{
	MyString src("What's done is done");

	SECTION("Call Clear() method")
	{
		REQUIRE(strcmp(src.GetStringData(), "What's done is done") == 0);

		src.Clear();

		REQUIRE(src.GetLength() == 0);
		REQUIRE(strcmp(src.GetStringData(), "") == 0);
	}

	SECTION("Assign previous value to another variable")
	{
		REQUIRE(strcmp(src.GetStringData(), "What's done is done") == 0);
		MyString dest = src;

		src.Clear();
		
		REQUIRE(strcmp(dest.GetStringData(), "What's done is done") == 0);
		REQUIRE(src.GetLength() == 0);
		REQUIRE(strcmp(src.GetStringData(), "") == 0);
	}
}

TEST_CASE("Test += operator")
{
	MyString primary("All shall ");

	SECTION("Append non-zero length string")
	{
		MyString appendix("revealed");
		primary += "be ";
		primary += appendix;
		
		REQUIRE(strcmp(primary.GetStringData(), "All shall be revealed") == 0);
	}

	SECTION("Append zero length string")
	{
		primary += "";

		REQUIRE(strcmp(primary.GetStringData(), "All shall ") == 0);
	}

	SECTION("Append string with available capacity left")
	{
		primary = "Hi, ";
		primary += "dudes";

		REQUIRE(primary.GetLength() == 9);
		REQUIRE(strcmp(primary.GetStringData(), "Hi, dudes") == 0);
	}
}

TEST_CASE("Test concatenation of two string")
{
	SECTION("Concatenate three strings")
	{
		MyString result = MyString("Hello") + " " + MyString("World");

		REQUIRE(strcmp(result.GetStringData(), "Hello World") == 0);
	}

	SECTION("Some complex sequence of concatenations")
	{
		MyString lval("bezumno");

		MyString result = MyString("Yes,\0there is\0null\0chars ", 24) + (lval += " mojno byt' first") + " this is end :^)";
		REQUIRE(strcmp(result.GetStringData(), "Yes,\0there is\0null\0chars bezumno mojno byt' first this is end :^)") == 0);
		REQUIRE(strcmp(lval.GetStringData(), "bezumno mojno byt' first") == 0);
	}
}

TEST_CASE("Test equality comparison of two strings")
{
	SECTION("Compare strings without null chars in the middle")
	{
		REQUIRE(MyString("1234") != MyString("1235"));
		REQUIRE(MyString("1234") != "1235");

		REQUIRE(MyString("1234") == std::string("1234"));
		REQUIRE("1234" == MyString("1234"));
	}

	SECTION("Compare strings with null chars")
	{
		REQUIRE(MyString("12\0 34", 6) == MyString("12\0 34", 6));
		REQUIRE(MyString("12\0 34", 6) != "12");
	}
}

TEST_CASE("Test comparison operators")
{
	SECTION("Compare strings with same length")
	{
		REQUIRE(MyString("1234") < "1235");
		REQUIRE("1235" > MyString("1234"));
		REQUIRE(MyString("123\0", 4) >= MyString("123\0", 4));
		REQUIRE(MyString("ab \0 c", 6) < MyString("ab \0 d", 6));
		REQUIRE(MyString("ab\0 d", 5) > MyString("ab\0 c", 5));
	}

	SECTION("Left string is shorter than right one")
	{
		REQUIRE(MyString() < MyString("123"));
		REQUIRE(MyString("1235") > MyString("1234567"));
		REQUIRE(MyString("1234") <= MyString("1234567"));
		REQUIRE(MyString("1\0 2", 4) < MyString("1\0 234", 6));
		REQUIRE(MyString("1\0 3", 4) > MyString("1\0 234", 6));
	}

	SECTION("Left string is longer than right one")
	{
		REQUIRE(MyString("12345") >= MyString("123"));
		REQUIRE(MyString("12\0 45", 6) > MyString("12\0 4", 6));
		REQUIRE(MyString("12345") > MyString());
		REQUIRE(MyString("321") >= MyString("32"));
	}
}

TEST_CASE("Test operator []")
{
	SECTION("Constant version of operator")
	{
		const MyString immutable("I The Immutability");

		REQUIRE(immutable[2] == 'T');
		REQUIRE(immutable[6] == 'I');
		REQUIRE(immutable[7] == immutable[8]);
		REQUIRE_THROWS_AS(immutable[100], std::out_of_range);
	}

	SECTION("Non-constant version of operator")
	{
		MyString str("Some content you can change");
		REQUIRE(str == "Some content you can change");

		str[0] = 'C';
		str[5] = 'm';
		str[13] = 'w';
		str[14] = 'e';
		str[15] = ' ';

		REQUIRE(str == "Come montent we  can change");

		REQUIRE_THROWS_AS(str[-23], std::out_of_range);
	}
}

TEST_CASE("Test istream >> operator overload for MyString")
{
	SECTION("No leading whitespaces in istream")
	{
		std::istringstream iss("For the king");
		MyString str("That value should be overrided");

		iss >> str;

		REQUIRE(iss);
		REQUIRE(str == "For");
	}

	SECTION("Leading whitespaces present and skipws flag is set")
	{
		std::istringstream iss("  \t\n  What a good idea.");
		MyString str;

		iss >> str;

		REQUIRE(iss);
		REQUIRE(str == "What");
	}

	SECTION("Leading whitespaces present and skipws flag is unset")
	{
		std::istringstream iss("  \t\n\  What a good idea.");
		MyString str;

		iss >> std::noskipws >> str;

		REQUIRE(!iss);
		REQUIRE(str == "");
	}
}

TEST_CASE("Test ostream << operator overload for MyString")
{
	SECTION("Output string without null chars in the middle")
	{
		std::ostringstream oss;
		MyString str("The flows of magic are whimsical today.");

		oss << str;

		REQUIRE(oss.str() == "The flows of magic are whimsical today.");
	}

	SECTION("Output string with null chars in the middle")
	{
		std::ostringstream oss;
		MyString str("The flows\0of magic are\0whimsical today.");

		oss << str;

		REQUIRE(oss.str() == "The flows\0of magic are\0whimsical today.");
	}
}
