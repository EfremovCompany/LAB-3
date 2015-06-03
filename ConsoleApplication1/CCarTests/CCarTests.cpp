// CCarTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../ConsoleApplication1/Car.h"

struct CCarFixture
{
	CCar carTest;
};

/*
	ТЕСТЫ:
	- Двигатель автомобиля может находиться как во включенном состоянии, так и в выключенном.
	- В автомобиле может быть включена одна из следующих передач:
		 Задний ход (-1)
		 Нейтральная передача (0)
		 Первая передача (1)
		 Вторая передача (2)
		 Третья передача (3)
		 Четвертая передача (4)
		 Пятая передача (5)
		 Другие передачи включить невозможно
	- На каждой передаче можно развить скорость в пределах отведенного данной передаче диапазона. 
		Задний ход: 0 – 20
		Нейтраль: Без ограничений
		Первая: 0 – 30
		Вторая: 20 – 50
		Третья: 30 – 60
		Четвертая: 40 – 90
		Пятая: 50 – 150
	- Нейтральная передача, на которой скорость можно изменить только в сторону нуля.
	- На задний ход можно переключиться только с нейтральной или первой передачи на нулевой скорости
	- C заднего хода можно переключиться на первую передачу только на нулевой скорости
	- Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости, переключиться на первую передачу можно только после остановки
*/

BOOST_FIXTURE_TEST_SUITE(Car, CCarFixture)

BOOST_AUTO_TEST_CASE(EngineCanBeTurnOnOrTurnOff)
{
	BOOST_CHECK(carTest.TurnOnEngine());
	BOOST_CHECK(carTest.IsTurnedOn());
	BOOST_CHECK(carTest.TurnOffEngine());
	BOOST_CHECK(!carTest.IsTurnedOn());
}

BOOST_AUTO_TEST_CASE(CarCanSetGearFromMinus1To5)
{
	BOOST_CHECK(carTest.TurnOnEngine());
	BOOST_CHECK(carTest.IsTurnedOn());
	BOOST_CHECK(carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
	BOOST_CHECK(carTest.SetGear(0));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
	BOOST_CHECK(carTest.SetGear(1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(20));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
	BOOST_CHECK(carTest.SetGear(2));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 2);
	BOOST_CHECK(carTest.SetSpeed(50));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 50);
	BOOST_CHECK(carTest.SetGear(3));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 3);
	BOOST_CHECK(carTest.SetGear(4));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 4);
	BOOST_CHECK(carTest.SetGear(5));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 5);
	BOOST_CHECK(!carTest.SetGear(6));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 5);
	BOOST_CHECK(!carTest.SetGear(-2));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 5);
}

BOOST_AUTO_TEST_CASE(CheckSpeedRange)
{
	{
		BOOST_CHECK(carTest.TurnOnEngine());
		BOOST_CHECK(carTest.IsTurnedOn());
		BOOST_CHECK(carTest.SetGear(-1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
		BOOST_CHECK(carTest.SetSpeed(20));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
		BOOST_CHECK(!carTest.SetSpeed(21));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
		BOOST_CHECK(!carTest.SetSpeed(-1));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
	}

	{
		BOOST_CHECK(carTest.SetGear(0));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
		BOOST_CHECK(carTest.SetSpeed(0));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
		BOOST_CHECK(carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
		BOOST_CHECK(carTest.SetSpeed(30));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 30);
		BOOST_CHECK(!carTest.SetSpeed(31));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 30);
		BOOST_CHECK(!carTest.SetSpeed(-1));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 30);
	}

	{
		BOOST_CHECK(carTest.SetGear(2));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 2);
		BOOST_CHECK(carTest.SetSpeed(20));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
		BOOST_CHECK(!carTest.SetSpeed(19));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
		BOOST_CHECK(carTest.SetSpeed(50));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 50);
		BOOST_CHECK(!carTest.SetSpeed(51));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 50);
	}

	{
		BOOST_CHECK(carTest.SetGear(3));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 3);
		BOOST_CHECK(carTest.SetSpeed(30));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 30);
		BOOST_CHECK(!carTest.SetSpeed(29));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 30);
		BOOST_CHECK(carTest.SetSpeed(60));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 60);
		BOOST_CHECK(!carTest.SetSpeed(61));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 60);
	}

	{
		BOOST_CHECK(carTest.SetGear(4));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 4);
		BOOST_CHECK(carTest.SetSpeed(40));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 40);
		BOOST_CHECK(!carTest.SetSpeed(39));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 40);
		BOOST_CHECK(carTest.SetSpeed(90));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 90);
		BOOST_CHECK(!carTest.SetSpeed(91));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 90);
	}

	{
		BOOST_CHECK(carTest.SetGear(5));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 5);
		BOOST_CHECK(carTest.SetSpeed(50));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 50);
		BOOST_CHECK(!carTest.SetSpeed(49));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 50);
		BOOST_CHECK(carTest.SetSpeed(150));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 150);
		BOOST_CHECK(!carTest.SetSpeed(151));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 150);
	}
}

BOOST_AUTO_TEST_CASE(CheckNeutralGear)
{
	BOOST_CHECK(carTest.TurnOnEngine());
	BOOST_CHECK(carTest.IsTurnedOn());
	BOOST_CHECK(carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
	BOOST_CHECK(carTest.SetSpeed(20));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
	BOOST_CHECK(carTest.SetGear(0));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
	BOOST_CHECK(carTest.SetSpeed(1));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 1);
	BOOST_CHECK(carTest.SetSpeed(0));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
	BOOST_CHECK(!carTest.SetSpeed(1));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
}

BOOST_AUTO_TEST_CASE(CheckBackGear)
{
	BOOST_CHECK(carTest.TurnOnEngine());
	BOOST_CHECK(carTest.IsTurnedOn());
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
	BOOST_CHECK(carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
	BOOST_CHECK(carTest.SetGear(1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(1));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 1);
	BOOST_CHECK(!carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(0));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
	BOOST_CHECK(carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
}

BOOST_AUTO_TEST_CASE(FromBackGear)
{
	BOOST_CHECK(carTest.TurnOnEngine());
	BOOST_CHECK(carTest.IsTurnedOn());
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
	BOOST_CHECK(carTest.SetGear(1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(20));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
	BOOST_CHECK(!carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(0));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
	BOOST_CHECK(carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
}

BOOST_AUTO_TEST_CASE(FromBackToNeutral)
{
	{
		BOOST_CHECK(carTest.TurnOnEngine());
		BOOST_CHECK(carTest.IsTurnedOn());
		BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
		BOOST_CHECK(carTest.SetGear(-1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
		BOOST_CHECK(carTest.SetSpeed(1));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 1);
		BOOST_CHECK(carTest.SetGear(0));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
		BOOST_CHECK(!carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
	}

	{
		BOOST_CHECK(carTest.SetGear(-1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
		BOOST_CHECK(carTest.SetSpeed(0));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
		BOOST_CHECK(carTest.SetGear(0));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
		BOOST_CHECK(carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	}
}

BOOST_AUTO_TEST_SUITE_END()