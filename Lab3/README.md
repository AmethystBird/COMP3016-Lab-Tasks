# Object Orientation in C++ Part 2
## Polymorphism
### Overview
The term 'polymorphism' literally means 'many forms.' In the context of object-oriented programming, it is applied to refer to any scenario in which a class, an object or an object's members are accessed in an ambiguous form. Different types of polymorphism are beneficial for different reasons.
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


## Virtual Functions
## Virtual Classes
## Static Classes
## Interfaces