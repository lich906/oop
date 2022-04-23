#include <catch2/catch.hpp>
#include <fakeit/fakeit.hpp>
#include "ICanvas.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

using namespace fakeit;

std::ostream& operator<<(std::ostream& stream, const Point& p)
{
	return stream << "{ " << p.x << ", " << p.y << " }";
}

TEST_CASE("Drawing line")
{
	Mock<ICanvas> mock;

	Fake(Method(mock, DrawLine));

	Point start(1, 3), end(4, 5);
	uint32_t outlineColor = 0xEEAAFFFF;
	LineSegment line(start, end, outlineColor);

	line.Draw(mock.get());

	auto matchingArguments = [&](const Point& from, const Point& to, uint32_t color) -> bool {
		return (from == start) && (to == end) && (color == outlineColor);
	};

	Verify(Method(mock, DrawLine).Matching(matchingArguments)).Once();
}

TEST_CASE("Drawing triangle")
{
	Mock<ICanvas> mock;

	Fake(Method(mock, FillPolygon));
	Fake(Method(mock, DrawLine));

	Point vertex1(1, 3), vertex2(4, 5), vertex3(9, -4);
	uint32_t outlineColor = 0xEEAAFFFF, fillColor = 0xAABBCCFF;
	Triangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

	triangle.Draw(mock.get());

	SECTION("Verifying FillPolygon invocation")
	{
		Verify(Method(mock, FillPolygon).Using(Any<std::vector<Point>>(), fillColor)).Once();
	}

	SECTION("Verifying DrawLine invocation from vertex1 to vertex2")
	{
		Verify(Method(mock, DrawLine).Using(vertex1, vertex2, outlineColor)).Once();
	}

	SECTION("Verifying DrawLine invocation from vertex2 to vertex3")
	{
		Verify(Method(mock, DrawLine).Using(vertex2, vertex3, outlineColor)).Once();
	}

	SECTION("Verifying DrawLine invocation from vertex3 to vertex1")
	{
		Verify(Method(mock, DrawLine).Using(vertex3, vertex1, outlineColor)).Once();
	}
}

TEST_CASE("Drawing rectangle")
{
	Mock<ICanvas> mock;

	Fake(Method(mock, FillPolygon));
	Fake(Method(mock, DrawLine));

	Point leftTop(1.0, 3.0);
	double width = 20.0, height = 30.0;
	uint32_t outlineColor = 0xEEAAFFFF, fillColor = 0xAABBCCFF;
	Rectangle rectangle(leftTop, width, height, outlineColor, fillColor);

	rectangle.Draw(mock.get());

	SECTION("Verifying FillPolygon invocation")
	{
		Verify(Method(mock, FillPolygon).Using(Any<std::vector<Point>>(), fillColor)).Once();
	}

	SECTION("Verifying DrawLine invocations")
	{
		Verify(Method(mock, DrawLine).Using(_, _, outlineColor)).Exactly(4);
	}
}

TEST_CASE("Drawing circle")
{
	Mock<ICanvas> mock;

	Fake(Method(mock, DrawCircle));
	Fake(Method(mock, FillCircle));

	Point center(10, 30);
	double radius = 15;
	uint32_t outlineColor = 0xEEAAFFFF, fillColor = 0xAABBCCFF;
	Circle circle(center, radius, outlineColor, fillColor);

	circle.Draw(mock.get());

	SECTION("Verify DrawCircle")
	{
		Verify(Method(mock, DrawCircle).Using(center, radius, outlineColor)).Once();
	}

	SECTION("Verify FillCircle")
	{
		Verify(Method(mock, FillCircle).Using(center, radius, fillColor)).Once();
	}
}
