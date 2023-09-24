#include "dragon.h"

int Dragon::health; //defined here.

void Dragon::Hello()
{
	cout << "Dragon says Hello!" << "\n";
}

void Dragon::Roar()
{
	cout << "Roar!" << "\n";
}

void Dragon::Health()
{
	cout << "Dragon's health is: " << health << "\n";
}

void Dragon::TakeDamage(int damage)
{
	health = health - damage;

	if (health < 0)
	{
		health = 0;
	}
}
