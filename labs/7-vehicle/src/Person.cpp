#include "Person/Concrete/Person.h"

Person::Person(std::string name)
	: PersonImpl(std::move(name))
{
}
