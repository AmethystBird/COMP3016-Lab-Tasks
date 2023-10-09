# Lab 2 - Object-Oriented Programming with C++ Part 1
**Note: Content on file reading & writing has been moved to Lab 3.**
## Classes & Objects
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

## Members
In a class, a member is any function or variable that exists at the scope of the entire class. Therefore, a member variable or function is accessable from at least anywhere from within the class that it is contained in. Importantly, it is best practice that class declarations, as well as all of a class's members are placed within an appropriate header file. All implementations of member functions & instantiations of member variables should be contained within an appropriate CPP file.

The example below from [Members](/Lab2/Examples/AccessSpecifiers/) demonstrates how to implement member variables & functions. However, note the use of the ```public``` keyword. This is necessary & its use is explained further in this lab in the [Access Specifiers](#access-specifiers) section.

**Header**
```c++
#pragma once

using namespace std;

class Apple {
public: //The 'public' keyword is necessary; explained later
	void Eat();
	bool isOnlyCoreLeft;
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	Apple* PickedApple = new Apple();
	PickedApple->Eat();
	PickedApple->Eat();
	delete PickedApple;
}

//function implementations always require class prefix, followed by '::' behind name
void Apple::Eat()
{
	if (isOnlyCoreLeft == false)
	{
		cout << "This apple has been eaten." << "\n";
		isOnlyCoreLeft = true;
	}
	else
	{
		cout << "You can't eat apple cores! The seeds have cyanide in them.\n";
	}
}
```

## Constructors
Sometimes, when an object is instantiated, certain tasks must be completed or certain additional inputs must be given. This can be done through a class constructor, which is a class's member function that must run on the instantiation of any object of that class. Constructors are always named after the class itself. The example below from [Constructors](/Lab2/Examples/Constructors/) demonstrates using a constructor:

**Header**
```c++
#pragma once

using namespace std;

class Apple {
public: //The 'public' keyword is necessary; explained later
	Apple(int replenishmentIn);
	int replenishment;
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	Apple* PickedApple = new Apple(4);
	cout << "Apple replenishment value: " << PickedApple->replenishment << "\n";
	delete PickedApple;
}

Apple::Apple(int replenishmentIn)
{
	replenishment = replenishmentIn;
}
```

## Scope
### Access Specifiers
By default, member functions & variables contained within an object cannot be read from or written to from outside of the object. The purpose of restricting access to variables & functions within an object from outside of the object is to prevent accidental & unintentional operations on members of objects from areas of code that would never need to be able to do so. This helps to prevent the accumulation of bugs. However, accessibility can be & should be flexible where appropriate.

The ability to change the scope by which members can be accessed is done through access specifiers. There are three main types, ```public```, ```protected``` & ```private```. The private specifier is the default setting, denying any direct access from outside the class. The public specifier, in contrast, allows complete direct access from outside the class. Lastly, the protected specifier exists as a kind of middle ground. It prevents direct access from outside the class, however it allows for direct access from [subclasses](#inheritance).

Below is an example from [AccessSpecifiers1](/Lab2/Examples/AccessSpecifiers1/) demonstrating access specification. For clarification on subclasses however, see the [Inheritance](#inheritance) section.

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

It is worth noting that for a ```protected``` or ```public``` access specifier to apply to a subclass of another, that the inherited class must also be given the appropriate access specifier. This is shown in the [AccessSpecifiers2](/Lab2/Examples/AccessSpecifiers2/) example:

**Header**
```c++
#pragma once

#include <string>

using namespace std;

class Fruit {
public:
	Fruit(string nameIn);
	string name;
};

//Without 'public Fruit' specification, the 'name' variable would be inaccessible
class Apple : public Fruit {
public:
	Apple(string nameIn) : Fruit(nameIn) {}
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	Apple* PickedApple = new Apple("Red Apple");
	cout << "Player picked a " << PickedApple->name << ".\n";
	delete PickedApple;
}

Fruit::Fruit(string nameIn)
{
	name = nameIn;
}
```

### Task 1
In [Task 1](/Lab2/Tasks/Task1/), the code is currently broken. This is due to various unimplemented or incomplete object-orientation components that need to be amended for. Your task is to fix the code.

### Task 2
The code located in [Task 2](/Lab2/Tasks/Task2/) is broken. The reasons for the code not functioning correctly are not related to the contents of the functions, but rather due to various errors in the program's implementation of object-orientation. Your task is to fix these errors so that the code compiles.

### Getters & Setters
While not the case with member functions, it is best practice to keep all member variables private to a class to restrict all direct access from outside. However, the reason that this is done is not because access to these variables should never be given, but due to the use of getters & setters to utilise indirect access instead. In doing so, one can better restrict in what capacity member variables can be accessed.

Getters & setters are public functions that allow one to read from (get) & write to (set) private member variables. Since they are functions, they can allow for indirect access to reading & writing of variables or the calling of functions that would normally be out of scope, but that are within the scope of the getter or setter.

Getters & setters are important for instances where one member variable's value is dependent upon other variable conditions. Using getters & setters can automate & enforce these requirements. An example of how getters & setters can be used from [GettersAndSetters](/Lab2/Examples/GettersAndSetters/) is shown below:

**Header**
```c++
#pragma once

#include <string>

using namespace std;

class Player {
public:
	Player();

	void Walk();
	void Run();

	//Public getters & setters for private variables.
	int GetHunger();
	void SetHunger(int hungerIn);
	int GetSpeed();
	void SetSpeed(int speedIn);

private:
	void Exhausted(string movementModeIn);

	//Private. Variables depend upon each other; changing one without changing the other can produce issues
	int hunger;
	int speed;
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	Player* Boris = new Player();
	Boris->Run();
	Boris->Walk();

	Boris->SetHunger(4); //This will also set Boris's speed to 1
	Boris->Run();
	Boris->Walk();

	Boris->SetSpeed(2); //This will not set Boris's speed to 2, since his hunger level does not allow it
	cout << "Boris's current speed: " << Boris->GetSpeed() << "\n";
	Boris->Run();
}

Player::Player()
{
	hunger = 20;
	speed = 2;
}

void Player::Walk()
{
	if (speed >= 1)
	{
		cout << "Player walked.\n";
	}
	else if (speed == 0)
	{
		Exhausted("walk");
	}
}

void Player::Run()
{
	if (speed == 2)
	{
		cout << "Player ran!\n";
	}
	else if (speed <= 1)
	{
		Exhausted("run");
	}
}

int Player::GetHunger()
{
	return hunger;
}

void Player::SetHunger(int hungerIn)
{
	hunger = hungerIn;

	//If necessary, lowers speed to level that hunger allows
	if (hunger <= 5 && GetSpeed() == 2)
	{
		SetSpeed(1);
	}
}

int Player::GetSpeed()
{
	return speed;
}

void Player::SetSpeed(int speedIn) 
{
	//Checks if speed level can be set, requiring that hunger level allows it
	if (speedIn == 2 && GetHunger() < 5)
	{
		return;
	}
	speed = speedIn;
}

void Player::Exhausted(string movementModeIn)
{
	cout << "Player is too exhausted to " << movementModeIn << "\n";
}
```

## Inheritance
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
## Superclass Constructors
Unlike most members of classes, constructors do not follow the specifications set by access specifiers. Constructors must be public, since if they do exist, they must be called from outside of the class they are a member of in order to instantiate an object of said class.

In the case of subclasses, the constructors of any of the above superclasses will always be private & are not inherited by default. However, there is a workaround to this. A subclass can define its own constructor & call upon its superclass constructor. In this case, as in the [SuperclassConstructors](/Lab2/Examples/SuperclassConstructors/) example, the CPP file contains no implemented constructor for the subclass:

**Header**
```c++
#pragma once

#include <string>

using namespace std;

class Animal {
public:
	Animal(string nameIn);
	string name;
};

//Inherited from 'Animal' & calls 'Animal' constructor.
class Chicken : Animal {
public:
	//The 'Chicken' class implements the 'Animal' constructor
	Chicken(string nameIn) : Animal(nameIn) {}
	void LayEgg();
};
```

**CPP**
```c++
#include "main.h"

#include <iostream>

int main()
{
	Animal* Dmitri = new Animal("Dmitri");
	Chicken* Rufus = new Chicken("Rufus");
	Rufus->LayEgg();
	delete Dmitri;
	delete Rufus;
}

Animal::Animal(string nameIn)
{
	name = nameIn;
}

//Only the 'Chicken' class needs an implemented constructor
void Chicken::LayEgg()
{
	cout << name << " laid an egg!\n";
}
```

## Multiple Inheritance
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

## Task 3
There are various classes declared in [Task 3](/Lab2/Tasks/Task3/) with commenting to describe their relations to each other & whether to call superclass constructors from a subclass. Your task is to implement the correct class hereditary, as well as to apply the calling of superclass constructors in subclasses where deemed appropriate.