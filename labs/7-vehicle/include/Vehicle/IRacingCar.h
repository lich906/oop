#pragma once
#include "..\Person\IRacer.h"
#include "ICar.h"

class IRacingCar : public ICar<IRacer>
{
};