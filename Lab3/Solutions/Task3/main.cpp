#include "main.h"

#include <iostream>

int main()
{
	Item* Inventory[9];

	int itemType;
	for (int i = 0; i < 9; i++)
	{
		itemType = (rand() % 2);
		if (itemType == 0) //rock
		{
			Rock* HeldRock = new Rock();
			Inventory[i] = (Item*)HeldRock; //casting to Item pointer
		}
		else //stick
		{
			Stick* HeldStick = new Stick();
			Inventory[i] = (Item*)HeldStick;
		}
	}

	cout << "Inventory Contents\n";
	string typeName;
	for (int i = 0; i < 9; i++)
	{
		cout << "Slot " << i << ": ";
		typeName = Inventory[i]->type;
		cout << typeName << "\n";
		
		//Checking value of commonly existing variable 'type' to correctly recast
		if (typeName == "Rock")
		{
			Rock* HeldRock = (Rock*)Inventory[i];
			HeldRock->Throw();
		}
		else
		{
			Stick* HeldStick = (Stick*)Inventory[i];
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
