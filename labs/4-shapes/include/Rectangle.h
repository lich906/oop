#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Rectangle : public ISolidShape
{
public:
	Rectangle(Point leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	Point m_leftTop;
	double m_width;
	double m_height;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
