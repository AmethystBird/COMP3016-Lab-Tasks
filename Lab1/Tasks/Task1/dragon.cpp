#include "dragon.h"

int Dragon::health; //defined here.

void Hello()
{
	cout << "Dragon says Hello!" << "\n";
}

void Roar()
{
	cout << "Roar!" << "\n";
}

void Health()
{
	cout << "Dragon's health is: " << health << "\n";
}

void TakeDamage(int damage)
{
	health = health - damage;

	if (health < 0)
	{
		health = 0;
	}
}
