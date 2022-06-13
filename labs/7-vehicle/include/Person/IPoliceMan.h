#pragma once
#include "IPerson.h"

class IPoliceMan : public IPerson
{
public:
	virtual std::string GetDepartmentName() const = 0;
};