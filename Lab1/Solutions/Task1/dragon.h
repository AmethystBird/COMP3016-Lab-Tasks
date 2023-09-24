#pragma once
#include <iostream>

using namespace std;

namespace Dragon
{
	void Hello();
	void Roar();
	void Health();
	void TakeDamage(int damage);
	extern int health; //functions are declared by default, but variables are not unless 'extern' is used. If this is not done, will not compile due to separate health declaration in main.h
}