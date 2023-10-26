#pragma once

#include <string>

using namespace std;

class Item {
public:
	Item();
	string type;
};

class Rock : public Item {
public:
	Rock();
	void Throw();
};

class Stick : public Item {
public:
	Stick();
	void Attack();
};