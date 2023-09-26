#pragma once

#include <string>

using namespace std;

class Fruit {
public:
	int GetReplenishment();
	void SetReplenishment(int replenishmentIn);

protected:
	int replenishment;
};

class Apple : Fruit {
public:
	Apple();
	void Eat();
};

class Lemon : Fruit {
public:
	Lemon();
	void Squeeze();
	void DrinkJuice();
	void hasLemonBeenSqueezed();

private:
	bool squeezed;
};