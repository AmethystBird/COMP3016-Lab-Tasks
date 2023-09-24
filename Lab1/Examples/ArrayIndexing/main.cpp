#include <iostream>

using namespace std;

int main()
{
    const int numbersSize = 4;
    int numbers[numbersSize] = { 64, 128, 256, 512 };

    for (int i = 0; i < numbersSize; i++)
    {
        cout << numbers[i] << "\n";
    }
}