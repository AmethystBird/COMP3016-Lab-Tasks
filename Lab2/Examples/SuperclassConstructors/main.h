#pragma once

#include <string>

using namespace std;

class Animal {
public:
	Animal(string nameIn);
	string name;
};

//Inherited from 'Animal' & calls 'Animal' constructor.
class Chicken : Animal {
public:
	//The 'Chicken' class implements the 'Animal' constructor
	Chicken(string nameIn) : Animal(nameIn) {}
	void LayEgg();
};