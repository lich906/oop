#pragma once
#include "..\Person\IPerson.h"
#include "ICar.h"

class ITaxi : public ICar<IPerson>
{
};