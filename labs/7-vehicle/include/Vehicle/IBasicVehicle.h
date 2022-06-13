#pragma once

class IBasicVehicle
{
public:
	virtual bool IsEmpty() const = 0;

	virtual bool IsFull() const = 0;

	virtual size_t GetPlaceCount() const = 0;

	virtual size_t GetPassengerCount() const = 0;

	virtual void RemoveAllPassengers() = 0;
};