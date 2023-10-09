#include "main.h"

#include <iostream>

int main()
{
	Apple* PickedApple = new Apple(4);
	cout << "Apple replenishment value: " << PickedApple->replenishment << "\n";
	delete PickedApple;
}

Apple::Apple(int replenishmentIn)
{
	replenishment = replenishmentIn;
}