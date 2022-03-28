#pragma once
class Car
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool PrintInfo();

private:
	int m_gear;
	int m_speed;
	bool m_isEngineRunning;
};
