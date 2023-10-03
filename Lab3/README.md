# Lab 3 - Object Orientation Part 2 & Extras
## Files
### Reading & Writing
Files can be created, written to & read from in C++. There are three objects in the standard library ```std``` that can be used for operating upon files. The ```ofstream``` object can be used to create & output a file, the ```ifstream``` object for reading from a file & lastly ```fstream```, which can be used for both purposes. Below is an example from [ReadingAndWriting](/Lab2/Examples/ReadingAndWriting/) of these file operations together:
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
In [Task 1](/Lab3/Tasks/Task1/), code similar to the above is present, except that there are multiple lines being written to the file. However, currently only one line is being outputted. Your task is to output all lines of the file elegantly by using appropriate loop iteration.

### Task 2
The program in [Task 2](/Lab3/Tasks/Task2/), asks the user for the user's name & favourite fruit. However, the code is unfinished. The code needs to write the information that the user inputs to a file, then read the file & lastly print the information from the file to the terminal. Your task is to implement the rest of this program.

### Position Pointers
Files use file-position pointers to determine where they are currently being operated on. By default, the file-position pointer starts at the beginning of the file's contents. However, in order to read text from files from specific points, the use of the ```seekg()``` function can be used to shift the file-position pointer. In the code from [PositionPointers1](/Lab2/Examples/PositionPointers1/) demonstrated below, only the second line of the file is printed:

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

There are additional ways in which to operate on file-position pointers. In the example from [PositionPointers2](/Lab2/Examples/PositionPointers2/) below, ```ios::end``` first positions the pointer to the end of the file. Next, the pointer is decremented by 27 characters in relation to this:

```c++
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
```

## Polymorphism
### Overview
The term 'polymorphism' literally means 'many forms.' In the context of object-oriented programming, it is applied to refer to any scenario in which a class, an object or an object's members are plausibly accessed in an ambiguous form. Different types of polymorphism are beneficial for different reasons.
### Inheritance
Members of a subclass can be given identical names to that of other equivalent members in a superclass. In these instances, the subclass implementation will by default override the superclass implementation. However, one can specify to use a superclass implementation of a member by using the class name, followed by ```::``` & lastly the member. The [PolymorphismInheritance](/Lab3/Examples/PolymorphismInheritance/) example demonstrates this kind of polymorphism & how to be explicit about the use of the superclass members:

**Header**
```c++
#pragma once

class Human {
public:
	void Hello();
	int age;
};

class Dave : public Human {
public:
	void Hello();
	int age;
};
```
**CPP**
```c++
#include "main.h"

#include <string>

#include <iostream>

using namespace std;

int main()
{
	Human* NewHuman = new Human();
	Dave* HumanCalledDave = new Dave();

	NewHuman->Hello();
	HumanCalledDave->Hello(); //calls the subclass 'Hello()' function
	HumanCalledDave->Human::Hello(); //calls the superclass 'Hello()' function

	cout << NewHuman->age << "\n";
	cout << HumanCalledDave->age << "\n"; //prints the subclass 'age' value
	cout << HumanCalledDave->Human::age << "\n"; //prints the superclass 'age' value
}

void Human::Hello()
{
	cout << "Hello!\n";
	age = 16;
}

void Dave::Hello()
{
	cout << "Hello! My name's Dave.\n";
	age = 24;
}
```

### Casting
It is possible to convert the outward appearance of an object's class type into that of another through casting. In doing so, the object becomes treated as though it derives from a different class type in the program. An example of polymorphic casting from [PolymorphismCasting]() is displayed below:

**CPP**
```c++

```

It is important to note that casting in this way introduces the possibility of errors if not handled correctly. Errors can ensue if an attempt to access an apparent, but non-existent member of an object is attempted; attempts to access members that only exist within the casted derived class that do not derive from the actual derived class will cause errors. For this reason, generally this form of casting is used to make an object appear to be derived from a superclass, rather than an unrelated one.

An example of where casting an object's class type is useful is for containers. For example, one may have an array of the class type ```Bird```, however there may be many subclasses of type ```Bird```, such as ```Parrot```, ```Pigeon``` & ```Peacock```. Since the array can only take objects of type ```Bird```, one may ambiguify the objects entering so as to all appear as though they are of type ```Bird``` & then disambiguify/recast them back to their actual existing types once they are accessed.

### Task 3

## Virtual Functions
## Virtual Classes
## Static Classes
## Interfaces