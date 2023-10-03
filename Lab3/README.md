# Lab 3 - Object Orientation in C++ Part 2
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

## Virtual Functions
## Virtual Classes
## Static Classes
## Interfaces