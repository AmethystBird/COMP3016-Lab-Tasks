# Lab 2 - Object Orientation in C++
## Files
### Reading & Writing
#### Overview
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
#### Task 1
In [Task 1](/Lab2/Tasks/Task1/), code similar to the above is present, except that there are multiple lines being written to the file. However, currently only one line is being outputted. Your task is to output all lines of the file elegantly - do not use repetitive code.

#### Task 2
The program in [Task 2](/Lab2/Tasks/Task2/), asks the user for the user's name & favourite fruit. However, the code is unfinished. The code needs to write the information that the user inputs to a file, then read the file & lastly print the information from the file to the terminal. Your task is to implement the rest of this program.

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

## Object-Orientation
### Classes & Objects
C++ is an object-oriented programming language. The purpose of object-orientation is to be able to divide & organise code into inter-related groups. In doing so, this also reduces code repetition.

Object-oriented programming makes use of two concepts, known as classes & objects. Classes can be described as self-contained blueprints of interdependent code. However, since classes act as blueprints, they themselves do not interact with other areas of the program they exist in. Instead, they exist as concepts. Objects, in contrast to classes, are physically existing implementations of a particular class. Objects therefore logically reflect the class they are derived from, while also existing within & influencing the rest of the program.

Notably, many objects deriving from the same class also may exist. A major benefit of this is for reducing code repetition. For example, if a procedural program contained 10 apples, the same code for 10 different apples would need to be hardcoded into the program. In an object-oriented program however, one class named ```Apple``` would be created & 10 ```objects``` of type ```Apple``` could be instantiated, as in the example from [ClassesAndObjects](/Lab2/Examples/ClassesAndObjects/) below:

**Header**
```c++
#pragma once

//Declaration of 'Apple' class
class Apple {
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

using namespace std;

int main()
{
	//Instantiating two new objects, both of which are derived from the 'Apple' class
	Apple* RedApple1 = new Apple(); //apple #1
	Apple* RedApple2 = new Apple(); //apple #2
    delete RedApple1;
    delete RedApple2;
}
```

It is **important** to note that if multiple classes are declared on the same file, that **classes declared above others will be unaware of the existence of the classes below them**, but not vice versa. If not taken into account, this can present errors if a class needs access to another in some way.

### Members
In a class, a member is any function or variable that exists at the scope of the entire class. Therefore, a member variable or function is accessable from at least anywhere from within the class that it is contained in. Importantly, it is best practice that class declarations, as well as all of a class's members are placed within an appropriate header file. All implementations of member functions & instantiations of member variables should be contained within an appropriate CPP file.

**Header**
```c++
class Apple {
	void Eat();
	bool isOnlyCoreLeft;
};
```

**CPP**
```c++
//function implementations always require class prefix, followed by '::' behind name
void Apple::Eat()
{
	cout << "This apple has been eaten." << "\n";
	isOnlyCoreLeft = true;
}
```

### Constructors
Sometimes, when an object is instantiated, certain tasks must be completed or certain additional inputs must be given. This can be done through a class constructor, which is a class's member function that must run on the instantiation of any object of that class. Constructors are always named after the class itself:

**Header**
```c++
#pragma once

class Apple {
	Apple(int replenishmentIn);
	int replenishment;
};
```

**CPP**
```c++
Apple::Apple(int replenishmentIn)
{
	replenishment = replenishmentIn;
}
```
### Scope
#### Access Specifiers
By default, member functions & variables contained within an object cannot be read from or written to from outside of the object. The purpose of restricting access to variables & functions within an object from outside of the object is to prevent accidental & unintentional operations on members of objects from areas of code that would never need to be able to do so. This helps to prevent the accumulation of bugs. However, accessibility can be & should be flexible where appropriate.

The ability to change the scope by which members can be accessed is done through access specifiers. There are three main types, ```public```, ```protected``` & ```private```. The private specifier is the default setting, denying any direct access from outside the class. The public specifier, in contrast, allows complete direct access from outside the class. Lastly, the protected specifier exists as a kind of middle ground. It prevents direct access from outside the class, however it allows for direct access from [subclasses](#inheritance).

Below is an example from [AccessSpecifiers](/Lab2/Examples/AccessSpecifiers/) demonstrating access specification. For clarification on subclasses however, see the [Inheritance](#inheritance) section.

**Header**
```c++
#pragma once

#include <string>

class Apple {
public:
	Apple(int replenishmentIn);
	void Eat(); //needs to be executed from outside in order to be eaten
protected:
	int replenishment; //may vary for different apples
private:
	bool isEdible; //apples of all kinds are always edible; shouldn't change
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

using namespace std;
int health = 8;
int main()
{
	Apple* RedApple = new Apple(2);
	cout << "Health before eating: " << health << "\n";
	RedApple->Eat();
	cout << "Health after eating: " << health << "\n";
}

Apple::Apple(int replenishmentIn)
{
	replenishment = replenishmentIn;
	isEdible = true;
}

void Apple::Eat()
{
	if (isEdible == true)
	{
		health = health + replenishment;
		delete this;
	}
}
```

#### Task 3
The code located in [Task 3](/Lab2/Tasks/Task3/) is broken. The reasons for the code not functioning correctly are not related to the contents of the functions, but rather due to various errors in the program's implementation of object-orientation. Your task is to fix these errors so that the code compiles.

#### Getters & Setters
While not the case with member functions, it is best practice to keep all member variables private to a class to restrict all direct access from outside. However, the reason that this is done is not because access to these variables should never be given, but due to the use of getters & setters to utilise indirect access instead. In doing so, one can better restrict in what capacity member variables can be accessed.

Getters & setters are public functions that allow one to read from (get) & write to (set) private member variables. Since they are functions, they can also control the implications of reading & writing. This is important for instances where one member variable's value is dependent upon another member variable. In this case, if one variable's value changes, the other also must change. By using getters & setters, this automates & enforces these requirements. An example of how getters & setters can be used from [GettersAndSetters](/Lab2/Examples/GettersAndSetters/) is shown below:

**Header**
```c++
#pragma once

#include <string>

using namespace std;

class Apple {
public:
	Apple(int replenishmentIn);

	int GetReplenishment();
	void SetReplenishment(int replenishmentIn);

	string GetType();
	void SetType(string typeIn);
protected:
	int replenishment;
private:
	string type;
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	Apple* GreenApple = new Apple(3);
	cout << "Replenishment value: " << GreenApple->GetReplenishment() << "\n";
	GreenApple->SetReplenishment(2);
    delete GreenApple;
}

Apple::Apple(int replenishmentIn)
{
	SetReplenishment(replenishmentIn);
}

int Apple::GetReplenishment()
{
	return replenishment;
}

void Apple::SetReplenishment(int replenishmentIn)
{
	replenishment = replenishmentIn;

	if (replenishment == 2) { SetType("Red"); } //should be red
	else if (replenishment == 3) { SetType("Green"); } //should be green
}

string Apple::GetType()
{
	return type;
}

void Apple::SetType(string typeIn)
{
	type = typeIn;

	if (type == "red") { SetReplenishment(2); } //should give 2 health
	else if (type == "green") { SetReplenishment(3); } //should give 3 health
}
```

### Inheritance
Multiple types of classes can be defined in order to allow for multiple types of objects to be instantiated. However, sometimes objects may in part share identical code, but in other respects may differentiate. As in the situation where classes are not used, this would cause unwanted repetition of code. To avoid this, ```inheritance``` can be used.

By using inheritance, classes can be given relations to other classes in a hierarchical form. If a class inherits from another, the inheriting class is referred to as a subclass & the class being inherited from is referred to as the superclass or the parent class. The subclass will acquire all of the members of the superclass, however this is not applied vice versa.

In the code displayed below from [Inheritance](/Lab2/Examples/Inheritance/), there are three classes; the superclass named ```Fruit``` & the subclasses named ```Apple``` & ```Lemon```. All edible fruit have the attribute of being consumable, therefore ```Fruit``` has a ```replenishment``` variable. Apples & lemons are fruits, therefore they can both be consumed. However, apples are eaten & lemons instead are usually juiced to be drunk instead:

**Header**
```c++
#pragma once

#include <string>

using namespace std;

class Fruit {
public:
	int GetReplenishment();
	void SetReplenishment(int replenishmentIn);

protected:
	int replenishment;
};

class Apple : Fruit {
public:
	Apple();
	void Eat();
};

class Lemon : Fruit {
public:
	Lemon();
	void Squeeze();
	void DrinkJuice();
	void hasLemonBeenSqueezed();

private:
	bool squeezed;
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int health = 8;

int main()
{
	Apple* NewApple = new Apple();
	cout << "Health: " << health << "\n";
	NewApple->Eat();
	cout << "Health: " << health << "\n";
	Lemon* NewLemon = new Lemon();

	NewLemon->hasLemonBeenSqueezed();
	NewLemon->Squeeze();
	NewLemon->hasLemonBeenSqueezed();
	delete NewLemon;
}

int Fruit::GetReplenishment()
{
	return replenishment;
}

void Fruit::SetReplenishment(int replenishmentIn)
{
	replenishment = replenishmentIn;
}

Apple::Apple()
{
	SetReplenishment(2);
}

void Apple::Eat()
{
	cout << "You ate an apple." << "\n";
	health = health + replenishment;
	delete this;
}

Lemon::Lemon()
{
	SetReplenishment(2);
	squeezed = false;
}

void Lemon::Squeeze()
{
	cout << "You squeezed the juice out of a lemon." << "\n";
	squeezed = true;
}

void Lemon::DrinkJuice()
{
	if (squeezed) { cout << "You drunk lemon juice." << "\n"; }
	else { cout << "You can't drink lemon juice until you've juiced a lemon first!" << "\n"; };
}

void Lemon::hasLemonBeenSqueezed()
{
	if (squeezed) { cout << "Lemon has been squeezed." << "\n"; }
	else { cout << "Lemon has not been squeezed." << "\n"; }
}
```
### Superclass Constructors
Unlike most members of classes, constructors do not follow the specifications set by access specifiers. Constructors must be public, since if they do exist, they must be called from outside of the class they are a member of in order to instantiate an object of said class.

In the case of subclasses, the constructors of any of the above superclasses will always be private & are not inherited by default. However, there is a workaround to this. A subclass can define its own constructor & call upon its superclass constructor.

[EXAMPLE NEEDED]

**Header**
```c++
```

**CPP**
```c++
```

### Multiple Inheritance
In certain cases, a class may share commonalities with not just one, but multiple other classes. For example, the grapefruit is a species of citrus fruit that is a hybrid of both oranges & pomelos. For this reason, it shares certain characteristics of both oranges & pomelos. In cases such as this, multiple inheritance can be used in order to allow for a class to derive from many superclasses. The example code from [MultipleInheritance](/Lab2/Examples/MultipleInheritance/) below displays how this can be achieved:

**Header**
```c++
#pragma once

#include <string>

using namespace std;

class Orange {
public:
	Orange();
	int sweetness;
};

class Pomelo {
public:
	Pomelo();
	int bitterness;
};

class Grapefruit : Orange, Pomelo {
public:
	Grapefruit(string variationIn);
private:
	string variation;
};
```
**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	cout << "Grapefruits are a hybrid between the orange & the pomelo." << "\n";
}

Orange::Orange()
{
	sweetness = 5;
}

Pomelo::Pomelo()
{
	bitterness = 5;
}

//Grapefruits are notably both sweet & bitter
Grapefruit::Grapefruit(string variationIn)
{
	if (variationIn == "White")
	{
		variation = variationIn,
		sweetness = 3, bitterness = 5;
	}
	else if (variationIn == "Red" || variationIn == "Pink") //pink & red vaguely refer to the grapefruits with orange zest
	{
		variation = variationIn,
		sweetness = 4, bitterness = 2;
	}
}
```