#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ofstream fileToWrite("myFile.txt"); //Creates file in project directory

    fileToWrite << "Welcome to Lab 2!";

    fileToWrite.close(); //Closes file

    string fileOutput;

    ifstream fileToRead("myFile.txt"); //Reopens file for reading

    getline(fileToRead, fileOutput); //Acquires the first line of 'myFile.txt' & sets the 'fileOutput' variable's value to it
    cout << fileOutput << "\n";

    fileToRead.close();
}