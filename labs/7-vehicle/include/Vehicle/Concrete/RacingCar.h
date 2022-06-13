#pragma once
#include "..\Impl\VehicleImpl.hpp"
#include "..\Impl\CarImpl.h"
#include "..\IRacingCar.h"
#include "..\..\Person\IRacer.h"

class RacingCar : public CarImpl<VehicleImpl<IRacingCar, IRacer>>
{
public:
	RacingCar(size_t placeCount, MakeOfCar makeOfCar);
};