#include "stdafx.h"
#include "Car.h"

using namespace std;

void PrintMenu()
{
	cout << "|-------------------|\n1- Info \n2 - EngineOn \n3 - EngineOff \n4 - SetGear \n5 - SetSpeed\n0 - Exit\n|-------------------|" << endl;
}

void Menu(int choise, CCar* obj)
{
	int choiseSpeed, choiseGear;
	if (choise == 1)
	{
		if (obj->IsTurnedOn())
			cout << "Engine On" << endl;
		else
			cout << "Engine Off" << endl;
		cout << "Speed = " << obj->GetSpeed() << endl;
		cout << "Gear = " << obj->GetGear() << endl;
		if (obj->GetDirection() == 1)
			cout << "Car moves straight" << endl;
		else if (obj->GetDirection() == 0)
			cout << "Car not moving" << endl;
		else
			cout << "Car moves back" << endl;
	}
	if (choise == 2)
	{
		if (!obj->TurnOnEngine())
			cout << "Can't turn on engine!" << endl;
	}
	if (choise == 3)
	{
		if (!obj->TurnOffEngine())
			cout << "Can't turn off engine!" << endl;
	}
	if (choise == 4)
	{
		cout << "Write gear: ";
		cin >> choiseGear;
		if (!obj->SetGear(choiseGear))
			cout << "Can't change gear!" << endl;
	}
	if (choise == 5)
	{
		cout << "Write speed: ";
		cin >> choiseSpeed;
		if (!obj->SetSpeed(choiseSpeed))
			cout << "Can't change speed!" << endl;
	}
}

int main()
{
	int answer;
	CCar* obj = new CCar;
	do
	{
		PrintMenu();
		cout << "Your choise: ";
		cin >> answer;
		Menu(answer, obj);
	} while (answer != 0);
	system("Pause");
	return 0;
}