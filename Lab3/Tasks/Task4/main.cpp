#include "main.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(0));
	bool inputWeapon = false;
	string weaponType;
	Sword* NewSword = new Sword();
	Battleaxe* NewBattleaxe = new Battleaxe();

	while (inputWeapon == false)
	{
		cout << "Choose weapon: Type either 'Sword' or 'Battleaxe'\n";

		cin >> weaponType;

		if (weaponType == "Sword" || weaponType == "Battleaxe")
		{
			inputWeapon = true;
		}
		else
		{
			cout << "Your specified weapon does not exist. Please try again.\n";
		}
	}

	Enemy* Dragon = new Enemy("Dragon");

	bool weaponDestroyedOrEnemyDied = false;

	while (weaponDestroyedOrEnemyDied == false)
	{
		cout << "Choose an action by typing either 'Attack' or 'Block'\n";
		string action;
		cin >> action;
		if (action == "Attack")
		{
			if (weaponType == "Sword")
			{
				if (NewSword->Attack(Dragon) == true)
				{
					weaponDestroyedOrEnemyDied = true;
				}
			}
			else
			{
				if (NewBattleaxe->Attack(Dragon) == true)
				{
					weaponDestroyedOrEnemyDied = true;
				}
			}
		}
		else if (action == "Block")
		{
			if (weaponType == "Battleaxe")
			{
				if (NewSword->Block() == true)
				{
					weaponDestroyedOrEnemyDied = true;
				}
			}
			else
			{
				if (NewBattleaxe->Block(Dragon) == true)
				{
					weaponDestroyedOrEnemyDied = true;
				}
			}
		}
	}

	cout << "Game ended.\n";

	delete Dragon;

	if (NewSword != NULL)
	{
		delete NewSword;
	}
	if (NewBattleaxe != NULL)
	{
		delete NewBattleaxe;
	}
}

bool Weapon::Attack(Enemy* EnemyIn)
{
	bool isEnemyAlive = EnemyIn->TakeDamage(strength);
	bool isWeaponBroken = TakeWear("Attack");

	if (isWeaponBroken == true || isEnemyAlive == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Weapon::Block()
{
	return TakeWear("Block");
}

bool Weapon::TakeWear(string damageTypeIn)
{
	if (damageTypeIn == "Attack") //attacked
	{
		durability = durability - 1;
	}
	else //blocked
	{
		durability = durability - 2;
	}

	if (durability <= 0)
	{
		cout << type << " broke!\n";
		return true;
	}
	return false;
}

Enemy::Enemy(string typeIn)
{
	type = typeIn;
	health = 20;
}

bool Enemy::TakeDamage(int damageIn)
{
	health = health - damageIn;

	if (health <= 0)
	{
		cout << "Enemy perished!\n";
		return true;
	}
	return false;
}

bool Weapon::DidEnemyPerish(bool isEnemyAliveIn)
{
	if (isEnemyAliveIn == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Sword::Sword()
{
	type = "Sword";
	strength = 5;
	durability = 10;
}

bool Sword::Attack(Enemy* EnemyIn)
{
	int success = (rand() % 1);

	if (success == 0)
	{
		cout << "Successfully attacked enemy!\n";
		bool isEnemyAlive = Weapon::Attack(EnemyIn);

		return DidEnemyPerish(isEnemyAlive);
	}
	else
	{
		cout << "Enemy dodged attack.\n";
	}
	return false;
}

bool Sword::Block()
{
	int success = (rand() % 1);

	if (success == 0)
	{
		cout << "Successfully blocked attack!\n";
		if (Weapon::Block())
		{
			return true;
		}
	}
	else
	{
		cout << "Unsuccessfully blocked attack & got hit.\n";
	}
	return false;
}

Battleaxe::Battleaxe()
{
	type = "Battleaxe";
	strength = 10;
	durability = 5;
}

bool Battleaxe::Attack(Enemy* EnemyIn)
{
	int success = (rand() % 6);

	if (success == 0)
	{
		cout << "Critically hit enemy!\n";
		bool isEnemyAlive = EnemyIn->TakeDamage(strength * 2);
		bool isWeaponBroken = TakeWear("Attack");

		if (isWeaponBroken)
		{
			return TakeWear("Block");
		}

		return DidEnemyPerish(isEnemyAlive);
	}
	else if (success > 0 && success < 2)
	{
		cout << "Successfully attacked enemy!\n";
		Weapon::Attack(EnemyIn);
	}
	else
	{
		cout << "Enemy dodged attack.\n";
	}
	return false;
}

bool Battleaxe::Block(Enemy* EnemyIn)
{
	int success = (rand() % 6);

	if (success == 0)
	{
		cout << "Critically blocked enemy!\n";
		bool isEnemyAlive = EnemyIn->TakeDamage(strength / 2);

		return DidEnemyPerish(isEnemyAlive);
	}
	else if (success > 0 && success < 2)
	{
		cout << "Successfully blocked attack!\n";
		Weapon::Block();
	}
	else
	{
		cout << "Unsuccessfully blocked attack & got hit.\n";
	}
	return false;
}