#pragma once

#include <string>

using namespace std;

class Parrot {
private:
	Parrot(string nameIn, int maxHungerIn, int maxStaminaIn);
	void DisplayStats();
	void Eat(Food* FoodIn);
	bool HasNoHunger();
	void Fly();
	void Walk();
	bool HasNoEnergy();
public:
	string name;
	int hunger;
	int maxHunger;
	int stamina;
	int maxStamina;
};

class Food {
protected:
	Food(string typeIn);
	bool GetNutritionalValue();
public:
	string type;
};