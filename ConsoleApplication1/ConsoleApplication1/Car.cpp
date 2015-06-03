// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Car.h"

const SpeedRange SpeedRangeArray[] {{ 0, 20 }, {0, 0}, { 0, 30 }, { 20, 50 }, { 30, 60 }, { 40, 90 }, { 50, 150 }};

CCar::CCar()
:m_isTurnedOn(false)
, m_gear(0)
, m_speed(0)
, m_direction(0)
{
}

CCar::~CCar()
{
}

bool CCar::IsTurnedOn()const
{
	return m_isTurnedOn;
}

bool CCar::TurnOnEngine()
{
	if (!IsTurnedOn())
	{
		m_isTurnedOn = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{

	if (!IsTurnedOn())
	{
		return false;
	}
	if (m_gear == 0 && m_speed == 0)
	{
		m_isTurnedOn = false;
		return true;
	}
	return false;
}

bool CCar::SetGear(int gear)
{
	if (gear > 5 || gear < -1)
	{
		return false;
	}
	if (!IsTurnedOn())
	{
		return false;
	}
	if (gear == m_gear)
	{
		return true;
	}
	if (gear == -1 && m_speed == 0)
	{
		m_gear = gear;
		return true;
	}
	if (gear == 0)
	{
		m_gear = gear;
		return true;
	}
	if (m_speed >= SpeedRangeArray[gear + 1].minSpeed && m_speed <= SpeedRangeArray[gear + 1].maxSpeed)
	{
		if (m_direction == 1 && gear < 0 || m_direction == -1 && gear > 0)
		{
			return false;
		}
		m_gear = gear;
		return true;
	}
	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!IsTurnedOn())
	{
		return false;
	}
	if (speed < -20 || speed > 150)
	{
		return false;
	}
	if (speed < m_speed && m_gear == 0)
	{
		m_speed = speed;
		SetDirection();
		return true;
	}
	if (speed != 0 && m_gear == 0)
	{
		return false;
	}
	if (speed <= SpeedRangeArray[m_gear + 1].maxSpeed && speed >= SpeedRangeArray[m_gear + 1].minSpeed)
	{
		if (m_direction == 1 && m_gear < 0 || m_direction == -1 && m_gear > 0)
		{
			return false;
		}
		m_speed = speed;
		SetDirection();
		return true;
	}
	return false;
}

int CCar::GetSpeed()
{
	return m_speed;
}

int CCar::GetGear()
{
	return m_gear;
}

void CCar::SetDirection()
{
	if (m_speed == 0)
	{
		m_direction = 0;
	}
	if (m_gear == -1 && m_speed != 0)
	{
		m_direction = -1;
	}
	if (m_gear > 0 && m_speed != 0)
	{
		m_direction = 1;
	}
}

int CCar::GetDirection()
{
	return m_direction;
}