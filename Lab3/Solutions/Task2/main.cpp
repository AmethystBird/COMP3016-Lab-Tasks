#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ofstream fileToWrite("myFile.txt");

    cout << "What's your name?\n";
    string input;
    cin >> input;
    fileToWrite << "Name: " << input << "\n";

    cout << "What's your favourite fruit?\n";
    cin >> input;
    fileToWrite << "Favourite Fruit: " << input << "\n";

    fileToWrite.close();

    string fileOutput;

    ifstream fileToRead("myFile.txt");

    while (getline(fileToRead, fileOutput))
    {
        cout << fileOutput << "\n";
    }

    fileToRead.close();
}