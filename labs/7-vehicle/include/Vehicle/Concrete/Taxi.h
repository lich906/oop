#pragma once
#include "..\Impl\VehicleImpl.hpp"
#include "..\Impl\CarImpl.h"
#include "..\ITaxi.h"
#include "..\..\Person\IPerson.h"

class Taxi : public CarImpl<VehicleImpl<ITaxi, IPerson>>
{
public:
	Taxi(size_t placeCount, MakeOfCar makeOfCar);
};