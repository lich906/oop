#pragma once
#include <string>

class Point
{
public:
	Point(double x, double y)
		: x(x)
		, y(y)
	{
	}

	double x;
	double y;

	std::string ToString() const;
};
