#pragma once

#include <string>

using namespace std;

class Base {
public:
	Base(string nameIn);
	void Hello();
protected:
	string name;
};

//Inherits class 'Base' virtually
class A : virtual public Base {
public:
	A(string nameIn) : Base(nameIn) {}
};

//Inherits class 'Base' virtually
class B : virtual public Base {
public:
	B(string nameIn) : Base(nameIn) {}
};

//Inherits both class 'A' & 'B' that both inherit the 'Base' class virtually; result is only one 'Base' class is inherited by class 'C'
class C : public A, public B {
public:
	//Must also initialise a single 'Base' class constructor, along with the constructors of Class 'A' & 'B'
	C(string nameIn) : Base(nameIn), A(nameIn), B(nameIn) {}
};