#pragma once

#include <string>

using namespace std;

class Food {
public:
	Food(string typeIn);
	bool GetNutritionalValue();
private:
	string type;
};

class Parrot {
public:
	Parrot(string nameIn, int maxHungerIn, int maxStaminaIn);
	void DisplayStats();
	void Eat(Food* FoodIn);
	bool HasNoHunger();
	void Fly();
	void Walk();
	bool HasNoEnergy();
private:
	string name;
	int hunger;
	int maxHunger;
	int stamina;
	int maxStamina;
};