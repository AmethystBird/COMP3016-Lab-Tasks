#include "main.h"

#include <iostream>

int main()
{
	Pear* NewPear = new Pear();
	PassionFruit* NewPassionFruit = new PassionFruit();
	Kiwi* NewKiwi = new Kiwi();

	NewPear->Description();
	NewPassionFruit->Description();
	NewKiwi->Description();

	delete NewPear;
	delete NewPassionFruit;
	delete NewKiwi;
}

Pear::Pear(string typeIn)
{
	type = typeIn;
}

void Pear::Description()
{
	cout << type << "s taste sweet & have a crunchy texture.\n";
}

PassionFruit::PassionFruit(string typeIn)
{
	type = typeIn;
}

void PassionFruit::Description()
{
	cout << type << "s are aromatic & should be very sweet. If they are sour, they are underripe.\n";
}

Kiwi::Kiwi(string typeIn)
{
	type = typeIn;
}

void Kiwi::Description()
{
	cout << type << "s are quite aromatic & are sweet & quite sour.\n";
}
