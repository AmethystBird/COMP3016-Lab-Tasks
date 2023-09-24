#include <iostream>

using namespace std;

int main()
{
    int originalNumber = 64;
    int& referenceToNumber = originalNumber;
    int copyOfNumber = originalNumber;

    originalNumber = 128;

    cout << "Copy by Reference: " << referenceToNumber << "\n";
    cout << "Copy by Value: " << copyOfNumber << "\n";
}