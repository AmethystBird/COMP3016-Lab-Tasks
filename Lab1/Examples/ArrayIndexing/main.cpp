#include <iostream>

using namespace std;

int main()
{
    const int numbersSize = 4;
    int numbers[numbersSize] = { 64, 128, 256, 512 };
    int* position = numbers;
    cout << *position << "\n"; //prints the first index of the 'numbers' array
    position++;
    cout << *position << "\n"; //prints the second index
}