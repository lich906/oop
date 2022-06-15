#pragma once
#include "..\ICar.h"

template<class VehicleImpl>
class CarImpl : public VehicleImpl
{
public:
	MakeOfCar GetMakeOfCar() const final
	{
		return m_makeOfCar;
	}

protected:
	CarImpl(size_t placeCount, MakeOfCar makeOfCar)
		: VehicleImpl(placeCount)
		, m_makeOfCar(makeOfCar)
	{
	}

	~CarImpl() = default;

	const MakeOfCar m_makeOfCar;
};