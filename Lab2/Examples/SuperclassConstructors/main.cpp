#include "main.h"

#include <iostream>

int main()
{
	Animal* Dmitri = new Animal("Dmitri");
	Chicken* Rufus = new Chicken("Rufus");
	Rufus->LayEgg();
	delete Dmitri;
	delete Rufus;
}

Animal::Animal(string nameIn)
{
	name = nameIn;
}

//Only the 'Chicken' class needs an implemented constructor
void Chicken::LayEgg()
{
	cout << name << " laid an egg!\n";
}
