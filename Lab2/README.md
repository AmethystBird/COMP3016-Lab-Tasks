# Lab 2 - Object Orientation in C++
## Files
### Reading & Writing
Files can be created, written to & read in C++. There are three objects in the standard library ```std``` that can be used for operating with files. The ```ofstream``` object can be used to create & output a file, the ```ifstream``` object for reading from a file & lastly ```fstream```, which can be used for both purposes:
```c++
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
```
### Task 1
In [Task 1](/Lab2/Tasks/Task1/), code similar to the above is present, except that there are multiple lines being written to the file. However, currently only one line is being outputted. Your task is to output all lines of the file elegantly - do not use repetitive code.

### Task 2
The program in [Task 2](/Lab2/Tasks/Task2/), asks the user for the user's name & favourite fruit. However, the code is unfinished. The code needs to write the information that the user inputs to a file, then read the file & lastly print the information from the file to the terminal. Your task is to implement the rest of this program.

### Position Pointers
```c++
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
```

### Overview
### Writing
### Reading
## Classes
### Overview
### Functions
### Constructors
### Access Specifiers
### Getters & Setters
### Inheritance
#### Single
#### Multiple
### Polymorphism