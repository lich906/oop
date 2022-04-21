#include "Rectangle.h"
#include "misc.h"
#include <sstream>

double Rectangle::GetArea() const
{
	return m_width * m_height;
}

double Rectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

std::string Rectangle::ToString() const
{
	std::ostringstream oss;

	oss << std::setprecision(outputPrecision) << std::fixed;

	oss << "type: rectangle" << std::endl
		<< "left top:" << std::endl
		<< m_leftTop.ToString() << std::endl
		<< "width: " << m_width << std::endl
		<< "height: " << m_height << std::endl
		<< "area: " << GetArea() << std::endl
		<< "perimeter: " << GetPerimeter() << std::endl
		<< "outline color: " << GetColorHexString(m_outlineColor) << std::endl
		<< "fill color: " << GetColorHexString(m_fillColor) << std::endl;

	return oss.str();
}

uint32_t Rectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Rectangle::GetFillColor() const
{
	return m_fillColor;
}

Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return Point(m_leftTop.x + m_width, m_leftTop.y + m_height);
}

double Rectangle::GetWidth() const
{
	return m_width;
}

double Rectangle::GetHeight() const
{
	return m_height;
}

void Rectangle::Draw(ICanvas& canvas) const
{
	Point rightTop(m_leftTop.x + m_width, m_leftTop.y);
	Point leftBottom(m_leftTop.x, m_leftTop.y + m_height);

	canvas.FillPolygon({m_leftTop, rightTop, GetRightBottom(), leftBottom}, m_fillColor);
	canvas.DrawLine(m_leftTop, rightTop, m_outlineColor);
	canvas.DrawLine(rightTop, GetRightBottom(), m_outlineColor);
	canvas.DrawLine(GetRightBottom(), leftBottom, m_outlineColor);
	canvas.DrawLine(m_leftTop, leftBottom, m_outlineColor);
}
