#include "main.h"

#include <iostream>

int main()
{
	Parrot* ScarletMacaw = new Parrot("Derick", 20, 20);
	ScarletMacaw->Fly();
	ScarletMacaw->Walk();
	Food* Seeds = new Food("Seeds");
	ScarletMacaw->Eat(Seeds);
	ScarletMacaw->DisplayStats();
}

Food::Food(string typeIn)
{
	type = typeIn;
}

bool Food::GetNutritionalValue()
{
	if (type == "Seeds")
	{
		return 1;
	}
	else if (type == "Nut")
	{
		return 2;
	}
	return 0;
}

Parrot::Parrot(string nameIn, int maxHungerIn, int maxStaminaIn)
{
	name = nameIn;

	maxHunger = maxHungerIn;
	hunger = maxHunger;

	maxStamina = maxStaminaIn;
	stamina = maxStamina;
}

void Parrot::DisplayStats()
{
	cout << name << " has " << hunger << " hunger & " << stamina << " stamina." << "\n";
}

void Parrot::Eat(Food* FoodIn)
{
	int nutritionalValue = FoodIn->GetNutritionalValue();
	if (nutritionalValue == 1)
	{
		hunger = hunger + 4;
		stamina = stamina + 4;
	}
	else if (nutritionalValue == 2)
	{
		hunger = hunger + 8;
		stamina = stamina + 8;
	}

	if (hunger > maxHunger)
	{
		hunger == maxHunger;
	}
	if (stamina > maxStamina)
	{
		stamina == maxStamina;
	}
}

bool Parrot::HasNoHunger()
{
	if (hunger <= 0) { return true; }
	else { return false; };
}

void Parrot::Fly()
{
	cout << "Parrot started flying." << "\n";
	hunger = hunger -= 2;
	stamina = stamina -= 4;
}

void Parrot::Walk()
{
	cout << "Parrot started walking." << "\n";
	hunger = hunger -= 1;
}

bool Parrot::HasNoEnergy()
{
	if (stamina <= 0) { return true; }
	else { return false; };
}