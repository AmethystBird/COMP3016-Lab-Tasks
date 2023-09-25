#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ofstream fileToWrite("myFile.txt");

    fileToWrite << "This first line won't be printed.\nHowever, this line will be.";

    fileToWrite.close();

    string fileOutput;

    ifstream fileToRead("myFile.txt");

    fileToRead.seekg(35); //Shifts by 35 characters from starting position

    getline(fileToRead, fileOutput);
    cout << fileOutput << "\n";

    fileToRead.close();
}