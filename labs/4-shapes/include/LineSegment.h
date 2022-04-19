#pragma once
#include "IShape.h"
#include "Point.h"

class LineSegment : public IShape
{
public:
	LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor)
		: m_startPoint(startPoint)
		, m_endPoint(endPoint)
		, m_outlineColor(outlineColor)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	Point GetStartPoint() const;
	Point GetEndPoint() const;

private:
	Point m_startPoint;
	Point m_endPoint;
	uint32_t m_outlineColor;
};
