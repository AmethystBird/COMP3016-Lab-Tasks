#include "main.h"

#include <iostream>

int main()
{
	Chicken* NewChicken = new Chicken("Bruce");
	TrueDragon* NewDragon = new TrueDragon("Felix");
	Wyvern* NewWyvern = new Wyvern("Greg");
	Cockatrice* NewCockatrice = new Cockatrice("Derick");

	NewCockatrice->DeathStare();
	delete NewCockatrice;
	
	NewWyvern->SpitVenom();
	NewWyvern->Fly();
	delete NewWyvern;

	NewDragon->Fly();
	NewDragon->BreatheFire();
	delete NewDragon;

	NewChicken->LayEgg();
	delete NewChicken;
}

MythicalCreature::MythicalCreature(string nameIn)
{
	name = nameIn;
	cout << "A mythical creature has been spawned!\n";
}

Creature::Creature(string nameIn)
{
	name = nameIn;
	cout << "A regular creature has been spawned!\n";
}

void Chicken::Walk()
{
	cout << name << " started walking.\n";
}

void Chicken::LayEgg()
{
	cout << name << " laid an egg!\n";
}

void TrueDragon::Walk()
{
	cout << name << " started walking.\n";
}

void TrueDragon::Fly()
{
	cout << name << " started flying.\n";
}

void TrueDragon::BreatheFire()
{
	cout << name << " started breathing fire!\n";
}

void Wyvern::Run()
{
	cout << name << " started running.\n";
}

void Wyvern::SpitVenom()
{
	cout << name << " spat venom!\n";
}

void Cockatrice::DeathStare()
{
	cout << MythicalCreature::name << " started death staring something!\n";
}
