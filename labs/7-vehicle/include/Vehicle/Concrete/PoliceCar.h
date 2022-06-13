#pragma once
#include "..\Impl\VehicleImpl.hpp"
#include "..\Impl\CarImpl.h"
#include "..\IPoliceCar.h"
#include "..\..\Person\IPoliceMan.h"

class PoliceCar : public CarImpl<VehicleImpl<IPoliceCar, IPoliceMan>>
{
public:
	PoliceCar(size_t placeCount, MakeOfCar makeOfCar);
};