#include "main.h"

#include <iostream>

using namespace std;

int main()
{
	//Instantiating two new objects, both of which are derived from the 'Apple' class
	Apple* RedApple1 = new Apple(); //apple #1
	Apple* RedApple2 = new Apple(); //apple #2
	delete RedApple1;
	delete RedApple2;
}