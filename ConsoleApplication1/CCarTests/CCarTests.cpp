// CCarTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../ConsoleApplication1/Car.h"

struct CCarFixture
{
	CCar carTest;
};

/*
	Тесты для 3ей лабы, 2ое задание:
	- Проверка, включен ли двигатель изначально
	- Можно ли включить двигатель
	- Можно ли выключить двигатель (в состоянии покоя, когда движется, когда передача != 0)
	- Можно ли при нейтральной передачи переключиться на первую или заднюю
	- Проверить направление движения (при положительной скорости, при отрицательной скорости)
	- Можно ли переключиться с задней передачи на первую
	- Переключение передачи саму на себя
	- С заднего хода на нейтральную при 0 скорости
	- С заднего хода на нейтральную при не 0 скорости
	- Со 2й передачи на нейтральную
	- Со скоростью 10 нейтральную включить
	- Со 2 передачи на 4 переключить
	- Переключить передачу с недопустимой скоростью
	- На 1й передаче при скорости 10 заднюю включить и наоборот
*/

BOOST_FIXTURE_TEST_SUITE(Car, CCarFixture)

BOOST_AUTO_TEST_CASE(TurnedOnByDefault)
{
	BOOST_CHECK(!carTest.IsTurnedOn());
}

BOOST_AUTO_TEST_CASE(CanBeTurnedOn)
{
	BOOST_CHECK(carTest.TurnOnEngine());
	BOOST_CHECK(carTest.IsTurnedOn());
}

BOOST_AUTO_TEST_CASE(CanBeTurnedOff)
{
	{
		carTest.TurnOnEngine();
		BOOST_CHECK(carTest.TurnOffEngine());
		BOOST_CHECK(!carTest.IsTurnedOn());
	}
		
	{
		carTest.TurnOnEngine();
		BOOST_CHECK(carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
		BOOST_CHECK(carTest.SetSpeed(20));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
		BOOST_CHECK(carTest.SetGear(0));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
		BOOST_CHECK(!carTest.TurnOffEngine());
	}

	{
		carTest.TurnOnEngine();
		BOOST_CHECK(carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
		BOOST_CHECK(!carTest.TurnOffEngine());
	}
}

BOOST_AUTO_TEST_CASE(ChangeGearFrom0To1AndMinus1)
{
	{
		carTest.TurnOnEngine();
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
		BOOST_CHECK(carTest.SetGear(-1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
	}

	{
		carTest.TurnOnEngine();
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
		BOOST_CHECK(carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	}
}

BOOST_AUTO_TEST_CASE(CheckDirection)
{
	{
		carTest.TurnOnEngine();
		BOOST_CHECK(carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
		BOOST_CHECK(carTest.SetSpeed(20));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
		BOOST_CHECK_EQUAL(carTest.GetDirection(), 1);
	}

	{
		carTest.TurnOnEngine();
		BOOST_CHECK(carTest.SetGear(-1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
		BOOST_CHECK(carTest.SetSpeed(20));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
		BOOST_CHECK_EQUAL(carTest.GetDirection(), -1);
	}
}

BOOST_AUTO_TEST_CASE(ChangeGearFromMinus1To1)
{
	carTest.TurnOnEngine();
	BOOST_CHECK(carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
	BOOST_CHECK(carTest.SetGear(1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
}

BOOST_AUTO_TEST_CASE(SelfSwitch)
{
	carTest.TurnOnEngine();
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
	BOOST_CHECK(carTest.SetGear(0));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
}

BOOST_AUTO_TEST_CASE(To0At0Speed)
{
	carTest.TurnOnEngine();
	BOOST_CHECK(carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 0);
	BOOST_CHECK(carTest.SetGear(0));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
}

BOOST_AUTO_TEST_CASE(To0AtNot0Speed)
{
	carTest.TurnOnEngine();
	BOOST_CHECK(carTest.SetGear(-1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
	BOOST_CHECK(carTest.SetSpeed(20));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
	BOOST_CHECK(carTest.SetGear(0));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
}

BOOST_AUTO_TEST_CASE(From2GearTo0)
{
	carTest.TurnOnEngine();
	BOOST_CHECK(carTest.SetGear(1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(20));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
	BOOST_CHECK(carTest.SetGear(2));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 2);
	BOOST_CHECK(carTest.SetGear(0));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
}

BOOST_AUTO_TEST_CASE(With10SpeedTo0Gear)
{
	carTest.TurnOnEngine();
	BOOST_CHECK(carTest.SetGear(1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(10));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 10);
	BOOST_CHECK(carTest.SetGear(0));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 0);
}

BOOST_AUTO_TEST_CASE(From2GearTo4Gear)
{
	carTest.TurnOnEngine();
	BOOST_CHECK(carTest.SetGear(1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(20));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
	BOOST_CHECK(carTest.SetGear(2));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 2);
	BOOST_CHECK(!carTest.SetGear(4));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 2);
}

BOOST_AUTO_TEST_CASE(SwitchGearWithIllegalSpeed)
{
	carTest.TurnOnEngine();
	BOOST_CHECK(carTest.SetGear(1));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	BOOST_CHECK(carTest.SetSpeed(20));
	BOOST_CHECK_EQUAL(carTest.GetSpeed(), 20);
	BOOST_CHECK(!carTest.SetGear(5));
	BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
}

BOOST_AUTO_TEST_CASE(From1GearWith10SpeedToMinus1)
{
	{
		carTest.TurnOnEngine();
		BOOST_CHECK(carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
		BOOST_CHECK(carTest.SetSpeed(10));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 10);
		BOOST_CHECK(!carTest.SetGear(-1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), 1);
	}

	{
		carTest.TurnOnEngine();
		BOOST_CHECK(carTest.SetGear(-1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
		BOOST_CHECK(carTest.SetSpeed(10));
		BOOST_CHECK_EQUAL(carTest.GetSpeed(), 10);
		BOOST_CHECK(!carTest.SetGear(1));
		BOOST_CHECK_EQUAL(carTest.GetGear(), -1);
	}
}

BOOST_AUTO_TEST_SUITE_END()