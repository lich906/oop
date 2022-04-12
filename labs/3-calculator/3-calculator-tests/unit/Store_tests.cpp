#include <catch2/catch.hpp>
#include <Store.h>

TEST_CASE("Declaring variable")
{
	Store store;

	SECTION("Declaring new variable")
	{
		REQUIRE(!store.ContainsIdentifier("something"));

		REQUIRE(store.DeclareVariable("something").status == ResultStatus::OK);

		REQUIRE(store.ContainsIdentifier("something"));
	}

	SECTION("Declaring existing variable")
	{
		REQUIRE(!store.ContainsIdentifier("beans"));

		REQUIRE(store.DeclareVariable("beans").status == ResultStatus::OK);

		REQUIRE(store.DeclareVariable("beans").status == ResultStatus::Error);
	}
}

TEST_CASE("Getting variable's value")
{
	Store store;
	std::optional<double> value;

	SECTION("Get value of undeclared variable, expect error result status")
	{
		REQUIRE(!store.ContainsIdentifier("volume"));

		REQUIRE(store.GetValue("volume", value).status == ResultStatus::Error);
	}

	SECTION("Get value of uninitialized variable, expect no value")
	{
		REQUIRE(store.DeclareVariable("mass").status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("mass"));

		REQUIRE(store.GetValue("mass", value).status == ResultStatus::OK);

		REQUIRE(!value.has_value());
	}
}

TEST_CASE("Assigning value to variable")
{
	Store store;
	std::optional<double> value;

	SECTION("Assign constant number to uninitialized variable")
	{
		REQUIRE(!store.ContainsIdentifier("length"));

		REQUIRE(store.DeclareVariable("length").status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("length"));

		REQUIRE(store.GetValue("length", value).status == ResultStatus::OK);
		REQUIRE(!value.has_value());

		REQUIRE(store.AssignValueToVariable("length", 3.45).status == ResultStatus::OK);

		REQUIRE(store.GetValue("length", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 3.45);
	}

	SECTION("Assign constant number to undeclared variable, expect variable will be declared and initialized")
	{
		REQUIRE(!store.ContainsIdentifier("height"));

		REQUIRE(store.AssignValueToVariable("height", 45.2).status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("height"));

		REQUIRE(store.GetValue("height", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 45.2);
	}

	SECTION("Assign UNINITIALIZED variable's value to another UNDECLARED variable")
	{
		REQUIRE(!store.ContainsIdentifier("foo"));
		REQUIRE(!store.ContainsIdentifier("bar"));

		REQUIRE(store.DeclareVariable("foo").status == ResultStatus::OK);

		REQUIRE(store.GetValue("foo", value).status == ResultStatus::OK);
		REQUIRE(!value.has_value());

		REQUIRE(store.ContainsIdentifier("foo"));
		REQUIRE(!store.ContainsIdentifier("bar"));

		REQUIRE(store.AssignValueToVariable("bar", "foo").status == ResultStatus::OK);

		REQUIRE(store.ContainsIdentifier("bar"));

		REQUIRE(store.GetValue("bar", value).status == ResultStatus::OK);
		REQUIRE(!value.has_value());
	}

	SECTION("Assign UNINITIALIZED 'foo' variable's value to another INITIALIZED variable 'bar'")
	{
		REQUIRE(!store.ContainsIdentifier("foo"));
		REQUIRE(!store.ContainsIdentifier("bar"));

		REQUIRE(store.DeclareVariable("foo").status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("foo"));

		REQUIRE(store.AssignValueToVariable("bar", 66.7).status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("bar"));

		REQUIRE(store.GetValue("bar", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 66.7);

		REQUIRE(store.AssignValueToVariable("bar", "foo").status == ResultStatus::OK);

		REQUIRE(store.GetValue("bar", value).status == ResultStatus::OK);
		REQUIRE(!value.has_value());
	}

	SECTION("Assign INITIALIZED 'bar' variable's value to another UNDECLARED variable 'foo'")
	{
		REQUIRE(!store.ContainsIdentifier("foo"));
		REQUIRE(!store.ContainsIdentifier("bar"));

		REQUIRE(store.AssignValueToVariable("bar", -32.7).status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("bar"));

		REQUIRE(store.GetValue("bar", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == -32.7);

		REQUIRE(store.AssignValueToVariable("foo", "bar").status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("foo"));

		REQUIRE(store.GetValue("foo", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == -32.7);
	}

	SECTION("Assign UNDECLARED variable's value, expect error result status")
	{
		REQUIRE(!store.ContainsIdentifier("foo"));

		REQUIRE(store.AssignValueToVariable("bar", "foo").status == ResultStatus::Error);
	}

	SECTION("Assign value of var 'foo' to var 'bar' and change 'foo' variable's value")
	{
		REQUIRE(store.AssignValueToVariable("bar", -32.7).status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("bar"));

		REQUIRE(store.AssignValueToVariable("foo", 4.2).status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("foo"));

		REQUIRE(store.AssignValueToVariable("bar", "foo").status == ResultStatus::OK);

		REQUIRE(store.AssignValueToVariable("foo", 56.6).status == ResultStatus::OK);

		REQUIRE(store.GetValue("bar", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 4.2);

		REQUIRE(store.GetValue("foo", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 56.6);
	}
}

TEST_CASE("Declaring function")
{
	Store store;

	SECTION("Declare function with single undeclared variable, expect error result status")
	{
		REQUIRE(!store.ContainsIdentifier("fooFn"));
		REQUIRE(!store.ContainsIdentifier("unknown"));

		REQUIRE(store.DeclareFunction("fooFn", "unknown").status == ResultStatus::Error);
	}

	SECTION("Declare function with existing variable identifier, expect error result status")
	{
		REQUIRE(store.DeclareVariable("bar").status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("bar"));

		REQUIRE(store.DeclareVariable("foo").status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("foo"));

		REQUIRE(store.DeclareFunction("bar", "foo").status == ResultStatus::Error);
	}

	SECTION("Declare same function more than ones")
	{
		REQUIRE(!store.ContainsIdentifier("bar"));
		REQUIRE(store.DeclareVariable("bar").status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("bar"));

		REQUIRE(store.DeclareFunction("foo", "bar").status == ResultStatus::OK);

		REQUIRE(store.DeclareFunction("foo", "bar", Function::Operation::Add, "bar").status == ResultStatus::Error);
	}

	SECTION("Declare function with undeclared parameters")
	{
		REQUIRE(!store.ContainsIdentifier("bar"));
		REQUIRE(store.DeclareFunction("fooFunc", "bar").status == ResultStatus::Error);
		REQUIRE(!store.ContainsIdentifier("fooFunc"));

		REQUIRE(store.DeclareVariable("bar").status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("bar"));

		REQUIRE(store.DeclareFunction("fooFunc", "bar", Function::Operation::Mul, "x").status == ResultStatus::Error);
		REQUIRE(!store.ContainsIdentifier("fooFunc"));
	}

	SECTION("Try declare recursive function")
	{
		REQUIRE(!store.ContainsIdentifier("f"));
		REQUIRE(store.AssignValueToVariable("v", 6).status == ResultStatus::OK);
		REQUIRE(store.DeclareFunction("f", "f", Function::Operation::Mul, "v").status == ResultStatus::Error);
	}
}

TEST_CASE("Getting value of functions")
{
	Store store;
	std::optional<double> value;

	SECTION("Get value of function of one variable")
	{
		REQUIRE(!store.ContainsIdentifier("bar"));
		REQUIRE(store.AssignValueToVariable("bar", 4).status == ResultStatus::OK);
		REQUIRE(store.ContainsIdentifier("bar"));
		REQUIRE(store.GetValue("bar", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 4);

		REQUIRE(store.DeclareFunction("fooFunc", "bar").status == ResultStatus::OK);
		REQUIRE(store.GetValue("fooFunc", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 4);

		REQUIRE(store.AssignValueToVariable("bar", -8).status == ResultStatus::OK);

		REQUIRE(store.GetValue("fooFunc", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == -8);
		REQUIRE(store.GetValue("bar", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == -8);
	}

	SECTION("tripleA=doubleA+A, doubleA=A+A, A=5 then changed to A=10")
	{
		REQUIRE(!store.ContainsIdentifier("A"));
		REQUIRE(store.AssignValueToVariable("A", 5).status == ResultStatus::OK);
		REQUIRE(store.GetValue("A", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 5);

		REQUIRE(store.DeclareFunction("doubleA", "A", Function::Operation::Add, "A").status == ResultStatus::OK);
		REQUIRE(store.GetValue("doubleA", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 10);

		REQUIRE(store.DeclareFunction("tripleA", "doubleA", Function::Operation::Add, "A").status == ResultStatus::OK);
		REQUIRE(store.GetValue("tripleA", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 15);

		REQUIRE(store.AssignValueToVariable("A", 10).status == ResultStatus::OK);
		REQUIRE(store.GetValue("doubleA", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 20);

		REQUIRE(store.GetValue("tripleA", value).status == ResultStatus::OK);
		REQUIRE(value.has_value());
		REQUIRE(*value == 30);
	}
}