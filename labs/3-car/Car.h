#pragma once
#include <string>

class Car
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool IsTurnedOn() const;
	int GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;
	std::string GetLastErrorMessage() const;

private:
	int m_gear = 0;
	int m_speed = 0;
	bool m_isEngineOn = false;
	// TODO: Дифференцировать ошибки с помощью m_lastErrorMessage
	std::string m_lastErrorMessage;
};
