# Lab 3 - Object-Oriented Programming with C++ Part 2 & Extras
## Files
### Reading & Writing
Files can be created, written to & read from in C++. There are three objects in the standard library ```std``` that can be used for operating upon files. The ```ofstream``` object can be used to create & output a file, the ```ifstream``` object for reading from a file & lastly ```fstream```, which can be used for both purposes. Below is an example from [ReadingAndWriting](/Lab3/Examples/ReadingAndWriting/) of these file operations together:
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
Files use file-position pointers to determine where they are currently being operated on. By default, the file-position pointer starts at the beginning of the file's contents. However, in order to read text from files from specific points, the use of the ```seekg()``` function can be used to shift the file-position pointer. In the code from [PositionPointers1](/Lab3/Examples/PositionPointers1/) demonstrated below, only the second line of the file is printed:

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

There are additional ways in which to operate on file-position pointers. In the example from [PositionPointers2](/Lab3/Examples/PositionPointers2/) below, ```ios::end``` first positions the pointer to the end of the file. Next, the pointer is decremented by 27 characters in relation to this:

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
It is possible to convert the outward appearance of an object's class type into that of another through casting. In doing so, the object becomes treated as though it derives from a different class type in the program. An example of polymorphic casting from [PolymorphismCasting](/Lab3/Examples/PolymorphismCasting/) is displayed below:

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	Colour* AmbiguousColour = new Colour("Ambiguous");
	Red* TypeofColour = new Red("Red");

    //Pointer to 'Red' object is of type 'Colour*,' but holds an object of type 'Red'
	Colour* TechnicallyRed = (Colour*)TypeofColour;

	delete AmbiguousColour;
	delete TypeofColour;
}

Colour::Colour(string typeIn)
{
	type = typeIn;
}
```

It is important to note that casting in this way introduces the possibility of errors if not handled correctly. Errors can ensue if an attempt to access an apparent, but non-existent member of an object is attempted; attempts to access members that only exist within the casted derived class that do not derive from the actual derived class will cause errors. For this reason, generally this form of casting is used to make an object appear to be derived from a superclass, rather than an unrelated one.

An example of where casting an object's class type is useful is for containers. For example, one may have an array of the class type ```Bird```, however there may be many subclasses of type ```Bird```, such as ```Parrot```, ```Pigeon``` & ```Peacock```. Since the array can only take objects of type ```Bird```, one may ambiguify the objects entering so as to all appear as though they are of type ```Bird``` & then disambiguify/recast them back to their actual existing types once they are accessed.

Additionally, where a function's parameter may need to take various types of objects, the parameter may be set to take a generic object so as to allow for other objects to be casted to it in order to be passed through.

### Task 3
The code in [Task 3](/Lab3/Tasks/Task3/) is incomplete. Currently existing is the ```Item``` class, as well as two subclasses of it, the ```Rock``` & ```Stick``` classes. The code is intended to do as follows:
- The first for loop is to randomly assign either a ```Rock``` or ```Stick``` to all of the ```Inventory``` array's 9 slots.
- The second for loop is to recast the array's contents back to their original class types & then execute either the ```Throw()``` or ```Attack()``` function on them based on the given object's type.

Your task is to implement the missing components of the code.

## Virtual Functions
When using polymorphism to access a function of an object's inherited class, that function is considered an implementation within the superclass as opposed to the subclass. However, there are cases where the function may need to differ to some extent depending upon the subclass in question. In order to do this, the function can be declared with the ```virtual``` keyword in the class that it is a member of. When this is done, subclasses can re-define the function using the ```override``` keyword. If this is done, then the function can be re-implemented. This is shown in the [VirtualFunctions](/Lab3/Examples/VirtualFunctions/) example below:

**Header**
```c++
#pragma once

#include <string>

using namespace std;

class Dragon {
public:
	Dragon(string nameIn);
	virtual void Roar(); //Function declared as virtual; allows it to be reimplemented in subclasses
protected:
	string name;
};

class BigDragon : Dragon {
public:
	BigDragon(string nameIn) : Dragon(nameIn) {}
	virtual void Roar() override; //Virtual function from superclass overriden & reimplemented
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	Dragon* NewDragon = new Dragon("Richard");
	BigDragon* NewDragon2 = new BigDragon("Michael");
	NewDragon->Roar();
	NewDragon2->Roar();
}

Dragon::Dragon(string nameIn)
{
	name = nameIn;
}

void Dragon::Roar()
{
	cout << name << " roared!\n";
}

//Virtual function from superclass overriden & reimplemented
void BigDragon::Roar()
{
	cout << name << " roared loudly!\n";
}
```

## Static Members
Normally, one cannot directly access a class member but instead must access an instance of one from an object derived from a class. Since normally there may be multiple instances of objects, there are by extension never any common implementations of any object members across all of these objects. However, this can be changed with the use of the ```static``` keyword.

By declaring a class's member as ```static```, only one implementation of the member is able to exist & becomes common to all instances of objects derived from the respective class. For this reason, the member becomes accessible from the class directly & cannot be accessed from any derived object.

For example ...

**Header**
```c++

```

**CPP**
```c++

```

It is worth being aware that in some object-oriented languages, classes themselves can be declared as ```static```. Generally, when this is done, the entire class's contents become static. This feature does not exist in C++, however to more or less replicate such a scenario, one can declare all of a class's members as ```static```.

## Virtual Classes
Unlike singular inheritance, multiple inheritance can pose the issue of ambiguity in the class hierarchy. For example, consider the four classes, ```Class Base```, ```Class A```, ```Class B``` & ```Class C```, in the following diagram:

![Virtual Classes Diagram](/Lab3/Examples/VirtualClasses/VirtualClassesDiagram.png)

```Class Base``` is a base class that both ```Class A``` & ```Class B``` derive from. So far, this presents no particular errors. However, ```Class C``` inherits directly from both ```Class A``` & ```Class C``` through multiple inheritance. Due to this, ```Class C``` acquires not one, but two copies of ```Class Base```. This is problematic because if an instance of ```Class C``` attempts to make use of any members from either ```Class Base```, the program will not compile as it will be unable to differentiate between which ```Class Base``` is or needs to be accessed.

[Change this]
To solve this, inheritance of ```Base Class``` can be prefixed with the keyword ```virtual```. Note, this is not related to the concept of [Virtual Functions](#virtual-functions), as explained earlier in this lab. This is demonstrated in the code from [VirtualClasses](/Lab3/Examples/VirtualClasses/) below:

**Header**
```c++
#pragma once

#include <string>

using namespace std;

class Base {
public:
	Base(string nameIn);
	void Hello();
protected:
	string name;
};

//Inherits class 'Base' virtually
class A : virtual public Base {
public:
	A(string nameIn) : Base(nameIn) {}
};

//Inherits class 'Base' virtually
class B : virtual public Base {
public:
	B(string nameIn) : Base(nameIn) {}
};

//Inherits both class 'A' & 'B' that both inherit the 'Base' class virtually; result is only one 'Base' class is inherited by class 'C'
class C : public A, public B {
public:
	//Must also initialise a single 'Base' class constructor, along with the constructors of Class 'A' & 'B'
	C(string nameIn) : Base(nameIn), A(nameIn), B(nameIn) {}
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	C* Felix = new C("Felix");
	Felix->Hello();
}

Base::Base(string nameIn)
{
	name = nameIn;
}

void Base::Hello()
{
	cout << "Hello! " << "my name is " << name << "\n";
}
```

## Interfaces