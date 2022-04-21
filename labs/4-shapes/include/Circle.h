#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Circle : public ISolidShape
{
public:
	Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor)
		: m_center(center)
		, m_radius(radius)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

	Point GetCenter() const;
	double GetRadius() const;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_center;
	double m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
