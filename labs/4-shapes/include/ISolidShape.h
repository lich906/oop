#pragma once
#include "IShape.h"
class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;

protected:
	~ISolidShape() = default;
};
