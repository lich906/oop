#include "Point.h"
#include <sstream>

bool Point::operator==(const Point& other) const
{
	return (this->x == other.x) && (this->y == other.y);
}

std::string Point::ToString() const
{
	std::ostringstream oss;

	oss << "\tx: " << x << "\ty: " << y;

	return oss.str();
}
