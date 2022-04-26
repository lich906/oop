#pragma once
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include <iostream>
#include <vector>
#include <map>
#include <memory>

class ShapeService
{
public:
	enum class ShapeType
	{
		LineSegment,
		Triangle,
		Rectangle,
		Circle
	};

	bool ReadShapeData(std::istream& input);
	void PrintMaxAreaShapeInfo(std::ostream& output) const;
	void PrintMinPerimeterShapeInfo(std::ostream& output) const;

	void DrawAll(ICanvas& canvas) const;

private:
	std::shared_ptr<IShape> FindMaxAreaShape() const;
	std::shared_ptr<IShape> FindMinPerimeterShape() const;

	bool ReadLineSegmentData(std::istream& input);
	bool ReadTriangleData(std::istream& input);
	bool ReadRectangleData(std::istream& input);
	bool ReadCircleData(std::istream& input);

	std::vector<std::shared_ptr<IShape>> m_shapes;
};
