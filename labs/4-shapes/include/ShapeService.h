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
	void PrintShapeInfo(std::ostream& output, const std::weak_ptr<IShape>& shape);
	std::weak_ptr<IShape> GetShapeAt(size_t pos);
	std::weak_ptr<IShape> FindMaxAreaShape();
	std::weak_ptr<IShape> FindMinPerimeterShape();

private:
	bool ReadLineSegmentData(std::istream& input);
	bool ReadTriangleData(std::istream& input);
	bool ReadRectangleData(std::istream& input);
	bool ReadCircleData(std::istream& input);

	std::vector<std::shared_ptr<IShape>> m_shapes;
};
