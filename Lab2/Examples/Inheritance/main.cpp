#include "main.h"

#include <iostream>

int health = 8;

int main()
{
	Apple* NewApple = new Apple();
	cout << "Health: " << health << "\n";
	NewApple->Eat();
	cout << "Health: " << health << "\n";
	Lemon* NewLemon = new Lemon();

	NewLemon->hasLemonBeenSqueezed();
	NewLemon->Squeeze();
	NewLemon->hasLemonBeenSqueezed();
	delete NewLemon;
}

int Fruit::GetReplenishment()
{
	return replenishment;
}

void Fruit::SetReplenishment(int replenishmentIn)
{
	replenishment = replenishmentIn;
}

Apple::Apple()
{
	SetReplenishment(2);
}

void Apple::Eat()
{
	cout << "You ate an apple." << "\n";
	health = health + replenishment;
	delete this;
}

Lemon::Lemon()
{
	SetReplenishment(2);
	squeezed = false;
}

void Lemon::Squeeze()
{
	cout << "You squeezed the juice out of a lemon." << "\n";
	squeezed = true;
}

void Lemon::DrinkJuice()
{
	if (squeezed) { cout << "You drunk lemon juice." << "\n"; }
	else { cout << "You can't drink lemon juice until you've juiced a lemon first!" << "\n"; };
}

void Lemon::hasLemonBeenSqueezed()
{
	if (squeezed) { cout << "Lemon has been squeezed." << "\n"; }
	else { cout << "Lemon has not been squeezed." << "\n"; }
}