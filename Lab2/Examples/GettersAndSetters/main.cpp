#include "main.h"

#include <iostream>

int main()
{
	Player* Boris = new Player();
	Boris->Run();
	Boris->Walk();

	Boris->SetHunger(4); //This will also set Boris's speed to 1
	Boris->Run();
	Boris->Walk();

	Boris->SetSpeed(2); //This will not set Boris's speed to 2, since his hunger level does not allow it
	cout << "Boris's current speed: " << Boris->GetSpeed() << "\n";
	Boris->Run();
}

Player::Player()
{
	hunger = 20;
	speed = 2;
}

void Player::Walk()
{
	if (speed >= 1)
	{
		cout << "Player walked.\n";
	}
	else if (speed == 0)
	{
		Exhausted("walk");
	}
}

void Player::Run()
{
	if (speed == 2)
	{
		cout << "Player ran!\n";
	}
	else if (speed <= 1)
	{
		Exhausted("run");
	}
}

int Player::GetHunger()
{
	return hunger;
}

void Player::SetHunger(int hungerIn)
{
	hunger = hungerIn;

	//If necessary, lowers speed to level that hunger allows
	if (hunger <= 5 && GetSpeed() == 2)
	{
		SetSpeed(1);
	}
}

int Player::GetSpeed()
{
	return speed;
}

void Player::SetSpeed(int speedIn) 
{
	//Checks if speed level can be set, requiring that hunger level allows it
	if (speedIn == 2 && GetHunger() < 5)
	{
		return;
	}
	speed = speedIn;
}

void Player::Exhausted(string movementModeIn)
{
	cout << "Player is too exhausted to " << movementModeIn << "\n";
}
