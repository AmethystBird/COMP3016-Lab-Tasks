#include "main.h"

#include <iostream>

int main()
{
	int value = 17;
	int step = 10;
	int result = Maths::RoundIntegerByInteger(value, step); //Accessed from class
	cout << result << "\n";
}

int Maths::RoundIntegerByInteger(int valueIn, int stepIn)
{
	int quotient = valueIn / stepIn;
	int remainder = valueIn % stepIn;

	int lowerValue = quotient * stepIn;
	int upperValue = (quotient + 1.f) * stepIn;

	return (remainder < (stepIn / 2.f)) ? lowerValue : upperValue;
}
