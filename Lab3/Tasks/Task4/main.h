#pragma once

#include <string>

using namespace std;

class Enemy {
public:
	Enemy(string typeIn);
	bool TakeDamage(int damageIn);

protected:
	string type;
	int health;
};

class Weapon {
public:
	bool Attack(Enemy* EnemyIn);
	bool Block();
	bool TakeWear(string damageTypeIn);
	bool DidEnemyPerish(bool isEnemyAliveIn);

protected:
	string type;
	int strength;
	int durability;
};

class Sword : virtual public Weapon {
public:
	Sword();
	bool Attack(Enemy* EnemyIn);
	bool Block();
};

class Battleaxe : virtual public Weapon {
public:
	Battleaxe();
	bool Attack(Enemy* EnemyIn);
	bool Block(Enemy* EnemyIn);
};