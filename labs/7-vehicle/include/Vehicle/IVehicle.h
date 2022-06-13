#pragma once
#include "IBasicVehicle.h"
#include <memory>

template <typename Passenger>
class IVehicle : public IBasicVehicle
{
public:
	virtual void AddPassenger(std::shared_ptr<Passenger> pPassenger) = 0;

	virtual const Passenger& GetPassenger(size_t index) const = 0;

	virtual void RemovePassenger(size_t index) = 0;
};
