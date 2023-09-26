#include "main.h"

#include <iostream>

int main()
{
	Apple* GreenApple = new Apple(3);
	cout << "Replenishment value: " << GreenApple->GetReplenishment() << "\n";
	GreenApple->SetReplenishment(2);
	delete GreenApple;
}

Apple::Apple(int replenishmentIn)
{
	SetReplenishment(replenishmentIn);
}

int Apple::GetReplenishment()
{
	return replenishment;
}

void Apple::SetReplenishment(int replenishmentIn)
{
	replenishment = replenishmentIn;

	if (replenishment == 2) { SetType("Red"); } //should be red
	else if (replenishment == 3) { SetType("Green"); } //should be green
}

string Apple::GetType()
{
	return type;
}

void Apple::SetType(string typeIn)
{
	type = typeIn;

	if (type == "red") { SetReplenishment(2); } //should give 2 health
	else if (type == "green") { SetReplenishment(3); } //should give 3 health
}