#include "Person/Concrete/Racer.h"

Racer::Racer(std::string name, size_t awardsCount)
	: PersonImpl(name)
	, m_awardsCount(awardsCount)
{
}

size_t Racer::GetAwardsCount() const
{
	return m_awardsCount;
}
