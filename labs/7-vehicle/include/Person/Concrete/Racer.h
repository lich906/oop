#pragma once
#include "Person\Impl\PersonImpl.hpp"
#include "Person\IRacer.h"

class Racer : public PersonImpl<IRacer>
{
public:
	Racer(std::string name, size_t awardsCount);

	size_t GetAwardsCount() const override;

private:
	size_t m_awardsCount;
};