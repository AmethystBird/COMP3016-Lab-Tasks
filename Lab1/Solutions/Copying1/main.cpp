#include <iostream>

using namespace std;

int main()
{
    int originalNumber = 64;
    int& referenceToNumber = originalNumber; //The '&' is used to declare a reference
    int copyOfNumber = originalNumber;
    cout << "Copy by Reference: " << referenceToNumber << "\n";
    cout << "Copy by Value: " << copyOfNumber << "\n";
}