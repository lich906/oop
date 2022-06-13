#pragma once
#include "Person\Impl\PersonImpl.hpp"
#include "Person\IPoliceMan.h"

class PoliceMan : public PersonImpl<IPoliceMan>
{
public:
	PoliceMan(std::string name, std::string departmentName);

	std::string GetDepartmentName() const override;

private:
	std::string m_departmentName;
};