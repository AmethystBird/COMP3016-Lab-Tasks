#pragma once

#include <string>

using namespace std;

class Dragon {
public:
	Dragon(string nameIn);
	virtual void Roar(); //Function declared as virtual; allows it to be reimplemented in subclasses
protected:
	string name;
};

class BigDragon : Dragon {
public:
	BigDragon(string nameIn) : Dragon(nameIn) {}
	virtual void Roar() override; //Virtual function from superclass overriden & reimplemented
};