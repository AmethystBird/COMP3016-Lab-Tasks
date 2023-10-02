#include "main.h"

#include <string>

#include <iostream>

using namespace std;

int main()
{
	Human* NewHuman = new Human();
	Dave* HumanCalledDave = new Dave();

	NewHuman->Hello();
	HumanCalledDave->Hello(); //calls the subclass 'Hello()' function
	HumanCalledDave->Human::Hello(); //calls the superclass 'Hello()' function

	cout << NewHuman->age << "\n";
	cout << HumanCalledDave->age << "\n"; //prints the subclass 'age' value
	cout << HumanCalledDave->Human::age << "\n"; //prints the superclass 'age' value
}

void Human::Hello()
{
	cout << "Hello!\n";
	age = 16;
}

void Dave::Hello()
{
	cout << "Hello! My name's Dave.\n";
	age = 24;
}