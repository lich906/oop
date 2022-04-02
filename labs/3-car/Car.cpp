#include "Car.h"
#include <map>

const std::map<int, std::pair<int, int>> gearSpeedRange = {
	{ -1, { -20, 0 } },
	{ 0, {} },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } }
};

bool Car::TurnOnEngine()
{
	m_isEngineRunning = true;

	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear != 0 || m_speed != 0)
	{
		return false;
	}

	m_isEngineRunning = false;

	return true;
}

bool Car::SetGear(int gear)
{
	if (!gearSpeedRange.contains(gear) || !IsTurnedOn())
	{
		return false;
	}

	switch (gear)
	{
	case -1:
		if (m_speed != 0)
		{
			return m_gear == gear;
		}
		m_gear = gear;
		return true;

	case 0:
		m_gear = gear;
		return true;

	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		if (m_speed < gearSpeedRange.at(gear).first || gearSpeedRange.at(gear).second < m_speed)
		{
			return false;
		}
		m_gear = gear;
		return true;

	default:
		return false;
	}
}

bool Car::SetSpeed(int speed)
{
	if (speed < 0 || !IsTurnedOn())
	{
		return false;
	}

	switch (m_gear)
	{
	case -1:
		if (-speed < gearSpeedRange.at(-1).first)
		{
			return false;
		}
		m_speed = -speed;
		return true;

	case 0:
		if (speed > abs(m_speed))
		{
			return false;
		}
		m_speed = (m_speed < 0) ? -speed : speed;
		return true;

	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		if (speed < gearSpeedRange.at(m_gear).first || gearSpeedRange.at(m_gear).second < speed)
		{
			return false;
		}
		m_speed = speed;
		return true;

	default:
		return false;
	}
}

bool Car::IsTurnedOn() const
{
	return m_isEngineRunning;
}

int Car::GetDirection() const
{
	if (m_speed >= 0)
	{
		if (m_speed == 0)
		{
			return 0;
		}

		return 1;
	}

	return -1;
}

int Car::GetSpeed() const
{
	return abs(m_speed);
}

int Car::GetGear() const
{
	return m_gear;
}
