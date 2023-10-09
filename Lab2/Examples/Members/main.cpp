#include "main.h"

#include <iostream>

int main()
{
	Apple* PickedApple = new Apple();
	PickedApple->Eat();
	PickedApple->Eat();
	delete PickedApple;
}

//function implementations always require class prefix, followed by '::' behind name
void Apple::Eat()
{
	if (isOnlyCoreLeft == false)
	{
		cout << "This apple has been eaten." << "\n";
		isOnlyCoreLeft = true;
	}
	else
	{
		cout << "You can't eat apple cores! The seeds have cyanide in them.\n";
	}
}