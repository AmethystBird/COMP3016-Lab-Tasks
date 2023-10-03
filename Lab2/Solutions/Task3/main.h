#pragma once

#include <string>

using namespace std;

//Base
class Entity {
public:
	string name;
};

//Inherited from 'Entity' with its own constructor.
class MythicalCreature : Entity {
public:
	MythicalCreature(string nameIn);
	string name;
};

//Inherited from 'Entity' with its own constructor.
class Creature : public Entity {
public:
	Creature(string nameIn);
};

//Inherited from 'Creature' & calls 'Creature' constructor.
class Chicken : Creature {
public:
	Chicken(string nameIn) : Creature(nameIn) {}
	void Walk();
	void LayEgg();
};

//Inherited from 'MythicalCreature' & calls 'MythicalCreature' constructor.
class TrueDragon : public MythicalCreature {
public:
	TrueDragon(string nameIn) : MythicalCreature(nameIn) {}
	void Walk();
	void Fly();
	void BreatheFire();
};

//Inherited from 'TrueDragon' & calls 'TrueDragon' constructor.
class Wyvern : public TrueDragon {
public:
	Wyvern(string nameIn) : TrueDragon(nameIn) {}
	void Run();
	void SpitVenom();
};

/*
Inherits directly from both 'Chicken' & 'Wyvern' & calls 'Chicken' & 'Wyvern' constructors.
Optionally, could create new constructor, stating "A regular-mythical creature has been spawned!" as opposed to both other messages being printed.
*/
class Cockatrice : public Chicken, public Wyvern {
public:
	Cockatrice(string nameIn) : Chicken(nameIn), Wyvern(nameIn) {}
	void DeathStare();
};