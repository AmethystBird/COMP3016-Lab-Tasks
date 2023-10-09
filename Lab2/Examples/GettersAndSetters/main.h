#pragma once

#include <string>

using namespace std;

class Player {
public:
	Player();

	void Walk();
	void Run();

	//Public getters & setters for private variables.
	int GetHunger();
	void SetHunger(int hungerIn);
	int GetSpeed();
	void SetSpeed(int speedIn);

private:
	void Exhausted(string movementModeIn);

	//Private. Variables depend upon each other; changing one without changing the other can produce issues
	int hunger;
	int speed;
};