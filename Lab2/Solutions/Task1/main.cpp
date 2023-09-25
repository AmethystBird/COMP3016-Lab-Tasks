#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ofstream fileToWrite("myFile.txt");

    fileToWrite << "Welcome to Lab 2!\nThis time, there are multiple lines in the file.\nTry to read all of them.";

    fileToWrite.close();

    string fileOutput;

    ifstream fileToRead("myFile.txt");

    while (getline(fileToRead, fileOutput))
    {
        cout << fileOutput << "\n";
    }

    fileToRead.close();
}