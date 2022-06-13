#pragma once
#include "..\IVehicle.h"
#include<vector>
#include<stdexcept>

template <class Base, typename Passenger>
class VehicleImpl : public Base
{
public:
	bool IsEmpty() const final
	{
		return !m_passengers.size();
	}

	bool IsFull() const final
	{
		return m_passengers.size() == m_placeCount;
	}

	size_t GetPlaceCount() const final
	{
		return m_placeCount;
	}

	size_t GetPassengerCount() const final
	{
		return m_passengers.size();
	}

	void RemoveAllPassengers() final
	{
		m_passengers.clear();
	}

	void AddPassenger(std::shared_ptr<Passenger> pPassenger) final
	{
		if (IsFull())
			throw std::logic_error("Failed to add passenger to vehicle, no free places left");

		m_passengers.push_back(pPassenger);
	}

	const Passenger& GetPassenger(size_t index) const final
	{
		if (index >= m_passengers.size())
			throw new std::out_of_range("Failed to get passenger at index");

		return *m_passengers[index];
	}

	void RemovePassenger(size_t index) final
	{
		if (index >= m_passengers.size())
			throw new std::out_of_range("Failed to get passenger at index");
		
		m_passengers.erase(m_passengers.begin() + index);
	}

protected:
	VehicleImpl(size_t placeCount)
		: m_placeCount(placeCount)
	{
	}

	~VehicleImpl() = default;

	std::vector<std::shared_ptr<Passenger>> m_passengers;
	const size_t m_placeCount;
};