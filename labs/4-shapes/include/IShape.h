#pragma once
#include <string>
#include <iomanip>

constexpr int outputPrecision = 2;

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
};
