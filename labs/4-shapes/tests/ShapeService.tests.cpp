#include "ShapeService.h"
#include "catch2/catch.hpp"
#include <sstream>

TEST_CASE("ReadShapeData reads data from istream and saves the object")
{
	ShapeService service;
	std::ostringstream oss;

	SECTION("Read data with invalid shape type")
	{
		std::istringstream iss("upyachka 0 0 3 4 00FF00");
		REQUIRE(!service.ReadShapeData(iss));
	}

	SECTION("Read line segment data")
	{
		std::istringstream iss("line 0 0 3 4 00FF00");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.GetShapeAt(0));
		REQUIRE(oss.str() == "type: line segment\nstart point:\n\tx: 0\ty: 0\nend point:\n\tx: 3\ty: 4\nlength: 5.00\noutline color: 00FF00\n");
	}

	SECTION("Read invalid line segment data")
	{
		std::istringstream iss("line 0 0 3");
		REQUIRE(!service.ReadShapeData(iss));
	}

	SECTION("Read triangle data")
	{
		std::istringstream iss("triangle 0 0 3 4 6 0 00FF00 EEFFAA");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.GetShapeAt(0));
		REQUIRE(oss.str() == "type: triangle\nvertex 1:\n\tx: 0\ty: 0\nvertex 2:\n\tx: 3\ty: 4\nvertex 3:\n\tx: 6\ty: 0\narea: 12.00\nperimeter: 16.00\noutline color: 00FF00\nfill color: EEFFAA\n");
	}

	SECTION("Read rectangle data")
	{
		std::istringstream iss("rectangle 0 10 20 10 00FF33 EEFFBB");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.GetShapeAt(0));
		REQUIRE(oss.str() == "type: rectangle\nleft top:\n\tx: 0\ty: 10\nwidth: 20.00\nheight: 10.00\narea: 200.00\nperimeter: 60.00\noutline color: 00FF33\nfill color: EEFFBB\n");
	}

	SECTION("Read circle data")
	{
		std::istringstream iss("circle 10 10 20 22AA33 CCFFBB");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.GetShapeAt(0));
		REQUIRE(oss.str() == "type: circle\ncenter:\n\tx: 10\ty: 10\nradius: 20.00\narea: 1256.64\nperimeter: 125.66\noutline color: 22AA33\nfill color: CCFFBB\n");
	}
}

TEST_CASE("FindMaxAreaShape finds the shape with max area")
{
	ShapeService service;
	std::ostringstream oss;

	SECTION("If there is no shapes")
	{
		service.PrintShapeInfo(oss, service.FindMaxAreaShape());
		REQUIRE(oss.str() == "Failed to print shape data.\n");
	}

	SECTION("If there is single shape")
	{
		std::istringstream iss("rectangle 0 10 20 10 00FF33 EEFFBB");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.FindMaxAreaShape());
		REQUIRE(oss.str() == "type: rectangle\nleft top:\n\tx: 0\ty: 10\nwidth: 20.00\nheight: 10.00\narea: 200.00\nperimeter: 60.00\noutline color: 00FF33\nfill color: EEFFBB\n");
	}

	SECTION("Find max area rectangle: first rect area = 50, second = 100, third = 15")
	{
		std::istringstream iss("rectangle 1 3 10 5 00FF33 EEFFBB\nrectangle 5 -6 10 10 00FF33 EEFFBB\nrectangle -7 4 1 15 00FF33 EEFFBB");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.FindMaxAreaShape());
		REQUIRE(oss.str() == "type: rectangle\nleft top:\n\tx: 5\ty: -6\nwidth: 10.00\nheight: 10.00\narea: 100.00\nperimeter: 40.00\noutline color: 00FF33\nfill color: EEFFBB\n");
	}

	SECTION("Find max area circle among other shape types: first rect area = 50, second triangle = 12, third circle = 706.86")
	{
		std::istringstream iss("rectangle 1 3 10 5 00FF33 EEFFBB\ntriangle 0 0 3 4 6 0 00FF33 EEFFBB\ncircle 0 0 15 00FF33 EEFFBB");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.FindMaxAreaShape());
		REQUIRE(oss.str() == "type: circle\ncenter:\n\tx: 0\ty: 0\nradius: 15.00\narea: 706.86\nperimeter: 94.25\noutline color: 00FF33\nfill color: EEFFBB\n");
	}
}

TEST_CASE("FindMinPerimeterShape finds the shape with min perimeter")
{
	ShapeService service;
	std::ostringstream oss;

	SECTION("If there is no shapes")
	{
		service.PrintShapeInfo(oss, service.FindMinPerimeterShape());
		REQUIRE(oss.str() == "Failed to print shape data.\n");
	}

	SECTION("If there is single shape")
	{
		std::istringstream iss("rectangle 0 10 20 10 00FF33 EEFFBB");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.FindMinPerimeterShape());
		REQUIRE(oss.str() == "type: rectangle\nleft top:\n\tx: 0\ty: 10\nwidth: 20.00\nheight: 10.00\narea: 200.00\nperimeter: 60.00\noutline color: 00FF33\nfill color: EEFFBB\n");
	}

	SECTION("Find min perimeter rectangle: first rect perim = 30, second = 40, third = 32")
	{
		std::istringstream iss("rectangle 1 3 10 5 00FF33 EEFFBB\nrectangle 5 -6 10 10 00FF33 EEFFBB\nrectangle -7 4 1 15 00FF33 EEFFBB");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.FindMinPerimeterShape());
		REQUIRE(oss.str() == "type: rectangle\nleft top:\n\tx: 1\ty: 3\nwidth: 10.00\nheight: 5.00\narea: 50.00\nperimeter: 30.00\noutline color: 00FF33\nfill color: EEFFBB\n");
	}

	SECTION("Find min perimeter triangle among other shape types: first rect perim = 30, second triangle = 16, third circle = 94.25")
	{
		std::istringstream iss("rectangle 1 3 10 5 00FF33 EEFFBB\ntriangle 0 0 3 4 6 0 00FF33 EEFFBB\ncircle 0 0 15 00FF33 EEFFBB");
		REQUIRE(service.ReadShapeData(iss));
		service.PrintShapeInfo(oss, service.FindMinPerimeterShape());
		REQUIRE(oss.str() == "type: triangle\nvertex 1:\n\tx: 0\ty: 0\nvertex 2:\n\tx: 3\ty: 4\nvertex 3:\n\tx: 6\ty: 0\narea: 12.00\nperimeter: 16.00\noutline color: 00FF33\nfill color: EEFFBB\n");
	}
}