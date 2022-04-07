#include <catch2/catch.hpp>
#include <VariablesContainer.h>

TEST_CASE("Variables declaration")
{
	VariablesContainer container;

	SECTION("Declaring new variable")
	{
		CHECK(!container.ContainsIdentifier("var"));

		Result res = container.DeclareNew("var");

		CHECK(res.status == ResultStatus::OK);

		CHECK(container.ContainsIdentifier("var"));
	}

	SECTION("Declaring existing variable")
	{
		container.DeclareNew("var");

		CHECK(container.ContainsIdentifier("var"));

		Result res = container.DeclareNew("var");

		CHECK(res.status == ResultStatus::Error);
	}
}
