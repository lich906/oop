#pragma once
#include "IVehicle.h"

enum class MakeOfCar
{
	BMW,
	MITSUBISHI,
	FORD,
	MERCEDES,
	TOYOTA,
	KIA,
	FERRARI,
	PORSCHE,
	LEXUS,
	NISSAN,
	INFINITI
};

template <typename Passenger>
class ICar : public IVehicle<Passenger>
{
public:
	virtual MakeOfCar GetMakeOfCar() const = 0;
};
