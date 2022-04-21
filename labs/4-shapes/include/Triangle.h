#pragma once
#include "ISolidShape.h"
#include <Point.h>
class Triangle : public ISolidShape
{
public:
	Triangle(Point vertex1, Point vertex2, Point vertex3, uint32_t outlineColor, uint32_t fillColor)
		: m_vertex{ vertex1, vertex2, vertex3 }
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_vertex[3];
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
