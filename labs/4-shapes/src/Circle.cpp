#include "Circle.h"
#include "misc.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>


double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string Circle::ToString() const
{
	std::ostringstream oss;

	oss << std::setprecision(outputPrecision) << std::fixed;

	oss << "type: circle" << std::endl
		<< "center:" << std::endl
		<< m_center.ToString() << std::endl
		<< "radius: " << m_radius << std::endl
		<< "area: " << GetArea() << std::endl
		<< "perimeter: " << GetPerimeter() << std::endl 
		<< "outline color: " << GetColorHexString(m_outlineColor) << std::endl
		<< "fill color: " << GetColorHexString(m_fillColor) << std::endl;

	return oss.str();
}

uint32_t Circle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Circle::GetFillColor() const
{
	return m_fillColor;
}
