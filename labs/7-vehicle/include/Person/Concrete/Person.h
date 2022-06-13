#pragma once
#include "Person\Impl\PersonImpl.hpp"
#include "Person\IPerson.h"

class Person : public PersonImpl<IPerson>
{
public:
	Person(std::string name);
};