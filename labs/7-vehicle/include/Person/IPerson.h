#pragma once
#include <string>

class IPerson
{
public:
	virtual std::string GetName() const = 0;
};
