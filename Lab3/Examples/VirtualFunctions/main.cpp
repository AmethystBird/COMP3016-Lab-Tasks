#include "main.h"

#include <iostream>

int main()
{
	Dragon* NewDragon = new Dragon("Richard");
	BigDragon* NewDragon2 = new BigDragon("Michael");
	NewDragon->Roar();
	NewDragon2->Roar();
}

Dragon::Dragon(string nameIn)
{
	name = nameIn;
}

void Dragon::Roar()
{
	cout << name << " roared!\n";
}

//Virtual function from superclass overriden & reimplemented
void BigDragon::Roar()
{
	cout << name << " roared loudly!\n";
}
