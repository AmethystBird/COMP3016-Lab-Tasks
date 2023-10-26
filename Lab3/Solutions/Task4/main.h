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
	virtual bool Attack(Enemy* EnemyIn);
	virtual bool Block();
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
	virtual bool Attack(Enemy* EnemyIn) override;
	virtual bool Block() override;
};

class Battleaxe : virtual public Weapon {
public:
	Battleaxe();
	virtual bool Attack(Enemy* EnemyIn) override;
	bool Block(Enemy* EnemyIn);
};