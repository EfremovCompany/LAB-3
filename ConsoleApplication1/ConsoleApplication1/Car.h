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
	void SetDirection();
private:
	bool m_isTurnedOn;
	int m_gear;
	int m_speed;
	int m_direction;
};

struct SpeedRange{
	int minSpeed;
	int maxSpeed;
};