#include <catch2/catch.hpp>
#include <ExpressionParser.h>

TEST_CASE("Parsing invalid command")
{
	ExpressionParser parser;
	ExpressionParser::CommandData expr;

	REQUIRE(parser.Parse("hello b=5", expr).status == ResultStatus::Error);

	REQUIRE(parser.Parse("var 34g8", expr).status == ResultStatus::Error);

	REQUIRE(parser.Parse("let 40gk=erg", expr).status == ResultStatus::Error);

	REQUIRE(parser.Parse("printvarsdr", expr).status == ResultStatus::Error);
}

TEST_CASE("Parsing print commands")
{
	ExpressionParser parser;
	ExpressionParser::CommandData expr;

	SECTION("Parse 'print'")
	{
		REQUIRE(parser.Parse("print ab", expr).status == ResultStatus::OK);
		REQUIRE(expr.type == ExpressionParser::CommandType::PrintValue);
		REQUIRE(expr.identifiers[0] == "ab");

		REQUIRE(parser.Parse("print", expr).status == ResultStatus::Error);

		REQUIRE(parser.Parse("print 983", expr).status == ResultStatus::Error);
	}

	SECTION("Parse 'printvars'")
	{
		REQUIRE(parser.Parse("printvars", expr).status == ResultStatus::OK);
		REQUIRE(expr.type == ExpressionParser::CommandType::PrintAllVariables);
		REQUIRE(expr.identifiers.empty());
	}

	SECTION("Parse 'printfns'")
	{
		REQUIRE(parser.Parse("printfns", expr).status == ResultStatus::OK);
		REQUIRE(expr.type == ExpressionParser::CommandType::PrintAllFunctions);
		REQUIRE(expr.identifiers.empty());
	}
}

TEST_CASE("Parsing variable commands")
{
	ExpressionParser parser;
	ExpressionParser::CommandData expr;

	SECTION("Parse 'var'")
	{
		REQUIRE(parser.Parse("var abc", expr).status == ResultStatus::OK);

		REQUIRE(expr.type == ExpressionParser::CommandType::DeclareVariable);
		REQUIRE(expr.identifiers.size() == 1);
		REQUIRE(expr.identifiers[0] == "abc");

		REQUIRE(parser.Parse("var 9834gh", expr).status == ResultStatus::Error);
	}

	SECTION("Parse 'let'")
	{
		REQUIRE(parser.Parse("let b=6", expr).status == ResultStatus::OK);

		REQUIRE(expr.type == ExpressionParser::CommandType::AssignVariable);
		REQUIRE(expr.identifiers.size() == 1);
		REQUIRE(expr.identifiers[0] == "b");
		REQUIRE(expr.value.has_value());
		REQUIRE(*expr.value == 6);

		REQUIRE(parser.Parse("let another_variable=b", expr).status == ResultStatus::OK);

		REQUIRE(expr.type == ExpressionParser::CommandType::AssignVariable);
		REQUIRE(expr.identifiers.size() == 2);
		REQUIRE(expr.identifiers[0] == "another_variable");
		REQUIRE(expr.identifiers[1] == "b");
		REQUIRE(!expr.value.has_value());

		REQUIRE(parser.Parse("let +#t=4", expr).status == ResultStatus::Error);
	}
}

TEST_CASE("Parsing function commands")
{
	ExpressionParser parser;
	ExpressionParser::CommandData expr;

	SECTION("Parse function with two parameters")
	{
		REQUIRE(parser.Parse("fn product_of_x_and_y=x*y", expr).status == ResultStatus::OK);

		REQUIRE(expr.type == ExpressionParser::CommandType::DeclareFunction);
		REQUIRE(expr.identifiers.size() == 3);
		REQUIRE(expr.identifiers[0] == "product_of_x_and_y");
		REQUIRE(expr.identifiers[1] == "x");
		REQUIRE(expr.identifiers[2] == "y");
		REQUIRE(!expr.value.has_value());
		REQUIRE(expr.operation.has_value());
		REQUIRE(*expr.operation == '*');
	}

	SECTION("Parse function with one parameter")
	{
		REQUIRE(parser.Parse("fn alias_for_x=x", expr).status == ResultStatus::OK);

		REQUIRE(expr.type == ExpressionParser::CommandType::DeclareFunction);
		REQUIRE(expr.identifiers.size() == 2);
		REQUIRE(expr.identifiers[0] == "alias_for_x");
		REQUIRE(expr.identifiers[1] == "x");
		REQUIRE(!expr.value.has_value());
		REQUIRE(!expr.operation.has_value());
	}
}