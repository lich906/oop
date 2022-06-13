#pragma once
#include "..\IPerson.h"

template<typename Base>
class PersonImpl : public Base
{
public:
	std::string GetName() const final
	{
		return m_name;
	}

protected:
	PersonImpl(std::string name)
		: m_name(std::move(name))
	{
	}

	~PersonImpl() = default;

	std::string m_name;
};