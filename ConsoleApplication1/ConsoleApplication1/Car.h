#pragma once

class CCar
{
public:
	CCar();
	~CCar();
	bool IsTurnedOn()const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	int GetSpeed();
	int GetGear();
	int GetDirection();
private:
	bool m_isTurnedOn;
	int m_gear;
	int m_speed;
};

struct SpeedRange{
	int minSpeed;
	int maxSpeed;
};