#include "catch2/catch.hpp"
#include "Complex.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

TEST_CASE("Creating complex number")
{
	SECTION("Create complex number with real and imaginary part initialization")
	{
		Complex cplx(4, -2);

		REQUIRE(cplx.Re() == 4);
		REQUIRE(cplx.Im() == -2);
	}

	SECTION("Create complex number with real part initialization")
	{
		Complex cplx(4);

		REQUIRE(cplx.Re() == 4);
		REQUIRE(cplx.Im() == 0);

		Complex cplx2 = 4;

		REQUIRE(cplx2.Re() == 4);
		REQUIRE(cplx2.Im() == 0);
	}
}

TEST_CASE("Get magnitude of complex number")
{
	SECTION("Magnitude of real number is number it is")
	{
		Complex real = 6.54;

		REQUIRE(real.GetMagnitude() == 6.54);
	}

	SECTION("Magnitude of complex number with imaginary part")
	{
		Complex cplx(3, 4);

		REQUIRE(cplx.GetMagnitude() == 5);
	}
}

TEST_CASE("Get argument of complex number")
{
	SECTION("Argument of positive real number must be 0")
	{
		Complex real = 5;

		REQUIRE(real.GetArgument() == 0);
	}

	SECTION("Argument of negative real number must be PI")
	{
		Complex real = -3;

		REQUIRE(real.GetArgument() == M_PI);
	}

	SECTION("Argument of complex number with positive imaginary part only must be PI/2")
	{
		Complex cplx(0, 4);

		REQUIRE(cplx.GetArgument() == M_PI_2);
	}

	SECTION("Argument of complex number with negative imaginary part only must be -PI/2")
	{
		Complex cplx(0, -3);

		REQUIRE(cplx.GetArgument() == -M_PI_2);
	}

	SECTION("Argument of (2 + 2i) must be PI/4")
	{
		Complex cplx(2, 2);

		REQUIRE_THAT(cplx.GetArgument(), Catch::Matchers::WithinRel(M_PI_4, 0.0000001));
	}

	SECTION("Argument of (2 - 2i) must be PI/4")
	{
		Complex cplx(2, -2);

		REQUIRE_THAT(cplx.GetArgument(), Catch::Matchers::WithinRel(-M_PI_4, 0.0000001));
	}

	SECTION("Argument of (-2 + 2i) must be 3*PI/4")
	{
		Complex cplx(-2, 2);

		REQUIRE_THAT(cplx.GetArgument(), Catch::Matchers::WithinRel(3 * M_PI_4, 0.0000001));
	}

	SECTION("Argument of (-2 - 2i) must be -3*PI/4")
	{
		Complex cplx(-2, -2);

		REQUIRE_THAT(cplx.GetArgument(), Catch::Matchers::WithinRel(-3 * M_PI_4, 0.0000001));
	}
}

TEST_CASE("Check equations of two complex numbers")
{
	SECTION("Equation of complex and real number")
	{
		REQUIRE(Complex(4, 0) == 4);
		REQUIRE(2 == Complex(2));

		REQUIRE(5 != Complex(5, 2));
		REQUIRE(Complex(2) != 9);
	}

	SECTION("Equation of two complex numbers")
	{
		REQUIRE(Complex(4, -2) == Complex(4, -2));
		REQUIRE(Complex(3, 9.1) != Complex(3, 4));
	}
}

TEST_CASE("Addition of complex numbers")
{
	SECTION("Add real number to complex number")
	{
		Complex z(2, 3);

		Complex result = z + 4;
		REQUIRE(result == Complex(6, 3));

		result = 6 + z;
		REQUIRE(result == Complex(8, 3));

		Complex result2;
		result2 += 5;
		REQUIRE(result2 == Complex(5, 0));
	}

	SECTION("Add up complex numbers")
	{
		Complex x(3, -5), y(2, 7);

		Complex result = x + y + Complex(3, -1);
		REQUIRE(result == Complex(8, 1));

		REQUIRE(x == Complex(3, -5));
		result = x += y;
		REQUIRE(x == Complex(5, 2));
		REQUIRE(result == Complex(5, 2));
	}
}

TEST_CASE("Subtraction of complex numbers")
{
	SECTION("Subtract real number from complex number")
	{
		Complex z(6, 3);

		Complex result = z - 5;
		REQUIRE(result == Complex(1, 3));

		z -= 5;
		REQUIRE(z == Complex(1, 3));
	}

	SECTION("Subtract complex number from real number")
	{
		Complex z(3.2, 1);

		Complex result = 7 - z - Complex(0, 3);
		REQUIRE(result == Complex(3.8, -4));
	}

	SECTION("Subtract complex number from complex number")
	{
		Complex x(6, 7), y(5, -2);

		Complex result = x - y;
		REQUIRE(result == Complex(1, 9));

		result = y -= x - Complex(-2, 1);
		REQUIRE(y == Complex(-3, -8));
		REQUIRE(result == Complex(-3, -8));
	}
}

TEST_CASE("Test unary plus and minus")
{
	SECTION("Assign inverse complex number")
	{
		Complex source(5, -3);

		Complex inverse = -source;
		REQUIRE(inverse == Complex(-5, 3));
	}

	SECTION("Addition of number with its inverse must be zero element")
	{
		Complex z(5, 4);

		Complex result1 = -z + z;
		REQUIRE(result1 == 0);

		Complex result2 = z + -z;
		REQUIRE(result2 == 0);
	}

	SECTION("Unary plus")
	{
		Complex source(7, 2);

		Complex dest = +source;
		REQUIRE(dest == source);
	}
}

TEST_CASE("Multiplication of complex numbers")
{
	SECTION("Multiply complex number and real number")
	{
		Complex z(3, 4);

		Complex result = z * 5;
		REQUIRE(result == Complex(15, 20));
		REQUIRE(z == Complex(3, 4));

		result = 2 * z;
		REQUIRE(result == Complex(6, 8));
	}

	SECTION("Zero property z * 0 = 0")
	{
		Complex z(5, 2);

		Complex result = z * 0;
		REQUIRE(result == 0);
	}

	SECTION("Unit property z * 1 = z")
	{
		Complex z(5, 2);

		Complex result = z * 1;
		REQUIRE(result == z);
	}

	SECTION("Commutative property")
	{
		Complex x(3, 4), y(2, 3);

		Complex result1 = x * y;
		Complex result2 = y * x;
		REQUIRE(result1 == result2);
	}

	SECTION("Associative property")
	{
		Complex x(3, 4.5), y(2, 3.31), z(-4, 2.2);

		Complex result1 = (x * y) * z;
		Complex result2 = x * (y * z);
		REQUIRE(result1 == result2);
	}

	SECTION("Distributive property")
	{
		Complex x(3.2, 2.1), y(2, 0.31), z(-4, 2.2);

		Complex result1 = x * (y + z);
		Complex result2 = x * y + x * z;
		REQUIRE(result1 == result2);
	}
}

TEST_CASE("Division of complex numbers")
{
	SECTION("Divide complex number by real number")
	{
		Complex z(4, 4);

		Complex result = z / 2;
		REQUIRE(result == Complex(2, 2));
	}

	SECTION("Divide two complex numbers")
	{
		Complex x(3, 2), y(2, 4);

		Complex result = x / y;
		REQUIRE(result == Complex(0.7, -0.4));
	}

	SECTION("Assigning division complex number by real number")
	{
		Complex z(6, 8);

		z /= 2;
		REQUIRE(z == Complex(3, 4));
	}

	SECTION("Assigning division complex number by real number")
	{
		Complex z(20, 56);

		z /= Complex(-5, 3);
		REQUIRE(z == Complex(2, -10));
	}
}

TEST_CASE("Output complex numbers to ostream")
{
	std::ostringstream oss;
	SECTION("With negative imaginary part")
	{
		Complex z(6, -9.84);

		oss << z;
		REQUIRE(oss.str() == "6-9.84i");
	}

	SECTION("With positive imaginary part")
	{
		Complex z(-4, 7.2);

		oss << z;
		REQUIRE(oss.str() == "-4+7.2i");
	}
}

TEST_CASE("Input complex number from istream")
{
	Complex z;

	SECTION("Read number without imaginary part")
	{
		std::istringstream input("23hf");

		input >> z;
		REQUIRE(z == Complex(23, 0));
		REQUIRE(z == 23.0);
	}

	SECTION("Read complex number with imaginary part")
	{
		std::istringstream input("3+45i");

		input >> z;
		REQUIRE(z == Complex(3, 45));
	}

	SECTION("Read real number followed with another number after whitespace")
	{
		std::istringstream input("3 34i");

		input >> z;
		REQUIRE(z == 3);
		REQUIRE(z == Complex(3, 0));
	}

	SECTION("Read several complex numbers separated with whitespace")
	{
		Complex x, y;

		std::istringstream input("5+3i 8-6i 32.4-23.98i");

		input >> z >> x >> y;
		REQUIRE(z == Complex(5, 3));
		REQUIRE(x == Complex(8, -6));
		REQUIRE(y == Complex(32.4, -23.98));
	}
}