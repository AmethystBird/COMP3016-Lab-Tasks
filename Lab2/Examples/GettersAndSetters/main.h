#pragma once

#include <string>

using namespace std;

class Apple {
public:
	Apple(int replenishmentIn);

	int GetReplenishment();
	void SetReplenishment(int replenishmentIn);

	string GetType();
	void SetType(string typeIn);
protected:
	int replenishment;
private:
	string type;
};