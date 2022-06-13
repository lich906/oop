#include "Person/Concrete/PoliceMan.h"

PoliceMan::PoliceMan(std::string name, std::string departmentName)
	: PersonImpl(name)
	, m_departmentName(departmentName)
{
}

std::string PoliceMan::GetDepartmentName() const
{
	return m_departmentName;
}
