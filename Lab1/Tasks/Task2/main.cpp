#include <iostream>

using namespace std;

int main()
{
    const int numbersSize = 5;
    const int resultsSize = numbersSize * numbersSize;
    int numbers[numbersSize] = { 27, 15, 83, 16, 8 };
    int numbers2[numbersSize] = { 7, 92, 87, 37, 2 };
    int results[resultsSize];

    cout << "Standard Indexing:" << "\n";
    for (int i = 0; i < numbersSize; i++)
    {
        for (int i2 = 0; i2 < numbersSize; i2++)
        {
            results[i * i2] = numbers[i] + numbers2[i2];
            cout << results[i * i2] << "\n";
        }
    }

    cout << "Pointer Indexing:" << "\n";
}