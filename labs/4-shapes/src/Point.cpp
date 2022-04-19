#include "Point.h"
#include <sstream>

std::string Point::ToString() const
{
	std::ostringstream oss;

	oss << "\tx: " << x << "\ty: " << y;

	return oss.str();
}
