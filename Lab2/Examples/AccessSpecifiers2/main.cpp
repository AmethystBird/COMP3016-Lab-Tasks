#include "main.h"

#include <iostream>

int main()
{
	Apple* PickedApple = new Apple("Red Apple");
	cout << "Player picked a " << PickedApple->name << ".\n";
	delete PickedApple;
}

Fruit::Fruit(string nameIn)
{
	name = nameIn;
}
