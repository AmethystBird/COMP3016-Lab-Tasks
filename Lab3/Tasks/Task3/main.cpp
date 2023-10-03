#include "main.h"

#include <iostream>

int main()
{
	Item* Inventory[9];

	int itemType;
	for (int i = 0; i < 9; i++)
	{
		itemType = (rand() % 2);

		//Optionally cast object to superclass & add to 'Inventory' array
		if (itemType == 0) //rock
		{

		}
		else //stick
		{

		}
	}

	cout << "Inventory Contents\n";
	string typeName;
	for (int i = 0; i < 9; i++)
	{
		cout << "Slot " << i << ": ";
		typeName = Inventory[i]->type;
		cout << typeName << "\n";
		
		//Extract object & recast to correct type
		if (typeName == "Rock")
		{
			HeldRock->Throw();
		}
		else
		{
			HeldStick->Attack();
		}
	}
}

Item::Item()
{
	type = "Unspecified";
}

Rock::Rock()
{
	type = "Rock";
}

void Rock::Throw()
{
	cout << "A rock was thrown!\n";
}

Stick::Stick()
{
	type = "Stick";
}

void Stick::Attack()
{
	cout << "A stick was swung!\n";
}
