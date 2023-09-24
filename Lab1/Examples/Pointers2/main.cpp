#include <iostream>

using namespace std;

int main()
{
    int originalNumber = 64;
    int* pointerToNumber = &originalNumber;
    cout << pointerToNumber << "\n";
    cout << *pointerToNumber << "\n";
}