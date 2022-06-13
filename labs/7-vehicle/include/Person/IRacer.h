#pragma once
#include "IPerson.h"

class IRacer : public IPerson
{
public:
	virtual size_t GetAwardsCount() const = 0;
};