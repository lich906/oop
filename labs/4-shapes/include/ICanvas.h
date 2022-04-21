#pragma once
#include "Point.h"
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(const Point& from, const Point& to, uint32_t lineColor) = 0;
	virtual void FillPolygon(const std::vector<Point>& points, uint32_t fillColor) = 0;
	virtual void DrawCircle(const Point& center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(const Point& center, double radius, uint32_t fillColor) = 0;
};