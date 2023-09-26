#pragma once

#include <string>

class Apple {
public:
	Apple(int replenishmentIn);
	void Eat(); //needs to be executed from outside in order to be eaten
protected:
	int replenishment; //may vary for different apples
private:
	bool isEdible; //apples of all kinds are always edible; shouldn't change
};