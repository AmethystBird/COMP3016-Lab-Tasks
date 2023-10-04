#include "main.h"

#include <iostream>

int main()
{
	C* Felix = new C("Felix");
	Felix->Hello();
}

Base::Base(string nameIn)
{
	name = nameIn;
}

void Base::Hello()
{
	cout << "Hello! " << "my name is " << name << "\n";
}