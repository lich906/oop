#include "LineSegment.h"
#include "misc.h"
#include <sstream>

double LineSegment::GetArea() const
{
	return 0.0;
}

double LineSegment::GetPerimeter() const
{
	return hypot(m_endPoint.x - m_startPoint.x, m_endPoint.y - m_startPoint.y);
}

std::string LineSegment::ToString() const
{
	std::ostringstream oss;

	oss << std::setprecision(outputPrecision) << std::fixed;

	oss << "type: line segment" << std::endl
		<< "start point:" << std::endl
		<< m_startPoint.ToString() << std::endl
		<< "end point:" << std::endl
		<< m_endPoint.ToString() << std::endl
		<< "length: " << GetPerimeter() << std::endl
		<< "outline color: " << GetColorHexString(m_outlineColor) << std::endl;

	return oss.str();
}

uint32_t LineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

Point LineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}
