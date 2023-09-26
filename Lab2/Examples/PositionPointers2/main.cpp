#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ofstream fileToWrite("myFile.txt");
    fileToWrite << "This first line won't be printed.\nHowever, this line will be.\n";
    fileToWrite.close();
    string fileOutput;
    ifstream fileToRead("myFile.txt");
    cout << "Position: " << fileToRead.tellg() << "\n";

    //Shifts backwards by 27 characters from the last position
    fileToRead.seekg(-29, ios::end);
    cout << "Position: " << fileToRead.tellg() << "\n";

    //When getline() is called, the file-position pointer moves to the end of the acquired line (the start of the next line)
    getline(fileToRead, fileOutput);
    cout << "Position: " << fileToRead.tellg() << "\n";

    cout << fileOutput << "\n";
    fileToRead.close();
}