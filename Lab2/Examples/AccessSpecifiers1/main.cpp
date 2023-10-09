#include "main.h"

#include <iostream>

using namespace std;
int health = 8;
int main()
{
	Apple* RedApple = new Apple(2);
	cout << "Health before eating: " << health << "\n";
	RedApple->Eat();
	cout << "Health after eating: " << health << "\n";
}

Apple::Apple(int replenishmentIn)
{
	replenishment = replenishmentIn;
	isEdible = true;
}

void Apple::Eat()
{
	if (isEdible == true)
	{
		health = health + replenishment;
		delete this;
	}
}