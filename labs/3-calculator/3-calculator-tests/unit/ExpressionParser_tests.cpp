#include <catch2/catch.hpp>
#include <ExpressionParser.h>

TEST_CASE("Parsing invalid command")
{
	ExpressionParser parser;
	ExpressionParser::Expression expr;

	REQUIRE(parser.Parse("hello b=5", expr).status == ResultStatus::Error);

	REQUIRE(parser.Parse("var 34g8", expr).status == ResultStatus::Error);

	REQUIRE(parser.Parse("let 40gk=erg", expr).status == ResultStatus::Error);

	REQUIRE(parser.Parse("printvarsdr", expr).status == ResultStatus::Error);
}

TEST_CASE("Parsing print commands")
{
	ExpressionParser parser;
	ExpressionParser::Expression expr;

	SECTION("Parse 'print'")
	{
		REQUIRE(parser.Parse("print ab", expr).status == ResultStatus::OK);
		REQUIRE(expr.type == ExpressionParser::ExprType::Print);
		REQUIRE(expr.identifiers[0] == "ab");
	}

	SECTION("Parse 'printvars'")
	{
		REQUIRE(parser.Parse("printvars", expr).status == ResultStatus::OK);
		REQUIRE(expr.type == ExpressionParser::ExprType::Printvars);
		REQUIRE(expr.identifiers.empty());
	}

	SECTION("Parse 'printfns'")
	{
		REQUIRE(parser.Parse("printfns", expr).status == ResultStatus::OK);
		REQUIRE(expr.type == ExpressionParser::ExprType::Printfns);
		REQUIRE(expr.identifiers.empty());
	}

	SECTION("Parse 'var'")
	{
		REQUIRE(parser.Parse("var abc", expr).status == ResultStatus::OK);

		REQUIRE(expr.type == ExpressionParser::ExprType::Var);
		REQUIRE(expr.identifiers.size() == 1);
		REQUIRE(expr.identifiers[0] == "abc");

		// Invalid identifier
		REQUIRE(parser.Parse("var 9834gh", expr).status == ResultStatus::Error);
	}

	SECTION("Parse 'let'")
	{
		REQUIRE(parser.Parse("let b=6", expr).status == ResultStatus::OK);

		REQUIRE(expr.type == ExpressionParser::ExprType::Let);
		REQUIRE(expr.identifiers.size() == 1);
		REQUIRE(expr.identifiers[0] == "b");
		REQUIRE(expr.value.has_value());
		REQUIRE(*expr.value == 6);
	}
}