#include "main.h"

#include <iostream>

using namespace std;

int main()
{
    originalNumber = 64; //Assigned as an object variable for purpose of demonstration
    Hello(originalNumber, originalNumber);
}

void Hello(int& number0In, int number1In)
{
    originalNumber = 128;
    cout << "Copy by Reference: " << number0In << "\n"; //No '&' needed
    cout << "Copy by Value: " << number1In << "\n";
}