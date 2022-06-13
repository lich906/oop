#pragma once
#include "..\Person\IPoliceMan.h"
#include "ICar.h"

class IPoliceCar : public ICar<IPoliceMan>
{
};
