#include "main.h"

#include <iostream>

int main()
{
	cout << "Grapefruits are a hybrid between the orange & the pomelo." << "\n";
}

Orange::Orange()
{
	sweetness = 5;
}

Pomelo::Pomelo()
{
	bitterness = 5;
}

//Grapefruits are notably both sweet & bitter
Grapefruit::Grapefruit(string variationIn)
{
	if (variationIn == "White")
	{
		variation = variationIn,
			sweetness = 3, bitterness = 5;
	}
	else if (variationIn == "Red" || variationIn == "Pink") //pink & red vaguely refer to the grapefruits with orange zest
	{
		variation = variationIn,
			sweetness = 4, bitterness = 2;
	}
}