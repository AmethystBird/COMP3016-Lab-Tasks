#pragma once

#include <string>

using namespace std;

class Fruit {
public:
	Fruit(string nameIn);
	string name;
};

//Without 'public Fruit' specification, the 'name' variable would be inaccessible
class Apple : public Fruit {
public:
	Apple(string nameIn) : Fruit(nameIn) {}
};